// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * chartagger.h - the definitions for the dependency parser.     *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#ifndef _CHARTAGGER_IMPL_H
#define _CHARTAGGER_IMPL_H

#include "chartagger_base.h"

/*===============================================================
 *
 * Global items
 *
 *==============================================================*/

namespace TARGET_LANGUAGE {

namespace chartagger {

#include "state.h"

}; // namespace chartagger
};

#include "chartagger_weight.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CCharTagger - the dependency parser for English
 *
 *==============================================================*/

class CCharTagger : public CCharTaggerBase {

private:

   CAgendaSimple<chartagger::action::CScoredAction> *m_Beam;

   chartagger::CStateItem * lattice_;
   int max_lattice_size_;

   // caches for input
   CWordCache m_lCache;
   CStringVector m_Sentence;
   std::vector< int > m_wordIndexs;
   int m_nSentSize;


   int m_nTrainingRound;
   int m_nTotalErrors;
   bool m_bScoreModified;
   int m_nScoreIndex;

   chartagger::CWeight *m_delta_weight;

public:
   // constructor and destructor
   CCharTagger( const std::string &sFeatureDBPath , bool bTrain ) : CCharTaggerBase(sFeatureDBPath, bTrain), m_lCache(chartagger::MAX_SENTENCE_SIZE),
   lattice_(0),max_lattice_size_(0){
      m_Beam = new CAgendaSimple<chartagger::action::CScoredAction>(AGENDA_SIZE);
      m_weights = new chartagger :: CWeight(sFeatureDBPath, bTrain, 65536 );
      m_nTrainingRound = 0; 
      m_nTotalErrors = 0;
//      m_nScoreIndex = CScore<chartagger::SCORE_TYPE>::eNonAverage ;
      if (bTrain){
        m_nScoreIndex = CScore<chartagger::SCORE_TYPE>::eNonAverage ;
        m_delta_weight = new chartagger :: CWeight("", bTrain, 512 );
      }
      else{
        m_nScoreIndex = CScore<chartagger::SCORE_TYPE>::eAverage ;
        m_delta_weight = 0;
      }

   }
   ~CCharTagger() {
     delete m_Beam;
     delete m_weights;
     if(m_delta_weight) delete m_delta_weight;
     releaseLattice();

   }
/*
   CCharTagger( CCharTagger &chartagger) : CCharTaggerBase(chartagger) {
      assert(1==0);
   }
*/
public:
   void parse( const CStringVector &sentence , CDependencyParse *retval, int nBest=1 , chartagger::SCORE_TYPE *scores=0 ) ;
   void train( const CDependencyParse &correct, int round ) ;

   void finishtraining() {
      static_cast<chartagger::CWeight*>(m_weights)->computeAverageFeatureWeights(m_nTrainingRound);
      static_cast<chartagger::CWeight*>(m_weights)->saveScores();
      std::cout << "Total number of training errors are: " << m_nTotalErrors << std::endl;
   }

   chartagger::SCORE_TYPE getGlobalScore(const CDependencyParse &parsed);

   void updateScores(const CDependencyParse &parse, const CDependencyParse &correct, int round=0);

private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};

   chartagger::CStateItem * getLattice(int size);
   int insertIntoBeam(chartagger::CStateItem ** beam,
                      const chartagger::CStateItem * item,
                      const int current_beam_size,
                      const int max_beam_size);

   void releaseLattice(){
     if(max_lattice_size_ > 0){
       for (int i = 0; i < max_lattice_size_; ++i) {
         lattice_[i].clear();
       }
       delete[] lattice_;
       lattice_ = NULL;
     }
   }

   void work( const bool bTrain, const CStringVector &sentence , CDependencyParse *retval, const CDependencyParse &correct, int nBest, chartagger::SCORE_TYPE *scores ) ;

   inline chartagger::SCORE_TYPE getOrUpdateStackScore( const chartagger::CStateItem *item, const unsigned &action, chartagger::SCORE_TYPE amount=0, int round=0 );

   // update the built-in weight std::vector for this feature object specifically
   bool updateScoresForStates(const chartagger::CStateItem *outout , const chartagger::CStateItem *correct , chartagger::SCORE_TYPE amount_add , chartagger::SCORE_TYPE amount_subtract ) ;



   // helper method
   inline void shift( const chartagger::CStateItem *item) ;
   inline void finish( const chartagger::CStateItem *item) ;
   inline void shiftin( const chartagger::CStateItem *item) ;
   inline void arcleft( const chartagger::CStateItem *item) ;
   inline void arcright( const chartagger::CStateItem *item) ;
   inline void idle( const chartagger::CStateItem *item) ;

};

}; // namespace TARGET_LANGUAGE

#endif


