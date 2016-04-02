// Copyright (C) University of Oxford 2010
#ifndef _CHARTAGGER_IMPL_INCLUDE_H
#define _CHARTAGGER_IMPL_INCLUDE_H

#include "agenda.h"
#include "pair_stream.h"

#include "learning/perceptron/score.h"
#include "learning/perceptron/hashmap_score.h"

#include "bigram.h"
#include "tuple2.h"
#include "tuple3.h"
#include "tuple4.h"

#include "linguistics/lemma.h"

#include "charcat.h"

typedef CBigram< CTaggedWord<TARGET_LANGUAGE::CTag, TARGET_LANGUAGE::TAG_SEPARATOR> > CTwoTaggedWords; 





#endif
