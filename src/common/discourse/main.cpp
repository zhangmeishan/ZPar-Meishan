// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * main.cpp - main app of the general constituent parser.       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "discourse.h"
#include "reader.h"
#include "writer.h"
#include "stdlib.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * decode
 *
 *==============================================================*/

void process(const std::string &sInputFile, const std::string &sOutputFile, const std::string &sFeatureFile, 
		const std::string &sConInputPath, int nBest, const bool bScores, const bool bBinary) {

   std::cout << "Parsing started" << std::endl;

   int time_start = clock();

   CDisParser parser(sFeatureFile, false) ;
   std::ifstream is(sInputFile.c_str());

   std::ifstream *cis=0;
   if (!sConInputPath.empty()) cis=new std::ifstream(sConInputPath.c_str());

   std::ofstream os(sOutputFile.c_str());
   std::ofstream *os_scores=0;
   discourse::SCORE_TYPE *scores=0;
   assert(os.is_open());
   static CSentenceParsed raw_input;
   static CSentenceParsed con_input;
   CSentenceParsed *outout_sent; 


   int nCount=0;
   bool bReadSuccessful;

   if (bScores) {
      scores = new discourse::SCORE_TYPE[nBest];
      os_scores = new std::ofstream(std::string(sOutputFile+".scores").c_str());
   }

   outout_sent = new CSentenceParsed[nBest];
 
   // Read the next example
   is >> raw_input;
   while( ! raw_input.empty() ) {

      TRACE("Sentence " << nCount << "...");
      ++ nCount;

      // Find decoder outout
      if (!sConInputPath.empty()) {
    	  ASSERT((*cis) >> con_input, "No input provided for the sentence, though the input data is provided.");
    	  parser.parse( con_input , outout_sent , nBest , scores ) ;
      }
      else
          parser.parse( raw_input , outout_sent , nBest , scores ) ;
      
      // Ouptut sent
      for (int i=0; i<nBest; ++i) {
         if (bBinary)
            os << outout_sent[i] ;
         else
            os << outout_sent[i].str_unbinarized() << std::endl;

         if (bScores) *os_scores << scores[i] << std::endl;
      }

      //if(bBinary) os << raw_input;
      //else os << raw_input.str_unbinarized() << std::endl;
      TRACE("done. " << std::endl);
      
      // Read the next example
      is >> raw_input;
   }

   delete [] outout_sent ;
   os.close();

   if (bScores) {
      os_scores->close();
      delete os_scores;
      delete []scores;
   }

   std::cout << "Parsing has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
}

/*===============================================================
 *
 * main
 *
 *==============================================================*/

int main(int argc, char* argv[]) {
   try {
      COptions options(argc, argv);
      CConfigurations configurations;
      configurations.defineConfiguration("b", "", "outout binarized parse trees", "");
      configurations.defineConfiguration("n", "N", "N best list outout", "1");
      configurations.defineConfiguration("s", "", "outout scores to outout_file.scores", "");
      configurations.defineConfiguration("c", "Path", "input with multiple constituents for terminal tokens", "");
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
      bool bBinary = configurations.getConfiguration("b").empty() ? false : true;
      std::string sConInputPath = configurations.getConfiguration("c");
      process(options.args[1], options.args[2], options.args[3], 
    		  sConInputPath, nBest, bScores, bBinary);
   } 
   catch (const std::string &e) {
      std::cerr << "Error: " << e << std::endl;
      exit(1);
   }

   return 0;
}

