 #****************************************************************
#
# Makefile
#
# Yue Zhang
# Computing lab, Oxford. 2006.10 - 2008.2
#
#****************************************************************

# Makable targe systems include:
#
# === Chinese ===
# segmentor - Chinese word segmentor
# chinese.postagger - Chinese POS tagger (joint / single)
# chinese.depparser - Chinese dependency parser
#
# === English ===
# english.postagger - English POS tagger
# english.depparser - English dependency parser

#================================================================
#
# Configurations
#
#================================================================

# choose between agenda, agendachart etc ## NO SPACE AFTER NAME ###
#
# agenda: the single agenda method - reproduce paper
# agendaplus: try to improve upon the decoding algorithm of agenda
# viterbi: dynamic programming
SEGMENTOR_IMPL = agenda

# Chinese postagger implementations
#
# joint taggers include the following implementations
# agendachart: combining agenda and chart, this is the best system - reproduce paper
# 
# taggers on segmented sentences include the following implementations
# segmented: the unidirectional trigram tagger
CHINESE_TAGGER_IMPL = agendalexicon
CHINESE_CHARTAGGER_IMPL = agenda
CHINESE_STTAGGER_IMPL = stagenda

# Chinese dependency parser
#
# currently support eisner, covington, nivre, combined and joint implementations 
CHINESE_DEPPARSER_IMPL = arcstandard
CHINESE_DEPPARSER_LABELED = true
CHINESE_DEPLABELER_IMPL = naive

# currently support arceager implementations 
CHINESE_DEPSEM_IMPL = arceager
CHINESE_DEPSEM_LABELED = true

# currently support eisner, covington, nivre, combined and joint implementations 
CHINESE_POSDEPPARSER_IMPL = arcstandard
CHINESE_POSDEPPARSER_LABELED = true
CHINESE_POSDEPLABELER_IMPL = naive
CHINESE_PROCESS_MANNER = charbase

# currently support sr implementations 
CHINESE_CONPARSER_IMPL = cad

# currently support only agenda
ENGLISH_TAGGER_IMPL = sancl

# currently support eisner, covington, nivre, combined implementations 
ENGLISH_DEPPARSER_IMPL =arcstandard
ENGLISH_DEPPARSER_LABELED = true
ENGLISH_DEPLABELER_IMPL = naive

# currently support arceager implementations 
ENGLISH_DEPSEM_IMPL =arceager
ENGLISH_DEPSEM_LABELED = true


# currently support eisner, covington, nivre, combined implementations 
ENGLISH_POSDEPPARSER_IMPL = arcstandard
ENGLISH_POSDEPPARSER_LABELED = true
ENGLISH_POSDEPLABELER_IMPL = naive

# currently support sr implementations 
ENGLISH_CONPARSER_IMPL = cad

# currently support sr implementations 
ENGLISH_DISCOURSE_IMPL = mira


# currently support eisner, covington, nivre, combined implementations 
ENGLISH_MACHINETRANSLATOR_IMPL = TSOSM


#================================================================
#
# Debug mode or the run mode (empty)
#
#================================================================

#DEBUG = -DDEBUG -g -O0
DEBUG = -DNDEBUG -O3

#================================================================
#
# directory configurations
#
#================================================================

BASE_DIR = .
include Makefile.common

#================================================================
#
# compiler commands
# 
#================================================================

INCLUDES = -I$(SRC_INCLUDES)

CXX = g++
CXXFLAGS = -w -W  $(INCLUDES) $(DEBUG)

LD=$(CXX)
LDFLAGS =

#================================================================
#
# Shared objects
#
#================================================================

# the objects
LINGUISTICS_OBJECTS = $(OBJECT_DIR)/linguistics/lemma.o $(OBJECT_DIR)/linguistics/conll.o
OBJECTS = $(OBJECT_DIR)/reader.o $(OBJECT_DIR)/writer.o $(OBJECT_DIR)/options.o $(LINGUISTICS_OBJECTS)

$(OBJECT_DIR)/%.o: $(SRC_LIBS)/%.cpp $(SRC_INCLUDES)/%.h
	mkdir -p $(OBJECT_DIR)
	mkdir -p $(OBJECT_DIR)/linguistics
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: zpar

# the directories
$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)
$(DIST_DIR):
	mkdir -p $(DIST_DIR)

#  tagger
SRC_TAGGER = $(SRC_CHINESE)/tagger
DIST_TAGGER = $(DIST_DIR)/chinese.postagger
OBJECT_TAGGER = $(OBJECT_DIR)/chinese.postagger
$(DIST_TAGGER):
	mkdir $(DIST_TAGGER)
$(OBJECT_TAGGER):
	mkdir $(OBJECT_TAGGER)
	

#add by zms, forget its purpose now
#  sttagger
SRC_STTAGGER = $(SRC_CHINESE)/sttagger
DIST_STTAGGER = $(DIST_DIR)/chinese.stpostagger
OBJECT_STTAGGER = $(OBJECT_DIR)/chinese.stpostagger
$(DIST_STTAGGER):
	mkdir $(DIST_STTAGGER)
$(OBJECT_STTAGGER):
	mkdir $(OBJECT_STTAGGER)


#add by zms, forget its purpose now
#  chartagger
SRC_CHARTAGGER = $(SRC_CHINESE)/chartagger
DIST_CHARTAGGER = $(DIST_DIR)/chinese.chartagger
OBJECT_CHARTAGGER = $(OBJECT_DIR)/chinese.chartagger
$(DIST_CHARTAGGER):
	mkdir $(DIST_CHARTAGGER)
$(OBJECT_CHARTAGGER):
	mkdir $(OBJECT_CHARTAGGER)
	
	
SRC_ENGLISH_TAGGER = $(SRC_COMMON)/tagger
DIST_ENGLISH_TAGGER = $(DIST_DIR)/english.postagger
OBJECT_ENGLISH_TAGGER = $(OBJECT_DIR)/english.postagger
$(DIST_ENGLISH_TAGGER):
	mkdir $(DIST_ENGLISH_TAGGER)
$(OBJECT_ENGLISH_TAGGER):
	mkdir $(OBJECT_ENGLISH_TAGGER)

#  depparser
SRC_COMMON_DEPPARSER = $(SRC_COMMON)/depparser
SRC_CHINESE_DEPPARSER = $(SRC_COMMON_DEPPARSER)
DIST_DEPPARSER = $(DIST_DIR)/chinese.depparser
OBJECT_DEPPARSER = $(OBJECT_DIR)/chinese.depparser
DIST_ENGLISH_DEPPARSER = $(DIST_DIR)/english.depparser
OBJECT_ENGLISH_DEPPARSER = $(OBJECT_DIR)/english.depparser

#  depsem
SRC_COMMON_DEPSEM = $(SRC_COMMON)/depsem
DIST_DEPSEM = $(DIST_DIR)/chinese.depsem
OBJECT_DEPSEM = $(OBJECT_DIR)/chinese.depsem
DIST_ENGLISH_DEPSEM = $(DIST_DIR)/english.depsem
OBJECT_ENGLISH_DEPSEM = $(OBJECT_DIR)/english.depsem


#  posdepparser
SRC_COMMON_POSDEPPARSER = $(SRC_COMMON)/posdepparser
ifeq ($(CHINESE_PROCESS_MANNER), charbase)
	SRC_CHINESE_POSDEPPARSER = $(SRC_CHINESE)/posdepparser
else	
	SRC_CHINESE_POSDEPPARSER = $(SRC_COMMON_POSDEPPARSER)
endif
DIST_POSDEPPARSER = $(DIST_DIR)/chinese.posdepparser
OBJECT_POSDEPPARSER = $(OBJECT_DIR)/chinese.posdepparser
DIST_ENGLISH_POSDEPPARSER = $(DIST_DIR)/english.posdepparser
OBJECT_ENGLISH_POSDEPPARSER = $(OBJECT_DIR)/english.posdepparser


#  machinetranslation
SRC_COMMON_MACHINETRANSLATOR = $(SRC_COMMON)/machinetranslation
DIST_ENGLISH_MACHINETRANSLATOR = $(DIST_DIR)/english.machinetranslator
OBJECT_ENGLISH_MACHINETRANSLATOR = $(OBJECT_DIR)/english.machinetranslator

# deplabeler
SRC_COMMON_DEPLABELER = $(SRC_COMMON)/deplabeler
SRC_CHINESE_DEPLABELER = $(SRC_COMMON_DEPLABELER)
DIST_DEPLABELER = $(DIST_DIR)/chinese.deplabeler
OBJECT_DEPLABELER = $(OBJECT_DIR)/chinese.deplabeler
SRC_ENGLISH_DEPLABELER = $(SRC_COMMON_DEPLABELER)
DIST_ENGLISH_DEPLABELER = $(DIST_DIR)/english.deplabeler
OBJECT_ENGLISH_DEPLABELER = $(OBJECT_DIR)/english.deplabeler

#  conparser
SRC_COMMON_CONPARSER = $(SRC_COMMON)/conparser
ifeq ($(CHINESE_PROCESS_MANNER), charbase)
	SRC_CHINESE_CONPARSER = $(SRC_CHINESE)/conparser
else 
	SRC_CHINESE_CONPARSER = $(SRC_COMMON_CONPARSER)
endif

SRC_ENGLISH_CONPARSER = $(SRC_COMMON_CONPARSER)
DIST_CONPARSER = $(DIST_DIR)/chinese.conparser
OBJECT_CONPARSER = $(OBJECT_DIR)/chinese.conparser
DIST_ENGLISH_CONPARSER = $(DIST_DIR)/english.conparser
OBJECT_ENGLISH_CONPARSER = $(OBJECT_DIR)/english.conparser


#  discourse
SRC_COMMON_DISCOURSE = $(SRC_COMMON)/discourse
SRC_ENGLISH_DISCOURSE = $(SRC_COMMON_DISCOURSE)
DIST_ENGLISH_DISCOURSE = $(DIST_DIR)/english.discourse
OBJECT_ENGLISH_DISCOURSE = $(OBJECT_DIR)/english.discourse

#----------------------------------------------------------------
#
# zpar general
#
#----------------------------------------------------------------

include Makefile.zpar
include Makefile.zpar.en
include Makefile.zpar.ge

#----------------------------------------------------------------
#
# The sentence boundary detector
#
#----------------------------------------------------------------

include Makefile.doc2snt

#----------------------------------------------------------------
#
# The segmentor
#
#----------------------------------------------------------------

include Makefile.segmentor

#----------------------------------------------------------------
#
# The pos taggers (Chinese and English)
#
#----------------------------------------------------------------

include Makefile.postagger
include Makefile.stpostagger
include Makefile.chartagger

#----------------------------------------------------------------
#
# The depparsers (Chinese and English)
#
#----------------------------------------------------------------

include Makefile.depparser
include Makefile.depsem
include Makefile.deplabeler

include Makefile.posdepparser

include Makefile.machinetranslation

#----------------------------------------------------------------
#
# The conparser
#
#----------------------------------------------------------------

include Makefile.conparser

#----------------------------------------------------------------
#
# The discourse
#
#----------------------------------------------------------------

include Makefile.discourse

#----------------------------------------------------------------
#
# The ccgparser
#
#----------------------------------------------------------------

include Makefile.ccg

#----------------------------------------------------------------
#
# Miscelaneous
#
#----------------------------------------------------------------

include Makefile.misc
#include Makefile.rr

