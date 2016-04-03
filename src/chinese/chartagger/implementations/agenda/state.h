// Copyright (C) University of Oxford 2010
#ifndef _CHINESE_CHARTAGGER_STATEITEM
#define _CHINESE_CHARTAGGER_STATEITEM

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce. 
 *
 * Note about members: there are two types of item properties;
 * The first is the stack, which changes during the process; 
 * The second is the incoming sentence, including m_nHeads,
 * m_lDepsL and m_lDepsR, m_lDepNumL, m_lDepNumR etc, which 
 * records the properties of each input word so far.
 *
 * A state item is partial and do not include information about
 * all words from the input sentence. Though m_nHeads, m_lDepsL
 * and m_lDepsR are fixed arrays with MAX_SENTENCE_SIZE length, 
 * not all the elements from the arrays are used. The ACTIVE 
 * elements are from the input index 0 to m_nNextWord, inclusive. 
 * And a state item only captures information about the active 
 * sub section from input.
 *
 * The property for each input word need to be initialised. 
 * m_nHeads m_lDepsL etc could be initialised within the
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
  enum STACK_STATUS {
    OFF_STACK = 0, ON_STACK_SHIFT, ON_STACK_ARCRIGHT
  };

public:
  int m_Stack[MAX_SENTENCE_SIZE]; // stack of words that are currently processed
  int m_nStackSize;
  int m_nInnerStackSize;
  bool m_HeadSet[MAX_SENTENCE_SIZE]; // stack of words that already have heads
  int m_nHeadSetSize;
  int m_Action[3 * MAX_SENTENCE_SIZE];
  int m_nActionSize;
  int m_nNextWord;                         // index for the next word
  int m_nHeads[MAX_SENTENCE_SIZE];         // the lexical head for each word
  int m_nCoverStart[MAX_SENTENCE_SIZE];         // the left-most index of the tree dominated by current index
  int m_nCoverEnd[MAX_SENTENCE_SIZE];         // the left-most index of the tree dominated by current index
  //false denotes inner word, true denotes outer word
  bool m_bLabelTypes[MAX_SENTENCE_SIZE];  // the label of each dependency link
  unsigned long m_nLastAction;                  // the last stack action
  int m_nSentLen;
  unsigned long m_nPOSs[MAX_SENTENCE_SIZE];
  //true denotes word start, otherwise false
  bool m_bPOSTypes[MAX_SENTENCE_SIZE];

public:
  SCORE_TYPE score; // score of stack - predicting how potentially this is the correct one
  const CStateItem * m_preState;

public:
  // constructors and destructor
  CStateItem(int nSentLen = 0) :
      m_nSentLen(nSentLen) {
    clear();
  }
  ~CStateItem() {
  }

  CStateItem(CStateItem& item) {
    m_nStackSize = item.m_nStackSize;
    m_nInnerStackSize = item.m_nInnerStackSize;

    for (int i = 0; i < m_nStackSize; i++) {
      m_Stack[i] = item.m_Stack[i];
    }

    m_nActionSize = item.m_nActionSize;

    for (int i = 0; i < m_nActionSize; i++) {
      m_Action[i] = item.m_Action[i];
    }

    m_nHeadSetSize = item.m_nHeadSetSize;
    m_nNextWord = item.m_nNextWord;

    m_nLastAction = item.m_nLastAction;
    m_nSentLen = item.m_nSentLen;
    score = item.score;
    for (int i = 0; i <= m_nNextWord; ++i) { // only copy active word (including m_nNext)
      m_HeadSet[i] = item.m_HeadSet[i];
      {
        m_nHeads[i] = item.m_nHeads[i];
        m_nCoverStart[i] = item.m_nCoverStart[i];
        m_nCoverEnd[i] = item.m_nCoverEnd[i];
        m_bLabelTypes[i] = item.m_bLabelTypes[i];
      }
      m_nPOSs[i] = item.m_nPOSs[i];
      m_bPOSTypes[i] = item.m_bPOSTypes[i];
    }
    m_preState = item.m_preState;
    ClearNext();
  }

public:
  // comparison
  inline bool operator <(const CStateItem &item) const {
    return score < item.score;
  }
  inline bool operator >(const CStateItem &item) const {
    return score > item.score;
  }
  inline bool operator ==(const CStateItem &item) const {
    int i;
    if (m_nNextWord != item.m_nNextWord)
      return false;
    for (i = 0; i < m_nNextWord; ++i) {
      if (m_nPOSs[i] != item.m_nPOSs[i])
        return false;
      if (m_bPOSTypes[i] != item.m_bPOSTypes[i])
        return false;
    }

    if (m_nStackSize != item.m_nStackSize)
      return false;
    if (m_nInnerStackSize != item.m_nInnerStackSize)
      return false;
    if (m_nStackSize > 0) {
      for (int i = 0; i < m_nStackSize; i++) {
        if (m_Stack[i] != item.m_Stack[i]) {
          return false;
        }
      }
    }

    if (m_nActionSize != item.m_nActionSize)
      return false;
    if (m_nActionSize > 0) {
      for (int i = 0; i < m_nActionSize; i++) {
        if (m_Action[i] != item.m_Action[i]) {
          return false;
        }
      }
    }

    if (m_nHeadSetSize != item.m_nHeadSetSize)
      return false;
    if (m_nHeadSetSize > 0) {
      for (int i = 0; i < m_nNextWord; i++) {
        if (m_HeadSet[i] != item.m_HeadSet[i]) {
          return false;
        }
        if (m_HeadSet[i]) {
          if (m_nHeads[i] != item.m_nHeads[i]) {
            return false;
          }
          if (m_bLabelTypes[i] != item.m_bLabelTypes[i]) {
            return false;
          }
        } else {
          if (m_nHeads[i] != item.m_nHeads[i]) {
            return false;
          }
          if (m_bLabelTypes[i] != item.m_bLabelTypes[i]) {
            return false;
          }
        }
      }
    }

    // I think that the stacks don't have to be compared
    // might be proved by translating tree to stack
    //assert( m_Stack == item.m_Stack );
    return true;
  }

  inline bool operator !=(const CStateItem &item) const {
    return !((*this) == item);
  }

  // propty
  inline int stacksize() const {
    return m_nStackSize;
  }
  inline int innerstacksize() const {
    return m_nInnerStackSize;
  }
  inline bool stackempty() const {
    return m_nStackSize <= 0;
  }
  inline int stacktop() const {
    if (m_nStackSize <= 0) {
      std::cout << "error" << std::endl;
    }
    return m_Stack[m_nStackSize - 1];
  }
  inline int stackbottom() const {
    assert(m_nStackSize > 0);
    return m_Stack[0];
  }
  inline int stackitem(const unsigned &index) const {
    assert(index < m_nStackSize);
    return m_Stack[index];
  }

  inline int headsetsize() const {
    return m_nHeadSetSize;
  }
  inline bool headsetempty() const {
    return m_nHeadSetSize <= 0;
  }

  inline int actionsize() const {
    return m_nActionSize;
  }
  inline bool actionempty() const {
    return m_nActionSize <= 0;
  }

  inline void setsentsize(int nSentLen) {
    m_nSentLen = nSentLen;
  }

  inline int wordstart(int index) const {
    if (index < m_nNextWord && index >= 0) {
      return m_nCoverStart[index];
    } else {
      return -1;
    }
  }

  inline int wordend(int index) const {
    if (index < m_nNextWord && index >= 0) {
      return m_nCoverEnd[index];
    } else {
      return -1;
    }
  }



  inline int head(const int &index) const {
    if (index < m_nNextWord && index >= 0 && m_HeadSet[index]) {
      return m_nHeads[index];
    } else {
      // this is an error
      return -1;
    }
  }

  inline int pos(const int &index) const {
    if (index <= m_nNextWord && index >= 0) {
      return m_nPOSs[index];
    } else {
      // this is an error
      return -1;
    }
  }

  inline int nextword() const {
    return m_nNextWord;
  }

  void clear() {
    m_nNextWord = 0;
    m_nStackSize = 0;
    m_nInnerStackSize = 0;
    m_nHeadSetSize = 0;
    m_nActionSize = 0;
    score = 0;
    m_nLastAction = action::NO_ACTION;
    m_preState = 0;
    ClearNext();
  }

  void operator =(const CStateItem &item) {
    m_nStackSize = item.m_nStackSize;
    m_nInnerStackSize = item.m_nInnerStackSize;

    for (int i = 0; i < m_nStackSize; i++) {
      m_Stack[i] = item.m_Stack[i];
    }

    m_nActionSize = item.m_nActionSize;

    for (int i = 0; i < m_nActionSize; i++) {
      m_Action[i] = item.m_Action[i];
    }

    m_nHeadSetSize = item.m_nHeadSetSize;
    m_nNextWord = item.m_nNextWord;

    m_nLastAction = item.m_nLastAction;
    m_nSentLen = item.m_nSentLen;
    score = item.score;
    for (int i = 0; i <= m_nNextWord; ++i) { // only copy active word (including m_nNext)
      m_HeadSet[i] = item.m_HeadSet[i];
      {
        m_nHeads[i] = item.m_nHeads[i];
        m_nCoverStart[i] = item.m_nCoverStart[i];
        m_nCoverEnd[i] = item.m_nCoverEnd[i];
        m_bLabelTypes[i] = item.m_bLabelTypes[i];
      }
      m_nPOSs[i] = item.m_nPOSs[i];
      m_bPOSTypes[i] = item.m_bPOSTypes[i];
    }
    m_preState = item.m_preState;
    ClearNext();
  }

//-----------------------------------------------------------------------------

public:

  bool canarcin() const {
    if (m_nInnerStackSize > 1) {
      return true;
    } else {
      return false;
    }
  }

  bool canshiftin() const {
    if (m_nInnerStackSize > 0 && m_nNextWord < m_nSentLen) {
      return true;
    } else {
      return false;
    }
  }

  bool canshift() const {
    if ((m_nStackSize == 0 || m_nInnerStackSize == 1) && m_nNextWord < m_nSentLen) {
      return true;
    } else {
      return false;
    }
  }

  bool canfinish() const {
    if ((m_nStackSize == 0 || m_nInnerStackSize == 1) && m_nNextWord == m_nSentLen) {
      return true;
    } else {
      return false;
    }
  }

  // the arc left action links the current stack top to the next word with popping

  void ArcLeft() {
    if (!canarcin()) {
      std::cout << "error" << std::endl;
    }
    static int top0, top1;
    top0 = m_Stack[m_nStackSize - 1];
    top1 = m_Stack[m_nStackSize - 2];
    if (m_bLabelTypes[top0] || m_bLabelTypes[top1]) {
      std::cout << "error" << std::endl;
    }
    m_nStackSize--;
    m_nInnerStackSize--;
    m_Stack[m_nStackSize - 1] = top0;
    m_nHeads[top1] = top0;
    m_HeadSet[top1] = true;
    m_nCoverStart[top0] = m_nCoverStart[top1];
    m_nHeadSetSize++;

    m_nLastAction = action::encodeAction(action::ARC_LEFT);
    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  // the arc right action links the next word to the current stack top with pushing

  void ArcRight() {
    if (!canarcin()) {
      std::cout << "error" << std::endl;
    }
    static int top0, top1;
    top0 = m_Stack[m_nStackSize - 1];
    top1 = m_Stack[m_nStackSize - 2];
    if (m_bLabelTypes[top0] || m_bLabelTypes[top1]) {
      std::cout << "error" << std::endl;
    }
    m_nStackSize--;
    m_nInnerStackSize--;
    m_Stack[m_nStackSize - 1] = top1;
    m_nHeads[top0] = top1;
    m_HeadSet[top0] = true;
    m_nCoverEnd[top1] = m_nCoverEnd[top0];
    m_nHeadSetSize++;

    m_nLastAction = action::encodeAction(action::ARC_RIGHT);
    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  // the shift action does pushing
  void ShiftIn() {
    if (!canshiftin()) {
      std::cout << "error" << std::endl;
    }

    m_nStackSize++;
    m_nInnerStackSize++;
    m_Stack[m_nStackSize - 1] = m_nNextWord;

    m_nPOSs[m_nNextWord] = m_nPOSs[m_nNextWord - 1];
    m_bPOSTypes[m_nNextWord] = false;
    m_bLabelTypes[m_nNextWord] = false;

    m_nCoverStart[m_nNextWord] = m_nNextWord;
    m_nCoverEnd[m_nNextWord] = m_nNextWord;

    m_nNextWord++;
    m_nLastAction = action::encodeAction(action::SHIFT_IN);
    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  // the shift action does pushing
  void Shift(unsigned long lab) {
    if (!canshift()) {
      std::cout << "error" << std::endl;
    }

    int top0 = m_nStackSize > 0 ? m_Stack[m_nStackSize - 1] : -1;

    m_nStackSize++;
    m_nInnerStackSize = 1;
    m_Stack[m_nStackSize - 1] = m_nNextWord;

    m_nPOSs[m_nNextWord] = lab;
    m_bPOSTypes[m_nNextWord] = true;
    m_bLabelTypes[m_nNextWord] = false;
    if(top0>0)m_bLabelTypes[top0] = true;

    m_nCoverStart[m_nNextWord] = m_nNextWord;
    m_nCoverEnd[m_nNextWord] = m_nNextWord;

    m_nNextWord++;

    m_nLastAction = action::encodeAction(action::SHIFT, lab);

    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  // this is used for the convenience of scoring and updating
  void Finish() {
    if (!canfinish()) {
      std::cout << "error" << std::endl;
    }

    int top0 = m_Stack[m_nStackSize - 1];
    m_nInnerStackSize = 0;
    m_bLabelTypes[top0] = true;
    m_nNextWord++;

    m_nLastAction = action::encodeAction(action::FINISH);

    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  void Idle() {
    assert(IsTerminated());
    m_nLastAction = action::encodeAction(action::IDLE);
    m_Action[m_nActionSize] = m_nLastAction;
    m_nActionSize++;
    ClearNext();
  }

  // the clear next action is used to clear the next word, used with forwarding the next word index
  void ClearNext() {
    m_Stack[m_nStackSize] = -1;
    m_Action[m_nActionSize] = -1;
    m_HeadSet[m_nNextWord] = false;
    m_nHeads[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
    m_nCoverStart[m_nNextWord] = -1;
    m_nCoverEnd[m_nNextWord] = -1;
    m_nPOSs[m_nNextWord] = false;
    m_bPOSTypes[m_nNextWord] = 0;
    m_bLabelTypes[m_nNextWord] = false;
  }

  // the move action is a simple call to do action according to the action code
  void Move(const unsigned long &ac) {
    switch (action::getUnlabeledAction(ac)) {
    case action::NO_ACTION:
      return;
    case action::SHIFT:
      Shift(action::getLabel(ac));
      return;
    case action::ARC_LEFT:
      ArcLeft();
      return;
    case action::ARC_RIGHT:
      ArcRight();
      return;
    case action::FINISH:
      Finish();
      return;
    case action::IDLE:
      Idle();
      return;
    case action::SHIFT_IN:
      ShiftIn();
      return;
    default:
      THROW("unknown action: " << ac << '.');
    }
  }

//-----------------------------------------------------------------------------

public:

  // returns true is the next word advances -- by shift or arcright.
  bool StandardMoveStep(const CDependencyParse &tree) {
    static int top0, top1;
    if (IsTerminated()) {
      Idle();
      return false;
    } else if (m_nStackSize == 0) {
      assert(m_nNextWord == 0 && tree[m_nNextWord].tagtype.compare("b") == 0);
      Shift(CTag(tree[m_nNextWord].tag).code());
      return true;
    } else if (m_nInnerStackSize == 1) {
      if (m_nNextWord == static_cast<int>(tree.size())) {
        Finish();
        return true;
      } else {
        if (tree[m_nNextWord].tagtype.compare("b") == 0) {
          Shift(CTag(tree[m_nNextWord].tag).code());
          return true;
        } else {
          ShiftIn();
        }
        return true;
      }
    } else {
      assert(m_nInnerStackSize > 1);
      top0 = m_Stack[m_nStackSize - 1];
      top1 = m_Stack[m_nStackSize - 2];
      bool bTop0HasRightChild = false;
      for (int i = m_nNextWord; i < tree.size(); i++) {
        if (tree[i].tagtype.compare("b") == 0) {
          break;
        }
        if (tree[i].head == top0) {
          bTop0HasRightChild = true;
          break;
        }
      }
      if (tree[top0].head == top1 && !bTop0HasRightChild) {
        ArcRight();
        return false;
      } else if (tree[top1].head == top0) {
        ArcLeft();
        return false;
      } else {
        ShiftIn();
        return true;
      }
    }
  }

  // we want to pop the root item after the whole tree done
  // on the one hand this seems more natural
  // on the other it is easier to score
  //bool StandardFinish() {
  //   return ( m_nStackSize == 0 && m_nNextWord == m_nSentLen);
  //}

  bool IsTerminated() const {
    return m_nLastAction == action::FINISH || m_nLastAction == action::IDLE;
  }

  bool IsIdle() const {
    return m_nLastAction == action::IDLE;
  }

  unsigned FollowMove(const CStateItem *item) {
    static int top0, top1;
    // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
    if (IsTerminated()) {
      return action::encodeAction(action::IDLE);
    } else if (m_nNextWord == item->m_nNextWord) {
      if (m_nInnerStackSize > 1) {
        top0 = m_Stack[m_nStackSize - 1];
        top1 = m_Stack[m_nStackSize - 2];
        if (item->m_HeadSet[top1] && item->m_nHeads[top1] == top0) {
          return action::encodeAction(action::ARC_LEFT);
        } else if (item->m_HeadSet[top0] && item->m_nHeads[top0] == top1) {
          return action::encodeAction(action::ARC_RIGHT);
        }
      } else if (m_nInnerStackSize == 1) {
        // only shift, finish
        std::cout << "impossible" << std::endl;
      }
    } else {
      assert(m_nNextWord < item->m_nNextWord);
      if (m_nInnerStackSize > 1) {
        top0 = m_Stack[m_nStackSize - 1];
        top1 = m_Stack[m_nStackSize - 2];

        bool bTop0HasRightChild = false;
        for (int i = m_nNextWord; i < item->m_nNextWord; i++) {
          if (item->m_bPOSTypes[i]) {
            break;
          }
          if (item->head(i) == top0) {
            bTop0HasRightChild = true;
            break;
          }
        }

        if (item->m_HeadSet[top1] && item->m_nHeads[top1] == top0) {
          return action::encodeAction(action::ARC_LEFT);
        } else if (item->m_HeadSet[top0] && item->m_nHeads[top0] == top1 && !bTop0HasRightChild) {
          return action::encodeAction(action::ARC_RIGHT);
        } else {
          return action::encodeAction(action::SHIFT_IN);
        }

      } else if (m_nInnerStackSize == 1) {
        if (m_nNextWord == m_nSentLen) {
          return action::encodeAction(action::FINISH);
        } else if (m_nNextWord < m_nSentLen) {
          if (m_bPOSTypes[m_nNextWord]) {
            return action::encodeAction(action::SHIFT, item->m_nPOSs[m_nNextWord]);
          } else {
            return action::encodeAction(action::SHIFT_IN);
          }
        }
      } else {
        assert(m_nInnerStackSize == 0 && m_nNextWord == 0);
        return action::encodeAction(action::SHIFT, item->m_nPOSs[m_nNextWord]);
      }
    }
  }

  void GenerateTree(const CStringVector &input, CDependencyParse &output) const {
    output.clear();
    for (int i = 0; i < nextword() && i < m_nSentLen; ++i)
      output.push_back(
          CCharDependencyTreeNode(input.at(i), CTag(m_nPOSs[i]).str(), m_bPOSTypes[i] ? "b" : "i", m_nHeads[i], "ROOT",
              m_bLabelTypes[i] ? "out" : "in"));
  }

};

#endif
