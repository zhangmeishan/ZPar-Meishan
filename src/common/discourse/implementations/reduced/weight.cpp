// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * weight.cpp - the weight definition method                    *
 *                                                              *
 * Part of the constituent parser of english                    *
 *                                                              *
 * Yue Zhang                                                    *
 * 2007.8                                                       *
 *                                                              *
 ****************************************************************/

#include "weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::discourse;

/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *         
 * Affects: m_bScoreModified, clearing it. 
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::discourse::CWeight::loadScores(std::ifstream &file) {
   clock_t time_start = clock();
   std::cout<<"Loading scores..."; std::cout.flush();
//   std::ifstream file ; 
//   file.open(m_sRecordPath.c_str()) ;

   if (!file.is_open()) {
      std::cout << " empty." << std::endl; return;
   }
   m_bEmpty = false;

   static std::string s;
   getline(file, s);
   ASSERT(s=="Categories:", "Category symbols not found in model file") ;
   getline(file, s);
   std::istringstream iss_c(s);
   CDisConstituent c;
   while(iss_c >> c);
   getline(file, s);
   ASSERT(s=="", "No empty line after the category symbols") ;

   iterate_templates(file >>,;);

   getline(file, s);
   ASSERT(s=="Word frequency", "Word frequency not found from model.");
   file >> m_mapWordFrequency;

   getline(file, s);
   ASSERT(s=="Maximum frequency", "Maximum frequency not found from model.");
   getline(file, s);
   std::istringstream iss_f(s);
//   iss.str(s);
   iss_f >> m_nMaxWordFrequency;

//   file.close() ;
   std::cout << " done. (" << double(clock()-time_start)/CLOCKS_PER_SEC << "s)" << std::endl;
}

/*---------------------------------------------------------------
 *
 * saveScores - save scores back to database
 *
 * This method is called by the destructor is m_bScoreModified
 * is true.
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::discourse::CWeight::saveScores(std::ofstream &file) {
   std::cout<<"Saving scores..."; std::cout.flush();
//   std::ofstream file ;
//   file.open(m_sRecordPath.c_str()) ;

   file << "Categories:" << std::endl;
   file << CDisConstituent(CConstituent::FIRST);
   for (unsigned c=CDisConstituent::FIRST+1; c<CDisConstituent::COUNT; ++c)
      file << ' ' << CDisConstituent(c);
   file << std::endl << std::endl;

   iterate_templates(file<<,;)

   file << "Word frequency" << std::endl; 
   file << m_mapWordFrequency;
   file << "Maximum frequency" << std::endl; 
   file << m_nMaxWordFrequency << std::endl;

//   file.close();
   std::cout<<" done."<<std::endl;
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void TARGET_LANGUAGE::discourse::CWeight::computeAverageFeatureWeights(int round) {
   std::cout<<"Computing averaged (total) feature vector..."; std::cout.flush();
   
   iterate_templates(,.computeAverage(round);) ;
   
   std::cout<<"done."<<std::endl;
}

void TARGET_LANGUAGE::discourse::CWeight::addCurrent(CWeight*w, int round) {
   iterate_double_templates(, .addCurrent ID_LRB w-> , ID_COMMA round ID_RRB ;);
}

void TARGET_LANGUAGE::discourse::CWeight::subtractCurrent(CWeight*w, int round) {
   iterate_double_templates(, .subtractCurrent ID_LRB w-> , ID_COMMA round ID_RRB ;);
}

SCORE_TYPE TARGET_LANGUAGE::discourse::CWeight::dotProduct(CWeight&w) {
   iterate_double_templates(, .dotProduct ID_LRB w. , ID_RRB ;);
}

void TARGET_LANGUAGE::discourse::CWeight::outputScores() {
   std::cout<<"Dump weights..."; std::cout.flush();
   iterate_templates(std::cout<<,;)
   std::cout<<" done."<<std::endl;
   std::cout.flush();
}

