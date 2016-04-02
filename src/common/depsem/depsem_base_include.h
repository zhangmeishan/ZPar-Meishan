// Copyright (C) SUTD 2015
#define SIMPLE_HASH
#include "definitions.h"
#include "utils.h"
#include "linguistics/word_tokenized.h"
#include "linguistics/taggedword.h"
#include "linguistics/dependency.h"
#include "linguistics/semanticdependency.h"


namespace TARGET_LANGUAGE { 
namespace depsem { 
#include "depsem_macros.h" 
}
}

#include "tags.h"
#include "dep.h"
#include "sem.h"
#include "depsem_impl_inc.h"

typedef CSemanticDependencyTree CDependencyParse;

#include "linguistics/conll.h"
#include "linguistics/tagset.h"
#include "options.h"

#include "stackfeats.h"

typedef std::vector< TARGET_LANGUAGE::depsem::CStackFeats > CSTackFeatsVec;
