// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * penn.h - the definitions for english cfg                     *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2006.10                        *
 *                                                              *
 ****************************************************************/

namespace english {

// the penn constituent set
const std::string PENN_DIS_STRINGS[] = {
   "-NONE-",
   "-BEGIN-",
   "elaboration-additional#l", "elaboration-object-attribute-e#l",
   "attribution#r", "List#c", "Same-Unit#c",
   "attribution#l", "elaboration-additional-e#l",
   "explanation-argumentative#l", "purpose#l",
   "Contrast#c", "elaboration-general-specific#l",
   "circumstance#l", "circumstance#r", "example#l",
   "consequence-s#l", "antithesis#r", "Sequence#c",
   "concession#r", "interpretation-s#l", "evidence#l",
   "reason#l", "antithesis#l", "evaluation-s#l",
   "comment#l", "TextualOrganization#c", "background#l",
   "comparison#l", "attribution-e#l", "condition#r",
   "Comparison#c", "Topic-Shift#c", "means#l",
   "condition#l", "result#l", "background#r",
   "Topic-Drift#c", "manner#l", "elaboration-object-attribute#l",
   "restatement#l", "Temporal-Same-Time#c",
   "elaboration-set-member#l", "concession#l",
   "consequence-n#r", "definition#l", "temporal-after#l",
   "Cause-Result#c", "restatement-e#l", "consequence-n#l",
   "temporal-same-time#l", "summary-n#l", "elaboration-general-specific-e#l",
   "attribution-n#r", "elaboration-set-member-e#l",
   "result#r", "Problem-Solution#c", "example-e#l",
   "cause#l", "purpose-e#l", "temporal-before#l",
   "hypothetical#l", "purpose#r", "elaboration-part-whole#l",
   "Statement-Response#c", "reason#r", "circumstance-e#r",
   "Disjunction#c", "Question-Answer#c", "Consequence#c",
   "circumstance-e#l", "temporal-after#r", "temporal-same-time#r",
   "enablement#l", "rhetorical-question#l",
   "interpretation-n#r", "condition-e#r", "contingency#l",
   "comment#r", "Inverted-Sequence#c", "evaluation-n#r",
   "elaboration-part-whole-e#l", "Otherwise#c",
   "comment-e#l", "summary-s#l", "concession-e#r",
   "comparison#r", "explanation-argumentative#r",
   "definition-e#l", "analogy#l", "contingency#r",
   "means#r", "hypothetical#r", "enablement#r",
   "antithesis-e#r", "problem-solution-n#r",
   "preference#r", "summary-s#r", "cause#r",
   "Reason#c", "manner-e#l", "elaboration-additional-e#r",
   "elaboration-additional#r", "comparison-e#l",
   "preference#l", "interpretation-s-e#l", "evaluation-s#r",
   "manner#r", "problem-solution-s#l", "attribution-n#l",
   "summary-n#r", "temporal-before#r", "consequence-s-e#l",
   "means-e#l", "condition-e#l", "consequence-s#r",
   "Topic-Comment#c", "Evaluation#c", "evaluation-s-e#l",
   "conclusion#l", "analogy#r", "antithesis-e#l",
   "example#r", "reason-e#r", "attribution-e#r",
   "temporal-same-time-e#l", "consequence-n-e#l",
   "temporal-after-e#r", "temporal-after-e#l",
   "topic-shift#l", "topic-drift#l", "statement-response-s#l",
   "Proportion#c", "analogy-e#l", "purpose-e#r",
   "question-answer-n#l", "question-answer-n#r",
   "elaboration-part-whole#r", "rhetorical-question#r",
   "temporal-same-time-e#r", "interpretation-s#r",
   "question-answer-s#l", "consequence-n-e#r",
   "concession-e#l", "statement-response-n#r",
   "explanation-argumentative-e#l", "consequence-s-e#r",
   "result-e#l", "Comment-Topic#c", "elaboration-process-step#l",
   "Interpretation#c", "otherwise#l", "result-e#r",
   "elaboration-general-specific-e#r", "evidence#r",
   "comment-e#r", "elaboration-set-member#r",
   "elaboration-process-step-e#l", "Analogy#c",
   "restatement#r", "question-answer-s#r", "conclusion#r",
   "explanation-argumentative-e#r", "temporal-before-e#r",
   "means-e#r", "manner-e#r", "background-e#l",
   "preference-e#l", "otherwise#r", "Consequence#r",
   "analogy-e#r", "enablement-e#l", "evidence-e#l",
   "elaboration-general-specific#r", "elaboration-object-attribute-e#r"
};


enum PENN_DIS_DISSTANTS {
   PENN_DIS_NONE=0,
   PENN_DIS_BEGIN=1,
   PENN_ELABORATION_ADDITIONAL_L, PENN_ELABORATION_OBJECT_ATTRIBUTE_E_L,
   PENN_ATTRIBUTION_R, PENN_LIST_C, PENN_SAME_UNIT_C,
   PENN_ATTRIBUTION_L, PENN_ELABORATION_ADDITIONAL_E_L,
   PENN_EXPLANATION_ARGUMENTATIVE_L, PENN_PURPOSE_L,
   PENN_CONTRAST_C, PENN_ELABORATION_GENERAL_SPECIFIC_L,
   PENN_CIRCUMSTANCE_L, PENN_CIRCUMSTANCE_R, PENN_EXAMPLE_L,
   PENN_CONSEQUENCE_S_L, PENN_ANTITHESIS_R, PENN_SEQUENCE_C,
   PENN_CONCESSION_R, PENN_INTERPRETATION_S_L, PENN_EVIDENCE_L,
   PENN_REASON_L, PENN_ANTITHESIS_L, PENN_EVALUATION_S_L,
   PENN_COMMENT_L, PENN_TEXTUALORGANIZATION_C, PENN_BACKGROUND_L,
   PENN_COMPARISON_L, PENN_ATTRIBUTION_E_L, PENN_CONDITION_R,
   PENN_COMPARISON_C, PENN_TOPIC_SHIFT_C, PENN_MEANS_L,
   PENN_CONDITION_L, PENN_RESULT_L, PENN_BACKGROUND_R,
   PENN_TOPIC_DRIFT_C, PENN_MANNER_L, PENN_ELABORATION_OBJECT_ATTRIBUTE_L,
   PENN_RESTATEMENT_L, PENN_TEMPORAL_SAME_TIME_C,
   PENN_ELABORATION_SET_MEMBER_L, PENN_CONCESSION_L,
   PENN_CONSEQUENCE_N_R, PENN_DEFINITION_L, PENN_TEMPORAL_AFTER_L,
   PENN_CAUSE_RESULT_C, PENN_RESTATEMENT_E_L, PENN_CONSEQUENCE_N_L,
   PENN_TEMPORAL_SAME_TIME_L, PENN_SUMMARY_N_L, PENN_ELABORATION_GENERAL_SPECIFIC_E_L,
   PENN_ATTRIBUTION_N_R, PENN_ELABORATION_SET_MEMBER_E_L,
   PENN_RESULT_R, PENN_PROBLEM_SOLUTION_C, PENN_EXAMPLE_E_L,
   PENN_CAUSE_L, PENN_PURPOSE_E_L, PENN_TEMPORAL_BEFORE_L,
   PENN_HYPOTHETICAL_L, PENN_PURPOSE_R, PENN_ELABORATION_PART_WHOLE_L,
   PENN_STATEMENT_RESPONSE_C, PENN_REASON_R, PENN_CIRCUMSTANCE_E_R,
   PENN_DISJUNCTION_C, PENN_QUESTION_ANSWER_C, PENN_CONSEQUENCE_C,
   PENN_CIRCUMSTANCE_E_L, PENN_TEMPORAL_AFTER_R, PENN_TEMPORAL_SAME_TIME_R,
   PENN_ENABLEMENT_L, PENN_RHETORICAL_QUESTION_L,
   PENN_INTERPRETATION_N_R, PENN_CONDITION_E_R, PENN_CONTINGENCY_L,
   PENN_COMMENT_R, PENN_INVERTED_SEQUENCE_C, PENN_EVALUATION_N_R,
   PENN_ELABORATION_PART_WHOLE_E_L, PENN_OTHERWISE_C,
   PENN_COMMENT_E_L, PENN_SUMMARY_S_L, PENN_CONCESSION_E_R,
   PENN_COMPARISON_R, PENN_EXPLANATION_ARGUMENTATIVE_R,
   PENN_DEFINITION_E_L, PENN_ANALOGY_L, PENN_CONTINGENCY_R,
   PENN_MEANS_R, PENN_HYPOTHETICAL_R, PENN_ENABLEMENT_R,
   PENN_ANTITHESIS_E_R, PENN_PROBLEM_SOLUTION_N_R,
   PENN_PREFERENCE_R, PENN_SUMMARY_S_R, PENN_CAUSE_R,
   PENN_REASON_C, PENN_MANNER_E_L, PENN_ELABORATION_ADDITIONAL_E_R,
   PENN_ELABORATION_ADDITIONAL_R, PENN_COMPARISON_E_L,
   PENN_PREFERENCE_L, PENN_INTERPRETATION_S_E_L, PENN_EVALUATION_S_R,
   PENN_MANNER_R, PENN_PROBLEM_SOLUTION_S_L, PENN_ATTRIBUTION_N_L,
   PENN_SUMMARY_N_R, PENN_TEMPORAL_BEFORE_R, PENN_CONSEQUENCE_S_E_L,
   PENN_MEANS_E_L, PENN_CONDITION_E_L, PENN_CONSEQUENCE_S_R,
   PENN_TOPIC_COMMENT_C, PENN_EVALUATION_C, PENN_EVALUATION_S_E_L,
   PENN_CONCLUSION_L, PENN_ANALOGY_R, PENN_ANTITHESIS_E_L,
   PENN_EXAMPLE_R, PENN_REASON_E_R, PENN_ATTRIBUTION_E_R,
   PENN_TEMPORAL_SAME_TIME_E_L, PENN_CONSEQUENCE_N_E_L,
   PENN_TEMPORAL_AFTER_E_R, PENN_TEMPORAL_AFTER_E_L,
   PENN_TOPIC_SHIFT_L, PENN_TOPIC_DRIFT_L, PENN_STATEMENT_RESPONSE_S_L,
   PENN_PROPORTION_C, PENN_ANALOGY_E_L, PENN_PURPOSE_E_R,
   PENN_QUESTION_ANSWER_N_L, PENN_QUESTION_ANSWER_N_R,
   PENN_ELABORATION_PART_WHOLE_R, PENN_RHETORICAL_QUESTION_R,
   PENN_TEMPORAL_SAME_TIME_E_R, PENN_INTERPRETATION_S_R,
   PENN_QUESTION_ANSWER_S_L, PENN_CONSEQUENCE_N_E_R,
   PENN_CONCESSION_E_L, PENN_STATEMENT_RESPONSE_N_R,
   PENN_EXPLANATION_ARGUMENTATIVE_E_L, PENN_CONSEQUENCE_S_E_R,
   PENN_RESULT_E_L, PENN_COMMENT_TOPIC_C, PENN_ELABORATION_PROCESS_STEP_L,
   PENN_INTERPRETATION_C, PENN_OTHERWISE_L, PENN_RESULT_E_R,
   PENN_ELABORATION_GENERAL_SPECIFIC_E_R, PENN_EVIDENCE_R,
   PENN_COMMENT_E_R, PENN_ELABORATION_SET_MEMBER_R,
   PENN_ELABORATION_PROCESS_STEP_E_L, PENN_ANALOGY_C,
   PENN_RESTATEMENT_R, PENN_QUESTION_ANSWER_S_R, PENN_CONCLUSION_R,
   PENN_EXPLANATION_ARGUMENTATIVE_E_R, PENN_TEMPORAL_BEFORE_E_R,
   PENN_MEANS_E_R, PENN_MANNER_E_R, PENN_BACKGROUND_E_L,
   PENN_PREFERENCE_E_L, PENN_OTHERWISE_R, PENN_CONSEQUENCE_R,
   PENN_ANALOGY_E_R, PENN_ENABLEMENT_E_L, PENN_EVIDENCE_E_L,
   PENN_ELABORATION_GENERAL_SPECIFIC_R, PENN_ELABORATION_OBJECT_ATTRIBUTE_E_R,
   PENN_DIS_COUNT
};


const int PENN_DIS_FIRST = 2;
const int PENN_DIS_COUNT_BITS = 9;

//===============================================================

class CDisConstituentLabel {
public:
   enum {NONE=0};
   enum {SENTENCE_BEGIN=PENN_DIS_BEGIN};
   enum {FIRST=PENN_DIS_FIRST};
   enum {COUNT=PENN_DIS_COUNT}; 
   enum {SIZE=PENN_DIS_COUNT_BITS};

protected:
   unsigned long m_code;

public:
   CDisConstituentLabel() { m_code=PENN_DIS_NONE; }
   CDisConstituentLabel(PENN_DIS_DISSTANTS t) { 
      m_code=t; 
   }
   CDisConstituentLabel(const unsigned long &t) { 
      m_code=t; 
   }
   CDisConstituentLabel(const std::string &s) { load(s); }
   virtual ~CDisConstituentLabel() {}

public:
   const unsigned long &code() const { return m_code; }
   const unsigned long &hash() const { return m_code; }
   void copy(const CDisConstituentLabel &c) {m_code = c.m_code; }
   const void clear() { m_code=NONE; }
   const bool empty() const { return m_code==NONE; }
   std::string str() const { assert(m_code<PENN_DIS_COUNT) ; return PENN_DIS_STRINGS[m_code]; }
   bool headleft() const
   {
	   assert(m_code<PENN_DIS_COUNT);
	   static int strlength;
	   strlength = PENN_DIS_STRINGS[m_code].length();
	   if(PENN_DIS_STRINGS[m_code][strlength-1] == 'r')
	   {
		   return false;
	   }
	   return true;
   }
   void load(const std::string &s) {
      m_code = PENN_DIS_NONE ;
      bool bFound = false;
      if (s.empty()) return;
      for (int i=0; i<PENN_DIS_COUNT; ++i) {
         if (PENN_DIS_STRINGS[i] == s) {
            m_code = i;
            bFound = true;
         }
      }
      // unknown constituent
      if (!bFound) {
         THROW("unknown constituent: " << s << '.');
      }
   }
   void load(const unsigned long &code) {m_code=code;}

public:
   bool operator == (const CDisConstituentLabel &t1) const { return m_code == t1.m_code; }
   bool operator < (const CDisConstituentLabel &t1) const { return m_code < t1.m_code; }
   bool operator > (const CDisConstituentLabel &t1) const { return m_code > t1.m_code; }
   bool operator <= (const CDisConstituentLabel &t1) const { return m_code <= t1.m_code; }
   bool operator >= (const CDisConstituentLabel &t1) const { return m_code >= t1.m_code; }
};

};

