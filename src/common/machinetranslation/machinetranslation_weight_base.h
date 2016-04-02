// Copyright (C) University of Oxford 2010
/***************************************************************
 *                                                             *
 * weight_base.h - the dependency translator weights               *
 *                                                             *
 * Yue Zhang, 2007.10                                          *
 *                                                             *
 ***************************************************************/

#ifndef _MACHINETRANS_WEIGHTS_BASE_H
#define _MACHINETRANS_WEIGHTS_BASE_H

#include "machinetranslation_base_include.h"

namespace TARGET_LANGUAGE {
namespace machinetranslation {

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


public:
   // CONSTRUCTOR 
   CWeightBase(const std::string &sFile, bool bTrain) : m_bTrain(bTrain) , m_sRecordPath(sFile) { }
   virtual ~CWeightBase() { }


   virtual void loadScores() = 0 ;
   virtual void saveScores() = 0 ; 
   virtual void outputScores() = 0 ;

};

};
};

#endif
