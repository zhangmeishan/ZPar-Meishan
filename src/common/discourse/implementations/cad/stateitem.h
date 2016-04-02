// Copyright (C) University of Oxford 2010
#ifndef _COMMON_CON_PARSER_STATEITEM
#define _COMMON_CON_PARSER_STATEITEM

#include "action.h"


class CConNode {
public:
   enum CON_NODE_TYPE {LEAF=0, SINGLE_CHILD, HEAD_LEFT, HEAD_RIGHT};
public:
   int id;
   CON_NODE_TYPE type;
   bool temp;
   // fields for constituents
   CConstituent constituent;
   const CConNode* left_child;
   const CConNode* right_child;
   // fields for tokens and constituents
   int headword;
   int headsent_id;
   int headpara_id;
   int word_start;
   int word_end;


public:
   inline bool head_left() const { return type==HEAD_LEFT; }
   inline bool head_right() const { return type==HEAD_RIGHT; }
   inline bool single_child() const { return type==SINGLE_CHILD; }
   inline bool is_leaf() const { return type==LEAF; }
   inline bool is_constituent() const { return type!=LEAF; }


public:
   CConNode(const int &id, const CON_NODE_TYPE &type, const bool &temp, const unsigned long &constituent,
		   CConNode *left_child, CConNode *right_child, const int &headword,
		   const int &headsent_id, const int &headpara_id, const int &word_start, const int &word_end) :
	   id(id), type(type), temp(temp), constituent(constituent), left_child(left_child), right_child(right_child),
	   headword(headword), headsent_id(headsent_id), headpara_id(headpara_id), word_start(word_start), word_end(word_end) {}

   CConNode(const int &id, const CON_NODE_TYPE &type, const bool &temp, const unsigned long &constituent,
		   const int &headword, const int &headsent_id, const int &headpara_id, const int &word_start, const int &word_end) :
	   id(id), type(type), temp(temp), constituent(constituent), left_child(0), right_child(0),
	   headword(headword), headsent_id(headsent_id), headpara_id(headpara_id), word_start(word_start), word_end(word_end) {}

   CConNode() : id(-1), type(), temp(0), constituent(), left_child(0), right_child(0),
		   headword(-1), headsent_id(-1), headpara_id(-1), word_start(-1), word_end(-1) {}

   virtual ~CConNode() {}

public:
   bool valid() const { return id!=-1; }

   void clear() {
      this->id = -1;
      this->type = static_cast<CON_NODE_TYPE>(0);
      this->temp = 0;
      this->constituent.clear();
      this->left_child = 0;
      this->right_child = 0;
      this->headword = -1;
      this->headsent_id = -1;
      this->headpara_id = -1;
      this->word_start = -1;
      this->word_end = -1;
   }

   void set(const int &id, const CON_NODE_TYPE &type, const bool &temp, const unsigned long &constituent, const CConNode *left_child,
		   const CConNode *right_child, const int &headword, const int &headsent_id, const int &headpara_id, const int &word_start, const int &word_end) {
      this->id = id;
      this->type = type;
      this->temp = temp;
      this->constituent = constituent;
      this->left_child = left_child;
      this->right_child = right_child;
      this->headword = headword;
      this->headsent_id = headsent_id;
      this->headpara_id = headpara_id;
      this->word_start = word_start;
      this->word_end = word_end;
   }//{}

   bool operator == (const CConNode &nd) const {
      return id == nd.id &&
             type == nd.type &&
             temp == nd.temp &&
             constituent == nd.constituent &&
             left_child == nd.left_child &&
             right_child == nd.right_child &&
             headword == nd.headword &&
             headsent_id == nd.headsent_id &&
             headpara_id == nd.headpara_id &&
             word_start == nd.word_start &&
             word_end == nd.word_end;
   }

   void operator = (const CConNode &nd) {
	      id = nd.id;
	      type = nd.type;
	      temp = nd.temp;
	      constituent = nd.constituent;
	      left_child = nd.left_child;
	      right_child = nd.right_child;
	      headword = nd.headword;
	      headsent_id = nd.headsent_id;
	      headpara_id = nd.headpara_id;
	      word_start = nd.word_start;
	      word_end = nd.word_end;
   }
public:
   void toCCONTreeNode(CDISTreeNode &node) const {
//      node.parent = parent->id;

	   node.is_leaf = is_leaf(); //
	   node.single_child = single_child(); // single or double
	   node.head_left = head_left(); // 0 terminal; 1 single; 2 coordinate; 3 left; 4 right.
	   node.temp = temp;
	   // fields for constituents
	   node.constituent = CConstituent(constituent.extractConstituentCode()).str();
	   //node.constituent = constituent.str();
	   // if constituent tree, false; if discourse tree, true
	   node.type = false;
	//   unsigned long constituent;
	   node.left_child = left_child ? left_child->id : -1;
	   node.right_child = right_child ? right_child->id : -1;
	   // fields for tokens and constituents
	   node.token_start = word_start;
	   node.token_end = word_end;
	   node.head_start = headword;
	   node.head_end = headword;
   }
};


/*===============================================================
 *
 * CDisNode - tree nodes
 *
 *==============================================================*/

class CDisNode {
public:
   enum DIS_NODE_TYPE {LEAF=0, HEAD_LEFT, HEAD_RIGHT};
public:
   int id;
   DIS_NODE_TYPE type;
   // fields for constituents
   CDisConstituent constituent;
   const CDisNode* left_child;
   const CDisNode* right_child;
   const CConNode* syn_tree;
   // fields for tokens and constituents
   int headword_start;
   int headword_end;
   int headedu_id;
   int headsent_id;
   int headpara_id;
   int word_start;
   int word_end;
   int edu_start;
   int edu_end;
   int sent_start;
   int sent_end;
   int para_start;
   int para_end;
   std::vector<const CConNode*> headspans;


public:
   inline bool head_left() const { return type==HEAD_LEFT; }
   inline bool head_right() const { return type==HEAD_RIGHT; }
   inline bool is_leaf() const { return type==LEAF; }
   inline bool is_constituent() const { return type!=LEAF; }


public:
   CDisNode(const int &id, const DIS_NODE_TYPE &type, const unsigned long &constituent,
		   CDisNode *left_child, CDisNode *right_child, const CConNode* syn_tree,
		   const int &headword_start, const int &headword_end, const int &headedu_id,
		   const int &headsent_id, const int &headpara_id,
		   const int &word_start, const int &word_end, const int &edu_start, const int &edu_end,
		   const int &sent_start, const int &sent_end, const int &para_start, const int &para_end) :
	   id(id), type(type), constituent(constituent), left_child(left_child), right_child(right_child),
	   syn_tree(syn_tree), headword_start(headword_start), headword_end(headword_end),
	   headedu_id(headedu_id),  headsent_id(headsent_id),  headpara_id(headpara_id),
	   word_start(word_start), word_end(word_end), edu_start(edu_start), edu_end(edu_end),
	   sent_start(sent_start), sent_end(sent_end), para_start(para_start), para_end(para_end)
       {
	   	   headspans.clear();
       }

   CDisNode() : id(-1), type(), constituent(), left_child(0), right_child(0), syn_tree(0),
		   headword_start(-1), headword_end(-1), headsent_id(-1), headedu_id(-1), headpara_id(-1),
		   word_start(-1), word_end(-1), edu_start(-1), edu_end(-1),
		   sent_start(-1), sent_end(-1), para_start(-1), para_end(-1)
	   {
		   headspans.clear();
	   }

   virtual ~CDisNode() {}

public:
   bool valid() const { return id!=-1; }

   void clear() { 
      this->id = -1;
      this->type = static_cast<DIS_NODE_TYPE>(0);
      this->constituent.clear(); 
      this->left_child = 0; 
      this->right_child = 0; 
      this->syn_tree = 0;
      this->headword_start = -1;
      this->headword_end = -1;
      this->headedu_id = -1;
      this->headsent_id = -1;
      this->headpara_id = -1;
      this->word_start = -1;
      this->word_end = -1;
      this->edu_start = -1;
      this->edu_end = -1;
      this->sent_start = -1;
      this->sent_end = -1;
      this->para_start = -1;
      this->para_end = -1;
      this->headspans.clear();
   }

   void addSpanHeadCFG(const CConNode* head_tree)
   {
	   headspans.push_back(head_tree);
   }

   void set(const int &id, const DIS_NODE_TYPE &type, const unsigned long &constituent, const CDisNode *left_child, const CDisNode *right_child,
		   const CConNode* syn_tree, const int &headword_start, const int &headword_end, const int &headedu_id, const int &headsent_id,  const int &headpara_id,
		   const int &word_start, const int &word_end, const int &edu_start, const int &edu_end,
		   const int &sent_start, const int &sent_end, const int &para_start, const int &para_end) {
      this->id = id;
      this->type = type;
      this->constituent = constituent; 
      this->left_child = left_child; 
      this->right_child = right_child; 
      this->syn_tree = syn_tree;
      this->headword_start = headword_start;
      this->headword_end = headword_end;
      this->headedu_id = headedu_id;
      this->headsent_id = headsent_id;
      this->headpara_id = headpara_id;
      this->word_start = word_start;
      this->word_end = word_end;
      this->edu_start = edu_start;
      this->edu_end = edu_end;
      this->sent_start = sent_start;
      this->sent_end = sent_end;
      this->para_start = para_start;
      this->para_end = para_end;
      this->headspans.clear();
   }

   bool operator == (const CDisNode &nd) const {
	   //if(!bIgnoreHeadSpanHeads)
	   {
		   if(headspans.size() != nd.headspans.size()) return false;
		   for(int i = 0; i < headspans.size(); i++)
		   {
			   if(headspans[i] != nd.headspans[i]) return false;
		   }
	   }
	   return id == nd.id &&
             type == nd.type && 
             constituent == nd.constituent && 
             left_child == nd.left_child && 
             right_child == nd.right_child &&
             syn_tree == nd.syn_tree &&
             headword_start == nd.headword_start &&
             headword_end == nd.headword_end &&
             headedu_id == nd.headedu_id &&
             headsent_id == nd.headsent_id &&
             headpara_id == nd.headpara_id &&
             word_start == nd.word_start &&
             word_end == nd.word_end &&
             edu_start == nd.edu_start &&
             edu_end == nd.edu_end &&
             sent_start == nd.sent_start &&
             sent_end == nd.sent_end &&
             para_start == nd.para_start &&
             para_end == nd.para_end;
   }

   void operator = (const CDisNode &nd) {
	      id = nd.id;
	      type = nd.type;
	      constituent = nd.constituent;
	      left_child = nd.left_child;
	      right_child = nd.right_child;
	      syn_tree = nd.syn_tree;
	      headword_start = nd.headword_start;
	      headword_end = nd.headword_end;
	      headedu_id = nd.headedu_id;
	      headsent_id = nd.headsent_id;
	      headpara_id = nd.headpara_id;
	      word_start = nd.word_start;
	      word_end = nd.word_end;
	      edu_start = nd.edu_start;
	      edu_end = nd.edu_end;
	      sent_start = nd.sent_start;
	      sent_end = nd.sent_end;
	      para_start = nd.para_start;
	      para_end = nd.para_end;

	      headspans.clear();
	      for(int i=0; i<nd.headspans.size(); i++)
	      {
	    	  headspans.push_back(nd.headspans[i]);
	      }
   }

public:
   void toCDISTreeNode(CDISTreeNode &node) const {
//      node.parent = parent->id;

	   node.is_leaf = is_leaf(); //
	   node.single_child = false; // single or double
	   node.head_left = head_left(); // 0 terminal; 1 single; 2 coordinate; 3 left; 4 right.
	   node.temp = false;
	   // fields for constituents
	   if(is_leaf()) node.constituent = "leaf";
	   else node.constituent = constituent.str();
	   // if constituent tree, false; if discourse tree, true
	   node.type = true;
	//   unsigned long constituent;
	   node.left_child = left_child ? left_child->id : -1;
	   node.right_child = right_child ? right_child->id : -1;
	   // fields for tokens and constituents
	   node.token_start = word_start;
	   node.token_end = word_end;
	   node.head_start = headword_start;
	   node.head_end = headword_end;
   }
};

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce. 
 *
 *==============================================================*/

class CContext;

class CStateItem {
public:
   SCORE_TYPE score;
   CDisNode node;
   const CStateItem *statePtr;
   const CStateItem *stackPtr;
   int current_edu;
   int current_sent;
   int current_para;
   CAction action;

   const std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > *m_sent;
   const std::vector< int > *m_edu_starts;
   const std::vector< int > *m_edu_ends;
   const std::vector< int > *m_edu_sentids;
   const std::vector< int > *m_edu_paraids;
   const std::vector< int > *m_sent_first_edus;
   const std::vector< int > *m_para_first_edus;
   const std::vector< std::vector<const CConNode*> > *m_edu_headspans;
   const std::vector< CConNode > *m_syn_nodes;
   const std::vector< int > *m_syn_roots;
   const std::vector< int > *m_syn_starts;
   const std::vector< int > *m_syn_ends;

   
public:

   CStateItem() : current_edu(0), current_sent(0), current_para(0), score(0), action(),
   stackPtr(0), statePtr(0), node(),
   m_sent(0), m_edu_starts(0), m_edu_ends(0), m_edu_sentids(0),
   m_edu_paraids(0), m_sent_first_edus(0), m_para_first_edus(0),
   m_edu_headspans(0), m_syn_nodes(0), m_syn_roots(0), m_syn_starts(0), m_syn_ends(0){}
   virtual ~CStateItem() {}
public:
   void init(const std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > *sent,
		     const std::vector< int > *edu_starts,
		     const std::vector< int > *edu_ends,
		     const std::vector< int > *edu_sentids,
		     const std::vector< int > *edu_paraids,
		     const std::vector< int > *sent_first_edus,
		     const std::vector< int > *para_first_edus,
		     const std::vector< std::vector<const CConNode*> > *edu_headspans,
		     const std::vector< CConNode > *syn_nodes,
		     const std::vector< int > *syn_roots,
		     const std::vector< int > *syn_starts,
		     const std::vector< int > *syn_ends)
   {
	   m_sent = sent;
	   m_edu_starts = edu_starts;
	   m_edu_ends = edu_ends;
	   m_edu_sentids = edu_sentids;
	   m_edu_paraids = edu_paraids;
	   m_sent_first_edus = sent_first_edus;
	   m_para_first_edus = para_first_edus;
	   m_edu_headspans = edu_headspans;
	   m_syn_nodes = syn_nodes;
	   m_syn_roots = syn_roots;
	   m_syn_starts = syn_starts;
	   m_syn_ends = syn_ends;
   }

   void clear() {
      statePtr = 0;
      stackPtr = 0;
      current_edu = 0;
      current_sent = 0;
      current_para = 0;
      node.clear();
      score = 0;
      action.clear();
   }
   bool empty() const {
      if (current_edu==0) {
         assert(stackPtr == 0 && statePtr == 0 && score==0);
         return true;
      }
      return false;
   }
   unsigned stacksize() const {
      unsigned retval = 0;
      const CStateItem *current = this;
      while (current) {
         if (current->node.valid()) ++retval;// no node -> start/fini
         current = current->stackPtr;
      }
      return retval;
   }

   int newNodeIndex() const { return node.id+1; }

public:
   bool operator < (const CStateItem &st) const { return score < st.score; }
   bool operator > (const CStateItem &st) const { return score > st.score; }
   bool operator == (const CStateItem &st) const {
      THROW("State items are not comparable with each other");
   }
   bool operator != (const CStateItem &st) const { return !( (*this) == st ); }

protected:
   // now this actions MUST BE called by Move
   void shift(CStateItem *retval) const {
      //TRACE("shift");
      assert(!IsTerminated());

      int word_start = (*m_edu_starts)[current_edu];
      if(word_start != node.word_end+1)
      {
    	  std::cout << "look shift !" << std::endl;
      }
      int word_end = (*m_edu_ends)[current_edu];
      CConNode syn_root = (*m_syn_nodes)[(*m_syn_roots)[current_sent]];
      retval->node.set(node.id+1, CDisNode::LEAF, 0, 0, 0, &syn_root, word_start, word_end, current_edu, current_sent, current_para,
    		  word_start, word_end, current_edu, current_edu, current_sent, current_sent, current_para, current_para);
      for(int i=0; i<(*m_edu_headspans)[current_edu].size(); i++)
      {
    	  retval->node.addSpanHeadCFG((*m_edu_headspans)[current_edu][i]);
      }

      retval->current_edu = current_edu+1;
      if((*m_sent)[word_end].tag == 0){
    	  retval->current_sent = current_sent+1;
      }
      else retval->current_sent=current_sent;

      if((*m_sent)[word_end].word == CWord("<P>")){
    	  assert((*m_sent)[word_end].tag == 0);
    	  retval->current_para = current_para+1;
      }
      else retval->current_para=current_para;

      assert( retval->current_edu == (*m_edu_starts).size() || ( (*m_edu_sentids)[retval->current_edu] == retval->current_sent
    		  && (*m_edu_paraids)[retval->current_edu] == retval->current_para ) );


      retval->stackPtr = this; ///  
      assert(!retval->IsTerminated());
   }

   void reduce(CStateItem *retval, const unsigned long &constituent, const bool &head_left) const {
      //TRACE("reduce");
      assert(!IsTerminated());
      const static CDisNode *l, *r;
      assert(stackPtr!=0);
      static unsigned long fullconst;
      assert(stacksize()>=2);
      r = &node;
      l = &(stackPtr->node);
      fullconst = CDisConstituent::encodeTmp(constituent, false);

      retval->node.set(node.id+1, (head_left?CDisNode::HEAD_LEFT:CDisNode::HEAD_RIGHT), fullconst, l, r,
			 (head_left?l->syn_tree:r->syn_tree), (head_left?l->headword_start:r->headword_start),
			 (head_left?l->headword_end:r->headword_end), (head_left?l->headedu_id:r->headedu_id),
			 (head_left?l->headsent_id:r->headsent_id), (head_left?l->headpara_id:r->headpara_id),
			 l->word_start, r->word_end, l->edu_start, r->edu_end, l->sent_start, r->sent_end,
			 l->para_start, r->para_start);
      int maxspan_heads = head_left?l->headspans.size():r->headspans.size();
      for(int i=0; i<maxspan_heads; i++)
      {
		 retval->node.addSpanHeadCFG(head_left?l->headspans[i]:r->headspans[i]);
      }

      retval->stackPtr = stackPtr->stackPtr;
      retval->current_edu = current_edu;
      retval->current_sent = current_sent;
      retval->current_para = current_para;
      assert(!IsTerminated());
   }
   void terminate(CStateItem *retval) const {
      //TRACE("terminate");
//      assert(IsComplete());
      assert(!IsTerminated());
      retval->node = this->node;
      retval->stackPtr=this->stackPtr;
      retval->current_edu = current_edu;
      // compute loss
      assert(retval->IsTerminated());
   }
   void noact(CStateItem *retval) const {
      //TRACE("noact");
      assert(IsTerminated());
      retval->node = this->node;
      retval->stackPtr=this->stackPtr;
      retval->current_edu = current_edu;
      // compute loss
   }

public:

   void NextMove(const CDISTree &snt, CAction &retval) const {
      int s = node.id;
      const CDISTreeNode &nd = snt.dis_nodes[s];
      const CDISTreeNode &hd = snt.dis_nodes[snt.parent(s, false)];
      assert(!hd.constituent.empty()); // so that reduce and reduce_root are not same
      bool single_child;
      bool head_left;
      bool temporary;
      // stack top single child ? reduce unary
         // stack top left child ? shift
	  if (s == hd.left_child) {
		 retval.encodeShift(0); return;
	  }
	  // stack top right child ? reduce bin
	  assert(s==hd.right_child);
	  single_child = false;
	  head_left = hd.head_left;
	  temporary = false;

      retval.encodeReduce(CDisConstituent(hd.constituent).code(), single_child, head_left, temporary);
   }

   void StandardMove(const CDISTree &tr, CAction &retval) const {
      if (IsTerminated()) {
         retval.encodeIdle();
         return;
      }
      // stack empty?shift
      if (stacksize()==0) {
         retval.encodeShift(0);
         return;
      }
      if (tr.parent(node.id, false) == -1) {
         assert(IsComplete(m_edu_starts->size()));
         retval.encodeReduceRoot();
         return;
      }
      NextMove(tr, retval);
   }

   void Move(CStateItem *retval, const CAction &action) const {
      retval->action = action; // this makes it necessary for the actions to 
      retval->statePtr = this; // be called by Move
      if (action.isIdle()) {
         noact(retval);
      }
      else {
         if (action.isShift())
            { shift(retval); }
         else if (action.isReduceRoot())
            { terminate(retval); }
         else
         {
        	 assert(!action.isTemporary());
        	 reduce(retval, action.getConstituent(), action.headLeft());
         }
      }
   }
   
   bool IsComplete(const int &nEdus) const {
      return current_edu == nEdus && stacksize() == 1;
   }

   bool IsTerminated() const {
      return action.type() == CActionType::POP_ROOT or action.type() == CActionType::IDLE; 
   }

   bool IsIdle() const {
      return action.type() == CActionType::IDLE; 
   }

   void GenerateTree(CSentenceParsed &out) const {
      // parsing done?
      assert(IsTerminated());
//      assert(tagged.size()==sent->size());
      out.clear();
      if (stacksize()>1) { WARNING("Parser failed.");return; }
      // generate nodes for out
      static int i,j;
      // first words
      for (i=0; i<m_sent->size(); ++i)
         out.newWord((*m_sent)[i].word.str(), (*m_sent)[i].tag.str());
      //second syn trees;
      for(i=0; i<m_syn_nodes->size();i++)
      {
    	  j = out.newNode(true);
    	  (*m_syn_nodes)[i].toCCONTreeNode(out.syn_nodes[j]);
    	  if((*m_syn_nodes)[i].type == CConNode::LEAF
    	   && (i==0 || (*m_sent)[(*m_syn_nodes)[i].headword-1].tag==0))
    	   {
    		  out.syn_starts.push_back(j);
    	   }
      }
      for(i=0; i<m_syn_roots->size(); i++)
      {
    	  out.syn_roots.push_back((*m_syn_roots)[i]);
    	  out.syn_ends.push_back((*m_syn_roots)[i]);
      }
      // second constituents
      static const CDisNode* nodes[MAX_SENTENCE_SIZE*(2+UNARY_MOVES)+2];
      static int count;
      count = 0;
      const static CStateItem *current;
      current = this;
      while (current) {
         if (!current->IsTerminated() && current->node.valid()) {
            nodes[count] = &current->node;
            ++count; 
         }
         current = current->statePtr;
      }

      for (i=count-1; i>=0; --i) {
         j = out.newNode(false);
         // copy node
         assert(j==nodes[i]->id);
         nodes[i]->toCDISTreeNode(out.dis_nodes[j]);
      }
      out.dis_root = nodes[0]->id;
   }


   //===============================================================================

   void trace() const {
      static const CStateItem* states[MAX_SENTENCE_SIZE*(2+UNARY_MOVES)+2];
      static int count;
      const static CStateItem *current;
      count = 0;
      current = this;
      while (current->statePtr) {
         states[count] = current;
         ++count ; //updating
         current = current->statePtr;
      }
      TRACE("State item score == " << score);
      TRACE("State item size == " << stacksize());
      --count;
      while (count>=0) {
         TRACE(states[count]->action.str());
         --count;
      }
      TRACE("");
   }

   static const CConNode* first_maxsynleftspan(const CConNode *node, int start_token, int end_token,  int &result_head, int &result_cfg, int &right_token)
   {
	   result_head = right_token = -1;
	   if(node->word_start > start_token)
	   {
		   return 0;
	   }
	   else if(node->headword >= start_token && node->headword <= end_token)
	   {
		   result_head = node->headword;
		   result_cfg = node->constituent.code();
		   right_token = node->word_end;
		   return node;
	   }
	   else
	   {
		   if(node->word_start == start_token && node->word_end < end_token)
		   {
			   result_head = node->headword;
			   result_cfg = node->constituent.code();
			   right_token = node->word_end;
			   return node;
		   }
		   else if(node->word_start == start_token && node->word_end > end_token)
		   {
			   return first_maxsynleftspan(node->left_child, start_token, end_token, result_head, result_cfg, right_token);
		   }
		   else if(node->word_start < start_token)
		   {
			   if(node->type > CConNode::SINGLE_CHILD)
			   {
				   const CConNode* right_result = first_maxsynleftspan(node->right_child, start_token, end_token, result_head, result_cfg, right_token);
				   if(right_result!=0) return right_result;
			   }
			   return first_maxsynleftspan(node->left_child, start_token, end_token, result_head, result_cfg, right_token);
		   }
	   }

	   return 0;
   }
};

/*===============================================================
 *
 * scored actions
 *
 *==============================================================*/

class CScoredStateAction {

public:
   CAction action;
   const CStateItem *item;
   SCORE_TYPE score;

public:
   CScoredStateAction() : item(0), action(), score(0) {}
   void load(const CAction &action, const CStateItem *item, const SCORE_TYPE &score) {
      SCORE_TYPE item_sc;
      this->action = action; 
      this->item = item;
      item_sc = item->score;
      this->score = item_sc + score;
   }

public:
   bool operator < (const CScoredStateAction &a1) const { return score < a1.score; }
   bool operator > (const CScoredStateAction &a1) const { return score > a1.score; }
   bool operator <= (const CScoredStateAction &a1) const { return score <= a1.score; }
   bool operator >= (const CScoredStateAction &a1) const { return score >= a1.score; }

};

#endif
