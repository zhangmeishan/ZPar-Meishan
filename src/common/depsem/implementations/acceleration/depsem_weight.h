// Copyright (C) SUTD 2015
/***************************************************************
 *
 * weight.h - the dependency parser weights 
 *
 * Meishan Zhang, 01.06.2015
 *
 ***************************************************************/

#ifndef _DEPSEM_WEIGHTS_H
#define _DEPSEM_WEIGHTS_H

#include "depsem_weight_base.h"

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,
#define ID_POINTER ->

#define iterate_templates(left, right) \
   left(m_mapSTw)right\
   left(m_mapSTt)right\
   left(m_mapSTwt)right\
   left(m_mapN0w)right\
   left(m_mapN0t)right\
   left(m_mapN0wt)right\
   left(m_mapN1w)right\
   left(m_mapN1t)right\
   left(m_mapN1wt)right\
   left(m_mapN2w)right\
   left(m_mapN2t)right\
   left(m_mapN2wt)right\
   left(m_mapSTHw)right\
   left(m_mapSTHt)right\
   left(m_mapSTi)right\
   left(m_mapSTHHw)right\
   left(m_mapSTHHt)right\
   left(m_mapSTHi)right\
   left(m_mapSTLDw)right\
   left(m_mapSTLDt)right\
   left(m_mapSTLDi)right\
   left(m_mapSTRDw)right\
   left(m_mapSTRDt)right\
   left(m_mapSTRDi)right\
   left(m_mapN0LDw)right\
   left(m_mapN0LDt)right\
   left(m_mapN0LDi)right\
   left(m_mapSTL2Dw)right\
   left(m_mapSTL2Dt)right\
   left(m_mapSTL2Di)right\
   left(m_mapSTR2Dw)right\
   left(m_mapSTR2Dt)right\
   left(m_mapSTR2Di)right\
   left(m_mapN0L2Dw)right\
   left(m_mapN0L2Dt)right\
   left(m_mapN0L2Di)right\
   left(m_mapHTw)right\
   left(m_mapHTt)right\
   left(m_mapHTwt)right\
\
   left(m_mapSTwtN0wt)right\
   left(m_mapSTwtN0w)right\
   left(m_mapSTwN0wt)right\
   left(m_mapSTtN0wt)right\
   left(m_mapSTwtN0t)right\
   left(m_mapSTwN0w)right\
   left(m_mapSTtN0t)right\
\
   left(m_mapN0tN1t)right\
   left(m_mapN0tN1tN2t)right\
   left(m_mapSTtN0tN1t)right\
   left(m_mapSTtN0tN0LDt)right\
   left(m_mapN0tN0LDtN0L2Dt)right\
   left(m_mapSTHtSTtN0t)right\
   left(m_mapHTtHT2tN0t)right\
   left(m_mapSTHHtSTHtSTt)right\
   left(m_mapSTtSTLDtN0t)right\
   left(m_mapSTtSTLDtSTL2Dt)right\
   left(m_mapSTtSTRDtN0t)right\
   left(m_mapSTtSTRDtSTR2Dt)right\
\
   left(m_mapSTwd)right\
   left(m_mapSTtd)right\
   left(m_mapN0wd)right\
   left(m_mapN0td)right\
   left(m_mapSTwN0wd)right\
   left(m_mapSTtN0td)right\
\
   left(m_mapSTwra)right\
   left(m_mapSTtra)right\
   left(m_mapSTwla)right\
   left(m_mapSTtla)right\
   left(m_mapN0wla)right\
   left(m_mapN0tla)right\
\
   left(m_mapSTwrp)right\
   left(m_mapSTtrp)right\
   left(m_mapSTwlp)right\
   left(m_mapSTtlp)right\
   left(m_mapN0wlp)right\
   left(m_mapN0tlp)right\
\
   left(m_mapSTl)right\
   left(m_mapN0l)right\
   left(m_mapN1l)right



#define iterate_double_templates(left,middle,right) \
   left m_mapSTw middle m_mapSTw right \
   left m_mapSTt middle m_mapSTt right \
   left m_mapSTwt middle m_mapSTwt right \
   left m_mapN0w middle m_mapN0w right \
   left m_mapN0t middle m_mapN0t right \
   left m_mapN0wt middle m_mapN0wt right \
   left m_mapN1w middle m_mapN1w right \
   left m_mapN1t middle m_mapN1t right \
   left m_mapN1wt middle m_mapN1wt right \
   left m_mapN2w middle m_mapN2w right \
   left m_mapN2t middle m_mapN2t right \
   left m_mapN2wt middle m_mapN2wt right \
   left m_mapSTHw middle m_mapSTHw right \
   left m_mapSTHt middle m_mapSTHt right \
   left m_mapSTi middle m_mapSTi right \
   left m_mapSTHHw middle m_mapSTHHw right \
   left m_mapSTHHt middle m_mapSTHHt right \
   left m_mapSTHi middle m_mapSTHi right \
   left m_mapSTLDw middle m_mapSTLDw right \
   left m_mapSTLDt middle m_mapSTLDt right \
   left m_mapSTLDi middle m_mapSTLDi right \
   left m_mapSTRDw middle m_mapSTRDw right \
   left m_mapSTRDt middle m_mapSTRDt right \
   left m_mapSTRDi middle m_mapSTRDi right \
   left m_mapN0LDw middle m_mapN0LDw right \
   left m_mapN0LDt middle m_mapN0LDt right \
   left m_mapN0LDi middle m_mapN0LDi right \
   left m_mapSTL2Dw middle m_mapSTL2Dw right \
   left m_mapSTL2Dt middle m_mapSTL2Dt right \
   left m_mapSTL2Di middle m_mapSTL2Di right \
   left m_mapSTR2Dw middle m_mapSTR2Dw right \
   left m_mapSTR2Dt middle m_mapSTR2Dt right \
   left m_mapSTR2Di middle m_mapSTR2Di right \
   left m_mapN0L2Dw middle m_mapN0L2Dw right \
   left m_mapN0L2Dt middle m_mapN0L2Dt right \
   left m_mapN0L2Di middle m_mapN0L2Di right \
 \
   left m_mapHTw middle m_mapHTw right \
   left m_mapHTt middle m_mapHTt right \
   left m_mapHTwt middle m_mapHTwt right \
   left m_mapSTwtN0wt middle m_mapSTwtN0wt right \
   left m_mapSTwtN0w middle m_mapSTwtN0w right \
   left m_mapSTwN0wt middle m_mapSTwN0wt right \
   left m_mapSTtN0wt middle m_mapSTtN0wt right \
   left m_mapSTwtN0t middle m_mapSTwtN0t right \
   left m_mapSTwN0w middle m_mapSTwN0w right \
   left m_mapSTtN0t middle m_mapSTtN0t right \
   left m_mapN0tN1t middle m_mapN0tN1t right \
   left m_mapN0tN1tN2t middle m_mapN0tN1tN2t right \
   left m_mapSTtN0tN1t middle m_mapSTtN0tN1t right \
   left m_mapSTtN0tN0LDt middle m_mapSTtN0tN0LDt right \
   left m_mapN0tN0LDtN0L2Dt middle m_mapN0tN0LDtN0L2Dt right \
   left m_mapSTHtSTtN0t middle m_mapSTHtSTtN0t right \
   left m_mapHTtHT2tN0t middle m_mapHTtHT2tN0t right \
   left m_mapSTHHtSTHtSTt middle m_mapSTHHtSTHtSTt right \
   left m_mapSTtSTLDtN0t middle m_mapSTtSTLDtN0t right \
   left m_mapSTtSTLDtSTL2Dt middle m_mapSTtSTLDtSTL2Dt right \
   left m_mapSTtSTRDtN0t middle m_mapSTtSTRDtN0t right \
   left m_mapSTtSTRDtSTR2Dt middle m_mapSTtSTRDtSTR2Dt right \
\
   left m_mapSTwd middle m_mapSTwd right \
   left m_mapSTtd middle m_mapSTtd right \
   left m_mapN0wd middle m_mapN0wd right \
   left m_mapN0td middle m_mapN0td right \
   left m_mapSTwN0wd middle m_mapSTwN0wd right \
   left m_mapSTtN0td middle m_mapSTtN0td right \
   left m_mapSTwra middle m_mapSTwra right \
   left m_mapSTtra middle m_mapSTtra right \
   left m_mapSTwla middle m_mapSTwla right \
   left m_mapSTtla middle m_mapSTtla right \
   left m_mapN0wla middle m_mapN0wla right \
   left m_mapN0tla middle m_mapN0tla right \
   left m_mapSTwrp middle m_mapSTwrp right \
   left m_mapSTtrp middle m_mapSTtrp right \
   left m_mapSTwlp middle m_mapSTwlp right \
   left m_mapSTtlp middle m_mapSTtlp right \
   left m_mapN0wlp middle m_mapN0wlp right \
   left m_mapN0tlp middle m_mapN0tlp right \
\
   left m_mapSTl middle m_mapSTl right \
   left m_mapN0l middle m_mapN0l right \
   left m_mapN1l middle m_mapN1l right


namespace TARGET_LANGUAGE {

namespace depsem {

const static unsigned DEP_TABLE_SIZE = (1<<17);//1000121;

//
// TYPE DEFINITIONS
//
typedef CScoreMap< std::pair<CWord, unsigned long>, SCORE_TYPE> CWordACMap;
typedef CScoreMap< std::pair<CTag, unsigned long>, SCORE_TYPE> CTagACMap;
typedef CScoreMap< std::pair<int, unsigned long>, SCORE_TYPE> CIntACMap;
typedef CScoreMap< std::pair<CTagSet<CTag, 2>, unsigned long>, SCORE_TYPE> CTagSet2ACMap;
typedef CScoreMap< std::pair<CTagSet<CTag, 3>, unsigned long>, SCORE_TYPE> CTagSet3ACMap;
typedef CScoreMap< std::pair<CTagSet<CTag, 4>, unsigned long>, SCORE_TYPE> CTagSet4ACMap;
typedef CScoreMap< std::pair<CTuple2<CWord, CTag>, unsigned long>, SCORE_TYPE> CWordTagACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CTag, CTag>, unsigned long>, SCORE_TYPE> CWordTagTagACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CWord, CTag>, unsigned long>, SCORE_TYPE> CWordWordTagACMap;
typedef CScoreMap< std::pair<CTaggedWord<CTag, TAG_SEPARATOR>, unsigned long>, SCORE_TYPE> CTaggedWordACMap;
typedef CScoreMap< std::pair<CTwoWords, unsigned long>, SCORE_TYPE> CTwoWordsACMap;
typedef CScoreMap< std::pair<CTwoTaggedWords, unsigned long>, SCORE_TYPE> CTwoTaggedWordsACMap;
typedef CScoreMap< std::pair<CTuple2<CWord, int>, unsigned long>, SCORE_TYPE> CWordIntACMap;
typedef CScoreMap< std::pair<CTuple2<CTag, int>, unsigned long>, SCORE_TYPE> CTagIntACMap;
typedef CScoreMap< std::pair<CTuple3<CTag, CTag, int>, unsigned long>, SCORE_TYPE> CTagTagIntACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CWord, int>, unsigned long>, SCORE_TYPE> CWordWordIntACMap;
typedef CScoreMap< std::pair<CTuple2< CWord, CSetOfTags<CDependencyLabel> >, unsigned long>, SCORE_TYPE> CWordSetOfLabelsACMap;
typedef CScoreMap< std::pair<CTuple2< CTag, CSetOfTags<CDependencyLabel> >, unsigned long>, SCORE_TYPE> CTagSetOfLabelsACMap;

typedef CScoreMap< std::pair<CLemma, unsigned long>, SCORE_TYPE> CLemmaACMap;


/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:

	//default features are combined with action
	//if not combined, please use m_mapXXX_WOAC to define variable
   CWordACMap m_mapSTw;
   CTagACMap m_mapSTt;
   CTaggedWordACMap m_mapSTwt;

   CWordACMap m_mapN0w;
   CTagACMap m_mapN0t;
   CTaggedWordACMap m_mapN0wt;

   CWordACMap m_mapN1w;
   CTagACMap m_mapN1t;
   CTaggedWordACMap m_mapN1wt;

   CWordACMap m_mapN2w;
   CTagACMap m_mapN2t;
   CTaggedWordACMap m_mapN2wt;

   CWordACMap m_mapSTHw;
   CTagACMap m_mapSTHt;
   CIntACMap m_mapSTi;

   CWordACMap m_mapSTHHw;
   CTagACMap m_mapSTHHt;
   CIntACMap m_mapSTHi;

   CWordACMap m_mapSTLDw;
   CTagACMap m_mapSTLDt;
   CIntACMap m_mapSTLDi;

   CWordACMap m_mapSTRDw;
   CTagACMap m_mapSTRDt;
   CIntACMap m_mapSTRDi;

   CWordACMap m_mapN0LDw;
   CTagACMap m_mapN0LDt;
   CIntACMap m_mapN0LDi;

   CWordACMap m_mapSTL2Dw;
   CTagACMap m_mapSTL2Dt;
   CIntACMap m_mapSTL2Di;

   CWordACMap m_mapSTR2Dw;
   CTagACMap m_mapSTR2Dt;
   CIntACMap m_mapSTR2Di;

   CWordACMap m_mapN0L2Dw;
   CTagACMap m_mapN0L2Dt;
   CIntACMap m_mapN0L2Di;

   CWordACMap m_mapHTw;
   CTagACMap m_mapHTt;
   CTaggedWordACMap m_mapHTwt;

   CTwoTaggedWordsACMap m_mapSTwtN0wt;
   CWordWordTagACMap m_mapSTwtN0w;
   CWordWordTagACMap m_mapSTwN0wt;
   CWordTagTagACMap m_mapSTtN0wt;
   CWordTagTagACMap m_mapSTwtN0t;
   CTwoWordsACMap m_mapSTwN0w;
   CTagSet2ACMap m_mapSTtN0t;

   CTagSet2ACMap m_mapN0tN1t;
   CTagSet3ACMap m_mapN0tN1tN2t;
   CTagSet3ACMap m_mapSTtN0tN1t;
   CTagSet3ACMap m_mapSTtN0tN0LDt;
   CTagSet3ACMap m_mapN0tN0LDtN0L2Dt;
   CTagSet3ACMap m_mapSTHtSTtN0t;
   CTagSet3ACMap m_mapHTtHT2tN0t;
   CTagSet3ACMap m_mapSTHHtSTHtSTt;
   CTagSet3ACMap m_mapSTtSTLDtN0t;
   CTagSet3ACMap m_mapSTtSTLDtSTL2Dt;
   CTagSet3ACMap m_mapSTtSTRDtN0t;
   CTagSet3ACMap m_mapSTtSTRDtSTR2Dt;

   CWordIntACMap m_mapSTwd;
   CTagIntACMap m_mapSTtd;
   CWordIntACMap m_mapN0wd;
   CTagIntACMap m_mapN0td;
   CWordWordIntACMap m_mapSTwN0wd;
   CTagTagIntACMap m_mapSTtN0td;

   CWordIntACMap m_mapSTwra;
   CTagIntACMap m_mapSTtra;
   CWordIntACMap m_mapSTwla;
   CTagIntACMap m_mapSTtla;
   CWordIntACMap m_mapN0wla;
   CTagIntACMap m_mapN0tla;

   CWordSetOfLabelsACMap m_mapSTwrp;
   CTagSetOfLabelsACMap m_mapSTtrp;
   CWordSetOfLabelsACMap m_mapSTwlp;
   CTagSetOfLabelsACMap m_mapSTtlp;
   CWordSetOfLabelsACMap m_mapN0wlp;
   CTagSetOfLabelsACMap m_mapN0tlp;

   CLemmaACMap m_mapSTl;
   CLemmaACMap m_mapN0l;
   CLemmaACMap m_mapN1l;


public:

   CWeight(const std::string &sPath, bool bTrain, int dep_table_size) : CWeightBase(sPath, bTrain) ,

                                               m_mapSTw("StackWord", dep_table_size),
                                               m_mapSTt("StackTag", dep_table_size),
                                               m_mapSTwt("StackWordTag", dep_table_size),

                                               m_mapN0w("NextWord", dep_table_size),
                                               m_mapN0t("NextTag", dep_table_size),
                                               m_mapN0wt("NextWordTag", dep_table_size),

                                               m_mapN1w("Next+1Word", dep_table_size),
                                               m_mapN1t("Next+1Tag", dep_table_size),
                                               m_mapN1wt("Next+1WordTag", dep_table_size),

                                               m_mapN2w("Next+2Word", dep_table_size),
                                               m_mapN2t("Next+2Tag", dep_table_size),
                                               m_mapN2wt("Next+2WordTag", dep_table_size),

                                               m_mapSTHw("StackHeadWord", dep_table_size),
                                               m_mapSTHt("StackHeadTag", dep_table_size),
                                               m_mapSTi("StackLabel", dep_table_size),

                                               m_mapSTHHw("StackHeadHeadWord", dep_table_size),
                                               m_mapSTHHt("StackHeadHeadTag", dep_table_size),
                                               m_mapSTHi("StackLabel", dep_table_size),

                                               m_mapSTLDw("StackLDWord", dep_table_size),
                                               m_mapSTLDt("StackLDTag", dep_table_size),
                                               m_mapSTLDi("StackLDLabel", dep_table_size),

                                               m_mapSTRDw("StackRDWord", dep_table_size),
                                               m_mapSTRDt("StackRDTag", dep_table_size),
                                               m_mapSTRDi("StackRDLabel", dep_table_size),

                                               m_mapN0LDw("NextLDWord", dep_table_size),
                                               m_mapN0LDt("NextLDTag", dep_table_size),
                                               m_mapN0LDi("NextLDLabel", dep_table_size),

                                               m_mapSTL2Dw("StackL2DWord", dep_table_size),
                                               m_mapSTL2Dt("StackL2DTag", dep_table_size),
                                               m_mapSTL2Di("StackL2DLabel", dep_table_size),

                                               m_mapSTR2Dw("StackR2DWord", dep_table_size),
                                               m_mapSTR2Dt("StackR2DTag", dep_table_size),
                                               m_mapSTR2Di("StackR2DLabel", dep_table_size),

                                               m_mapN0L2Dw("NextL2DWord", dep_table_size),
                                               m_mapN0L2Dt("NextL2DTag", dep_table_size),
                                               m_mapN0L2Di("NextL2DLabel", dep_table_size),

                                               m_mapHTw("HeadStackWord", dep_table_size),
                                               m_mapHTt("HeadStackTag", dep_table_size),
                                               m_mapHTwt("HeadStackWordTag", dep_table_size),

                                               m_mapSTwtN0wt("StackWordTagNextWordTag", dep_table_size),
                                               m_mapSTwtN0w("StackWordTagNextWord", dep_table_size),
                                               m_mapSTwN0wt("StackWordNextWordTag", dep_table_size),
                                               m_mapSTtN0wt("StackTagNextWordTag", dep_table_size),
                                               m_mapSTwtN0t("StackWordTagNextTag", dep_table_size),
                                               m_mapSTwN0w("StackWordNextWord", dep_table_size),
                                               m_mapSTtN0t("StackTagNextTag", dep_table_size),

                                               m_mapN0tN1t("NextTagNext+1Tag", dep_table_size),
                                               m_mapN0tN1tN2t("NextTagTrigram", dep_table_size),
                                               m_mapSTtN0tN1t("StackTagNextTagNext+1Tag", dep_table_size),
                                               m_mapSTtN0tN0LDt("StackTagNextTagNextLDTag", dep_table_size),
                                               m_mapN0tN0LDtN0L2Dt("StackTagNextTagNextLDTagNextTagNextL2DTag", dep_table_size),
                                               m_mapSTHtSTtN0t("StackHeadTagStackTagNextTag", dep_table_size),
                                               m_mapHTtHT2tN0t("HeadStackTagHeadStack2TagNextTag", dep_table_size),
                                               m_mapSTHHtSTHtSTt("StackHeadHeadTagStackHeadTagStackTag", dep_table_size),
                                               m_mapSTtSTLDtN0t("StackTagStackLDTagNextTag", dep_table_size),
                                               m_mapSTtSTLDtSTL2Dt("StackTagStackLDTagStackL2DTag", dep_table_size),
                                               m_mapSTtSTRDtN0t("StackTagStackRDTagNextTag", dep_table_size),
                                               m_mapSTtSTRDtSTR2Dt("StackTagStackRDTagStackR2DTag", dep_table_size),

                                               m_mapSTwd("StackWordDist", dep_table_size),
                                               m_mapSTtd("StackTagDist", dep_table_size),
                                               m_mapN0wd("NextWordDist", dep_table_size),
                                               m_mapN0td("NextTagDist", dep_table_size),
                                               m_mapSTwN0wd("StackWordNextWordDist", dep_table_size),
                                               m_mapSTtN0td("StackTagNextTagDist", dep_table_size),

                                               m_mapSTwra("StackWordRightArity", dep_table_size),
                                               m_mapSTtra("StackTagRightArity", dep_table_size),
                                               m_mapSTwla("StackWordLeftArity", dep_table_size),
                                               m_mapSTtla("StackTagLeftArity", dep_table_size),
                                               m_mapN0wla("NextWordRightArity", dep_table_size),
                                               m_mapN0tla("NextTagRightArity", dep_table_size),

                                               m_mapSTwrp("StackWordRightSetoftags", dep_table_size),
                                               m_mapSTtrp("StackTagRightSetoftags", dep_table_size),
                                               m_mapSTwlp("StackWordLeftSetoftags", dep_table_size),
                                               m_mapSTtlp("StackTagLeftSetoftags", dep_table_size),
                                               m_mapN0wlp("Next0WordLeftSetoftags", dep_table_size),
                                               m_mapN0tlp("Next0TagLeftSetoftags", dep_table_size),

                                               m_mapSTl("StackLemma", dep_table_size),
                                               m_mapN0l("NextLemma", dep_table_size),
                                               m_mapN1l("Next+1Lemma", dep_table_size)
   { loadScores(); }

   virtual ~CWeight() {
//      iterate_templates(,.freePoolMemory(););
//      CPackedScore<SCORE_TYPE>::freePoolMemory();
   }

   // MEHTODS
   virtual void loadScores();
   virtual void saveScores();
   virtual void outputScores();
   void computeAverageFeatureWeights(int round);
   //SCORE_TYPE dotProduct(const CWeight &w);

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
 
};

};
};

#endif
