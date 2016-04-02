// Copyright (C) University of Oxford 2010
#ifndef _ENGLISH_DEPLABEL_H
#define _ENGLISH_DEPLABEL_H

#ifdef LABELED
//#ifdef STANFORD_DEPENDENCIES
//#include "dependency/label/stanford.h"
//#else
//#ifdef MULTI_SCHEMA
//#include "dependency/label/multilabel.h"
//#else
#include "dependency/label/sancl.h"
//#endif
//#endif
#endif

//#ifdef STANFORD_DEPENDENCIES
//#include "dependency/rules/stanford.h"
//#elseif MULTI_SCHEMA
//#include "dependency/rules/stanford.h"
//#else
#include "dependency/rules/stanford.h"
//#endif

#endif
