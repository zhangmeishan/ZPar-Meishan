// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * dependencylabel.h - the labeled dependency tree              *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2008.07                        *
 *                                                              *
 ****************************************************************/

#ifndef _SEMDEPENDENCY_LABEL_H
#define _SEMDEPENDENCY_LABEL_H

#include "dependency.h"

/*==============================================================
 *
 * CSemanticDependencyTreeNode
 *
 *==============================================================*/

class CSemanticDependencyTreeNode : public CDependencyTreeNode {

public:
   std::string synlabel;
   std::string semlabel;

public:
   CSemanticDependencyTreeNode( ) : CDependencyTreeNode(), synlabel(""), semlabel("") { }
   CSemanticDependencyTreeNode( const std::string &w, const std::string &t, const int &h, const std::string &syn, const std::string &sem) : CDependencyTreeNode(w, t, h), synlabel(syn), semlabel(sem) { }
   virtual ~CSemanticDependencyTreeNode() {}

public:
   bool operator ==(const CSemanticDependencyTreeNode &item) const {
      return static_cast<CDependencyTreeNode>(*this) == static_cast<CDependencyTreeNode>(item) && synlabel == item.synlabel && semlabel == item.semlabel;
   }

};

//==============================================================

inline std::istream & operator >> (std::istream &is, CSemanticDependencyTreeNode &node) {
   (is) >> static_cast<CDependencyTreeNode&>(node) >> node.synlabel >> node.semlabel;
   if (node.synlabel.empty() || node.semlabel.empty()) THROW("dependency label is unavailable for the input: " << node.word);
   return is ;
}

inline std::ostream & operator << (std::ostream &os, const CSemanticDependencyTreeNode &node) {
   os << static_cast<const CDependencyTreeNode&>(node) << "\t" << node.synlabel << "\t" << node.semlabel ;
   return os ;
}


/*==============================================================
 *
 * CSemanticDependencyTree
 *
 * Note that we must define the dependency as sentencetemplate
 * in order to use the standard reading and writing functions
 * defined by the sentence template. Inheritance does not work
 * with template because the generic programming idea does not
 * mix well with the object-oriented programming ideologies. 
 *
 *==============================================================*/

typedef CSentenceTemplate<CSemanticDependencyTreeNode> CSemanticDependencyTree ;

#endif
