// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * machinetranslation.cpp - the action based translator implementation       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

#include "machinetranslation.h"
#include "machinetranslation_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::machinetranslation;

const CWord g_emptyWord("");


#define cast_weights static_cast<CWeight*>(m_weights)
#define cast_delta_weights static_cast<CWeight*>(m_delta_weight)
#define refer_or_allocate_tuple2(x, o1, o2) { if (amount == 0) x.refer(o1, o2); else x.allocate(o1, o2); }
#define refer_or_allocate_tuple3(x, o1, o2, o3) { if (amount == 0) x.refer(o1, o2, o3); else x.allocate(o1, o2, o3); }
#define refer_or_allocate_tuple4(x, o1, o2, o3, o4) { if (amount == 0) x.refer(o1, o2, o3, o4); else x.allocate(o1, o2, o3, o4); }
#define unit_feat_operation(x, f, w) {if (amount == 0) score += w*cast_weights->x.getOrUpdateScore(f, m_nScoreIndex , amount , round); \
                     else score+=cast_delta_weights->x.getOrUpdateScore(f, m_nScoreIndex , amount*w , round);}

/*===============================================================
 *
 * CMachineTrans - the machinetranslation for TARGET_LANGUAGE
 *
 *==============================================================*/

/*---------------------------------------------------------------
 * 
 * getOrUpdateStackScore - manipulate the score from stack 
 *
 *---------------------------------------------------------------*/

inline SCORE_TYPE CMachineTrans::getOrUpdateActionScore(const CStateItem *item,  CAction& action, SCORE_TYPE amount, unsigned long round ) {

	// to obtain the const model parameters, we use cast_weights
	//target language model
	SCORE_TYPE score = (SCORE_TYPE)0;
	int curx = item->m_nCurrentIndexInStackX;
	int ruleId = action.getRuleID();
	CActionType curAT = action.type(cast_weights->m_mapTranslateRuleTypes);

	static CTuple2<CWord,CWord> biWords;
	static CTuple3<CWord,CWord, CWord> triWords;

	static CTuple2<CAction,CAction> biActions;
	static CTuple3<CAction,CAction,CAction> triActions;
	static CTuple4<CAction,CAction,CAction,CAction> fourActions;

	static CTuple2<CActionType,CActionType> biActionTypes;
	static CTuple3<CActionType,CActionType,CActionType> triActionTypes;
	static CTuple4<CActionType,CActionType,CActionType,CActionType> fourActionTypes;

	static float prob, prob1, prob2;
	static int i;
	static std::vector<CWord> lConditionPhraseWords, lTranslatedPhraseWords;

	lConditionPhraseWords.clear();
	lTranslatedPhraseWords.clear();

	if(ruleId >= 0)
	{
		std::istringstream condition_str(cast_weights->m_mapTranslateSources[ruleId]);
		condition_str >> lConditionPhraseWords;
		for(i = 0; i < cast_weights->m_mapTranslateRules[ruleId].size(); i++)
		{
			lTranslatedPhraseWords.push_back(cast_weights->m_mapTranslateRules[ruleId][i]);
		}
	}



	static CAction prev1Action, prev2Action, prev3Action;
	static CActionType prev1AT, prev2AT, prev3AT;

	prev1Action = item->m_nActionSize>=1 ? item->m_Action[item->m_nActionSize-1] : CAction::encodeNone();
	prev1AT = item->m_nActionSize>=1 ? item->m_ActionType[item->m_nActionSize-1] : CActionType::NO_ACTION;
	prev2Action = item->m_nActionSize>=2 ? item->m_Action[item->m_nActionSize-2] : CAction::encodeNone();
	prev2AT = item->m_nActionSize>=2 ? item->m_ActionType[item->m_nActionSize-2] : CActionType::NO_ACTION;
	prev3Action = item->m_nActionSize>=3 ? item->m_Action[item->m_nActionSize-3] : CAction::encodeNone();
	prev3AT = item->m_nActionSize>=3 ? item->m_ActionType[item->m_nActionSize-3] : CActionType::NO_ACTION;


	static int leftgaps, left_gap_dist, leftmost_gap_dist, rightgaps, right_gap_dist, rightmost_gap_dist;

	leftgaps = 0;
	left_gap_dist = 0;
	leftmost_gap_dist = 0;

	rightgaps = 0;
	right_gap_dist = 0;
	rightmost_gap_dist = 0;

	for(i = item->m_nCurrentIndexInStackX-1; i>=0; i--)
	{
		if(item->m_StackX[i] == -1)
		{
			leftmost_gap_dist = item->m_nCurrentIndexInStackX-i;
			if(left_gap_dist == 0)
			{
				left_gap_dist = item->m_nCurrentIndexInStackX-i;
			}
			leftgaps++;
		}
	}

	for(i = item->m_nCurrentIndexInStackX; i<item->m_nStackXSize; i++)
	{
		if(item->m_StackX[i] == -1)
		{
			rightmost_gap_dist = i-item->m_nCurrentIndexInStackX+1;
			if(right_gap_dist == 0)
			{
				right_gap_dist = i-item->m_nCurrentIndexInStackX+1;
			}
			rightgaps++;
		}
	}

	//if(action.code() == 5535)
	//{
	//	std::cout << "debug begin" << std::endl;
	//}

	// language model features




	// translation table prob
	if(ruleId >= 0)
	{
		prob1 = cast_weights->m_mapTranslateRuleScore1s[ruleId];
		prob2 = cast_weights->m_mapTranslateRuleScore2s[ruleId];
		if(prob1 < LOWEAST_LOG_PROB) prob1 = LOWEAST_LOG_PROB;
		if(prob2 < LOWEAST_LOG_PROB) prob2 = LOWEAST_LOG_PROB;
		prob1 = prob1/TGT_LM_NORMALIZE;
		prob2 = prob2/TGT_LM_NORMALIZE;
		unit_feat_operation(m_mapSrcTgtProb, std::make_pair(lConditionPhraseWords.size(), lTranslatedPhraseWords.size()), prob1)
		unit_feat_operation(m_mapTgtSrcProb, std::make_pair(lConditionPhraseWords.size(), lTranslatedPhraseWords.size()), prob2)
	}


	//operation language model
	//bigram
	{
		prob = LOWEAST_LOG_PROB;
		if(m_osmLM2.element(prev1Action) &&
		   m_osmLM2[prev1Action].find(action) != m_osmLM2[prev1Action].end())
		{
			if(prob<m_osmLM2[prev1Action][action])prob=m_osmLM2[prev1Action][action];
		}
		prob = prob/OSM_LM_NORMALIZE;
		unit_feat_operation(m_mapOsmLM, 2, prob)

		if(item->m_nActionSize>0)
		{
			biActions.refer(&prev2Action, &prev1Action);
			prob = LOWEAST_LOG_PROB;
			if(m_osmLM3.element(biActions) &&
			   m_osmLM3[biActions].find(action) != m_osmLM3[biActions].end())
			{
				if(prob<m_osmLM3[biActions][action])prob=m_osmLM3[biActions][action];
			}
			prob = prob/OSM_LM_NORMALIZE;
			unit_feat_operation(m_mapOsmLM, 3, prob)
		}

		if(item->m_nActionSize>1)
		{
			triActions.refer(&prev3Action, &prev2Action, &prev1Action);
			prob = LOWEAST_LOG_PROB;
			if(m_osmLM4.element(triActions) &&
			   m_osmLM4[triActions].find(action) != m_osmLM4[triActions].end())
			{
				if(prob<m_osmLM4[triActions][action])prob=m_osmLM4[triActions][action];
			}
			prob = prob/OSM_LM_NORMALIZE;
			unit_feat_operation(m_mapOsmLM, 4, prob)
		}
	}


	// action ngram

	{
		unit_feat_operation(m_mapUniAction, action, 1)
		refer_or_allocate_tuple2(biActions, &prev1Action, &action);
		unit_feat_operation(m_mapBiAction, biActions, 1)
		refer_or_allocate_tuple3(triActions, &prev2Action, &prev1Action, &action);
		unit_feat_operation(m_mapTriAction, triActions, 1)
		refer_or_allocate_tuple4(fourActions, &prev3Action, &prev2Action, &prev1Action, &action);
		unit_feat_operation(m_mapFourAction, fourActions, 1)

		unit_feat_operation(m_mapUniActionType, curAT, 1)
		refer_or_allocate_tuple2(biActionTypes, &prev1AT, &curAT);
		unit_feat_operation(m_mapBiActionType, biActionTypes, 1)
		refer_or_allocate_tuple3(triActionTypes, &prev2AT, &prev1AT, &curAT);
		unit_feat_operation(m_mapTriActionType, triActionTypes, 1)
		refer_or_allocate_tuple4(fourActionTypes, &prev3AT, &prev2AT, &prev1AT, &curAT);
		unit_feat_operation(m_mapFourActionType, fourActionTypes, 1)
	}
	//length bonus
	if(ruleId >= 0)
	{
		//float percentage = (lTranslatedPhraseWords.size() + 0.2) / (lConditionPhraseWords.size() + 0.2);
		unit_feat_operation(m_mapSourceLengthBonus, lConditionPhraseWords.size(), 1)
		unit_feat_operation(m_mapTargetLengthBonus, lTranslatedPhraseWords.size(), 1)
		unit_feat_operation(m_mapTransLengthPairBonus, std::make_pair(lConditionPhraseWords.size(), lTranslatedPhraseWords.size()), 1)
	}

	//gap bonus
	{
		unit_feat_operation(m_mapLeftGapBonus, leftgaps, 1)
		unit_feat_operation(m_mapRightGapBonus, rightgaps, 1)
		unit_feat_operation(m_mapLeftGapDistBonus, left_gap_dist, 1)
		unit_feat_operation(m_mapRightGapDistBonus, right_gap_dist, 1)
		unit_feat_operation(m_mapLeftMostGapDistBonus, leftmost_gap_dist, 1)
		unit_feat_operation(m_mapRightMostGapDistBonus, rightmost_gap_dist, 1)
	}


	//if(score > 1000)
	//{
	//	m_weights->outputScores();
	//	outputaction(std::cout, item, action);
	//}

	return score;

}

/*---------------------------------------------------------------
 *
 * getGlobalScore - get the score of a parse tree
 *
 * Inputs: parse graph
 *
 *---------------------------------------------------------------*/

SCORE_TYPE CMachineTrans::getGlobalScore(const CAlignedSentencePair &parsed) {
   THROW("machinetranslation.cpp: getGlobalScore unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScores - update the score std::vector 
 *
 * This method is different from updateScoreVector in that
 * 1. It is for external call
 * 2. The tagging sequences for parsed and correct may differ
 *
 * Inputs: the parsed and the correct example
 *
 *---------------------------------------------------------------*/

void CMachineTrans::updateScores(const CAlignedSentencePair & parsed , const CAlignedSentencePair & correct , int round ) {
   THROW("machinetranslation.cpp: updateScores unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScoreForState - update a single positive or negative outout
 *
 *--------------------------------------------------------------*/

inline SCORE_TYPE CMachineTrans::updateScoreForState(const CStateItem &from, const CStateItem *outout , const SCORE_TYPE &amount ) {
   static CStateItem item(&m_lCache);
   item.clear();
   static CAction action;
   static int ruleid;
   static bool bvalid;
   std::vector<CWord> *p_translated_words;
   std::vector<int> *p_tgt_word_sequences;
   item = from;
   //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   SCORE_TYPE loss = 0;
   //std::cout << "seperated actions:" << std::endl;

   while ( item != *outout ) {
	  bvalid = item.FollowMove( outout, action);
	  //outputaction(std::cout, &item, action);
	  ruleid = action.getRuleID();
	  if(ruleid >= 0)
	  {
		  p_translated_words = &(cast_weights->m_mapTranslateRules[ruleid]);
		  p_tgt_word_sequences = 0; //will modify
	  }
	  else
	  {
		  p_translated_words = 0;
		  p_tgt_word_sequences = 0;
	  }
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
	  getOrUpdateActionScore( &item, action, amount,  m_nTrainingRound );
	  std::cout.flush();

      loss = loss + 1;

      item.Move(action.code(), p_tgt_word_sequences, p_translated_words, cast_weights->m_mapTranslateRuleTypes);
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   }
   std::cout.flush();
   return loss;
}

/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/

void CMachineTrans::updateScoresForStates(const CStateItem *outout , const CStateItem *correct , SCORE_TYPE amount_add, SCORE_TYPE amount_subtract ) {

   // do not update those steps where they are correct
   static CStateItem item(&m_lCache);
   static CAction action, correct_action;
   static int ruleid, correct_ruleid;
   static bool bvalid;
   std::vector<CWord> *p_translated_words;
   std::vector<int> *p_tgt_word_sequences;
   item.clear();
   //std::cout << "common actions:" << std::endl;

   while ( item != *outout ) {
	   bvalid = item.FollowMove(outout, action);
	   bvalid = item.FollowMove(correct,  correct_action);
      if ( action == correct_action)
      {
    	  //outputaction(std::cout, &item, action);
    	  ruleid = action.getRuleID();
    	  if(ruleid >= 0)
    	  {
    		  p_translated_words = &(cast_weights->m_mapTranslateRules[ruleid]);
    		  p_tgt_word_sequences = 0; // will modify
    	  }
    	  else
    	  {
    		  p_translated_words = 0;
    		  p_tgt_word_sequences = 0;
    	  }
    	  item.Move( action.code(), p_tgt_word_sequences, p_translated_words, cast_weights->m_mapTranslateRuleTypes);
      }
      else break;
   }

   int actionloss = outout->m_nActionSize - item.m_nActionSize;
   std::cout << "action loss = " << actionloss << std::endl;
   // for the necessary information for the correct and outout burster
   //std::cout << "start check correst features" << std::endl;
   SCORE_TYPE correct_loss = updateScoreForState(item, correct , amount_add ) ;
   //m_delta_weight->outputScores();
   //std::cout << "\nend check correst features" << std::endl;
   //std::cout.flush();
   //m_delta_weight->clear();
   SCORE_TYPE outout_loss = updateScoreForState(item, outout , amount_subtract ) ;
   //if(correct_loss > 0)
   //{
	//   std::cout << "error" << std::endl;
   //}

   //SCORE_TYPE pos_loss = outout->postagloss(tree);
   //SCORE_TYPE dep_loss = outout_loss - correct_loss;
   //m_delta_weight->outputScores();
   SCORE_TYPE loss = outout->score - correct->score +actionloss;
   if(loss < actionloss)
   {
	   std::cout << "should be error" << std::endl;
	   return;
   }
   //if(dep_loss > 1e-20)
   {
	   SCORE_TYPE normalization = m_delta_weight->squareNorm();
	   SCORE_TYPE weightloss = (loss)/(normalization + 0.5);
	   std::cout << "loss = " << loss <<", normalization = " << normalization <<", update parameter: " << weightloss << std::endl;
	   std::cout.flush();
	   //SCORE_TYPE weightloss = 1;
	   //if(pos_loss < 1e-20)weightloss = weightloss * 3;
	   static_cast<CWeight*>(m_delta_weight)->scaleCurrent(weightloss, m_nTrainingRound);
	   //m_delta_weight->outputScores();
	   cast_weights->addCurrent(m_delta_weight, m_nTrainingRound);
   }



   m_delta_weight->clear();

   m_nTotalErrors++;
}


/*---------------------------------------------------------------
 *
 * reduce - helper function
 *
 *--------------------------------------------------------------*/

//inline void CMachineTrans::reduce( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
//   static action::CScoredAction scoredaction;
   // update stack score
//   scoredaction.action = action::REDUCE;
//   scoredaction.score = item->score + scores[scoredaction.action];
//   m_Beam->insertItem(&scoredaction);
//}



/*
inline void CMachineTrans::ShiftXHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize == 0) return;
	if(item->m_nCurrentIndexInStackX <= item->m_nLastInsertWordXPosition ) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeShiftX();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}


inline void CMachineTrans::ShiftYHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize > 0 || item->m_nStackYSize >= m_lCache.size()-1) return;
	if(item->mustInsertStackX()) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeShiftY();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}

inline void CMachineTrans::InsertGapHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nCurrentIndexInStackX > 0 && item->m_StackX[item->m_nCurrentIndexInStackX-1] == -1) return;
	if(item->m_nCurrentIndexInStackX +1 < item->m_nStackXSize
	   && item->m_StackX[item->m_nCurrentIndexInStackX] == -1
	   && item->m_StackX[item->m_nCurrentIndexInStackX+1] == -1) return;
	if(item->mustInsertStackX()) return;
	if(item->m_nStackYSize == m_lCache.size() && item->m_nBufferXSize == 0) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeInsertGap();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}

inline void CMachineTrans::JumpBackHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nLastAction == CAction::encodeJumpForward()) return;
	if(item->mustInsertStackX()) return;
	bool canJumpBack = false;
	for(int i = 0; i < item->m_nCurrentIndexInStackX; i++)
	{
		if(item->m_StackX[i] == -1)
		{
			canJumpBack = true;
			break;
		}
	}
	if(!canJumpBack) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeJumpBack();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}

inline void CMachineTrans::JumpForwardHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nLastAction == CAction::encodeJumpBack()
	|| item->m_nCurrentIndexInStackX == item->m_nStackXSize) return;
	if(item->mustInsertStackX()) return;
	if(item->m_nStackYSize == m_lCache.size()
	  && item->m_nBufferXSize == 0)
	{
		for(int i = 0; i <= item->m_nCurrentIndexInStackX && i< item->m_nStackXSize; i++)
		{
			if(item->m_StackX[i] == -1)
			{
				return;
			}
		}
	}

	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeJumpForward();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}

inline void CMachineTrans::FinishHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize != 0
	|| item->m_nCurrentIndexInStackX != item->m_nStackXSize
	|| item->m_nStackYSize != m_lCache.size()) return;
	if(item->mustInsertStackX()) return;

	bool canJumpBack = false;
	for(int i = 0; i < item->m_nCurrentIndexInStackX; i++)
	{
		if(item->m_StackX[i] == -1)
		{
			canJumpBack = true;
			break;
		}
	}

	if(canJumpBack) return;

	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeFinish();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}


inline void CMachineTrans::IdleHelper( const CStateItem *item) {
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	if(item->m_nLastAction == CAction::encodeFinish()
	|| item->m_nLastAction == CAction::encodeIdle())
	{
		scoredaction.action = CAction::encodeIdle();
		score = getOrUpdateActionScore(item, scoredaction.action);
		scoredaction.score = item->score + score;
		m_Beam->insertItem(&scoredaction);
	}
}

inline void CMachineTrans::GenerateXXHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize > 0 || item->m_nStackYSize == m_lCache.size()) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	scoredaction.action = CAction::encodeGenerateXX();
	score = getOrUpdateActionScore(item, scoredaction.action);
	scoredaction.score = item->score + score;
	m_Beam->insertItem(&scoredaction);
}

inline void CMachineTrans::GenerateXYHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize > 0 || item->m_nStackYSize == m_lCache.size()) return;
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	static std::vector<CWord> lConditionPhraseWords;
	static std::vector<CWord> lTranslatedPhraseWords;
	static int i;
	static std::string sourcephrase;
	//get x
	lConditionPhraseWords.clear();
	for(i = item->m_nCurrentIndexInStackY; i <= item->m_nStackYSize; i++)
	{
		lConditionPhraseWords.push_back(m_lCache[i]);
	}
	if(lConditionPhraseWords.size() == 0)
	{
		std::cout << "error" << std::endl;
	}
	sourcephrase = tostring(lConditionPhraseWords);
	if(cast_weights->m_mapTranslateStart.element(sourcephrase))
	{
		for(i = cast_weights->m_mapTranslateStart[sourcephrase]; i <= cast_weights->m_mapTranslateEnd[sourcephrase]; i++)
		{
			lTranslatedPhraseWords = cast_weights->m_mapTranslateRules[i];
			if(lTranslatedPhraseWords.size() == 0) continue;
			scoredaction.action = CAction::encodeGenerateXY(i);
			score = getOrUpdateActionScore(item, scoredaction.action);
			scoredaction.score = item->score + score;
			m_Beam->insertItem(&scoredaction);
		}
	}
}


inline void CMachineTrans::GenerateYHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nBufferXSize > 0 || item->m_nStackYSize == m_lCache.size()) return;
	if(item->mustInsertStackX()) return;
	//if(action.isGenerateY(cast_weights->m_mapTranslateRuleTypes))return;
	static int i;
	for(i=1; item->m_nActionSize-i>=0; i++ )
	{
		if(i > MAX_NULL_ALIGN_NUMBER)return;
		if(item->m_ActionType[item->m_nActionSize-i] != CActionType::GENERATE_Y)break;
	}
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	static std::vector<CWord> lConditionPhraseWords;
	static std::vector<CWord> lTranslatedPhraseWords;
	static std::string sourcephrase;
	//get x
	lConditionPhraseWords.clear();
	lTranslatedPhraseWords.clear();
	for(i = item->m_nCurrentIndexInStackY; i <= item->m_nStackYSize; i++)
	{
		lConditionPhraseWords.push_back(m_lCache[i]);
	}
	sourcephrase = tostring(lConditionPhraseWords);
	int ruleId = FindOneRule(sourcephrase, lTranslatedPhraseWords);
	if(ruleId>=0)
	{
		scoredaction.action = CAction::encodeGenerateY(ruleId);
		score = getOrUpdateActionScore(item, scoredaction.action);
		scoredaction.score = item->score + score;
		m_Beam->insertItem(&scoredaction);
	}
}

inline void CMachineTrans::GenerateXHelper( const CStateItem *item) {
	if(item->m_nLastAction == CAction::encodeFinish() || item->m_nLastAction == CAction::encodeIdle() ) return;
	if(item->m_nCurrentIndexInStackX > 0 && item->m_StackX[item->m_nCurrentIndexInStackX-1] == -1) return;
	for(int i= 1; item->m_nCurrentIndexInStackX-i>= 0; i++)
	{
		if(item->m_StackXAlign[item->m_nCurrentIndexInStackX-i]>=0)break;
		if(i>=MAX_NULL_ALIGN_NUMBER)return;
	}

	if(item->m_nCurrentIndexInStackX < item->m_nStackXSize && item->m_StackX[item->m_nCurrentIndexInStackX] == -1)
	{
		if(item->m_nBufferXSize == 0 && item->m_nStackYSize == m_lCache.size())
		{
			//std::cout << "illegal, but we can avoid it" << std::endl;
		}
		else
		{
			return;
		}
	}
	static CScoredAction scoredaction;
	static SCORE_TYPE score;
	static std::vector<CWord> lConditionPhraseWords;
	static std::vector<CWord> lTranslatedPhraseWords;
	static int i;
	static std::string sourcephrase;
	static CWord prevWord, nextWord;
	//get x
	lConditionPhraseWords.clear();
	lTranslatedPhraseWords.clear();
	sourcephrase = tostring(lConditionPhraseWords);
	prevWord = (item->m_nCurrentIndexInStackX > 0) ? item->m_StackX[item->m_nCurrentIndexInStackX-1] : g_emptyWord;
	if(cast_weights->m_mapTranslateStart.element(sourcephrase))
	{
		for(i = cast_weights->m_mapTranslateStart[sourcephrase]; i <= cast_weights->m_mapTranslateEnd[sourcephrase]; i++)
		{
			lTranslatedPhraseWords = cast_weights->m_mapTranslateRules[i];
			assert(lTranslatedPhraseWords.size()==1);
			nextWord = lTranslatedPhraseWords[0];
			if(m_targetLM2[prevWord].find(nextWord) != m_targetLM2[prevWord].end())
			{
				scoredaction.action = CAction::encodeGenerateX(i);
				score = getOrUpdateActionScore(item, scoredaction.action);
				scoredaction.score = item->score + score;
				m_Beam->insertItem(&scoredaction);
			}
		}
	}
}
*/

/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CAlignedSentencePair
 *
 *--------------------------------------------------------------*/

void CMachineTrans::work( const bool bTrain , const CStringVector &sentence , CAlignedSentencePair *retval , const CAlignedSentencePair &correct, const CSTackFeatsVec  & stackfeats , int nBest , SCORE_TYPE *scores ) {

#ifdef DEBUG
   clock_t total_start_time = clock();
#endif
   static int index;
   const int length = sentence.size() ; 

   const CStateItem *pGenerator ;
   const CStateItem *pBestGenerator ;
   static CStateItem pCandidate(&m_lCache) ;

   static CAction action;
   static CAction goldac;
   static int ruleid;
   std::vector<CWord> *p_translated_words;
   std::vector<int> *p_tgt_word_sequences;

   // used only for training
   static bool bCorrect ;  // used in learning for early update
   //static bool bContradictsRules;
   static CStateItem correctState(&m_lCache);
   //static CStateItem correctState_next(&m_lCache) ;


   ASSERT(length<MAX_SENTENCE_SIZE, "The size of the sentence is larger than the system configuration.");

   TRACE("Initialising the decoding process...") ;
   // initialise word cache
   //bContradictsRules = false;
   m_lCache.clear();
   if(!stackfeats.empty())
   {
	   assert(stackfeats.size() == length);
   }
   m_stackfeats.clear();
   for ( index=0; index<length; ++index ) {
      m_lCache.push_back( sentence[index] );
      if(!stackfeats.empty())
      {
    	  m_stackfeats.push_back(stackfeats[index]);
      }
   }


   // initialise agenda
   m_Agenda->clear();
   pCandidate.clear();                          // restore state using clean
   m_Agenda->pushCandidate(&pCandidate);           // and push it back
   m_Agenda->nextRound();                       // as the generator item
   if (bTrain) correctState.clear();

   TRACE("Decoding started"); 
   // loop with the next word to process in the sentence
   while (1) {
      

      // none can this find with pruning ???
      if (m_Agenda->generatorSize() == 0) {
         WARNING("parsing failed"); 

         return;
      }


      // decide correction


      if (m_bTrain)bCorrect = false;
      pGenerator = m_Agenda->generatorStart();
      pBestGenerator = 0;
      for (int j=0; j<m_Agenda->generatorSize(); ++j) {
// DEBUG: stateitems
//            static CTwoStringVector stm;
//            stm.clear();
//            generate(pGenerator, sentence, this, &stm);
//            static CSentenceWriter writer("");
//            writer.writeSentence(&stm);

		if ( m_bTrain && *pGenerator == correctState ) bCorrect = true;
		if(pBestGenerator == 0 || pGenerator->score > pBestGenerator->score) pBestGenerator = pGenerator;
		pGenerator = m_Agenda->generatorNext();  // next generator
	 }

      if(pBestGenerator->m_nLastAction == CAction::encodeFinish()
      || pBestGenerator->m_nLastAction == CAction::encodeIdle()) break;
//         std::cout <<std::endl;
	 if ( m_bTrain ) {
#ifdef EARLY_UPDATE
         if ( !bCorrect ) {
            TRACE("Training error at character " << correctState.m_nActionSize);
            //pGenerator = m_Agenda->bestGenerator();
// DEBUG: gold
//            CTwoStringVector tmp;
//            tmp.clear();
//            generate( pGenerator , sentence , this , &tmp ) ;
//            CSentenceWriter writer("");
//            writer.writeSentence(&tmp);
//            tmp.clear();
//            generate( &goldState , sentence , this , &tmp ) ;
//            writer.writeSentence(&tmp);
            updateScoresForStates(pBestGenerator, &correctState, (SCORE_TYPE)1, (SCORE_TYPE)-1);
#ifndef LOCAL_LEARNING
            return ;
#else
            m_Agenda->clearCandidates();
            m_Agenda->pushCandidate(&correctState);
#endif
         }
#endif
      }

      pGenerator = m_Agenda->generatorStart();
      // iterate generators
      int generatedsize = 0;
      //std::cout << "start out last iter scores:" << std::endl;
      for (int j=0; j<m_Agenda->generatorSize(); ++j) {

         // for the state items that already contain all words
    	 //std::cout << pGenerator->score << " ";
         m_Beam->clear();

/*
         ShiftXHelper(pGenerator);
         ShiftYHelper(pGenerator);
         InsertGapHelper(pGenerator);
         JumpBackHelper(pGenerator);
         JumpForwardHelper(pGenerator);
         FinishHelper(pGenerator);
         IdleHelper(pGenerator);
         //GenerateXXHelper(pGenerator);
         GenerateXYHelper(pGenerator);
         GenerateXHelper(pGenerator);
         GenerateYHelper(pGenerator);

*/
         // operation help functions

         // insert item
         //bool canReachGold = false;

         for (unsigned i=0; i<m_Beam->size(); ++i) {
            pCandidate = *pGenerator;
            if(pCandidate.m_nStackXSize < 0)
            {
            	std::cout << "error" << std::endl;
            }
            pCandidate.score = m_Beam->item(i)->score;
            action =  m_Beam->item(i)->action;
            ruleid = action.getRuleID();
            if(ruleid >= 0)
            {
            	p_translated_words = &(cast_weights->m_mapTranslateRules[ruleid]);
            	p_tgt_word_sequences = 0; // will modify
            }
            else
            {
            	p_translated_words = 0;
            	p_tgt_word_sequences = 0;
            }
            if(pCandidate.Move( action.code(),  p_tgt_word_sequences, p_translated_words, cast_weights->m_mapTranslateRuleTypes))
            {
            	m_Agenda->pushCandidate(&pCandidate);
            	generatedsize++;
            }
         }


         pGenerator = m_Agenda->generatorNext() ;

      }

      //std::cout << std::endl;
      //std::cout.flush();
      /*
      if(generatedsize == 0)
      {
    	  pCandidate = *pBestGenerator;
    	  pCandidate.score = (SCORE_TYPE)0;
    	  translated_words = 0;
    	  if(pCandidate.m_nStackYSize < m_lCache.size())
    	  {
			  if(pCandidate.Move( CActionType::GENERATE_XX,  translated_words, cast_weights->m_mapTranslateRuleTypes))
			  {
				  m_Agenda->pushCandidate(&pCandidate);
				  generatedsize++;
			  }
    	  }
    	  else
    	  {
    		  std::vector<CWord> sourceWords, targetWords;
    		  sourceWords.clear();
    		  targetWords.clear();
    		  std::string sourcephrase = tostring(sourceWords);
    		  int tmpActId = cast_weights->m_mapTranslateStart[sourcephrase];
    		  CAction tmpAction = CAction::encodeGenerateX(tmpActId);
    		  targetWords = cast_weights->m_mapTranslateRules[tmpActId];
    		  translated_words = &targetWords;
			  if(pCandidate.Move( tmpAction.code(),  translated_words, cast_weights->m_mapTranslateRuleTypes))
			  {
				  m_Agenda->pushCandidate(&pCandidate);
				  generatedsize++;
			  }
    	  }
      }*/
      if(generatedsize == 0)
      {
    	  std::cout << "no way to go on now" << std::endl;
    	  break;
      }




      // when we are doing training, we need to consider the standard move and update
      if (bTrain) {

    	  if(correctState.StandardMoveStep(goldac, correct))
    	  {
    		  correctState.score += getOrUpdateActionScore(&correctState, goldac);
    		  ruleid = goldac.getRuleID();
              if(ruleid >= 0)
              {
            	  p_translated_words = &(cast_weights->m_mapTranslateRules[ruleid]);
            	  p_tgt_word_sequences = 0; // will modify
              }
              else
              {
            	  p_translated_words = 0;
            	  p_tgt_word_sequences = 0;
              }
              if(!correctState.Move( goldac.code(), p_tgt_word_sequences,  p_translated_words, cast_weights->m_mapTranslateRuleTypes))
              {
            	  assert(0);
              }

    	  }
    	  else
    	  {
    		  assert(0);
    	  }

#ifdef LOCAL_LEARNING
    	  ++m_nTrainingRound; // each training round is one transition-action
#endif
      } 
      
      m_Agenda->nextRound(); // move round
   }

   if (bTrain) {
  //    correctState.StandardFinish(); // pop the root that is left

      // then make sure that the correct item is stack top finally
      if ( *(m_Agenda->bestGenerator()) != correctState ) {
         TRACE("The best item is not the correct one")
		 //if(m_debug_info.is_open())
		 {
			 //std::cout << *(m_Agenda->bestGenerator()) << std::endl;
			 //std::cout.flush();
		 }
         updateScoresForStates(m_Agenda->bestGenerator(), &correctState, (SCORE_TYPE)1, (SCORE_TYPE)-1) ;

         return ;
      }
   } 

   TRACE("Outputing sentence");
   m_Agenda->sortGenerators();
   for (int i=0; i<std::min(m_Agenda->generatorSize(), nBest); ++i) {
      pGenerator = m_Agenda->generator(i) ; 
      if (pGenerator) {
         pGenerator->GenerateTree(retval[i] ) ;
         if (scores) scores[i] = pGenerator->score;
      }
   }
   TRACE("Done, the highest score is: " << m_Agenda->bestGenerator()->score ) ;
   TRACE("The total time spent: " << double(clock() - total_start_time)/CLOCKS_PER_SEC) ;
}

/*---------------------------------------------------------------
 *
 * parse - do dependency parsing to a sentence
 *
 * Returns: makes a new instance of CAlignedSentencePair
 *
 *--------------------------------------------------------------*/

void CMachineTrans::translator( const CStringVector &sentence , CAlignedSentencePair *retval, const CSTackFeatsVec  & stackfeats , int nBest , SCORE_TYPE *scores ) {

   static CAlignedSentencePair empty ;


   for (int i=0; i<nBest; ++i) {
      // clear the outout sentences
      retval[i].clear();
      if (scores) scores[i] = 0; //pGenerator->score;
   }

   work(false, sentence, retval, empty, stackfeats, nBest, scores ) ;

}



/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CMachineTrans::train(CAlignedSentencePair &correct, const CSTackFeatsVec  & stackfeats , int round ) {

   static CStringVector sentence ;
   static CAlignedSentencePair outout ;
   static CStringVector translated_sentence;
   sentence = correct.m_tgt_sent;
   translated_sentence = correct.m_src_sent;
   if(sentence.size() > MAX_SENTENCE_SIZE
      || translated_sentence.size() > MAX_SENTENCE_SIZE)
   {
 	  assert(0);
   }

   // Updates that are common for all example
   //for ( unsigned i=0; i<sentence.size(); ++i ) {
    //  const CWord &word = sentence[i] ;
   //}

   //for ( unsigned i=0; i<translated_sentence.size(); ++i ) {
  //   const CWord &word = translated_sentence[i] ;
   //}


   //ObtainSentencePair2Actions(correct);

   // The following code does update for each processing stage
#ifndef LOCAL_LEARNING
   ++m_nTrainingRound;
   ASSERT(m_nTrainingRound == round, "Training round error") ;
#endif
   work( true , sentence , &outout , correct , stackfeats, 1 , 0 ) ;

};


/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

bool CMachineTrans::first_train(CAlignedSentencePair &correct) {

   static CStringVector sentence ;
   //static CAlignedSentencePair outout ;
   static CStringVector translated_sentence;
   sentence = correct.m_tgt_sent;
   translated_sentence = correct.m_src_sent;

   if(sentence.size() > MAX_SENTENCE_SIZE
      || translated_sentence.size() > 8*MAX_SENTENCE_SIZE)
   {
 	  return false;
   }

   // Updates that are common for all example
   for ( unsigned i=0; i<sentence.size(); ++i ) {
      const CWord &word = sentence[i] ;
   }

   for ( unsigned i=0; i<translated_sentence.size(); ++i ) {
      const CWord &word = translated_sentence[i] ;
   }


   return ObtainSentencePair2Actions(correct);
};


void CMachineTrans::CollectTransferRules(CAlignedSentencePair &sentpair)
{
	static std::vector<CWord> lConditionWords;
	static std::vector<CWord> lTranslatedWords;

	static std::vector<CWord> lConditionPhraseWords;
	static std::vector<CWord> lTranslatedPhraseWords;

	static CStringVector sentence ;
	static CStringVector translated_sentence;

	static std::string os;
	float minweight1 = 0.1, minweight2 = 0.1, minweight3 = 0.1;


	sentence = sentpair.m_tgt_sent;
	translated_sentence = sentpair.m_src_sent;

	lConditionWords.clear();
	for ( unsigned i=0; i<sentence.size(); ++i ) {
		lConditionWords.push_back(sentence[i]);
	}

	lTranslatedWords.clear();
	for ( unsigned i=0; i<translated_sentence.size(); ++i ) {
		lTranslatedWords.push_back(translated_sentence[i]);
	}

	for(unsigned i=1; i<sentpair.m_alignmap_pos.size(); i++ )
	{
		lConditionPhraseWords.clear();
		lTranslatedPhraseWords.clear();

		for(int j = sentpair.m_alignmap_pos[i-1]; j < sentpair.m_alignmap_pos[i]; j++)
		{
			lTranslatedPhraseWords.push_back(translated_sentence[j]);
		}

		for(int j = 0; j < translated_sentence.size(); j++)
		{
			if(sentpair.m_alignmap_target[j] == i-1)
			{
				lConditionPhraseWords.push_back(sentence[j]);
			}
		}

		os = tostring(lConditionPhraseWords);
		AddOneRule(os, lTranslatedPhraseWords, minweight1, minweight2, minweight3, lTranslatedPhraseWords.size()>0 ? 0 : -1);
	}

	for(int i = 0; i < sentence.size(); i++)
	{
		if(sentpair.m_alignmap_target[i] == -1)
		{
			lConditionPhraseWords.clear();
			lTranslatedPhraseWords.clear();
			lTranslatedPhraseWords.push_back(translated_sentence[i]);
			os = tostring(lConditionPhraseWords);
			AddOneRule(os, lTranslatedPhraseWords, minweight1, minweight2, minweight3, 1);
		}
	}

}

void CMachineTrans::FirstTrainInitRules(std::string ruleFile)
{
	   clock_t time_start = clock();
	   std::cout<<"Loading rules..."; std::cout.flush();
	   std::ifstream file ;

	   std::string s, os;
	   int i, j;

	   std::vector<CWord> condition_phrase;
	   std::vector<CWord> translated_phrase;
	   float translate_rule_weight1, translate_rule_weight2, translate_rule_weight3;
	   int condition_phrase_translation_rule_num;

	   file.open(ruleFile.c_str()) ;

	   if (!file.is_open()) {
	      std::cout << " empty." << std::endl; return;
	   }


	   getline(file, s);
	   ASSERT(s=="translation table rules", "translation table rules not found from model.");
	   file >> cast_weights->m_nTranslationRuleNum;
	   i = 0;
	   while(i < cast_weights->m_nTranslationRuleNum)
	   {
		   file >> condition_phrase;
		   file >> condition_phrase_translation_rule_num;
		   os = tostring(condition_phrase);
		   cast_weights->m_mapTranslateStart.insert(os, i);
		   cast_weights->m_mapTranslateEnd.insert(os, i+condition_phrase_translation_rule_num-1);
		   j = 0;
		   assert(i + condition_phrase_translation_rule_num <=  cast_weights->m_nTranslationRuleNum);
		   while(j < condition_phrase_translation_rule_num)
		   {
			   file >> translated_phrase;
			   file >> translate_rule_weight1 >> translate_rule_weight2 >> translate_rule_weight3;
			   cast_weights->m_mapTranslateSources.push_back(os);
			   cast_weights->m_mapTranslateRules.push_back(translated_phrase);
			   cast_weights->m_mapTranslateRuleScore1s.push_back(translate_rule_weight1);
			   cast_weights->m_mapTranslateRuleScore2s.push_back(translate_rule_weight2);
			   cast_weights->m_mapTranslateRuleScore3s.push_back(translate_rule_weight3);
			   if(condition_phrase.size() == 0 && translated_phrase.size() == 0)
			   {
				   std::cout << "error transition rule!" << std::endl;
			   }
			   if(condition_phrase.size() == 0)
			   {
				   cast_weights->m_mapTranslateRuleTypes.push_back(1);
			   }
			   else if(translated_phrase.size() == 0)
			   {
				   cast_weights->m_mapTranslateRuleTypes.push_back(-1);
			   }
			   else
			   {
				   assert(condition_phrase.size() > 0 && translated_phrase.size() > 0);
				   cast_weights->m_mapTranslateRuleTypes.push_back(0);
			   }
			   j++;

		   }
		   i += condition_phrase_translation_rule_num;
	   }

	   file.close() ;
	   std::cout << " done. (" << double(clock()-time_start)/CLOCKS_PER_SEC << "s)" << std::endl;

}


void CMachineTrans::AddOneRule(const std::string& condition_str, const std::vector<CWord>& translated_words,
		float weight1, float weight2, float weight3, int ruletype)
{
	if(FindOneRule(condition_str, translated_words) != -1) return;
	static std::string tmp_condition_str;
	if(cast_weights->m_mapTranslateEnd.element(condition_str))
	{
		int end = cast_weights->m_mapTranslateEnd[condition_str];

		cast_weights->m_mapTranslateSources.insert(cast_weights->m_mapTranslateSources.begin()+end+1, condition_str);
		cast_weights->m_mapTranslateRules.insert(cast_weights->m_mapTranslateRules.begin()+end+1, translated_words);
		cast_weights->m_mapTranslateRuleScore1s.insert(cast_weights->m_mapTranslateRuleScore1s.begin()+end+1, weight1);
		cast_weights->m_mapTranslateRuleScore2s.insert(cast_weights->m_mapTranslateRuleScore2s.begin()+end+1, weight2);
		cast_weights->m_mapTranslateRuleScore3s.insert(cast_weights->m_mapTranslateRuleScore3s.begin()+end+1, weight3);
		cast_weights->m_mapTranslateRuleTypes.insert(cast_weights->m_mapTranslateRuleTypes.begin()+end+1, ruletype);
		cast_weights->m_nTranslationRuleNum++;

		cast_weights->m_mapTranslateEnd[condition_str]++;
		int i = end+2;
		while(i<cast_weights->m_nTranslationRuleNum)
		{
			tmp_condition_str = cast_weights->m_mapTranslateSources[i];
			cast_weights->m_mapTranslateStart[tmp_condition_str]++;
			cast_weights->m_mapTranslateEnd[tmp_condition_str]++;
			i = cast_weights->m_mapTranslateEnd[tmp_condition_str]+1;
		}
	}
	else
	{
		cast_weights->m_mapTranslateSources.push_back(condition_str);
		cast_weights->m_mapTranslateRules.push_back(translated_words);
		cast_weights->m_mapTranslateRuleScore1s.push_back(weight1);
		cast_weights->m_mapTranslateRuleScore2s.push_back(weight2);
		cast_weights->m_mapTranslateRuleScore3s.push_back(weight3);
		cast_weights->m_mapTranslateRuleTypes.push_back(ruletype);
		cast_weights->m_nTranslationRuleNum++;
		cast_weights->m_mapTranslateStart.insert(condition_str,cast_weights->m_nTranslationRuleNum-1);
		cast_weights->m_mapTranslateEnd.insert(condition_str,cast_weights->m_nTranslationRuleNum-1);
	}
}

int CMachineTrans::FindOneRule(const std::string& condition_str, const std::vector<CWord>& translated_words)
{
	if(cast_weights->m_mapTranslateEnd.element(condition_str))
	{
		for(int i = cast_weights->m_mapTranslateStart[condition_str]; i<=cast_weights->m_mapTranslateEnd[condition_str]; i++)
		{
			bool bIdendifal = true;
			if(cast_weights->m_mapTranslateRules[i].size() != translated_words.size()) bIdendifal = false;
			else
			{
				for(int j = 0; j < cast_weights->m_mapTranslateRules[i].size(); j++)
				{
					if(cast_weights->m_mapTranslateRules[i][j] != translated_words[j])
					{
						bIdendifal = false;
						break;
					}
				}
			}
			if(bIdendifal) return i;
		}
	}

	return -1;
}


void CMachineTrans::ReadLanguageModel(const std::string& lmfile, CLanguageModel1Type& lm1, CLanguageModel2Type& lm2,
		CLanguageModel3Type& lm3, CLanguageModel4Type& lm4)
{
	std::ifstream is(lmfile.c_str());
	assert(is.is_open());

	lm1.clear();
	lm2.clear();
	lm3.clear();
	lm4.clear();

	char cTemp;
	int ngram = 0;
	int i;
	std::string first_elem = "";
	std::vector<CWord> middle_elems;
	std::string last_elem = "";
	std::string sWord = "";                    // std::string for next word
	std::string sline;
	int tabnum = 0;
	static CTuple2<CWord, CWord> biwords;
	static CTuple3<CWord, CWord, CWord> triwords;
	static CWord uniword;


	while (is.get(cTemp)) {
		if (cTemp == '\r')
			continue;
		if (cTemp == '\n') {               // if we meet EOL, return std::string
			if (!sWord.empty()) {                  // we have found another word
				if (middle_elems.size() > 0) {
					if (tabnum == 1)
					{
						if(sWord == "<s>")
						{
							middle_elems.push_back(g_emptyWord);
						}
						else middle_elems.push_back(CWord(sWord));
					}
					if (first_elem.empty() || middle_elems.size() != ngram) {
						std::cout << middle_elems.size() << " : " << ngram
								<< std::endl;
						for (i = 0; i < middle_elems.size(); i++)
							std::cout << middle_elems[i] << " ";
						std::cout << std::endl;
						std::cout << "must error here" << std::endl;
						std::cout.flush();
						return;
					}
					float theScore = atof(first_elem.c_str());

					if (ngram == 1) {
						lm1.insert(middle_elems[0], theScore);
					} else if (ngram == 2) {
						uniword = middle_elems[0];
						if (!lm2.element(uniword)) {
							std::map<CWord, float> init_elem;
							init_elem.insert(std::pair<CWord, float>(middle_elems[1],theScore));
							lm2.insert(uniword, init_elem);
						} else {
							lm2[uniword].insert(std::pair<CWord, float>(middle_elems[1],theScore));
						}
					}
					else if (ngram == 3) {
						biwords.allocate(&middle_elems[0], &middle_elems[1]);
						if (!lm3.element(biwords)) {
							std::map<CWord, float> init_elem;
							init_elem.insert(std::pair<CWord, float>(middle_elems[2],theScore));
							lm3.insert(biwords, init_elem);
						} else {
							lm3[biwords].insert(std::pair<CWord, float>(middle_elems[2],theScore));
						}
					}
					else if (ngram == 4) {
						triwords.allocate(&middle_elems[0], &middle_elems[1], &middle_elems[2]);
						if (!lm4.element(triwords)) {
							std::map<CWord, float> init_elem;
							init_elem.insert(std::pair<CWord, float>(middle_elems[3],theScore));
							lm4.insert(triwords, init_elem);
						} else {
							lm4[triwords].insert(std::pair<CWord, float>(middle_elems[3],theScore));
						}
					}
					else {
						std::cout << "must error here" << std::endl;
						std::cout.flush();
						break;
					}

				} else if (sWord.length() > 8
						&& sWord.substr(sWord.length() - 7) == "-grams:") {
					ngram = atoi(sWord.substr(1, sWord.size() - 8).c_str());
					if (ngram > 4)
						break;
				}
				sWord = "";
				first_elem = "";
				last_elem = "";
				middle_elems.clear();
				tabnum = 0;
			}
		} else if (cTemp == ' ') {                  // otherwise, if we meet " "
			if (!first_elem.empty() && !sWord.empty()) { // we have found another word
				if(sWord == "<s>")
				{
					middle_elems.push_back(g_emptyWord);
				}
				else middle_elems.push_back(CWord(sWord));
				sWord = "";
			}
		} else if (cTemp == '\t') {
			if (first_elem.empty()) {
				first_elem = sWord;
			} else {
				if(sWord == "<s>")
				{
					middle_elems.push_back(g_emptyWord);
				}
				else middle_elems.push_back(CWord(sWord));
			}
			sWord = "";
			tabnum++;
		} else
			// otherwise
			sWord += cTemp;

	}

	is.close();

}


void CMachineTrans::ReadActionLanguageModel(const std::string& lmfile, CActionLMModel1Type& lm1, CActionLMModel2Type& lm2,
		CActionLMModel3Type& lm3, CActionLMModel4Type& lm4)
{
	std::ifstream is(lmfile.c_str());
	assert(is.is_open());

	lm1.clear();
	lm2.clear();
	lm3.clear();
	lm4.clear();

	char cTemp;
	int ngram = 0;
	int i;
	std::string first_elem = "";
	std::vector<CAction> middle_elems;
	std::string last_elem = "";
	std::string sWord = "";                    // std::string for next word
	std::string sline;
	int tabnum = 0;
	static CTuple2<CAction, CAction> biwords;
	static CTuple3<CAction, CAction, CAction> triwords;
	static CAction uniword;


	while (is.get(cTemp)) {
		if (cTemp == '\r')
			continue;
		if (cTemp == '\n') {               // if we meet EOL, return std::string
			if (!sWord.empty()) {                  // we have found another word
				if (middle_elems.size() > 0) {
					if (tabnum == 1)
					{
						if(sWord == "<s>")
						{
							middle_elems.push_back(CAction(0));
						}
						else middle_elems.push_back(CAction(atoi(sWord.c_str())));
					}
					if (first_elem.empty() || middle_elems.size() != ngram) {
						std::cout << middle_elems.size() << " : " << ngram
								<< std::endl;
						for (i = 0; i < middle_elems.size(); i++)
							std::cout << middle_elems[i] << " ";
						std::cout << std::endl;
						std::cout << "must error here" << std::endl;
						std::cout.flush();
						return;
					}
					float theScore = atof(first_elem.c_str());

					if (ngram == 1) {
						lm1.insert(middle_elems[0], theScore);
					} else if (ngram == 2) {
						uniword = middle_elems[0];
						if (!lm2.element(uniword)) {
							std::map<CAction, float> init_elem;
							init_elem.insert(std::pair<CAction, float>(middle_elems[1],theScore));
							lm2.insert(uniword, init_elem);
						} else {
							lm2[uniword].insert(std::pair<CAction, float>(middle_elems[1],theScore));
						}
					}
					else if (ngram == 3) {
						biwords.allocate(&middle_elems[0], &middle_elems[1]);
						if (!lm3.element(biwords)) {
							std::map<CAction, float> init_elem;
							init_elem.insert(std::pair<CAction, float>(middle_elems[2],theScore));
							lm3.insert(biwords, init_elem);
						} else {
							lm3[biwords].insert(std::pair<CAction, float>(middle_elems[2],theScore));
						}
					}
					else if (ngram == 4) {
						triwords.allocate(&middle_elems[0], &middle_elems[1], &middle_elems[2]);
						if (!lm4.element(triwords)) {
							std::map<CAction, float> init_elem;
							init_elem.insert(std::pair<CAction, float>(middle_elems[3],theScore));
							lm4.insert(triwords, init_elem);
						} else {
							lm4[triwords].insert(std::pair<CAction, float>(middle_elems[3],theScore));
						}
					}
					else {
						std::cout << "must error here" << std::endl;
						std::cout.flush();
						break;
					}

				} else if (sWord.length() > 8
						&& sWord.substr(sWord.length() - 7) == "-grams:") {
					ngram = atoi(sWord.substr(1, sWord.size() - 8).c_str());
					if (ngram > 4)
						break;
				}
				sWord = "";
				first_elem = "";
				last_elem = "";
				middle_elems.clear();
				tabnum = 0;
			}
		} else if (cTemp == ' ') {                  // otherwise, if we meet " "
			if (!first_elem.empty() && !sWord.empty()) { // we have found another word
				if(sWord == "<s>")
				{
					middle_elems.push_back(CAction(0));
				}
				else middle_elems.push_back(CAction(atoi(sWord.c_str())));
				sWord = "";
			}
		} else if (cTemp == '\t') {
			if (first_elem.empty()) {
				first_elem = sWord;
			} else {
				if(sWord == "<s>")
				{
					middle_elems.push_back(CAction(0));
				}
				else middle_elems.push_back(CAction(atoi(sWord.c_str())));
			}
			sWord = "";
			tabnum++;
		} else
			// otherwise
			sWord += cTemp;

	}

	is.close();

}


void CMachineTrans::init_tagetlm(const std::string& lmfile)
{
	   ReadLanguageModel(lmfile, m_targetLM1, m_targetLM2, m_targetLM3, m_targetLM4);
}

void CMachineTrans::init_osmlm(const std::string& lmfile)
{
	   ReadActionLanguageModel(lmfile, m_osmLM1, m_osmLM2, m_osmLM3, m_osmLM4);
}

void CMachineTrans::init_priorlm(const std::string& lmfile)
{
	   ReadLanguageModel(lmfile, m_priorLM1, m_priorLM2, m_priorLM3, m_priorLM4);
}


void CMachineTrans::outputaction(std::ostream &os, const machinetranslation::CStateItem *item, machinetranslation::CAction& action )
{
		int ruleId = action.getRuleID();
		int i;
		/*
		std::vector<CWord> lConditionPhraseWords, lTranslatedPhraseWords;
		lConditionPhraseWords.clear();
		lTranslatedPhraseWords.clear();
		if(action.isGenerateXY(cast_weights->m_mapTranslateRuleTypes))
		{
			for(i = item->m_nCurrentIndexInStackY; i <= item->m_nStackYSize; i++)
			{
				lConditionPhraseWords.push_back(m_lCache[i]);
			}
		}
		if(ruleId >= 0)
		{
			for(i = 0; i < cast_weights->m_mapTranslateRules[ruleId].size(); i++)
			{
				lTranslatedPhraseWords.push_back(cast_weights->m_mapTranslateRules[ruleId][i]);
			}
		}
*/
		if(ruleId == -1)
		{
			os << CActionType(action.code()) << " ";
		}
		else
		{
			os << "GEN" << " ";
		}


		os  << std::endl;
		os.flush();

}

bool CMachineTrans::ObtainSentencePair2Actions(CAlignedSentencePair &sentpair)
{
	static CStateItem correctState(&m_lCache);
	static CStringVector sentence ;
	static CStringVector translated_sentence;

	translated_sentence = sentpair.m_src_sent;
	sentence = sentpair.m_tgt_sent;

	m_lCache.clear();
	for ( unsigned i=0; i<sentence.size(); ++i ) {
		m_lCache.push_back(sentence[i]);
	}

	correctState.clear();
	sentpair.m_actions.clear();

	static int i, j, r, x_next_start, ruleId; // current phrase index in Y
	static int left_stackid, right_stackid, left_genid, right_genid;
	// tgt translate into src

	static CAction action;
	std::vector<CWord> *p_translated_words;
	std::vector<int> *p_tgt_word_sequences;
	static std::string condition_phrase, translated_phrase;


	static std::vector<CWord> lConditionPhraseWords;
	static std::vector<CWord> lTranslatedPhraseWords;
	static std::vector<int> tgt_word_sequences;

	r= 0;
	while(correctState.m_nLastAction != CAction::encodeFinish())
	{
		//Will need a GEN-style action
		if(correctState.m_nBufferXSize == 0)
		{
			if(correctState.m_nStackYSize == translated_sentence.size())
			{
				assert(r==sentpair.m_alignmap_pos.size()-1);

				//the right most word w[j] to generate the source sentence is in stack
				// at this time, stack should be 0, 1, ..., j;
				for(i = 0; i < correctState.m_nStackXSize; i++)
				{
					if(correctState.m_StackX[i] == -1)
					{
						std::cout << "error convertion" << std::endl;
						return false;
					}
					if(i < correctState.m_nCurrentIndexInStackX)
					{
						if(correctState.m_StackX[i] != i)
						{
							std::cout << "error convertion" << std::endl;
							return false;
						}
					}
				}

				left_stackid = correctState.m_nCurrentIndexInStackX-1;
				left_genid = left_stackid;

				right_stackid = correctState.m_nCurrentIndexInStackX;
				right_genid = sentence.size();
				if(right_stackid<correctState.m_nStackXSize)
				{
					right_genid=correctState.m_StackX[right_stackid];
				}

				if(left_genid+1 == right_genid)
				{
					if(correctState.m_nCurrentIndexInStackX < correctState.m_nStackXSize)
					{
						action = CAction::encodeJumpForward();
						p_translated_words = 0;
						p_tgt_word_sequences = 0;
						//operation
					}
					else
					{
						action = CAction::encodeFinish();
						p_translated_words = 0;
						p_tgt_word_sequences = 0;
					}
				}
				else if(left_genid+1 < right_genid)
				{
					assert(sentpair.m_alignmap_target[left_genid+1]==-1);
					lConditionPhraseWords.clear();
					lTranslatedPhraseWords.clear();
					tgt_word_sequences.clear();
					lConditionPhraseWords.push_back(sentence[left_genid+1]);
					tgt_word_sequences.push_back(left_genid+1);
					condition_phrase = tostring(lConditionPhraseWords);
					//std::cout << condition_phrase << std::endl;
					//std::cout.flush();
					ruleId = FindOneRule(condition_phrase, lTranslatedPhraseWords);
					//assert(ruleId>=0);
					if(ruleId == -1)
					{
						std::cout << "source: " << condition_phrase << "\ttarget: " << lTranslatedPhraseWords << std::endl;
						std::cout.flush();
						return false;
					}
					action = CAction::encodeGenerateX(ruleId);

					p_translated_words = &lTranslatedPhraseWords;
					p_tgt_word_sequences = &tgt_word_sequences;

				}
			}
			else // before GEN, we need do something to locate correct position
			{
				if(sentpair.m_alignmap_source[r].size() == 0)
				{
					for(int m = 0; m < sentpair.m_alignmap_source.size(); m++)
					{
						std::cout << m << ":";
						for(int n = 0; n < sentpair.m_alignmap_source[m].size(); n++)
						{
							std::cout << " " << sentpair.m_alignmap_source[m][n];
						}
						std::cout << std::endl;
					}
					std::cout << std::endl;
					std::cout.flush();
					return false;
				}
				x_next_start = sentpair.m_alignmap_source[r][0];

				left_stackid = correctState.m_nCurrentIndexInStackX-1;
				while(left_stackid >= 0 && correctState.m_StackX[left_stackid] == -1)
				{
					left_stackid--;
				}
				left_genid = -1;
				if(left_stackid>=0)
				{
					left_genid=correctState.m_StackX[left_stackid];
				}

				right_stackid = correctState.m_nCurrentIndexInStackX;
				while(right_stackid < correctState.m_nStackXSize && correctState.m_StackX[right_stackid] == -1)
				{
					right_stackid++;
				}
				right_genid = sentence.size();
				if(right_stackid<correctState.m_nStackXSize)
				{
					right_genid=correctState.m_StackX[right_stackid];
				}

				if(left_genid+1 < right_genid && sentpair.m_alignmap_target[left_genid+1]==-1)
				{
					assert(left_stackid == correctState.m_nCurrentIndexInStackX-1);
					lConditionPhraseWords.clear();
					lTranslatedPhraseWords.clear();
					tgt_word_sequences.clear();
					lConditionPhraseWords.push_back(sentence[left_genid+1]);
					tgt_word_sequences.push_back(left_genid+1);
					condition_phrase = tostring(lConditionPhraseWords);
					//std::cout << condition_phrase << std::endl;
					//std::cout.flush();
					ruleId = FindOneRule(condition_phrase, lTranslatedPhraseWords);
					//assert(ruleId>=0);
					if(ruleId == -1)
					{
						std::cout << "source: " << condition_phrase << "\ttarget: " << lTranslatedPhraseWords << std::endl;
						std::cout.flush();
						return false;
					}
					action = CAction::encodeGenerateX(ruleId);

					p_translated_words = &lTranslatedPhraseWords;
					p_tgt_word_sequences = &tgt_word_sequences;
				}
				else if((x_next_start < left_genid || x_next_start > right_genid)
					&& left_genid<right_genid-1 && left_stackid==right_stackid-1
					&& correctState.m_nCurrentIndexInStackX>0
					&& correctState.m_nCurrentIndexInStackX<correctState.m_nStackXSize)
				{
					//for later to jump to here
					action = CAction::encodeInsertGap();
					p_translated_words = 0;
					p_tgt_word_sequences = 0;
				}
				else if(x_next_start<left_genid
					&& correctState.m_nCurrentIndexInStackX>0) // JumpBack
				{
					action = CAction::encodeJumpBack();
					p_translated_words = 0;
					p_tgt_word_sequences = 0;
				}
				else if(x_next_start>right_genid
					&& correctState.m_nCurrentIndexInStackX<correctState.m_nStackXSize) // JumpForward
				{
					action = CAction::encodeJumpForward();
					p_translated_words = 0;
					p_tgt_word_sequences = 0;
				}
				else if(x_next_start>left_genid+1
					&& left_stackid==correctState.m_nCurrentIndexInStackX-1)
				{
					// back insert gap
					action = CAction::encodeInsertGap();
					p_translated_words = 0;
					p_tgt_word_sequences = 0;
				}
				else // GENXY
				{
					//assert(correctState.m_nCurrentIndexInStackX == correctState.m_nStackXSize || correctState.m_StackX[correctState.m_nCurrentIndexInStackX]==-1);
					lConditionPhraseWords.clear();
					lTranslatedPhraseWords.clear();
					tgt_word_sequences.clear();
					for(i = sentpair.m_alignmap_pos[r]; i<sentpair.m_alignmap_pos[r+1]; i++)
					{
						lTranslatedPhraseWords.push_back(translated_sentence[i]);
					}

					for(i = 0; i<sentpair.m_alignmap_source[r].size(); i++)
					{
						j = sentpair.m_alignmap_source[r][i];
						lConditionPhraseWords.push_back(sentence[j]);
						tgt_word_sequences.push_back(j);
					}

					condition_phrase = tostring(lConditionPhraseWords);
					ruleId = FindOneRule(condition_phrase, lTranslatedPhraseWords);
					//assert(ruleId >= 0);
					if(ruleId == -1)
					{
						std::cout << "source: " << condition_phrase << "\ttarget: " << lTranslatedPhraseWords << std::endl;
						std::cout.flush();
						return false;
					}


					action = CAction::encodeGenerateXY(ruleId);
					p_translated_words = &(cast_weights->m_mapTranslateRules[ruleId]);
					p_tgt_word_sequences = &tgt_word_sequences;

					r++;
				}

			}
		}
		else
		{
			x_next_start = correctState.m_BufferX[correctState.m_nBufferXSize-1];
			left_stackid = correctState.m_nCurrentIndexInStackX-1;
			while(left_stackid >= 0 && correctState.m_StackX[left_stackid] == -1)
			{
				left_stackid--;
			}
			left_genid = -1;
			if(left_stackid>=0)
			{
				left_genid=correctState.m_StackX[left_stackid];
			}

			right_stackid = correctState.m_nCurrentIndexInStackX;
			while(right_stackid < correctState.m_nStackXSize && correctState.m_StackX[right_stackid] == -1)
			{
				right_stackid++;
			}
			right_genid = sentence.size();
			if(right_stackid<correctState.m_nStackXSize)
			{
				right_genid=correctState.m_StackX[right_stackid];
			}

			if(left_genid+1 < right_genid && sentpair.m_alignmap_target[left_genid+1]==-1)
			{
				assert(left_stackid == correctState.m_nCurrentIndexInStackX-1);
				lConditionPhraseWords.clear();
				lTranslatedPhraseWords.clear();
				tgt_word_sequences.clear();
				lConditionPhraseWords.push_back(sentence[left_genid+1]);
				tgt_word_sequences.push_back(left_genid+1);
				condition_phrase = tostring(lConditionPhraseWords);
				//std::cout << condition_phrase << std::endl;
				//std::cout.flush();
				ruleId = FindOneRule(condition_phrase, lTranslatedPhraseWords);
				//assert(ruleId>=0);
				if(ruleId == -1)
				{
					std::cout << "source: " << condition_phrase << "\ttarget: " << lTranslatedPhraseWords << std::endl;
					std::cout.flush();
					return false;
				}
				action = CAction::encodeGenerateX(ruleId);

				p_translated_words = &lTranslatedPhraseWords;
				p_tgt_word_sequences = &tgt_word_sequences;
			}
			else if((x_next_start < left_genid || x_next_start > right_genid)
				&& left_genid<right_genid-1 && left_stackid==right_stackid-1
				&& correctState.m_nCurrentIndexInStackX>0
				&& correctState.m_nCurrentIndexInStackX<correctState.m_nStackXSize)
			{
				//for later to jump to here
				action = CAction::encodeInsertGap();
				p_translated_words = 0;
				p_tgt_word_sequences = 0;
			}
			else if(x_next_start<left_genid
				&& correctState.m_nCurrentIndexInStackX>0) // JumpBack
			{
				action = CAction::encodeJumpBack();
				p_translated_words = 0;
				p_tgt_word_sequences = 0;
			}
			else if(x_next_start>right_genid
				&& correctState.m_nCurrentIndexInStackX<correctState.m_nStackXSize) // JumpForward
			{
				action = CAction::encodeJumpForward();
				p_translated_words = 0;
				p_tgt_word_sequences = 0;
			}
			else if(x_next_start>left_genid+1
				&& left_stackid==correctState.m_nCurrentIndexInStackX-1)
			{
				// back insert gap
				action = CAction::encodeInsertGap();
				p_translated_words = 0;
				p_tgt_word_sequences = 0;
			}
			else // SHIFT_X
			{
				//assert(correctState.m_nCurrentIndexInStackX == correctState.m_nStackXSize || correctState.m_StackX[correctState.m_nCurrentIndexInStackX]==-1);
				action = CAction::encodeShiftX();
				p_translated_words = 0;
				p_tgt_word_sequences = 0;
			}
		}

		sentpair.m_actions.push_back(action.code());

		correctState.Move(action.code(), p_tgt_word_sequences, p_translated_words, cast_weights->m_mapTranslateRuleTypes);
		{
			//debug info

			std::cout << "action: " << CActionType(action.type(cast_weights->m_mapTranslateRuleTypes)) << " ruleid: " << action.getRuleID() << std::endl;

			if(action.code() > CActionType::IDLE)
			{
				std::cout << "source: " << lConditionPhraseWords << std::endl;
				std::cout << "target: " << lTranslatedPhraseWords << std::endl;
			}
			std::cout.flush();

		}
	}
	CAlignedSentencePair output;
	correctState.GenerateTree(output);
	if(output != sentpair)
	{
		std::cout << "error convertions" << std::endl;
		std::cout.flush();
		return false;
	}

	if(m_debug_info.is_open())
	{
		//m_debug_info << output << std::endl;
		if(sentpair.m_actions.size() > 0)
		{
			m_debug_info << sentpair.m_actions[0];
			for(i = 1; i < sentpair.m_actions.size(); i++)
			{
				m_debug_info << " " << sentpair.m_actions[i];
			}
			m_debug_info << std::endl;
		}

	}

	return true;
};
