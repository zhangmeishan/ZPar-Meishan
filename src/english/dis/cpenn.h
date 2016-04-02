// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * penn.h - the definitions for english cfg                     *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2006.10                        *
 *                                                              *
 ****************************************************************/

namespace english {

// the penn constituent set
const std::string PENN_DIS_STRINGS[] = {
   "-NONE-",
   "-BEGIN-",
   "elab#l", "attr#r", "list#c", "same#c", "attr#l",
   "evid#l", "eval#l", "purp#l", "back#l", "cause#l",
   "cont#r", "cont#c", "back#r", "temp#c", "cont#l",
   "summ#l", "mann#l", "topic#c", "temp#l",
   "cond#l", "cond#r", "comp#l", "text#c", "cause#r",
   "comp#c", "prob#c", "cause#c", "eval#r",
   "temp#r", "evid#r", "purp#r", "prob#l", "comp#r",
   "elab#r", "mann#r", "prob#r", "summ#r", "cond#c",
   "eval#c", "evid#c", "topic#l"
};


enum PENN_DIS_DISSTANTS {
   PENN_DIS_NONE=0,
   PENN_DIS_BEGIN=1,
   PENN_ELAB_L, PENN_ATTR_R, PENN_LIST_C, PENN_SAME_C, PENN_ATTR_L,
   PENN_EVID_L, PENN_EVAL_L, PENN_PURP_L, PENN_BACK_L, PENN_CAUSE_L,
   PENN_CONT_R, PENN_CONT_C, PENN_BACK_R, PENN_TEMP_C, PENN_CONT_L,
   PENN_SUMM_L, PENN_MANN_L, PENN_TOPIC_C, PENN_TEMP_L,
   PENN_COND_L, PENN_COND_R, PENN_COMP_L, PENN_TEXT_C, PENN_CAUSE_R,
   PENN_COMP_C, PENN_PROB_C, PENN_CAUSE_C, PENN_EVAL_R,
   PENN_TEMP_R, PENN_EVID_R, PENN_PURP_R, PENN_PROB_L, PENN_COMP_R,
   PENN_ELAB_R, PENN_MANN_R, PENN_PROB_R, PENN_SUMM_R, PENN_COND_C,
   PENN_EVAL_C, PENN_EVID_C, PENN_TOPIC_L,
   PENN_DIS_COUNT
};


const int PENN_DIS_FIRST = 2;
const int PENN_DIS_COUNT_BITS = 8;

//===============================================================

class CDisConstituentLabel {
public:
   enum {NONE=0};
   enum {SENTENCE_BEGIN=PENN_DIS_BEGIN};
   enum {FIRST=PENN_DIS_FIRST};
   enum {COUNT=PENN_DIS_COUNT}; 
   enum {SIZE=PENN_DIS_COUNT_BITS};

protected:
   unsigned long m_code;

public:
   CDisConstituentLabel() { m_code=PENN_DIS_NONE; }
   CDisConstituentLabel(PENN_DIS_DISSTANTS t) { 
      m_code=t; 
   }
   CDisConstituentLabel(const unsigned long &t) { 
      m_code=t; 
   }
   CDisConstituentLabel(const std::string &s) { load(s); }
   virtual ~CDisConstituentLabel() {}

public:
   const unsigned long &code() const { return m_code; }
   const unsigned long &hash() const { return m_code; }
   void copy(const CDisConstituentLabel &c) {m_code = c.m_code; }
   const void clear() { m_code=NONE; }
   const bool empty() const { return m_code==NONE; }
   std::string str() const { assert(m_code<PENN_DIS_COUNT) ; return PENN_DIS_STRINGS[m_code]; }
   bool headleft() const
   {
	   assert(m_code<PENN_DIS_COUNT);
	   static int strlength;
	   strlength = PENN_DIS_STRINGS[m_code].length();
	   if(PENN_DIS_STRINGS[m_code][strlength-1] == 'r')
	   {
		   return false;
	   }
	   return true;
   }
   void load(const std::string &s) {
      m_code = PENN_DIS_NONE ;
      bool bFound = false;
      if (s.empty()) return;
      for (int i=0; i<PENN_DIS_COUNT; ++i) {
         if (PENN_DIS_STRINGS[i] == s) {
            m_code = i;
            bFound = true;
         }
      }
      // unknown constituent
      if (!bFound) {
         THROW("unknown constituent: " << s << '.');
      }
   }
   void load(const unsigned long &code) {m_code=code;}

public:
   bool operator == (const CDisConstituentLabel &t1) const { return m_code == t1.m_code; }
   bool operator < (const CDisConstituentLabel &t1) const { return m_code < t1.m_code; }
   bool operator > (const CDisConstituentLabel &t1) const { return m_code > t1.m_code; }
   bool operator <= (const CDisConstituentLabel &t1) const { return m_code <= t1.m_code; }
   bool operator >= (const CDisConstituentLabel &t1) const { return m_code >= t1.m_code; }
};

};

