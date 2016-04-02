// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * depparser_base.h - the definition for the dependency parser. *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.10                        *
 *                                                              *
 ****************************************************************/

#ifndef _CHARTAGGER_BASE_H
#define _CHARTAGGER_BASE_H

#include "chartagger_base_include.h"
#include "chartagger_weight_base.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CCharTaggerBase - the general dependency parser def
 *
 *==============================================================*/

class CCharTaggerBase {

protected:

   chartagger::CWeightBase *m_weights;

   bool m_bTrain ; // the system runs either at training mode or decoding mode



public:
   // constructor and destructor
   CCharTaggerBase( std::string sFeatureDBPath , bool bTrain) : m_bTrain(bTrain)  {
      // do nothing
   }
   virtual ~CCharTaggerBase() {
      // do nothing
   }
   CCharTaggerBase( CCharTaggerBase &depparser) {
      THROW("CCharTagger does not support copy constructor!");
   }




public:

   virtual void parse( const CStringVector &sentence , CDependencyParse *retval , int nBest=1, chartagger::SCORE_TYPE *scores=0 ) = 0 ;
   virtual void train( const CDependencyParse &correct , int round ) = 0 ;

   virtual void finishtraining() = 0 ;  

};

}; // namespace TARGET_LANGUAGE

#endif


