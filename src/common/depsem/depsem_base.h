// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * depsem_base.h - the definition for the dependency parser. *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 * 2015.01                       *
 *                                                              *
 ****************************************************************/

#ifndef _DEPSEM_BASE_H
#define _DEPSEM_BASE_H

#include "depsem_base_include.h"

#include "depsem_weight_base.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CDepParserBase - the general dependency parser def
 *
 *==============================================================*/

class CDepParserBase {

protected:

   depsem::CWeightBase *m_weights;

   bool m_bTrain ; // the system runs either at training mode or decoding mode



public:
   // constructor and destructor
   CDepParserBase( std::string sFeatureDBPath , bool bTrain ) : m_bTrain(bTrain) {
      // do nothing
   }
   virtual ~CDepParserBase() {
      // do nothing
   }
   CDepParserBase( CDepParserBase &depsem) { 
      THROW("CDepParser does not support copy constructor!"); 
   }

public:
   void setRules(const bool &bRules) {
      m_weights->setRules(bRules);
   }

public:

   virtual void parse( const CDependencyParse &input, const CSTackFeatsVec &stackfeats , CDependencyParse *retval , int nBest=1, depsem::SCORE_TYPE *scores=0 ) = 0 ;

   virtual void train( const CDependencyParse &correct, const CSTackFeatsVec &stackfeats , int round ) = 0 ;

   virtual void finishtraining() = 0 ;  

};

}; // namespace TARGET_LANGUAGE

#endif


