// Copyright (C) University of Oxford 2010
#define SIMPLE_HASH
#include "definitions.h"
#include "utils.h"
#include "linguistics/word_tokenized.h"
#include "linguistics/aligned_sentence_pair.h"

namespace TARGET_LANGUAGE { 
namespace machinetranslation { 
#include "machinetranslation_macros.h" 
}
}

#include "machinetranslation_impl_inc.h"
#include "options.h"

#include "stackfeats.h"
#include <map>

typedef std::vector< TARGET_LANGUAGE::machinetranslation::CStackFeats > CSTackFeatsVec;


typedef std::vector<std::vector<CWord> >  CTranslateVector;
typedef std::vector<float >  CTranslateScoreVector;
typedef std::vector<int >  CTranslateTypeVector;  // -1, Y->NULL; +1, NULL->X; otherwise 0
typedef CHashMap<std::string, unsigned long > CStringToInt;
typedef CHashMap<std::string, std::map<std::string, float> > CLanguageModelType;
typedef CHashMap<std::string, float > CLanguageModel1Type;
