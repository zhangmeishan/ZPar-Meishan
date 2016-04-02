// Copyright (C) SUTD 2015
/***************************************************************
 *                                                             *
 * weight_base.h - the dependency parser weights               *
 *                                                             *
 * Meishan Zhang, 2015.01                                          *
 *                                                             *
 ***************************************************************/

#ifndef _DEPSEM_WEIGHTS_BASE_H
#define _DEPSEM_WEIGHTS_BASE_H

#include "depsem_base_include.h"

namespace TARGET_LANGUAGE {
namespace depsem {

/*===============================================================
 *
 * CWeightBase - the definition of weights
 *
 *==============================================================*/

class CWeightBase {

protected:
   bool m_bTrain;
   bool m_bModified;
   std::string m_sRecordPath;

   bool m_bRules;

public:
   // CONSTRUCTOR 
   CWeightBase(const std::string &sFile, bool bTrain) : m_bTrain(bTrain) , m_sRecordPath(sFile) , m_bRules(false) { }
   virtual ~CWeightBase() { }

   void setRules(const bool &bRules) {
      TRACE("Rules set to " << (bRules ? "true" : "false"));
      m_bRules = bRules;
   }
   bool rules() const {
      return m_bRules;
   }

   virtual void loadScores() = 0 ;
   virtual void saveScores() = 0 ; 

};

};
};

#endif
