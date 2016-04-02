// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * stanford.h - the Stanford Dependency style dependency labels *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 ****************************************************************/

#ifndef _DEPENDENCY_L_SANCL
#define _DEPENDENCY_L_SANCL

#include "tags.h"

namespace english {

const std::string SANCL_DEP_STRINGS[] = {
   "-none-",
   "root",
   "cc", 
   "number", 
   "ccomp", 
   "possessive", 
   "prt", 
   "num", 
   "nsubjpass", 
   "csubj", 
   "conj", 
   "amod", 
   "nn", 
   "neg", 
   "csubjpass", 
   "mark", 
   "auxpass", 
   "infmod", 
   "rel", 
   "advcl", 
   "aux", 
   "prep", 
   "parataxis", 
   "nsubj", 
   "rcmod", 
   "advmod", 
   "punct", 
   "quantmod", 
   "tmod", 
   "acomp", 
   "complm", 
   "pcomp", 
   "poss", 
   "xcomp", 
   "cop", 
   "attr", 
   "partmod", 
   "dep", 
   "det", 
   "dobj", 
   "purpcl", 
   "abbrev", 
   "pobj", 
   "iobj", 
   "expl", 
   "predet",
   "npadvmod",
   "mwe",
   "preconj"
};

enum SANCL_DEP_LABELS {
   SANCL_DEP_NONE=0,
   SANCL_DEP_ROOT,
   SANCL_DEP_CC, 
   SANCL_DEP_NUMBER, 
   SANCL_DEP_CCOMP, 
   SANCL_DEP_POSSESSIVE, 
   SANCL_DEP_PRT, 
   SANCL_DEP_NUM, 
   SANCL_DEP_NSUBJPASS, 
   SANCL_DEP_CSUBJ, 
   SANCL_DEP_CONJ, 
   SANCL_DEP_AMOD, 
   SANCL_DEP_NN, 
   SANCL_DEP_NEG, 
   SANCL_DEP_CSUBJPASS, 
   SANCL_DEP_MARK, 
   SANCL_DEP_AUXPASS, 
   SANCL_DEP_INFMOD, 
   SANCL_DEP_REL, 
   SANCL_DEP_ADVCL, 
   SANCL_DEP_AUX, 
   SANCL_DEP_PREP, 
   SANCL_DEP_PARATAXIS, 
   SANCL_DEP_NSUBJ, 
   SANCL_DEP_RCMOD, 
   SANCL_DEP_ADVMOD, 
   SANCL_DEP_PUNCT, 
   SANCL_DEP_QUANTMOD, 
   SANCL_DEP_TMOD, 
   SANCL_DEP_ACOMP, 
   SANCL_DEP_COMPLM, 
   SANCL_DEP_PCOMP, 
   SANCL_DEP_POSS, 
   SANCL_DEP_XCOMP, 
   SANCL_DEP_COP, 
   SANCL_DEP_ATTR, 
   SANCL_DEP_PARTMOD, 
   SANCL_DEP_DEP, 
   SANCL_DEP_DET, 
   SANCL_DEP_DOBJ, 
   SANCL_DEP_PURPCL, 
   SANCL_DEP_ABBREV, 
   SANCL_DEP_POBJ, 
   SANCL_DEP_IOBJ, 
   SANCL_DEP_EXPL, 
   SANCL_DEP_PREDET, 
   SANCL_DEP_PRECONJ,
   SANCL_DEP_NPADVMOD,
   SANCL_DEP_MWE,
   SANCL_DEP_COUNT 
};

const unsigned long SANCL_DEP_COUNT_BITS = 6;

/*==============================================================
 *
 * dependency lab
 *
 *==============================================================*/

class CDependencyLabel {

public:

   enum {NONE=0};
   enum {ROOT=1};
   enum {FIRST=1};
   enum {COUNT=SANCL_DEP_COUNT};
   enum {MAX_COUNT=COUNT};
   enum {SIZE=SANCL_DEP_COUNT_BITS};

protected:

   unsigned long m_code;

public:

   CDependencyLabel() : m_code(NONE) {}
   CDependencyLabel(const unsigned long &code) : m_code(code) { }
   CDependencyLabel(const std::string &str) { load(str); }
   virtual ~CDependencyLabel() {}

public:

   const unsigned long &hash() const { return m_code; }
   bool operator == (const CDependencyLabel &l) const { return m_code == l.m_code; }
   bool operator != (const CDependencyLabel &l) const { return m_code != l.m_code; }
   bool operator < (const CDependencyLabel &l) const { return m_code < l.m_code; }
   bool operator > (const CDependencyLabel &l) const { return m_code > l.m_code; }
   bool operator <= (const CDependencyLabel &l) const { return m_code <= l.m_code; }
   bool operator >= (const CDependencyLabel &l) const { return m_code >= l.m_code; }

   void load(const std::string &str) { 
      m_code = SANCL_DEP_NONE;
      for (int i=FIRST; i<COUNT; ++i) {
         if (SANCL_DEP_STRINGS[i]==str) {
            m_code = i;
            return;
         }
      }
   }

   void load(const unsigned long &u) { 
      m_code = u;
   }

   const std::string &str() const { 
      return SANCL_DEP_STRINGS[ m_code ]; 
   }

   const unsigned long &code() const {
      return m_code;
   }

};

inline std::istream & operator >> (std::istream &is, CDependencyLabel &label) {
   std::string s;
   is >> s;
   label.load(s);
   return is;
}

inline std::ostream & operator << (std::ostream &os, const CDependencyLabel &label) {
   os << label.str() ;
   return os;
}
};

#endif
