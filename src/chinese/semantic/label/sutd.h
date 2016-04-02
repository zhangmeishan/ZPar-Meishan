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
namespace chinese {

const std::string PENN_SEM_STRINGS[] = {
   "-NONE-",
   "ROOT",
   "ACT", "BSS", "CAU",
   "COS", "DAT", "DIR",
   "FAKE", "FIN", "INI",
   "INS", "LOC", "MAN",
   "MAT", "MSB", "OBJ",
   "OLO", "OS0", "OSB",
   "POS", "PUR", "QUN",
   "RAN", "SBJ", "SCO",
   "SDA", "SL0", "SLO",
   "SO0", "SOB", "SS0",
   "SSB", "STP", "THR",
   "TIM", "TL0", "TOP",
   "TS0", "TSB", "TT0",
   "TTP", "rBSS", "rCAU",
   "rDAT", "rINI", "rINS",
   "rLOC", "rMAN", "rOBJ",
   "rPOS", "rSBJ", "rSSB",
   "rTHR", "rTIM", "rTOP",
};

enum PENN_SEM_LABELS {
   PENN_SEM_NONE=0,
   PENN_SEM_ROOT,
   PENN_SEM_LAB_ACT, PENN_SEM_LAB_BSS, PENN_SEM_LAB_CAU,
   PENN_SEM_LAB_COS, PENN_SEM_LAB_DAT, PENN_SEM_LAB_DIR,
   PENN_SEM_LAB_FAKE, PENN_SEM_LAB_FIN, PENN_SEM_LAB_INI,
   PENN_SEM_LAB_INS, PENN_SEM_LAB_LOC, PENN_SEM_LAB_MAN,
   PENN_SEM_LAB_MAT, PENN_SEM_LAB_MSB, PENN_SEM_LAB_OBJ,
   PENN_SEM_LAB_OLO, PENN_SEM_LAB_OS0, PENN_SEM_LAB_OSB,
   PENN_SEM_LAB_POS, PENN_SEM_LAB_PUR, PENN_SEM_LAB_QUN,
   PENN_SEM_LAB_RAN, PENN_SEM_LAB_SBJ, PENN_SEM_LAB_SCO,
   PENN_SEM_LAB_SDA, PENN_SEM_LAB_SL0, PENN_SEM_LAB_SLO,
   PENN_SEM_LAB_SO0, PENN_SEM_LAB_SOB, PENN_SEM_LAB_SS0,
   PENN_SEM_LAB_SSB, PENN_SEM_LAB_STP, PENN_SEM_LAB_THR,
   PENN_SEM_LAB_TIM, PENN_SEM_LAB_TL0, PENN_SEM_LAB_TOP,
   PENN_SEM_LAB_TS0, PENN_SEM_LAB_TSB, PENN_SEM_LAB_TT0,
   PENN_SEM_LAB_TTP, PENN_SEM_LAB_RBSS, PENN_SEM_LAB_RCAU,
   PENN_SEM_LAB_RDAT, PENN_SEM_LAB_RINI, PENN_SEM_LAB_RINS,
   PENN_SEM_LAB_RLOC, PENN_SEM_LAB_RMAN, PENN_SEM_LAB_ROBJ,
   PENN_SEM_LAB_RPOS, PENN_SEM_LAB_RSBJ, PENN_SEM_LAB_RSSB,
   PENN_SEM_LAB_RTHR, PENN_SEM_LAB_RTIM, PENN_SEM_LAB_RTOP,
   PENN_SEM_COUNT
};

const unsigned long PENN_SEM_COUNT_BITS = 6;

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
   enum {COUNT=PENN_SEM_COUNT};
   enum {MAX_COUNT=COUNT};
   enum {SIZE=PENN_SEM_COUNT_BITS};

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
      m_code = PENN_SEM_NONE;
      for (int i=FIRST; i<COUNT; ++i) {
         if (PENN_SEM_STRINGS[i]==str) {
            m_code = i;
            return;
         }
      }
   }

   void load(const unsigned long &u) { 
      m_code = u;
   }

   const std::string &str() const { 
      return PENN_SEM_STRINGS[ m_code ];
   }

   const unsigned long &code() const {
      return m_code;
   }

   static bool canDuplicated(int code)
   {
	   if(code == PENN_SEM_LAB_FAKE) return true;
	   else return false;
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
