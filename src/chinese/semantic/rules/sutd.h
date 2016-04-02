// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * sutd.h - the SUTD semantic style labels *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 ****************************************************************/

#ifndef _SEMANTIC_RUL_SUTD
#define _SEMANTIC_RUL_SUTD

#include "tags.h"
#include "dep.h"

namespace chinese {

/*==============================================================
 *
 * semantic constraints
 *
 *==============================================================*/

inline bool canAssignLabel(const std::vector< CTaggedWord<CTag,TAG_SEPARATOR> > &sent, const int &head, const int &dep, const CDependencyLabel &synlab, const CSemanticLabel &semlab) {

   return true;
}


};

#endif
