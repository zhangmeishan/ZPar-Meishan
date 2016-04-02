// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * sutd.h - the SUTD semantic style labels *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 ****************************************************************/

#ifndef _SEMANTIC_L_SUTD
#define _SEMANTIC_L_SUTD

#include "tags.h"

namespace english {

const std::string SUTD_DEP_STRINGS[] = {
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

enum SUTD_DEP_LABELS {
   SUTD_DEP_NONE=0,
   SUTD_DEP_ROOT,
   SUTD_DEP_CC,
   SUTD_DEP_NUMBER,
   SUTD_DEP_CCOMP,
   SUTD_DEP_POSSESSIVE,
   SUTD_DEP_PRT,
   SUTD_DEP_NUM,
   SUTD_DEP_NSUBJPASS,
   SUTD_DEP_CSUBJ,
   SUTD_DEP_MEASURE,
   SUTD_DEP_CONJ,
   SUTD_DEP_AMOD,
   SUTD_DEP_PRED,
   SUTD_DEP_NN,
   SUTD_DEP_NEG,
   SUTD_DEP_CSUBJPASS,
   SUTD_DEP_MARK,
   SUTD_DEP_AUXPASS,
   SUTD_DEP_INFMOD,
   SUTD_DEP_REL,
   SUTD_DEP_ADVCL,
   SUTD_DEP_AUX,
   SUTD_DEP_PREP,
   SUTD_DEP_PARATAXIS,
   SUTD_DEP_NSUBJ,
   SUTD_DEP_RCMOD,
   SUTD_DEP_ADVMOD,
   SUTD_DEP_PUNCT,
   SUTD_DEP_QUANTMOD,
   SUTD_DEP_TMOD,
   SUTD_DEP_ACOMP,
   SUTD_DEP_COMPLM,
   SUTD_DEP_PCOMP,
   SUTD_DEP_POSS,
   SUTD_DEP_XCOMP,
   SUTD_DEP_COP,
   SUTD_DEP_ATTR,
   SUTD_DEP_PARTMOD,
   SUTD_DEP_DEP,
   SUTD_DEP_APPOS,
   SUTD_DEP_DET,
   SUTD_DEP_DOBJ,
   SUTD_DEP_PURPCL,
   SUTD_DEP_ABBREV,
   SUTD_DEP_POBJ,
   SUTD_DEP_IOBJ,
   SUTD_DEP_EXPL,
   SUTD_DEP_PREDET,
   SUTD_DEP_PRECONJ,
   SUTD_DEP_NPADVMOD,
   SUTD_DEP_MWE,
   SUTD_DEP_COUNT
};

const unsigned long SUTD_DEP_COUNT_BITS = 6;

/*==============================================================
 *
 * semantic lab
 *
 *==============================================================*/

class CSemanticLabel {

public:

   enum {NONE=0};
   enum {ROOT=1};
   enum {FIRST=1};
   enum {COUNT=SUTD_DEP_COUNT};
   enum {MAX_COUNT=COUNT};
   enum {SIZE=SUTD_DEP_COUNT_BITS};

protected:

   unsigned long m_code;

public:

   CSemanticLabel() : m_code(NONE) {}
   CSemanticLabel(const unsigned long &code) : m_code(code) { }
   CSemanticLabel(const std::string &str) { load(str); }
   virtual ~CSemanticLabel() {}

public:

   const unsigned long &hash() const { return m_code; }
   bool operator == (const CSemanticLabel &l) const { return m_code == l.m_code; }
   bool operator != (const CSemanticLabel &l) const { return m_code != l.m_code; }
   bool operator < (const CSemanticLabel &l) const { return m_code < l.m_code; }
   bool operator > (const CSemanticLabel &l) const { return m_code > l.m_code; }
   bool operator <= (const CSemanticLabel &l) const { return m_code <= l.m_code; }
   bool operator >= (const CSemanticLabel &l) const { return m_code >= l.m_code; }

   void load(const std::string &str) { 
      m_code = SUTD_DEP_NONE;
      for (int i=FIRST; i<COUNT; ++i) {
         if (SUTD_DEP_STRINGS[i]==str) {
            m_code = i;
            return;
         }
      }
   }

   void load(const unsigned long &u) { 
      m_code = u;
   }

   const std::string &str() const { 
      return SUTD_DEP_STRINGS[ m_code ];
   }

   const unsigned long &code() const {
      return m_code;
   }

};

inline std::istream & operator >> (std::istream &is, CSemanticLabel &label) {
   std::string s;
   is >> s;
   label.load(s);
   return is;
}

inline std::ostream & operator << (std::ostream &os, const CSemanticLabel &label) {
   os << label.str() ;
   return os;
}
};

#endif
