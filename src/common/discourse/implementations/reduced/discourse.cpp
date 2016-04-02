// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * discourse.cpp - the action based parser implementation       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

#include "discourse.h"
#include "weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::discourse;

#define refer_or_allocate_tuple2(x, o1, o2) { if (amount == 0) x.refer(o1, o2); else x.allocate(o1, o2); }

const CAction g_noneAction(0);

/*===============================================================
 *
 * CDisParser - the discourse for TARGET_LANGUAGE 
 *
 *==============================================================*/

/*---------------------------------------------------------------
 * 
 * getOrUpdateStackScore - manipulate the score from stack 
 *
 *---------------------------------------------------------------*/

inline SCORE_TYPE CDisParser::getOrUpdateStackScore( CWeight *cast_weights, const CStateItem *item, const CAction &action, SCORE_TYPE amount , int round ) {

   SCORE_TYPE score = 0;

   // will be added after the decoding can be run through

   //if (m_Context.stacksize==0) return;

   static unsigned int j;
   
   //static CDISCFGSet s0ts1tbt;
   //s0ts1tbt.copy(m_Context.s0ts1tbt);



//   s0cs1c_distaction = encodeAction(action, m_Context.s0cs1c_dist);

   static CTuple2<CWord, CConstituent> word_constituent;
   static CTuple2<CTag, CConstituent> tag_constituent;
   static CTuple2<CTwoWords, CDISCFGSet> twoword_cfgset;
   static CTuple2<CWord, CDISCFGSet> word_cfgset;

   static CActionType actionType;
   actionType.code = action.type();

   const CAction &a1 = item->action;
   const CAction &a2 = item->statePtr == 0 ? g_noneAction : item->statePtr->action;

   static CTuple2<CAction, CAction> tuple_action2;

   // S0
   // syn head
   if (m_Context.s0!=0) {
	   score += cast_weights->m_mapS0w.getOrUpdateScore(std::make_pair(*(m_Context.s0w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0t.getOrUpdateScore(std::make_pair(m_Context.s0t, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0sc, m_Context.s0m), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0c.getOrUpdateScore(std::make_pair(m_Context.s0c, action), m_nScoreIndex, amount, round);

	   score += cast_weights->m_mapS0HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.s0length, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0EDUNUM.getOrUpdateScore(std::make_pair(m_Context.s0edunum, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0SentBegin.getOrUpdateScore(std::make_pair(m_Context.s0_sent_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0SentEnd.getOrUpdateScore(std::make_pair(m_Context.s0_sent_end_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0ParaBegin.getOrUpdateScore(std::make_pair(m_Context.s0_para_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0ParaEnd.getOrUpdateScore(std::make_pair(m_Context.s0_para_end_dist, action), m_nScoreIndex, amount, round);


	   // edu begin words
	   score += cast_weights->m_mapS0bw.getOrUpdateScore(std::make_pair(*(m_Context.s0b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0bt.getOrUpdateScore(std::make_pair(m_Context.s0b1t, action), m_nScoreIndex, amount, round);

	   // edu end words
	   score += cast_weights->m_mapS0ew.getOrUpdateScore(std::make_pair(*(m_Context.s0b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0et.getOrUpdateScore(std::make_pair(m_Context.s0b1t, action), m_nScoreIndex, amount, round);

	   for(j = m_Context.s0b1; j <= m_Context.s0e1; j++)
	   {
		   score += cast_weights->m_mapS0EduWords.getOrUpdateScore(std::make_pair(m_sent[j].word, action), m_nScoreIndex, amount, round);
	   }
   }
   // S1
   if (m_Context.s1!=0) {
	   score += cast_weights->m_mapS1w.getOrUpdateScore(std::make_pair(*(m_Context.s1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1t.getOrUpdateScore(std::make_pair(m_Context.s1t, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s1sc, m_Context.s1m), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1c.getOrUpdateScore(std::make_pair(m_Context.s1c, action), m_nScoreIndex, amount, round);

	   score += cast_weights->m_mapS1HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.s1length, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1EDUNUM.getOrUpdateScore(std::make_pair(m_Context.s1edunum, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1SentBegin.getOrUpdateScore(std::make_pair(m_Context.s1_sent_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1SentEnd.getOrUpdateScore(std::make_pair(m_Context.s1_sent_end_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1ParaBegin.getOrUpdateScore(std::make_pair(m_Context.s1_para_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1ParaEnd.getOrUpdateScore(std::make_pair(m_Context.s1_para_end_dist, action), m_nScoreIndex, amount, round);

	   // edu begin words
	   score += cast_weights->m_mapS1bw.getOrUpdateScore(std::make_pair(*(m_Context.s1b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1bt.getOrUpdateScore(std::make_pair(m_Context.s1b1t, action), m_nScoreIndex, amount, round);

	   // edu end words
	   score += cast_weights->m_mapS1ew.getOrUpdateScore(std::make_pair(*(m_Context.s1b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS1et.getOrUpdateScore(std::make_pair(m_Context.s1b1t, action), m_nScoreIndex, amount, round);

	   for(j = m_Context.s1b1; j <= m_Context.s1e1; j++)
	   {
		   score += cast_weights->m_mapS1EduWords.getOrUpdateScore(std::make_pair(m_sent[j].word, action), m_nScoreIndex, amount, round);
	   }
   }

   // S2
   if (m_Context.s2!=0) {
	   score += cast_weights->m_mapS2w.getOrUpdateScore(std::make_pair(*(m_Context.s2w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2t.getOrUpdateScore(std::make_pair(m_Context.s2t, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s2sc, m_Context.s2m), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2c.getOrUpdateScore(std::make_pair(m_Context.s2c, action), m_nScoreIndex, amount, round);

	   score += cast_weights->m_mapS2HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.s2length, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2EDUNUM.getOrUpdateScore(std::make_pair(m_Context.s2edunum, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2SentBegin.getOrUpdateScore(std::make_pair(m_Context.s2_sent_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2SentEnd.getOrUpdateScore(std::make_pair(m_Context.s2_sent_end_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2ParaBegin.getOrUpdateScore(std::make_pair(m_Context.s2_para_begin_dist, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2ParaEnd.getOrUpdateScore(std::make_pair(m_Context.s2_para_end_dist, action), m_nScoreIndex, amount, round);

	   // edu begin words
	   score += cast_weights->m_mapS2bw.getOrUpdateScore(std::make_pair(*(m_Context.s2b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2bt.getOrUpdateScore(std::make_pair(m_Context.s2b1t, action), m_nScoreIndex, amount, round);

	   // edu end words
	   score += cast_weights->m_mapS2ew.getOrUpdateScore(std::make_pair(*(m_Context.s2b1w), action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS2et.getOrUpdateScore(std::make_pair(m_Context.s2b1t, action), m_nScoreIndex, amount, round);

	  //for(j = m_Context.s2b1; j <= m_Context.s2e1; j++)
	  //{
		//   score += cast_weights->m_mapS2EduWords.getOrUpdateScore(std::make_pair(m_sent[j].word, action), m_nScoreIndex, amount, round);
	  //}

   }


   // N0
   if (m_Context.n0!=-1) {
	  score += cast_weights->m_mapN0w.getOrUpdateScore(std::make_pair(*(m_Context.n0w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0t.getOrUpdateScore(std::make_pair(m_Context.n0t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.n0sc, m_Context.n0m), action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN0HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.n0length, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0SentBegin.getOrUpdateScore(std::make_pair(m_Context.n0_sent_begin_dist, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0SentEnd.getOrUpdateScore(std::make_pair(m_Context.n0_sent_end_dist, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0ParaBegin.getOrUpdateScore(std::make_pair(m_Context.n0_para_begin_dist, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0ParaEnd.getOrUpdateScore(std::make_pair(m_Context.n0_para_end_dist, action), m_nScoreIndex, amount, round);


	  score += cast_weights->m_mapN0bw.getOrUpdateScore(std::make_pair(*(m_Context.n0b1w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0bt.getOrUpdateScore(std::make_pair(m_Context.n0b1t, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN0ew.getOrUpdateScore(std::make_pair(*(m_Context.n0e1w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0et.getOrUpdateScore(std::make_pair(m_Context.n0e1t, action), m_nScoreIndex, amount, round);
   }

   // N1
   if (m_Context.n1!=-1) {
	  score += cast_weights->m_mapN1w.getOrUpdateScore(std::make_pair(*(m_Context.n1w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN1t.getOrUpdateScore(std::make_pair(m_Context.n1t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN1sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.n1sc, m_Context.n1m), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN1HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.n1length, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN1bw.getOrUpdateScore(std::make_pair(*(m_Context.n1b1w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN1bt.getOrUpdateScore(std::make_pair(m_Context.n1b1t, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN1ew.getOrUpdateScore(std::make_pair(*(m_Context.n1e1w), action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN1et.getOrUpdateScore(std::make_pair(m_Context.n1e1t, action), m_nScoreIndex, amount, round);
   }


   // N2
   if (m_Context.n2!=-1) {
		  score += cast_weights->m_mapN2w.getOrUpdateScore(std::make_pair(*(m_Context.n2w), action), m_nScoreIndex, amount, round);
		  score += cast_weights->m_mapN2t.getOrUpdateScore(std::make_pair(m_Context.n2t, action), m_nScoreIndex, amount, round);
		  score += cast_weights->m_mapN2sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.n2sc, m_Context.n2m), action), m_nScoreIndex, amount, round);
		  score += cast_weights->m_mapN2HeadEduSize.getOrUpdateScore(std::make_pair(m_Context.n2length, action), m_nScoreIndex, amount, round);

		  score += cast_weights->m_mapN2bw.getOrUpdateScore(std::make_pair(*(m_Context.n2b1w), action), m_nScoreIndex, amount, round);
		  score += cast_weights->m_mapN2bt.getOrUpdateScore(std::make_pair(m_Context.n2b1t, action), m_nScoreIndex, amount, round);

		  score += cast_weights->m_mapN2ew.getOrUpdateScore(std::make_pair(*(m_Context.n2e1w), action), m_nScoreIndex, amount, round);
		  score += cast_weights->m_mapN2et.getOrUpdateScore(std::make_pair(m_Context.n2e1t, action), m_nScoreIndex, amount, round);
   }

   // S0 S1
   if (m_Context.s1!=0) {
	  score += cast_weights->m_mapS0wS1w.getOrUpdateScore(std::make_pair(m_Context.s0ws1w, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0tS1t.getOrUpdateScore(std::make_pair(m_Context.s0ts1t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0cS1c.getOrUpdateScore(std::make_pair(m_Context.s0cs1c, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0bwS1bw.getOrUpdateScore(std::make_pair(m_Context.s0bws1bw, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0btS1bt.getOrUpdateScore(std::make_pair(m_Context.s0bts1bt, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0ewS1ew.getOrUpdateScore(std::make_pair(m_Context.s0ews1ew, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0etS1et.getOrUpdateScore(std::make_pair(m_Context.s0ets1et, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0scS1sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0scs1sc, m_Context.s0m*10 +m_Context.s1m), action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0S1HeadEDUSameSentence.getOrUpdateScore(std::make_pair(m_Context.s0s1_type, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0S1Dist.getOrUpdateScore(std::make_pair(m_Context.s0s1_dist, action), m_nScoreIndex, amount, round);
   }

   // S0 N0
   if (m_Context.s0!=0 && m_Context.n0!=-1) {
	  score += cast_weights->m_mapS0wN0w.getOrUpdateScore(std::make_pair(m_Context.s0wn0w, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0cN0t.getOrUpdateScore(std::make_pair(m_Context.s0cn0t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0tN0t.getOrUpdateScore(std::make_pair(m_Context.s0tn0t, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0bwN0bw.getOrUpdateScore(std::make_pair(m_Context.s0bwn0bw, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0btN0bt.getOrUpdateScore(std::make_pair(m_Context.s0btn0bt, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0ewN0ew.getOrUpdateScore(std::make_pair(m_Context.s0ewn0ew, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0etN0et.getOrUpdateScore(std::make_pair(m_Context.s0etn0et, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0scN0sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0scn0sc, m_Context.s0m*10 +m_Context.n0m), action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0N0HeadEDUSameSentence.getOrUpdateScore(std::make_pair(m_Context.s0n0_type, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0N0Dist.getOrUpdateScore(std::make_pair(m_Context.s0n0_dist, action), m_nScoreIndex, amount, round);
   }

   // S1 N0
   if (m_Context.s1!=0 && m_Context.n0!=-1) {
	  score += cast_weights->m_mapS1wN0w.getOrUpdateScore(std::make_pair(m_Context.s1wn0w, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1cN0t.getOrUpdateScore(std::make_pair(m_Context.s1cn0t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1tN0t.getOrUpdateScore(std::make_pair(m_Context.s1tn0t, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1bwN0bw.getOrUpdateScore(std::make_pair(m_Context.s1bwn0bw, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1btN0bt.getOrUpdateScore(std::make_pair(m_Context.s1btn0bt, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1ewN0ew.getOrUpdateScore(std::make_pair(m_Context.s1ewn0ew, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1etN0et.getOrUpdateScore(std::make_pair(m_Context.s1etn0et, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1scN0sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s1scn0sc, m_Context.s1m*10 +m_Context.n0m), action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1N0HeadEDUSameSentence.getOrUpdateScore(std::make_pair(m_Context.s1n0_type, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1N0Dist.getOrUpdateScore(std::make_pair(m_Context.s1n0_dist, action), m_nScoreIndex, amount, round);

   }

   //S1 S2
   if (m_Context.s2!=0) {
	  score += cast_weights->m_mapS1wS2w.getOrUpdateScore(std::make_pair(m_Context.s1ws2w, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1tS2t.getOrUpdateScore(std::make_pair(m_Context.s1ts2t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1cS2c.getOrUpdateScore(std::make_pair(m_Context.s1cs2c, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1bwS2bw.getOrUpdateScore(std::make_pair(m_Context.s1bws2bw, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1btS2bt.getOrUpdateScore(std::make_pair(m_Context.s1bts2bt, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1ewS2ew.getOrUpdateScore(std::make_pair(m_Context.s1ews2ew, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1etS2et.getOrUpdateScore(std::make_pair(m_Context.s1ets2et, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1scS2sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s1scs2sc, m_Context.s1m*10 +m_Context.s2m), action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS1S2HeadEDUSameSentence.getOrUpdateScore(std::make_pair(m_Context.s1s2_type, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS1S2Dist.getOrUpdateScore(std::make_pair(m_Context.s1s2_dist, action), m_nScoreIndex, amount, round);
   }

   // N0 N1
   if (m_Context.n1!=-1) {
	  score += cast_weights->m_mapN0wN1w.getOrUpdateScore(std::make_pair(m_Context.n0wn1w, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0tN1t.getOrUpdateScore(std::make_pair(m_Context.n0tn1t, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN0bwN1bw.getOrUpdateScore(std::make_pair(m_Context.n0bwn1bw, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0btN1bt.getOrUpdateScore(std::make_pair(m_Context.n0btn1bt, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN0ewN1ew.getOrUpdateScore(std::make_pair(m_Context.n0ewn1ew, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapN0etN1et.getOrUpdateScore(std::make_pair(m_Context.n0etn1et, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapN0scN1sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.n0scn1sc, m_Context.n0m*10 +m_Context.n1m), action), m_nScoreIndex, amount, round);
   }


   // S0 S1 N0
   if(m_Context.s1!=0 && m_Context.n0!=-1)
   {
	   score += cast_weights->m_mapS0cS1cN0t.getOrUpdateScore(std::make_pair(m_Context.s0cs1cn0t, action), m_nScoreIndex, amount, round);

	   score += cast_weights->m_mapS0tS1tN0t.getOrUpdateScore(std::make_pair(m_Context.s0ts1tn0t, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0btS1btN0bt.getOrUpdateScore(std::make_pair(m_Context.s0bts1btn0bt, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0etS1etN0et.getOrUpdateScore(std::make_pair(m_Context.s0ets1etn0et, action), m_nScoreIndex, amount, round);
	   score += cast_weights->m_mapS0scS1scN0sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0scs1scn0sc, 100*m_Context.s0m + 10*m_Context.s1m + m_Context.n0m), action), m_nScoreIndex, amount, round);
   }

   // S0 N0 N1
   if (m_Context.s0!=0 && m_Context.n1!=-1) {
	  score += cast_weights->m_mapS0cN0tN1t.getOrUpdateScore(std::make_pair(m_Context.s0cn0tn1t, action), m_nScoreIndex, amount, round); // m_Context.n0

	  score += cast_weights->m_mapS0tN0tN1t.getOrUpdateScore(std::make_pair(m_Context.s0tn0tn1t, action), m_nScoreIndex, amount, round); // m_Context.n0
	  score += cast_weights->m_mapS0btN0btN1bt.getOrUpdateScore(std::make_pair(m_Context.s0btn0btn1bt, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0etN0etN1et.getOrUpdateScore(std::make_pair(m_Context.s0etn0etn1et, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0scN0scN1sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0scn0scn1sc, 100*m_Context.s0m + 10*m_Context.n0m + m_Context.n1m), action), m_nScoreIndex, amount, round);
   }


   // S0 S1 S2
   if (m_Context.s2!=0) {
	  score += cast_weights->m_mapS0cS1cS2c.getOrUpdateScore(std::make_pair(m_Context.s0cs1cs2c, action), m_nScoreIndex, amount, round);

	  score += cast_weights->m_mapS0tS1tS2t.getOrUpdateScore(std::make_pair(m_Context.s0ts1ts2t, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0btS1btS2bt.getOrUpdateScore(std::make_pair(m_Context.s0bts1bts2bt, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0etS1etS2et.getOrUpdateScore(std::make_pair(m_Context.s0ets1ets2et, action), m_nScoreIndex, amount, round);
	  score += cast_weights->m_mapS0scS1scS2sc.getOrUpdateScore(std::make_pair(std::make_pair(m_Context.s0scs1scs2sc, 100*m_Context.s0m + 10*m_Context.s1m + m_Context.s2m), action), m_nScoreIndex, amount, round);
   }


   score += cast_weights->m_mapA1.getOrUpdateScore(std::make_pair(a1, action), m_nScoreIndex, amount, round);
   refer_or_allocate_tuple2(tuple_action2, &a1, &a2);
   score += cast_weights->m_mapA1A2.getOrUpdateScore(std::make_pair(tuple_action2, action), m_nScoreIndex, amount, round);

   return score;
}

/*---------------------------------------------------------------
 *
 * getGlobalScore - get the score of a parse tree
 *
 * Inputs: parse graph
 *
 *---------------------------------------------------------------*/

SCORE_TYPE CDisParser::getGlobalScore(const CSentenceParsed &parsed) {
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

void CDisParser::updateScores(const CSentenceParsed & parsed , const CSentenceParsed & correct , int round ) {
   
   THROW("Unsupported method");
}


/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/

void CDisParser::updateScoresForStates( const CStateItem *outout , const CStateItem *correct ) {

   TRACE("updating parameters ... ") ;


   const static CStateItem* states_gold[MAX_SENTENCE_SIZE*2+2];
   const static CStateItem* states_pred[MAX_SENTENCE_SIZE*2+2];

   static int count_gold, count_pred, exc_count;
   const CStateItem *current;
   SCORE_TYPE score, score_gold, score_pred;
   score = score_gold = score_pred = 0;

   count_pred = 0;
   current = outout;
   while (current) {
	  states_pred[count_pred] = current;
      ++count_pred ; //updating
      current = current->statePtr;
   }
   --count_pred; // state [0..count] are the reverse lifecycle of item.

   count_gold = 0;
   current = correct;
   while (current) {
	  states_gold[count_gold] = current;
      ++count_gold ; //updating
      current = current->statePtr;
   }
   --count_gold; // state [0..count] are the reverse lifecycle of item.

   assert(count_gold == count_pred);
   exc_count = count_gold;

   while(exc_count > 0)
   {
	   if(states_gold[exc_count-1] != states_pred[exc_count-1])
	   {
		   break;
	   }
	   assert(states_gold[exc_count-1] == states_pred[exc_count-1]);

	   m_Context.load(states_gold[exc_count], false);
	   const CAction &action = states_gold[exc_count-1]->action;
	   score = getOrUpdateStackScore(static_cast<CWeight*>(m_weights), states_gold[exc_count], action);
	   score_pred += score;
	   score_gold += score;
	   exc_count--;
   }

   while(exc_count > 0)
   {
	   m_Context.load(states_gold[exc_count], false);
	   const CAction &gold_action = states_gold[exc_count-1]->action;
	   score = getOrUpdateStackScore(static_cast<CWeight*>(m_weights), states_gold[exc_count], gold_action);
	   score_gold += score;

	   m_Context.load(states_pred[exc_count], false);
	   const CAction &pred_action = states_pred[exc_count-1]->action;
	   score = getOrUpdateStackScore(static_cast<CWeight*>(m_weights), states_pred[exc_count], pred_action);
	   score_pred += score;

	   m_Context.load(states_gold[exc_count], true);
	   getOrUpdateStackScore(m_delta, states_gold[exc_count], gold_action, 1, m_nTrainingRound);
	   //m_delta->outputScores();
	   //m_delta->clear();
	   m_Context.load(states_pred[exc_count], true);
	   getOrUpdateStackScore(m_delta, states_pred[exc_count], pred_action, -1, m_nTrainingRound);
	   exc_count--;
	   //std::cout << "gold: " << gold_action.str() << " pred: " << pred_action.str() << std::endl;
   }

   if( std::abs(states_pred[0]->score-score_pred) > 0.000001
	|| std::abs(states_gold[0]->score-score_gold) > 0.000001
	|| score_gold > score_pred+0.000001)
   {
	   std::cout << "update error ......" << std::endl;
	   assert(0);
   }

   static_cast<CWeight*>(m_weights)->addCurrent(m_delta, m_nTrainingRound);
   //m_delta->outputScores();
   m_delta->clear();

   m_nTotalErrors++;
}



/*---------------------------------------------------------------
 *
 * getOrUpdateScore - get or update the score of a state and act
 *
 *--------------------------------------------------------------*/

void CDisParser::getOrUpdateScore(const discourse::CStateItem &item, const discourse::CAction &action, discourse::SCORE_TYPE amount, int round ) {
   THROW("Not implemented");
}

/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CSentenceParsed 
 *
 *--------------------------------------------------------------*/

void CDisParser::work( const bool bTrain , const CSentenceParsed &input , CSentenceParsed *retval , const CSentenceParsed &correct , int nBest , SCORE_TYPE *scores ) {

   static CStateItem lattice[(MAX_SENTENCE_SIZE*2+2)*(AGENDA_SIZE+1)];
   static CStateItem *lattice_index[MAX_SENTENCE_SIZE*2+2];

#ifdef DEBUG
   clock_t total_start_time = clock();
#endif

   const int length = input.edu_starts.size();

   const static CStateItem *pGenerator ;
   const static CStateItem *pBestGen;
   const static CStateItem *correctState ;
   static bool bCorrect ;  // used in learning for early update
   static int tmp_i, tmp_j, tmp_k;
   static CAction correct_action;
   static CScoredStateAction scored_correct_action;
   static bool correct_action_scored;
   static std::vector<CAction> actions; // actions to apply for a candidate
   static CAgendaSimple<CScoredStateAction> beam(AGENDA_SIZE);
   static CScoredStateAction scored_action; // used rank actions
   ASSERT(nBest=1, "currently only do 1 best parse");
   static unsigned index;
   static bool bSkipLast;
   static SCORE_TYPE score;

   assert(length<MAX_SENTENCE_SIZE);

   TRACE("Initialising the decoding process ... ") ;
   // initialise word cache
   m_sent.clear();
   m_edu_starts.clear();
   m_edu_ends.clear();
   m_edu_sentids.clear();
   m_edu_paraids.clear();
   m_sent_first_edus.clear();
   m_para_first_edus.clear();
   m_edu_headspans.clear();
   m_syn_nodes.clear();
   m_syn_roots.clear();
   m_syn_starts.clear();
   m_syn_ends.clear();

   for ( tmp_i=0; tmp_i<input.words.size(); tmp_i++ ) {
	   m_sent.push_back( CTaggedWord<CTag, TAG_SEPARATOR>(input.words[tmp_i].first , input.words[tmp_i].second) );
	   //std::cout << "(" << m_sent[tmp_i].word.code() << "," << m_sent[tmp_i].tag.code() << ") ";
   }
   //std::cout << std::endl;
   for ( tmp_i=0; tmp_i<input.edu_starts.size();tmp_i++)
   {
	   m_edu_starts.push_back(input.edu_starts[tmp_i]);
	   m_edu_ends.push_back(input.edu_ends[tmp_i]);
   }
   for ( tmp_i=0; tmp_i<input.syn_roots.size();tmp_i++)
   {
	   m_syn_roots.push_back(input.syn_roots[tmp_i]);
	   m_syn_starts.push_back(input.syn_starts[tmp_i]);
	   m_syn_ends.push_back(input.syn_ends[tmp_i]);
   }
   tmp_j = 0;
   tmp_k = 0;
   for ( tmp_i=0; tmp_i<input.syn_nodes.size();tmp_i++)
   {
	   CConstituent cur_constituent(0);
	   CConNode::CON_NODE_TYPE type = CConNode::LEAF;
	   if(!input.syn_nodes[tmp_i].is_leaf)
	   {
		   cur_constituent = CConstituent(input.syn_nodes[tmp_i].constituent);
		   if(input.syn_nodes[tmp_i].single_child)
		   {
			   type = CConNode::SINGLE_CHILD;
		   }
		   else
		   {
			   cur_constituent.setTemporary(input.syn_nodes[tmp_i].temp);
			   if(input.syn_nodes[tmp_i].head_left)type = CConNode::HEAD_LEFT;
			   else type = CConNode::HEAD_RIGHT;
		   }

	   }
	   CConNode conNode(tmp_i, type, input.syn_nodes[tmp_i].temp, cur_constituent.code(),
			   input.syn_nodes[tmp_i].head_start, tmp_j, tmp_k,
			   input.syn_nodes[tmp_i].token_start, input.syn_nodes[tmp_i].token_end);
	   if(tmp_i == m_syn_ends[tmp_j])
	   {
		   tmp_j++;
		   int end_word = input.syn_nodes[tmp_i].token_end;
		   assert( end_word == m_sent.size()-1 || (m_sent[end_word+1].tag == 0));
		   if(end_word == m_sent.size()-1 || (m_sent[end_word+1].word == CWord("<P>")))
		   {
			   tmp_k++;
		   }
	   }
	   m_syn_nodes.push_back(conNode);
   }
   for ( tmp_i=0; tmp_i<input.syn_nodes.size();tmp_i++)
   {
	   m_syn_nodes[tmp_i].left_child = input.syn_nodes[tmp_i].left_child == -1 ? 0 : &m_syn_nodes[input.syn_nodes[tmp_i].left_child];
	   m_syn_nodes[tmp_i].right_child = input.syn_nodes[tmp_i].right_child == -1 ? 0 :&m_syn_nodes[input.syn_nodes[tmp_i].right_child];
   }

   tmp_j = 0;
   tmp_k = 0;
   m_sent_first_edus.push_back(0);
   m_para_first_edus.push_back(0);
   for ( tmp_i=0; tmp_i<input.edu_starts.size();tmp_i++)
   {
	   std::vector<const CConNode *> headspans;
	   headspans.clear();
	   m_edu_sentids.push_back(tmp_j);
	   m_edu_paraids.push_back(tmp_k);

	  int result_head, result_cfg, right_token;
	  int word_start = m_edu_starts[tmp_i];
	  int word_end = m_edu_ends[tmp_i];
	  const CConNode * syn_root = &m_syn_nodes[m_syn_roots[tmp_j]];
	  assert(syn_root->headsent_id == tmp_j);
	  if(syn_root->word_end < word_end)
	  {
		  assert(syn_root->word_end == word_end-1);
		  word_end = syn_root->word_end;

		  tmp_j++;
		  m_sent_first_edus.push_back(tmp_i+1);
		  if(m_sent[word_end+1].word == CWord("<P>")){
			  tmp_k++;
			  m_para_first_edus.push_back(tmp_i+1);
		  }
	  }

	  const CConNode * span_head = CStateItem::first_maxsynleftspan(syn_root, word_start, word_end, result_head, result_cfg, right_token);
	  assert(span_head != 0 && result_head>=word_start && result_head<=word_end);
	  if(result_cfg == 0)
	  {
		  assert(word_start == right_token);
	  }

	  if(!m_sent[result_head].tag.isPunc() || result_cfg > 0)
	  {
		  headspans.push_back(span_head);
	  }
	  //else
	  //{
		  //std::cout << m_sent[result_head].word.str() << "_" << m_sent[result_head].tag.str() << std::endl;
	  //}
	  while( right_token < word_end)
	  {
		  int span_start = right_token+1;
		  span_head = CStateItem::first_maxsynleftspan(syn_root, span_start, word_end, result_head, result_cfg, right_token);
		  assert(span_head && result_head>=span_start && result_head<=word_end);
		  if(result_cfg == 0)
		  {
			  assert(span_start == right_token);
		  }
		  if(!m_sent[result_head].tag.isPunc() || result_cfg > 0)
		  {
			  headspans.push_back(span_head);
		  }
		  //else
		  //{
			  //std::cout << m_sent[result_head].word.str() << "_" << m_sent[result_head].tag.str() << std::endl;
		  //}
	  }
	  //if(headspans.size() == 0)
	  /*{
		  std::cout << "edu: " << m_edu_starts[tmp_i] << " " << m_edu_ends[tmp_i] << std::endl;
		  for(int idx = m_edu_starts[tmp_i]; idx <= m_edu_ends[tmp_i]; idx++)
		  {
			  std::cout << m_sent[idx].word.str() << "_" << m_sent[idx].tag.str() << " ";
		  }
		  std::cout << std::endl;
		  std::cout << "span num: " << headspans.size() << std::endl;
		  for(int idx=0; idx < headspans.size(); idx++)
		  {
			  std::cout << "span: [" << headspans[idx]->word_start << ", " << headspans[idx]->word_end << "], head: " << headspans[idx]->headword
				  << ", wordpos: " << m_sent[headspans[idx]->headword].word.str() << "_" << m_sent[headspans[idx]->headword].tag.str() << std::endl;
			  std::cout << input.debugNode(headspans[idx]->id, true) << std::endl;
		  }
		  std::cout << "whole sentence: " << std::endl;
		  std::cout << input.debugNode(m_syn_roots[syn_root->headsent_id], true) << std::endl;;

	  }*/
	  m_edu_headspans.push_back(headspans);
   }

   //for ( tmp_i=0; tmp_i<m_edu_headspans.size();tmp_i++)
   //{
	//   std::cout << m_edu_headspans[tmp_i].size() << " ";
   //}

   //std::cout << std::endl;

   for(tmp_i=0; tmp_i<(MAX_SENTENCE_SIZE*2+2)*(AGENDA_SIZE+1); tmp_i++)
   {
	   lattice[tmp_i].init(&m_sent, &m_edu_starts, &m_edu_ends, &m_edu_sentids, &m_edu_paraids, &m_sent_first_edus,
	   &m_para_first_edus, &m_edu_headspans, &m_syn_nodes, &m_syn_roots, &m_syn_starts, &m_syn_ends);
   }

   // initialise agenda
   lattice_index[0] = lattice;
   lattice_index[0]->clear();

#ifndef EARLY_UPDATE
   if (bTrain) bSkipLast = false;
#endif
   lattice_index[1] = lattice+1;
   if (bTrain) { 
      correctState = lattice_index[0];
   }
   index=0;

   TRACE("Decoding start ... ") ;
   while (true) { // for each step

      ++index;
      lattice_index[index+1] = lattice_index[index];
         
      beam.clear();

      pBestGen = 0;

      if (bTrain) {
         bCorrect = false;
         correctState->StandardMove(correct, correct_action);
         correct_action_scored = false;
      }

      for (pGenerator=lattice_index[index-1]; pGenerator!=lattice_index[index]; ++pGenerator) { // for each generator

#ifndef EARLY_UPDATE
         if (bTrain && bSkipLast && pGenerator == lattice_index[index]-1) {
            getOrUpdateStackScore(static_cast<CWeight*>(m_weights), packedscores, pGenerator);
            scored_correct_action.load(correct_action, pGenerator, packedscores[correct_action.code()]);
            correct_action_scored = true;
            break;
         }
#endif

         // load context
         m_Context.load(pGenerator, false);
   
         // get actions
         m_rule.getActions(*pGenerator, actions);

         if(index == 2 * m_edu_starts.size() )
         {
        	 if(actions.size() != 1 || !actions[0].isReduceRoot())
        	 {
        		 std::cout << actions[0].str() << std::endl;
        	 }
         }
         // test correction:
         //actions.clear();
/*
         {
			 bool test_correction =  false;
        	 pGenerator->StandardMove(input, correct_action);
			 //actions.push_back(correct_action);

			 for (tmp_j=0; tmp_j<actions.size(); ++tmp_j) {
				 if(actions[tmp_j]==correct_action)
				 {
					 test_correction = true;
					 break;
				 }
			 }
			 if(!test_correction)
			 {
				 std::cout << "error pruning...." << std::endl;

				 for (int idy=0; idy<actions.size(); ++idy) {
					 std::cout << actions[idy].str() << " ";
					 if(idy%20 == 0) std::cout << std::endl;
				 }
				 std::cout << std::endl;
				 std::cout << "gold: " << correct_action.str() << " constituent: "
						 << CDisConstituent(correct_action.getConstituent()).extractConstituentCode() << std::endl;
				 std::cout << "left: "<< pGenerator->stackPtr->node.constituent.str() << " right :"
						 << pGenerator->node.constituent.str() << std::endl;
				 actions.clear();
				 m_rule.getActions(*pGenerator, actions);
			 }
			 actions.clear();
			 actions.push_back(correct_action);
         }
*/
         if (actions.size() > 0)
         {
			 for (tmp_j=0; tmp_j<actions.size(); ++tmp_j) {
				score = getOrUpdateStackScore(static_cast<CWeight*>(m_weights), pGenerator, actions[tmp_j]);
				scored_action.load(actions[tmp_j], pGenerator, score);
				beam.insertItem(&scored_action);
				if (bTrain && pGenerator == correctState && actions[tmp_j] == correct_action) {
				   scored_correct_action = scored_action;
				   correct_action_scored = true;
				}
			 }
         }
      } // done iterating generator item

      // insertItems
      for (tmp_j=0; tmp_j<beam.size(); ++tmp_j) { // insert from
         pGenerator = beam.item(tmp_j)->item;
         pGenerator->Move(lattice_index[index+1], beam.item(tmp_j)->action);
         lattice_index[index+1]->score = beam.item(tmp_j)->score;

         if ( pBestGen == 0 || lattice_index[index+1]->score > pBestGen->score ) {
            pBestGen = lattice_index[index+1];
         }

         // update bestgen
         if (bTrain) {
            if ( pGenerator == correctState && beam.item(tmp_j)->action == correct_action ) {
               correctState = lattice_index[index+1];
               bCorrect = true;
            }
         }
         ++lattice_index[index+1];
      }

      if (pBestGen->IsTerminated())
         break; // while

      // update items if correct item jump out of the agenda
      if (bTrain) { 
         if (!bCorrect ) {
            // note that if bCorrect == true then the correct state has 
            // already been updated, and the new value is one of the new states
            // among the newly produced from lattice[index+1].
            correctState->Move(lattice_index[index+1], correct_action); 
            correctState = lattice_index[index+1];
            lattice_index[index+1]->score = scored_correct_action.score;
            ++lattice_index[index+1];
            assert(correct_action_scored); // scored_correct_act valid

#ifdef EARLY_UPDATE
//         if (!bCorrect ) {
            TRACE("Error at the "<<correctState->current_edu<<"th edu; total is "<<m_edu_starts.size())
            // update
            // trace
            //correctState->trace();
            //pBestGen->trace();
            updateScoresForStates(pBestGen, correctState) ; 
            return ;
//         } // bCorrect
#else // EARLY UDPATE
            bSkipLast = true;
#endif
         } // bCorrect
      }  // bTrain
   } // while

   if (bTrain) {
      // make sure that the correct item is stack top finally
      if ( pBestGen != correctState ) {
         if (!bCorrect) {
            correctState->Move(lattice_index[index+1], correct_action); 
            correctState = lattice_index[index+1];
            lattice_index[index+1]->score = scored_correct_action.score;
            assert(correct_action_scored); // scored_correct_act valid
         }
         TRACE("The best item is not the correct one")

         //correctState->trace();
         //pBestGen->trace();
//         updateScoresByLoss(pBestGen, correctState) ; 
         updateScoresForStates(pBestGen, correctState) ; 
         return ;
      }
      else {
         TRACE("correct");
         //correctState->trace();
         //pBestGen->trace();
      }
   } 

   if (!retval) 
      return;

   TRACE("Outputing sentence");
   //pBestGen->trace();
   pBestGen->GenerateTree(retval[0] );
   if (scores) scores[0] = pBestGen->score;

   TRACE("Done, the highest score is: " << pBestGen->score ) ;
   TRACE("The total time spent: " << double(clock() - total_start_time)/CLOCKS_PER_SEC) ;
}

/*---------------------------------------------------------------
 *
 * parse - do constituent parsing to a sentence
 *
 * Returns: makes a new instance of CSentenceParsed 
 *
 *--------------------------------------------------------------*/

void CDisParser::parse( const CSentenceParsed &input , CSentenceParsed *retval , int nBest , SCORE_TYPE *scores ) {

   static CSentenceParsed empty ;

   work(false, input, retval, empty, nBest, scores ) ;

}



/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CDisParser::train( const CSentenceParsed &correct , int round ) {

   //static CTwoStringVector sentence ;
//   static CSentenceParsed outout ; 

   //UnparseSentence( &correct, &sentence ) ;

   // The following code does update for each processing stage
   m_nTrainingRound = round ;
//   work( true , sentence , &outout , correct , 1 , 0 ) ; 
   work( true , correct , 0 , correct , 1 , 0 ) ;

};



