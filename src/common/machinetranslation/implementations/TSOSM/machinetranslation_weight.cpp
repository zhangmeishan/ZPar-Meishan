// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * weight.cpp - the weight definition method                    *
 *                                                              *
 * Part of the dependency translator of english                     *
 *                                                              *
 * Yue Zhang                                                    *
 * 2007.8                                                       *
 *                                                              *
 ****************************************************************/

#include "machinetranslation_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::machinetranslation;

/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *         
 * Affects: m_bScoreModified, clearing it. 
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::machinetranslation::CWeight::loadScores() {
   clock_t time_start = clock();
   std::cout<<"Loading scores..."; std::cout.flush();
   std::ifstream file ; 
   std::string s, os;
   std::vector<CWord> srcPhrase;
   std::vector<CWord> tgtPhrase;
   float translate_rule_weight1, translate_rule_weight2, translate_rule_weight3;
   int one_srcphrase_translation_rule_num;
   int i, j;
   file.open(m_sRecordPath.c_str()) ;

   if (!file.is_open()) {
      std::cout << " empty." << std::endl; return;
   }


   iterate_templates(file >>,;);

// translation tables
   getline(file, s);
   ASSERT(s=="translation table rules", "translation table rules not found from model.");
   file >> m_nTranslationRuleNum;
   i = 0;
   while(i < m_nTranslationRuleNum)
   {
	   file >> srcPhrase;
	   file >> one_srcphrase_translation_rule_num;
	   os = tostring(srcPhrase);
	   m_mapTranslateStart.insert(os, i);
	   m_mapTranslateEnd.insert(os, i+one_srcphrase_translation_rule_num-1);
	   j = 0;
	   assert(i + one_srcphrase_translation_rule_num <=  m_nTranslationRuleNum);
	   while(j < one_srcphrase_translation_rule_num)
	   {
		   file >> tgtPhrase;
		   file >> translate_rule_weight1 >> translate_rule_weight2 >> translate_rule_weight3;
		   m_mapTranslateSources.push_back(os);
		   m_mapTranslateRules.push_back(tgtPhrase);
		   m_mapTranslateRuleScore1s.push_back(translate_rule_weight1);
		   m_mapTranslateRuleScore2s.push_back(translate_rule_weight2);
		   m_mapTranslateRuleScore3s.push_back(translate_rule_weight3);
		   if(srcPhrase.size() == 0 && tgtPhrase.size() == 0)
		   {
			   std::cout << "error transition rule!" << std::endl;
		   }
		   if(srcPhrase.size() == 0)
		   {
			   m_mapTranslateRuleTypes.push_back(1);
		   }
		   else if(tgtPhrase.size() == 0)
		   {
			   m_mapTranslateRuleTypes.push_back(-1);
		   }
		   else
		   {
			   assert(srcPhrase.size() > 0 && tgtPhrase.size() > 0);
			   m_mapTranslateRuleTypes.push_back(0);
		   }
		   j++;

	   }
	   i += one_srcphrase_translation_rule_num;
   }


   file.close() ;
   std::cout << " done. (" << double(clock()-time_start)/CLOCKS_PER_SEC << "s)" << std::endl;
}

/*---------------------------------------------------------------
 *
 * saveScores - save scores back to database
 *
 * This method is called by the destructor is m_bScoreModified
 * is true.
   std::cout<<"done."<<std::endl;
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::machinetranslation::CWeight::saveScores() {
   std::cout<<"Saving scores..."; std::cout.flush();
   std::ofstream file ;
   file.open(m_sRecordPath.c_str()) ;

   iterate_templates(file<<,;)
#ifdef DEBUG
   iterate_templates(,.trace(););
#endif

// translation tables
   file << "translation table rules" << std::endl;
   file << m_nTranslationRuleNum << std::endl;
   int i = 0;
   while(i < m_nTranslationRuleNum)
   {
	   std::string sourcePhrase = m_mapTranslateSources[i];
	   int start_pos = m_mapTranslateStart[sourcePhrase];
	   int end_pos = m_mapTranslateEnd[sourcePhrase];
	   file << sourcePhrase << std::endl;
	   file << end_pos - start_pos + 1 << std::endl;
	   for(int j = start_pos; j <= end_pos; j++)
	   {
		   file << m_mapTranslateRules[j] << std::endl;
		   file << m_mapTranslateRuleScore1s[j] <<"\t" <<  m_mapTranslateRuleScore2s[j] <<"\t" <<  m_mapTranslateRuleScore3s[j]<< std::endl;
	   }
	   i = end_pos + 1;
   }


   file.close();
   std::cout<<" done."<<std::endl;
}


void TARGET_LANGUAGE::machinetranslation::CWeight::outputScores() {
   std::cout<<"Dump weights..."; std::cout.flush();
   iterate_templates(std::cout<<,;)
   std::cout<<" done."<<std::endl;
   std::cout.flush();
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void TARGET_LANGUAGE::machinetranslation::CWeight::computeAverageFeatureWeights(int round) {
   std::cout<<"Computing averaged (total) feature vector..."; std::cout.flush();
   iterate_templates(,.computeAverage(round);) ;

   std::cout<<"done."<<std::endl;
}


void TARGET_LANGUAGE::machinetranslation::CWeight::addCurrent(CWeight*w, int round) {
   iterate_double_templates(, .addCurrent ID_LRB w-> , ID_COMMA round ID_RRB ;);
}

void TARGET_LANGUAGE::machinetranslation::CWeight::subtractCurrent(CWeight*w, int round) {
   iterate_double_templates(, .subtractCurrent ID_LRB w-> , ID_COMMA round ID_RRB ;);
}




