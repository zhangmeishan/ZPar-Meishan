// Copyright (C) SUTD 2014
/****************************************************************
 *                                                              *
 * train.cpp - the training of the general translator.          *
 *                                                              *
 * Author: Meishan Zhang                                        *
 *                                                              *
 * SUTD 12.12, 2014                                             *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "machinetranslation.h"
#include "reader.h"
#include "writer.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * auto_train - train by the translator itself, black-box training
 *
 *===============================================================*/
void auto_first_train(const std::string &sOutputFile, const std::string &sFeatureFile, const std::string &sRulePath) {

   std::cout << "Training iteration is started..." << std::endl ; std::cout.flush();

   CMachineTrans translator(sFeatureFile, true);
   //translator.setRules(bRules);

   assert(!sRulePath.empty());
   std::string actionfile = sOutputFile + ".action";
   translator.FirstTrainInitRules(sRulePath);
   translator.m_debug_info.open(actionfile.c_str());
   assert(translator.m_debug_info.is_open());

   std::ifstream is(sOutputFile.c_str());
   assert(is.is_open());

   CAlignedSentencePair ref_sent;

   int nCount=0;

   while(  is>>ref_sent ) {
	  if(ref_sent.m_src_sent.size() > machinetranslation::MAX_SENTENCE_SIZE
		|| ref_sent.m_tgt_sent.size() > machinetranslation::MAX_SENTENCE_SIZE)
	  {
		  continue;
	  }
      TRACE("Sentence " << nCount);
      ++ nCount ;
      //std::cout << ref_sent << std::endl;


      if(!translator.first_train( ref_sent))
      {
    	  std::cout << "error, please check" << std::endl;
      }

   }

   translator.finishtraining();
   translator.m_debug_info.close();

   std::cout << "Done. " << std::endl;

}



void auto_train(const std::string &sOutputFile, const std::string &sFeatureFile, const std::string &sTgtLMPath, const std::string &sOsmLMPath, const std::string &sPrLMPath, const std::string &sStackingPath) {

   std::cout << "Training iteration is started..." << std::endl ; std::cout.flush();

   CMachineTrans translator(sFeatureFile, true);


   // load target language model
   translator.init_tagetlm(sTgtLMPath);

   // load operation language model
   translator.init_osmlm(sOsmLMPath);

   // load prior probability model
   translator.init_priorlm(sPrLMPath);



   std::ifstream is(sOutputFile.c_str());
   assert(is.is_open());



   CAlignedSentencePair ref_sent;

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
	   isstack.open(sStackingPath.c_str());
	   assert(isstack.is_open());
   }

   int nCount=0;
 
   while(  is>>ref_sent ) {
	  if(!translator.first_train( ref_sent))continue;
	  if(ref_sent.m_src_sent.size() > machinetranslation::MAX_SENTENCE_SIZE
		|| ref_sent.m_tgt_sent.size() > machinetranslation::MAX_SENTENCE_SIZE)
	  {
		  continue;
	  }
	  TRACE("Sentence " << nCount);
      ++ nCount ; 
     // std::cout << ref_sent << std::endl;

      if(isstack.is_open())
      {
    	   stackfeats.clear();
    	   std::string line;
    	   getline(isstack, line);

    	   while(isstack && !line.empty())
    	   {
    		   machinetranslation::CStackFeats node;
    		   std::istringstream iss(rstrip(line));
    		   iss >> node ;
    		   stackfeats.push_back( node );
    		   getline(isstack, line);
    	   }
      }

      // example
      translator.train( ref_sent , stackfeats, nCount );
   }

   translator.finishtraining();
   if(translator.m_debug_info.is_open())translator.m_debug_info.close();

   std::cout << "Done. " << std::endl;

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
      configurations.defineConfiguration("e", "path", "external features for stacking", "");
      //configurations.defineConfiguration("r", "", "use rules", "");

      // when first training, there must be a file that contains translation table rules
      configurations.defineConfiguration("t", "path", "first round training only: initializing translation table rules", "");

      configurations.loadConfigurations(options.opts);

      std::string sStackingPath = configurations.getConfiguration("e");

      std::string sRulePath = configurations.getConfiguration("t");




      if ( (!sRulePath.empty() && options.args.size() == 3)
    	|| (sRulePath.empty() && options.args.size() == 7)
    		  )
      {

      }
      else
      {
          std::cout << "\nUsage: " << argv[0] << " training_data model" << std::endl ;
          std::cout << "\nUsage: " << argv[0] << " training_data model iteration targetLM osmLM priorLM" << std::endl ;
          std::cout << configurations.message() << std::endl;
          return 1;
      }


      if(!sRulePath.empty())
      {

          std::cout << "Initialize Training started" << std::endl;
          int time_start = clock();
          auto_first_train(options.args[1], options.args[2], sRulePath);
          std::cout << "Training has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
      }
      else
      {
          int training_rounds;
          if (!fromString(training_rounds, options.args[3])) {
             std::cerr << "Error: the number of training iterations must be an integer." << std::endl;
             return 1;
          }
          std::cout << "Training started" << std::endl;
          int time_start = clock();
          for (int i=0; i<training_rounds; ++i)
             auto_train(options.args[1], options.args[2], options.args[4], options.args[5], options.args[6], sStackingPath);
          std::cout << "Training has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
      }


      return 0;
   } catch (const std::string &e) {
      std::cerr << std::endl << "Error: " << e << std::endl;
      return 1;
   }

}

