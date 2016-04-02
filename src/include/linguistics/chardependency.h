// Copyright (C) SUTD 2014
/****************************************************************
 *                                                              *
 * chardependency.h - the character-level dependency tree       *
 *                                                              *
 * Author: Meishan Zhang                                        *
 *                                                              *
 * SUTD. 2014.12                                                *
 *                                                              *
 ****************************************************************/

#ifndef _CHARDEPENDENCY_H
#define _CHARDEPENDENCY_H

#include "sentence_template.h"
#include "sentence_string.h"

const int CHARDEPENDENCY_LINK_NO_HEAD = -1;

/*==============================================================
 *
 * CCharDependencyTreeNode
 *
 *==============================================================*/

class CCharDependencyTreeNode {

public:
   std::string word;
   std::string tag;
   std::string tagtype;
   int head;
   std::string label;
   std::string labeltype;

public:
   CCharDependencyTreeNode() :
	   word(""),
	   tag(""),
	   tagtype(""),
	   head(CHARDEPENDENCY_LINK_NO_HEAD),
	   label(""),
	   labeltype("")
   { }
   CCharDependencyTreeNode( const std::string &w, const std::string &t, const std::string &tt, const int &h, const std::string &l, const std::string &lt) :
	   word(w),
	   tag(t),
	   tagtype(tt),
	   head(h),
	   label(l),
	   labeltype(lt) { }
   virtual ~CCharDependencyTreeNode() {}

public:
   bool operator ==(const CCharDependencyTreeNode &item) const {
      return word == item.word && tag == item.tag && tagtype == item.tagtype && head == item.head && label == item.label && labeltype == item.labeltype;
   }

};

//==============================================================

inline std::istream & operator >> (std::istream &is, CCharDependencyTreeNode &node) {
   (is) >> node.word >> node.tag >> node.tagtype >> node.head >> node.label >> node.labeltype ;
   return is ;
}

inline std::ostream & operator << (std::ostream &os, const CCharDependencyTreeNode &node) {
   os << node.word << "\t" << node.tag << "\t" << node.tagtype << "\t" << node.head << "\t" << node.label << "\t" << node.labeltype ;
   return os ;
}

/*==============================================================
 *
 * CUnlabeledDependencyTree
 *
 * Note that we must define the dependency as sentencetemplate
 * in order to use the standard reading and writing functions
 * defined by the sentence template. Inheritance does not work
 * with template because the generic programming idea does not
 * mix well with the object-oriented programming ideologies. 
 *
 *==============================================================*/

typedef CSentenceTemplate<CCharDependencyTreeNode> CCharDependencyTree ;

//==============================================================


/*==============================================================
 *
 * dependency tree utility functioned
 *
 *==============================================================*/

/*--------------------------------------------------------------
 *
 * IsValidDependencyTree - check well-formed
 *
 *--------------------------------------------------------------*/


inline
bool IsValidDependencyTree(const CCharDependencyTree &tree) {
   if ( tree.empty() ) return true;
   int nHead = 0;
   int nLoop = 0;
   int j;
   for ( int i=0; i<static_cast<int>(tree.size()); ++i ) {
      if ( tree.at(i).head == CHARDEPENDENCY_LINK_NO_HEAD ) nHead++ ;
      j = i;
      while ( nLoop & (1<<j) == 0 ) {
         nLoop &= (1<<j); // mark to avoid duplicate checking for head
         j = tree.at(i).head;  // move to head
         if (j==CHARDEPENDENCY_LINK_NO_HEAD) break; // head found
         if (j>=static_cast<int>(tree.size())) return false; // std::cout of the boundary of sentence
         if (j==i) return false; // loop found
      }
   }
   if (nHead==1) return true; return false;
}

/*--------------------------------------------------------------
 *
 * IsProjectiveDependencyTree - check projectivity
 *
 *--------------------------------------------------------------*/


inline
bool IsProjectiveDependencyTree(const CCharDependencyTree &tree) {
   if (!IsValidDependencyTree(tree)) return false;
   for ( int i=0; i<static_cast<int>(tree.size()); ++i ) {
      int mini = std::min(i, tree.at(i).head);
      int maxi = std::max(i, tree.at(i).head);
      for ( int j=mini+1; j<maxi; ++j )
         if (tree.at(j).head<mini||tree.at(j).head>maxi) return false;
   }
   return true;
}

/*---------------------------------------------------------------
 *
 * UnparseSentence - from dependency tree to raw sentence
 *
 *--------------------------------------------------------------*/

inline
void UnparseDeSegmentedSentenceCharConll(const CCharDependencyTree *parsed, CStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   CCharDependencyTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
      retval->push_back(it->word);
}



/*---------------------------------------------------------------
 *
 * UnparseSentenceCharConll - from char dependency tree to raw sentence
 *
 *--------------------------------------------------------------*/


inline
void UnparseSentenceCharConll(const CCharDependencyTree *parsed, CStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   CCharDependencyTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
   {
	   if(it->tagtype.compare("b") == 0)
	   {
		   retval->push_back(it->word);
	   }
	   else
	   {
		   std::string curword = retval->back() + it->word;
		   retval->pop_back();
		   retval->push_back(curword);
	   }
   }
}

/*---------------------------------------------------------------
 *
 * UnparseSentenceCharConll - from char dependency tree to tagged sentence
 *
 *--------------------------------------------------------------*/

inline
void UnparseSentenceCharConll(const CCharDependencyTree *parsed, CTwoStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   CCharDependencyTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
   {
	   if(it->tagtype.compare("b") == 0)
	   {
		   retval->push_back(std::make_pair(it->word, it->tag));
	   }
	   else
	   {
		   std::pair<std::string, std::string> curwordpair = retval->back();
		   retval->pop_back();
		   retval->push_back(std::make_pair(curwordpair.first+it->word, curwordpair.second));
	   }
   }
}



#endif
