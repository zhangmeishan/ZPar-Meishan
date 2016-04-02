// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the dependency translator weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _MACHINETRANS_WEIGHTS_H
#define _MACHINETRANS_WEIGHTS_H

#include "machinetranslation_weight_base.h"

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,

//#define iterate_templates(left, right) \
//   left(m_mapSTw)right





//#define iterate_double_templates(left, middle, right)\
//	left  m_mapSTw  middle  m_mapSTw  right





namespace TARGET_LANGUAGE {

namespace machinetranslation {

const static unsigned DEP_TABLE_SIZE = (1<<17);//1000121;

//
// TYPE DEFINITIONS
//
#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,
#define ID_POINTER ->


#define iterate_templates(left,right) \
   left(m_mapLeftWord)right \
   left(m_mapOsmLM)right \
   left(m_mapSrcTgtProb)right \
   left(m_mapTgtSrcProb)right \
   left(m_mapTargetLM)right \
   left(m_mapPriorLM)right \
   left(m_mapUniAction)right \
   left(m_mapBiAction)right \
   left(m_mapTriAction)right \
   left(m_mapFourAction)right \
   left(m_mapUniActionType)right \
   left(m_mapBiActionType)right \
   left(m_mapTriActionType)right \
   left(m_mapFourActionType)right \
   left(m_mapAttributeMap)right \
   left(m_mapSourceLengthBonus)right \
   left(m_mapTargetLengthBonus)right \
   left(m_mapLeftGapBonus)right \
   left(m_mapRightGapBonus)right \
   left(m_mapTransLengthPairBonus)right \
   left(m_mapLeftMostGapDistBonus)right \
   left(m_mapRightMostGapDistBonus)right \
   left(m_mapLeftGapDistBonus)right \
   left(m_mapRightGapDistBonus)right




#define iterate_double_templates(left,middle,right) \
   left m_mapLeftWord middle m_mapLeftWord right \
   left m_mapOsmLM middle m_mapOsmLM right \
   left m_mapSrcTgtProb middle m_mapSrcTgtProb right \
   left m_mapTgtSrcProb middle m_mapTgtSrcProb right \
   left m_mapTargetLM middle m_mapTargetLM right \
   left m_mapPriorLM middle m_mapPriorLM right \
   left m_mapUniAction middle m_mapUniAction right \
   left m_mapBiAction middle m_mapBiAction right \
   left m_mapTriAction middle m_mapTriAction right \
   left m_mapFourAction middle m_mapFourAction right \
   left m_mapUniActionType middle m_mapUniActionType right \
   left m_mapBiActionType middle m_mapBiActionType right \
   left m_mapTriActionType middle m_mapTriActionType right \
   left m_mapFourActionType middle m_mapFourActionType right \
   left m_mapAttributeMap middle m_mapAttributeMap right \
   left m_mapSourceLengthBonus middle m_mapSourceLengthBonus right \
   left m_mapTargetLengthBonus middle m_mapTargetLengthBonus right \
   left m_mapLeftGapBonus middle m_mapLeftGapBonus right \
   left m_mapRightGapBonus middle m_mapRightGapBonus right \
   left m_mapTransLengthPairBonus middle m_mapTransLengthPairBonus right \
   left m_mapLeftMostGapDistBonus middle m_mapLeftMostGapDistBonus right \
   left m_mapRightMostGapDistBonus middle m_mapRightMostGapDistBonus right \
   left m_mapLeftGapDistBonus middle m_mapLeftGapDistBonus right \
   left m_mapRightGapDistBonus middle m_mapRightGapDistBonus right


//
// TYPE DEFINITIONS
//
typedef CScoreMap< CWord, SCORE_TYPE > CWordMap;
typedef CScoreMap< CTwoWords, SCORE_TYPE > CTwoWordsMap;
typedef CScoreMap< std::pair<CWord, int>, SCORE_TYPE > CWordIntMap;
typedef CScoreMap< int, SCORE_TYPE > CIntMap;
typedef CScoreMap< std::pair<int, int>, SCORE_TYPE > CIntPairMap;
typedef CScoreMap< std::string, SCORE_TYPE > CStringMap;

typedef CScoreMap< CAction, SCORE_TYPE > CActionMap;
typedef CScoreMap< CTuple2<CAction, CAction>, SCORE_TYPE > CBiActionMap;
typedef CScoreMap< CTuple3<CAction, CAction, CAction>, SCORE_TYPE > CTriActionMap;
typedef CScoreMap< CTuple4<CAction, CAction, CAction, CAction>, SCORE_TYPE > CFourActionMap;

typedef CScoreMap< CActionType, SCORE_TYPE > CActionTypeMap;
typedef CScoreMap< CTuple2<CActionType, CActionType>, SCORE_TYPE > CBiActionTypeMap;
typedef CScoreMap< CTuple3<CActionType, CActionType, CActionType>, SCORE_TYPE > CTriActionTypeMap;
typedef CScoreMap< CTuple4<CActionType, CActionType, CActionType, CActionType>, SCORE_TYPE > CFourActionTypeMap;

typedef CHashMap<CWord, unsigned long> CWordToIntMap;
typedef CHashMap<unsigned long, unsigned long> CIntToIntMap;


/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:

	CStringToInt m_mapTranslateStart; // if X map to empty word, then Y->NULL
	CStringToInt m_mapTranslateEnd;   // if X map to empty word, then Y->NULL
	std::vector<std::string>	m_mapTranslateSources;
	CTranslateVector	m_mapTranslateRules;
	CTranslateScoreVector	m_mapTranslateRuleScore1s;
	CTranslateScoreVector	m_mapTranslateRuleScore2s;
	CTranslateScoreVector	m_mapTranslateRuleScore3s;
	CTranslateTypeVector m_mapTranslateRuleTypes;
	int m_nTranslationRuleNum;


	//features list:
	CWordMap m_mapLeftWord;
	CIntMap m_mapOsmLM;
	CIntPairMap m_mapSrcTgtProb;
	CIntPairMap m_mapTgtSrcProb;
	CIntMap m_mapTargetLM;
	CIntMap m_mapPriorLM;

	CActionMap m_mapUniAction;
	CBiActionMap m_mapBiAction;
	CTriActionMap m_mapTriAction;
	CFourActionMap m_mapFourAction;

	CActionTypeMap m_mapUniActionType;
	CBiActionTypeMap m_mapBiActionType;
	CTriActionTypeMap m_mapTriActionType;
	CFourActionTypeMap m_mapFourActionType;

	CStringMap m_mapAttributeMap; //currently not in use

	CIntMap m_mapSourceLengthBonus;
	CIntMap m_mapTargetLengthBonus;
	CIntMap m_mapLeftGapBonus;
	CIntMap m_mapRightGapBonus;
	CIntPairMap m_mapTransLengthPairBonus;
	CIntMap m_mapLeftMostGapDistBonus;
	CIntMap m_mapRightMostGapDistBonus;
	CIntMap m_mapLeftGapDistBonus;
	CIntMap m_mapRightGapDistBonus;











//   CTagDict<CWord, CTag> m_mapWordTuple;


public:

   CWeight(const std::string &sPath, bool bTrain, int dep_table_size) : CWeightBase(sPath, bTrain) ,
                                               m_mapTranslateStart(dep_table_size),
                                               m_mapTranslateEnd(dep_table_size),
											   m_mapLeftWord("LeftWord", dep_table_size),
											   m_mapOsmLM("OsmLM", dep_table_size),
											   m_mapSrcTgtProb("SrcTgtProb", dep_table_size),
											   m_mapTgtSrcProb("TgtSrcProb", dep_table_size),
											   m_mapTargetLM("TargetLM", dep_table_size),
											   m_mapPriorLM("PriorLM", dep_table_size),
											   m_mapUniAction("UniAction", dep_table_size),
											   m_mapBiAction("BiAction", dep_table_size),
											   m_mapTriAction("TriAction", dep_table_size),
											   m_mapFourAction("FourAction", dep_table_size),
											   m_mapUniActionType("UniActionType", dep_table_size),
											   m_mapBiActionType("BiActionType", dep_table_size),
											   m_mapTriActionType("TriActionType", dep_table_size),
											   m_mapFourActionType("FourActionType", dep_table_size),
											   m_mapAttributeMap("AttributeMap", dep_table_size),
											   m_mapSourceLengthBonus("SourceLengthBonus", dep_table_size),
											   m_mapTargetLengthBonus("TargetLengthBonus", dep_table_size),
											   m_mapLeftGapBonus("LeftGapBonus", dep_table_size),
											   m_mapRightGapBonus("RightGapBonus", dep_table_size),
											   m_mapTransLengthPairBonus("TransLengthPairBonus", dep_table_size),
											   m_mapLeftMostGapDistBonus("LeftMostGapDistBonus", dep_table_size),
											   m_mapRightMostGapDistBonus("RightMostGapDistBonus", dep_table_size),
											   m_mapLeftGapDistBonus("LeftGapDistBonus", dep_table_size),
											   m_mapRightGapDistBonus("RightGapDistBonus", dep_table_size),
											   m_nTranslationRuleNum(0)

   { loadScores(); }

   virtual ~CWeight() {
   }

   // MEHTODS
   virtual void loadScores();
   virtual void saveScores();
   virtual void outputScores();
   void computeAverageFeatureWeights(int round);

   void clear() {
      iterate_templates(,.clear(););
   }

   SCORE_TYPE squareNorm() {
      static SCORE_TYPE retval;
      retval = 0;
      iterate_templates(retval+=,.squareNorm(););
      return retval;
   }

   void scaleCurrent(const SCORE_TYPE &scale, const int &round) {
      iterate_templates(,ID(.scaleCurrent(scale, round);));
   }

   void addCurrent(CWeight*w, int round);
   void subtractCurrent(CWeight*w, int round);

   // load translation rules from external files
   void loadTranslationRules()
   {

   }
 
};

};
};

#endif
