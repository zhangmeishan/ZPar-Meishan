// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * weight.cpp - the impl of tagger weights                      *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.5                         *
 *                                                              *
 ****************************************************************/

#include "weight.h"

using namespace chinese;
using namespace chinese::tagger;

#define iterate_templates(left,right) \
   left(m_mapCharUnigram)right \
   left(m_mapCharBigram)right \
   left(m_mapCharTrigram)right \
   left(m_mapSeenWords)right \
   left(m_mapLastWordByWord)right \
   left(m_mapCurrentWordLastChar)right \
   left(m_mapLastWordFirstChar)right \
   left(m_mapFirstCharLastWordByWord)right \
   left(m_mapLastWordByLastChar)right \
   left(m_mapSeparateChars)right \
   left(m_mapConsecutiveChars)right \
   left(m_mapFirstAndLastChars)right \
   left(m_mapOneCharWord)right \
   left(m_mapLengthByFirstChar)right \
   left(m_mapLengthByLastChar)right \
   left(m_mapLengthByLastWord)right \
   left(m_mapLastLengthByWord)right \
   left(m_mapLastTagByTag)right \
   left(m_mapLastTwoTagsByTag)right \
   left(m_mapCurrentTag)right \
   left(m_mapTagByLastWord)right \
   left(m_mapLastTagByWord)right \
   left(m_mapTagByFirstChar)right \
   left(m_mapTagByLastChar)right \
   left(m_mapTagByChar)right \
   left(m_mapTagOfOneCharWord)right \
   left(m_mapRepeatedCharByTag)right \
   left(m_mapTagByWordAndPrevChar)right \
   left(m_mapTagByWordAndNextChar)right \
   left(m_mapTaggedCharByFirstChar)right \
   left(m_mapTaggedCharByLastChar)right \
   left(m_mapTagByFirstCharCat)right \
   left(m_mapTagByLastCharCat)right \
   left(m_mapTaggedSeparateChars)right \
   left(m_mapTaggedConsecutiveChars)right\
   left(m_mapWordTagTag)right\
   left(m_mapTagWordTag)right\
   left(m_mapFirstCharBy2Tags)right\
   left(m_mapFirstCharBy3Tags)right\
   left(m_mapFirstCharAndChar)right\
   left(m_mapSepCharAndNextChar)right\
   left(m_mapAppCharAndNextChar)right\
   left(m_mapPartialWord)right\
   left(m_mapPartialLengthByFirstChar)right \
   left(m_mapLengthByTagAndFirstChar)right \
   left(m_mapLengthByTagAndLastChar)right \
   left(m_mapTag0Tag1Size1)right\
   left(m_mapTag1Tag2Size1)right\
   left(m_mapTag0Tag1Tag2Size1)right\
   left(m_mapSegFeat1)right \
   left(m_mapPosFeat1)right \
   left(m_mapSegPosFeat1)right \
   left(m_mapSegFeat0SegFeat1)right \
   left(m_mapPosFeat0PosFeat1)right \
   left(m_mapTwoCharSegFeat0)right \
   left(m_mapTwoCharSegFeat1)right \
   left(m_mapTwoCharPosFeat0)right \
   left(m_mapTwoCharPosFeat1)right \
   left(m_mapTwoCharSegPosFeat0)right \
   left(m_mapTwoCharSegPosFeat1)right \
   left(m_mapTwoCharSegFeat0SegFeat1)right \
   left(m_mapTwoCharPosFeat0PosFeat1)right \
   left(m_mapFirstChar0SegFeat1)right \
   left(m_mapFirstChar0PosFeat1)right \
   left(m_mapFirstChar0SegPosFeat1)right \
   left(m_mapFirstChar0SegFeat0SegFeat1)right \
   left(m_mapFirstChar0PosFeat0PosFeat1)right \
   left(m_mapSegFeat0)right \
   left(m_mapPosFeat0)right \
   left(m_mapSegPosFeat0)right \
   left(m_mapFirstChar0SegFeat0)right \
   left(m_mapFirstChar0PosFeat0)right \
   left(m_mapFirstChar0SegPosFeat0)right \
   left(m_mapAppSegFeat1)right \
   left(m_mapAppPosFeat1)right \
   left(m_mapAppSegPosFeat1)right \
   left(m_mapAppSegFeat0SegFeat1)right \
   left(m_mapAppPosFeat0PosFeat1)right \
   left(m_mapAppTwoCharSegFeat0)right \
   left(m_mapAppTwoCharSegFeat1)right \
   left(m_mapAppTwoCharPosFeat0)right \
   left(m_mapAppTwoCharPosFeat1)right \
   left(m_mapAppTwoCharSegPosFeat0)right \
   left(m_mapAppTwoCharSegPosFeat1)right \
   left(m_mapAppTwoCharSegFeat0SegFeat1)right \
   left(m_mapAppTwoCharPosFeat0PosFeat1)right \
   left(m_mapAppFirstChar0SegFeat1)right \
   left(m_mapAppFirstChar0PosFeat1)right \
   left(m_mapAppFirstChar0SegPosFeat1)right \
   left(m_mapAppFirstChar0SegFeat0SegFeat1)right \
   left(m_mapAppFirstChar0PosFeat0PosFeat1)right \
   left(m_mapAppSegFeat0)right \
   left(m_mapAppPosFeat0)right \
   left(m_mapAppSegPosFeat0)right \
   left(m_mapAppFirstChar0SegFeat0)right \
   left(m_mapAppFirstChar0PosFeat0)right \
   left(m_mapAppFirstChar0SegPosFeat0)right\
   left(m_mapSEPB)right \
   left(m_mapSEPBTagByChar)right \
   left(m_mapSEPBLastTagByTag)right \
   left(m_mapSEPBSeenWords)right \
   left(m_mapSEPBTwoChars)right \
   left(m_mapSEPA)right \
   left(m_mapSEPATagByChar)right \
   left(m_mapSEPALastTagByTag)right \
   left(m_mapSEPASeenWords)right \
   left(m_mapSEPATwoChars)right \
   left(m_mapAPPB)right \
   left(m_mapAPPBTagByChar)right \
   left(m_mapAPPBConsecutiveChars)right \
   left(m_mapAPPA)right \
   left(m_mapAPPATagByChar)right \
   left(m_mapAPPAConsecutiveChars)right \


/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *
 *--------------------------------------------------------------*/

void CWeight::loadScores() {
   std::cout << "Loading scores ..."; std::cout.flush();
   clock_t time_start = clock();
   std::string st;
   std::ifstream is(m_sFeatureDB.c_str());
   std::istringstream iss;

   if (!is.is_open()) {
      std::cout << " empty." << std::endl; return;
   }
   // load feature weights
   iterate_templates(is>>,;);

   // load tag dictionary
   getline(is, st);
   if (st=="Segmentation rules") {
      if (m_bTrain) {ASSERT(m_Knowledge, "The model indicates that there is knowledge, but the training parameters did not indicate knowledge");}
      else newKnowledge();
   }
   else {
      ASSERT(st=="Segmentation rules=0", "Segmentation rules on/off switch not found from model.");
      ASSERT(m_Knowledge==0, "The model indicates no knowledge but the system parameters indicates knowledge");
   }
//   getline(is, st);
//   if (st=="Knowledge") {
//      ASSERT(m_Knowledge==0, "Model loading knowledge but it already exists.")
//      is >> (*m_Knowledge);
//   }
//   else {
//      ASSERT(st=="Knowledge=0", "Knowledge not found from model.");
//   }
   getline(is, st);
   ASSERT(st=="Tag dictionary", "Tag dictionary not found from model.");
   is >> m_mapTagDictionary;
   getline(is, st);
   ASSERT(st=="Char tag dictionary", "Char tag dictionary not found from model.");
   is >> m_mapCharTagDictionary;
   getline(is, st);
   ASSERT(st=="Can start", "Starting character dictionary not found from model.");
   is >> m_mapCanStart;
   getline(is, st);
   ASSERT(st=="Word frequency", "Word frequency not found from model.");
   is >> m_mapWordFrequency;
   getline(is, st);
   ASSERT(st=="Maximum frequency", "Maximum frequency not found from model.");
   getline(is, st);
   iss.str(st);
   iss >> m_nMaxWordFrequency;
   getline(is, st);
   getline(is, st);
   ASSERT(st=="Maximum wordlen by tag", "Maximum word length by tag not found from model.");
   std::string ts;
   for (int i=0; i<CTag::COUNT; ++i) {
      std::istringstream iss;
      getline(is, st);
      iss.str(st);
      int j;
      iss >> ts >> j;
      m_maxLengthByTag[i] = j;
      ASSERT(CTag(ts).code()==i, "Maximum word size record loading failed.");
   }
   {
      std::istringstream iss;
      getline(is, st);
      iss.str(st);
      iss >> ts >> m_maxLengthByTag[CTag::COUNT];
      ASSERT(ts=="All", "Maximum word size record failed loading.");
   }

   std::cout << " done. (" << double(clock()-time_start)/CLOCKS_PER_SEC << "s)" << std::endl;
}

/*---------------------------------------------------------------
 *
 * saveScores - save scores back to database
 *
 *--------------------------------------------------------------*/

void CWeight::saveScores() {
   std::cout << "Saving scores ..."; std::cout.flush();

   std::ofstream os(m_sFeatureDB.c_str());
   ASSERT(os.is_open(), "Can't open "<<m_sFeatureDB<<" for saving model.");
   iterate_templates(os<<,;);

   if (m_Knowledge) os << "Segmentation rules" << std::endl;
   else os << "Segmentation rules=0" << std::endl;

//   if (m_Knowledge==0) {
//      os << "Knowledge=0" << std::endl;
//   }
//   else {
//      os << "Knowledge" << std::endl;
//      os << (*m_Knowledge);
//   }

   os << "Tag dictionary" << std::endl;
   os << m_mapTagDictionary;
   os << "Char tag dictionary" << std::endl;
   os << m_mapCharTagDictionary;
   os << "Can start" << std::endl;
   os << m_mapCanStart;
   os << "Word frequency" << std::endl;
   os << m_mapWordFrequency;
   os << "Maximum frequency" << std::endl;
   os << m_nMaxWordFrequency << std::endl;
   os << std::endl << "Maximum wordlen by tag" << std::endl;
   for (int i=0; i<CTag::COUNT; ++i)
      os << CTag(i).str() << "\t" << m_maxLengthByTag[i] << std::endl;
   os << "All\t" << m_maxLengthByTag[CTag::COUNT] << std::endl;
   std::cout << " done." << std::endl;
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void CWeight::computeAverageFeatureWeights(unsigned long round) {
   std::cout << "Comuting averaged feature vector ..."; std::cout.flush();
   iterate_templates(,.computeAverage(round););
   std::cout << " done." << std::endl;
}


