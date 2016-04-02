// Copyright (C) University of Oxford 2010
#ifndef _MACHINETRANS_IMPL_INCLUDE_H
#define _MACHINETRANS_IMPL_INCLUDE_H

#include "agenda.h"
#include "pair_stream.h"
#include "vector_stream.h"

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

typedef std::vector<std::vector<CWord> >  CTranslateVector;
typedef std::vector<float >  CTranslateScoreVector;
typedef std::vector<int >  CTranslateTypeVector;  // -1, Y->NULL; +1, NULL->X; otherwise 0
typedef CHashMap<std::string, unsigned long > CStringToInt;

#endif
