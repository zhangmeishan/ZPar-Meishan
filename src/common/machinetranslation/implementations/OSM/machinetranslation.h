// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * machinetranslation.h - the definitions for the dependency translator.     *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#ifndef _MACHINETRANS_IMPL_H
#define _MACHINETRANS_IMPL_H

#include "machinetranslation_base.h"

/*===============================================================
 *
 * Global items
 *
 *==============================================================*/

namespace TARGET_LANGUAGE {

namespace machinetranslation {

#include "state.h"

}; // namespace machinetranslation
};

#include "machinetranslation_weight.h"

namespace TARGET_LANGUAGE {

typedef CHashMap<CTuple3<CWord, CWord, CWord>, std::map<CWord, float> > CLanguageModel4Type;
typedef CHashMap<CTuple2<CWord, CWord>, std::map<CWord, float> > CLanguageModel3Type;
typedef CHashMap<CWord, std::map<CWord, float> > CLanguageModel2Type;
typedef CHashMap<CWord, float > CLanguageModel1Type;

typedef CHashMap<CTuple3<machinetranslation::CAction, machinetranslation::CAction, machinetranslation::CAction>, std::map<machinetranslation::CAction, float> > CActionLMModel4Type;
typedef CHashMap<CTuple2<machinetranslation::CAction, machinetranslation::CAction>, std::map<machinetranslation::CAction, float> > CActionLMModel3Type;
typedef CHashMap<machinetranslation::CAction, std::map<machinetranslation::CAction, float> > CActionLMModel2Type;
typedef CHashMap<machinetranslation::CAction, float > CActionLMModel1Type;

/*===============================================================
 *
 * CMachineTrans - the dependency translator for English
 *
 *==============================================================*/

class CMachineTrans : public CMachineTransBase {

private:

   CAgendaBeam<machinetranslation::CStateItem> *m_Agenda;
   CAgendaSimple<machinetranslation::CScoredAction> *m_Beam;

   // caches for input
   std::vector< CWord > m_lCache;
   CSTackFeatsVec  m_stackfeats;

   CActionLMModel1Type m_osmLM1;
   CLanguageModel1Type m_targetLM1;
   CLanguageModel1Type m_priorLM1;
   CActionLMModel2Type m_osmLM2;
   CLanguageModel2Type m_targetLM2;
   CLanguageModel2Type m_priorLM2;
   CActionLMModel3Type m_osmLM3;
   CLanguageModel3Type m_targetLM3;
   CLanguageModel3Type m_priorLM3;
   CActionLMModel4Type m_osmLM4;
   CLanguageModel4Type m_targetLM4;
   CLanguageModel4Type m_priorLM4;




   int m_nTrainingRound;
   int m_nTotalErrors;
   bool m_bScoreModified;
   int m_nScoreIndex;

   machinetranslation::CWeight *m_delta_weight;

public:
//added for debug only, will remove it
   std::ofstream m_debug_info;

public:
   // constructor and destructor
   CMachineTrans( const std::string &sFeatureDBPath , bool bTrain ) : CMachineTransBase(sFeatureDBPath, bTrain),
   m_targetLM1(1<<20), m_osmLM1(1<<20), m_priorLM1(1<<20),
   m_targetLM2(1<<20), m_osmLM2(1<<20), m_priorLM2(1<<20),
   m_targetLM3(1<<20), m_osmLM3(1<<20), m_priorLM3(1<<20),
   m_targetLM4(1<<20), m_osmLM4(1<<20), m_priorLM4(1<<20){
      m_Agenda = new CAgendaBeam<machinetranslation::CStateItem>(AGENDA_SIZE);
      m_Beam = new CAgendaSimple<machinetranslation::CScoredAction>(AGENDA_SIZE);
      m_weights = new machinetranslation :: CWeight(sFeatureDBPath, bTrain,  machinetranslation::DEP_TABLE_SIZE);
      m_delta_weight = new machinetranslation :: CWeight("", bTrain, 512 );
      m_nTrainingRound = 0; 
      m_nTotalErrors = 0;
//      m_nScoreIndex = CScore<machinetranslation::SCORE_TYPE>::eNonAverage ;
      if (bTrain) m_nScoreIndex = CScore<machinetranslation::SCORE_TYPE>::eNonAverage ; else m_nScoreIndex = CScore<machinetranslation::SCORE_TYPE>::eAverage ;
   }
   ~CMachineTrans() {
      delete m_Agenda;
      delete m_Beam;
      delete m_weights;
   }
   CMachineTrans( CMachineTrans &machinetranslation) : CMachineTransBase(machinetranslation),
		   m_targetLM1(1<<20), m_osmLM1(1<<20), m_priorLM1(1<<20),
		   m_targetLM2(1<<20), m_osmLM2(1<<20), m_priorLM2(1<<20),
		   m_targetLM3(1<<20), m_osmLM3(1<<20), m_priorLM3(1<<20),
		   m_targetLM4(1<<20), m_osmLM4(1<<20), m_priorLM4(1<<20){
      assert(1==0);
   }

public:
   void translator( const CStringVector &sentence , CAlignedSentencePair *retval, const CSTackFeatsVec  & stackfeats , int nBest=1 , machinetranslation::SCORE_TYPE *scores=0 ) ;
   void train(CAlignedSentencePair &correct, const CSTackFeatsVec  & stackfeats , int round ) ;

   bool first_train(CAlignedSentencePair &correct) ;

   void init_tagetlm(const std::string& lmfile);

   void init_osmlm(const std::string& lmfile);

   void init_priorlm(const std::string& lmfile);


   void FirstTrainInitRules(std::string ruleFile);

   void finishtraining() {
      static_cast<machinetranslation::CWeight*>(m_weights)->computeAverageFeatureWeights(m_nTrainingRound);
      static_cast<machinetranslation::CWeight*>(m_weights)->saveScores();
      std::cout << "Total number of training errors are: " << m_nTotalErrors << std::endl;
   }

   machinetranslation::SCORE_TYPE getGlobalScore(const CAlignedSentencePair &parsed);

   void updateScores(const CAlignedSentencePair &parse, const CAlignedSentencePair &correct, int round=0);

private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};

   void work( const bool bTrain, const CStringVector &sentence , CAlignedSentencePair *retval, const CAlignedSentencePair &correct, const CSTackFeatsVec  & stackfeats, int nBest, machinetranslation::SCORE_TYPE *scores ) ;

   machinetranslation::SCORE_TYPE getOrUpdateActionScore(const machinetranslation::CStateItem *item,  machinetranslation::CAction& action, machinetranslation::SCORE_TYPE amount = 0, unsigned long round = 0 );
   // update the built-in weight std::vector for this feature object specifically
   void updateScoresForStates(const machinetranslation::CStateItem *outout , const machinetranslation::CStateItem *correct , machinetranslation::SCORE_TYPE amount_add , machinetranslation::SCORE_TYPE amount_subtract ) ;

   inline machinetranslation::SCORE_TYPE updateScoreForState(const machinetranslation::CStateItem &from, const machinetranslation::CStateItem *outout , const machinetranslation::SCORE_TYPE &amount ) ;

   inline void ShiftXHelper( const machinetranslation::CStateItem *item);
   inline void ShiftYHelper( const machinetranslation::CStateItem *item);
   inline void InsertGapHelper( const machinetranslation::CStateItem *item);
   inline void JumpBackHelper( const machinetranslation::CStateItem *item);
   inline void JumpForwardHelper( const machinetranslation::CStateItem *item);
   inline void FinishHelper( const machinetranslation::CStateItem *item);
   inline void IdleHelper( const machinetranslation::CStateItem *item);
   inline void GenerateXXHelper( const machinetranslation::CStateItem *item);
   inline void GenerateXYHelper( const machinetranslation::CStateItem *item);
   inline void GenerateYHelper( const machinetranslation::CStateItem *item);
   inline void GenerateXHelper( const machinetranslation::CStateItem *item);


   inline bool ObtainSentencePair2Actions(CAlignedSentencePair &correct);

   inline void CollectTransferRules(CAlignedSentencePair &sentpair);

   inline void AddOneRule(const std::string& source, const std::vector<CWord>& target, float weight1, float weight2, float weight3, int ruletype);

   inline int FindOneRule(const std::string& source, const std::vector<CWord>& target);

   inline void ReadLanguageModel(const std::string& lmfile, CLanguageModel1Type& lm1, CLanguageModel2Type& lm2, CLanguageModel3Type& lm3, CLanguageModel4Type& lm4);

   inline void ReadActionLanguageModel(const std::string& lmfile, CActionLMModel1Type& lm1, CActionLMModel2Type& lm2, CActionLMModel3Type& lm3, CActionLMModel4Type& lm4);

   inline void outputaction(std::ostream &os, const machinetranslation::CStateItem *item, machinetranslation::CAction& action );

};

}; // namespace TARGET_LANGUAGE

#endif


