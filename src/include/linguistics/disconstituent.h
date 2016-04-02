// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * constituent.h - the constituent tree                         *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2008.11                        *
 *                                                              *
 ****************************************************************/

#ifndef _DISCONSTITUENT_H
#define _DISCONSTITUENT_H

#include "definitions.h"
#include "utils.h"
#include "cfg.h"

namespace TARGET_LANGUAGE {

/*==============================================================
 *
 * CDISTreeNode
 *
 *==============================================================*/

class CDISTreeNode {

public:
   bool is_leaf; //
   bool single_child; // single or double
   bool head_left;
   bool temp;
   // fields for constituents
   std::string constituent;
   // if constituent tree, false; if discourse tree, true
   bool type;
//   unsigned long constituent;
   int left_child;
   int right_child;
   // fields for tokens and constituents
   int token_start;
   int token_end;
   int head_start;
   int head_end;

public:
   CDISTreeNode() : head_start(-1), head_end(-1), token_start(-1), token_end(-1),
                    left_child(-1), right_child(-1), is_leaf(false), single_child(false),
                    head_left(true), temp(false), type(false), constituent("") {
   }
   virtual ~CDISTreeNode() {}

public:
   bool operator ==(const CDISTreeNode &item) const {
      throw("Can't compare directly because the contents are flexible indice. Compare trees!");
   }
   
   std::string str() const {
     std::ostringstream os;
     if (!is_leaf)
        os << "Constituent(left=" << left_child << ", right=" << right_child << ")";
     else os << "Leaf";
     
     return os.str();
   }

};

/*==============================================================
 *
 * CDISTree
 *
 * Note that we must define the constituent as sentencetemplate
 * in order to use the standard reading and writing functions
 * defined by the sentence template. Inheritance does not work
 * with template because the generic programming idea does not
 * mix well with the object-oriented programming ideologies. 
 *
 *==============================================================*/

class CDISTree {

public:
   CTwoStringVector words;
   std::vector<CDISTreeNode> syn_nodes;
   std::vector<unsigned long> syn_roots;
   std::vector<unsigned long> syn_starts;
   std::vector<unsigned long> syn_ends;
   std::vector< unsigned long > edu_starts;
   std::vector< unsigned long > edu_ends;
   std::vector<CDISTreeNode> dis_nodes;
   int dis_root;

public:
   CDISTree() : dis_root (-1) {}
   virtual ~CDISTree() {}

public:
   int newNode(bool is_syn) {
	   if(is_syn){syn_nodes.push_back(CDISTreeNode()); return syn_nodes.size()-1; }
	   else{dis_nodes.push_back(CDISTreeNode()); return dis_nodes.size()-1;}
   }
   int newWord(const std::string &word, const std::string &pos) { words.push_back(std::make_pair(word, pos)); return(words.size()-1); }
   int newEdu(const unsigned long &startId, const unsigned long &endId) {edu_starts.push_back(startId); edu_ends.push_back(endId);return(edu_starts.size()-1); }
   bool empty() const {return dis_nodes.empty()&&syn_nodes.empty()&&words.empty();}
   void clear() {dis_root=-1;dis_nodes.clear();syn_roots.clear();syn_nodes.clear(); syn_starts.clear(); syn_ends.clear(); words.clear();edu_starts.clear();edu_ends.clear();}
   int readNode(std::istream &is, bool is_syn);
   std::string writeNode(int node, bool is_syn) const;
   std::string debugNode(int node, bool is_syn) const;
   std::string writeNodeUnbin(int node, bool is_syn) const;
   bool nodesEqual(const CDISTree &tree, int i, int tree_i, bool is_syn) const ;
   std::string str() const {
      if (dis_root == -1)
         return "";
      std::ostringstream oss;
      static int i;
      for(i=0; i<words.size();i++)
      {
    	  if(words[i].second == "-NONE-" ) oss << words[i].first << std::endl;
    	  else oss << words[i].first << "_" << words[i].second << " ";
      }
      for(i=0; i<syn_roots.size();i++) oss << writeNode(syn_roots[i], true) << std::endl;
      oss << writeNode(dis_root, false) << std::endl;
      return oss.str();
   }
   std::string str_unbinarized() const {
	  if (dis_root == -1)
		 return "";
	  std::ostringstream oss;
	  static int i;
	  for(i=0; i<words.size();i++)
	  {
		  if(words[i].second == "-NONE-" ) oss << words[i].first << std::endl;
		  else oss << words[i].first << "_" << words[i].second << " ";
	  }
	  for(i=0; i<syn_roots.size();i++) oss << "(ROOT " << writeNodeUnbin(syn_roots[i], true)  << ")" << std::endl;
	  oss << writeNodeUnbin(dis_root, false) << std::endl;
	  return oss.str();
   }
   bool operator == (const CDISTree &tree) const {
	  static int i;
	  if(words.size() != tree.words.size()) return false;
	  if(syn_roots.size() != tree.words.size()) return false;
	  for(i=0; i<words.size();i++)
	  {
		  if(words[i].first != tree.words[i].first
		  || words[i].second != tree.words[i].second)
		  {	return false; }
	  }
	  for(i=0; i<syn_roots.size();i++)
	  {
		  if(!nodesEqual(tree, syn_roots[i], tree.syn_roots[i], true))
			  return false;
	  }

	  return nodesEqual(tree, dis_root, tree.dis_root, false);
   }

   int parent(const int &node, bool is_syn) const {
	   if(is_syn)
	   {
		   int sent_id = 0;
		   while(syn_ends[sent_id] < node) sent_id++;
		   for (int i=node+1; i<=syn_ends[i]; ++i) {
			 if (syn_nodes[i].left_child==node || syn_nodes[i].right_child==node)
				return i;
		  }
	   }
	   else
	   {
		  for (int i=node+1; i<dis_nodes.size(); ++i) {
			 if (dis_nodes[i].left_child==node || dis_nodes[i].right_child==node)
				return i;
		  }
	   }
	   return -1;
   }


}; 

//==============================================================

inline std::istream & operator >> (std::istream &is, CDISTree &tree) {
   tree.clear();
   std::vector<std::string> lines;
   std::string line;
   std::string word_pos, curword, curpos;
   int i, j;

   getline(is, line);
   while(is && !line.empty())
   {
      lines.push_back(line);
      getline(is, line);
   }

   int line_count = lines.size();
   if(line_count == 0) return is;

   if(line_count%2!=1)
   {
	   assert(0);
   }

   int sent_num = line_count/2;

   for(i=0; i < sent_num; i++)
   {
	   std::istringstream iss_sent(lines[i]);

	   while(iss_sent)
	   {
		   iss_sent >> word_pos;
		   curword = "";
		   curpos = "";
		   j=word_pos.length()-1;
		   while(j>=0)
		   {
			   if(word_pos[j] == '_')break;
			   curpos = word_pos[j]+curpos;
			   j--;
		   }
		   if(j==-1)
		   {
			   curword=curpos;
			   curpos = "-NONE-";
			   assert(curword=="<S>"||curword=="<P>");
			   tree.words.push_back(std::make_pair(curword, curpos));
			   break;
		   }
		   else
		   {
			   j--;
			   while(j>=0)
			   {
				   curword = word_pos[j]+curword;
				   j--;
			   }
			   tree.words.push_back(std::make_pair(curword, curpos));
		   }
	   }

	   std::istringstream iss_cfg(lines[sent_num+i]);
	   tree.syn_starts.push_back(tree.syn_nodes.size());
	   tree.syn_roots.push_back(tree.readNode(iss_cfg, true));
	   tree.syn_ends.push_back(tree.syn_nodes.size()-1);
   }

   std::istringstream iss_dis(lines[2*sent_num]);
   tree.dis_root = tree.readNode(iss_dis, false);

   /*
   std::cout << "syn trees:" << std::endl;
   for(i=0; i<tree.syn_starts.size();i++)
   {
	   std::cout << "start: " << tree.syn_starts[i] << "\tend: " << tree.syn_ends[i] << "\tend: " << tree.syn_roots[i] << std::endl;
   }

   std::cout << "edus:" << std::endl;
   for(i=0; i<tree.edu_starts.size();i++)
   {
	   std::cout << "start: " << tree.edu_starts[i] << "\tend: " << tree.edu_ends[i] << std::endl;
   }
   */

   return is ;
}

inline std::ostream & operator << (std::ostream &os, const CDISTree &tree) {
   os << tree.str() << std::endl;
   return os ;
}

//==============================================================

inline void UnparseSentence(const CDISTree *parsed, CTwoStringVector *tagged) {
   (*tagged) = parsed->words;
}

}



#endif
