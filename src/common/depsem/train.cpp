// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * train.cpp - the training of the general dependency parser.   *
 *                                                              *
 * Author: Meishan Zhang                                        *
 *                                                              *
 * 2015.01                                                      *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "depsem.h"
#include "reader.h"
#include "writer.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * auto_train - train by the parser itself, black-box training
 *
 *===============================================================*/

void auto_train(const std::string &sOutputFile, const std::string &sFeatureFile, const bool &bRules,
		const bool &bExtract, const std::string &sMetaPath, const std::string &sStackingPath) {

   std::cout << "Training iteration is started..." << std::endl ; std::cout.flush();

   CDepParser parser(sFeatureFile, true);
   parser.setRules(bRules);
#ifdef SUPPORT_META_FEATURE_DEFINITION
   if (!sMetaPath.empty() )
      parser.loadMeta(sMetaPath);
#endif

   std::ifstream is(sOutputFile.c_str());
   assert(is.is_open());

   std::ofstream os;
   if(bExtract)
   {
	   std::string tempfile = sOutputFile + ".verify";
	   os.open(tempfile.c_str());
	   assert(os.is_open());
   }

   CDependencyParse ref_sent; 

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
	   isstack.open(sStackingPath.c_str());
	   assert(isstack.is_open());
   }

   int nCount=0;
 
   while(is>>ref_sent ) {



      TRACE("Sentence " << nCount);
      ++ nCount ; 


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

	  if (ref_sent.size() > depsem::MAX_SENTENCE_SIZE)
	  {
		  WARNING("The sentence is longer than system limitation, skipping it.");
		  continue;
	  }


      // example
      if (bExtract) {
#ifdef SUPPORT_FEATURE_EXTRACTION
        parser.extract_features( ref_sent , stackfeats, os);
#else
         ASSERT(false, "Internal error: feature extract not allowed but option set.");
#endif
      }
      else {
         parser.train( ref_sent, stackfeats, nCount );
      }
 
   }

   parser.finishtraining();

   if(bExtract)os.close();

   std::cout << "Done. " << std::endl;

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
      configurations.defineConfiguration("r", "", "use rules", "");
      configurations.defineConfiguration("e", "path", "external features for stacking", "");
#ifdef SUPPORT_FEATURE_EXTRACTION
      configurations.defineConfiguration("f", "", "extract features only: weights will be counts", "");
#endif
#ifdef SUPPORT_META_FEATURE_DEFINITION
      configurations.defineConfiguration("t", "path", "meta feature types", "");
#endif
      if (options.args.size() != 4) {
         std::cout << "\nUsage: " << argv[0] << " training_data model num_iterations" << std::endl ;
         std::cout << configurations.message() << std::endl;
         return 1;
      } 
      configurations.loadConfigurations(options.opts);
   
      int training_rounds;
      if (!fromString(training_rounds, options.args[3])) {
         std::cerr << "Error: the number of training iterations must be an integer." << std::endl;
         return 1;
      }
   
      bool bRules = configurations.getConfiguration("r").empty() ? false : true;
      bool bExtract = false;
#ifdef SUPPORT_FEATURE_EXTRACTION
      bExtract = configurations.getConfiguration("f").empty() ? false : true;
#endif
   std::string sMetaPath;
#ifdef SUPPORT_META_FEATURE_DEFINITION
      sMetaPath = configurations.getConfiguration("t");
#endif

      std::string sStackingPath = configurations.getConfiguration("e");
      std::cout << "Training started" << std::endl;
      int time_start = clock();
      for (int i=0; i<training_rounds; ++i) 
         auto_train(options.args[1], options.args[2], bRules, bExtract, sMetaPath, sStackingPath);
      std::cout << "Training has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
   
      return 0;
   } catch (const std::string &e) {
      std::cerr << std::endl << "Error: " << e << std::endl;
      return 1;
   }

}

