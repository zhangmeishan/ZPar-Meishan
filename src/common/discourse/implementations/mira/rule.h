// Copyright (C) University of Oxford 2010
#ifndef _COMMON_CON_PARSER_RULE
#define _COMMON_CON_PARSER_RULE

/*===============================================================
 *
 * Rules
 *
 *==============================================================*/

#include "tuple2.h"

namespace TARGET_LANGUAGE {

namespace discourse {

class CRule {

protected:
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
   CRule(const std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > *sent,
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
		 const std::vector< int > *syn_ends) :
		 m_sent(sent),  m_edu_starts(edu_starts),  m_edu_ends(edu_ends),  m_edu_sentids(edu_sentids),  m_edu_paraids(edu_paraids),
		 m_sent_first_edus(sent_first_edus), m_para_first_edus(para_first_edus), m_edu_headspans(edu_headspans),
		 m_syn_nodes(syn_nodes), m_syn_roots(syn_roots),  m_syn_starts(syn_starts),  m_syn_ends(syn_ends){}
   virtual ~CRule() {
   }

public:
   void getActions(const CStateItem &item, std::vector<CAction> &actions) {
      actions.clear();

      static CAction action;
      const unsigned stack_size = item.stacksize();
      const unsigned &length = m_edu_starts->size();

      // finish
      if (item.IsTerminated()) {
         action.encodeIdle();
         actions.push_back(action);
         return;
      }
      // finish parsing
      if (item.IsComplete(length)) { 
         action.encodeReduceRoot();
         actions.push_back(action);
      }
      // shift
      if (item.current_edu < length ) {
         // do not shift for head right tmp item
         getShiftRules(item, actions);
      }
      // reduce bin
      if ( stack_size > 1 ) {
         getBinaryRules(item, actions);
      }
   }

protected:
   void getShiftRules(const CStateItem &item, std::vector<CAction> &actions) {
      static CAction action;
      // the default rules
	  action.encodeShift(0);
	  actions.push_back(action);

   }
   void getBinaryRules(const CStateItem &item,  std::vector<CAction> &actions) {
      static CAction action;
      const unsigned stack_size = item.stacksize();
      ASSERT(stack_size>0, "Binary reduce required for stack containing one node");

      for (unsigned long constituent=CDisConstituent::FIRST; constituent<CDisConstituent::COUNT; ++constituent) {
    	  bool head_left = CDisConstituent(constituent).headleft();
    	  action.encodeReduce(constituent, false, head_left, false);
    	  actions.push_back(action);
      }
   }

};

} // namespace discourse

}

#endif
