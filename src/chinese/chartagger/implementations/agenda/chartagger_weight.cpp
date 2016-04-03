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

#include "chartagger_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::chartagger;

/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *
 *--------------------------------------------------------------*/

void CWeight::loadScores() {
  std::cout << "Loading scores ...";
  std::cout.flush();
  clock_t time_start = clock();
  std::string st;
  std::ifstream is(m_sFeatureDB.c_str());
  std::istringstream iss;

  if (!is.is_open()) {
    std::cout << " empty." << std::endl;
    return;
  }
  // load feature weights
  iterate_templates(is>>, ;);

  getline(is, st);
  ASSERT(st == "Maximum word frequency", "Maximum word frequency not found from model.");
  getline(is, st);
  std::istringstream iss_f(st);
  iss_f >> m_nMaxWordFrequency;

  getline(is, st);
  ASSERT(st == "Maximum char frequency", "Maximum char frequency not found from model.");
  getline(is, st);
  iss_f.str(st);
  iss_f >> m_nMaxCharFrequency;

  getline(is, st);
  ASSERT(st == "Maximum subword frequency", "Maximum subword frequency not found from model.");
  getline(is, st);
  iss_f.str(st);
  iss_f >> m_nMaxSubWordFrequency;

  getline(is, st);
  ASSERT(st == "Word frequency", "Word frequency not found from model.");
  is >> m_mapWordFrequency;

  getline(is, st);
  ASSERT(st == "Char frequency", "Char frequency not found from model.");
  is >> m_mapCharFrequency;

  getline(is, st);
  ASSERT(st == "SubWord frequency", "Char frequency not found from model.");
  is >> m_mapSubWordFrequency;

  getline(is, st);
  ASSERT(st == "SubWord head word frequency", "SubWord tag head frequency not found from model.");
  is >> m_mapSubWordHeadWordDictionary;

  getline(is, st);
  ASSERT(st == "Word tag dictionary", "Word tag dictionary not found from model.");
  is >> m_mapWordTagDictionary;

  getline(is, st);
  ASSERT(st == "Char tag dictionary", "Char tag dictionary not found from model.");
  is >> m_mapCharTagDictionary;

  getline(is, st);
  ASSERT(st == "SubWord tag dictionary", "SubWord tag dictionary not found from model.");
  is >> m_mapSubWordTagDictionary;

  getline(is, st);
  ASSERT(st == "Can start", "Starting character dictionary not found from model.");
  is >> m_mapCanStart;

  getline(is, st);
  ASSERT(st == "Maximum wordlen by tag", "Maximum word length by tag not found from model.");
  std::string ts;
  for (int i = 0; i < CTag::COUNT; ++i) {
    std::istringstream iss;
    getline(is, st);
    iss.str(st);
    int j;
    iss >> ts >> j;
    m_maxLengthByTag[i] = j;
    ASSERT(CTag(ts).code() == i, "Maximum word size record loading failed.");
  }
  {
    std::istringstream iss;
    getline(is, st);
    iss.str(st);
    iss >> ts >> m_maxLengthByTag[CTag::COUNT];
    ASSERT(ts == "All", "Maximum word size record failed loading.");
  }

  std::cout << " done. (" << double(clock() - time_start) / CLOCKS_PER_SEC << "s)" << std::endl;
}

/*---------------------------------------------------------------
 *
 * saveScores - save scores back to database
 *
 *--------------------------------------------------------------*/

void CWeight::saveScores() {
  std::cout << "Saving scores ...";
  std::cout.flush();

  std::ofstream os(m_sFeatureDB.c_str());
  ASSERT(os.is_open(), "Can't open "<<m_sFeatureDB<<" for saving model.");
  iterate_templates(os<<, ;);

  os << "Maximum word frequency" << std::endl;
  os << m_nMaxWordFrequency << std::endl;
  os << "Maximum char frequency" << std::endl;
  os << m_nMaxCharFrequency << std::endl;
  os << "Maximum subword frequency" << std::endl;
  os << m_nMaxSubWordFrequency << std::endl;

  os << "Word frequency" << std::endl;
  os << m_mapWordFrequency;
  os << "Char frequency" << std::endl;
  os << m_mapCharFrequency;
  os << "SubWord frequency" << std::endl;
  os << m_mapSubWordFrequency;

  os << "SubWord head word frequency" << std::endl;
  os << m_mapSubWordHeadWordDictionary;

  os << "Word tag dictionary" << std::endl;
  os << m_mapWordTagDictionary;
  os << "Char tag dictionary" << std::endl;
  os << m_mapCharTagDictionary;
  os << "SubWord tag dictionary" << std::endl;
  os << m_mapSubWordTagDictionary;

  os << "Can start" << std::endl;
  os << m_mapCanStart;

  os << "Maximum wordlen by tag" << std::endl;
  for (int i = 0; i < CTag::COUNT; ++i)
    os << CTag(i).str() << "\t" << m_maxLengthByTag[i] << std::endl;
  os << "All\t" << m_maxLengthByTag[CTag::COUNT] << std::endl;
  std::cout << " done." << std::endl;
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void CWeight::computeAverageFeatureWeights(int round) {
  std::cout << "Computing averaged (total) feature vector...";
  std::cout.flush();
  iterate_templates(, .computeAverage(round););

  std::cout << "done." << std::endl;
}

void CWeight::outputScores() {
  std::cout << "Dump weights...";
  std::cout.flush();
  iterate_templates(std::cout<<, ;)
  std::cout << " done." << std::endl;
  std::cout.flush();
}

void CWeight::addCurrent(CWeight*w, int round) {
  iterate_double_templates(, .addCurrent ID_LRB w->, ID_COMMA round ID_RRB ;);
}

void CWeight::subtractCurrent(CWeight*w, int round) {
  iterate_double_templates(, .subtractCurrent ID_LRB w->, ID_COMMA round ID_RRB ;);
}

