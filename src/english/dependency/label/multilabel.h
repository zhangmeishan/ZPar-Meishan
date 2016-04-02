// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * penn.h - the penn treebank style dependency labels           *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2008.07                        *
 *                                                              *
 ****************************************************************/

#ifndef _DEPENDENCY_L_PENN
#define _DEPENDENCY_L_PENN

#include "tags.h"

namespace english {

const std::string PENN_DEP_STRINGS[] = {
   "-NONE-",
   "ROOT", 
   "AMOD",
   "DEP", 
   "NMOD", 
   "OBJ", 
   "P",
   "PMOD", 
   "PRD",
   "SBAR",
   "SUB",
   "VC",
   "VMOD",
   "root",
   "cc",
   "number",
   "ccomp",
   "possessive",
   "prt",
   "num",
   "nsubjpass",
   "csubj",
   "measure",
   "conj",
   "amod",
   "pred",
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
   "appos",
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

enum PENN_DEP_LABELS {
   PENN_DEP_NONE=0,
   PENN_DEP_ROOT, 
   PENN_DEP_AMOD, 
   PENN_DEP_DEP, 
   PENN_DEP_NMOD, 
   PENN_DEP_OBJ, 
   PENN_DEP_P, 
   PENN_DEP_PMOD, 
   PENN_DEP_PRD, 
   PENN_DEP_SBAR, 
   PENN_DEP_SUB, 
   PENN_DEP_VC, 
   PENN_DEP_VMOD, 
   STANFORD_DEP_ROOT,
   STANFORD_DEP_CC,
   STANFORD_DEP_NUMBER,
   STANFORD_DEP_CCOMP,
   STANFORD_DEP_POSSESSIVE,
   STANFORD_DEP_PRT,
   STANFORD_DEP_NUM,
   STANFORD_DEP_NSUBJPASS,
   STANFORD_DEP_CSUBJ,
   STANFORD_DEP_MEASURE,
   STANFORD_DEP_CONJ,
   STANFORD_DEP_AMOD,
   STANFORD_DEP_PRED,
   STANFORD_DEP_NN,
   STANFORD_DEP_NEG,
   STANFORD_DEP_CSUBJPASS,
   STANFORD_DEP_MARK,
   STANFORD_DEP_AUXPASS,
   STANFORD_DEP_INFMOD,
   STANFORD_DEP_REL,
   STANFORD_DEP_ADVCL,
   STANFORD_DEP_AUX,
   STANFORD_DEP_PREP,
   STANFORD_DEP_PARATAXIS,
   STANFORD_DEP_NSUBJ,
   STANFORD_DEP_RCMOD,
   STANFORD_DEP_ADVMOD,
   STANFORD_DEP_PUNCT,
   STANFORD_DEP_QUANTMOD,
   STANFORD_DEP_TMOD,
   STANFORD_DEP_ACOMP,
   STANFORD_DEP_COMPLM,
   STANFORD_DEP_PCOMP,
   STANFORD_DEP_POSS,
   STANFORD_DEP_XCOMP,
   STANFORD_DEP_COP,
   STANFORD_DEP_ATTR,
   STANFORD_DEP_PARTMOD,
   STANFORD_DEP_DEP,
   STANFORD_DEP_APPOS,
   STANFORD_DEP_DET,
   STANFORD_DEP_DOBJ,
   STANFORD_DEP_PURPCL,
   STANFORD_DEP_ABBREV,
   STANFORD_DEP_POBJ,
   STANFORD_DEP_IOBJ,
   STANFORD_DEP_EXPL,
   STANFORD_DEP_PREDET,
   STANFORD_DEP_PRECONJ,
   STANFORD_DEP_NPADVMOD,
   STANFORD_DEP_MWE,
   PENN_DEP_COUNT 
};

const unsigned long PENN_DEP_COUNT_BITS = 7;

/*==============================================================
 *
 * dependency lab
 *
 *==============================================================*/

class CDependencyLabel {

public:

   enum {NONE=0};
   enum {ROOT0=PENN_DEP_ROOT};
   enum {ROOT1=STANFORD_DEP_ROOT};
   enum {FIRST=1};
   enum {COUNT=PENN_DEP_COUNT};
   enum {MAX_COUNT=COUNT};
   enum {SIZE=PENN_DEP_COUNT_BITS};

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
      m_code = PENN_DEP_NONE;
      for (int i=FIRST; i<COUNT; ++i) {
         if (PENN_DEP_STRINGS[i]==str) {
            m_code = i;
            return;
         }
      }
   }

   void load(const unsigned long &u) { 
      m_code = u;
   }

   const std::string &str() const { 
      return PENN_DEP_STRINGS[ m_code ]; 
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
