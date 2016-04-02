// Copyright (C) University of Oxford 2010
#ifndef _ENGLISH_DEPENDENCY_PARSER_STATEITEM
#define _ENGLISH_DEPENDENCY_PARSER_STATEITEM

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
   int m_nActionNum[2];
   std::vector<int> m_Stack[2];                     // stack of words that are currently processed
   std::vector<int> m_HeadStack[2];
   int m_nNextWord[2];                         // index for the next word
   int m_lHeads[2][MAX_SENTENCE_SIZE];         // the lexical head for each word
   int m_lDepsL[2][MAX_SENTENCE_SIZE];         // the leftmost dependency for each word (just for cache, temporary info)
   int m_lDepsR[2][MAX_SENTENCE_SIZE];         // the rightmost dependency for each word (just for cache, temporary info)
   int m_lDepNumL[2][MAX_SENTENCE_SIZE];       // the number of left dependencies
   int m_lDepNumR[2][MAX_SENTENCE_SIZE];       // the number of right dependencies
   CSetOfTags<CDependencyLabel> m_lDepTagL[2][MAX_SENTENCE_SIZE]; // the set of left tags
   CSetOfTags<CDependencyLabel> m_lDepTagR[2][MAX_SENTENCE_SIZE]; // the set of right tags
   int m_lSibling[2][MAX_SENTENCE_SIZE];       // the sibling towards head
#ifdef LABELED
   unsigned long m_lLabels[2][MAX_SENTENCE_SIZE];   // the label of each dependency link
#endif
   unsigned long m_nLastAction[2];                  // the last stack action
   unsigned long m_nActions[2][2*MAX_SENTENCE_SIZE+1];                  // the last stack action
   const std::vector < CTaggedWord<CTag, TAG_SEPARATOR> >* m_lCache;
   unsigned long last_action_index;

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
      if (last_action_index != item.last_action_index)
      {
          return false;
      }

    for(int index = 0; index < 2; index++)
    {
          int i;
          if ( m_nActionNum[index] != item.m_nActionNum[index] )
             return false;
          for ( i=0; i<m_nActionNum[index]; ++i ) {
             if ( m_nActions[index][i] != item.m_nActions[index][i] )
                return false;
          }
          if ( m_nNextWord[index] != item.m_nNextWord[index] )
             return false;
          for ( i=0; i<m_nNextWord[index]; ++i ) {
             if ( m_lHeads[index][i] != item.m_lHeads[index][i] )
                return false;
          }
    #ifdef LABELED
          for ( i=0; i<m_nNextWord[index]; ++i )
             if ( m_lLabels[index][i] != item.m_lLabels[index][i] )
                return false;
    #endif
          if ( m_Stack[index].size() != item.m_Stack[index].size() )
             return false;
          if ( m_Stack[index].size()>0 && m_Stack[index].back()!=item.m_Stack[index].back() )
             return false;
          // I think that the stacks don't have to be compared
          // might be proved by translating tree to stack
          assert( m_Stack[index] == item.m_Stack[index] );
          assert( m_HeadStack[index] == item.m_HeadStack[index] );
    }
      return true;
   }


   inline bool operator != (const CStateItem &item) const {
      return ! ((*this)==item);
   }



   inline int nextactionindex() const {
       if(max_1_advance_2 > 0)
       {
          int index = 0;
          if(m_nActionNum[1] <= m_nActionNum[0] - max_1_advance_2 || terminated(0))
          {
              index = 1;
          }

          return index;
       }
       else
       {
           int index = 1;
           if(m_nActionNum[0] <= m_nActionNum[1] + max_1_advance_2 || terminated(1))
           {
               index = 0;
           }

           return index;
       }


   }

   // propty current processing
   inline int stacksize() const {int idx = nextactionindex(); return stacksize(idx); }
   inline bool stackempty() const {int idx = nextactionindex(); return stackempty(idx); }
   inline int stacktop() const {int idx = nextactionindex();  return stacktop(idx); }
   inline int stackbottom() const {int idx = nextactionindex(); return stackbottom(idx); }
   inline int stackitem( const unsigned &index ) const {int idx = nextactionindex(); return stackitem(idx, index); }

   inline bool headstackempty() const {int idx = nextactionindex(); return headstackempty(idx); }
   inline int headstacktop() const {int idx = nextactionindex(); return headstacktop(idx); }
   inline int headstackitem( const unsigned &index ) const {int idx = nextactionindex();  return headstackitem(idx,index); }
   inline int headstacksize() const {int idx = nextactionindex(); return headstacksize(idx); }

   inline bool afterreduce() const {
       int idx = nextactionindex();
      return afterreduce(idx);
}

   inline int head( const int &index ) const {int idx = nextactionindex();  return head(idx,index); }
   inline int leftdep( const int &index ) const {int idx = nextactionindex();  return leftdep(idx,index); }
   inline int rightdep( const int &index ) const {int idx = nextactionindex();  return rightdep(idx,index); }
   inline int sibling( const int &index ) const {int idx = nextactionindex();  return sibling(idx,index); }
   inline int size( ) const {int idx = nextactionindex(); return size(idx) ; }
#ifdef LABELED
   inline int label( const int &index ) const {int idx = nextactionindex(); return label(idx,index); }
#endif

   inline int leftarity( const int &index ) const {int idx = nextactionindex(); return leftarity(idx,index); }
   inline int rightarity( const int &index ) const {int idx = nextactionindex(); return rightarity(idx,index); }

   inline const CSetOfTags<CDependencyLabel> &lefttagset( const int &index ) const {int idx = nextactionindex(); return lefttagset(idx,index); }
   inline const CSetOfTags<CDependencyLabel> &righttagset( const int &index ) const {int idx = nextactionindex(); return righttagset(idx,index); }


   // propty other scheme
   inline int stacksize_another() const {int idx = nextactionindex(); return stacksize(1-idx); }
   inline bool stackempty_another() const {int idx = nextactionindex(); return stackempty(1-idx); }
   inline int stacktop_another() const {int idx = nextactionindex();  return stacktop(1-idx); }
   inline int stackbottom_another() const {int idx = nextactionindex(); return stackbottom(1-idx); }
   inline int stackitem_another( const unsigned &index ) const {int idx = nextactionindex(); return stackitem(1-idx, index); }

   inline bool headstackempty_another() const {int idx = nextactionindex(); return headstackempty(1-idx); }
   inline int headstacktop_another() const {int idx = nextactionindex(); return headstacktop(1-idx); }
   inline int headstackitem_another( const unsigned &index ) const {int idx = nextactionindex();  return headstackitem(1-idx,index); }
   inline int headstacksize_another() const {int idx = nextactionindex(); return headstacksize(1-idx); }

   inline bool afterreduce_another() const {
       int idx = nextactionindex();
      return afterreduce(1-idx);
}

   inline int head_another( const int &index ) const {int idx = nextactionindex();  return head(1-idx,index); }
   inline int leftdep_another( const int &index ) const {int idx = nextactionindex();  return leftdep(1-idx,index); }
   inline int rightdep_another( const int &index ) const {int idx = nextactionindex();  return rightdep(1-idx,index); }
   inline int sibling_another( const int &index ) const {int idx = nextactionindex();  return sibling(1-idx,index); }
   inline int size_another( ) const {int idx = nextactionindex(); return size(1-idx) ; }
#ifdef LABELED
   inline int label_another( const int &index ) const {int idx = nextactionindex(); return label(1-idx,index); }
#endif

   inline int leftarity_another( const int &index ) const {int idx = nextactionindex(); return leftarity(1-idx,index); }
   inline int rightarity_another( const int &index ) const {int idx = nextactionindex(); return rightarity(1-idx,index); }

   inline const CSetOfTags<CDependencyLabel> &lefttagset_another( const int &index ) const {int idx = nextactionindex(); return lefttagset(1-idx,index); }
   inline const CSetOfTags<CDependencyLabel> &righttagset_another( const int &index ) const {int idx = nextactionindex(); return righttagset(1-idx,index); }



   inline int stacksize(const int &idx) const { return m_Stack[idx].size(); }
   inline bool stackempty(const int &idx) const { return m_Stack[idx].empty(); }
   inline int stacktop(const int &idx) const { assert(!m_Stack[idx].empty()); return m_Stack[idx].back(); }
   inline int stackbottom(const int &idx) const { assert(!m_Stack[idx].empty()); return m_Stack[idx].front(); }
   inline int stackitem(const int &idx, const unsigned &index ) const { assert(index<m_Stack[idx].size()); return m_Stack[idx][index]; }

   inline bool headstackempty(const int &idx) const { return m_HeadStack[idx].empty(); }
   inline int headstacktop(const int &idx) const { assert(!m_HeadStack[idx].empty()); return m_HeadStack[idx].back(); }
   inline int headstackitem(const int &idx, const unsigned &index ) const { assert(index<m_HeadStack[idx].size()); return m_HeadStack[idx][index]; }
   inline int headstacksize(const int &idx) const { return m_HeadStack[idx].size(); }

   inline bool afterreduce(const int &idx) const {
#ifdef LABELED
       if(idx == 0)
       {
           return action::getUnlabeledAction(m_nLastAction[idx])==action::REDUCE0;
       }
       else
       {
           return action::getUnlabeledAction(m_nLastAction[idx])==action::REDUCE1;
       }
#else
       if(idx == 0)
       {
           return m_nLastAction[idx]==action::REDUCE0;
       }
       else
       {
           return m_nLastAction[idx]==action::REDUCE1;
       }
#endif
}

   inline int head(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lHeads[idx][index]; }
   inline int leftdep(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepsL[idx][index]; }
   inline int rightdep(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepsR[idx][index]; }
   inline int sibling(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lSibling[idx][index]; }
   inline int size(const int &idx ) const { return m_nNextWord[idx] ; }
#ifdef LABELED
   inline int label(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lLabels[idx][index]; }
#endif

   inline int leftarity(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepNumL[idx][index]; }
   inline int rightarity(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepNumR[idx][index]; }

   inline const CSetOfTags<CDependencyLabel> &lefttagset(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepTagL[idx][index]; }
   inline const CSetOfTags<CDependencyLabel> &righttagset(const int &idx, const int &index ) const { assert(index<=m_nNextWord[idx]); return m_lDepTagR[idx][index]; }

   void clear() { 
      m_nNextWord[0] = 0; m_Stack[0].clear(); m_HeadStack[0].clear();
      m_nNextWord[1] = 0; m_Stack[1].clear(); m_HeadStack[1].clear();
      score = 0; 
      m_nLastAction[0] = action::NO_ACTION;
      m_nLastAction[1] = action::NO_ACTION;
      m_nActionNum[0] = 0;
      m_nActionNum[1] = 0;
      m_nActions[0][0] = action::NO_ACTION;
      m_nActions[1][0] = action::NO_ACTION;
      last_action_index = 0;
      ClearNext();
   }

   void operator = ( const CStateItem &item ) {
       m_lCache = item.m_lCache;
       score = item.score;
       last_action_index = item.last_action_index;
       for(int idx = 0; idx < 2; idx++)
       {
          m_Stack[idx] = item.m_Stack[idx];
          m_nActionNum[idx] = item.m_nActionNum[idx];
          m_HeadStack[idx] = item.m_HeadStack[idx];
          m_nNextWord[idx] = item.m_nNextWord[idx];
          m_nLastAction[idx] = item.m_nLastAction[idx];
          for ( int i=0; i<=m_nNextWord[idx]; ++i ){ // only copy active word (including m_nNext)
             m_lHeads[idx][i] = item.m_lHeads[idx][i];
             m_lDepsL[idx][i] = item.m_lDepsL[idx][i];
             m_lDepsR[idx][i] = item.m_lDepsR[idx][i];
             m_lDepNumL[idx][i] = item.m_lDepNumL[idx][i];
             m_lDepNumR[idx][i] = item.m_lDepNumR[idx][i];
             m_lDepTagL[idx][i] = item.m_lDepTagL[idx][i];
             m_lDepTagR[idx][i] = item.m_lDepTagR[idx][i];
             m_lSibling[idx][i] = item.m_lSibling[idx][i];
    #ifdef LABELED
             m_lLabels[idx][i] = item.m_lLabels[idx][i];
    #endif
          }
          for ( int i=0; i<=m_nActionNum[idx]; ++i ){ // only copy active word (including m_nNext)
              m_nActions[idx][i] = item.m_nActions[idx][i];
          }
       }
   }

   inline bool terminated() const {
     return (m_nLastAction[0] == action::POP_ROOT0 && m_nLastAction[1] == action::POP_ROOT1
             && m_Stack[0].empty() && m_Stack[1].empty());
   }

   inline bool terminated(int index) const {
       if(index == 0)
       {
           return (m_nLastAction[0] == action::POP_ROOT0
                   && m_Stack[0].empty());
       }
       else
       {
           return (m_nLastAction[1] == action::POP_ROOT1
                   && m_Stack[1].empty());
       }
   }

//-----------------------------------------------------------------------------

public:
   // the arc left action links the current stack top to the next word with popping
#ifdef LABELED
   void ArcLeft(int index, unsigned long lab) {
#else
   void ArcLeft(int index) {
#endif
      if( m_Stack[index].size() == 0 )
      {
          std::cout << *this << std::endl;
          std::cout << "ArcLeft:" << m_Stack[index].size()  << std::endl;
      }
      assert( m_lHeads[index][m_Stack[index].back()] == DEPENDENCY_LINK_NO_HEAD ) ;
      static int left ;
      left = m_Stack[index].back() ;
      m_Stack[index].pop_back() ;
      m_HeadStack[index].pop_back() ;
      m_lHeads[index][left] = m_nNextWord[index];
#ifdef LABELED
      m_lLabels[index][left] = lab;
      m_lDepTagL[index][m_nNextWord[index]].add(lab) ;
#endif
      m_lSibling[index][left] = m_lDepsL[index][m_nNextWord[index]];
      m_lDepsL[index][m_nNextWord[index]] = left ;
      m_lDepNumL[index][m_nNextWord[index]] ++ ;
      m_nActionNum[index]++;
      last_action_index = index;
#ifdef LABELED
      m_nLastAction[index]=action::encodeAction(action::ARC_LEFT, lab);
#else
      m_nLastAction[index]=action::encodeAction(action::ARC_LEFT);
#endif
      m_nActions[index][m_nActionNum[index]-1] = m_nLastAction[index];
   }

   // the arc right action links the next word to the current stack top with pushing
#ifdef LABELED
   void ArcRight(int index, unsigned long lab) {
#else
   void ArcRight(int index) {
#endif
      if( m_Stack[index].size() == 0 )
      {
          std::cout << *this << std::endl;
          std::cout << "ArcRight:" << m_Stack[index].size()  << std::endl;
      }
      static int left ;
      left = m_Stack[index].back() ;
      m_Stack[index].push_back( m_nNextWord[index] ) ;
      m_lHeads[index][m_nNextWord[index]] = left ;
#ifdef LABELED
      m_lLabels[index][m_nNextWord[index]] = lab ;
      m_lDepTagR[index][left].add(lab) ;
#endif
      m_lSibling[index][m_nNextWord[index]] = m_lDepsR[index][left];
      m_lDepsR[index][left] = m_nNextWord[index] ;
      m_lDepNumR[index][left] ++ ;
      m_nNextWord[index] ++;
      ClearNext();
      m_nActionNum[index]++;
      last_action_index = index;
#ifdef LABELED
      m_nLastAction[index]=action::encodeAction(action::ARC_RIGHT, lab);
#else
      m_nLastAction[index]=action::encodeAction(action::ARC_RIGHT);
#endif
      m_nActions[index][m_nActionNum[index]-1] = m_nLastAction[index];
   }

   // the shift action does pushing
   void Shift(int index) {
      m_Stack[index].push_back( m_nNextWord[index] );
      m_HeadStack[index].push_back( m_nNextWord[index] );
      m_nNextWord[index] ++ ;
      ClearNext();
      m_nActionNum[index]++;
      last_action_index = index;
      if(index == 0)
      {
          m_nLastAction[index]=action::encodeAction(action::SHIFT0);
      }
      else
      {
          m_nLastAction[index]=action::encodeAction(action::SHIFT1);
      }

      m_nActions[index][m_nActionNum[index]-1] = m_nLastAction[index];
   }
 
   // the reduce action does popping
   void Reduce(int index) {
      if( m_lHeads[index][m_Stack[index].back()] == DEPENDENCY_LINK_NO_HEAD )
      {
          std::cout << *this << std::endl;
          std::cout << "Reduce:" << m_Stack[index].size() <<  std::endl;
      }
      m_Stack[index].pop_back() ;
      m_nActionNum[index]++;
      last_action_index = index;
      if(index == 0)
      {
          m_nLastAction[index]=action::encodeAction(action::REDUCE0);
      }
      else
      {
          m_nLastAction[index]=action::encodeAction(action::REDUCE1);
      }

      m_nActions[index][m_nActionNum[index]-1] = m_nLastAction[index];
   }

   // this is used for the convenience of scoring and updating
   void PopRoot(int index) {
#ifndef FRAGMENTED_TREE
      if( m_Stack[index].size() != 1 || m_lHeads[index][m_Stack[index].back()] != DEPENDENCY_LINK_NO_HEAD )  // make sure only one root item in stack
      {
          std::cout << *this << std::endl;
          std::cout << "PopRoot:" << m_Stack[index].size() << std::endl;
      }
#else
      assert( m_lHeads[index][m_Stack[index].back()] == DEPENDENCY_LINK_NO_HEAD ) ;
#endif
#ifdef LABELED
      if(index == 0)
      {
          m_lLabels[index][m_Stack[index].back()] = CDependencyLabel::ROOT0;
      }
      else
      {
          m_lLabels[index][m_Stack[index].back()] = CDependencyLabel::ROOT1;
      }
#endif
      m_nActionNum[index]++;
      last_action_index = index;
      if(index == 0)
      {
          m_nLastAction[index]=action::encodeAction(action::POP_ROOT0);
      }
      else
      {
          m_nLastAction[index]=action::encodeAction(action::POP_ROOT1);
      }
      m_Stack[index].pop_back() ; // pop it

      m_nActions[index][m_nActionNum[index]-1] = m_nLastAction[index];
   }

   // the clear next action is used to clear the next word, used with forwarding the next word index
   void ClearNext() {
       for(int idx = 0; idx < 2; idx++)
       {
          m_lHeads[idx][m_nNextWord[idx]] = DEPENDENCY_LINK_NO_HEAD ;
          m_lDepsL[idx][m_nNextWord[idx]] = DEPENDENCY_LINK_NO_HEAD ;
          m_lDepsR[idx][m_nNextWord[idx]] = DEPENDENCY_LINK_NO_HEAD ;
          m_lDepNumL[idx][m_nNextWord[idx]] = 0 ;
          m_lDepTagL[idx][m_nNextWord[idx]].clear() ;
          m_lDepNumR[idx][m_nNextWord[idx]] = 0 ;
          m_lDepTagR[idx][m_nNextWord[idx]].clear() ;
          m_lSibling[idx][m_nNextWord[idx]] = DEPENDENCY_LINK_NO_HEAD ;
    #ifdef LABELED
          m_lLabels[idx][m_nNextWord[idx]] = CDependencyLabel::NONE;
    #endif

          m_nActions[idx][m_nActionNum[idx]] = action::NO_ACTION;
       }
   }

   // the move action is a simple call to do action according to the action code
   void Move (int idx, const unsigned long &ac ) {
#ifdef LABELED
      switch (action::getUnlabeledAction(ac)) {
#else
      switch (ac) {
#endif
      case action::NO_ACTION:
         return;
      case action::SHIFT0:
         assert(idx == 0);
         Shift(idx);
         return;
      case action::SHIFT1:
         assert(idx == 1);
         Shift(idx);
         return;
      case action::REDUCE0:
          assert(idx == 0);
          Reduce(idx);
         return;
      case action::REDUCE1:
          assert(idx == 1);
          Reduce(idx);
         return;
      case action::ARC_LEFT:
#ifdef LABELED
         ArcLeft(idx, action::getLabel(ac));
#else
         ArcLeft(idx);
#endif
         return;
      case action::ARC_RIGHT:
#ifdef LABELED
         ArcRight(idx, action::getLabel(ac));
#else
         ArcRight(idx);
#endif
         return;
      case action::POP_ROOT0:
         assert(idx == 0);
         PopRoot(idx);
         return;
      case action::POP_ROOT1:
         assert(idx == 1);
         PopRoot(idx);
         return;
      default:
         THROW("unknown action: " << ac << '.');
      }
   }

    void Move (const unsigned long &ac ) {
        int index = nextactionindex();
        Move(index, ac);
    }

//-----------------------------------------------------------------------------

public:

   // returns true is the next word advances -- by shift or arcright. 
#ifdef LABELED
   bool StandardMoveStep(int index, const CDependencyParse &tree, const std::vector<CDependencyLabel>&m_lCacheLabel ) {
#else
   bool StandardMoveStep(int index,  const CDependencyParse &tree ) {
#endif
      static int top;
      // when the next word is tree.size() it means that the sentence is done already
      if ( m_nNextWord[index] == static_cast<int>(tree.size()) ) {
         assert( m_Stack[index].size() > 0 );
         if ( m_Stack[index].size() > 1 ) {
            Reduce(index);
            return false;
         }
         else {
            PopRoot(index);
            return false;
         }
      }
      // the first case is that there is some words on the stack linking to nextword
      if ( m_Stack[index].size() > 0 ) {
         top = m_Stack[index].back();
         while ( !(m_lHeads[index][top] == DEPENDENCY_LINK_NO_HEAD) )
            top = m_lHeads[index][top];
         if ( tree[top].head == m_nNextWord[index] ) {    // if a local head deps on nextword first
            if ( top == m_Stack[index].back() ) {
#ifdef LABELED
               if(m_lCacheLabel[top].str() != tree[top].label)
               {
                   std::cout << m_lCacheLabel[top].str() << " " << tree[top].label << std::endl;
               }
               ArcLeft(index, m_lCacheLabel[top].code()); // link it to the next word
#else
               ArcLeft(index);                          // link it to the next word
#endif
               return false;
            }
            else {
               Reduce(index);
               return false;
            }
         }
      }
      // the second case is that no words on the stack links nextword, and nextword does not link to stack word
      if ( tree[m_nNextWord[index]].head == DEPENDENCY_LINK_NO_HEAD || // the root or
           tree[m_nNextWord[index]].head > m_nNextWord[index] ) { // head on the right
         Shift(index);
         return true;
      }
      // the last case is that the next words links to stack word
      else {                                        // head on the left 
         assert( m_Stack[index].size() > 0 );
         top = m_Stack[index].back();
         if ( tree[m_nNextWord[index]].head == top ) {     // the next word deps on stack top
#ifdef LABELED
            assert(m_lCacheLabel[m_nNextWord[index]].str()==tree[m_nNextWord[index]].label);
            ArcRight(index, m_lCacheLabel[m_nNextWord[index]].code());
#else            
            ArcRight(index);
#endif            
            return true;
         }
         else {                                     // must depend on non-immediate h
            Reduce(index);
            return false;
         }
      }
   }

   unsigned StandardMove(const CDependencyParse & tree0, const CDependencyParse & tree1,
           const std::vector<CDependencyLabel> & m_lCacheLabel0,  const std::vector<CDependencyLabel> & m_lCacheLabel1) {
       int index = nextactionindex();
       unsigned action = 0;
#ifdef LABELED
       if(index == 1)
       {
           return StandardMoveStep(index, tree1, m_lCacheLabel1);
       }
       else
       {
           return StandardMoveStep(index, tree0, m_lCacheLabel0);
       }
#else
       if(index == 1)
       {
           return StandardMoveStep(index, tree1);
       }
       else
       {
           return StandardMoveStep(index, tree0);
       }
#endif
   }


   void StandardMoveStep(const CDependencyParse & tree0, const CDependencyParse & tree1,
           const std::vector<CDependencyLabel> & m_lCacheLabel0,  const std::vector<CDependencyLabel> & m_lCacheLabel1) {

       int index = nextactionindex();
       unsigned action = 0;
#ifdef LABELED
       if(index == 1)
       {
           action = StandardMoveStep(index, tree1, m_lCacheLabel1);
       }
       else
       {
           action = StandardMoveStep(index, tree0, m_lCacheLabel0);
       }
#else
       if(index == 1)
       {
           action = StandardMove(index, tree1);
       }
       else
       {
           action = StandardMove(index, tree0);
       }
#endif

       //Move(index, action);
   }

   // we want to pop the root item after the whole tree done
   // on the one hand this seems more natural
   // on the other it is easier to score
   void StandardFinish() {
       int index = nextactionindex();
       StandardFinish(index);
   }

   void StandardFinish_another() {
       int index = nextactionindex();
       StandardFinish(1-index);
   }

   void StandardFinish(int index) {
      assert( m_Stack[index].size() == 0 );
   }

   unsigned FollowMove(int index, const CStateItem *item ) {
      static int top;
      // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
      if ( m_nNextWord[index] == item->m_nNextWord[index] ) {

         if( m_Stack[index].size() <= item->m_Stack[index].size() )
         {
             std::cout << *this << std::endl;
             std::cout << *item << std::endl;
             std::cout << m_Stack[index].size() << " " << item->m_Stack[index].size() << std::endl;
         }
         top = m_Stack[index].back();
         if ( item->m_lHeads[index][top] == m_nNextWord[index] )
#ifdef LABELED
            return action::encodeAction(action::ARC_LEFT, item->m_lLabels[index][top]);
#else
            return action::ARC_LEFT;
#endif
         else if ( item->m_lHeads[index][top] != DEPENDENCY_LINK_NO_HEAD )
         {
             if(index == 0)
             {
                 return action::encodeAction(action::REDUCE0);
             }
             else
             {
                 return action::encodeAction(action::REDUCE1);
             }
         }
         else 
         {
             //std::cout << *this << std::endl;
             //std::cout << *item << std::endl;
             //std::cout << m_Stack[index].size() << " " << item->m_Stack[index].size() << std::endl;
             if(index == 0)
             {
                 return action::encodeAction(action::POP_ROOT0);
             }
             else
             {
                 return action::encodeAction(action::POP_ROOT1);
             }
         }
      }
      // the first case is that there is some words on the stack linking to nextword
      if ( m_Stack[index].size() > 0 ) {
         top = m_Stack[index].back();
         while ( !(m_lHeads[index][top] == DEPENDENCY_LINK_NO_HEAD) )
            top = m_lHeads[index][top];
         if ( item->head(index, top) == m_nNextWord[index] ) {    // if a local head deps on nextword first
            if ( top == m_Stack[index].back() ) {
                //std::cout << *this << std::endl;
                //std::cout << *item << std::endl;
                //std::cout << m_Stack[index].size() << " " << item->m_Stack[index].size() << std::endl;
#ifdef LABELED
               return action::encodeAction(action::ARC_LEFT, item->m_lLabels[index][top]);
#else
               return action::ARC_LEFT;
#endif
            }
            else {
                if(index == 0)
                {
                    return action::encodeAction(action::REDUCE0);
                }
                else
                {
                    return action::encodeAction(action::REDUCE1);
                }
            }
         }
      }
      // the second case is that no words on the stack links nextword, and nextword does not link to stack word
      if ( item->head(index, m_nNextWord[index]) == DEPENDENCY_LINK_NO_HEAD || // the root or
           item->head(index, m_nNextWord[index]) > m_nNextWord[index] ) { // head on the right
          if(index == 0)
          {
              return action::encodeAction(action::SHIFT0);
          }
          else
          {
              return action::encodeAction(action::SHIFT1);
          }
      }
      // the last case is that the next words links to stack word
      else {                                        // head on the left 
         assert( m_Stack[index].size() > 0 );
         top = m_Stack[index].back();
         if ( item->head(index, m_nNextWord[index]) == top ) {    // the next word deps on stack top
             //std::cout << *this << std::endl;
             //std::cout << *item << std::endl;
             //std::cout << m_Stack[index].size() << " " << item->m_Stack[index].size() << std::endl;
#ifdef LABELED
            return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[index][m_nNextWord[index]]);
#else
            return action::ARC_RIGHT;
#endif
         }
         else {                                     // must depend on non-immediate h
             if(index == 0)
             {
                 return action::encodeAction(action::REDUCE0);
             }
             else
             {
                 return action::encodeAction(action::REDUCE1);
             }
         }
      }
   }

   unsigned FollowMove(const CStateItem *item ) {
       int index = nextactionindex();
       return FollowMove(index, item);
   }

   void GenerateTree( const CTwoStringVector &input, CDependencyParse &output0, CDependencyParse &output1 ) const {
      output0.clear();
      for ( int i=0; i<size(); ++i ) 
#ifdef LABELED
         output0.push_back( CLabeledDependencyTreeNode( input.at(i).first , input.at(i).second , m_lHeads[0][i] , CDependencyLabel(m_lLabels[0][i]).str() ) ) ;
#else
         output0.push_back( CDependencyTreeNode( input.at(i).first , input.at(i).second , m_lHeads[0][i] ) ) ;
#endif

     for ( int i=0; i<size(); ++i )
#ifdef LABELED
        output1.push_back( CLabeledDependencyTreeNode( input.at(i).first , input.at(i).second , m_lHeads[1][i] , CDependencyLabel(m_lLabels[1][i]).str() ) ) ;
#else
        output1.push_back( CDependencyTreeNode( input.at(i).first , input.at(i).second , m_lHeads[1][i] ) ) ;
#endif
   }


   friend std::ostream & operator << (std::ostream& out, const CStateItem & item) {
     out << "scheme 0:" << action::getUnlabeledAction(item.m_nLastAction[0])
         << "-" << action::getLabel(item.m_nLastAction[0])
         << " "
         << "scheme 1:" << action::getUnlabeledAction(item.m_nLastAction[1])
             << "-" << action::getLabel(item.m_nLastAction[1])
         << " (" << item.score
         << "): \n schema 0 (";
     for(int index = 0; index < 2; index++)
     {
         for (int i = 0; i < item.m_Stack[index].size(); ++ i) {
           out << item.m_Stack[index][i];
           if (i + 1 < item.m_Stack[index].size()) { out << "|"; }
         }
         out << ") ";
         for (int i = 0; i < item.m_nNextWord[index]; ++ i) {
             out << i << "<-" << item.m_lHeads[index][i] << " ";
         }
         out << item.m_nNextWord[index] << " " << item.m_nActions[index][0];
         for (int i = 1; i < item.m_nActionNum[index]; ++ i) {
             out << "|" << item.m_nActions[index][i] ;
         }
         if(index == 0) out << std::endl  << "schema 1 (";
     }
     return out;
   }
 };



#endif
