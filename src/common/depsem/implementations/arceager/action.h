#ifndef DEPSEM_ACTION_H
#define DEPSEM_ACTION_H

namespace action {

// SH RE AL AR PR [AL+LABEL] AR+LABEL
enum STACK_ACTION { NO_ACTION=0, SHIFT, REDUCE, ARC_LEFT, ARC_RIGHT, POP_ROOT, LABEL_AL_FIRST, LABEL_AR_FIRST=LABEL_AL_FIRST+MAX_LABEL_COUNT, MAX=LABEL_AR_FIRST+MAX_LABEL_COUNT };

#ifdef LABELED
static unsigned long encodeAction(const STACK_ACTION &action, const unsigned long &synlabel=0, const unsigned long &semlabel=0) {
   assert(synlabel<=DEP_LABEL_COUNT && semlabel<=SEM_LABEL_COUNT);
   if (action==ARC_LEFT) {
	  if(synlabel==0 || semlabel==0)
	  {
		  assert(0);
	  }
      return LABEL_AL_FIRST+(synlabel-1)*SEM_LABEL_COUNT+semlabel-1;
   }
   else if (action==ARC_RIGHT) {
	  if(synlabel==0 || semlabel==0)
	  {
		  assert(0);
	  }
      return LABEL_AR_FIRST+(synlabel-1)*SEM_LABEL_COUNT+semlabel-1;
   }
   else
	   assert(synlabel==0 && semlabel==0);
   return action;
}
static unsigned long getUnlabeledAction(const unsigned long &action ) {
   assert(action<MAX);
   if (action<LABEL_AL_FIRST)
      return action;
   else if (action<LABEL_AR_FIRST)
      return ARC_LEFT;
   else
      return ARC_RIGHT;
}
static unsigned long getSynLabel(const unsigned long &action) {
   assert(action<MAX);
   if (action < LABEL_AL_FIRST)
      return 0;
   else if (action < LABEL_AR_FIRST)
      return (action-LABEL_AL_FIRST)/SEM_LABEL_COUNT+1;
   else
      return (action-LABEL_AR_FIRST)/SEM_LABEL_COUNT+1;
}

static unsigned long getSemLabel(const unsigned long &action) {
   assert(action<MAX);
   if (action < LABEL_AL_FIRST)
      return 0;
   else if (action < LABEL_AR_FIRST)
      return (action-LABEL_AL_FIRST)%SEM_LABEL_COUNT+1;
   else
      return (action-LABEL_AR_FIRST)%SEM_LABEL_COUNT+1;
}
#endif

struct CScoredAction {
   unsigned long action;
   SCORE_TYPE score;
public:
   bool operator < (const CScoredAction &a) const {
      return score < a.score;
   }
   bool operator > (const CScoredAction &a) const {
      return score > a.score;
   }
};

}//namespace
#endif
