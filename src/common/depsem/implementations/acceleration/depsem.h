// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * depsem.h - the definitions for the dependency parser.     *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 * 2015.01.06                         *
 *                                                              *
 ****************************************************************/

#ifndef _DEPSEM_IMPL_H
#define _DEPSEM_IMPL_H 

#include "depsem_base.h"

/*===============================================================
 *
 * Global items
 *
 *==============================================================*/

namespace TARGET_LANGUAGE {

namespace depsem {

#include "state.h"

}; // namespace depsem
};

#include "depsem_weight.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CDepParser - the dependency parser for English 
 *
 *==============================================================*/

class CDepParser : public CDepParserBase {

private:

   CAgendaSimple<depsem::action::CScoredAction> *m_Beam;

   // caches for input
   std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > m_lCache;
   std::vector< CDependencyLabel > m_lCacheLabel;
   std::vector< CSemanticLabel > m_lCacheSemLabel;


   int m_nTrainingRound;
   int m_nTotalErrors;
   bool m_bScoreModified;
   int m_nScoreIndex;

   depsem::CStateItem * lattice_;
   int max_lattice_size_;


   depsem::CWeight *m_delta_weight;

public:
   // constructor and destructor
   CDepParser( const std::string &sFeatureDBPath , bool bTrain ) : CDepParserBase(sFeatureDBPath, bTrain),
             lattice_(0),max_lattice_size_(0) {
      m_Beam = new CAgendaSimple<depsem::action::CScoredAction>(AGENDA_SIZE);
      m_weights = new depsem :: CWeight(sFeatureDBPath, bTrain, depsem::DEP_TABLE_SIZE );
      if(bTrain)m_delta_weight = new depsem::CWeight("", true,  513);
      else m_delta_weight = 0;
      m_nTrainingRound = 0; 
      m_nTotalErrors = 0;
//      m_nScoreIndex = CScore<depsem::SCORE_TYPE>::eNonAverage ; 
      if (bTrain) m_nScoreIndex = CScore<depsem::SCORE_TYPE>::eNonAverage ; else m_nScoreIndex = CScore<depsem::SCORE_TYPE>::eAverage ;
   }
   ~CDepParser() {

      delete m_Beam;
      delete m_weights;
      if(m_delta_weight) delete m_delta_weight;
   }
   CDepParser( CDepParser &depsem) : CDepParserBase(depsem) { 
      assert(1==0);
   }

public:
   void parse( const CDependencyParse &input,  const CSTackFeatsVec &stackfeats,  CDependencyParse *retval , int nBest=1 , depsem::SCORE_TYPE *scores=0 ) ;
   void train( const CDependencyParse &correct, const CSTackFeatsVec  &stackfeats, int round ) ;
   void extract_features( const CDependencyParse &input, const CSTackFeatsVec  &stackfeats, std::ofstream& os ) ;


   void finishtraining() {
      static_cast<depsem::CWeight*>(m_weights)->computeAverageFeatureWeights(m_nTrainingRound);
      static_cast<depsem::CWeight*>(m_weights)->saveScores();
      std::cout << "Total number of training errors are: " << m_nTotalErrors << std::endl;
   }
   depsem::SCORE_TYPE getGlobalScore(const CDependencyParse &parsed);
   void updateScores(const CDependencyParse &parse, const CDependencyParse &correct, int round=0);

private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};


   void work( const bool bTrain, const CTwoStringVector &sentence, const CSTackFeatsVec  &stackfeats, CDependencyParse *retval, const CDependencyParse &correct, int nBest, depsem::SCORE_TYPE *scores ) ;

   inline depsem::SCORE_TYPE getOrUpdateStackScore( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats, const unsigned long &action, depsem::SCORE_TYPE amount=0, int round=0 );

   // update the built-in weight std::vector for this feature object specifically
   inline bool updateScoresForStates(const CSTackFeatsVec &stackfeats, const depsem::CStateItem *outout , const depsem::CStateItem *correct , depsem::SCORE_TYPE amount_add , depsem::SCORE_TYPE amount_subtract ) ;


   depsem::CStateItem * GetLattice(int size);
   int InsertIntoBeam(depsem::CStateItem ** beam,
                      const depsem::CStateItem * item,
                      const int current_beam_size,
                      const int max_beam_size);
   // helper method
   inline void reduce( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats) ;
   inline void shift( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats) ;
   inline void arcleft( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats) ;
   inline void arcright( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats) ;
   inline void poproot( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats) ;
   inline void semanticActions( const depsem::CStateItem *item, const CSTackFeatsVec &stackfeats, unsigned long start_action, unsigned long end_action) ;

};

}; // namespace TARGET_LANGUAGE

#endif


