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

const std::string PENN_DEP_STRINGS[] = {
   "-NONE-",
   "ROOT", 
   "ACT", "ADV", "APP",
   "ATT", "CMP", "COO",
   "COS", "DE", "DEI",
   "DI", "IC", "IOB",
   "IS", "ISC", "LAD",
   "MT", "NUM", "POB",
   "PUN", "PUS", "QUC",
   "QUN", "RAD", "RADC",
   "RED", "SBV", "TPC",
   "VOB", "VV",
};

enum PENN_DEP_LABELS {
   PENN_DEP_NONE=0,
   PENN_DEP_ROOT, 
   SUTD_SYN_LAB_ACT, SUTD_SYN_LAB_ADV, SUTD_SYN_LAB_APP,
   SUTD_SYN_LAB_ATT, SUTD_SYN_LAB_CMP, SUTD_SYN_LAB_COO,
   SUTD_SYN_LAB_COS, SUTD_SYN_LAB_DE, SUTD_SYN_LAB_DEI,
   SUTD_SYN_LAB_DI, SUTD_SYN_LAB_IC, SUTD_SYN_LAB_IOB,
   SUTD_SYN_LAB_IS, SUTD_SYN_LAB_ISC, SUTD_SYN_LAB_LAD,
   SUTD_SYN_LAB_MT, SUTD_SYN_LAB_NUM, SUTD_SYN_LAB_POB,
   SUTD_SYN_LAB_PUN, SUTD_SYN_LAB_PUS, SUTD_SYN_LAB_QUC,
   SUTD_SYN_LAB_QUN, SUTD_SYN_LAB_RAD, SUTD_SYN_LAB_RADC,
   SUTD_SYN_LAB_RED, SUTD_SYN_LAB_SBV, SUTD_SYN_LAB_TPC,
   SUTD_SYN_LAB_VOB, SUTD_SYN_LAB_VV,
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
