// Copyright (C) University of Oxford 2010
#ifndef _GENERAL_MACHINETRANS_MACROS_H
#define _GENERAL_MACHINETRANS_MACROS_H

#define SIMPLE_HASH

// early update? 
#define EARLY_UPDATE

// local training? it will affect the setting of early update and agenda size
// if you want to experiment with local training, define this when you train
// it will automatically set beam1
// but undefine this when you decode with beam more than one
// using the model you trained with this defined
//#define LOCAL_LEARNING

// The size of agenda
#define AGENDA_SIZE 16


typedef double SCORE_TYPE ;
#include "action.h"

// supertag
#define SR_SUPERTAG 1

// force the tree to be single-rooted or allow multiple pseudo roots
//#define FRAGMENTED_TREE

// the implementation supports the extraction of features as a command
#define SUPPORT_FEATURE_EXTRACTION

// The size of a sentence and the words
const unsigned MAX_SENTENCE_SIZE = 128 ;
const unsigned MAX_ACTION_SIZE = MAX_SENTENCE_SIZE*2;
const unsigned MAX_SENTENCE_SIZE_BITS = 8 ; 

const SCORE_TYPE LOWEAST_LOG_PROB = -10;
const SCORE_TYPE TGT_LM_NORMALIZE = 50;
const SCORE_TYPE OSM_LM_NORMALIZE = 100;
const int MAX_NULL_ALIGN_NUMBER = 8;



#ifdef LOCAL_LEARNING
#define EARLY_UPDATE
#define AGENDA_SIZE 1
#endif

#endif
