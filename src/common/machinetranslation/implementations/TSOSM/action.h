#ifndef MACHINETRANS_ACTION_H
#define MACHINETRANS_ACTION_H


//enum STACK_ACTION { NO_ACTION=0, SHIFT_Y, GENERATE_XY, GENERATE_X, GENERATE_Y, GENERATE_XX, SHIFT_X, INSERT_GAP, JUMP_BACK, JUMP_FORWARD, FINISH, IDLE, MAX};
class CActionType {

public:
   static const unsigned long SIZE=4;
   enum CODE {NO_ACTION=0, SHIFT_X=1, INSERT_GAP=2,
	   JUMP_BACK=3, JUMP_FORWARD=4, FINISH=5, IDLE=6,
	   GENERATE_XY=7, GENERATE_X=8};

public:
   unsigned long code;

public:
   CActionType(unsigned long ac) : code(ac){}
   CActionType() : code(0){}

public:
   const unsigned long &hash() const {return code;}
   bool operator == (const CActionType &a1) const { return code == a1.code; }
   bool operator != (const CActionType &a1) const { return code != a1.code; }

   inline void operator = ( const unsigned long &item ) {
 	  code = item;
   }

   inline void operator = ( const CActionType &item ) {
 	  code = item.code;
   }
   bool operator < (const CActionType &a1) const { return code < a1.code; }
   bool operator > (const CActionType &a1) const { return code > a1.code; }

   std::string str()
   {
	   std::string os;
	   switch(code) {
	   case CActionType::NO_ACTION:
	      os = "NO_ACTION";
	      break;
	   case CActionType::GENERATE_XY:
	      os = "GENERATE_XY";
	      break;
	   case CActionType::GENERATE_X:
	      os = "GENERATE_X";
	      break;
	   case CActionType::SHIFT_X:
	       os = "SHIFT_X";
	       break;
	   case CActionType::INSERT_GAP:
	       os = "INSERT_GAP";
	       break;
	   case CActionType::JUMP_BACK:
	       os = "JUMP_BACK";
	       break;
	   case CActionType::JUMP_FORWARD:
	       os = "JUMP_FORWARD";
	      break;
	   case CActionType::FINISH:
	       os = "FINISH";
	       break;
	   case CActionType::IDLE:
	       os = "IDLE";
	       break;
	   default:
	      THROW("Internal error: unknown action type code (" << code << ")");
	   }
	   return os;
   }

};

inline std::istream & operator >> (std::istream &is, CActionType &action) {
   std::string s;
   is >> s;
   if (s=="NO_ACTION")
      action.code = CActionType::NO_ACTION;
   else if (s=="GENERATE_XY")
      action.code = CActionType::GENERATE_XY;
   else if (s=="GENERATE_X")
      action.code = CActionType::GENERATE_X;
   else if (s=="SHIFT_X")
      action.code = CActionType::SHIFT_X;
   else if (s=="INSERT_GAP")
      action.code = CActionType::INSERT_GAP;
   else if (s=="JUMP_BACK")
      action.code = CActionType::JUMP_BACK;
   else if (s=="JUMP_FORWARD")
      action.code = CActionType::JUMP_FORWARD;
   else if (s=="FINISH")
      action.code = CActionType::FINISH;
   else if (s=="IDLE")
      action.code = CActionType::IDLE;
   else
      THROW("Action type unrecognized (" << s << ")");
   return is;
}

inline std::ostream & operator << (std::ostream &os, const CActionType &action) {
   switch(action.code) {
   case CActionType::NO_ACTION:
      os << "NO_ACTION";
      break;
   case CActionType::GENERATE_XY:
      os << "GENERATE_XY";
      break;
   case CActionType::GENERATE_X:
      os << "GENERATE_X";
      break;
   case CActionType::SHIFT_X:
       os << "SHIFT_X";
       break;
   case CActionType::INSERT_GAP:
       os << "INSERT_GAP";
       break;
   case CActionType::JUMP_BACK:
       os << "JUMP_BACK";
       break;
   case CActionType::JUMP_FORWARD:
        os << "JUMP_FORWARD";
        break;
   case CActionType::FINISH:
        os << "FINISH";
        break;
   case CActionType::IDLE:
        os << "IDLE";
        break;
   default:
      THROW("Internal error: unknown action type code (" << action.code << ")");
   }
   return os;
}

class CAction
{
public:
	static unsigned long MAX;
	static void SetMax(int rulesize)
	{
		MAX = rulesize + CActionType::IDLE;
	}

protected:
   unsigned long action;

public:
   void clear() { action=0; }

public:
  CAction() : action(0) {}

  CAction(unsigned long ac) : action(ac){}

  CAction(const CAction &item) : action(item.action){}

  inline unsigned long code() const{return action;}

  inline unsigned long hash() const{return action;}

public:
  inline void operator = ( const unsigned long &item ) {
	  action = item;
  }

  inline void operator = ( const CAction &item ) {
	  action = item.action;
  }

  inline bool operator == (const unsigned long &item) const {
	  if(item == action) return true;
	  return false;
  }

  inline bool operator == (const CAction &item) const {
	  if(item.action == action) return true;
	  return false;
  }

public:
   inline bool isNone(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::NO_ACTION; }
   inline bool isIdle(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::IDLE; }
   inline bool isFinish(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::FINISH; }
   inline bool isInsertGap(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::INSERT_GAP; }
   inline bool isJumpBack(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::JUMP_BACK; }
   inline bool isJumpForward(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::JUMP_FORWARD; }
   inline bool isShiftX(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::SHIFT_X; }
   inline bool isGenerateXY(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::GENERATE_XY; }
   inline bool isGenerateX(const std::vector<int >& mapTranslateRuleTypes) const { return type(mapTranslateRuleTypes)==CActionType::GENERATE_X; }


public:
   static unsigned long encodeNone() { return CActionType::NO_ACTION; }
   static unsigned long encodeIdle() { return CActionType::IDLE; }
   static unsigned long encodeFinish() { return CActionType::FINISH; }
   static unsigned long encodeInsertGap() { return CActionType::INSERT_GAP; }
   static unsigned long encodeJumpBack() { return CActionType::JUMP_BACK; }
   static unsigned long encodeJumpForward() { return CActionType::JUMP_FORWARD; }
   static unsigned long encodeShiftX() { return CActionType::SHIFT_X; }
   static unsigned long encodeGenerateXY(int ruleId) { return CActionType::IDLE+1+ruleId; }
   static unsigned long encodeGenerateX(int ruleId) {  return CActionType::IDLE+1+ruleId; }


public:
   inline unsigned long type(const std::vector<int >& mapTranslateRuleTypes) const {
      if(action < CActionType::IDLE+1)
      {
    	  return action;
      }
      else
      {
    	  int ruleId = action - CActionType::IDLE -1;
    	  //if(ruleId == 10146)
    	  //{
    		//  std::cout << "debug:" << mapTranslateRuleTypes.size() << std::endl;
    		 // std::cout.flush();
    	  //}
    	  if(mapTranslateRuleTypes[ruleId] == -1)
    	  {
    		  return CActionType::GENERATE_X;
    	  }
    	  else
    	  {
    		  if(mapTranslateRuleTypes[ruleId] != 0)
    		  {
    			  return CActionType::NO_ACTION;
    		  }
    		  return CActionType::GENERATE_XY;
    	  }
      }
   }

   int getRuleID()
   {
	      if(action < CActionType::IDLE+1)
	      {
	    	  return -1;
	      }
	      else
	      {
	    	  return action - CActionType::IDLE -1;
	      }
   }

   std::string str()
   {
	   std::stringstream ssc;
	   ssc << action;
	   return ssc.str();
   }

   bool operator < (const CAction &a1) const { return action < a1.action; }
   bool operator > (const CAction &a1) const { return action > a1.action; }
};

inline std::ostream & operator << (std::ostream &os, const CAction &action)
{
	os << action.code();
}

inline std::istream & operator >> (std::istream &is, CAction &action) {
   unsigned long code;;
   is >> code;
   action = code;
}

struct CScoredAction {
   CAction action;
   SCORE_TYPE score;

public:
   bool operator < (const CScoredAction &a) const {
      return score < a.score;
   }
   bool operator > (const CScoredAction &a) const {
      return score > a.score;
   }
};

#endif
