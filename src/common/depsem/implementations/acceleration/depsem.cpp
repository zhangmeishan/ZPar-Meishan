// Copyright (C) SUTD 2015
/****************************************************************
 *                                                              *
 * depsem.cpp - the action based parser implementation       *
 *                                                              *
 * Author: Meishan Zhang                                            *
 *                                                              *
 * 2015.1.6                        *
 *                                                              *
 ****************************************************************/

#include "depsem.h"
#include "depsem_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::depsem;

const CWord g_emptyWord("");
const CTaggedWord<CTag, TAG_SEPARATOR> g_emptyTaggedWord;
const CTag g_noneTag = CTag::NONE;

#define cast_weights static_cast<CWeight*>(m_weights)
#define refer_or_allocate_tuple2(x, o1, o2) { if (amount == 0) x.refer(o1, o2); else x.allocate(o1, o2); }
#define refer_or_allocate_tuple3(x, o1, o2, o3) { if (amount == 0) x.refer(o1, o2, o3); else x.allocate(o1, o2, o3); }
#define _conll_or_empty(x) (x == "_" ? "" : x)

/*===============================================================
 *
 * CDepParser - the depsem for TARGET_LANGUAGE 
 *
 *==============================================================*/

/*---------------------------------------------------------------
 * 
 * getOrUpdateStackScore - manipulate the score from stack 
 *
 *---------------------------------------------------------------*/

inline SCORE_TYPE CDepParser::getOrUpdateStackScore( const CStateItem *item, const CSTackFeatsVec  &stackfeats, const unsigned long &action, SCORE_TYPE amount , int round ) {
   SCORE_TYPE score = 0;
   const int &st_index = item->stackempty() ? -1 : item->stacktop(); // stack top
   const int &sth_index = st_index == -1 ? -1 : item->head(st_index); // stack top head
   const int &sthh_index = sth_index == -1 ? -1 : item->head(sth_index); // stack top head
   const int &stld_index = st_index == -1 ? -1 : item->leftdep(st_index); // leftmost dep of stack
   const int &strd_index = st_index == -1 ? -1 : item->rightdep(st_index); // rightmost dep st
   const int &stl2d_index = stld_index == -1 ? -1 : item->sibling(stld_index); // left 2ndmost dep of stack
   const int &str2d_index = strd_index == -1 ? -1 : item->sibling(strd_index); // right 2ndmost dep st
   const int &n0_index = item->size()==m_lCache.size() ? -1 : item->size(); // next
   if(n0_index>=static_cast<int>(m_lCache.size()))
   {
	   assert(0);
   }
   const int &n0ld_index = n0_index==-1 ? -1 : item->leftdep(n0_index); // leftmost dep of next
   const int &n0l2d_index = n0ld_index==-1 ? -1 : item->sibling(n0ld_index); // leftmost dep of next
   const int &ht_index = item->headstackempty() ? -1 : item->headstacktop(); // headstack
   const int &ht2_index = item->headstacksize()<2 ? -1 : item->headstackitem(item->headstacksize()-2); // headstack 2nd
   static int n1_index;
   static int n2_index;
   static int n3_index;
   n1_index = (n0_index != -1 && n0_index+1<m_lCache.size()) ? n0_index+1 : -1 ;
   n2_index = (n0_index != -1 && n0_index+2<m_lCache.size()) ? n0_index+2 : -1 ;
   n3_index = (n0_index != -1 && n0_index+3<m_lCache.size()) ? n0_index+3 : -1 ;

   static int action_type, action_syn, action_sem;
   //action_type = action::getUnlabeledAction(action);
   action_type = action;
   action_syn = action::getSynLabel(action);
   action_sem = action::getSemLabel(action);


   const CTaggedWord<CTag, TAG_SEPARATOR> &st_word_tag = st_index==-1 ? g_emptyTaggedWord : m_lCache[st_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &sth_word_tag = sth_index==-1 ? g_emptyTaggedWord : m_lCache[sth_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &sthh_word_tag = sthh_index==-1 ? g_emptyTaggedWord : m_lCache[sthh_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &stld_word_tag = stld_index==-1 ? g_emptyTaggedWord : m_lCache[stld_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &strd_word_tag = strd_index==-1 ? g_emptyTaggedWord : m_lCache[strd_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &stl2d_word_tag = stl2d_index==-1 ? g_emptyTaggedWord : m_lCache[stl2d_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &str2d_word_tag = str2d_index==-1 ? g_emptyTaggedWord : m_lCache[str2d_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &n0_word_tag = n0_index==-1 ? g_emptyTaggedWord : m_lCache[n0_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &n0ld_word_tag = n0ld_index==-1 ? g_emptyTaggedWord : m_lCache[n0ld_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &n0l2d_word_tag = n0l2d_index==-1 ? g_emptyTaggedWord : m_lCache[n0l2d_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &n1_word_tag = n1_index==-1 ? g_emptyTaggedWord : m_lCache[n1_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &n2_word_tag = n2_index==-1 ? g_emptyTaggedWord : m_lCache[n2_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &ht_word_tag = ht_index==-1 ? g_emptyTaggedWord : m_lCache[ht_index];
   const CTaggedWord<CTag, TAG_SEPARATOR> &ht2_word_tag = ht2_index==-1 ? g_emptyTaggedWord : m_lCache[ht2_index];

   const CWord &st_word = st_word_tag.word;
   const CWord &sth_word = sth_word_tag.word;
   const CWord &sthh_word = sthh_word_tag.word;
   const CWord &stld_word = stld_word_tag.word;
   const CWord &strd_word = strd_word_tag.word;
   const CWord &stl2d_word = stl2d_word_tag.word;
   const CWord &str2d_word = str2d_word_tag.word;
   const CWord &n0_word = n0_word_tag.word;
   const CWord &n0ld_word = n0ld_word_tag.word;
   const CWord &n0l2d_word = n0l2d_word_tag.word;
   const CWord &n1_word = n1_word_tag.word;
   const CWord &n2_word = n2_word_tag.word;
   const CWord &ht_word = ht_word_tag.word;
   const CWord &ht2_word = ht2_word_tag.word;

   const CTag &st_tag = st_word_tag.tag;
   const CTag &sth_tag = sth_word_tag.tag;
   const CTag &sthh_tag = sthh_word_tag.tag;
   const CTag &stld_tag = stld_word_tag.tag;
   const CTag &strd_tag = strd_word_tag.tag;
   const CTag &stl2d_tag = stl2d_word_tag.tag;
   const CTag &str2d_tag = str2d_word_tag.tag;
   const CTag &n0_tag = n0_word_tag.tag;
   const CTag &n0ld_tag = n0ld_word_tag.tag;
   const CTag &n0l2d_tag = n0l2d_word_tag.tag;
   const CTag &n1_tag = n1_word_tag.tag;
   const CTag &n2_tag = n2_word_tag.tag;
   const CTag &ht_tag = ht_word_tag.tag;
   const CTag &ht2_tag = ht2_word_tag.tag;

   const int &st_synlabel = st_index==-1 ? CDependencyLabel::NONE : item->synlabel(st_index);
   const int &sth_synlabel = sth_index==-1 ? CDependencyLabel::NONE : item->synlabel(sth_index);
   const int &stld_synlabel = stld_index==-1 ? CDependencyLabel::NONE : item->synlabel(stld_index);
   const int &strd_synlabel = strd_index==-1 ? CDependencyLabel::NONE : item->synlabel(strd_index);
   const int &stl2d_synlabel = stl2d_index==-1 ? CDependencyLabel::NONE : item->synlabel(stl2d_index);
   const int &str2d_synlabel = str2d_index==-1 ? CDependencyLabel::NONE : item->synlabel(str2d_index);
   const int &n0ld_synlabel = n0ld_index==-1 ? CDependencyLabel::NONE : item->synlabel(n0ld_index);
   const int &n0l2d_synlabel = n0l2d_index==-1 ? CDependencyLabel::NONE : item->synlabel(n0l2d_index);

   const int &st_semlabel = st_index==-1 ? CSemanticLabel::NONE : item->semlabel(st_index);
   const int &sth_semlabel = sth_index==-1 ? CSemanticLabel::NONE : item->semlabel(sth_index);
   const int &stld_semlabel = stld_index==-1 ? CSemanticLabel::NONE : item->semlabel(stld_index);
   const int &strd_semlabel = strd_index==-1 ? CSemanticLabel::NONE : item->semlabel(strd_index);
   const int &stl2d_semlabel = stl2d_index==-1 ? CSemanticLabel::NONE : item->semlabel(stl2d_index);
   const int &str2d_semlabel = str2d_index==-1 ? CSemanticLabel::NONE : item->semlabel(str2d_index);
   const int &n0ld_semlabel = n0ld_index==-1 ? CSemanticLabel::NONE : item->semlabel(n0ld_index);
   const int &n0l2d_semlabel = n0l2d_index==-1 ? CSemanticLabel::NONE : item->semlabel(n0l2d_index);

   static int st_n0_dist;
   st_n0_dist = encodeLinkDistance(st_index, n0_index);

   const int st_rarity = st_index==-1?0:item->rightarity(st_index);
   const int st_larity = st_index==-1?0:item->leftarity(st_index);
   const int n0_larity = n0_index==-1?0:item->leftarity(n0_index);

   const CSetOfTags<CDependencyLabel> &str_syntagset = st_index==-1?CSetOfTags<CDependencyLabel>():item->rightsyntagset(st_index);
   const CSetOfTags<CDependencyLabel> &stl_syntagset = st_index==-1?CSetOfTags<CDependencyLabel>():item->leftsyntagset(st_index);
   const CSetOfTags<CDependencyLabel> &n0l_syntagset = n0_index==-1?CSetOfTags<CDependencyLabel>():item->leftsyntagset(n0_index);

   const CSetOfTags<CSemanticLabel> &str_semtagset = st_index==-1?CSetOfTags<CSemanticLabel>():item->rightsemtagset(st_index);
   const CSetOfTags<CSemanticLabel> &stl_semtagset = st_index==-1?CSetOfTags<CSemanticLabel>():item->leftsemtagset(st_index);
   const CSetOfTags<CSemanticLabel> &n0l_semtagset = n0_index==-1?CSetOfTags<CSemanticLabel>():item->leftsemtagset(n0_index);

   static CTwoTaggedWords st_word_tag_n0_word_tag ;
   static CTwoWords st_word_n0_word ;
   if ( amount == 0 ) {
      st_word_tag_n0_word_tag.refer( &st_word_tag, &n0_word_tag );
      st_word_n0_word.refer( &st_word, &n0_word );
   }
   else {
      st_word_tag_n0_word_tag.allocate( st_word_tag, n0_word_tag );
      st_word_n0_word.allocate( st_word, n0_word );
   }

   static CTuple2<CWord, CTag> word_tag;
   static CTuple2<CWord, int> word_int;
   static CTuple2<CTag, int> tag_int;
   static CTuple3<CWord, CTag, CTag> word_tag_tag;
   static CTuple3<CWord, CWord, CTag> word_word_tag;
   static CTuple3<CWord, CWord, int> word_word_int;
   static CTuple3<CTag, CTag, int> tag_tag_int;
   static CTuple2<CWord, CSetOfTags<CDependencyLabel> > word_synlableset;
   static CTuple2<CTag, CSetOfTags<CDependencyLabel> > tag_synlabelset;

   static CTuple2<CWord, CSetOfTags<CSemanticLabel> > word_semlableset;
   static CTuple2<CTag, CSetOfTags<CSemanticLabel> > tag_semlabelset;

   CWeight* curweight;
   if(std::abs(amount) > 1e-20)
   {
	   curweight = m_delta_weight;
   }
   else
   {
	   curweight = cast_weights;
   }

   // single
   if (st_index != -1) {
      score += curweight->m_mapSTw.getOrUpdateScore( std::make_pair(st_word, action_type), m_nScoreIndex, amount, round) ;
      score += curweight->m_mapSTt.getOrUpdateScore( std::make_pair(st_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTwt.getOrUpdateScore( std::make_pair(st_word_tag, action_type), m_nScoreIndex, amount, round) ;
   }

   if (n0_index != -1) {
      score += curweight->m_mapN0w.getOrUpdateScore( std::make_pair(n0_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0t.getOrUpdateScore( std::make_pair(n0_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0wt.getOrUpdateScore( std::make_pair(n0_word_tag, action_type), m_nScoreIndex, amount, round) ;
   }

   if (n1_index != -1) {
      score += curweight->m_mapN1w.getOrUpdateScore( std::make_pair(n1_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN1t.getOrUpdateScore( std::make_pair(n1_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN1wt.getOrUpdateScore( std::make_pair(n1_word_tag, action_type), m_nScoreIndex, amount, round) ;
   }

   if (n2_index != -1) {
      score += curweight->m_mapN2w.getOrUpdateScore( std::make_pair(n2_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN2t.getOrUpdateScore( std::make_pair(n2_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN2wt.getOrUpdateScore( std::make_pair(n2_word_tag, action_type), m_nScoreIndex, amount, round) ;
   }

   if (sth_index != -1) {
      score += curweight->m_mapSTHw.getOrUpdateScore( std::make_pair(sth_word, action_type), m_nScoreIndex, amount, round) ;
      score += curweight->m_mapSTHt.getOrUpdateScore( std::make_pair(sth_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTi.getOrUpdateScore( std::make_pair(st_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (sthh_index != -1) {
      score += curweight->m_mapSTHHw.getOrUpdateScore( std::make_pair(sthh_word, action_type), m_nScoreIndex, amount, round) ;
      score += curweight->m_mapSTHHt.getOrUpdateScore( std::make_pair(sthh_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTHi.getOrUpdateScore( std::make_pair(sth_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (stld_index != -1) {
      score += curweight->m_mapSTLDw.getOrUpdateScore( std::make_pair(stld_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTLDt.getOrUpdateScore( std::make_pair(stld_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTLDi.getOrUpdateScore( std::make_pair(stld_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (strd_index != -1) {
      score += curweight->m_mapSTRDw.getOrUpdateScore( std::make_pair(strd_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTRDt.getOrUpdateScore( std::make_pair(strd_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTRDi.getOrUpdateScore( std::make_pair(strd_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (n0ld_index != -1) {
      score += curweight->m_mapN0LDw.getOrUpdateScore( std::make_pair(n0ld_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0LDt.getOrUpdateScore( std::make_pair(n0ld_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0LDi.getOrUpdateScore( std::make_pair(n0ld_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (stl2d_index != -1) {
      score += curweight->m_mapSTL2Dw.getOrUpdateScore( std::make_pair(stl2d_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTL2Dt.getOrUpdateScore( std::make_pair(stl2d_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTL2Di.getOrUpdateScore( std::make_pair(stl2d_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (str2d_index != -1) {
      score += curweight->m_mapSTR2Dw.getOrUpdateScore( std::make_pair(str2d_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTR2Dt.getOrUpdateScore( std::make_pair(str2d_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTR2Di.getOrUpdateScore( std::make_pair(str2d_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   if (n0l2d_index != -1) {
      score += curweight->m_mapN0L2Dw.getOrUpdateScore( std::make_pair(n0l2d_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0L2Dt.getOrUpdateScore( std::make_pair(n0l2d_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0L2Di.getOrUpdateScore( std::make_pair(n0l2d_synlabel, action_type), m_nScoreIndex, amount, round) ;
   }

   // s0 and n0
   if (st_index != -1) {
      score += curweight->m_mapSTwtN0wt.getOrUpdateScore( std::make_pair(st_word_tag_n0_word_tag, action_type), m_nScoreIndex, amount, round );
      refer_or_allocate_tuple3(word_word_tag, &st_word, &n0_word, &st_tag);
      score += curweight->m_mapSTwtN0w.getOrUpdateScore( std::make_pair(word_word_tag, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(word_word_tag, &st_word, &n0_word, &n0_tag);
      score += curweight->m_mapSTwN0wt.getOrUpdateScore( std::make_pair(word_word_tag, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(word_tag_tag, &st_word, &st_tag, &n0_tag);
      score += curweight->m_mapSTwtN0t.getOrUpdateScore( std::make_pair(word_tag_tag, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(word_tag_tag, &n0_word, &st_tag, &n0_tag);
      score += curweight->m_mapSTtN0wt.getOrUpdateScore( std::make_pair(word_tag_tag, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTwN0w.getOrUpdateScore( std::make_pair(st_word_n0_word, action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtN0t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 2>(encodeTags(st_tag,n0_tag)), action_type), m_nScoreIndex, amount, round ) ;
   }

   if (st_index != -1 && n0_index != -1) {
      score += curweight->m_mapN0tN1t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 2>(encodeTags(n0_tag,n1_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0tN1tN2t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(n0_tag,n1_tag,n2_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtN0tN1t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,n0_tag,n1_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtN0tN0LDt.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,n0_tag,n0ld_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapN0tN0LDtN0L2Dt.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(n0_tag,n0ld_tag,n0l2d_tag)), action_type), m_nScoreIndex, amount, round ) ;
   }
   if (st_index!=-1) {
      score += curweight->m_mapSTHtSTtN0t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(sth_tag,st_tag,n0_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTHHtSTHtSTt.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(sthh_tag, sth_tag,st_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtSTLDtN0t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,stld_tag,n0_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtSTLDtSTL2Dt.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,stld_tag,stl2d_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtSTRDtN0t.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,strd_tag,n0_tag)), action_type), m_nScoreIndex, amount, round ) ;
      score += curweight->m_mapSTtSTRDtSTR2Dt.getOrUpdateScore( std::make_pair(CTagSet<CTag, 3>(encodeTags(st_tag,strd_tag,str2d_tag)), action_type), m_nScoreIndex, amount, round ) ;
   }

   // distance
   if (st_index!=-1 && n0_index!=-1) {
      refer_or_allocate_tuple2(word_int, &st_word, &st_n0_dist);
      score += curweight->m_mapSTwd.getOrUpdateScore( std::make_pair(word_int, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_int, &st_tag, &st_n0_dist);
      score += curweight->m_mapSTtd.getOrUpdateScore( std::make_pair(tag_int, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple2(word_int, &n0_word, &st_n0_dist);
      score += curweight->m_mapN0wd.getOrUpdateScore( std::make_pair(word_int, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple2(tag_int, &n0_tag, &st_n0_dist);
      score += curweight->m_mapN0td.getOrUpdateScore( std::make_pair(tag_int, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(word_word_int, &st_word, &n0_word, &st_n0_dist);
      score += curweight->m_mapSTwN0wd.getOrUpdateScore( std::make_pair(word_word_int, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(tag_tag_int, &st_tag, &n0_tag, &st_n0_dist);
      score += curweight->m_mapSTtN0td.getOrUpdateScore( std::make_pair(tag_tag_int, action_type), m_nScoreIndex, amount, round ) ;
   }

   // st arity
   if (st_index != -1) {
      refer_or_allocate_tuple2(word_int, &st_word, &st_rarity);
      score += curweight->m_mapSTwra.getOrUpdateScore( std::make_pair(word_int, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_int, &st_tag, &st_rarity);
      score += curweight->m_mapSTtra.getOrUpdateScore( std::make_pair(tag_int, action_type), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple2(word_int, &st_word, &st_larity);
      score += curweight->m_mapSTwla.getOrUpdateScore( std::make_pair(word_int, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_int, &st_tag, &st_larity);
      score += curweight->m_mapSTtla.getOrUpdateScore( std::make_pair(tag_int, action_type), m_nScoreIndex, amount, round ) ;
   }

   // n0 arity
   if (n0_index!=-1) {
      refer_or_allocate_tuple2(word_int, &n0_word, &n0_larity);
      score += curweight->m_mapN0wla.getOrUpdateScore( std::make_pair(word_int, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_int, &n0_tag, &n0_larity);
      score += curweight->m_mapN0tla.getOrUpdateScore( std::make_pair(tag_int, action_type), m_nScoreIndex, amount, round ) ;
   }

   // st labelset
   if (st_index != -1){
      refer_or_allocate_tuple2(word_synlableset, &st_word, &str_syntagset);
      score += curweight->m_mapSTwrp.getOrUpdateScore( std::make_pair(word_synlableset, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_synlabelset, &st_tag, &str_syntagset);
      score += curweight->m_mapSTtrp.getOrUpdateScore( std::make_pair(tag_synlabelset, action_type), m_nScoreIndex, amount, round ) ;

      refer_or_allocate_tuple2(word_synlableset, &st_word, &stl_syntagset);
      score += curweight->m_mapSTwlp.getOrUpdateScore( std::make_pair(word_synlableset, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_synlabelset, &st_tag, &stl_syntagset);
      score += curweight->m_mapSTtlp.getOrUpdateScore( std::make_pair(tag_synlabelset, action_type), m_nScoreIndex, amount, round ) ;
   }

   // n0 labelset
   if (n0_index != -1){
      refer_or_allocate_tuple2(word_synlableset, &n0_word, &n0l_syntagset);
      score += curweight->m_mapN0wlp.getOrUpdateScore( std::make_pair(word_synlableset, action_type), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_synlabelset, &n0_tag, &n0l_syntagset);
      score += curweight->m_mapN0tlp.getOrUpdateScore( std::make_pair(tag_synlabelset, action_type), m_nScoreIndex, amount, round ) ;
   }

   return score;
}

/*---------------------------------------------------------------
 *
 * getGlobalScore - get the score of a parse tree
 *
 * Inputs: parse graph
 *
 *---------------------------------------------------------------*/

SCORE_TYPE CDepParser::getGlobalScore(const CDependencyParse &parsed) {
   THROW("depsem.cpp: getGlobalScore unsupported");
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

void CDepParser::updateScores(const CDependencyParse & parsed , const CDependencyParse & correct , int round ) {
   THROW("depsem.cpp: updateScores unsupported");
}



/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/

bool CDepParser::updateScoresForStates(const CSTackFeatsVec &stackfeats,  const CStateItem *predicated_state , const CStateItem *correct_state , SCORE_TYPE amount_add, SCORE_TYPE amount_subtract ) {

   // do not update those steps where they are correct
   m_delta_weight->clear();
/*   static CStateItem item(&m_lCache);
   static unsigned long action, correct_action;
   item.clear();
   while ( item != *outout ) {
      action = item.FollowMove( outout );
      correct_action = item.FollowMove( correct );
      if ( action == correct_action )
         item.Move( action );
      else break;
   }
*/
   const CStateItem * predicated_state_chain[MAX_SENTENCE_SIZE * 2];
   const CStateItem * correct_state_chain[MAX_SENTENCE_SIZE * 2];

   int num_predicated_states = 0;
   int num_correct_states = 0;
   for (const CStateItem * p = predicated_state; p; p = p->m_preState) {
     predicated_state_chain[num_predicated_states] = p;
     ++ num_predicated_states;
   }

   for (const CStateItem * p = correct_state; p; p = p->m_preState) {
     correct_state_chain[num_correct_states] = p;
     ++ num_correct_states;
   }

   ASSERT(num_correct_states == num_predicated_states,
          "Number of predicated action don't equals the correct one");

   int i;
   for (i = num_correct_states - 1; i >= 0; -- i) {
     // if the action is different, do the update
     unsigned long predicated_action = predicated_state_chain[i]->m_nLastAction;
     unsigned long correct_action = correct_state_chain[i]->m_nLastAction;
     // std::cout << correct_action << " " << predicated_action << std::endl;
     if (predicated_action != correct_action) {
       break;
     }
   }
   // for the necessary information for the correct and outout parsetree
   //SCORE_TYPE score_gold = updateScoreForState(stackfeats, item, correct , amount_add ) ;
   //SCORE_TYPE score_pred = updateScoreForState(stackfeats, item, outout , amount_subtract ) ;

   for (i = i + 1; i > 0; -- i) {
     unsigned predicated_action = predicated_state_chain[i - 1]->m_nLastAction;
     unsigned correct_action = correct_state_chain[i - 1]->m_nLastAction;
     getOrUpdateStackScore( predicated_state_chain[i], stackfeats, predicated_action, amount_subtract, m_nTrainingRound );
     getOrUpdateStackScore( correct_state_chain[i], stackfeats, correct_action, amount_add, m_nTrainingRound );

   }

   {
	   cast_weights->addCurrent(m_delta_weight, m_nTrainingRound);
   }

   m_nTotalErrors++;
   return true;
}

/*---------------------------------------------------------------
 *
 * reduce - helper function
 *
 *--------------------------------------------------------------*/

inline void CDepParser::reduce( const CStateItem *item, const CSTackFeatsVec &stackfeats) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::REDUCE;
   SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
   scoredaction.score = item->score + score;
   m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * arcleft - helping function
 *
 *--------------------------------------------------------------*/

inline void CDepParser::arcleft( const CStateItem *item, const CSTackFeatsVec &stackfeats ) {
   static action::CScoredAction scoredaction;
   static unsigned long synlabel, semlabel;
   for (synlabel=CDependencyLabel::FIRST; synlabel<CDependencyLabel::COUNT; ++synlabel)
   {
	   for (semlabel=CSemanticLabel::FIRST; semlabel<CSemanticLabel::COUNT; ++semlabel)
	   {
		  if ( !m_weights->rules() || canAssignLabel(m_lCache, item->size(), item->stacktop(), synlabel, semlabel) ) {
#ifdef  SEM_WO_DUPLICATED
			  if(CSemanticLabel::canDuplicated(semlabel)
			  || (!item->leftsemtagset(item->size()).contains(semlabel)
			  && !item->rightsemtagset(item->size()).contains(semlabel)))
#endif
			 {
				 scoredaction.action = action::encodeAction(action::ARC_LEFT, synlabel, semlabel);
				 SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
				 scoredaction.score = item->score + score;
				 m_Beam->insertItem(&scoredaction);
			 }
		  }
	   }
   }

}

/*---------------------------------------------------------------
 *
 * arcright - helping function
 *
 *--------------------------------------------------------------*/

inline void CDepParser::arcright( const CStateItem *item, const CSTackFeatsVec &stackfeats ) {
   static action::CScoredAction scoredaction;
   static unsigned long synlabel, semlabel;
   for (synlabel=CDependencyLabel::FIRST; synlabel<CDependencyLabel::COUNT; ++synlabel)
   {
	   for (semlabel=CSemanticLabel::FIRST; semlabel<CSemanticLabel::COUNT; ++semlabel)
	   {
		  if ( !m_weights->rules() || canAssignLabel(m_lCache, item->stacktop(), item->size(), synlabel, semlabel) ) {
#ifdef  SEM_WO_DUPLICATED
			  if(CSemanticLabel::canDuplicated(semlabel)
			  || (!item->leftsemtagset(item->stacktop()).contains(semlabel)
			  && !item->rightsemtagset(item->stacktop()).contains(semlabel)))
#endif
			  {
				 scoredaction.action = action::encodeAction(action::ARC_RIGHT, synlabel, semlabel);
				 SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
				 scoredaction.score = item->score + score;
				 m_Beam->insertItem(&scoredaction);
			  }
		  }
	   }
   }
}

/*---------------------------------------------------------------
 *
 * shift - help function
 *
 *--------------------------------------------------------------*/

inline void CDepParser::shift( const CStateItem *item, const CSTackFeatsVec &stackfeats ) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::SHIFT;
   SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
   scoredaction.score = item->score + score;
   m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * poproot - help function
 *
 *--------------------------------------------------------------*/

inline void CDepParser::poproot( const CStateItem *item, const CSTackFeatsVec &stackfeats ) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::POP_ROOT;
   SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
   scoredaction.score = item->score + score;
   m_Beam->insertItem(&scoredaction);
}


inline void CDepParser::semanticActions( const CStateItem *item, const CSTackFeatsVec &stackfeats, unsigned long start_action, unsigned long end_action) {
   static action::CScoredAction scoredaction;
   static unsigned long semlabel;
   // update stack score
   if(start_action == end_action)
   {
	   scoredaction.action = start_action;
	   SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
	   scoredaction.score = item->score + score;
	   m_Beam->insertItem(&scoredaction);
   }
   else
   {

	   for(unsigned long curact = start_action; curact <= end_action; curact++)
	   {
#ifdef  SEM_WO_DUPLICATED
		   semlabel = action::getSemLabel(curact);
		   if( CSemanticLabel::canDuplicated(semlabel)
			  || (action::getUnlabeledAction(curact) == action::ARC_RIGHT
			  && !item->leftsemtagset(item->stacktop()).contains(semlabel)
			  && !item->rightsemtagset(item->stacktop()).contains(semlabel))
			  || (action::getUnlabeledAction(curact) == action::ARC_LEFT
			  && !item->leftsemtagset(item->size()).contains(semlabel)
			  && !item->rightsemtagset(item->size()).contains(semlabel)))
#endif
		   {
			   scoredaction.action = curact;
			   SCORE_TYPE score = getOrUpdateStackScore(item, stackfeats, scoredaction.action);
			   scoredaction.score = item->score + score;
			   m_Beam->insertItem(&scoredaction);
		   }
	   }
   }
}


bool StateHeapMore(const CStateItem * x, const CStateItem * y) {
  return x->score > y->score;
}

int
CDepParser::InsertIntoBeam(CStateItem ** beam_wrapper,
                           const CStateItem * item,
                           const int current_beam_size,
                           const int max_beam_size) {
  if (current_beam_size == max_beam_size) {
    if (*item > **beam_wrapper) {
      std::pop_heap(beam_wrapper, beam_wrapper + max_beam_size, StateHeapMore);
      **(beam_wrapper + max_beam_size - 1) = *item;
      std::push_heap(beam_wrapper, beam_wrapper + max_beam_size, StateHeapMore);
    }
    return 0;
  }

  **(beam_wrapper + current_beam_size) = *(item);
  std::push_heap(beam_wrapper, beam_wrapper + current_beam_size + 1, StateHeapMore);
  return 1;
}

CStateItem *
CDepParser::GetLattice(int max_lattice_size) {
  if (0 == lattice_) {
    max_lattice_size_ = max_lattice_size;
    lattice_ = new CStateItem[max_lattice_size];
  } else if (max_lattice_size_ < max_lattice_size) {
    delete [] lattice_;
    max_lattice_size_ = max_lattice_size;
    lattice_ = new CStateItem[max_lattice_size];
  }

  for (int i = 0; i < max_lattice_size; ++ i) { lattice_[i].clear(); }
  return lattice_;
}
   

/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CDependencyParse 
 *
 *--------------------------------------------------------------*/

void CDepParser::work( const bool bTrain , const CTwoStringVector &sentence, const CSTackFeatsVec  &stackfeats, CDependencyParse *retval , const CDependencyParse &correct , int nBest , SCORE_TYPE *scores ) {

#ifdef DEBUG
   clock_t total_start_time = clock();
#endif
   static int index;
   static unsigned long correction_action;
   const int length = sentence.size() ; 

#ifdef SEMANTIC_ONLY
   static unsigned long start_action, end_action;
#endif
   const int max_round = length * 2 + 1;
   const int max_lattice_size = (AGENDA_SIZE + 1) * max_round;

   CStateItem * lattice = GetLattice(max_lattice_size);
   CStateItem * lattice_wrapper[max_lattice_size];
   CStateItem ** lattice_index[max_round];
   CStateItem * correct_state = lattice;

   for (int i = 0; i < max_lattice_size; ++ i) {
     lattice_wrapper[i] = lattice + i;
     lattice[i].m_nLen = length;
   }

   lattice[0].clear();
   correct_state = lattice;
   lattice_index[0] = lattice_wrapper;
   lattice_index[1] = lattice_index[0] + 1;


   // used only for training
   static bool bContradictsRules;


   ASSERT(length<MAX_SENTENCE_SIZE, "The size of the sentence is larger than the system configuration.");

   TRACE("Initialising the decoding process...") ;
   // initialise word cache
   bContradictsRules = false;
   m_lCache.clear();
   for ( index=0; index<length; ++index ) {
      m_lCache.push_back( CTaggedWord<CTag, TAG_SEPARATOR>(sentence[index].first , sentence[index].second) );
      // filter std::cout training examples with rules
      if (bTrain && m_weights->rules()) {
         // the root
         if ( correct[index].head == DEPENDENCY_LINK_NO_HEAD && canBeRoot(m_lCache[index].tag.code())==false) {
            TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " can be root.");
            bContradictsRules = true;
         }
         // head left
         if ( correct[index].head < index && hasLeftHead(m_lCache[index].tag.code())==false) {
            TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " has left head.");
            bContradictsRules = true;
         }
         // head right
         if ( correct[index].head > index && hasRightHead(m_lCache[index].tag.code())==false) {
            TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " has right head.");
            bContradictsRules = true;
         }
      }
   }


   unsigned long label;
   m_lCacheLabel.clear();
   m_lCacheSemLabel.clear();
   if (bTrain) {
      for (index=0; index<length; ++index) {
         m_lCacheLabel.push_back(CDependencyLabel(correct[index].synlabel));
         m_lCacheSemLabel.push_back(CSemanticLabel(correct[index].semlabel));
         if (m_weights->rules() && !canAssignLabel(m_lCache, correct[index].head, index, m_lCacheLabel[index], m_lCacheSemLabel[index])) {
            TRACE("Rule contradiction: " << correct[index].synlabel << " on link head " << m_lCache[correct[index].head].tag.code() << " dep " << m_lCache[index].tag.code());
            bContradictsRules = true;
         }
      }
   }

#ifdef SEMANTIC_ONLY
   m_lCacheLabel.clear();
   for (index=0; index<length; ++index) {
      m_lCacheLabel.push_back(CDependencyLabel(correct[index].synlabel));
   }
#endif

   // skip the training example if contradicts
   if (bTrain && m_weights->rules() && bContradictsRules) {
      std::cout << "Skipping training example because it contradicts rules..." <<std::endl;
      return;
   }

   TRACE("Decoding started"); 
   int num_results = 0;
   int round = 0;
   bool is_correct; // used for training to specify correct state in lattice

   // loop with the next word to process in the sentence,
   // `round` represent the generators, and the condidates should be inserted
   // into the `round + 1`
   for (round = 1; round < max_round; ++ round) {
     if (lattice_index[round - 1] == lattice_index[round]) {
       // there is nothing in generators, the proning has cut all legel
       // generator. actually, in this kind of case, we should raise a
       // exception. however to achieve a parsing tree, an alternative
       // solution is go back to the previous round
       WARNING("Parsing Failed!");
       -- round;
       break;
     }
      // iterate generators
      int current_beam_size = 0;
      // loop over the generator states
      // std::cout << "round : " << round << std::endl;
      for (CStateItem ** q = lattice_index[round - 1]; q != lattice_index[round]; ++ q) {

    	  const CStateItem * pGenerator = (*q);
         // for the state items that already contain all words
         m_Beam->clear();
#ifdef SEMANTIC_ONLY
         pGenerator->GetStandardMoveActions(correct, m_lCacheLabel, start_action, end_action);
         semanticActions(pGenerator,stackfeats, start_action, end_action) ;
#else

         if ( pGenerator->size() == length ) {
            assert( pGenerator->stacksize() != 0 );
            if ( pGenerator->stacksize()>1 ) {
#ifdef FRAGMENTED_TREE
               if (pGenerator->head(pGenerator->stacktop()) == DEPENDENCY_LINK_NO_HEAD)
                  poproot(pGenerator, stackfeats);
               else
#endif
               reduce(pGenerator, stackfeats) ;
            }
            else {
               poproot(pGenerator, stackfeats);
            }
         }
         // for the state items that still need more words
         else {  
            if ( !pGenerator->afterreduce() ) { // there are many ways when there are many arcrighted items on the stack and the root need arcleft. force this.               
               if ( 
#ifndef FRAGMENTED_TREE
                    ( pGenerator->size() < length-1 || pGenerator->stackempty() ) && // keep only one global root
#endif
                    ( pGenerator->stackempty() || !m_weights->rules() || canBeRoot( m_lCache[pGenerator->size()].tag.code() ) || hasRightHead(m_lCache[pGenerator->size()].tag.code()) ) // rules
                  ) {
                  shift(pGenerator, stackfeats) ;
               }
            }
            if ( !pGenerator->stackempty() ) {
               if ( 
#ifndef FRAGMENTED_TREE
                    ( pGenerator->size() < length-1 || pGenerator->headstacksize() == 1 ) && // one root
#endif
                    ( !m_weights->rules() || hasLeftHead(m_lCache[pGenerator->size()].tag.code()) ) // rules
                  ) { 
                  arcright(pGenerator, stackfeats) ;
               }
            }
            if ( !pGenerator->stackempty() ) {
               if ( pGenerator->head( pGenerator->stacktop() ) != DEPENDENCY_LINK_NO_HEAD ) {
                  reduce(pGenerator, stackfeats) ;
               }
               else {
                  if (!m_weights->rules() || hasRightHead(m_lCache[pGenerator->stacktop()].tag.code()) // rules
                     ) {
                     arcleft(pGenerator, stackfeats) ;
                  }
               }
            }
         }
#endif

         // insert item
         for (unsigned i = 0; i < m_Beam->size(); ++ i) {
           CStateItem candidate; candidate = (*pGenerator);
           // generate candidate state according to the states in beam
           candidate.Move(m_Beam->item(i)->action);
           candidate.score = m_Beam->item(i)->score;
           candidate.m_preState = pGenerator;
           current_beam_size += InsertIntoBeam(lattice_index[round],
                                               &candidate,
                                               current_beam_size,
                                               AGENDA_SIZE);
         }
      }
      lattice_index[round + 1] = lattice_index[round] + current_beam_size;

      if (bTrain) {
        CStateItem next_correct_state(*correct_state);

        correction_action = next_correct_state.StandardMoveStep(correct, m_lCacheLabel, m_lCacheSemLabel);
        next_correct_state.Move(correction_action);
        next_correct_state.m_preState = correct_state;
        is_correct = false;

        for (CStateItem ** q = lattice_index[round]; q != lattice_index[round + 1]; ++ q) {
          CStateItem * p = *q;
          if (next_correct_state.m_nLastAction == p->m_nLastAction
              && p->m_preState == correct_state) {
            correct_state = p;
            is_correct = true;
          }
        }

  #ifdef EARLY_UPDATE
        if (!is_correct || round == max_round -1) {
          TRACE("ERROR at the " << next_correct_state.size() << "th word;"
                << " Total is " << correct.size());

          CStateItem * best_generator = (*lattice_index[round]);
          for (CStateItem ** q = lattice_index[round];
               q != lattice_index[round + 1];
               ++ q) {
            CStateItem * p = (*q);
            if (best_generator->score < p->score) {
              best_generator = p;
            }
          }
          if (best_generator != correct_state) {
        	  updateScoresForStates(stackfeats, best_generator, &next_correct_state, 1, -1);
          }
          return;
        }
  #endif // end for EARLY_UPDATE
      }

   }

   TRACE("Output sentence");
   std::sort(lattice_index[round - 1], lattice_index[round], StateHeapMore);
   num_results = lattice_index[round] - lattice_index[round - 1];

   for (int i = 0; i < std::min(num_results, nBest); ++ i) {
     assert( (*(lattice_index[round - 1] + i))->size() == m_lCache.size());
     (*(lattice_index[round - 1] + i))->GenerateTree(sentence, retval[i]);
     if (scores) { scores[i] = (*(lattice_index[round - 1] + i))->score; }
   }
   TRACE("Done, total time spent: " << double(clock() - total_start_time) / CLOCKS_PER_SEC);
}

/*---------------------------------------------------------------
 *
 * parse - do dependency parsing to a sentence
 *
 * Returns: makes a new instance of CDependencyParse 
 *
 *--------------------------------------------------------------*/

void CDepParser::parse( const CDependencyParse &input, const CSTackFeatsVec  &stackfeats , CDependencyParse *retval , int nBest , SCORE_TYPE *scores ) {

   static CDependencyParse empty ;

   static CTwoStringVector sentence ;
   UnparseSentence( &input, &sentence ) ;

   for (int i=0; i<nBest; ++i) {
      // clear the outout sentences
      retval[i].clear();
      if (scores) scores[i] = 0; //pGenerator->score;
   }

   work(false, sentence, stackfeats, retval, input, nBest, scores ) ;

}

/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CDepParser::train( const CDependencyParse &correct, const CSTackFeatsVec  &stackfeats , int round ) {

   static CTwoStringVector sentence ;
   static CDependencyParse outout ; 

#ifndef FRAGMENTED_TREE
   assert( IsProjectiveDependencyTree(correct) ) ;
#endif
   UnparseSentence( &correct, &sentence ) ;

   // The following code does update for each processing stage
#ifndef LOCAL_LEARNING
   ++m_nTrainingRound;
   ASSERT(m_nTrainingRound == round, "Training round error") ;
#endif
   work( true , sentence, stackfeats , &outout , correct , 1 , 0 ) ;

};

/*---------------------------------------------------------------
 *
 * extract_features - extract features from an example (counts recorded to parser model as weights)
 *
 *---------------------------------------------------------------*/

void CDepParser::extract_features(const CDependencyParse &input, const CSTackFeatsVec  &stackfeats, std::ofstream& os) {

   CStateItem tmp;
   unsigned long action;

   static CTwoStringVector sentence ;
   static CDependencyParse outout ;

#ifndef FRAGMENTED_TREE
   assert( IsProjectiveDependencyTree(input) ) ;
#endif
   UnparseSentence( &input, &sentence ) ;

   // word and pos
   m_lCache.clear();
   m_lCacheLabel.clear();
   m_lCacheSemLabel.clear();
   for (int i=0; i<input.size(); ++i) {
      m_lCache.push_back(CTaggedWord<CTag, TAG_SEPARATOR>(input[i].word, input[i].tag));
      m_lCacheLabel.push_back(CDependencyLabel(input[i].synlabel));
      m_lCacheSemLabel.push_back(CSemanticLabel(input[i].semlabel));
   }
   tmp.m_nLen = m_lCache.size();
   // extract feature now with another step less efficient yet easier here
   tmp.clear();
   int i = 0;
   while (i<input.size() * 2) {
	  action = tmp.StandardMoveStep(input, m_lCacheLabel, m_lCacheSemLabel);
      getOrUpdateStackScore(&tmp, stackfeats, action);
      tmp.Move(action);
      i++;
   }
   tmp.GenerateTree( sentence , outout) ;
   os << outout;
   os.flush();
}



