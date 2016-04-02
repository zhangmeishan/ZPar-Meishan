// Copyright (C) SUTD 2015
#ifndef _DEPSEM_IMPL_INCLUDE_H
#define _DEPSEM_IMPL_INCLUDE_H

#include "agenda.h"
#include "pair_stream.h"

#include "learning/perceptron/score.h"
#include "learning/perceptron/hashmap_score.h"

#include "bigram.h"
#include "tuple2.h"
#include "tuple3.h"
#include "tuple4.h"

#include "linguistics/lemma.h"

#ifdef PUNCT
#include "charcat.h"
#endif

namespace TARGET_LANGUAGE {
namespace depsem {
const unsigned long DEP_LABEL_COUNT=CDependencyLabel::MAX_COUNT-1; // not count NONE
const unsigned long SEM_LABEL_COUNT=CSemanticLabel::MAX_COUNT-1; // not count NONE
const unsigned long MAX_LABEL_COUNT=DEP_LABEL_COUNT*SEM_LABEL_COUNT;

#include "action.h"
}
}

typedef CBigram< CTaggedWord<TARGET_LANGUAGE::CTag, TARGET_LANGUAGE::TAG_SEPARATOR> > CTwoTaggedWords; 




#endif
