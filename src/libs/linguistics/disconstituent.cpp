// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * disconstituent.cpp - the text-level parse tree                       *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 * SUTD 2015                        *
 *                                                              *
 ****************************************************************/

#include "linguistics/disconstituent.h"

using namespace TARGET_LANGUAGE;

int CDISTree::readNode(std::istream &is, bool is_syn) {
      int node;
      std::string s, name;
      is >> s;
      assert(s == "(");
      is >> name;
      is >> s;
      assert (s.size() <= 2);
      int left, right;
      bool temporary;
      temporary = false;
      if (s.size()==2) {
         assert(s[1]=='*');
         temporary = true;
      }
      std::vector<CDISTreeNode> &nodes = is_syn? syn_nodes : dis_nodes;
      if (s[0] == 'l' || s[0] == 'r') {
         left = readNode(is, is_syn);
         right = readNode(is, is_syn);
         node = newNode(is_syn);
         nodes[node].is_leaf = false;
         nodes[node].single_child = false;
         if (s[0] =='l' ){
        	 nodes[node].head_left = true;
        	 nodes[node].head_start = nodes.at(left).head_start;
        	 nodes[node].head_end = nodes.at(left).head_end;
         }
         else
		 {
        	 nodes[node].head_left = false;
        	 nodes[node].head_start = nodes.at(right).head_start;
        	 nodes[node].head_end = nodes.at(right).head_end;
		 }
         nodes[node].left_child = left;
         nodes[node].right_child = right;
         nodes[node].constituent = name;
         nodes[node].token_start = nodes.at(left).token_start;
         nodes[node].token_end = nodes.at(right).token_end;
         nodes[node].temp = temporary;
         is >> s;
         assert(s==")");
      }
      else if (s[0] == 's') {
         left = readNode(is, is_syn);
         node = newNode(is_syn);
         nodes[node].is_leaf = false;
         nodes[node].single_child = true;
         nodes[node].left_child = left;
         nodes[node].constituent = name;
         nodes[node].right_child = -1;
         nodes[node].token_start = nodes.at(left).token_start;
         nodes[node].token_end = nodes.at(left).token_end;
         nodes[node].head_left = false;
         nodes[node].head_start = nodes.at(left).head_start;
         nodes[node].head_end = nodes.at(left).head_end;
         nodes[node].temp = temporary;
         assert(temporary==false); // single node can't be binarized temp
         is >> s;
         assert(s==")");
      }
      else {
         ASSERT(s[0]=='t', "A leaf node must be tagged t, not "<<s[0]);
         int token_start, token_end;
         node = newNode(is_syn);
         nodes[node].is_leaf = true;;
         nodes[node].single_child = false;
         nodes[node].head_left = false;
         nodes[node].constituent = name;
         is >> token_start;
         is >> token_end;
         is >> s;
         assert(s==")");
         nodes[node].token_start = token_start;
         nodes[node].token_end = token_end;
         nodes[node].head_start = token_start;
         nodes[node].head_start = token_end;
         nodes[node].left_child = -1;
         nodes[node].right_child = -1;
         if(!is_syn)newEdu(token_start, token_end);
      }
      return node;
}

std::string CDISTree::writeNode(int node, bool is_syn) const {
      const CDISTreeNode &nd = is_syn ? syn_nodes[node] : dis_nodes[node];
      std::string name;
      std::string type;
      std::string cont;
      if (!nd.is_leaf) { // [1]node type cons
    	 if (nd.single_child)
			type = "s";
		 else if (nd.head_left)
			type = "l";
		 else
			type = "r";

		 name = nd.constituent;
		 if (nd.temp)
			type += "*";
		 if (nd.single_child)
			cont = writeNode(nd.left_child, is_syn);
		 else {
			cont = writeNode(nd.left_child, is_syn) + " " + writeNode(nd.right_child, is_syn);
		 }
      }
      else { //[2] node.type token
    	  name = nd.constituent;
    	  if(is_syn) name = words[nd.token_start].second;
    	  type = "t";
    	  std::ostringstream oss;
    	  oss << nd.token_start << " " << nd.token_end;
    	  cont = oss.str();
      }
      return "( " + name + " " + type + " " + cont + " )";
}

std::string CDISTree::writeNodeUnbin(int node, bool is_syn) const {
   const CDISTreeNode &nd = is_syn ? syn_nodes[node] : dis_nodes[node];
   std::string name;
   std::string cont;
   if (!nd.is_leaf) { // [1] constituent
      // do not write node label for temp nodes and NONE nodes (fragmented tree)
      if (nd.temp) {
         return writeNodeUnbin(nd.left_child, is_syn) + " " + writeNodeUnbin(nd.right_child, is_syn);
      }
      else {
         name = nd.constituent;
         if(!is_syn)
         {
        	 int namelength = name.length();
        	 std::string headlabel = name.substr(0, namelength-2);
        	 assert(name[namelength-2] == '#');
        	 if(headlabel == "Root")
        	 {
        		 name = "#" + headlabel + "#" + headlabel;
        	 }
        	 else if(name[namelength-1] == 'S')
        	 {
        		 name = "#Satellite#" + headlabel;
        	 }
        	 else
        	 {
        		 assert(name[namelength-1] == 'N');
        		 name = "#Nucleus#" + headlabel;
        	 }
         }
         if (nd.single_child) 
            cont = writeNodeUnbin(nd.left_child, is_syn);
         else {
            cont = writeNodeUnbin(nd.left_child, is_syn) + " " + writeNodeUnbin(nd.right_child, is_syn);
         }
         return "(" + name + " " + cont + ")";
      }
   }
   else { // [2] token
      name = nd.constituent;
      if(!is_syn)
       {
      	 int namelength = name.length();
      	 std::string headlabel = name.substr(0, namelength-2);
      	 if(name[namelength-2] != '#')
      	 {
      		 std::cout << "strange...." << std::endl;
      	 }
      	 if(headlabel == "Root")
      	 {
      		 name = "#" + headlabel + "#" + headlabel;
      	 }
      	 else if(name[namelength-1] == 'S')
      	 {
      		 name = "#Satellite#" + headlabel;
      	 }
      	 else
      	 {
      		 assert(name[namelength-1] == 'N');
      		 name = "#Nucleus#" + headlabel;
      	 }
       }
      else
      {
    	  name = words[nd.token_start].second;
      }
	  std::ostringstream oss;
	  if(!is_syn) oss << nd.token_start << "-" << nd.token_end;
	  else oss << words[nd.token_start].first;
	  cont = oss.str();
      return "(" + name + " " + cont + ")";
   }
}

bool CDISTree::nodesEqual(const CDISTree &tree, int i, int tree_i, bool is_syn) const {
      // compare nodes recursively between this and tree two cfg tree for the same inputs
      const CDISTreeNode &nd = is_syn ? syn_nodes[i] : dis_nodes[i];
      const CDISTreeNode &tree_nd = is_syn ? syn_nodes[tree_i] : dis_nodes[tree_i];
      if (nd.is_leaf != tree_nd.is_leaf)
         return false;
      if(nd.constituent != tree_nd.constituent)
    	 return false;
      if (!nd.is_leaf ) {
         if (nd.single_child != tree_nd.single_child)
            return false;
         if (nd.single_child) {
            return (nodesEqual(tree, nd.left_child, tree_nd.left_child, is_syn));
         }
         else {
            if (nd.head_left != tree_nd.head_left)
               return false;
            return (nodesEqual(tree, nd.left_child, tree_nd.left_child, is_syn) && nodesEqual(tree, nd.right_child, tree_nd.right_child, is_syn));
         }
      }
      else {
         assert(nd.is_leaf == true);
         if(nd.token_start != tree_nd.token_end) return false;
         return nd.token_end == tree_nd.token_end;
      }
   }


std::string CDISTree::debugNode(int node, bool is_syn) const {
      const CDISTreeNode &nd = is_syn ? syn_nodes[node] : dis_nodes[node];
      std::string name;
      std::string type;
      std::string cont;
      if (!nd.is_leaf) { // [1]node type cons
    	 if (nd.single_child)
			type = "s";
		 else if (nd.head_left)
			type = "l";
		 else
			type = "r";

		 name = nd.constituent;
		 if (nd.temp)
			type += "*";
		 if (nd.single_child)
			cont = debugNode(nd.left_child, is_syn);
		 else {
			cont = debugNode(nd.left_child, is_syn) + " " + debugNode(nd.right_child, is_syn);
		 }
      }
      else { //[2] node.type token
    	  name = nd.constituent;
    	  if(is_syn) name = words[nd.token_start].second;
    	  type = "t";
    	  std::ostringstream oss;
    	  oss << words[nd.token_start].first;
    	  cont = oss.str();
      }
      return "(" + name + "#" + type + " " + cont + ")";
}

