// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the dependency parser weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _CHARTAGGER_WEIGHTS_H
#define _CHARTAGGER_WEIGHTS_H

#include "chartagger_weight_base.h"

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,
#define ID_POINTER ->

#define iterate_templates(left,right) \
   left(m_mapCharUnigram)right \
   left(m_mapCharBigram)right \
   left(m_mapCharTrigram)right \
   left(m_mapSeenWords)right \
   left(m_mapLastWordByWord)right \
   left(m_mapCurrentWordLastChar)right \
   left(m_mapLastWordFirstChar)right \
   left(m_mapFirstCharLastWordByWord)right \
   left(m_mapLastWordByLastChar)right \
   left(m_mapSeparateChars)right \
   left(m_mapConsecutiveChars)right \
   left(m_mapFirstAndLastChars)right \
   left(m_mapOneCharWord)right \
   left(m_mapLengthByFirstChar)right \
   left(m_mapLengthByLastChar)right \
   left(m_mapLengthByLastWord)right \
   left(m_mapLastLengthByWord)right \
   left(m_mapLastTagByTag)right \
   left(m_mapLastTwoTagsByTag)right \
   left(m_mapCurrentTag)right \
   left(m_mapTagByLastWord)right \
   left(m_mapLastTagByWord)right \
   left(m_mapTagByFirstChar)right \
   left(m_mapTagByLastChar)right \
   left(m_mapTagByChar)right \
   left(m_mapTagOfOneCharWord)right \
   left(m_mapRepeatedCharByTag)right \
   left(m_mapTagByWordAndPrevChar)right \
   left(m_mapTagByWordAndNextChar)right \
   left(m_mapTaggedCharByFirstChar)right \
   left(m_mapTaggedCharByLastChar)right \
   left(m_mapTagByFirstCharCat)right \
   left(m_mapTagByLastCharCat)right \
   left(m_mapTaggedSeparateChars)right \
   left(m_mapTaggedConsecutiveChars)right\
   left(m_mapWordTagTag)right\
   left(m_mapTagWordTag)right\
   left(m_mapFirstCharBy2Tags)right\
   left(m_mapFirstCharBy3Tags)right\
   left(m_mapFirstCharAndChar)right\
   left(m_mapSepCharAndNextChar)right\
   left(m_mapAppCharAndNextChar)right\
   left(m_mapPartialWord)right\
   left(m_mapPartialLengthByFirstChar)right \
   left(m_mapLengthByTagAndFirstChar)right \
   left(m_mapLengthByTagAndLastChar)right \
   left(m_mapTag0Tag1Size1)right\
   left(m_mapTag1Tag2Size1)right\
   left(m_mapTag0Tag1Tag2Size1)right\
\
   left(m_mapST0wAction)right\
   left(m_mapST0tAction)right\
   left(m_mapST0wtAction)right\
   left(m_mapST1wAction)right\
   left(m_mapST1tAction)right\
   left(m_mapST1wtAction)right\
   left(m_mapST0wST1wAction)right\
   left(m_mapST0tST1tAction)right\
   left(m_mapST0wtST1tAction)right\
   left(m_mapST0tST1wtAction)right\
   left(m_mapST0wtST1wAction)right\
   left(m_mapST0wST1wtAction)right\
   left(m_mapST0wN0cAction)right\
   left(m_mapST0wtN0cAction)right\
   left(m_mapST0tST1tN0cAction)right\
   left(m_mapST0tST1wN0cAction)right\
   left(m_mapST0wST1tN0cAction)right\
   left(m_mapST0cAction)right\
   left(m_mapST0ctAction)right\
   left(m_mapST1cAction)right\
   left(m_mapST1ctAction)right\
   left(m_mapST0cST1cAction)right\
   left(m_mapST0wST1cAction)right\
   left(m_mapST0cST1wAction)right\
   left(m_mapST0wtST1cAction)right\
   left(m_mapST0cST1wtAction)right\
   left(m_mapST0wST1ctAction)right\
   left(m_mapST0ctST1wAction)right\
   left(m_mapST0cN0cAction)right\
   left(m_mapST1cST0cN0cAction)right\
   left(m_mapST2cST1cST0cAction)right\
   left(m_mapBiAction)right\
   left(m_mapTriAction)right


#define iterate_double_templates(left,middle,right) \
   left m_mapCharUnigram middle m_mapCharUnigram right \
   left m_mapCharBigram middle m_mapCharBigram right \
   left m_mapCharTrigram middle m_mapCharTrigram right \
   left m_mapSeenWords middle m_mapSeenWords right \
   left m_mapLastWordByWord middle m_mapLastWordByWord right \
   left m_mapCurrentWordLastChar middle m_mapCurrentWordLastChar right \
   left m_mapLastWordFirstChar middle m_mapLastWordFirstChar right \
   left m_mapFirstCharLastWordByWord middle m_mapFirstCharLastWordByWord right \
   left m_mapLastWordByLastChar middle m_mapLastWordByLastChar right \
   left m_mapSeparateChars middle m_mapSeparateChars right \
   left m_mapConsecutiveChars middle m_mapConsecutiveChars right \
   left m_mapFirstAndLastChars middle m_mapFirstAndLastChars right \
   left m_mapOneCharWord middle m_mapOneCharWord right \
   left m_mapLengthByFirstChar middle m_mapLengthByFirstChar right \
   left m_mapLengthByLastChar middle m_mapLengthByLastChar right \
   left m_mapLengthByLastWord middle m_mapLengthByLastWord right \
   left m_mapLastLengthByWord middle m_mapLastLengthByWord right \
   left m_mapLastTagByTag middle m_mapLastTagByTag right \
   left m_mapLastTwoTagsByTag middle m_mapLastTwoTagsByTag right \
   left m_mapCurrentTag middle m_mapCurrentTag right \
   left m_mapTagByLastWord middle m_mapTagByLastWord right \
   left m_mapLastTagByWord middle m_mapLastTagByWord right \
   left m_mapTagByFirstChar middle m_mapTagByFirstChar right \
   left m_mapTagByLastChar middle m_mapTagByLastChar right \
   left m_mapTagByChar middle m_mapTagByChar right \
   left m_mapTagOfOneCharWord middle m_mapTagOfOneCharWord right \
   left m_mapRepeatedCharByTag middle m_mapRepeatedCharByTag right \
   left m_mapTagByWordAndPrevChar middle m_mapTagByWordAndPrevChar right \
   left m_mapTagByWordAndNextChar middle m_mapTagByWordAndNextChar right \
   left m_mapTaggedCharByFirstChar middle m_mapTaggedCharByFirstChar right \
   left m_mapTaggedCharByLastChar middle m_mapTaggedCharByLastChar right \
   left m_mapTagByFirstCharCat middle m_mapTagByFirstCharCat right \
   left m_mapTagByLastCharCat middle m_mapTagByLastCharCat right \
   left m_mapTaggedSeparateChars middle m_mapTaggedSeparateChars right \
   left m_mapTaggedConsecutiveChars middle m_mapTaggedConsecutiveChars right \
   left m_mapWordTagTag middle m_mapWordTagTag right \
   left m_mapTagWordTag middle m_mapTagWordTag right \
   left m_mapFirstCharBy2Tags middle m_mapFirstCharBy2Tags right \
   left m_mapFirstCharBy3Tags middle m_mapFirstCharBy3Tags right \
   left m_mapFirstCharAndChar middle m_mapFirstCharAndChar right \
   left m_mapSepCharAndNextChar middle m_mapSepCharAndNextChar right \
   left m_mapAppCharAndNextChar middle m_mapAppCharAndNextChar right \
   left m_mapPartialWord middle m_mapPartialWord right \
   left m_mapPartialLengthByFirstChar middle m_mapPartialLengthByFirstChar right \
   left m_mapLengthByTagAndFirstChar middle m_mapLengthByTagAndFirstChar right \
   left m_mapLengthByTagAndLastChar middle m_mapLengthByTagAndLastChar right \
   left m_mapTag0Tag1Size1 middle m_mapTag0Tag1Size1 right \
   left m_mapTag1Tag2Size1 middle m_mapTag1Tag2Size1 right \
   left m_mapTag0Tag1Tag2Size1 middle m_mapTag0Tag1Tag2Size1 right\
\
   left m_mapST0wAction middle m_mapST0wAction right \
   left m_mapST0tAction middle m_mapST0tAction right \
   left m_mapST0wtAction middle m_mapST0wtAction right \
   left m_mapST1wAction middle m_mapST1wAction right \
   left m_mapST1tAction middle m_mapST1tAction right \
   left m_mapST1wtAction middle m_mapST1wtAction right \
   left m_mapST0wST1wAction middle m_mapST0wST1wAction right \
   left m_mapST0tST1tAction middle m_mapST0tST1tAction right \
   left m_mapST0wtST1tAction middle m_mapST0wtST1tAction right \
   left m_mapST0tST1wtAction middle m_mapST0tST1wtAction right \
   left m_mapST0wtST1wAction middle m_mapST0wtST1wAction right \
   left m_mapST0wST1wtAction middle m_mapST0wST1wtAction right \
   left m_mapST0wN0cAction middle m_mapST0wN0cAction right \
   left m_mapST0wtN0cAction middle m_mapST0wtN0cAction right \
   left m_mapST0tST1tN0cAction middle m_mapST0tST1tN0cAction right \
   left m_mapST0tST1wN0cAction middle m_mapST0tST1wN0cAction right \
   left m_mapST0wST1tN0cAction middle m_mapST0wST1tN0cAction right \
   left m_mapST0cAction middle m_mapST0cAction right \
   left m_mapST0ctAction middle m_mapST0ctAction right \
   left m_mapST1cAction middle m_mapST1cAction right \
   left m_mapST1ctAction middle m_mapST1ctAction right \
   left m_mapST0cST1cAction middle m_mapST0cST1cAction right \
   left m_mapST0wST1cAction middle m_mapST0wST1cAction right \
   left m_mapST0cST1wAction middle m_mapST0cST1wAction right \
   left m_mapST0wtST1cAction middle m_mapST0wtST1cAction right \
   left m_mapST0cST1wtAction middle m_mapST0cST1wtAction right \
   left m_mapST0wST1ctAction middle m_mapST0wST1ctAction right \
   left m_mapST0ctST1wAction middle m_mapST0ctST1wAction right \
   left m_mapST0cN0cAction middle m_mapST0cN0cAction right \
   left m_mapST1cST0cN0cAction middle m_mapST1cST0cN0cAction right \
   left m_mapST2cST1cST0cAction middle m_mapST2cST1cST0cAction right \
   left m_mapBiAction middle m_mapBiAction right \
   left m_mapTriAction middle m_mapTriAction right


namespace TARGET_LANGUAGE {

namespace chartagger {

//
// TYPE DEFINITIONS
//
typedef CScoreMap< CWord, SCORE_TYPE > CWordMap;
typedef CScoreMap< CTwoWords, SCORE_TYPE > CTwoWordsMap;
typedef CScoreMap< std::pair<CWord, int>, SCORE_TYPE > CWordIntMap;
typedef CScoreMap< std::pair<CWord, CTag>, SCORE_TYPE > CWordTagMap;
//typedef CScoreMap< long int, SCORE_TYPE > CIntMap;
typedef CScoreMap< CTwoTaggedWords, SCORE_TYPE > CTwoTaggedWordsMap;
typedef CScoreMap< std::pair<unsigned long long, CTag>, SCORE_TYPE > CIntTagMap;
typedef CScoreMap< CTagSet<CTag, 2>, SCORE_TYPE > CTagSet2Map;
typedef CScoreMap< CTagSet<CTag, 3>, SCORE_TYPE > CTagSet3Map;
typedef CScoreMap< std::pair<CWord, CTagSet<CTag, 2> >, SCORE_TYPE > CWordTagSet2Map;
typedef CScoreMap< std::pair<CWord, CTagSet<CTag, 3> >, SCORE_TYPE > CWordTagSet3Map;

typedef CScoreMap< std::pair<int, int>, SCORE_TYPE> CIntACMap;
typedef CScoreMap< std::pair<CWord, int>, SCORE_TYPE> CWordACMap;
typedef CScoreMap< std::pair<CTag, int>, SCORE_TYPE> CTagACMap;

typedef CScoreMap< std::pair<CTuple2<CWord, CTag>, int>, SCORE_TYPE> CWordTagACMap;
typedef CScoreMap< std::pair<CTuple2<CWord, CWord>, int>, SCORE_TYPE> CWordWordACMap;
typedef CScoreMap< std::pair<CTuple2<CTag, CTag>, int>, SCORE_TYPE> CTagTagACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CTag, CTag>, int>, SCORE_TYPE> CWordTagTagACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CWord, CTag>, int>, SCORE_TYPE> CWordWordTagACMap;
typedef CScoreMap< std::pair<CTuple3<CTag, CTag, CTag>, int>, SCORE_TYPE> CTagTagTagACMap;
typedef CScoreMap< std::pair<CTuple3<CWord, CWord, CWord>, int>, SCORE_TYPE> CWordWordWordACMap;

typedef CHashMap< CWord, int > CWordToIntMap;
typedef CScoreMap< std::pair<CTagSet<CTag, 2>, int>, SCORE_TYPE > CTagSet2IntMap;
typedef CScoreMap< std::pair<CTagSet<CTag, 3>, int>, SCORE_TYPE > CTagSet3IntMap;
typedef CHashMap< CTuple2<CWord, CWord>, int > CWordWordToIntMap;
//typedef CScoreMap< std::pair<long int, long int>, SCORE_TYPE > CIntPairMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:
   unsigned long m_maxLengthByTag[CTag::COUNT+1];
   unsigned long m_nMaxWordFrequency;

   // statistical information
   unsigned long m_nMaxSubWordFrequency;
   unsigned long m_nMaxCharFrequency;
   CWordToIntMap m_mapCharFrequency;
   CWordToIntMap m_mapSubWordFrequency;

   CWordToIntMap m_mapWordFrequency;
   CTagDict<CWord, CTag> m_mapCanStart;
   CWordWordToIntMap m_mapSubWordHeadWordDictionary;
   CTagDict<CWord, CTag> m_mapWordTagDictionary;
   CTagDict<CWord, CTag> m_mapCharTagDictionary;
   CTagDict<CWord, CTag> m_mapSubWordTagDictionary;



public:
   unsigned long getMaxWordLength() const {return m_maxLengthByTag[CTag::COUNT];}
   void setMaxLengthByTag(unsigned long tag, unsigned long length) {
      if (length<=m_maxLengthByTag[tag])
         return;
      m_maxLengthByTag[tag]=length;
      if (length>m_maxLengthByTag[CTag::COUNT])
         m_maxLengthByTag[CTag::COUNT]=length;
   }

   // feature templates about characters
   CWordIntMap m_mapCharUnigram;
   CWordIntMap m_mapCharBigram;
   CWordIntMap m_mapCharTrigram;

   // feature templates about words
   CWordMap m_mapSeenWords;
   CTwoWordsMap m_mapLastWordByWord;
   CWordMap m_mapCurrentWordLastChar;
   CWordMap m_mapLastWordFirstChar;
   CTwoWordsMap m_mapFirstCharLastWordByWord;
   CTwoWordsMap m_mapLastWordByLastChar;
   CWordMap m_mapSeparateChars;
   CWordMap m_mapConsecutiveChars;
   CTwoWordsMap m_mapFirstAndLastChars;
   CWordMap m_mapOneCharWord;
   CWordIntMap m_mapLengthByFirstChar;
   CWordIntMap m_mapLengthByLastChar;
   CWordIntMap m_mapLengthByLastWord;
   CWordIntMap m_mapLastLengthByWord;

   // feature templates tag
   CWordTagMap m_mapCurrentTag;
   CTagSet2Map m_mapLastTagByTag;
   CTagSet3Map m_mapLastTwoTagsByTag;
   CWordTagMap m_mapTagByLastWord;
   CWordTagMap m_mapLastTagByWord;
   CWordTagMap m_mapTagByFirstChar;
   CWordTagMap m_mapTagByLastChar;
   CWordTagMap m_mapTagByChar;
   CWordTagMap m_mapTagOfOneCharWord;
   CWordTagMap m_mapRepeatedCharByTag;
   CWordTagMap m_mapTagByWordAndPrevChar;
   CWordTagMap m_mapTagByWordAndNextChar;
   CTwoTaggedWordsMap m_mapTaggedCharByFirstChar;
   CTwoTaggedWordsMap m_mapTaggedCharByLastChar;

   // extra features
   CTwoTaggedWordsMap m_mapTaggedSeparateChars;
   CWordTagMap m_mapTaggedConsecutiveChars;

   CWordTagSet2Map m_mapWordTagTag;
   CWordTagSet2Map m_mapTagWordTag;
   CWordTagSet2Map m_mapFirstCharBy2Tags;
   CWordTagSet3Map m_mapFirstCharBy3Tags;
   CTwoWordsMap m_mapFirstCharAndChar;

   CWordMap m_mapSepCharAndNextChar;
   CWordMap m_mapAppCharAndNextChar;

   CWordMap m_mapPartialWord;
   CWordIntMap m_mapPartialLengthByFirstChar;
   CWordIntMap m_mapLengthByTagAndFirstChar;
   CWordIntMap m_mapLengthByTagAndLastChar;

   CTagSet2IntMap m_mapTag0Tag1Size1;
   CTagSet2IntMap m_mapTag1Tag2Size1;
   CTagSet3IntMap m_mapTag0Tag1Tag2Size1;

   // feature templates knowledge
   CIntTagMap m_mapTagByFirstCharCat;
   CIntTagMap m_mapTagByLastCharCat;

   CIntTagMap m_mapSeparateCharCat;
   CIntTagMap m_mapConsecutiveCharCat;


   CWordACMap m_mapST0wAction;
   CTagACMap m_mapST0tAction;
   CWordTagACMap m_mapST0wtAction;
   CWordACMap m_mapST1wAction;
   CTagACMap m_mapST1tAction;
   CWordTagACMap m_mapST1wtAction;
   CWordWordACMap m_mapST0wST1wAction;
   CTagTagACMap m_mapST0tST1tAction;
   CWordTagTagACMap m_mapST0wtST1tAction;
   CWordTagTagACMap m_mapST0tST1wtAction;
   CWordWordTagACMap m_mapST0wtST1wAction;
   CWordWordTagACMap m_mapST0wST1wtAction;
   CWordWordACMap m_mapST0wN0cAction;
   CWordWordTagACMap m_mapST0wtN0cAction;
   CWordTagTagACMap m_mapST0tST1tN0cAction;
   CWordWordTagACMap m_mapST0tST1wN0cAction;
   CWordWordTagACMap m_mapST0wST1tN0cAction;
   CWordACMap m_mapST0cAction;
   CWordTagACMap m_mapST0ctAction;
   CWordACMap m_mapST1cAction;
   CWordTagACMap m_mapST1ctAction;
   CWordWordACMap m_mapST0cST1cAction;
   CWordWordACMap m_mapST0wST1cAction;
   CWordWordACMap m_mapST0cST1wAction;
   CWordWordTagACMap m_mapST0wtST1cAction;
   CWordWordTagACMap m_mapST0cST1wtAction;
   CWordWordTagACMap m_mapST0wST1ctAction;
   CWordWordTagACMap m_mapST0ctST1wAction;
   CWordWordACMap m_mapST0cN0cAction;
   CWordWordWordACMap m_mapST1cST0cN0cAction;
   CWordWordWordACMap m_mapST2cST1cST0cAction;
   CIntACMap m_mapBiAction;
   CIntACMap m_mapTriAction;



public:
   // note that m_bSegmentation rules will be covered by load()
   // if there is a model file to load
   // therefore this argument only used first time training
   CWeight(const std::string &sFeatureDB, bool bTrain, int hash_table_size) :
            CWeightBase(sFeatureDB, bTrain) ,
            m_nMaxWordFrequency(0) ,
            m_nMaxCharFrequency(0) ,
            m_nMaxSubWordFrequency(0) ,
            m_mapWordFrequency(hash_table_size),
            m_mapCharFrequency(hash_table_size),
            m_mapSubWordFrequency(hash_table_size),
            m_mapSubWordHeadWordDictionary(hash_table_size),
            m_mapWordTagDictionary(CTag::COUNT),
            m_mapCharTagDictionary(CTag::COUNT),
            m_mapSubWordTagDictionary(CTag::COUNT),
            m_mapCanStart(CTag::COUNT),

            m_mapCharUnigram("CharacterUnigram", hash_table_size) ,
            m_mapCharBigram("CharacterBigram", hash_table_size) ,
            m_mapCharTrigram("CharacterTrigram", hash_table_size) ,
            m_mapSeenWords("WordDictionary", hash_table_size) ,
            m_mapLastWordByWord("LastWordByWord", hash_table_size) ,
            m_mapCurrentWordLastChar("CurrentWordLastChar", hash_table_size) ,
            m_mapLastWordFirstChar("LastWordFirstChar", hash_table_size) ,
            m_mapFirstCharLastWordByWord("FirstCharLastWordByWord", hash_table_size) ,
            m_mapLastWordByLastChar("LastWordByLastChar", hash_table_size) ,
            m_mapSeparateChars("SeparateChars", hash_table_size) ,
            m_mapConsecutiveChars("ConsecutiveChars", hash_table_size) ,
            m_mapFirstAndLastChars("FirstAndLastChars", hash_table_size) ,
            m_mapOneCharWord("OneCharWord", hash_table_size) ,
            m_mapLengthByFirstChar("LengthByFirstChar", hash_table_size) ,
            m_mapLengthByLastChar("LengthByLastChar", hash_table_size) ,
            m_mapLengthByLastWord("LengthByLastWord", hash_table_size) ,
            m_mapLastLengthByWord("LastLengthByWord", hash_table_size) ,

            m_mapLastTagByTag("LastTagByTag", 1627) ,
            m_mapLastTwoTagsByTag("LastTwoTagsByTag", 16381) ,
            m_mapCurrentTag("CurrentTag", hash_table_size) ,
            m_mapTagByLastWord("TagByLastWord", hash_table_size) ,
            m_mapLastTagByWord("LastTagByWord", hash_table_size) ,
            m_mapTagByFirstChar("TagByFirstChar", hash_table_size) ,
            m_mapTagByLastChar("TagByLastChar", hash_table_size) ,
            m_mapTagByChar("TagByChar", hash_table_size) ,
            m_mapTagOfOneCharWord("TagOfOneCharWord", hash_table_size) ,
            m_mapRepeatedCharByTag("RepeatedCharByTag", hash_table_size) ,
            m_mapTagByWordAndPrevChar("TagByWordAndPrevChar", hash_table_size) ,
            m_mapTagByWordAndNextChar("TagByWordAndNextChar", hash_table_size) ,
            m_mapTaggedCharByFirstChar("TaggedCharByFirstChar", hash_table_size) ,
            m_mapTaggedCharByLastChar("TaggedCharByLastChar", hash_table_size) ,
            m_mapTagByFirstCharCat("TagByFirstCharCat", hash_table_size) ,
            m_mapTagByLastCharCat("TagByLastCharCat", hash_table_size) ,

            m_mapSeparateCharCat("SeparateCharCat", hash_table_size) ,
            m_mapConsecutiveCharCat("ConsecutiveCharCat", hash_table_size) ,

            m_mapTaggedSeparateChars("TaggedSeparateChars", hash_table_size) ,
            m_mapTaggedConsecutiveChars("TaggedConsecutiveChars", hash_table_size),

            m_mapWordTagTag("WordByTheNextTwoTag", hash_table_size),
            m_mapTagWordTag("TagByNextWordSecondNextTag", hash_table_size),
            m_mapFirstCharBy2Tags("FirstCharByTagAndLastTag", hash_table_size),
            m_mapFirstCharBy3Tags("FirstCharByTagLastTagAndSecondLastTag", hash_table_size),
            m_mapFirstCharAndChar("FirstCharAndChar", hash_table_size),
            m_mapSepCharAndNextChar("SeparatedCharAndNextChar", hash_table_size),
            m_mapAppCharAndNextChar("AppendedCharAndNextChar", hash_table_size),
            m_mapPartialWord("PartialWord", hash_table_size),
            m_mapPartialLengthByFirstChar("PartialLengthByFirstChar", hash_table_size),
            m_mapLengthByTagAndFirstChar("LengthByTagAndFirstChar", hash_table_size) ,
            m_mapLengthByTagAndLastChar("LengthByTagAndLastChar", hash_table_size) ,
            m_mapTag0Tag1Size1("Tag0Tag1Size1", hash_table_size),
            m_mapTag1Tag2Size1("Tag1Tag2Size1", hash_table_size),
            m_mapTag0Tag1Tag2Size1("Tag0Tag1Tag2Size1", hash_table_size),
            m_mapST0wAction("ST0wAction", hash_table_size),
            m_mapST0tAction("ST0tAction", hash_table_size),
            m_mapST0wtAction("ST0wtAction", hash_table_size),
            m_mapST1wAction("ST1wAction", hash_table_size),
            m_mapST1tAction("ST1tAction", hash_table_size),
            m_mapST1wtAction("ST1wtAction", hash_table_size),
            m_mapST0wST1wAction("ST0wST1wAction", hash_table_size),
            m_mapST0tST1tAction("ST0tST1tAction", hash_table_size),
            m_mapST0wtST1tAction("ST0wtST1tAction", hash_table_size),
            m_mapST0tST1wtAction("ST0tST1wtAction", hash_table_size),
            m_mapST0wtST1wAction("ST0wtST1wAction", hash_table_size),
            m_mapST0wST1wtAction("ST0wST1wtAction", hash_table_size),
            m_mapST0wN0cAction("ST0wN0cAction", hash_table_size),
            m_mapST0wtN0cAction("ST0wtN0cAction", hash_table_size),
            m_mapST0tST1tN0cAction("ST0tST1tN0cAction", hash_table_size),
            m_mapST0tST1wN0cAction("ST0tST1wN0cAction", hash_table_size),
            m_mapST0wST1tN0cAction("ST0wST1tN0cAction", hash_table_size),
            m_mapST0cAction("ST0cAction", hash_table_size),
            m_mapST0ctAction("ST0ctAction", hash_table_size),
            m_mapST1cAction("ST1cAction", hash_table_size),
            m_mapST1ctAction("ST1ctAction", hash_table_size),
            m_mapST0cST1cAction("ST0cST1cAction", hash_table_size),
            m_mapST0wST1cAction("ST0wST1cAction", hash_table_size),
            m_mapST0cST1wAction("ST0cST1wAction", hash_table_size),
            m_mapST0wtST1cAction("ST0wtST1cAction", hash_table_size),
            m_mapST0cST1wtAction("ST0cST1wtAction", hash_table_size),
            m_mapST0wST1ctAction("ST0wST1ctAction", hash_table_size),
            m_mapST0ctST1wAction("ST0ctST1wAction", hash_table_size),
            m_mapST0cN0cAction("ST0cN0cAction", hash_table_size),
            m_mapST1cST0cN0cAction("ST1cST0cN0cAction", hash_table_size),
            m_mapST2cST1cST0cAction("ST2cST1cST0cAction", hash_table_size),
            m_mapBiAction("BiAction", hash_table_size),
            m_mapTriAction("TriAction", hash_table_size)
   {
      for (unsigned i=0; i<=CTag::COUNT; ++i) m_maxLengthByTag[i] = 1;
      loadScores();
   }

   virtual ~CWeight() {  }

public:
   // MEHTODS
   virtual void loadScores();
   virtual void saveScores();
   virtual void outputScores();
   void computeAverageFeatureWeights(int round);
   //SCORE_TYPE dotProduct(const CWeight &w);

   void clear() {
      iterate_templates(,.clear(););
   }

   SCORE_TYPE squareNorm() {
      static SCORE_TYPE retval;
      retval = 0;
      iterate_templates(retval+=,.squareNorm(););
      return retval;
   }

   void scaleCurrent(const SCORE_TYPE &scale, const int &round) {
      iterate_templates(,ID(.scaleCurrent(scale, round);));
   }

   void addCurrent(CWeight*w, int round);
   void subtractCurrent(CWeight*w, int round);

};

};
};

#endif
