// Copyright (C) University of Oxford 2010
#ifndef DEPPARSER_ARC_STANDARD_STATE_H
#define DEPPARSER_ARC_STANDARD_STATE_H

class CStateItem {
protected:
  int m_nActionNum[2];
  //the number of tree 0's operations advancing tree 1
  std::vector<int> m_Stack[2];
  // stack of words that are currently processed

  int m_nNextWord[2];
  // index for the next word

  int m_lHeads[2][MAX_SENTENCE_SIZE];
  // the lexical head for each word

  int m_lDepsL[2][MAX_SENTENCE_SIZE];
  // the leftmost dependency for each word (just for cache, temporary info)

  int m_lDepsR[2][MAX_SENTENCE_SIZE];
  // the rightmost dependency for each word (just for cache, temporary info)

  int m_lDepsL2[2][MAX_SENTENCE_SIZE];
  // the second-leftmost dependency for each word

  int m_lDepsR2[2][MAX_SENTENCE_SIZE];
  // the second-rightmost dependency for each word

  int m_lDepNumL[2][MAX_SENTENCE_SIZE];
  // the number of left dependencies

  int m_lDepNumR[2][MAX_SENTENCE_SIZE];
  // the number of right dependencies

  CSetOfTags<CDependencyLabel> m_lDepTagL[2][MAX_SENTENCE_SIZE];
  // the set of left tags

  CSetOfTags<CDependencyLabel> m_lDepTagR[2][MAX_SENTENCE_SIZE];
  // the set of right tags

#ifdef LABELED
  unsigned long m_lLabels[2][MAX_SENTENCE_SIZE];
  // the label of each dependency link
#endif

public:
  SCORE_TYPE score;
  // score of stack - predicting how potentially this is the correct one

  int len_;
  // the length of the sentence, it's set manually.

  const CStateItem * previous_;
  // Previous state of the current state

  unsigned long last_action_index;
  unsigned long last_action[2];
  // the last stack action
  unsigned long m_nActions[2][2*MAX_SENTENCE_SIZE+1];                  // the last stack action


public:
  // constructors and destructor
  CStateItem() {
    clear();
  }

  ~CStateItem() { }
public:
  // comparison
  inline bool operator < (const CStateItem &item) const {
    return score < item.score;
  }

  inline bool operator > (const CStateItem &item) const {
    return score > item.score;
  }

  inline bool operator == (const CStateItem &item) const {
    THROW("equal operator should not be used");
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

  // propty of next processing tree
   inline int stacksize() const {
       int index = nextactionindex();
     return stacksize(index);
   }

   inline bool stackempty() const {
       int index = nextactionindex();
     return stackempty(index);
   }

   inline int stacktop() const {
       int index = nextactionindex();
     return  stacktop(index);
   }

   inline int stack2top() const {
       int index = nextactionindex();
     return stack2top(index);
   }

   inline int stackbottom() const {
       int index = nextactionindex();
     return stackbottom(index);
   }

   inline int stackitem(const int & id) const {
       int index = nextactionindex();
     return stackitem(index, id);
   }

   inline int head(const int & id) const {
       int index = nextactionindex();
     return head(index, id);
   }

   inline int leftdep(const int & id) const {
       int index = nextactionindex();
     return leftdep(index, id);
   }

   inline int rightdep(const int & id) const {
       int index = nextactionindex();
     return rightdep(index, id);
   }

   inline int left2dep(const int & id) const {
       int index = nextactionindex();
     return left2dep(index, id);
   }

   inline int right2dep(const int & id) const {
       int index = nextactionindex();
     return right2dep(index, id);
   }

   inline int size() const {
       int index = nextactionindex();
     return size(index);
   }



   inline bool complete() const {
       int index = nextactionindex();
     return complete(index);
   }

 #ifdef LABELED
   inline int label(const int & id) const {
       int index = nextactionindex();
     return label(index, id);
   }
 #endif

   inline int leftarity(const int & id) const {
       int index = nextactionindex();
     return leftarity(index, id);
   }

   inline int rightarity(const int & id) const {
       int index = nextactionindex();
     return rightarity(index, id);
   }

   inline const CSetOfTags<CDependencyLabel> &lefttagset(const int &id) const {
       int index = nextactionindex();
     return lefttagset(index, id);
   }

   inline const CSetOfTags<CDependencyLabel> &righttagset(const int &id) const {
       int index = nextactionindex();
     return righttagset(index, id);
   }



   // propty of next unprocessing tree
   inline int stacksize_another() const {
       int index = nextactionindex();
     return stacksize(1-index);
   }

   inline bool stackempty_another() const {
       int index = nextactionindex();
     return stackempty(1-index);
   }

   inline int stacktop_another() const {
       int index = nextactionindex();
     return  stacktop(1-index);
   }

   inline int stack2top_another() const {
       int index = nextactionindex();
     return stack2top(1-index);
   }

   inline int stackbottom_another() const {
       int index = nextactionindex();
     return stackbottom(1-index);
   }

   inline int stackitem_another(const int & id) const {
       int index = nextactionindex();
     return stackitem(1-index, id);
   }

   inline int head_another(const int & id) const {
       int index = nextactionindex();
     return head(1-index, id);
   }

   inline int leftdep_another(const int & id) const {
       int index = nextactionindex();
     return leftdep(1-index, id);
   }

   inline int rightdep_another(const int & id) const {
       int index = nextactionindex();
     return rightdep(1-index, id);
   }

   inline int left2dep_another(const int & id) const {
       int index = nextactionindex();
     assert(id < m_nNextWord[index]);
     return left2dep(1-index, id);
   }

   inline int right2dep_another(const int & id) const {
       int index = nextactionindex();
     return right2dep(1-index, id);
   }

   inline int size_another() const {
       int index = nextactionindex();
     return size(1-index);
   }



   inline bool complete_another() const {
       int index = nextactionindex();
     return complete(1-index);
   }

 #ifdef LABELED
   inline int label_another(const int & id) const {
       int index = nextactionindex();
     return label(1-index, id);
   }
 #endif

   inline int leftarity_another(const int & id) const {
       int index = nextactionindex();
     return leftarity(1-index, id);
   }

   inline int rightarity_another(const int & id) const {
       int index = nextactionindex();
     return rightarity(1-index, id);
   }

   inline const CSetOfTags<CDependencyLabel> &lefttagset_another(const int &id) const {
       int index = nextactionindex();
     return lefttagset(1-index, id);
   }

   inline const CSetOfTags<CDependencyLabel> &righttagset_another(const int &id) const {
       int index = nextactionindex();
     return righttagset(1-index, id);
   }




  // propty for one
  inline int stacksize(int index) const {
    return m_Stack[index].size();
  }

  inline bool stackempty(int index) const {
    return m_Stack[index].empty();
  }

  inline int stacktop(int index) const {
    if (m_Stack[index].empty()) { return -1; }
    return m_Stack[index].back();
  }

  inline int stack2top(int index) const {
    if (m_Stack[index].size() < 2) { return -1; }
    return m_Stack[index][m_Stack[index].size() - 2];
  }

  inline int stackbottom(int index) const {
    assert(!m_Stack[index].empty());
    return m_Stack[index].front();
  }

  inline int stackitem(int index, const int & id) const {
    assert (id < m_Stack[index].size());
    return m_Stack[index][id];
  }

  inline int head(int index, const int & id) const {
    assert (id < m_nNextWord[index]);
    return m_lHeads[index][id];
  }

  inline int leftdep(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepsL[index][id];
  }

  inline int rightdep(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepsR[index][id];
  }

  inline int left2dep(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepsL2[index][id];
  }

  inline int right2dep(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepsR2[index][id];
  }

  inline int size(int index) const {
    return m_nNextWord[index];
  }

  inline bool terminated() const {
    return (last_action[0] == action::kPopRoot0 && last_action[1] == action::kPopRoot1
            && m_Stack[0].empty() && m_Stack[1].empty()
            && m_nNextWord[0] == len_ && m_nNextWord[1] == len_);
  }

  inline bool terminated(int index) const {
      if(index == 0)
      {
          return (last_action[0] == action::kPopRoot0
                  && m_Stack[0].empty());
      }
      else
      {
          return (last_action[1] == action::kPopRoot1
                  && m_Stack[1].empty());
      }
  }

  inline bool complete(int index) const {
    return (m_Stack[index].size() == 1
            && m_nNextWord[index] == len_);
  }
#ifdef LABELED
  inline int label(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lLabels[index][id];
  }
#endif

  inline int leftarity(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepNumL[index][id];
  }

  inline int rightarity(int index, const int & id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepNumR[index][id];
  }

  inline const CSetOfTags<CDependencyLabel> &lefttagset(int index, const int &id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepTagL[index][id];
  }

  inline const CSetOfTags<CDependencyLabel> &righttagset(int index, const int &id) const {
    assert(id < m_nNextWord[index]);
    return m_lDepTagR[index][id];
  }

  void clear() {
    m_nNextWord[0] = 0;
    m_nNextWord[1] = 0;
    m_Stack[0].clear();
    m_Stack[1].clear();
    score = 0;
    previous_ = 0;
    last_action[0] = action::kNoAction;
    last_action[1] = action::kNoAction;
    last_action_index = -1;
    m_nActions[0][0] = action::kNoAction;
    m_nActions[1][0] = action::kNoAction;
    ClearNext();
  }

  void operator = (const CStateItem &item) {

      last_action_index = item.last_action_index;
      score       = item.score;
      len_        = item.len_;
      previous_   = item.previous_;
    for(int index = 0; index < 2; index++)
    {
        m_nActionNum[index] = item. m_nActionNum[index];
        last_action[index] = item. last_action[index];
        m_Stack[index] = item.m_Stack[index];
        m_nNextWord[index] = item.m_nNextWord[index];

        for (int i = 0; i <= m_nNextWord[index]; ++ i) { // only copy active word (including m_nNext)
          m_lHeads[index][i] = item.m_lHeads[index][i];
          m_lDepsL[index][i] = item.m_lDepsL[index][i];
          m_lDepsR[index][i] = item.m_lDepsR[index][i];
          m_lDepsL2[index][i] = item.m_lDepsL2[index][i];
          m_lDepsR2[index][i] = item.m_lDepsR2[index][i];
          m_lDepNumL[index][i] = item.m_lDepNumL[index][i];
          m_lDepNumR[index][i] = item.m_lDepNumR[index][i];
    #ifdef LABELED
          m_lLabels[index][i] = item.m_lLabels[index][i];
          m_lDepTagL[index][i] = item.m_lDepTagL[index][i];
          m_lDepTagR[index][i] = item.m_lDepTagR[index][i];
    #endif
        }

        for ( int i=0; i<=m_nActionNum[index]; ++i ){ // only copy active word (including m_nNext)
            m_nActions[index][i] = item.m_nActions[index][i];
        }
    }
  }

//-----------------------------------------------------------------------------
public:
  // Perform Arc-Left operation in the arc-standard algorithm
  void ArcLeft(int index,
#ifdef LABELED
      unsigned long lab
#endif
      ) {
    // At least, there must be two elements in the stack.
    assert(m_Stack[index].size() > 1);
    //{

    //}
    //else
   // {
   //     std::cout << *this << std::endl;
    //}
    assert(m_lHeads[index][m_Stack[index].back()] == DEPENDENCY_LINK_NO_HEAD);

    int stack_size = m_Stack[index].size();
    int top0 = m_Stack[index][stack_size - 1];
    int top1 = m_Stack[index][stack_size - 2];

    m_Stack[index].pop_back();
    m_Stack[index].back() = top0;

    m_lHeads[index][top1] = top0;
    m_lDepNumL[index][top0] ++;


#ifdef LABELED
    m_lLabels[index][top1] = lab;
    m_lDepTagL[index][top0].add(lab);
#endif

    if (m_lDepsL[index][top0] == DEPENDENCY_LINK_NO_HEAD) {
      m_lDepsL[index][top0] = top1;
    } else if (top1 < m_lDepsL[index][top0]) {
      m_lDepsL2[index][top0] = m_lDepsL[index][top0];
      m_lDepsL[index][top0] = top1;
    } else if (top1 < m_lDepsL2[index][top0]) {
      m_lDepsL2[index][top0] = top1;
    }

    m_nActionNum[index]++;
    last_action_index = index;
    last_action[index] = action::EncodeAction(action::kArcLeft
#ifdef LABELED
        , lab
#endif
        );

    m_nActions[index][m_nActionNum[index]-1] = last_action[index];
  }

  // Perform the arc-right operation in arc-standard
  void ArcRight(int index,
#ifdef LABELED
      unsigned long lab
#endif
      ) {
    assert(m_Stack[index].size() > 1);

    int stack_size = m_Stack[index].size();
    int top0 = m_Stack[index][stack_size - 1];
    int top1 = m_Stack[index][stack_size - 2];

    m_Stack[index].pop_back();
    m_lHeads[index][top0] = top1;
    m_lDepNumR[index][top1] ++;

#ifdef LABELED
    m_lLabels[index][top0] = lab;
    m_lDepTagR[index][top1].add(lab);
#endif

    if (m_lDepsR[index][top1] == DEPENDENCY_LINK_NO_HEAD) {
      m_lDepsR[index][top1] = top0;
    } else if (m_lDepsR[index][top1] < top0) {
      m_lDepsR2[index][top1] = m_lDepsR[index][top1];
      m_lDepsR[index][top1] = top0;
    } else if (m_lDepsR2[index][top1] < top0) {
      m_lDepsR2[index][top1] = top0;
    }

    m_nActionNum[index]++;
    last_action_index = index;
    last_action[index] = action::EncodeAction(action::kArcRight
#ifdef LABELED
        , lab
#endif
        );
    m_nActions[index][m_nActionNum[index]-1] = last_action[index];
  }

  // the shift action does pushing
  void Shift(int index) {
    m_Stack[index].push_back(m_nNextWord[index]);
    m_nNextWord[index] ++;
    ClearNext();
    m_nActionNum[index]++;
    last_action_index = index;
    if(index == 0)
    {
        last_action[index] = action::EncodeAction(action::kShift0);
    }
    else
    {
        last_action[index] = action::EncodeAction(action::kShift1);
    }

    m_nActions[index][m_nActionNum[index]-1] = last_action[index];
  }

  // this is used for the convenience of scoring and updating
  void PopRoot(int index) {
    assert(m_Stack[index].size() == 1
           && m_lHeads[index][m_Stack[index].back()] == DEPENDENCY_LINK_NO_HEAD);
    // make sure only one root item in stack

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
        last_action[index] = action::EncodeAction(action::kPopRoot0);
    }
    else
    {
        last_action[index] = action::EncodeAction(action::kPopRoot1);
    }
    m_Stack[index].pop_back(); // pop it
    m_nActions[index][m_nActionNum[index]-1] = last_action[index];
  }

  // the clear next action is used to clear the next word, used 
  // with forwarding the next word index
  void ClearNext() {
      for(int index = 0; index < 2; index++)
      {
        m_lHeads[index][m_nNextWord[index]]   = DEPENDENCY_LINK_NO_HEAD;
        m_lDepsL[index][m_nNextWord[index]]   = DEPENDENCY_LINK_NO_HEAD;
        m_lDepsL2[index][m_nNextWord[index]]  = DEPENDENCY_LINK_NO_HEAD;
        m_lDepsR[index][m_nNextWord[index]]   = DEPENDENCY_LINK_NO_HEAD;
        m_lDepsR2[index][m_nNextWord[index]]  = DEPENDENCY_LINK_NO_HEAD;
        m_lDepNumL[index][m_nNextWord[index]] = 0;
        m_lDepNumR[index][m_nNextWord[index]] = 0;
        m_lDepTagL[index][m_nNextWord[index]].clear();
        m_lDepTagR[index][m_nNextWord[index]].clear();
        if(m_nActionNum[index] >= 0 && m_nActionNum[index] < 2*MAX_SENTENCE_SIZE+1)
        {
            m_nActions[index][m_nActionNum[index]] = action::kNoAction;
        }
        else
        {
            std::cout << m_nActionNum[index] << std::endl;
            std::cout << *this << std::endl;
        }

    #ifdef LABELED
        m_lLabels[index][m_nNextWord[index]] = CDependencyLabel::NONE;
    #endif
      }
  }

  // the move action is a simple call to do action according to the action code
  void Move (int index, const unsigned long &ac) {
    switch (action::DecodeUnlabeledAction(ac)) {
      case action::kNoAction: { return; }
      case action::kShift0:    { assert(index == 0); Shift(index);  return; }
      case action::kShift1:    { assert(index == 1); Shift(index);  return; }
      case action::kArcLeft:  { ArcLeft(index,
#ifdef LABELED
                                  action::DecodeLabel(ac)
#endif
                                  );
                                return;
                              }
      case action::kArcRight: { ArcRight(index,
#ifdef LABELED
                                  action::DecodeLabel(ac)
#endif
                                  );
                                return;
                              }
      case action::kPopRoot0:  { assert(index == 0); PopRoot(index); return; }
      case action::kPopRoot1:  { assert(index == 1); PopRoot(index); return; }
      default:                { THROW("unknown action: " << ac << '.'); }
    }
  }

//-----------------------------------------------------------------------------

public:
  unsigned StandardMove(int index, const CDependencyParse & tree,
                        const std::vector<CDependencyLabel> & m_lCacheLabel) {
    if (terminated(index)) {
      return action::EncodeAction(action::kNoAction);
    }

    int stack_size = m_Stack[index].size();
    if (0 == stack_size) {
        if(index == 0)
        {
            return action::EncodeAction(action::kShift0);
        }
        else
        {
            return action::EncodeAction(action::kShift1);
        }
    }
    else if (1 == stack_size) {
      if (m_nNextWord[index] == static_cast<int>(tree.size())) {
          if(index == 0)
          {
              return action::EncodeAction(action::kPopRoot0);
          }
          else
          {
              return action::EncodeAction(action::kPopRoot1);
          }
      } else {
          if(index == 0)
          {
              return action::EncodeAction(action::kShift0);
          }
          else
          {
              return action::EncodeAction(action::kShift1);
          }
      }
    }
    else {
      int top0 = m_Stack[index][stack_size - 1];
      int top1 = m_Stack[index][stack_size - 2];

      bool has_right_child = false;
      for (int i = m_nNextWord[index]; i < tree.size(); ++ i) {
        if (tree[i].head == top0) { has_right_child = true; break; }
      }

      if (tree[top0].head == top1 && !has_right_child) {
        return action::EncodeAction(action::kArcRight
#ifdef LABELED
            , m_lCacheLabel[top0].code()
#endif
            );
      }
      else if (tree[top1].head == top0) {
        return action::EncodeAction(action::kArcLeft
#ifdef LABELED
            , m_lCacheLabel[top1].code()
#endif
            );
      }
      else {
          if(index == 0)
          {
              return action::EncodeAction(action::kShift0);
          }
          else
          {
              return action::EncodeAction(action::kShift1);
          }
      }
    }
  }

  unsigned StandardMove(const CDependencyParse & tree0, const CDependencyParse & tree1,
          const std::vector<CDependencyLabel> & m_lCacheLabel0,  const std::vector<CDependencyLabel> & m_lCacheLabel1) {
      int index = nextactionindex();
      unsigned action = 0;
      if(index == 1)
      {
          return StandardMove(index, tree1, m_lCacheLabel1);
      }
      else
      {
          return StandardMove(index, tree0, m_lCacheLabel0);
      }
  }

  unsigned StandardMoveStep(const CDependencyParse & tree0, const CDependencyParse & tree1,
          const std::vector<CDependencyLabel> & m_lCacheLabel0,  const std::vector<CDependencyLabel> & m_lCacheLabel1) {
      int index = nextactionindex();
      unsigned action = 0;
      if(index == 1)
      {
          action = StandardMove(index, tree1, m_lCacheLabel1);
      }
      else
      {
          action = StandardMove(index, tree0, m_lCacheLabel0);
      }

      Move(index, action);

      return action;
  }

  // we want to pop the root item after the whole tree done
  // on the one hand this seems more natural
  // on the other it is easier to score
  void StandardFinish() {
    assert(m_Stack[0].size() == 0 && m_Stack[1].size() == 0);
  }

  void GenerateTree(const CTwoStringVector &input, CDependencyParse &output0,  CDependencyParse &output1) const {
      output0.clear();
    for (int i = 0; i < size(0); ++ i) {
#ifdef LABELED
        output0.push_back(CLabeledDependencyTreeNode(input.at(i).first,
                                                  input.at(i).second,
                                                  m_lHeads[0][i],
                                                  CDependencyLabel(m_lLabels[0][i]).str()));
#else
        output0.push_back(CDependencyTreeNode(input.at(i).first,
                                           input.at(i).second,
                                           m_lHeads[0][i]));
#endif
    }

    output1.clear();
  for (int i = 0; i < size(1); ++ i) {
#ifdef LABELED
      output1.push_back(CLabeledDependencyTreeNode(input.at(i).first,
                                                input.at(i).second,
                                                m_lHeads[1][i],
                                                CDependencyLabel(m_lLabels[1][i]).str()));
#else
      output1.push_back(CDependencyTreeNode(input.at(i).first,
                                         input.at(i).second,
                                         m_lHeads[1][i]));
#endif
  }
  }

  friend std::ostream & operator << (std::ostream& out, const CStateItem & item) {
     out << "scheme 0:" << action::DecodeUnlabeledAction(item.last_action[0])
         << "-" << action::DecodeLabel(item.last_action[0])
         << " "
         << "scheme 1:" << action::DecodeUnlabeledAction(item.last_action[1])
             << "-" << action::DecodeLabel(item.last_action[1])
         << " (" << item.score
         << "): \n schema 0 (";
     for(int index = 0; index < 2; index++)
     {
         for (int i = 0; i < item.m_Stack[index].size(); ++ i) {
           out << item.m_Stack[index][i];
           if (i + 1 < item.m_Stack[index].size()) { out << "|"; }
         }
         out << ") ";
         //for (int i = 0; i < item.m_nNextWord[index]; ++ i) {
         //    out << i << "<-" << item.m_lHeads[index][i] << " ";
         //}
         out << item.m_nNextWord[index] << " " << item.m_nActions[index][0];
         for (int i = 1; i < item.m_nActionNum[index]; ++ i) {
             out << "|" << item.m_nActions[index][i] ;
         }
         if(index == 0) out << std::endl  << "schema 1 (";
     }
     return out;
   }
 };

#endif  //  end for DEPPARSER_ARC_STANDARD_STATE_H
