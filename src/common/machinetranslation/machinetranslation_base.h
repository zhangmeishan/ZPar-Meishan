// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * deptranslator_base.h - the definition for the dependency translator. *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.10                        *
 *                                                              *
 ****************************************************************/

#ifndef _MACHINETRANS_BASE_H
#define _MACHINETRANS_BASE_H

#include "machinetranslation_base_include.h"

#include "machinetranslation_weight_base.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CMachineTransBase - the general dependency translator def
 *
 *==============================================================*/

class CMachineTransBase {

protected:

   machinetranslation::CWeightBase *m_weights;

   bool m_bTrain ; // the system runs either at training mode or decoding mode



public:
   // constructor and destructor
   CMachineTransBase( std::string sFeatureDBPath , bool bTrain) : m_bTrain(bTrain)  {
      // do nothing
   }
   virtual ~CMachineTransBase() {
      // do nothing
   }
   CMachineTransBase( CMachineTransBase &deptranslator) { 
      THROW("CMachineTrans does not support copy constructor!"); 
   }

public:



public:

   virtual void translator( const CStringVector &sentence , CAlignedSentencePair *retval , const CSTackFeatsVec & stackfeats, int nBest=1, machinetranslation::SCORE_TYPE *scores=0 ) = 0 ;
   virtual void train( CAlignedSentencePair &correct , const CSTackFeatsVec & stackfeats, int round ) = 0 ;


   virtual void finishtraining() = 0 ;  

};

}; // namespace TARGET_LANGUAGE

#endif


