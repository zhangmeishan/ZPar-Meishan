// Copyright (C) University of Oxford 2010
#ifndef _DISCOURSE_IMPL_INCLUDE_H
#define _DISCOURSE_IMPL_INCLUDE_H

#define SIMPLE_HASH

namespace TARGET_LANGUAGE {
#include "linguistics/cfgtemp.h"
typedef CTemporary<CConstituentLabel> CConstituent;
typedef CTemporary<CDisConstituentLabel> CDisConstituent;
};

#include "hash.h"
#include "bigram.h"
#include "tuple2.h"
#include "tuple3.h"
#include "tuple4.h"
#include "vector_stream.h"
#include "linguistics/word_tokenized.h"
#include "linguistics/taggedword.h"
#include "agenda.h"
#include "pair_stream.h"
#include "knowledge/tagdict.h"

#include "learning/perceptron/score.h"
#include "learning/perceptron/hashmap_score.h"

//#define CScoreMapType CPackedScoreMap

typedef CBigram< CTaggedWord<TARGET_LANGUAGE::CTag, TARGET_LANGUAGE::TAG_SEPARATOR> > CTwoTaggedWords; 

typedef TARGET_LANGUAGE::CDISTree CSentenceParsed;

#include "labeledbracket.h"
#include "labeleddisbracket.h"
#include "stack.h"

namespace TARGET_LANGUAGE { 

#include "linguistics/discfgset.h"

namespace discourse { 

typedef double SCORE_TYPE ;

// labeled brackets
typedef CTuple3<int, int, CDisConstituent> CDisBracketTuple;
typedef CHashMap<CDisBracketTuple, unsigned> CDisBracketTupleMap;

typedef CTuple3<int, int, CConstituent> CBracketTuple;
typedef CHashMap<CBracketTuple, unsigned> CBracketTupleMap;

#include "stateitem.h" 
#include "context.h"

}

}

#include "rule.h"

#endif
