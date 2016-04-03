// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * depparser.cpp - the action based parser implementation       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

#include "chartagger.h"

#include "chartagger_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::chartagger;

const CWord g_emptyWord("");
const CTaggedWord<CTag, TAG_SEPARATOR> g_emptyTaggedWord;
const CTag g_noneTag = CTag::NONE;

#define cast_weights static_cast<CWeight*>(m_weights)
#define refer_or_allocate_tuple2(x, o1, o2) { if (amount == 0) x.refer(o1, o2); else x.allocate(o1, o2); }
#define refer_or_allocate_tuple3(x, o1, o2, o3) { if (amount == 0) x.refer(o1, o2, o3); else x.allocate(o1, o2, o3); }
#define refer_or_allocate_tuple4(x, o1, o2, o3, o4) { if (amount == 0) x.refer(o1, o2, o3, o4); else x.allocate(o1, o2, o3, o4); }
#define find_or_replace_word_cache(tmp_start, tmp_end) ( amount == 0 ? m_lCache.find(tmp_start, tmp_end, &m_Sentence) : m_lCache.replace(tmp_start, tmp_end, &m_Sentence) )

inline int encodeCharSegmentation(const bool &b, const bool &e) {
  return (b ? 2 : 0) + (e ? 1 : 0); // 00 01 10 11
}

inline int encodeCharInfoAndPosition(const int &char_info, const int &pos) {
  assert(pos >= -3 && pos <= 3); // pos+3 0->6
  return (char_info << 3) | (pos + 3);
}
/*===============================================================
 *
 * CCharTagger - the depparser for TARGET_LANGUAGE
 *
 *==============================================================*/

/*---------------------------------------------------------------
 * 
 * getOrUpdateStackScore - manipulate the score from stack 
 *
 *---------------------------------------------------------------*/

inline SCORE_TYPE CCharTagger::getOrUpdateStackScore(const CStateItem *item, const unsigned &action, SCORE_TYPE amount, int round) {

  SCORE_TYPE score = 0;
  // stack
  static int st0_index, st1_index, st2_index;
  static int st0_start_index, st1_start_index, st2_start_index;
  static int st0_end_index, st1_end_index, st2_end_index;

  st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
  st0_start_index = st0_index == -1 ? -1 : item->wordstart(st0_index);
  st0_end_index = st0_index == -1 ? -1 : item->wordend(st0_index);

  st1_index = item->stacksize() <= 1 ? -1 : item->stackitem(item->stacksize() - 2); // stack top head
  st1_start_index = st1_index == -1 ? -1 : item->wordstart(st1_index);
  st1_end_index = st1_index == -1 ? -1 : item->wordend(st1_index);

  st2_index = item->stacksize() <= 2 ? -1 : item->stackitem(item->stacksize() - 3); // stack top 2 head
  st2_start_index = st2_index == -1 ? -1 : item->wordstart(st2_index);
  st2_end_index = st2_index == -1 ? -1 : item->wordend(st2_index);

  //queue
  static int n0_index, n1_index, n2_index, n3_index;
  n0_index = item->nextword() >= m_Sentence.size() ? -1 : item->nextword(); // next
  n1_index = (n0_index != -1 && n0_index + 1 < m_Sentence.size()) ? n0_index + 1 : -1;
  n2_index = (n0_index != -1 && n0_index + 2 < m_Sentence.size()) ? n0_index + 2 : -1;
  n3_index = (n0_index != -1 && n0_index + 3 < m_Sentence.size()) ? n0_index + 3 : -1;

  const unsigned long long st0_length = st0_index == -1 ? 99999 : st0_end_index - st0_start_index + 1;
  const unsigned long long st1_length = st1_index == -1 ? 99999 : st1_end_index - st1_start_index + 1;

  const unsigned long long st0_nlength = st0_index == -1 ? 99999 : (st0_length > 5 ? 5 : st0_length);
  const unsigned long long st1_nlength = st1_index == -1 ? 99999 : (st1_length > 5 ? 5 : st1_length);

  const CWord &st0_word = st0_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st0_start_index, st0_end_index));
  const CWord &st1_word = st1_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st1_start_index, st1_end_index));
  const CWord &st0_char = st0_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st0_index, st0_index));
  const CWord &st1_char = st1_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st1_index, st1_index));
  const CWord &st2_char = st2_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st2_index, st2_index));

  const CWord &st0_schar = st0_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st0_start_index, st0_start_index));
  const CWord &st1_schar = st1_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st1_start_index, st1_start_index));
  const CWord &st0_echar = st0_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st0_end_index, st0_end_index));
  const CWord &st1_echar = st1_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(st1_end_index, st1_end_index));

  const CWord &n0_char = n0_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(n0_index, n0_index));
  const CWord &n1_char = n1_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(n1_index, n1_index));
  const CWord &n2_char = n2_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(n2_index, n2_index));
  const CWord &n3_char = n3_index == -1 ? g_emptyWord : CWord(find_or_replace_word_cache(n3_index, n3_index));

  const CWord &two_char = st0_index == -1 || n0_index == -1 ? g_emptyWord : find_or_replace_word_cache(st0_end_index, n0_index);
  const CWord &st1_word_st0_schar = st1_index == -1 ? g_emptyWord : find_or_replace_word_cache(st1_start_index, st0_start_index);
  const CWord &st0_word_st1_echar = st1_index == -1 ? g_emptyWord : find_or_replace_word_cache(st1_end_index, st0_end_index);
  const CWord &three_char = (st0_nlength == 1 && st1_index != -1) ? find_or_replace_word_cache(st1_end_index, n0_index) : g_emptyWord;

  static CTwoWords st1_word_st0_word, st1_schar_st0_echar, st0_schar_st1_schar, st0_echar_st1_echar;

  if (amount == 0) {
    st1_word_st0_word.refer(&st0_word, &st1_word);
    st1_schar_st0_echar.refer(&st1_schar, &st0_echar);
    st0_schar_st1_schar.refer(&st0_schar, &st1_schar);
    st0_echar_st1_echar.refer(&st0_echar, &st1_echar);
  } else {
    st1_word_st0_word.allocate(st0_word, st1_word);
    st1_schar_st0_echar.allocate(st1_schar, st0_echar);
    st0_schar_st1_schar.allocate(st0_schar, st1_schar);
    st0_echar_st1_echar.allocate(st0_echar, st1_echar);
  }

  const CTag &st0_tag = st0_index == -1 ? g_noneTag : CTag(item->pos(st0_index));
  const CTag &st1_tag = st1_index == -1 ? g_noneTag : CTag(item->pos(st1_index));
  const CTag &n0_tag = action >= action::LABEL_SH_FIRST ? CTag(action - action::LABEL_SH_FIRST + 1) : g_noneTag;

  static CTagSet<CTag, 2> n0_tag_st0_tag, n0_tag_st1_tag, st0_tag_st1_tag;
  static CTagSet<CTag, 3> n0_tag_st0_tag_st1_tag;
  n0_tag_st0_tag.load(encodeTags(n0_tag, st0_tag));
  n0_tag_st1_tag.load(encodeTags(n0_tag, st1_tag));
  st0_tag_st1_tag.load(encodeTags(st0_tag, st1_tag));
  n0_tag_st0_tag_st1_tag.load(encodeTags(n0_tag, st0_tag, st1_tag));

  unsigned long long st0_charcat = cast_weights->m_mapCharTagDictionary.lookup(st0_char);
  unsigned long long st1_charcat = cast_weights->m_mapCharTagDictionary.lookup(st1_char);

  unsigned long long st0_scharcat = cast_weights->m_mapCharTagDictionary.lookup(st0_schar);
  unsigned long long st0_echarcat = cast_weights->m_mapCharTagDictionary.lookup(st0_echar);
  unsigned long long n0_charcat = cast_weights->m_mapCharTagDictionary.lookup(n0_char);
  unsigned long long n1_charcat = cast_weights->m_mapCharTagDictionary.lookup(n1_char);
  unsigned long long n2_charcat = cast_weights->m_mapCharTagDictionary.lookup(n2_char);
  unsigned long long n3_charcat = cast_weights->m_mapCharTagDictionary.lookup(n3_char);

  static CTaggedWord<CTag, TAG_SEPARATOR> wt1, wt2;
  static CTwoTaggedWords wt12;
  static int j;

  static CTuple2<CWord, CTag> word_tag;
  static CTuple2<CTag, CTag> tag_tag;
  static CTuple2<CWord, CWord> word_word;
  static CTuple3<CWord, CTag, CTag> word_tag_tag;
  static CTuple3<CWord, CWord, CTag> word_word_tag;
  static CTuple3<CTag, CTag, CTag> tag_tag_tag;
  static CTuple3<CWord, CWord, CWord> word_word_word;

  //t:postag; w:word; c:head char; a: head char attriabute
  //shared features

  CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_weight);

  // POS Tagging features
  if (action >= action::LABEL_SH_FIRST || action == action::FINISH) {
    // adding scores with features for last word
    score += curweights->m_mapSeenWords.getOrUpdateScore(st0_word, m_nScoreIndex, amount, round);
    score += curweights->m_mapLastWordByWord.getOrUpdateScore(st1_word_st0_word, m_nScoreIndex, amount, round);

    if (st0_length == 1) {
      score += curweights->m_mapOneCharWord.getOrUpdateScore(st0_word, m_nScoreIndex, amount, round);
    } else {
      score += curweights->m_mapFirstAndLastChars.getOrUpdateScore(st1_schar_st0_echar, m_nScoreIndex, amount, round);

      score += curweights->m_mapLengthByFirstChar.getOrUpdateScore(std::make_pair(st1_schar, st0_nlength), m_nScoreIndex, amount, round);
      score += curweights->m_mapLengthByLastChar.getOrUpdateScore(std::make_pair(st0_echar, st0_nlength), m_nScoreIndex, amount, round);

      //score += m_weights->m_mapLengthByTagAndFirstChar.getOrUpdateScore( std::make_pair(st1_schar, (st0_nlength<<CTag::SIZE)|st0_tag.code()) , m_nScoreIndex , amount , round ) ;
      //score += m_weights->m_mapLengthByTagAndLastChar.getOrUpdateScore( std::make_pair(st0_echar, (st0_nlength<<CTag::SIZE)|st0_tag.code()) , m_nScoreIndex , amount , round ) ;

      score += curweights->m_mapCurrentWordLastChar.getOrUpdateScore(st0_word_st1_echar, m_nScoreIndex, amount, round);
      score += curweights->m_mapLastWordByLastChar.getOrUpdateScore(st0_echar_st1_echar, m_nScoreIndex, amount, round);

      score += curweights->m_mapLengthByLastWord.getOrUpdateScore(std::make_pair(st1_word, st0_nlength), m_nScoreIndex, amount, round);
      score += curweights->m_mapLastLengthByWord.getOrUpdateScore(std::make_pair(st0_word, st1_nlength), m_nScoreIndex, amount, round);

      score += curweights->m_mapCurrentTag.getOrUpdateScore(std::make_pair(st0_word, st0_tag), m_nScoreIndex, amount, round);

      if (st0_length <= 2)
        score += curweights->m_mapLastTagByWord.getOrUpdateScore(std::make_pair(st0_word, st1_tag), m_nScoreIndex, amount, round);

      if (st0_length <= 2)
        score += curweights->m_mapTagByWordAndPrevChar.getOrUpdateScore(std::make_pair(st0_word_st1_echar, st0_tag), m_nScoreIndex, amount, round);
      if (st0_length == 1)
        score += curweights->m_mapTagOfOneCharWord.getOrUpdateScore(std::make_pair(three_char, st0_tag), m_nScoreIndex, amount, round);

      score += curweights->m_mapTagByLastChar.getOrUpdateScore(std::make_pair(st0_echar, st0_tag), m_nScoreIndex, amount, round);
      score += curweights->m_mapTagByLastCharCat.getOrUpdateScore(std::make_pair(st0_echarcat, st0_tag), m_nScoreIndex, amount, round);

      if(st0_index > 0){
        for (j = 0; j < st0_length - 1; ++j) {
          wt1.load(find_or_replace_word_cache(st0_start_index + j, st0_start_index + j), st0_tag);
          wt2.load(st0_echar); //
          if (amount == 0) {
            wt12.refer(&wt1, &wt2);
          } else {
            wt12.allocate(wt1, wt2);
          }
          score += curweights->m_mapTaggedCharByLastChar.getOrUpdateScore(wt12, m_nScoreIndex, amount, round);
        }
      }
    }

    // all about the current word
    score += curweights->m_mapLastTagByTag.getOrUpdateScore(n0_tag_st0_tag, m_nScoreIndex, amount, round);
    score += curweights->m_mapTag0Tag1Size1.getOrUpdateScore(std::make_pair(n0_tag_st0_tag, st0_nlength), m_nScoreIndex, amount, round);
    score += curweights->m_mapTag1Tag2Size1.getOrUpdateScore(std::make_pair(st0_tag_st1_tag, st0_nlength), m_nScoreIndex, amount, round);
    score += curweights->m_mapTag0Tag1Tag2Size1.getOrUpdateScore(std::make_pair(n0_tag_st0_tag_st1_tag, st0_nlength), m_nScoreIndex, amount, round);

    if (st0_length <= 2)
      score += curweights->m_mapTagByLastWord.getOrUpdateScore(std::make_pair(st0_word, n0_tag), m_nScoreIndex, amount, round);

    score += curweights->m_mapLastTwoTagsByTag.getOrUpdateScore(n0_tag_st0_tag_st1_tag, m_nScoreIndex, amount, round);

    score += curweights->m_mapSeparateChars.getOrUpdateScore(two_char, m_nScoreIndex, amount, round);

    score += curweights->m_mapLastWordFirstChar.getOrUpdateScore(st1_word_st0_schar, m_nScoreIndex, amount, round);

    score += curweights->m_mapFirstCharLastWordByWord.getOrUpdateScore(st0_schar_st1_schar, m_nScoreIndex, amount, round);

    if (st0_length <= 2)
      score += curweights->m_mapTagByWordAndNextChar.getOrUpdateScore(std::make_pair(st1_word_st0_schar, st0_tag), m_nScoreIndex, amount, round);

    //score += m_weights->m_mapSepCharAndNextChar.getOrUpdateScore( find_or_replace_word_cache(start_0, start_0==sentence->size()-1?start_0:start_0+1) , m_nScoreIndex , amount , round ) ;

    score += curweights->m_mapTagByFirstChar.getOrUpdateScore(std::make_pair(st0_schar, n0_tag), m_nScoreIndex, amount, round);
    score += curweights->m_mapTagByFirstCharCat.getOrUpdateScore(std::make_pair(n0_charcat, n0_tag), m_nScoreIndex, amount, round);

    score += curweights->m_mapFirstCharBy2Tags.getOrUpdateScore(std::make_pair(st0_schar, n0_tag_st0_tag), m_nScoreIndex, amount, round);

    score += curweights->m_mapFirstCharBy3Tags.getOrUpdateScore(std::make_pair(st0_schar, n0_tag_st0_tag_st1_tag), m_nScoreIndex, amount, round);

    score += curweights->m_mapTagByChar.getOrUpdateScore(std::make_pair(st0_schar, n0_tag), m_nScoreIndex, amount, round);

    wt1.load(st0_echar, st0_tag);
    wt2.load(st0_schar, n0_tag);
    if (amount == 0) {
      wt12.refer(&wt1, &wt2);
    } else {
      wt12.allocate(wt1, wt2);
    }
    score += curweights->m_mapTaggedSeparateChars.getOrUpdateScore(wt12, m_nScoreIndex, amount, round);

    score += curweights->m_mapTagWordTag.getOrUpdateScore(std::make_pair(st0_word, n0_tag_st1_tag), m_nScoreIndex, amount, round);
    score += curweights->m_mapWordTagTag.getOrUpdateScore(std::make_pair(st1_word, n0_tag_st0_tag), m_nScoreIndex, amount, round);

  }

  if (action == action::NO_ACTION || action == action::SHIFT_IN) {

    score += curweights->m_mapTagByChar.getOrUpdateScore(std::make_pair(n0_char, st0_tag), m_nScoreIndex, amount, round);

    wt1.load(n0_char, st0_tag);
    wt2.load(st0_schar);
    if (amount == 0) {
      wt12.refer(&wt1, &wt2);
    } else {
      wt12.allocate(wt1, wt2);
    }
    score += curweights->m_mapTaggedCharByFirstChar.getOrUpdateScore(wt12, m_nScoreIndex, amount, round);
    score += curweights->m_mapConsecutiveChars.getOrUpdateScore(two_char, m_nScoreIndex, amount, round);
    score += curweights->m_mapTaggedConsecutiveChars.getOrUpdateScore(std::make_pair(two_char, st0_tag), m_nScoreIndex, amount, round);
  }


//default features

  //S0
  if (st0_index != -1) {
    score += curweights->m_mapST0wAction.getOrUpdateScore(std::make_pair(st0_word, action), m_nScoreIndex, amount, round);
    score += curweights->m_mapST0tAction.getOrUpdateScore(std::make_pair(st0_tag, action), m_nScoreIndex, amount, round);
    refer_or_allocate_tuple2(word_tag, &st0_word, &st0_tag);
    score += curweights->m_mapST0wtAction.getOrUpdateScore(std::make_pair(word_tag, action), m_nScoreIndex, amount, round);
  }

  //S1
  if (st1_index != -1) {
    score += curweights->m_mapST1wAction.getOrUpdateScore(std::make_pair(st1_word, action), m_nScoreIndex, amount, round);
    score += curweights->m_mapST1tAction.getOrUpdateScore(std::make_pair(st1_tag, action), m_nScoreIndex, amount, round);
    refer_or_allocate_tuple2(word_tag, &st1_word, &st1_tag);
    score += curweights->m_mapST1wtAction.getOrUpdateScore(std::make_pair(word_tag, action), m_nScoreIndex, amount, round);
  }

  //N0
  if (n0_index != -1) {
      score += curweights->m_mapST1wAction.getOrUpdateScore(std::make_pair(n0_char, action), m_nScoreIndex, amount, round);
  }


  //S0S1
  if (st1_index != -1) {
      refer_or_allocate_tuple2(word_word, &st0_word, &st1_word);
      score += curweights->m_mapST0wST1wAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(tag_tag, &st0_tag, &st1_tag);
      score += curweights->m_mapST0tST1tAction.getOrUpdateScore(std::make_pair(tag_tag, action), m_nScoreIndex, amount, round ) ;
      refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st0_tag, &st1_tag);
      score += curweights->m_mapST0wtST1tAction.getOrUpdateScore(std::make_pair(word_tag_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_tag_tag, &st1_word, &st0_tag, &st1_tag);
      score += curweights->m_mapST0tST1wtAction.getOrUpdateScore(std::make_pair(word_tag_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st0_tag);
      score += curweights->m_mapST0wtST1wAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st1_tag);
      score += curweights->m_mapST0wST1wtAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
  }

  //S0N0
  if (st0_index != -1 && n0_index != -1) {
      refer_or_allocate_tuple2(word_word, &st0_word, &n0_char);
      score += curweights->m_mapST0wN0cAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_word, &n0_char, &st0_tag);
      score += curweights->m_mapST0wtN0cAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
  }


  //S0S1N0
  if (st1_index != -1 && n0_index != -1) {
      refer_or_allocate_tuple3(word_tag_tag, &n0_char, &st0_tag, &st1_tag);
      score += curweights->m_mapST0tST1tN0cAction.getOrUpdateScore(std::make_pair(word_tag_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &n0_char, &st1_word, &st0_tag);
      score += curweights->m_mapST0tST1wN0cAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &n0_char, &st0_word, &st1_tag);
      score += curweights->m_mapST0wST1tN0cAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
  }


  //S0
  if (st0_index != -1) {
      score += curweights->m_mapST0cAction.getOrUpdateScore(std::make_pair(st0_char, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(word_tag, &st0_char, &st0_tag);
      score += curweights->m_mapST0ctAction.getOrUpdateScore(std::make_pair(word_tag, action), m_nScoreIndex, amount, round) ;
  }

  //S1
  if (st1_index != -1) {
    score += curweights->m_mapST1cAction.getOrUpdateScore(std::make_pair(st1_char, action), m_nScoreIndex, amount, round) ;
    refer_or_allocate_tuple2(word_tag, &st1_char, &st1_tag);
    score += curweights->m_mapST1ctAction.getOrUpdateScore(std::make_pair(word_tag, action), m_nScoreIndex, amount, round) ;
  }


  //S0S1
  if (st1_index != -1) {
      refer_or_allocate_tuple2(word_word, &st0_char, &st1_char);
      score += curweights->m_mapST0cST1cAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(word_word, &st0_word, &st1_char);
      score += curweights->m_mapST0wST1cAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple2(word_word, &st0_char, &st1_word);
      score += curweights->m_mapST0cST1wAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_char, &st0_tag);
      score += curweights->m_mapST0wtST1cAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_char, &st1_word, &st1_tag);
      score += curweights->m_mapST0cST1wtAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_char, &st1_tag);
      score += curweights->m_mapST0wST1ctAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
      refer_or_allocate_tuple3(word_word_tag, &st0_char, &st1_word, &st0_tag);
      score += curweights->m_mapST0ctST1wAction.getOrUpdateScore(std::make_pair(word_word_tag, action), m_nScoreIndex, amount, round) ;
  }


  //S0N0
  if (st0_index != -1 && n0_index != -1) {
      refer_or_allocate_tuple2(word_word, &st0_char, &n0_char);
      score += curweights->m_mapST0cN0cAction.getOrUpdateScore(std::make_pair(word_word, action), m_nScoreIndex, amount, round) ;
  }

  //S0S1N0
  if (st1_index != -1 && n0_index != -1) {
      refer_or_allocate_tuple3(word_word_word, &st1_char, &st0_char, &n0_char);
      score += curweights->m_mapST1cST0cN0cAction.getOrUpdateScore(std::make_pair(word_word_word, action), m_nScoreIndex, amount, round) ;
  }

  //S0S1S2
  if(st2_index != -1) {
      refer_or_allocate_tuple3(word_word_word, &st2_char, &st1_char, &st0_char);
      score += curweights->m_mapST2cST1cST0cAction.getOrUpdateScore(std::make_pair(word_word_word, action), m_nScoreIndex, amount, round) ;
  }

  int lastAction = item->m_nActionSize > 0 ? item->m_Action[item->m_nActionSize - 1] : 0;
  int last2Action = item->m_nActionSize > 1 ? item->m_Action[item->m_nActionSize - 2] : 0;
  score += curweights->m_mapBiAction.getOrUpdateScore(std::make_pair(lastAction, action), m_nScoreIndex, amount, round) ;
  score += curweights->m_mapTriAction.getOrUpdateScore(std::make_pair(last2Action*1000+lastAction, action), m_nScoreIndex, amount, round) ;

  return score;
}

/*---------------------------------------------------------------
 *
 * getGlobalScore - get the score of a parse tree
 *
 * Inputs: parse graph
 *
 *---------------------------------------------------------------*/

SCORE_TYPE CCharTagger::getGlobalScore(const CDependencyParse &parsed) {
  THROW("poschartagger.cpp: getGlobalScore unsupported");
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

void CCharTagger::updateScores(const CDependencyParse & parsed, const CDependencyParse & correct, int round) {
  THROW("chartagger.cpp: updateScores unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/
bool CCharTagger::updateScoresForStates(const CStateItem *predicated_state, const CStateItem *correct_state, SCORE_TYPE amount_add,
    SCORE_TYPE amount_subtract) {

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
    ++num_predicated_states;
  }

  for (const CStateItem * p = correct_state; p; p = p->m_preState) {
    correct_state_chain[num_correct_states] = p;
    ++num_correct_states;
  }

  ASSERT(num_correct_states == num_predicated_states, "Number of predicated action don't equals the correct one");

  int i;
  for (i = num_correct_states - 1; i >= 0; --i) {
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

  for (i = i + 1; i > 0; --i) {
    unsigned predicated_action = predicated_state_chain[i - 1]->m_nLastAction;
    unsigned correct_action = correct_state_chain[i - 1]->m_nLastAction;
    getOrUpdateStackScore(predicated_state_chain[i], predicated_action, amount_subtract, m_nTrainingRound);
    getOrUpdateStackScore(correct_state_chain[i], correct_action, amount_add, m_nTrainingRound);

  }

  {
    cast_weights->addCurrent(m_delta_weight, m_nTrainingRound);
  }

  m_nTotalErrors++;
  return true;
}

/*---------------------------------------------------------------
 *
 * arcleft - helping function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::arcleft(const CStateItem *item) {
  if (!item->canarcin())
    return;
  static action::CScoredAction scoredaction;
  // update stack score
  scoredaction.action = action::ARC_LEFT;
  SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
  scoredaction.score = item->score + score;
  m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * arcright - helping function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::arcright(const CStateItem *item) {
  if (!item->canarcin())
    return;
  static action::CScoredAction scoredaction;
  // update stack score
  scoredaction.action = action::ARC_RIGHT;
  SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
  scoredaction.score = item->score + score;
  m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * shift - help function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::shift(const CStateItem *item) {
  if (!item->canshift())
    return;
  static action::CScoredAction scoredaction;
  // update stack score
  static unsigned label;

  for (label = CTag::FIRST; label < CTag::COUNT; ++label) {
    scoredaction.action = action::encodeAction(action::SHIFT, label);
    SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
    scoredaction.score = item->score + score;
    m_Beam->insertItem(&scoredaction);
  }

}

/*---------------------------------------------------------------
 *
 * poproot - help function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::finish(const CStateItem *item) {
  if (!item->canfinish())
    return;
  static action::CScoredAction scoredaction;
  scoredaction.action = action::FINISH;
  SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
  scoredaction.score = item->score + score;
  m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * popword - help function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::idle(const CStateItem *item) {
  if (!item->IsTerminated())
    return;
  static action::CScoredAction scoredaction;
  scoredaction.action = action::IDLE;
  SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
  scoredaction.score = item->score + score;
  m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * shiftin - help function
 *
 *--------------------------------------------------------------*/

inline void CCharTagger::shiftin(const CStateItem *item) {
  if (!item->canshiftin())
    return;
  static action::CScoredAction scoredaction;
  scoredaction.action = action::SHIFT_IN;
  SCORE_TYPE score = getOrUpdateStackScore(item, scoredaction.action);
  scoredaction.score = item->score + score;
  m_Beam->insertItem(&scoredaction);
}

bool StateHeapMore(const CStateItem * x, const CStateItem * y) {
  return x->score > y->score;
}

int CCharTagger::insertIntoBeam(CStateItem ** beam_wrapper, const CStateItem * item, const int current_beam_size, const int max_beam_size) {
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

CStateItem * CCharTagger::getLattice(int max_lattice_size) {
  if (0 == lattice_) {
    max_lattice_size_ = max_lattice_size;
    lattice_ = new CStateItem[max_lattice_size];
  } else if (max_lattice_size_ < max_lattice_size) {
    delete[] lattice_;
    max_lattice_size_ = max_lattice_size;
    lattice_ = new CStateItem[max_lattice_size];
  }

  for (int i = 0; i < max_lattice_size; ++i) {
    lattice_[i].clear();
  }
  return lattice_;
}



/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CDependencyParse 
 *
 *--------------------------------------------------------------*/

void CCharTagger::work(const bool bTrain, const CStringVector &sentence, CDependencyParse *retval, const CDependencyParse &correct, int nBest,
    SCORE_TYPE *scores) {

#ifdef DEBUG
  clock_t total_start_time = clock();
#endif
  static int index;
  static unsigned long correction_action;
  const int length = sentence.size();

  const int max_round = length * 3 + 1;
  const int max_lattice_size = (AGENDA_SIZE + 1) * max_round;

  CStateItem * lattice = getLattice(max_lattice_size);
  CStateItem * lattice_wrapper[max_lattice_size];
  CStateItem ** lattice_index[max_round];
  CStateItem * correct_state = lattice;
  static CStateItem * best_generator;

  for (int i = 0; i < max_lattice_size; ++i) {
    lattice_wrapper[i] = lattice + i;
    lattice[i].m_nSentLen = length;
  }

  lattice[0].clear();
  correct_state = lattice;
  lattice_index[0] = lattice_wrapper;
  lattice_index[1] = lattice_index[0] + 1;

  ASSERT(length < MAX_SENTENCE_SIZE, "The size of the sentence is larger than the system configuration.");

  TRACE("Initialising the decoding process...");

  TRACE("Decoding started");
  int num_results = 0;
  int round = 0;
  bool is_correct; // used for training to specify correct state in lattice

  // loop with the next word to process in the sentence,
  // `round` represent the generators, and the condidates should be inserted
  // into the `round + 1`
  for (round = 1; round < max_round; ++round) {
    if (lattice_index[round - 1] == lattice_index[round]) {
      // there is nothing in generators, the proning has cut all legel
      // generator. actually, in this kind of case, we should raise a
      // exception. however to achieve a parsing tree, an alternative
      // solution is go back to the previous round
      WARNING("Parsing Failed!");
      --round;
      break;
    }
    // iterate generators
    int current_beam_size = 0;

    // loop over the generator states
    // std::cout << "round : " << round << std::endl;
    for (CStateItem ** q = lattice_index[round - 1]; q != lattice_index[round]; ++q) {

      const CStateItem * pGenerator = (*q);
      // for the state items that already contain all words
      m_Beam->clear();

      arcleft(pGenerator);
      arcright(pGenerator);
      shift(pGenerator);
      shiftin(pGenerator);
      finish(pGenerator);
      idle(pGenerator);

      // insert item
      for (unsigned i = 0; i < m_Beam->size(); ++i) {
        CStateItem candidate;
        candidate = (*pGenerator);
        // generate candidate state according to the states in beam
        candidate.Move(m_Beam->item(i)->action);
        candidate.score = m_Beam->item(i)->score;
        candidate.m_preState = pGenerator;
        current_beam_size += insertIntoBeam(lattice_index[round], &candidate, current_beam_size,
        AGENDA_SIZE);
      }
    }

    lattice_index[round + 1] = lattice_index[round] + current_beam_size;

    best_generator = (*lattice_index[round]);
    int debug = 0;
    for (CStateItem ** q = lattice_index[round]; q != lattice_index[round + 1]; ++q) {
      CStateItem * p = (*q);
      if (best_generator->score < p->score) {
        best_generator = p;
      }
      debug++;
    }

    if (best_generator->IsTerminated()) {
      if(best_generator->m_nNextWord < length){
        std::cout << "error decoding" << std::endl;
      }
      break;
    }

    if (bTrain) {
      CStateItem next_correct_state(*correct_state);
      next_correct_state.StandardMoveStep(correct);
      next_correct_state.m_preState = correct_state;
      is_correct = false;

      for (CStateItem ** q = lattice_index[round]; q != lattice_index[round + 1]; ++q) {
        CStateItem * p = *q;
        if (next_correct_state.m_nLastAction == p->m_nLastAction && p->m_preState == correct_state) {
          correct_state = p;
          is_correct = true;
        }
      }

      if (!is_correct) {
        TRACE("ERROR at the " << next_correct_state.m_nActionSize << "th word;"
            << " Total is " << correct.size());

        updateScoresForStates(best_generator, &next_correct_state, 1, -1);
        return;
      }
    }
  }

  if (bTrain) {
    CStateItem next_correct_state(*correct_state);
    next_correct_state.StandardMoveStep(correct);
    next_correct_state.m_preState = correct_state;

    if (best_generator->m_preState != correct_state || best_generator->m_nLastAction != next_correct_state.m_nLastAction) {
      updateScoresForStates(best_generator, &next_correct_state, 1, -1);
    }
    else{
      TRACE("Corrected");
    }
    return;
  }

  TRACE("Output sentence");
  //std::sort(lattice_index[round - 1], lattice_index[round], StateHeapMore);
  //num_results = lattice_index[round] - lattice_index[round - 1];

  // current not support for n-best
  /*
  for (int i = 0; i < std::min(num_results, nBest); ++i) {
    (*(lattice_index[round - 1] + i))->GenerateTree(sentence, retval[i]);
    if (scores) {
      scores[i] = (*(lattice_index[round - 1] + i))->score;
    }
  }*/
  best_generator->GenerateTree(sentence, retval[0]);
  if (scores) {
    scores[0] = best_generator->score;
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

void CCharTagger::parse(const CStringVector &sentence, CDependencyParse *retval, int nBest, SCORE_TYPE *scores) {

  static CDependencyParse empty;

  for (int i = 0; i < nBest; ++i) {
    // clear the outout sentences
    retval[i].clear();
    if (scores)
      scores[i] = 0;    //pGenerator->score;
  }
  m_Sentence.clear();
  for (int idx = 0; idx < sentence.size(); idx++) {
    m_Sentence.push_back(sentence[idx]);
  }
  m_nSentSize = m_Sentence.size();
  m_lCache.clear();

  work(false, sentence, retval, empty, nBest, scores);

}

/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CCharTagger::train(const CDependencyParse &correct, int round) {

  static CStringVector sentence;
  static CDependencyParse outout;
  static CTwoStringVector wordtags;
  static CTuple2<CWord, CWord> word_word;

#ifndef FRAGMENTED_TREE

  assert(IsProjectiveDependencyTree(correct));
#endif

  UnparseDeSegmentedSentenceCharConll(&correct, &m_Sentence);
  m_nSentSize = m_Sentence.size();
  UnparseSentenceCharConll(&correct, &sentence);
  UnparseSentenceCharConll(&correct, &wordtags);

  static CStateItem item;
  item.setsentsize(m_nSentSize);

  unsigned action;

  m_lCache.clear();
  item.clear();
  for (int i = 0; i < m_nSentSize * 2; ++i) {
    item.StandardMoveStep(correct);
    if (item.IsTerminated()) {
      break;
    }
  }

  int wordcount = 0;
  for (int idx = 0; idx < m_nSentSize; idx++) {
    int start_word = item.wordstart(idx);
    int end_word = item.wordend(idx);
    CTag curTag = CTag(item.m_nPOSs[idx]);
    int tag = curTag.code();
    CWord curChar;
    curChar.load(m_lCache.replace(idx, idx, &m_Sentence));

    cast_weights->m_mapCharFrequency[curChar]++;
    cast_weights->m_mapCharTagDictionary.add(curChar, curTag);
    if (cast_weights->m_mapCharFrequency[curChar] > cast_weights->m_nMaxCharFrequency)
    cast_weights->m_nMaxCharFrequency = cast_weights->m_mapCharFrequency[curChar];

    if (item.m_bLabelTypes[idx]) {
      wordcount++;
      CWord curWord;
      curWord.load(m_lCache.replace(start_word, end_word, &m_Sentence));
      cast_weights->m_mapWordFrequency[curWord]++;
      cast_weights->m_mapWordTagDictionary.add(curWord, curTag);
      if (cast_weights->m_mapWordFrequency[curWord] > cast_weights->m_nMaxWordFrequency){
        cast_weights->m_nMaxWordFrequency = cast_weights->m_mapWordFrequency[curWord];
      }
      cast_weights->setMaxLengthByTag(tag, end_word-start_word+1);
    } else{
      CWord curSubWord;
      start_word = item.wordstart(idx);
      end_word = item.wordend(idx);

      curSubWord.load(m_lCache.replace(start_word, end_word, &m_Sentence));
      cast_weights->m_mapSubWordFrequency[curSubWord]++;
      cast_weights->m_mapSubWordTagDictionary.add(curSubWord, curTag);

      if (cast_weights->m_mapSubWordFrequency[curSubWord] > cast_weights->m_nMaxSubWordFrequency)
      cast_weights->m_nMaxSubWordFrequency = cast_weights->m_mapSubWordFrequency[curSubWord];

      if(start_word != end_word)
      {
        word_word.allocate(&curSubWord, &curChar);
        cast_weights->m_mapSubWordHeadWordDictionary[word_word]++;
      }
    }

    if(item.m_bPOSTypes[idx]){
      if (PENN_TAG_CLOSED[tag] || tag == PENN_TAG_CD) {
        cast_weights->m_mapCanStart.add(curChar, tag);
      }
    }

  }

  // The following code does update for each processing stage
  ++m_nTrainingRound;
  ASSERT(m_nTrainingRound == round, "Training round error");

  work(true, m_Sentence, &outout, correct, 1, 0);

}

