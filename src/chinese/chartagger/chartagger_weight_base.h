// Copyright (C) University of Oxford 2010
/***************************************************************
 *                                                             *
 * weight_base.h - the dependency parser weights               *
 *                                                             *
 * Yue Zhang, 2007.10                                          *
 *                                                             *
 ***************************************************************/

#ifndef _CHARTAGGER_WEIGHTS_BASE_H
#define _CHARTAGGER_WEIGHTS_BASE_H

#include "chartagger_base_include.h"

namespace TARGET_LANGUAGE {
namespace chartagger {

/*===============================================================
 *
 * CWeightBase - the definition of weights, in feature
 *
 *==============================================================*/

class CWeightBase {

public:
   bool m_bTrain;
   bool m_bModified;
   std::string m_sFeatureDB;

public:

   CWeightBase(const std::string &sFeatureDB, bool bTrain) : m_sFeatureDB(sFeatureDB), m_bTrain(bTrain) { }
   CWeightBase(const CWeightBase &weightbase) { THROW("CWeightBase cannot be copied by constructor"); }
   virtual ~CWeightBase() { }

   virtual void loadScores() = 0 ;
   virtual void saveScores() = 0 ;

};

};
};

#endif
