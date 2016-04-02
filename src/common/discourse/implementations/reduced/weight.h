// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the constituent parser weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _DISCOURSE_WEIGHTS_H
#define _DISCOURSE_WEIGHTS_H

#include "weight_base.h"

const static unsigned DEFAULT_TABLE_SIZE = 1<<17;

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,

#define iterate_templates(left, right) \
	left(m_mapS0w)right\
	left(m_mapS0t)right\
	left(m_mapS0c)right\
	left(m_mapS0sc)right\
	left(m_mapS0HeadEduSize)right\
	left(m_mapS0EDUNUM)right\
	left(m_mapS0SentBegin)right\
	left(m_mapS0SentEnd)right\
	left(m_mapS0ParaBegin)right\
	left(m_mapS0ParaEnd)right\
\
	left(m_mapS0bw)right\
	left(m_mapS0bt)right\
	left(m_mapS0ew)right\
	left(m_mapS0et)right\
	left(m_mapS0EduWords)right\
	left(m_mapS1w)right\
	left(m_mapS1t)right\
	left(m_mapS1c)right\
	left(m_mapS1sc)right\
	left(m_mapS1HeadEduSize)right\
\
	left(m_mapS1EDUNUM)right\
	left(m_mapS1SentBegin)right\
	left(m_mapS1SentEnd)right\
	left(m_mapS1ParaBegin)right\
	left(m_mapS1ParaEnd)right\
	left(m_mapS1bw)right\
	left(m_mapS1bt)right\
	left(m_mapS1ew)right\
	left(m_mapS1et)right\
	left(m_mapS1EduWords)right\
\
	left(m_mapS2w)right\
	left(m_mapS2t)right\
	left(m_mapS2c)right\
	left(m_mapS2sc)right\
	left(m_mapS2HeadEduSize)right\
	left(m_mapS2EDUNUM)right\
	left(m_mapS2SentBegin)right\
	left(m_mapS2SentEnd)right\
	left(m_mapS2ParaBegin)right\
	left(m_mapS2ParaEnd)right\
\
	left(m_mapS2bw)right\
	left(m_mapS2bt)right\
	left(m_mapS2ew)right\
	left(m_mapS2et)right\
	left(m_mapN0w)right\
	left(m_mapN0t)right\
	left(m_mapN0sc)right\
	left(m_mapN0HeadEduSize)right\
	left(m_mapN0EDUNUM)right\
	left(m_mapN0SentBegin)right\
\
	left(m_mapN0SentEnd)right\
	left(m_mapN0ParaBegin)right\
	left(m_mapN0ParaEnd)right\
	left(m_mapN0bw)right\
	left(m_mapN0bt)right\
	left(m_mapN0ew)right\
	left(m_mapN0et)right\
	left(m_mapN1w)right\
	left(m_mapN1t)right\
	left(m_mapN1sc)right\
\
	left(m_mapN1HeadEduSize)right\
	left(m_mapN1bw)right\
	left(m_mapN1bt)right\
	left(m_mapN1ew)right\
	left(m_mapN1et)right\
	left(m_mapN2w)right\
	left(m_mapN2t)right\
	left(m_mapN2sc)right\
	left(m_mapN2HeadEduSize)right\
	left(m_mapN2bw)right\
\
	left(m_mapN2bt)right\
	left(m_mapN2ew)right\
	left(m_mapN2et)right\
	left(m_mapS0wS1w)right\
	left(m_mapS0cS1c)right\
	left(m_mapS0tS1t)right\
	left(m_mapS0scS1sc)right\
	left(m_mapS0S1HeadEDUSameSentence)right\
	left(m_mapS0S1Dist)right\
	left(m_mapS0bwS1bw)right\
\
	left(m_mapS0btS1bt)right\
	left(m_mapS0ewS1ew)right\
	left(m_mapS0etS1et)right\
	left(m_mapS0wN0w)right\
	left(m_mapS0cN0t)right\
	left(m_mapS0tN0t)right\
	left(m_mapS0scN0sc)right\
	left(m_mapS0N0HeadEDUSameSentence)right\
	left(m_mapS0N0Dist)right\
	left(m_mapS0bwN0bw)right\
\
	left(m_mapS0btN0bt)right\
	left(m_mapS0ewN0ew)right\
	left(m_mapS0etN0et)right\
	left(m_mapS1wN0w)right\
	left(m_mapS1cN0t)right\
	left(m_mapS1tN0t)right\
	left(m_mapS1scN0sc)right\
	left(m_mapS1N0HeadEDUSameSentence)right\
	left(m_mapS1N0Dist)right\
	left(m_mapS1bwN0bw)right\
\
	left(m_mapS1btN0bt)right\
	left(m_mapS1ewN0ew)right\
	left(m_mapS1etN0et)right\
	left(m_mapS1wS2w)right\
	left(m_mapS1cS2c)right\
	left(m_mapS1tS2t)right\
	left(m_mapS1scS2sc)right\
	left(m_mapS1S2HeadEDUSameSentence)right\
	left(m_mapS1S2Dist)right\
	left(m_mapS1bwS2bw)right\
\
	left(m_mapS1btS2bt)right\
	left(m_mapS1ewS2ew)right\
	left(m_mapS1etS2et)right\
	left(m_mapN0wN1w)right\
	left(m_mapN0tN1t)right\
	left(m_mapN0scN1sc)right\
	left(m_mapN0bwN1bw)right\
	left(m_mapN0btN1bt)right\
	left(m_mapN0ewN1ew)right\
	left(m_mapN0etN1et)right\
\
	left(m_mapS0cS1cN0t)right\
	left(m_mapS0tS1tN0t)right\
	left(m_mapS0scS1scN0sc)right\
	left(m_mapS0btS1btN0bt)right\
	left(m_mapS0etS1etN0et)right\
	left(m_mapS0cN0tN1t)right\
	left(m_mapS0tN0tN1t)right\
	left(m_mapS0jN0tN1t)right\
	left(m_mapS0scN0scN1sc)right\
	left(m_mapS0btN0btN1bt)right\
\
	left(m_mapS0etN0etN1et)right\
	left(m_mapS0cS1cS2c)right\
	left(m_mapS0tS1tS2t)right\
	left(m_mapS0scS1scS2sc)right\
	left(m_mapS0btS1btS2bt)right\
	left(m_mapS0etS1etS2et)right\
	left(m_mapA1)right\
	left(m_mapA1A2)right


#define iterate_double_templates(left, middle, right)\
	left m_mapS0w middle m_mapS0w right\
	left m_mapS0t middle m_mapS0t right\
	left m_mapS0c middle m_mapS0c right\
	left m_mapS0sc middle m_mapS0sc right\
	left m_mapS0HeadEduSize middle m_mapS0HeadEduSize right\
	left m_mapS0EDUNUM middle m_mapS0EDUNUM right\
	left m_mapS0SentBegin middle m_mapS0SentBegin right\
	left m_mapS0SentEnd middle m_mapS0SentEnd right\
	left m_mapS0ParaBegin middle m_mapS0ParaBegin right\
	left m_mapS0ParaEnd middle m_mapS0ParaEnd right\
\
	left m_mapS0bw middle m_mapS0bw right\
	left m_mapS0bt middle m_mapS0bt right\
	left m_mapS0ew middle m_mapS0ew right\
	left m_mapS0et middle m_mapS0et right\
	left m_mapS0EduWords middle m_mapS0EduWords right\
	left m_mapS1w middle m_mapS1w right\
	left m_mapS1t middle m_mapS1t right\
	left m_mapS1c middle m_mapS1c right\
	left m_mapS1sc middle m_mapS1sc right\
	left m_mapS1HeadEduSize middle m_mapS1HeadEduSize right\
\
	left m_mapS1EDUNUM middle m_mapS1EDUNUM right\
	left m_mapS1SentBegin middle m_mapS1SentBegin right\
	left m_mapS1SentEnd middle m_mapS1SentEnd right\
	left m_mapS1ParaBegin middle m_mapS1ParaBegin right\
	left m_mapS1ParaEnd middle m_mapS1ParaEnd right\
	left m_mapS1bw middle m_mapS1bw right\
	left m_mapS1bt middle m_mapS1bt right\
	left m_mapS1ew middle m_mapS1ew right\
	left m_mapS1et middle m_mapS1et right\
	left m_mapS1EduWords middle m_mapS1EduWords right\
\
	left m_mapS2w middle m_mapS2w right\
	left m_mapS2t middle m_mapS2t right\
	left m_mapS2c middle m_mapS2c right\
	left m_mapS2sc middle m_mapS2sc right\
	left m_mapS2HeadEduSize middle m_mapS2HeadEduSize right\
	left m_mapS2EDUNUM middle m_mapS2EDUNUM right\
	left m_mapS2SentBegin middle m_mapS2SentBegin right\
	left m_mapS2SentEnd middle m_mapS2SentEnd right\
	left m_mapS2ParaBegin middle m_mapS2ParaBegin right\
	left m_mapS2ParaEnd middle m_mapS2ParaEnd right\
\
	left m_mapS2bw middle m_mapS2bw right\
	left m_mapS2bt middle m_mapS2bt right\
	left m_mapS2ew middle m_mapS2ew right\
	left m_mapS2et middle m_mapS2et right\
	left m_mapN0w middle m_mapN0w right\
	left m_mapN0t middle m_mapN0t right\
	left m_mapN0sc middle m_mapN0sc right\
	left m_mapN0HeadEduSize middle m_mapN0HeadEduSize right\
	left m_mapN0EDUNUM middle m_mapN0EDUNUM right\
	left m_mapN0SentBegin middle m_mapN0SentBegin right\
\
	left m_mapN0SentEnd middle m_mapN0SentEnd right\
	left m_mapN0ParaBegin middle m_mapN0ParaBegin right\
	left m_mapN0ParaEnd middle m_mapN0ParaEnd right\
	left m_mapN0bw middle m_mapN0bw right\
	left m_mapN0bt middle m_mapN0bt right\
	left m_mapN0ew middle m_mapN0ew right\
	left m_mapN0et middle m_mapN0et right\
	left m_mapN1w middle m_mapN1w right\
	left m_mapN1t middle m_mapN1t right\
	left m_mapN1sc middle m_mapN1sc right\
\
	left m_mapN1HeadEduSize middle m_mapN1HeadEduSize right\
	left m_mapN1bw middle m_mapN1bw right\
	left m_mapN1bt middle m_mapN1bt right\
	left m_mapN1ew middle m_mapN1ew right\
	left m_mapN1et middle m_mapN1et right\
	left m_mapN2w middle m_mapN2w right\
	left m_mapN2t middle m_mapN2t right\
	left m_mapN2sc middle m_mapN2sc right\
	left m_mapN2HeadEduSize middle m_mapN2HeadEduSize right\
	left m_mapN2bw middle m_mapN2bw right\
\
	left m_mapN2bt middle m_mapN2bt right\
	left m_mapN2ew middle m_mapN2ew right\
	left m_mapN2et middle m_mapN2et right\
	left m_mapS0wS1w middle m_mapS0wS1w right\
	left m_mapS0cS1c middle m_mapS0cS1c right\
	left m_mapS0tS1t middle m_mapS0tS1t right\
	left m_mapS0scS1sc middle m_mapS0scS1sc right\
	left m_mapS0S1HeadEDUSameSentence middle m_mapS0S1HeadEDUSameSentence right\
	left m_mapS0S1Dist middle m_mapS0S1Dist right\
	left m_mapS0bwS1bw middle m_mapS0bwS1bw right\
\
	left m_mapS0btS1bt middle m_mapS0btS1bt right\
	left m_mapS0ewS1ew middle m_mapS0ewS1ew right\
	left m_mapS0etS1et middle m_mapS0etS1et right\
	left m_mapS0wN0w middle m_mapS0wN0w right\
	left m_mapS0cN0t middle m_mapS0cN0t right\
	left m_mapS0tN0t middle m_mapS0tN0t right\
	left m_mapS0scN0sc middle m_mapS0scN0sc right\
	left m_mapS0N0HeadEDUSameSentence middle m_mapS0N0HeadEDUSameSentence right\
	left m_mapS0N0Dist middle m_mapS0N0Dist right\
	left m_mapS0bwN0bw middle m_mapS0bwN0bw right\
\
	left m_mapS0btN0bt middle m_mapS0btN0bt right\
	left m_mapS0ewN0ew middle m_mapS0ewN0ew right\
	left m_mapS0etN0et middle m_mapS0etN0et right\
	left m_mapS1wN0w middle m_mapS1wN0w right\
	left m_mapS1cN0t middle m_mapS1cN0t right\
	left m_mapS1tN0t middle m_mapS1tN0t right\
	left m_mapS1scN0sc middle m_mapS1scN0sc right\
	left m_mapS1N0HeadEDUSameSentence middle m_mapS1N0HeadEDUSameSentence right\
	left m_mapS1N0Dist middle m_mapS1N0Dist right\
	left m_mapS1bwN0bw middle m_mapS1bwN0bw right\
\
	left m_mapS1btN0bt middle m_mapS1btN0bt right\
	left m_mapS1ewN0ew middle m_mapS1ewN0ew right\
	left m_mapS1etN0et middle m_mapS1etN0et right\
	left m_mapS1wS2w middle m_mapS1wS2w right\
	left m_mapS1cS2c middle m_mapS1cS2c right\
	left m_mapS1tS2t middle m_mapS1tS2t right\
	left m_mapS1scS2sc middle m_mapS1scS2sc right\
	left m_mapS1S2HeadEDUSameSentence middle m_mapS1S2HeadEDUSameSentence right\
	left m_mapS1S2Dist middle m_mapS1S2Dist right\
	left m_mapS1bwS2bw middle m_mapS1bwS2bw right\
\
	left m_mapS1btS2bt middle m_mapS1btS2bt right\
	left m_mapS1ewS2ew middle m_mapS1ewS2ew right\
	left m_mapS1etS2et middle m_mapS1etS2et right\
	left m_mapN0wN1w middle m_mapN0wN1w right\
	left m_mapN0tN1t middle m_mapN0tN1t right\
	left m_mapN0scN1sc middle m_mapN0scN1sc right\
	left m_mapN0bwN1bw middle m_mapN0bwN1bw right\
	left m_mapN0btN1bt middle m_mapN0btN1bt right\
	left m_mapN0ewN1ew middle m_mapN0ewN1ew right\
	left m_mapN0etN1et middle m_mapN0etN1et right\
\
	left m_mapS0cS1cN0t middle m_mapS0cS1cN0t right\
	left m_mapS0tS1tN0t middle m_mapS0tS1tN0t right\
	left m_mapS0scS1scN0sc middle m_mapS0scS1scN0sc right\
	left m_mapS0btS1btN0bt middle m_mapS0btS1btN0bt right\
	left m_mapS0etS1etN0et middle m_mapS0etS1etN0et right\
	left m_mapS0cN0tN1t middle m_mapS0cN0tN1t right\
	left m_mapS0tN0tN1t middle m_mapS0tN0tN1t right\
	left m_mapS0jN0tN1t middle m_mapS0jN0tN1t right\
	left m_mapS0scN0scN1sc middle m_mapS0scN0scN1sc right\
	left m_mapS0btN0btN1bt middle m_mapS0btN0btN1bt right\
\
	left m_mapS0etN0etN1et middle m_mapS0etN0etN1et right\
	left m_mapS0cS1cS2c middle m_mapS0cS1cS2c right\
	left m_mapS0tS1tS2t middle m_mapS0tS1tS2t right\
	left m_mapS0scS1scS2sc middle m_mapS0scS1scS2sc right\
	left m_mapS0btS1btS2bt middle m_mapS0btS1btS2bt right\
	left m_mapS0etS1etS2et middle m_mapS0etS1etS2et right\
	left m_mapA1 middle m_mapA1 right\
	left m_mapA1A2 middle m_mapA1A2 right

namespace TARGET_LANGUAGE {

namespace discourse {

//#include "discourse_macros.h"

//
// TYPE DEFINITIONS
//
typedef CScoreMap< std::pair<CWord, CAction>, SCORE_TYPE > CWordMap;
typedef CScoreMap< std::pair<CTag, CAction>, SCORE_TYPE > CTagMap;
typedef CScoreMap< std::pair<CTaggedWord<CTag, TAG_SEPARATOR>, CAction>, SCORE_TYPE > CTaggedWordMap;
typedef CScoreMap< std::pair<std::pair<CWord, unsigned long>, CAction>,  SCORE_TYPE > CWordIntMap;
typedef CScoreMap< std::pair<unsigned long, CAction>, SCORE_TYPE > CIntMap;
typedef CScoreMap< std::pair<std::pair<unsigned long, unsigned long>, CAction>, SCORE_TYPE > CTwoIntMap;
typedef CScoreMap< std::pair<CTwoWords, CAction>, SCORE_TYPE > CTwoWordsMap;
typedef CScoreMap< std::pair<std::pair<CTwoWords, CActionType>, CAction>, SCORE_TYPE > CTwoWordsActionTypeMap;
typedef CScoreMap< std::pair<CTuple3<CTwoWords, CTag, CActionType>, CAction>, SCORE_TYPE > CTwoWordsTagActionTypeMap;
typedef CScoreMap< std::pair<CTuple2<CTwoWords, CDISCFGSet>, CAction>, SCORE_TYPE > CTwoWordsCFGSetMap;
//typedef CScoreMap< std::pair<CTwoTaggedWords, CAction>, SCORE_TYPE > CTwoWordsCFGSetMap;
typedef CScoreMap< std::pair<std::pair<CTwoTaggedWords, CActionType>, CAction>, SCORE_TYPE > CTwoTaggedWordsActionTypeMap;
typedef CScoreMap< std::pair<CDISCFGSet, CAction>, SCORE_TYPE > CCFGSetMap;
typedef CScoreMap< std::pair<std::pair<CDISCFGSet, unsigned long>, CAction>, SCORE_TYPE > CCFGSetIntMap;
typedef CScoreMap< std::pair<CTuple2<CWord, CDISCFGSet>, CAction>, SCORE_TYPE > CWordCFGSetMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CDISCFGSet, CActionType>, CAction>, SCORE_TYPE > CWordCFGSetActionTypeMap;
typedef CScoreMap< std::pair<std::pair<CWord, CDISCFGSet>, CAction>, SCORE_TYPE > CWordCFGRuleMap;
typedef CScoreMap< std::pair<std::pair<CTwoWords, CDISCFGSet>, CAction>, SCORE_TYPE > CTwoWordsCFGRuleMap;
typedef CScoreMap< std::pair<std::pair<CDISCFGSet, CActionType>, CAction>, SCORE_TYPE > CCFGSetActionTypeMap;
typedef CScoreMap< std::pair<CTuple2<CWord, CConstituent>, CAction>, SCORE_TYPE > CWordConstituentMap;
typedef CScoreMap< std::pair<CTuple2<CTag, CConstituent>, CAction>, SCORE_TYPE > CTagConstituentMap;
typedef CScoreMap< std::pair<CTuple3<CTag, CTag, unsigned long>, CAction>, SCORE_TYPE > CWordTagIntMap;
typedef CScoreMap< std::pair<CDisConstituent, CAction>, SCORE_TYPE > CDisConstituentMap;
typedef CScoreMap< std::pair<std::pair<CConstituent, unsigned long>, CAction>, SCORE_TYPE > CConstituentMap;
typedef CScoreMap< std::pair<CAction, CAction>, SCORE_TYPE > CActionMap;
typedef CScoreMap< std::pair<CTuple2<CAction, CAction>, CAction>, SCORE_TYPE > CAction2Map;

typedef CHashMap<CWord, unsigned long> CWordToIntMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:

   // S0
   CWordMap m_mapS0w;
   CTagMap m_mapS0t;
   CDisConstituentMap m_mapS0c;
   CConstituentMap m_mapS0sc;

   CIntMap m_mapS0HeadEduSize;
   CIntMap m_mapS0EDUNUM;
   CIntMap m_mapS0SentBegin;
   CIntMap m_mapS0SentEnd;
   CIntMap m_mapS0ParaBegin;
   CIntMap m_mapS0ParaEnd;

   CWordMap m_mapS0bw;
   CTagMap m_mapS0bt;
   CWordMap m_mapS0ew;
   CTagMap m_mapS0et;

   CWordMap m_mapS0EduWords;

   // S1
   CWordMap m_mapS1w;
   CTagMap m_mapS1t;
   CDisConstituentMap m_mapS1c;
   CConstituentMap m_mapS1sc;

   CIntMap m_mapS1HeadEduSize;
   CIntMap m_mapS1EDUNUM;
   CIntMap m_mapS1SentBegin;
   CIntMap m_mapS1SentEnd;
   CIntMap m_mapS1ParaBegin;
   CIntMap m_mapS1ParaEnd;

   CWordMap m_mapS1bw;
   CTagMap m_mapS1bt;
   CWordMap m_mapS1ew;
   CTagMap m_mapS1et;

   CWordMap m_mapS1EduWords;

   // S2
   CWordMap m_mapS2w;
   CTagMap m_mapS2t;
   CDisConstituentMap m_mapS2c;
   CConstituentMap m_mapS2sc;

   CIntMap m_mapS2HeadEduSize;
   CIntMap m_mapS2EDUNUM;
   CIntMap m_mapS2SentBegin;
   CIntMap m_mapS2SentEnd;
   CIntMap m_mapS2ParaBegin;
   CIntMap m_mapS2ParaEnd;

   CWordMap m_mapS2bw;
   CTagMap m_mapS2bt;
   CWordMap m_mapS2ew;
   CTagMap m_mapS2et;

   // N0
   CWordMap m_mapN0w;
   CTagMap m_mapN0t;
   CConstituentMap m_mapN0sc;

   CIntMap m_mapN0HeadEduSize;
   CIntMap m_mapN0EDUNUM;
   CIntMap m_mapN0SentBegin;
   CIntMap m_mapN0SentEnd;
   CIntMap m_mapN0ParaBegin;
   CIntMap m_mapN0ParaEnd;

   CWordMap m_mapN0bw;
   CTagMap m_mapN0bt;
   CWordMap m_mapN0ew;
   CTagMap m_mapN0et;

   // N1
   CWordMap m_mapN1w;
   CTagMap m_mapN1t;
   CConstituentMap m_mapN1sc;
   CIntMap m_mapN1HeadEduSize;

   CWordMap m_mapN1bw;
   CTagMap m_mapN1bt;
   CWordMap m_mapN1ew;
   CTagMap m_mapN1et;

   // N2
   CWordMap m_mapN2w;
   CTagMap m_mapN2t;
   CConstituentMap m_mapN2sc;
   CIntMap m_mapN2HeadEduSize;

   CWordMap m_mapN2bw;
   CTagMap m_mapN2bt;
   CWordMap m_mapN2ew;
   CTagMap m_mapN2et;

   // S0 S1
   CTwoWordsMap m_mapS0wS1w;
   CCFGSetMap m_mapS0cS1c;
   CCFGSetMap m_mapS0tS1t;
   CCFGSetIntMap m_mapS0scS1sc;

   CIntMap m_mapS0S1HeadEDUSameSentence;
   CIntMap m_mapS0S1Dist;

   CTwoWordsMap m_mapS0bwS1bw;
   CCFGSetMap m_mapS0btS1bt;
   CTwoWordsMap m_mapS0ewS1ew;
   CCFGSetMap m_mapS0etS1et;

   // S0 N0
   CTwoWordsMap m_mapS0wN0w;
   CCFGSetMap m_mapS0cN0t;
   CCFGSetMap m_mapS0tN0t;
   CCFGSetIntMap m_mapS0scN0sc;

   CIntMap m_mapS0N0HeadEDUSameSentence;
   CIntMap m_mapS0N0Dist;

   CTwoWordsMap m_mapS0bwN0bw;
   CCFGSetMap m_mapS0btN0bt;
   CTwoWordsMap m_mapS0ewN0ew;
   CCFGSetMap m_mapS0etN0et;

   // S1 N0
   CTwoWordsMap m_mapS1wN0w;
   CCFGSetMap m_mapS1cN0t;
   CCFGSetMap m_mapS1tN0t;
   CCFGSetIntMap m_mapS1scN0sc;

   CIntMap m_mapS1N0HeadEDUSameSentence;
   CIntMap m_mapS1N0Dist;

   CTwoWordsMap m_mapS1bwN0bw;
   CCFGSetMap m_mapS1btN0bt;
   CTwoWordsMap m_mapS1ewN0ew;
   CCFGSetMap m_mapS1etN0et;

   // S1 S2
   CTwoWordsMap m_mapS1wS2w;
   CCFGSetMap m_mapS1cS2c;
   CCFGSetMap m_mapS1tS2t;
   CCFGSetIntMap m_mapS1scS2sc;

   CIntMap m_mapS1S2HeadEDUSameSentence;
   CIntMap m_mapS1S2Dist;

   CTwoWordsMap m_mapS1bwS2bw;
   CCFGSetMap m_mapS1btS2bt;
   CTwoWordsMap m_mapS1ewS2ew;
   CCFGSetMap m_mapS1etS2et;

   // N0 N1
   CTwoWordsMap m_mapN0wN1w;
   CCFGSetMap m_mapN0tN1t;
   CCFGSetIntMap m_mapN0scN1sc;

   CTwoWordsMap m_mapN0bwN1bw;
   CCFGSetMap m_mapN0btN1bt;
   CTwoWordsMap m_mapN0ewN1ew;
   CCFGSetMap m_mapN0etN1et;

   // S0 S1N0
   CCFGSetMap m_mapS0cS1cN0t;
   CCFGSetMap m_mapS0tS1tN0t;

   CCFGSetIntMap m_mapS0scS1scN0sc;

   CCFGSetMap m_mapS0btS1btN0bt;
   CCFGSetMap m_mapS0etS1etN0et;

   // S0 N0N1
   CCFGSetMap m_mapS0cN0tN1t;
   CCFGSetMap m_mapS0tN0tN1t;
   CCFGSetMap m_mapS0jN0tN1t;

   CCFGSetIntMap m_mapS0scN0scN1sc;

   CCFGSetMap m_mapS0btN0btN1bt;
   CCFGSetMap m_mapS0etN0etN1et;

   // S0 S1S2
   CCFGSetMap m_mapS0cS1cS2c;
   CCFGSetMap m_mapS0tS1tS2t;

   CCFGSetIntMap m_mapS0scS1scS2sc;

   CCFGSetMap m_mapS0btS1btS2bt;
   CCFGSetMap m_mapS0etS1etS2et;

   // past action
   CActionMap m_mapA1;
   CAction2Map m_mapA1A2;

   // Rule dictionary
   unsigned long m_nMaxWordFrequency;
   CWordToIntMap m_mapWordFrequency;

public:

   CWeight(bool bTrain, unsigned TABLE_SIZE = DEFAULT_TABLE_SIZE) : 
                          CWeightBase(bTrain) ,

                          m_nMaxWordFrequency(0) ,
                          m_mapWordFrequency(TABLE_SIZE),

                          m_mapS0w("S0w", TABLE_SIZE),
                          m_mapS0t("S0t", TABLE_SIZE),
                          m_mapS0c("S0c", TABLE_SIZE),
                          m_mapS0sc("S0sc", TABLE_SIZE),
                          m_mapS0HeadEduSize("S0HeadEduSize", TABLE_SIZE),
                          m_mapS0EDUNUM("S0EDUNUM", TABLE_SIZE),
                          m_mapS0SentBegin("S0SentBegin", TABLE_SIZE),
                          m_mapS0SentEnd("S0SentEnd", TABLE_SIZE),
                          m_mapS0ParaBegin("S0ParaBegin", TABLE_SIZE),
                          m_mapS0ParaEnd("S0ParaEnd", TABLE_SIZE),
                          m_mapS0bw("S0bw", TABLE_SIZE),
                          m_mapS0bt("S0bt", TABLE_SIZE),
                          m_mapS0ew("S0ew", TABLE_SIZE),
                          m_mapS0et("S0et", TABLE_SIZE),
                          m_mapS0EduWords("S0EduWords", TABLE_SIZE),
                          m_mapS1w("S1w", TABLE_SIZE),
                          m_mapS1t("S1t", TABLE_SIZE),
                          m_mapS1c("S1c", TABLE_SIZE),
                          m_mapS1sc("S1sc", TABLE_SIZE),
                          m_mapS1HeadEduSize("S1HeadEduSize", TABLE_SIZE),
                          m_mapS1EDUNUM("S1EDUNUM", TABLE_SIZE),
                          m_mapS1SentBegin("S1SentBegin", TABLE_SIZE),
                          m_mapS1SentEnd("S1SentEnd", TABLE_SIZE),
                          m_mapS1ParaBegin("S1ParaBegin", TABLE_SIZE),
                          m_mapS1ParaEnd("S1ParaEnd", TABLE_SIZE),
                          m_mapS1bw("S1bw", TABLE_SIZE),
                          m_mapS1bt("S1bt", TABLE_SIZE),
                          m_mapS1ew("S1ew", TABLE_SIZE),
                          m_mapS1et("S1et", TABLE_SIZE),
                          m_mapS1EduWords("S1EduWords", TABLE_SIZE),
                          m_mapS2w("S2w", TABLE_SIZE),
                          m_mapS2t("S2t", TABLE_SIZE),
                          m_mapS2c("S2c", TABLE_SIZE),
                          m_mapS2sc("S2sc", TABLE_SIZE),
                          m_mapS2HeadEduSize("S2HeadEduSize", TABLE_SIZE),
                          m_mapS2EDUNUM("S2EDUNUM", TABLE_SIZE),
                          m_mapS2SentBegin("S2SentBegin", TABLE_SIZE),
                          m_mapS2SentEnd("S2SentEnd", TABLE_SIZE),
                          m_mapS2ParaBegin("S2ParaBegin", TABLE_SIZE),
                          m_mapS2ParaEnd("S2ParaEnd", TABLE_SIZE),
                          m_mapS2bw("S2bw", TABLE_SIZE),
                          m_mapS2bt("S2bt", TABLE_SIZE),
                          m_mapS2ew("S2ew", TABLE_SIZE),
                          m_mapS2et("S2et", TABLE_SIZE),
                          m_mapN0w("N0w", TABLE_SIZE),
                          m_mapN0t("N0t", TABLE_SIZE),
                          m_mapN0sc("N0sc", TABLE_SIZE),
                          m_mapN0HeadEduSize("N0HeadEduSize", TABLE_SIZE),
                          m_mapN0EDUNUM("N0EDUNUM", TABLE_SIZE),
                          m_mapN0SentBegin("N0SentBegin", TABLE_SIZE),
                          m_mapN0SentEnd("N0SentEnd", TABLE_SIZE),
                          m_mapN0ParaBegin("N0ParaBegin", TABLE_SIZE),
                          m_mapN0ParaEnd("N0ParaEnd", TABLE_SIZE),
                          m_mapN0bw("N0bw", TABLE_SIZE),
                          m_mapN0bt("N0bt", TABLE_SIZE),
                          m_mapN0ew("N0ew", TABLE_SIZE),
                          m_mapN0et("N0et", TABLE_SIZE),
                          m_mapN1w("N1w", TABLE_SIZE),
                          m_mapN1t("N1t", TABLE_SIZE),
                          m_mapN1sc("N1sc", TABLE_SIZE),
                          m_mapN1HeadEduSize("N1HeadEduSize", TABLE_SIZE),
                          m_mapN1bw("N1bw", TABLE_SIZE),
                          m_mapN1bt("N1bt", TABLE_SIZE),
                          m_mapN1ew("N1ew", TABLE_SIZE),
                          m_mapN1et("N1et", TABLE_SIZE),
                          m_mapN2w("N2w", TABLE_SIZE),
                          m_mapN2t("N2t", TABLE_SIZE),
                          m_mapN2sc("N2sc", TABLE_SIZE),
                          m_mapN2HeadEduSize("N2HeadEduSize", TABLE_SIZE),
                          m_mapN2bw("N2bw", TABLE_SIZE),
                          m_mapN2bt("N2bt", TABLE_SIZE),
                          m_mapN2ew("N2ew", TABLE_SIZE),
                          m_mapN2et("N2et", TABLE_SIZE),
                          m_mapS0wS1w("S0wS1w", TABLE_SIZE),
                          m_mapS0cS1c("S0cS1c", TABLE_SIZE),
                          m_mapS0tS1t("S0tS1t", TABLE_SIZE),
                          m_mapS0scS1sc("S0scS1sc", TABLE_SIZE),
                          m_mapS0S1HeadEDUSameSentence("S0S1HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS0S1Dist("S0S1Dist", TABLE_SIZE),
                          m_mapS0bwS1bw("S0bwS1bw", TABLE_SIZE),
                          m_mapS0btS1bt("S0btS1bt", TABLE_SIZE),
                          m_mapS0ewS1ew("S0ewS1ew", TABLE_SIZE),
                          m_mapS0etS1et("S0etS1et", TABLE_SIZE),
                          m_mapS0wN0w("S0wN0w", TABLE_SIZE),
                          m_mapS0cN0t("S0cN0t", TABLE_SIZE),
                          m_mapS0tN0t("S0tN0t", TABLE_SIZE),
                          m_mapS0scN0sc("S0scN0sc", TABLE_SIZE),
                          m_mapS0N0HeadEDUSameSentence("S0N0HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS0N0Dist("S0N0Dist", TABLE_SIZE),
                          m_mapS0bwN0bw("S0bwN0bw", TABLE_SIZE),
                          m_mapS0btN0bt("S0btN0bt", TABLE_SIZE),
                          m_mapS0ewN0ew("S0ewN0ew", TABLE_SIZE),
                          m_mapS0etN0et("S0etN0et", TABLE_SIZE),
                          m_mapS1wN0w("S1wN0w", TABLE_SIZE),
                          m_mapS1cN0t("S1cN0t", TABLE_SIZE),
                          m_mapS1tN0t("S1tN0t", TABLE_SIZE),
                          m_mapS1scN0sc("S1scN0sc", TABLE_SIZE),
                          m_mapS1N0HeadEDUSameSentence("S1N0HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS1N0Dist("S1N0Dist", TABLE_SIZE),
                          m_mapS1bwN0bw("S1bwN0bw", TABLE_SIZE),
                          m_mapS1btN0bt("S1btN0bt", TABLE_SIZE),
                          m_mapS1ewN0ew("S1ewN0ew", TABLE_SIZE),
                          m_mapS1etN0et("S1etN0et", TABLE_SIZE),
                          m_mapS1wS2w("S1wS2w", TABLE_SIZE),
                          m_mapS1cS2c("S1cS2c", TABLE_SIZE),
                          m_mapS1tS2t("S1tS2t", TABLE_SIZE),
                          m_mapS1scS2sc("S1scS2sc", TABLE_SIZE),
                          m_mapS1S2HeadEDUSameSentence("S1S2HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS1S2Dist("S1S2Dist", TABLE_SIZE),
                          m_mapS1bwS2bw("S1bwS2bw", TABLE_SIZE),
                          m_mapS1btS2bt("S1btS2bt", TABLE_SIZE),
                          m_mapS1ewS2ew("S1ewS2ew", TABLE_SIZE),
                          m_mapS1etS2et("S1etS2et", TABLE_SIZE),
                          m_mapN0wN1w("N0wN1w", TABLE_SIZE),
                          m_mapN0tN1t("N0tN1t", TABLE_SIZE),
                          m_mapN0scN1sc("N0scN1sc", TABLE_SIZE),
                          m_mapN0bwN1bw("N0bwN1bw", TABLE_SIZE),
                          m_mapN0btN1bt("N0btN1bt", TABLE_SIZE),
                          m_mapN0ewN1ew("N0ewN1ew", TABLE_SIZE),
                          m_mapN0etN1et("N0etN1et", TABLE_SIZE),
                          m_mapS0cS1cN0t("S0cS1cN0t", TABLE_SIZE),
                          m_mapS0tS1tN0t("S0tS1tN0t", TABLE_SIZE),
                          m_mapS0scS1scN0sc("S0scS1scN0sc", TABLE_SIZE),
                          m_mapS0btS1btN0bt("S0btS1btN0bt", TABLE_SIZE),
                          m_mapS0etS1etN0et("S0etS1etN0et", TABLE_SIZE),
                          m_mapS0cN0tN1t("S0cN0tN1t", TABLE_SIZE),
                          m_mapS0tN0tN1t("S0tN0tN1t", TABLE_SIZE),
                          m_mapS0jN0tN1t("S0jN0tN1t", TABLE_SIZE),
                          m_mapS0scN0scN1sc("S0scN0scN1sc", TABLE_SIZE),
                          m_mapS0btN0btN1bt("S0btN0btN1bt", TABLE_SIZE),
                          m_mapS0etN0etN1et("S0etN0etN1et", TABLE_SIZE),
                          m_mapS0cS1cS2c("S0cS1cS2c", TABLE_SIZE),
                          m_mapS0tS1tS2t("S0tS1tS2t", TABLE_SIZE),
                          m_mapS0scS1scS2sc("S0scS1scS2sc", TABLE_SIZE),
                          m_mapS0btS1btS2bt("S0btS1btS2bt", TABLE_SIZE),
                          m_mapS0etS1etS2et("S0etS1etS2et", TABLE_SIZE),
                          m_mapA1("A1", TABLE_SIZE),
                          m_mapA1A2("A1A2", TABLE_SIZE) { }
   ~CWeight() {
   }

   // MEHTODS
   virtual void loadScores(std::ifstream &is);
   virtual void saveScores(std::ofstream &os);
   virtual void outputScores();
   void computeAverageFeatureWeights(int round);
   SCORE_TYPE dotProduct(CWeight &w);
   void clear() {
      iterate_templates(,.clear(););
   }
   void addCurrent(CWeight*w, int round);
   void subtractCurrent(CWeight*w, int round);
   void scaleCurrent(const SCORE_TYPE &scale, const int &round) {
      iterate_templates(,ID(.scaleCurrent(scale, round);));
   }
   SCORE_TYPE squareNorm() {
      static SCORE_TYPE retval;
      retval = 0;
      iterate_templates(retval+=,.squareNorm(););
      return retval;
   }
 
};

};
};

#endif
