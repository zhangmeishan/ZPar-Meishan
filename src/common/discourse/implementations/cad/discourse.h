// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * discourse.h - the definitions for the constituent parser.    *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#ifndef _DISCOURSE_IMPL_H
#define _DISCOURSE_IMPL_H 

#include "discourse_base.h"
#include "weight.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CDisParser - the constituent parser
 *
 *==============================================================*/

class CDisParser : public CDisParserBase {

private:

   std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > m_sent;
   std::vector< int > m_edu_starts;
   std::vector< int > m_edu_ends;
   std::vector< int > m_edu_sentids;
   std::vector< int > m_edu_paraids;
   std::vector< int > m_sent_first_edus;
   std::vector< int > m_para_first_edus;
   std::vector< std::vector<const discourse::CConNode*> > m_edu_headspans;
   std::vector< discourse::CConNode > m_syn_nodes;
   std::vector< int > m_syn_roots;
   std::vector< int > m_syn_starts;
   std::vector< int > m_syn_ends;




   int m_nTrainingRound;
   int m_nTotalErrors;
   bool m_bScoreModified;
   int m_nScoreIndex;
   discourse::CContext m_Context;
   discourse::CWeight *m_delta;
   discourse::CRule m_rule;


public:
   // constructor and destructor
   CDisParser( const std::string &sFeatureDBPath , bool bTrain ) : CDisParserBase(sFeatureDBPath, bTrain),
            m_rule(&m_sent, &m_edu_starts, &m_edu_ends, &m_edu_sentids, &m_edu_paraids, &m_sent_first_edus,
            &m_para_first_edus, &m_edu_headspans, &m_syn_nodes, &m_syn_roots, &m_syn_starts, &m_syn_ends) {
      // and initialize the weith module loading content
      m_weights = new discourse :: CWeight( bTrain );
      if (bTrain) {

         m_delta = new discourse::CWeight( bTrain, 512 );
      }
      else {
         m_delta = 0;
      }

      std::ifstream file;
      file.open(sFeatureDBPath.c_str());
      m_weights->loadScores(file);
      // load rules
      file.close();
      // initialize 
      if (!bTrain && m_weights->empty()) { // when decoding, model must be found
         //THROW("The model file " << sFeatureDBPath<< " is not found.")
      }
      m_nTrainingRound = 0; 
      m_nTotalErrors = 0;
      if (bTrain) m_nScoreIndex = CScore<discourse::SCORE_TYPE>::eNonAverage ; else m_nScoreIndex = CScore<discourse::SCORE_TYPE>::eAverage ;
//      ASSERT(discourse::CAction::MAX<=(1LL<<(sizeof(unsigned)*8)), "discourse.h: The size of action is too big for the packed scoretype");
   }

   ~CDisParser() {
      if (m_delta) { delete m_delta; m_delta=0; }
      delete m_weights; m_weights=0;
   }


public:
   void parse( const CSentenceParsed &sentence , CSentenceParsed *retval , int nBest=1 , discourse::SCORE_TYPE *scores=0 ) ;
   void train( const CSentenceParsed &correct , int round ) ;
   void train( const CSentenceParsed &guided , const CSentenceParsed &correct , int round )
   {
	   assert(0);
   }

   void finishtraining() {
      // compute average
      static_cast<discourse::CWeight*>(m_weights)->computeAverageFeatureWeights(m_nTrainingRound);
      // save scores
      std::ofstream file ;
      file.open(m_sFeatureDB.c_str()) ;
      static_cast<discourse::CWeight*>(m_weights)->saveScores(file);
      file.close();
      std::cout << "Total number of training errors are: " << m_nTotalErrors << std::endl;
   }
   discourse::SCORE_TYPE getGlobalScore(const CSentenceParsed &parsed);
   void updateScores(const CSentenceParsed &parse, const CSentenceParsed &correct, int round=0);

private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};

   void work( const bool bTrain, const CSentenceParsed &input , CSentenceParsed *retval, const CSentenceParsed &correct, int nBest, discourse::SCORE_TYPE *scores ) ;

   // get the global score for a parsed sentence or section
   inline void getOrUpdateStackScore( discourse::CWeight *cast_weights, CPackedScoreType<discourse::SCORE_TYPE, discourse::CAction::MAX> &retval, const discourse::CStateItem *item, const discourse::CAction &action=discourse::CAction(), discourse::SCORE_TYPE amount=0, int round=0 );
   inline void getOrUpdateScore( CPackedScoreType<discourse::SCORE_TYPE, discourse::CAction::MAX> &retval, const discourse::CStateItem &item, const discourse::CAction &action=discourse::CAction(), discourse::SCORE_TYPE amount=0, int round=0 );

   // update the built-in weight vector for this feature object specifically
   void updateScoresForState( discourse::CWeight *cast_weights , const discourse::CStateItem *outout , SCORE_UPDATE update) ;

   void updateScoresForStates( const discourse::CStateItem *outout , const discourse::CStateItem *correct ) ;


};

}; // namespace TARGET_LANGUAGE

#endif


