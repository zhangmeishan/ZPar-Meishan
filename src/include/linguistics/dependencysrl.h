// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * dependencysrl.h - the dependency tree with srl arcs          *
 *                                                              *
 * Author: Meishan Zhang                                        *
 *                                                              *
 * SUTD . 2014.11                                               *
 *                                                              *
 ****************************************************************/

#ifndef _DEPENDENCYSRL_H
#define _DEPENDENCYSRL_H

#include "sentence_template.h"
#include "sentence_string.h"

const int DEPENDENCYSRL_LINK_NO_HEAD = -1;

/*==============================================================
 *
 * CDependencySRLTreeNode
 *
 *==============================================================*/

class CDependencySRLTreeNode {

public:
   std::string word;
   std::string tag;
   int head;
   std::string label;
   std::string srltype; //0: not srl, 1: verb, 2: noun
   std::string srllabels; // splited by |

public:
   CDependencySRLTreeNode() :
	   word(""),
	   tag(""),
	   head(DEPENDENCYSRL_LINK_NO_HEAD),
	   label(""),
	   srltype(""),
	   srllabels("")
   { }

   CDependencySRLTreeNode( const std::string &w, const std::string &t, const int &h, const std::string &l, const std::string &st, const std::string &sl) :
	   word(w),
	   tag(t),
	   head(h),
	   label(l),
	   srltype(st),
	   srllabels(sl) { }
   virtual ~CDependencySRLTreeNode() {}

public:
   bool operator ==(const CDependencySRLTreeNode &item) const {
      return word == item.word && tag == item.tag && head == item.head && label == item.label && srltype == item.srltype && srllabels == item.srllabels;
   }

};

//==============================================================

inline std::istream & operator >> (std::istream &is, CDependencySRLTreeNode &node) {
   (is) >> node.word >> node.tag>> node.head >> node.label >> node.srltype  >> node.srllabels ;
   return is ;
}

inline std::ostream & operator << (std::ostream &os, const CDependencySRLTreeNode &node) {
   os << node.word << "\t" << node.tag << "\t" << node.head << "\t" << node.label << "\t" << node.srltype << "\t" << node.srllabels ;
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

typedef CSentenceTemplate<CDependencySRLTreeNode> CDependencySRLTree ;

//==============================================================


/*==============================================================
 *
 * dependencysrl tree utility functioned
 *
 *==============================================================*/

/*--------------------------------------------------------------
 *
 * IsValidDependencySRLTree - check well-formed
 *
 *--------------------------------------------------------------*/
inline
bool IsValidDependencyTree(const CDependencySRLTree &tree) {
   if ( tree.empty() ) return true;
   int nHead = 0;
   int nLoop = 0;
   int j;
   for ( int i=0; i<static_cast<int>(tree.size()); ++i ) {
      if ( tree.at(i).head == DEPENDENCY_LINK_NO_HEAD ) nHead++ ;
      j = i;
      while ( nLoop & (1<<j) == 0 ) {
         nLoop &= (1<<j); // mark to avoid duplicate checking for head
         j = tree.at(i).head;  // move to head
         if (j==DEPENDENCY_LINK_NO_HEAD) break; // head found
         if (j>=static_cast<int>(tree.size())) return false; // std::cout of the boundary of sentence
         if (j==i) return false; // loop found
      }
   }
   if (nHead==1) return true; return false;
}

/*--------------------------------------------------------------
 *
 * IsProjectiveDependencySRLTree - check projectivity
 *
 *--------------------------------------------------------------*/
inline
bool IsProjectiveDependencyTree(const CDependencySRLTree &tree) {
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
 * UnparseSentence - from dependencysrl tree to raw sentence
 *
 *--------------------------------------------------------------*/


inline
void UnparseSentence(const CDependencySRLTree *parsed, CStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   typename CDependencySRLTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
      retval->push_back(it->word);
}

/*---------------------------------------------------------------
 *
 * UnparseSentence - from dependencysrl tree to tagged sentence
 *
 *--------------------------------------------------------------*/


inline
void UnparseSentence(const CDependencySRLTree *parsed, CTwoStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   typename CDependencySRLTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
      retval->push_back(std::make_pair(it->word, it->tag));
}

/*---------------------------------------------------------------
 *
 * UnparseSentence - from dependencysrl tree to tagged sentence & srltypes
 *
 *--------------------------------------------------------------*/


inline
void UnparseSentence(const CDependencySRLTree *parsed, CTwoStringVector *retval, CStringVector *srltypes) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   typename CDependencySRLTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
   {
      retval->push_back(std::make_pair(it->word, it->tag));
      srltypes->push_back(it->srltype);
   }
}

/*---------------------------------------------------------------
 *
 * UnparseAndDesegmentSentence - from dependencysrl tree to raw sent
 *
 *--------------------------------------------------------------*/


inline
void UnparseAndDesegmentSentence(const CDependencySRLTree *parsed, CStringVector *retval) {
   assert(retval != NULL);
   retval->clear();
   if (parsed == NULL)
      return;
   typename CDependencySRLTree::const_iterator it;
   for (it=parsed->begin(); it!=parsed->end(); ++it)
      getCharactersFromUTF8String(it->word, retval);
}




#endif
