
// Copyright (C) University of Oxford 2010
#define SIMPLE_HASH
#include "definitions.h"
#include "utils.h"
#include "tags.h"
#include "linguistics/word_tokenized.h"
#include "linguistics/taggedword.h"
#include "linguistics/chardependency.h"
#include "knowledge/tagdict.h"

typedef CCharDependencyTree CDependencyParse;

namespace TARGET_LANGUAGE { 
namespace chartagger {
#include "implementations/agenda/chartagger_macros.h" 
}
#include "wordcache.h"
}

#include "implementations/agenda/chartagger_impl_inc.h"
#include "linguistics/tagset.h"
#include "options.h"

#include "stackfeats.h"

typedef std::vector< TARGET_LANGUAGE::chartagger::CStackFeats > CSTackFeatsVec;
