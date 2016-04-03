#ifndef CHARTAGGER_ACTION_H
#define CHARTAGGER_ACTION_H

namespace action {

// SH AL AR [SH+POS]
enum STACK_ACTION {
  NO_ACTION = 0, SHIFT_IN, ARC_LEFT, ARC_RIGHT, SHIFT, FINISH, IDLE, LABEL_SH_FIRST, MAX = LABEL_SH_FIRST + POS_LABEL_COUNT - 1
};

static unsigned encodeAction(const STACK_ACTION &action, const unsigned &label = 0) {
  if (action == SHIFT) {
    assert(label < POS_LABEL_COUNT);
    return LABEL_SH_FIRST + label - 1;
  } else
    assert(label == 0);


  return action;
}
static unsigned getUnlabeledAction(const unsigned &action) {
  assert(action < MAX);
  if (action < LABEL_SH_FIRST)
    return action;
  else
    return SHIFT;
}
static unsigned getLabel(const unsigned &action) {
  assert(action < MAX);
  if (action < LABEL_SH_FIRST)
    return 0;
  else
    return action - LABEL_SH_FIRST + 1;
}

struct CScoredAction {
  unsigned action;
  SCORE_TYPE score;
public:
  bool operator <(const CScoredAction &a) const {
    return score < a.score;
  }
  bool operator >(const CScoredAction &a) const {
    return score > a.score;
  }
};

} //namespace
#endif
