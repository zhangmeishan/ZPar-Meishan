// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * weight.cpp - the weight definition method                    *
 *                                                              *
 * Part of the dependency parser of english                     *
 *                                                              *
 * Yue Zhang                                                    *
 * 2007.8                                                       *
 *                                                              *
 ****************************************************************/

#include "depparser_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::depparser;

/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *
 * Affects: m_bScoreModified, clearing it. 
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::depparser::CWeight::loadScores() {
  clock_t time_start = clock();
  std::cout<<"Loading scores...";
  std::cout.flush();
  std::ifstream file ;
  std::string s;
  file.open(m_sRecordPath.c_str()) ;

  if (!file.is_open()) {
    // the model file is not exist. manually init the models
    std::cout << " empty." << std::endl;
    iterate_templates(, .init());
    return;
  }

#ifdef LABELED
  getline(file, s);
  ASSERT(s == "Dependency labels:", 
      "Dependency labels not found in model file");
  getline(file, s);
  std::istringstream iss(s);
  CDependencyLabel label;
  while(iss >> label);
  getline(file, s);
  ASSERT(s == "", 
      "No empty line after the dependency labels");
#endif
  iterate_templates(file >>,;);

  getline(file, s);
  if (s=="Rules=1") {
    setRules(true);
  } else {
    ASSERT(s=="Rules=0", "Rules flag not found from the model file");
    setRules(false);
  }

  file.close();
  std::cout << " done. ("
    << double(clock()-time_start)/CLOCKS_PER_SEC << "s)"
    << std::endl;
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

void TARGET_LANGUAGE::depparser::CWeight::saveScores() {
  std::cout<<"Saving scores...";
  std::cout.flush();

  std::ofstream ofs;
  ofs.open(m_sRecordPath.c_str());

#ifdef LABELED
  ofs << "Dependency labels:" << std::endl;
  for (unsigned label = CDependencyLabel::FIRST;
      label < CDependencyLabel::COUNT;
      ++label) {
    ofs << CDependencyLabel(label) << ' ';
  }
  ofs << std::endl << std::endl;
#endif
  iterate_templates(ofs <<, ;);

#ifdef DEBUG
  iterate_templates( ,.trace());
#endif

  if (m_bRules) {
    ofs << "Rules=1" << std::endl;
  } else {
    ofs << "Rules=0" << std::endl;
  }

  ofs.close();
  std::cout<<" done."<<std::endl;
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void TARGET_LANGUAGE::depparser::CWeight::computeAverageFeatureWeights(int round) {
  std::cout << "Computing averaged (total) feature vector...";
  std::cout.flush();
  iterate_templates(,.computeAverage(round););
  std::cout << "done." <<std::endl;
}

