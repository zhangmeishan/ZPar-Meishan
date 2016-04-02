// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              * 
* xxxx.h - the penn treebank style dependency labels           * 
*                                                              * 
* Author: xxx  xxxx                                            * 
 *                                                              * 
* Computing Laboratory, Oxford. 2008.07                        * 
 *                                                              * 
 ****************************************************************/
const std::string PENN_DEP_STRINGS[] = {
   "-NONE-",
   "root",
   "advmod",
   "amod",
   "asp",
   "assm",
   "assmod",
   "attr",
   "ba",
   "cc",
   "ccomp",
   "clf",
   "comod",
   "conj",
   "cop",
   "cpm",
   "dep",
   "det",
   "dobj",
   "dvpm",
   "dvpmod",
   "etc",
   "lccomp",
   "lobj",
   "loc",
   "mmod",
   "neg",
   "nn",
   "nsubj",
   "nsubjpass",
   "nummod",
   "ordmod",
   "pass",
   "pccomp",
   "plmod",
   "pobj",
   "prep",
   "prnmod",
   "prtmod",
   "punct",
   "range",
   "rcmod",
   "rcomp",
   "tmod",
   "top",
   "vmod",
   "xsubj",
};


enum PENN_DEP_LABELS {
   PENN_DEP_NONE=0,
   PENN_DEP_root,
   PENN_DEP_advmod,
   PENN_DEP_amod,
   PENN_DEP_asp,
   PENN_DEP_assm,
   PENN_DEP_assmod,
   PENN_DEP_attr,
   PENN_DEP_ba,
   PENN_DEP_cc,
   PENN_DEP_ccomp,
   PENN_DEP_clf,
   PENN_DEP_comod,
   PENN_DEP_conj,
   PENN_DEP_cop,
   PENN_DEP_cpm,
   PENN_DEP_dep,
   PENN_DEP_det,
   PENN_DEP_dobj,
   PENN_DEP_dvpm,
   PENN_DEP_dvpmod,
   PENN_DEP_etc,
   PENN_DEP_lccomp,
   PENN_DEP_lobj,
   PENN_DEP_loc,
   PENN_DEP_mmod,
   PENN_DEP_neg,
   PENN_DEP_nn,
   PENN_DEP_nsubj,
   PENN_DEP_nsubjpass,
   PENN_DEP_nummod,
   PENN_DEP_ordmod,
   PENN_DEP_pass,
   PENN_DEP_pccomp,
   PENN_DEP_plmod,
   PENN_DEP_pobj,
   PENN_DEP_prep,
   PENN_DEP_prnmod,
   PENN_DEP_prtmod,
   PENN_DEP_punct,
   PENN_DEP_range,
   PENN_DEP_rcmod,
   PENN_DEP_rcomp,
   PENN_DEP_tmod,
   PENN_DEP_top,
   PENN_DEP_vmod,
   PENN_DEP_xsubj,
   PENN_DEP_COUNT
};


const unsigned long PENN_DEP_COUNT_BITS = 6;

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

