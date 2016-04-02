// Yue Zhang

#ifndef _LABELED_DISBRACKET_H
#define _LABELED_DISBRACKET_H

namespace TARGET_LANGUAGE {

class CLabeledDisBracket {

public:
   unsigned begin;
   unsigned end;
   unsigned long constituent;

public:
   CLabeledDisBracket(): begin(0), end(0), constituent(0) {}
   CLabeledDisBracket(const unsigned &begin, const unsigned &end, const unsigned long &constituent): begin(begin), end(end), constituent(constituent) {}
};

inline
std::ostream & operator << (std::ostream &os, const CLabeledDisBracket &lb) {
   os << '<' << lb.begin << ',' << lb.end << ',' << CDisConstituent(lb.constituent).str() << '>';
}

} // namespace TARGET_LANGUAGE

#endif
