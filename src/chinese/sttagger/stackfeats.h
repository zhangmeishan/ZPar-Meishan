// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * supertag.h - the supertags for dependency parser in general  *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 ****************************************************************/

#ifndef _CHINESETAGGER_STACKFEAT_H
#define _CHINESETAGGER_STACKFEAT_H



class CStackFeats {

public:
	//neglect the feats "_"
     std::vector<std::string>  m_feats1;
     std::vector<std::string>  m_feats2;


public:
     inline int getsize() const { return m_feats1.size(); }
     inline bool empty() const { return m_feats1.size()<=0; }
     inline std::string getfeat1(int index) const { assert(index<m_feats1.size()); return m_feats1[index]; }
     inline std::string getfeat2(int index) const { assert(index<m_feats2.size()); return m_feats2[index]; }


public:
   friend std::istream & operator >> (std::istream &is, CStackFeats &p);
   friend std::ostream & operator << (std::ostream &os, const CStackFeats &p);

};

//==============================================================================

inline std::istream & operator >> (std::istream &is, CStackFeats &p) {
   std::string s ; 
   getline(is, s);
   if (is && !(s.empty())) {
	   std::istringstream iss(s);
	   p.m_feats1.clear();
	   p.m_feats2.clear();
	   std::string line;
	   getline(iss, line, '\t');
	   while (iss && !line.empty()) {
	       std::string first = "";
	       std::string second = "";
	       bool bfind = false;
	       for(int idx = 0; idx < line.length();idx++)
	       {
	           if(line.at(idx) == '#')
	           {
	               bfind = true;
	               continue;
	           }
	           if(!bfind)
	           {
	               first = first + line.at(idx);
	           }
	           else
	           {
	               second = second + line.at(idx);
	           }
	       }
	       p.m_feats1.push_back(first);
	       p.m_feats2.push_back(second);
		   getline(iss, line, '\t');
	   }
   }
   else {
      THROW("No StackFeats read.");
   }
   return is;
}

//std::ostream & operator << (std::ostream &os, const TARGET_LANGUAGE::depparser::CSuperTag &p) {
inline std::ostream & operator << (std::ostream &os, const CStackFeats &p) {
   for (unsigned long i=0; i<p.m_feats1.size(); ++i) {
      os << p.m_feats1[i] << "#" << p.m_feats2[i] << '\t';
   }
   os << std::endl;
   return os ;
}





#endif

