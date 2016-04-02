// Copyright (C) SUTD 2015
#ifndef _ENGLISH_DEPSEM_STATEITEM
#define _ENGLISH_DEPSEM_STATEITEM

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce. 
 *
 * Note about members: there are two types of item properties;
 * The first is the stack, which changes during the process; 
 * The second is the incoming sentence, including m_lHeads, 
 * m_lDepsL and m_lDepsR, m_lDepNumL, m_lDepNumR etc, which 
 * records the properties of each input word so far.
 *
 * A state item is partial and do not include information about
 * all words from the input sentence. Though m_lHeads, m_lDepsL 
 * and m_lDepsR are fixed arrays with MAX_SENTENCE_SIZE length, 
 * not all the elements from the arrays are used. The ACTIVE 
 * elements are from the input index 0 to m_nNextWord, inclusive. 
 * And a state item only captures information about the active 
 * sub section from input.
 *
 * The property for each input word need to be initialised. 
 * m_lHeads m_lDepsL etc could be initialised within the 
 * clear() method. However, because the parsing process is
 * incremental, they can also be initialised lasily. 
 * Apart from the avoidance of unecessary assignments, one 
 * benefit of lazy initialisation is that we only need to copy
 * the active indexies when doing a copy operation. Therefore, 
 * this implementation takes the approach. 
 * The initialisation of these values are in clear(), shift()
 * and arcright()
 *
 *==============================================================*/

class CStateItem {

public:
   enum STACK_STATUS { OFF_STACK=0, ON_STACK_SHIFT, ON_STACK_ARCRIGHT } ;

protected:
   std::vector<int> m_Stack;                     // stack of words that are currently processed
   std::vector<int> m_HeadStack;
   int m_nNextWord;                         // index for the next word
   int m_lHeads[MAX_SENTENCE_SIZE];         // the lexical head for each word
   int m_lDepsL[MAX_SENTENCE_SIZE];         // the leftmost dependency for each word (just for cache, temporary info)
   int m_lDepsR[MAX_SENTENCE_SIZE];         // the rightmost dependency for each word (just for cache, temporary info)
   int m_lDepNumL[MAX_SENTENCE_SIZE];       // the number of left dependencies
   int m_lDepNumR[MAX_SENTENCE_SIZE];       // the number of right dependencies
   CSetOfTags<CDependencyLabel> m_lDepSynTagL[MAX_SENTENCE_SIZE]; // the set of left syn tags
   CSetOfTags<CDependencyLabel> m_lDepSynTagR[MAX_SENTENCE_SIZE]; // the set of right syn tags
   CSetOfTags<CSemanticLabel> m_lDepSemTagL[MAX_SENTENCE_SIZE]; // the set of left sem tags
   CSetOfTags<CSemanticLabel> m_lDepSemTagR[MAX_SENTENCE_SIZE]; // the set of right sem tags
   int m_lSibling[MAX_SENTENCE_SIZE];       // the sibling towards head
   unsigned long m_lSynLabels[MAX_SENTENCE_SIZE];   // the syn label of each dependency link
   unsigned long m_lSemLabels[MAX_SENTENCE_SIZE];   // the sem label of each dependency link
   unsigned long m_nLastAction;                  // the last stack action
   const std::vector < CTaggedWord<CTag, TAG_SEPARATOR> >* m_lCache;

public:
   SCORE_TYPE score;                        // score of stack - predicting how potentially this is the correct one

public:
   // constructors and destructor
   CStateItem(const std::vector < CTaggedWord<CTag, TAG_SEPARATOR> >*cache=0) : m_lCache(cache) { clear(); }
   ~CStateItem() { }
   CStateItem(CStateItem& item) : m_lCache(0) { std::cerr<<"CStateItem does not support copy constructor!"; std::cerr.flush(); assert(1==0); }

public:
   // comparison
   inline bool operator < (const CStateItem &item) const { return score < item.score; }
   inline bool operator > (const CStateItem &item) const { return score > item.score; }
   inline bool operator == (const CStateItem &item) const {
      int i;
      if ( m_nNextWord != item.m_nNextWord )
         return false;
      for ( i=0; i<m_nNextWord; ++i ) {
         if ( m_lHeads[i] != item.m_lHeads[i] )
            return false;
      }
      for ( i=0; i<m_nNextWord; ++i ) 
      {
         if ( m_lSynLabels[i] != item.m_lSynLabels[i] )
            return false;
         if ( m_lSemLabels[i] != item.m_lSemLabels[i] )
            return false;
      }
      if ( m_Stack.size() != item.m_Stack.size() )
         return false;
      if ( m_Stack.size()>0 && m_Stack.back()!=item.m_Stack.back() )
         return false;
      // I think that the stacks don't have to be compared
      // might be proved by translating tree to stack
      assert( m_Stack == item.m_Stack );
      assert( m_HeadStack == item.m_HeadStack );
      return true;
   }
   inline bool operator != (const CStateItem &item) const {
      return ! ((*this)==item);
   }

   // propty
   inline int stacksize() const { return m_Stack.size(); }
   inline bool stackempty() const { return m_Stack.empty(); }
   inline int stacktop() const { assert(!m_Stack.empty()); return m_Stack.back(); }
   inline int stackbottom() const { assert(!m_Stack.empty()); return m_Stack.front(); }
   inline int stackitem( const unsigned &index ) const { assert(index<m_Stack.size()); return m_Stack[index]; }

   inline bool headstackempty() const { return m_HeadStack.empty(); }
   inline int headstacktop() const { assert(!m_HeadStack.empty()); return m_HeadStack.back(); }
   inline int headstackitem( const unsigned &index ) const { assert(index<m_HeadStack.size()); return m_HeadStack[index]; }
   inline int headstacksize() const { return m_HeadStack.size(); }

   inline bool afterreduce() const { 
      return action::getUnlabeledAction(m_nLastAction)==action::REDUCE;
   }

   inline int head( const int &index ) const { assert(index<=m_nNextWord); return m_lHeads[index]; }
   inline int leftdep( const int &index ) const { assert(index<=m_nNextWord); return m_lDepsL[index]; }
   inline int rightdep( const int &index ) const { assert(index<=m_nNextWord); return m_lDepsR[index]; }
   inline int sibling( const int &index ) const { assert(index<=m_nNextWord); return m_lSibling[index]; }
   inline int size( ) const { return m_nNextWord ; }
   inline int synlabel( const int &index ) const { assert(index<=m_nNextWord); return m_lSynLabels[index]; }
   inline int semlabel( const int &index ) const { assert(index<=m_nNextWord); return m_lSemLabels[index]; }

   inline int leftarity( const int &index ) const { assert(index<=m_nNextWord); return m_lDepNumL[index]; }
   inline int rightarity( const int &index ) const { assert(index<=m_nNextWord); return m_lDepNumR[index]; }

   inline const CSetOfTags<CDependencyLabel> &leftsyntagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepSynTagL[index]; }
   inline const CSetOfTags<CDependencyLabel> &rightsyntagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepSynTagR[index]; }

   inline const CSetOfTags<CSemanticLabel> &leftsemtagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepSemTagL[index]; }
   inline const CSetOfTags<CSemanticLabel> &rightsemtagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepSemTagR[index]; }

   void clear() { 
      m_nNextWord = 0; m_Stack.clear(); m_HeadStack.clear(); 
      score = 0; 
      m_nLastAction = action::NO_ACTION;
      ClearNext();
   }

   void operator = ( const CStateItem &item ) {
      m_Stack = item.m_Stack;
      m_HeadStack = item.m_HeadStack;
      m_nNextWord = item.m_nNextWord;
      m_nLastAction = item.m_nLastAction;
      m_lCache = item.m_lCache;
      score = item.score; 
      for ( int i=0; i<=m_nNextWord; ++i ){ // only copy active word (including m_nNext)
         m_lHeads[i] = item.m_lHeads[i];  
         m_lDepsL[i] = item.m_lDepsL[i]; 
         m_lDepsR[i] = item.m_lDepsR[i];
         m_lDepNumL[i] = item.m_lDepNumL[i];
         m_lDepNumR[i] = item.m_lDepNumR[i];
         m_lDepSynTagL[i] = item.m_lDepSynTagL[i];
         m_lDepSynTagR[i] = item.m_lDepSynTagR[i];
         m_lDepSemTagL[i] = item.m_lDepSemTagL[i];
         m_lDepSemTagR[i] = item.m_lDepSemTagR[i];
         m_lSibling[i] = item.m_lSibling[i];
         m_lSynLabels[i] = item.m_lSynLabels[i];
         m_lSemLabels[i] = item.m_lSemLabels[i];
      }
   }

//-----------------------------------------------------------------------------

public:
   // the arc left action links the current stack top to the next word with popping
   void ArcLeft(unsigned long synlab, unsigned long semlab) {
      assert( m_Stack.size() > 0 ) ;
      assert( m_lHeads[m_Stack.back()] == DEPENDENCY_LINK_NO_HEAD ) ;
      static int left ;
      left = m_Stack.back() ;
      m_Stack.pop_back() ;
      m_HeadStack.pop_back() ;
      m_lHeads[left] = m_nNextWord;
      m_lSynLabels[left] = synlab;
      m_lSemLabels[left] = semlab;
      m_lDepSynTagL[m_nNextWord].add(synlab) ;
      m_lDepSemTagL[m_nNextWord].add(semlab) ;
      m_lSibling[left] = m_lDepsL[m_nNextWord];
      m_lDepsL[m_nNextWord] = left ;
      m_lDepNumL[m_nNextWord] ++ ;
      m_nLastAction=action::encodeAction(action::ARC_LEFT, synlab, semlab);
   }

   // the arc right action links the next word to the current stack top with pushing

   void ArcRight(unsigned long synlab, unsigned long semlab) {
      assert( m_Stack.size() > 0 ) ;
      static int left ;
      left = m_Stack.back() ;
      m_Stack.push_back( m_nNextWord ) ;
      m_lHeads[m_nNextWord] = left ;
      m_lSynLabels[m_nNextWord] = synlab ;
      m_lSemLabels[m_nNextWord] = semlab ;
      m_lDepSynTagR[left].add(synlab) ;
      m_lDepSemTagR[left].add(semlab) ;
      m_lSibling[m_nNextWord] = m_lDepsR[left];
      m_lDepsR[left] = m_nNextWord ;
      m_lDepNumR[left] ++ ;
      m_nNextWord ++;
      ClearNext();
      m_nLastAction=action::encodeAction(action::ARC_RIGHT, synlab, semlab);
   }

   // the shift action does pushing
   void Shift() {
      m_Stack.push_back( m_nNextWord );
      m_HeadStack.push_back( m_nNextWord );
      m_nNextWord ++ ;
      ClearNext();
      m_nLastAction=action::encodeAction(action::SHIFT);
   }
 
   // the reduce action does popping
   void Reduce() {
      assert( m_lHeads[m_Stack.back()] != DEPENDENCY_LINK_NO_HEAD ) ;
      m_Stack.pop_back() ;
      m_nLastAction=action::encodeAction(action::REDUCE);
   }

   // this is used for the convenience of scoring and updating
   void PopRoot() {
#ifndef FRAGMENTED_TREE
      assert( m_Stack.size() == 1 && m_lHeads[m_Stack.back()] == DEPENDENCY_LINK_NO_HEAD ) ; // make sure only one root item in stack 
#else
      assert( m_lHeads[m_Stack.back()] == DEPENDENCY_LINK_NO_HEAD ) ;
#endif
      m_lSynLabels[m_Stack.back()] = CDependencyLabel::ROOT;
      m_lSemLabels[m_Stack.back()] = CSemanticLabel::ROOT;
      m_nLastAction = action::encodeAction(action::POP_ROOT);
      m_Stack.pop_back() ; // pop it
   }

   // the clear next action is used to clear the next word, used with forwarding the next word index
   void ClearNext() {
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsL[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord] = 0 ;
      m_lDepSynTagL[m_nNextWord].clear() ;
      m_lDepSemTagL[m_nNextWord].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lDepSynTagR[m_nNextWord].clear() ;
      m_lDepSemTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lSynLabels[m_nNextWord] = CDependencyLabel::NONE;
      m_lSemLabels[m_nNextWord] = CSemanticLabel::NONE;
   }

   // the move action is a simple call to do action according to the action code
   void Move ( const unsigned long &ac ) {

      switch (action::getUnlabeledAction(ac)) {
      case action::NO_ACTION:
         return;
      case action::SHIFT:
         Shift();
         return;
      case action::REDUCE:
         Reduce();
         return;
      case action::ARC_LEFT:
         ArcLeft(action::getSynLabel(ac), action::getSemLabel(ac));
         return;
      case action::ARC_RIGHT:
         ArcRight(action::getSynLabel(ac), action::getSemLabel(ac));
         return;
      case action::POP_ROOT:
         PopRoot();
         return;
      default:
         THROW("unknown action: " << ac << '.');
      }
   }

//-----------------------------------------------------------------------------

public:
   unsigned long StandardMoveStep( const CDependencyParse &tree, const std::vector<CDependencyLabel>&m_lCacheLabel, const std::vector<CSemanticLabel>&m_lCacheSemLabel) {
      static int top;
      // when the next word is tree.size() it means that the sentence is done already
      if ( m_nNextWord == static_cast<int>(tree.size()) ) {
         assert( m_Stack.size() > 0 );
         if ( m_Stack.size() > 1 ) {
        	return action::REDUCE;
         }
         else {
            return action::POP_ROOT;
         }
      }
      // the first case is that there is some words on the stack linking to nextword
      if ( m_Stack.size() > 0 ) {
         top = m_Stack.back();
         while ( !(m_lHeads[top] == DEPENDENCY_LINK_NO_HEAD) )
            top = m_lHeads[top];
         if ( tree[top].head == m_nNextWord ) {    // if a local head deps on nextword first
            if ( top == m_Stack.back() ) {
               assert(m_lCacheLabel[top].str() == tree[top].synlabel && m_lCacheSemLabel[top].str() == tree[top].semlabel);
               return action::encodeAction(action::ARC_LEFT, m_lCacheLabel[top].code(), m_lCacheSemLabel[top].code());// link it to the next word
            }
            else {
               return action::REDUCE;
            }
         }
      }
      // the second case is that no words on the stack links nextword, and nextword does not link to stack word
      if ( tree[m_nNextWord].head == DEPENDENCY_LINK_NO_HEAD || // the root or
           tree[m_nNextWord].head > m_nNextWord ) { // head on the right
         return action::SHIFT;
      }
      // the last case is that the next words links to stack word
      else {                                        // head on the left 
         assert( m_Stack.size() > 0 );
         top = m_Stack.back(); 
         if ( tree[m_nNextWord].head == top ) {     // the next word deps on stack top
            assert(m_lCacheLabel[m_nNextWord].str()==tree[m_nNextWord].synlabel && m_lCacheSemLabel[m_nNextWord].str()==tree[m_nNextWord].semlabel);
            return action::encodeAction(action::ARC_RIGHT, m_lCacheLabel[m_nNextWord].code(), m_lCacheSemLabel[m_nNextWord].code());
         }
         else {                                     // must depend on non-immediate h
            return action::REDUCE;
         }
      }
   }


   // returns true is the next word advances -- by shift or arcright.
   bool GetStandardMoveActions( const CDependencyParse &tree, const std::vector<CDependencyLabel>&m_lCacheLabel, unsigned long &start_action, unsigned long &end_action) const
   {
      static int top;
      // when the next word is tree.size() it means that the sentence is done already
      if ( m_nNextWord == static_cast<int>(tree.size()) ) {
         assert( m_Stack.size() > 0 );
         if ( m_Stack.size() > 1 ) {
        	 start_action = end_action = action::REDUCE;
        	 return false;
         }
         else {
        	 start_action = end_action = action::POP_ROOT;
        	 return false;
         }
      }
      // the first case is that there is some words on the stack linking to nextword
      if ( m_Stack.size() > 0 ) {
         top = m_Stack.back();
         while ( !(m_lHeads[top] == DEPENDENCY_LINK_NO_HEAD) )
            top = m_lHeads[top];
         if ( tree[top].head == m_nNextWord ) {    // if a local head deps on nextword first
            if ( top == m_Stack.back() ) {
               assert(m_lCacheLabel[top].str() == tree[top].synlabel);
               start_action = action::encodeAction(action::ARC_LEFT, m_lCacheLabel[top].code(), CSemanticLabel::FIRST);
               end_action = action::encodeAction(action::ARC_LEFT, m_lCacheLabel[top].code(), CSemanticLabel::COUNT-1);
               return false;// link it to the next word
            }
            else {
           	 start_action = end_action = action::REDUCE;
           	 return false;
            }
         }
      }
      // the second case is that no words on the stack links nextword, and nextword does not link to stack word
      if ( tree[m_nNextWord].head == DEPENDENCY_LINK_NO_HEAD || // the root or
           tree[m_nNextWord].head > m_nNextWord ) { // head on the right
    	  start_action = end_action = action::SHIFT;
    	  return true;
      }
      // the last case is that the next words links to stack word
      else {                                        // head on the left
         assert( m_Stack.size() > 0 );
         top = m_Stack.back();
         if ( tree[m_nNextWord].head == top ) {     // the next word deps on stack top
            assert(m_lCacheLabel[m_nNextWord].str()==tree[m_nNextWord].synlabel);
            start_action = action::encodeAction(action::ARC_RIGHT, m_lCacheLabel[m_nNextWord].code(), CSemanticLabel::FIRST);
            end_action = action::encodeAction(action::ARC_RIGHT, m_lCacheLabel[m_nNextWord].code(), CSemanticLabel::COUNT-1);
            return false;
         }
         else {                                     // must depend on non-immediate h
           	 start_action = end_action = action::REDUCE;
           	 return false;
         }
      }
   }

   // we want to pop the root item after the whole tree done
   // on the one hand this seems more natural
   // on the other it is easier to score
   void StandardFinish() {
      if( m_Stack.size() != 0 )
      {
    	  assert(0);
      }
   }

   unsigned FollowMove( const CStateItem *item ) {
      static int top;
      // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
      if ( m_nNextWord == item->m_nNextWord ) {
         assert( m_Stack.size() > item->m_Stack.size() );
         top = m_Stack.back();
         if ( item->m_lHeads[top] == m_nNextWord ) 
            return action::encodeAction(action::ARC_LEFT, item->m_lSynLabels[top], item->m_lSemLabels[top]);
         else if ( item->m_lHeads[top] != DEPENDENCY_LINK_NO_HEAD ) 
            return action::encodeAction(action::REDUCE);
         else 
            return action::encodeAction(action::POP_ROOT);
      }
      // the first case is that there is some words on the stack linking to nextword
      if ( m_Stack.size() > 0 ) {
         top = m_Stack.back();
         while ( !(m_lHeads[top] == DEPENDENCY_LINK_NO_HEAD) )
            top = m_lHeads[top];
         if ( item->head(top) == m_nNextWord ) {    // if a local head deps on nextword first
            if ( top == m_Stack.back() ) {
               return action::encodeAction(action::ARC_LEFT, item->m_lSynLabels[top], item->m_lSemLabels[top]);
            }
            else {
               return action::encodeAction(action::REDUCE);
            }
         }
      }
      // the second case is that no words on the stack links nextword, and nextword does not link to stack word
      if ( item->head(m_nNextWord) == DEPENDENCY_LINK_NO_HEAD || // the root or
           item->head(m_nNextWord) > m_nNextWord ) { // head on the right
         return action::encodeAction(action::SHIFT);
      }
      // the last case is that the next words links to stack word
      else {                                        // head on the left 
         assert( m_Stack.size() > 0 );
         top = m_Stack.back(); 
         if ( item->head(m_nNextWord) == top ) {    // the next word deps on stack top
            return action::encodeAction(action::ARC_RIGHT, item->m_lSynLabels[m_nNextWord], item->m_lSemLabels[m_nNextWord]);
         }
         else {                                     // must depend on non-immediate h
            return action::encodeAction(action::REDUCE);
         }
      }
   }

   void GenerateTree( const CTwoStringVector &input, CDependencyParse &output ) const {
      output.clear();
      for ( int i=0; i<size(); ++i ) 
         output.push_back( CSemanticDependencyTreeNode( input.at(i).first , input.at(i).second , m_lHeads[i] , CDependencyLabel(m_lSynLabels[i]).str(), CSemanticLabel(m_lSemLabels[i]).str()) ) ;
   }




};

#endif
