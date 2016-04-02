// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * main.cpp - main app of the general dependency parser.        *
 *                                                              *
 * Meishan Zhang   2015.01                                         *
 *                                                              *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "depsem.h"
#include "reader.h"
#include "writer.h"
#include "stdlib.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * decode
 *
 *==============================================================*/

void process(const std::string sInputFile, const std::string sOutputFile, const std::string sFeatureFile, unsigned long nBest,
		const bool bScores, const std::string &sMetaPath, const std::string &sStackingPath) {

   std::cout << "Parsing started" << std::endl;

   int time_start = clock();

   CDepParser parser(sFeatureFile, false);
#ifdef SUPPORT_META_FEATURE_DEFINITION
   if (!sMetaPath.empty() )
      parser.loadMeta(sMetaPath);
#endif

   std::ifstream is(sInputFile.c_str());
   assert(is.is_open());

   std::ofstream os(sOutputFile.c_str());
   std::ofstream *os_scores=0;
   depsem::SCORE_TYPE *scores=0;
   assert(os.is_open());

   //CTwoStringVector input_sent;
   CDependencyParse ref_sent;
   CDependencyParse *outout_sent; 

   CSTackFeatsVec  stackfeats;
   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
	   isstack.open(sStackingPath.c_str());
	   assert(isstack.is_open());
   }

   int nCount=0;
   bool bReadSuccessful;

   if (bScores) {
      scores = new depsem::SCORE_TYPE[nBest];
      os_scores = new std::ofstream(std::string(sOutputFile+".scores").c_str());
   }



   outout_sent = new CDependencyParse[nBest];
 
   // Read the next example

   //bReadSuccessful = input_reader->readTaggedSentence(&input_sent, false, TAG_SEPARATOR);
   while(is>>ref_sent ) {

      TRACE("Sentence " << nCount);
      ++ nCount;

      if(isstack.is_open())
      {
    	   stackfeats.clear();
    	   std::string line;
    	   getline(isstack, line);

    	   while(isstack && !line.empty())
    	   {
    		   depsem::CStackFeats node;
    		   std::istringstream iss(rstrip(line));
    		   iss >> node ;
    		   stackfeats.push_back( node );
    		   getline(isstack, line);
    	   }
      }


      // check size
      if (ref_sent.size() > depsem::MAX_SENTENCE_SIZE) {
         WARNING("The sentence is longer than system limitation, skipping it.");
         for (unsigned i=0; i<nBest; ++i) {
            outout_sent[i].clear();
            if (bScores) scores[i]=0;
         }
      }
      else {
         parser.parse( ref_sent, stackfeats, outout_sent, nBest , scores ) ;
      }
      
      // Ouptut sent
      for (unsigned i=0; i<nBest; ++i) {
         os << outout_sent[i] ;
         if (bScores) *os_scores << scores[i] << std::endl;
      }

   }

   delete [] outout_sent ;
   os.close();

   if (bScores) {
      os_scores->close();
      delete os_scores;
      delete []scores;
   }

   if(!sStackingPath.empty())
   {
	   isstack.close();
   }

   std::cout << "Parsing has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
}

/*===============================================================
 *
 * main
 *
 *==============================================================*/

int main(int argc, char* argv[]) {

	//TODO This is temporary! Allow user to enter their own lexicons.

   try {
      COptions options(argc, argv);
      CConfigurations configurations;
      configurations.defineConfiguration("n", "N", "N best list outout", "1");
      configurations.defineConfiguration("s", "", "outout scores to outout_file.scores", "");
      configurations.defineConfiguration("e", "path", "external features for stacking", "");
#ifdef SUPPORT_META_FEATURE_DEFINITION
      configurations.defineConfiguration("t", "path", "meta feature types", "");
#endif
      // check arguments
      if (options.args.size() != 4) {
         std::cout << "Usage: " << argv[0] << " input_file outout_file model_file" << std::endl;
         std::cout << configurations.message() << std::endl;
         return 1;
      }
      configurations.loadConfigurations(options.opts);
   
      unsigned long nBest = 1;
      if (!fromString(nBest, configurations.getConfiguration("n"))) {
         std::cout << "The N best specification must be an integer." << std::endl;
         return 1;
      }
      bool bScores = configurations.getConfiguration("s").empty() ? false : true;
      std::string sMetaPath;
#ifdef SUPPORT_META_FEATURE_DEFINITION
      sMetaPath = configurations.getConfiguration("t");
#endif
   
      std::string sStackingPath = configurations.getConfiguration("e");

      process(options.args[1], options.args[2], options.args[3], nBest, bScores, sMetaPath, sStackingPath);
      return 0;
   } catch (const std::string &e) {
      std::cerr << "Error: " << e << std::endl;
      return 1;
   }
}

