// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * cfg.h - the definitions for english cfg                      *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2006.10                        *
 *                                                              *
 ****************************************************************/

#ifndef _ENGLISH_DISCFG_H
#define _ENGLISH_DISCFG_H

#include "tags.h"
#include "dis/cpenn.h"

//===============================================================

//inline unsigned long hash(const english::CConstituentLabel &con) { return con.code();}

//===============================================================

inline std::istream & operator >> (std::istream &is, english::CDisConstituentLabel &con) {
   std::string s;
   is >> s;
   con.load(s);
   return is;
}

inline std::ostream & operator << (std::ostream &os, const english::CDisConstituentLabel &con) {
   os << con.str() ;
   return os;
}

#endif

