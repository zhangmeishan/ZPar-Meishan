// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * ctb5.h - the definitions for chinese tags                    *
 *                                                              *
 * Author: meishan zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2013.01                        *
 *                                                              *
 ****************************************************************/

#ifndef _CHINESE_TAG_PENN_H
#define _CHINESE_TAG_PENN_H

namespace chinese {

// the penn tag set
// Modify the following three constants together, keeping consistency!
const std::string PENN_TAG_STRINGS[] = {
   "-NONE-",
   "-BEGIN-",
   "-END-",
   "a", "b", "c", "d", "e",
   "f", "h", "k", "m", "n",
   "nr", "nrf", "ns", "nt",
   "nx", "nz", "o", "p", "q",
   "r", "s", "t", "u", "v",
   "w", "y", "z",
};


enum PENN_TAG_CONSTANTS {
   PENN_TAG_NONE=0,
   PENN_TAG_BEGIN,
   PENN_TAG_END,
   SUTD_TAG_A, SUTD_TAG_B, SUTD_TAG_C, SUTD_TAG_D, SUTD_TAG_E,
   SUTD_TAG_F, SUTD_TAG_H, SUTD_TAG_K, SUTD_TAG_M, SUTD_TAG_N,
   SUTD_TAG_NR, SUTD_TAG_NRF, SUTD_TAG_NS, SUTD_TAG_NT,
   SUTD_TAG_NX, SUTD_TAG_NZ, SUTD_TAG_O, SUTD_TAG_P, SUTD_TAG_Q,
   SUTD_TAG_R, SUTD_TAG_S, SUTD_TAG_T, SUTD_TAG_U, SUTD_TAG_V,
   SUTD_TAG_W, SUTD_TAG_Y, SUTD_TAG_Z,
   PENN_TAG_COUNT
};

const unsigned long PENN_TAG_FIRST = 3;
const unsigned long PENN_TAG_COUNT_BITS = 6; // 32 < bits < 64, takes 6 bits

const bool PENN_TAG_CLOSED[] = {
   false,
   false,
   false,
   false, false, false, false, false,
   false, false, false, false, false,
   false, false, false, false,
   false, false, false, false, false,
   false, false, false, false, false,
   false, false, false,
};

//===============================================================

class CTag {
public:
   enum {SENTENCE_BEGIN = PENN_TAG_BEGIN};
   enum {SENTENCE_END = PENN_TAG_END};
   enum {COUNT = PENN_TAG_COUNT};
   enum {MAX_COUNT = PENN_TAG_COUNT};
   enum {NONE = PENN_TAG_NONE};
   enum {SIZE = PENN_TAG_COUNT_BITS};
   enum {FIRST = PENN_TAG_FIRST};
   enum {LAST = PENN_TAG_COUNT-1};

protected:
   unsigned long m_code;

public:
   CTag() : m_code(NONE) {}
   CTag(PENN_TAG_CONSTANTS t) : m_code(t) { }
   CTag(int t) : m_code(t) { assert(t<PENN_TAG_COUNT); }
   CTag(const std::string &s) { load(s); }
   virtual ~CTag() {}

public:
   const unsigned long &code() const { return m_code; }
   const unsigned long &hash() const { return m_code; }
   std::string str() const {
      assert(m_code<(1<<PENN_TAG_COUNT_BITS)) ;
      if (m_code>=PENN_TAG_COUNT) {
         std::stringstream ss;
         ss << "EXTRA(";
         ss << m_code;
         ss << ")";
         return ss.str();
      }
      return PENN_TAG_STRINGS[m_code];
   }
   void load(const std::string &s) {
      //m_code = PENN_TAG_NONE ;
      for (int i=0; i<PENN_TAG_COUNT; ++i)
         if (PENN_TAG_STRINGS[i] == s) {
            m_code = i;
            return;
         }
      THROW("Unknown tag (PENN Treebank): " << s);
   }
   bool loadcheck(const std::string &s) {
      //m_code = PENN_TAG_NONE ;
      for (int i=0; i<PENN_TAG_COUNT; ++i)
         if (PENN_TAG_STRINGS[i] == s) {
            m_code = i;
            return true;
         }
      m_code = 0;
      return false;
   }
   void load(const unsigned long &n) { m_code = n; }
   void copy(const CTag &t) { m_code = t.m_code; }

public:
   bool operator == (const CTag &t1) const { return m_code == t1.m_code; }
   bool operator != (const CTag &t1) const { return m_code != t1.m_code; }
   bool operator < (const CTag &t1) const { return m_code < t1.m_code; }
   bool operator > (const CTag &t1) const { return m_code > t1.m_code; }
   bool operator <= (const CTag &t1) const { return m_code <= t1.m_code; }
   bool operator >= (const CTag &t1) const { return m_code >= t1.m_code; }
};

}; // namespace chinese

#endif

