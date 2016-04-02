// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the constituent parser weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _DISCOURSE_WEIGHTS_H
#define _DISCOURSE_WEIGHTS_H

#include "weight_base.h"

const static unsigned DEFAULT_TABLE_SIZE = 1<<17;

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,

#define iterate_templates(left, right) \
	left(m_mapS0c)right\
	left(m_mapS0wt)right\
	left(m_mapS0tc)right\
	left(m_mapS0wc)right\
	left(m_mapS0bwt)right\
	left(m_mapS0btc)right\
	left(m_mapS0bwc)right\
	left(m_mapS0ewt)right\
	left(m_mapS0etc)right\
	left(m_mapS0ewc)right\
\
	left(m_mapS0sc)right\
	left(m_mapS1c)right\
	left(m_mapS1wt)right\
	left(m_mapS1tc)right\
	left(m_mapS1wc)right\
	left(m_mapS1bwt)right\
	left(m_mapS1btc)right\
	left(m_mapS1bwc)right\
	left(m_mapS1ewt)right\
	left(m_mapS1etc)right\
\
	left(m_mapS1ewc)right\
	left(m_mapS1sc)right\
	left(m_mapS2c)right\
	left(m_mapS2wt)right\
	left(m_mapS2tc)right\
	left(m_mapS2wc)right\
	left(m_mapS2bwt)right\
	left(m_mapS2btc)right\
	left(m_mapS2bwc)right\
	left(m_mapS2ewt)right\
\
	left(m_mapS2etc)right\
	left(m_mapS2ewc)right\
	left(m_mapS2sc)right\
	left(m_mapN0w)right\
	left(m_mapN0t)right\
	left(m_mapN0wt)right\
	left(m_mapN0sc)right\
	left(m_mapN0bw)right\
	left(m_mapN0bt)right\
	left(m_mapN0bwt)right\
\
	left(m_mapN0ew)right\
	left(m_mapN0et)right\
	left(m_mapN0ewt)right\
	left(m_mapN1w)right\
	left(m_mapN1t)right\
	left(m_mapN1wt)right\
	left(m_mapN1bw)right\
	left(m_mapN1bt)right\
	left(m_mapN1bwt)right\
	left(m_mapN1ew)right\
\
	left(m_mapN1et)right\
	left(m_mapN1ewt)right\
	left(m_mapN1sc)right\
	left(m_mapN2w)right\
	left(m_mapN2t)right\
	left(m_mapN2wt)right\
	left(m_mapN2bw)right\
	left(m_mapN2bt)right\
	left(m_mapN2bwt)right\
	left(m_mapN2ew)right\
\
	left(m_mapN2et)right\
	left(m_mapN2ewt)right\
	left(m_mapN2sc)right\
	left(m_mapS0Lwc)right\
	left(m_mapS0Ltc)right\
	left(m_mapS0Rwc)right\
	left(m_mapS0Rtc)right\
	left(m_mapS0Uwc)right\
	left(m_mapS0Utc)right\
	left(m_mapS1Lwc)right\
\
	left(m_mapS1Ltc)right\
	left(m_mapS1Rwc)right\
	left(m_mapS1Rtc)right\
	left(m_mapS1Uwc)right\
	left(m_mapS1Utc)right\
	left(m_mapS0wS1w)right\
	left(m_mapS0wcS1wc)right\
	left(m_mapS0wcS1c)right\
	left(m_mapS0cS1wc)right\
	left(m_mapS0cS1c)right\
\
	left(m_mapS0tS1t)right\
	left(m_mapS0wtS1wt)right\
	left(m_mapS0S1HeadEDUSameSentence)right\
	left(m_mapS0S1Dist)right\
	left(m_mapS0S1HeadEduSize)right\
	left(m_mapS0scS1sc)right\
	left(m_mapS0cS1sc)right\
	left(m_mapS0scS1c)right\
	left(m_mapS0bwS1bw)right\
	left(m_mapS0bwtS1bwt)right\
\
	left(m_mapS0bwcS1bwc)right\
	left(m_mapS0bwtS1c)right\
	left(m_mapS0cS1bwt)right\
	left(m_mapS0btS1bt)right\
	left(m_mapS0ewS1ew)right\
	left(m_mapS0ewtS1ewt)right\
	left(m_mapS0ewcS1ewc)right\
	left(m_mapS0ewtS1c)right\
	left(m_mapS0cS1ewt)right\
	left(m_mapS0etS1et)right\
\
	left(m_mapS0S1EDUNUMPairSize)right\
	left(m_mapS0SentBeginS1SentBegin)right\
	left(m_mapS0SentBeginS1SentEnd)right\
	left(m_mapS0SentEndS1SentBegin)right\
	left(m_mapS0SentEndS1SentEnd)right\
	left(m_mapS0ParaBeginS1ParaBegin)right\
	left(m_mapS0ParaBeginS1ParaEnd)right\
	left(m_mapS0ParaEndS1ParaBegin)right\
	left(m_mapS0ParaEndS1ParaEnd)right\
	left(m_mapS0wN0w)right\
\
	left(m_mapS0wtN0wt)right\
	left(m_mapS0wcN0wc)right\
	left(m_mapS0cN0wt)right\
	left(m_mapS0wcN0t)right\
	left(m_mapS0cN0t)right\
	left(m_mapS0tN0t)right\
	left(m_mapS0N0HeadEDUSameSentence)right\
	left(m_mapS0N0HeadEduSize)right\
	left(m_mapS0scN0sc)right\
	left(m_mapS0cN0sc)right\
\
	left(m_mapS0scN0t)right\
	left(m_mapS0bwN0bw)right\
	left(m_mapS0bwtN0bwt)right\
	left(m_mapS0bwcN0bwc)right\
	left(m_mapS0bwtN0t)right\
	left(m_mapS0cN0bwt)right\
	left(m_mapS0btN0bt)right\
	left(m_mapS0ewN0ew)right\
	left(m_mapS0ewtN0ewt)right\
	left(m_mapS0ewcN0ewc)right\
\
	left(m_mapS0ewtN0t)right\
	left(m_mapS0cN0ewt)right\
	left(m_mapS0etN0et)right\
	left(m_mapS0N0Dist)right\
	left(m_mapS0SentBeginN0SentBegin)right\
	left(m_mapS0SentBeginN0SentEnd)right\
	left(m_mapS0SentEndN0SentBegin)right\
	left(m_mapS0SentEndN0SentEnd)right\
	left(m_mapS0ParaBeginN0ParaBegin)right\
	left(m_mapS0ParaBeginN0ParaEnd)right\
\
	left(m_mapS0ParaEndN0ParaBegin)right\
	left(m_mapS0ParaEndN0ParaEnd)right\
	left(m_mapS1wN0w)right\
	left(m_mapS1wtN0wt)right\
	left(m_mapS1wcN0wc)right\
	left(m_mapS1cN0wt)right\
	left(m_mapS1wcN0t)right\
	left(m_mapS1cN0t)right\
	left(m_mapS1tN0t)right\
	left(m_mapS1N0HeadEDUSameSentence)right\
\
	left(m_mapS1N0HeadEduSize)right\
	left(m_mapS1scN0sc)right\
	left(m_mapS1cN0sc)right\
	left(m_mapS1scN0t)right\
	left(m_mapS1bwN0bw)right\
	left(m_mapS1bwtN0bwt)right\
	left(m_mapS1bwcN0bwc)right\
	left(m_mapS1bwtN0t)right\
	left(m_mapS1cN0bwt)right\
	left(m_mapS1btN0bt)right\
\
	left(m_mapS1ewN0ew)right\
	left(m_mapS1ewtN0ewt)right\
	left(m_mapS1ewcN0ewc)right\
	left(m_mapS1ewtN0t)right\
	left(m_mapS1cN0ewt)right\
	left(m_mapS1etN0et)right\
	left(m_mapS1N0Dist)right\
	left(m_mapS1SentBeginN0SentBegin)right\
	left(m_mapS1SentBeginN0SentEnd)right\
	left(m_mapS1SentEndN0SentBegin)right\
\
	left(m_mapS1SentEndN0SentEnd)right\
	left(m_mapS1ParaBeginN0ParaBegin)right\
	left(m_mapS1ParaBeginN0ParaEnd)right\
	left(m_mapS1ParaEndN0ParaBegin)right\
	left(m_mapS1ParaEndN0ParaEnd)right\
	left(m_mapS1wS2w)right\
	left(m_mapS1wcS2wc)right\
	left(m_mapS1wcS2c)right\
	left(m_mapS1cS2wc)right\
	left(m_mapS1cS2c)right\
\
	left(m_mapS1tS2t)right\
	left(m_mapS1wtS2wt)right\
	left(m_mapS1S2HeadEDUSameSentence)right\
	left(m_mapS1S2Dist)right\
	left(m_mapS1S2HeadEduSize)right\
	left(m_mapS1scS2sc)right\
	left(m_mapS1cS2sc)right\
	left(m_mapS1scS2c)right\
	left(m_mapS1bwS2bw)right\
	left(m_mapS1bwtS2bwt)right\
\
	left(m_mapS1bwcS2bwc)right\
	left(m_mapS1bwtS2c)right\
	left(m_mapS1cS2bwt)right\
	left(m_mapS1btS2bt)right\
	left(m_mapS1ewS2ew)right\
	left(m_mapS1ewtS2ewt)right\
	left(m_mapS1ewcS2ewc)right\
	left(m_mapS1ewtS2c)right\
	left(m_mapS1cS2ewt)right\
	left(m_mapS1etS2et)right\
\
	left(m_mapS1SentBeginS2SentBegin)right\
	left(m_mapS1SentBeginS2SentEnd)right\
	left(m_mapS1SentEndS2SentBegin)right\
	left(m_mapS1SentEndS2SentEnd)right\
	left(m_mapS1ParaBeginS2ParaBegin)right\
	left(m_mapS1ParaBeginS2ParaEnd)right\
	left(m_mapS1ParaEndS2ParaBegin)right\
	left(m_mapS1ParaEndS2ParaEnd)right\
	left(m_mapN0wN1w)right\
	left(m_mapN0wtN1wt)right\
\
	left(m_mapN0tN1wt)right\
	left(m_mapN0wtN1t)right\
	left(m_mapN0tN1t)right\
	left(m_mapN0N1HeadEduSize)right\
	left(m_mapN0scN1sc)right\
	left(m_mapN0tN1sc)right\
	left(m_mapN0scN1t)right\
	left(m_mapN0bwN1bw)right\
	left(m_mapN0bwtN1bwt)right\
	left(m_mapN0bwtN1t)right\
\
	left(m_mapN0tN1bwt)right\
	left(m_mapN0btN1bt)right\
	left(m_mapN0ewN1ew)right\
	left(m_mapN0ewtN1ewt)right\
	left(m_mapN0ewtN1t)right\
	left(m_mapN0tN1ewt)right\
	left(m_mapN0etN1et)right\
	left(m_mapS0wS1cN0t)right\
	left(m_mapS0cS1wN0t)right\
	left(m_mapS0cS1cN0w)right\
\
	left(m_mapS0cS1cN0t)right\
	left(m_mapS0tS1tN0t)right\
	left(m_mapS0scS1scN0sc)right\
	left(m_mapS0btS1btN0bt)right\
	left(m_mapS0etS1etN0et)right\
	left(m_mapS0wN0tN1t)right\
	left(m_mapS0cN0wN1t)right\
	left(m_mapS0cN0tN1w)right\
	left(m_mapS0cN0tN1t)right\
	left(m_mapS0tN0tN1t)right\
\
	left(m_mapS0jN0tN1t)right\
	left(m_mapS0scN0scN1sc)right\
	left(m_mapS0btN0btN1bt)right\
	left(m_mapS0etN0etN1et)right\
	left(m_mapS0wS1cS2c)right\
	left(m_mapS0cS1wS2c)right\
	left(m_mapS0cS1cS2w)right\
	left(m_mapS0cS1cS2c)right\
	left(m_mapS0tS1tS2t)right\
	left(m_mapS0scS1scS2sc)right\
\
	left(m_mapS0btS1btS2bt)right\
	left(m_mapS0etS1etS2et)right\
	left(m_mapS0cS0RcN0t)right\
	left(m_mapS0cS0RjN0t)right\
	left(m_mapS0cS0RcN0w)right\
	left(m_mapS0cS0LcN0t)right\
	left(m_mapS0wS0LcN0t)right\
	left(m_mapS0cS0LcN0w)right\
	left(m_mapS0wS0RcN0t)right\
	left(m_mapS0cS0UcN0t)right\
\
	left(m_mapS0wS0UcN0t)right\
	left(m_mapS0cS0UcN0w)right\
	left(m_mapS0cS0LcS1c)right\
	left(m_mapS0cS0LjS1j)right\
	left(m_mapS0cS0LcS1w)right\
	left(m_mapS0wS0LcS1c)right\
	left(m_mapS0cS0RcS1c)right\
	left(m_mapS0wS0RcS1c)right\
	left(m_mapS0cS0RcS1w)right\
	left(m_mapS0cS0UcS1c)right\
\
	left(m_mapS0wS0UcS1c)right\
	left(m_mapS0cS0UcS1w)right\
	left(m_mapS0cS1cS1Rc)right\
	left(m_mapS0jS1cS1Rj)right\
	left(m_mapS0wS1cS1Rc)right\
	left(m_mapS0cS1cS1Lc)right\
	left(m_mapS0wS1cS1Lc)right\
	left(m_mapS0cS1wS1Lc)right\
	left(m_mapS0cS1wS1Rc)right\
	left(m_mapS0cS1cS1Uc)right\
\
	left(m_mapS0wS1cS1Uc)right\
	left(m_mapS0cS1wS1Uc)right\
	left(m_mapA1)right\
	left(m_mapA1A2)right\
	left(m_mapS0AllWord)right\
	left(m_mapS1AllWord)right\
	left(m_mapN0AllWord)right


#define iterate_double_templates(left, middle, right)\
	left m_mapS0c middle m_mapS0c right\
	left m_mapS0wt middle m_mapS0wt right\
	left m_mapS0tc middle m_mapS0tc right\
	left m_mapS0wc middle m_mapS0wc right\
	left m_mapS0bwt middle m_mapS0bwt right\
	left m_mapS0btc middle m_mapS0btc right\
	left m_mapS0bwc middle m_mapS0bwc right\
	left m_mapS0ewt middle m_mapS0ewt right\
	left m_mapS0etc middle m_mapS0etc right\
	left m_mapS0ewc middle m_mapS0ewc right\
\
	left m_mapS0sc middle m_mapS0sc right\
	left m_mapS1c middle m_mapS1c right\
	left m_mapS1wt middle m_mapS1wt right\
	left m_mapS1tc middle m_mapS1tc right\
	left m_mapS1wc middle m_mapS1wc right\
	left m_mapS1bwt middle m_mapS1bwt right\
	left m_mapS1btc middle m_mapS1btc right\
	left m_mapS1bwc middle m_mapS1bwc right\
	left m_mapS1ewt middle m_mapS1ewt right\
	left m_mapS1etc middle m_mapS1etc right\
\
	left m_mapS1ewc middle m_mapS1ewc right\
	left m_mapS1sc middle m_mapS1sc right\
	left m_mapS2c middle m_mapS2c right\
	left m_mapS2wt middle m_mapS2wt right\
	left m_mapS2tc middle m_mapS2tc right\
	left m_mapS2wc middle m_mapS2wc right\
	left m_mapS2bwt middle m_mapS2bwt right\
	left m_mapS2btc middle m_mapS2btc right\
	left m_mapS2bwc middle m_mapS2bwc right\
	left m_mapS2ewt middle m_mapS2ewt right\
\
	left m_mapS2etc middle m_mapS2etc right\
	left m_mapS2ewc middle m_mapS2ewc right\
	left m_mapS2sc middle m_mapS2sc right\
	left m_mapN0w middle m_mapN0w right\
	left m_mapN0t middle m_mapN0t right\
	left m_mapN0wt middle m_mapN0wt right\
	left m_mapN0sc middle m_mapN0sc right\
	left m_mapN0bw middle m_mapN0bw right\
	left m_mapN0bt middle m_mapN0bt right\
	left m_mapN0bwt middle m_mapN0bwt right\
\
	left m_mapN0ew middle m_mapN0ew right\
	left m_mapN0et middle m_mapN0et right\
	left m_mapN0ewt middle m_mapN0ewt right\
	left m_mapN1w middle m_mapN1w right\
	left m_mapN1t middle m_mapN1t right\
	left m_mapN1wt middle m_mapN1wt right\
	left m_mapN1bw middle m_mapN1bw right\
	left m_mapN1bt middle m_mapN1bt right\
	left m_mapN1bwt middle m_mapN1bwt right\
	left m_mapN1ew middle m_mapN1ew right\
\
	left m_mapN1et middle m_mapN1et right\
	left m_mapN1ewt middle m_mapN1ewt right\
	left m_mapN1sc middle m_mapN1sc right\
	left m_mapN2w middle m_mapN2w right\
	left m_mapN2t middle m_mapN2t right\
	left m_mapN2wt middle m_mapN2wt right\
	left m_mapN2bw middle m_mapN2bw right\
	left m_mapN2bt middle m_mapN2bt right\
	left m_mapN2bwt middle m_mapN2bwt right\
	left m_mapN2ew middle m_mapN2ew right\
\
	left m_mapN2et middle m_mapN2et right\
	left m_mapN2ewt middle m_mapN2ewt right\
	left m_mapN2sc middle m_mapN2sc right\
	left m_mapS0Lwc middle m_mapS0Lwc right\
	left m_mapS0Ltc middle m_mapS0Ltc right\
	left m_mapS0Rwc middle m_mapS0Rwc right\
	left m_mapS0Rtc middle m_mapS0Rtc right\
	left m_mapS0Uwc middle m_mapS0Uwc right\
	left m_mapS0Utc middle m_mapS0Utc right\
	left m_mapS1Lwc middle m_mapS1Lwc right\
\
	left m_mapS1Ltc middle m_mapS1Ltc right\
	left m_mapS1Rwc middle m_mapS1Rwc right\
	left m_mapS1Rtc middle m_mapS1Rtc right\
	left m_mapS1Uwc middle m_mapS1Uwc right\
	left m_mapS1Utc middle m_mapS1Utc right\
	left m_mapS0wS1w middle m_mapS0wS1w right\
	left m_mapS0wcS1wc middle m_mapS0wcS1wc right\
	left m_mapS0wcS1c middle m_mapS0wcS1c right\
	left m_mapS0cS1wc middle m_mapS0cS1wc right\
	left m_mapS0cS1c middle m_mapS0cS1c right\
\
	left m_mapS0tS1t middle m_mapS0tS1t right\
	left m_mapS0wtS1wt middle m_mapS0wtS1wt right\
	left m_mapS0S1HeadEDUSameSentence middle m_mapS0S1HeadEDUSameSentence right\
	left m_mapS0S1Dist middle m_mapS0S1Dist right\
	left m_mapS0S1HeadEduSize middle m_mapS0S1HeadEduSize right\
	left m_mapS0scS1sc middle m_mapS0scS1sc right\
	left m_mapS0cS1sc middle m_mapS0cS1sc right\
	left m_mapS0scS1c middle m_mapS0scS1c right\
	left m_mapS0bwS1bw middle m_mapS0bwS1bw right\
	left m_mapS0bwtS1bwt middle m_mapS0bwtS1bwt right\
\
	left m_mapS0bwcS1bwc middle m_mapS0bwcS1bwc right\
	left m_mapS0bwtS1c middle m_mapS0bwtS1c right\
	left m_mapS0cS1bwt middle m_mapS0cS1bwt right\
	left m_mapS0btS1bt middle m_mapS0btS1bt right\
	left m_mapS0ewS1ew middle m_mapS0ewS1ew right\
	left m_mapS0ewtS1ewt middle m_mapS0ewtS1ewt right\
	left m_mapS0ewcS1ewc middle m_mapS0ewcS1ewc right\
	left m_mapS0ewtS1c middle m_mapS0ewtS1c right\
	left m_mapS0cS1ewt middle m_mapS0cS1ewt right\
	left m_mapS0etS1et middle m_mapS0etS1et right\
\
	left m_mapS0S1EDUNUMPairSize middle m_mapS0S1EDUNUMPairSize right\
	left m_mapS0SentBeginS1SentBegin middle m_mapS0SentBeginS1SentBegin right\
	left m_mapS0SentBeginS1SentEnd middle m_mapS0SentBeginS1SentEnd right\
	left m_mapS0SentEndS1SentBegin middle m_mapS0SentEndS1SentBegin right\
	left m_mapS0SentEndS1SentEnd middle m_mapS0SentEndS1SentEnd right\
	left m_mapS0ParaBeginS1ParaBegin middle m_mapS0ParaBeginS1ParaBegin right\
	left m_mapS0ParaBeginS1ParaEnd middle m_mapS0ParaBeginS1ParaEnd right\
	left m_mapS0ParaEndS1ParaBegin middle m_mapS0ParaEndS1ParaBegin right\
	left m_mapS0ParaEndS1ParaEnd middle m_mapS0ParaEndS1ParaEnd right\
	left m_mapS0wN0w middle m_mapS0wN0w right\
\
	left m_mapS0wtN0wt middle m_mapS0wtN0wt right\
	left m_mapS0wcN0wc middle m_mapS0wcN0wc right\
	left m_mapS0cN0wt middle m_mapS0cN0wt right\
	left m_mapS0wcN0t middle m_mapS0wcN0t right\
	left m_mapS0cN0t middle m_mapS0cN0t right\
	left m_mapS0tN0t middle m_mapS0tN0t right\
	left m_mapS0N0HeadEDUSameSentence middle m_mapS0N0HeadEDUSameSentence right\
	left m_mapS0N0HeadEduSize middle m_mapS0N0HeadEduSize right\
	left m_mapS0scN0sc middle m_mapS0scN0sc right\
	left m_mapS0cN0sc middle m_mapS0cN0sc right\
\
	left m_mapS0scN0t middle m_mapS0scN0t right\
	left m_mapS0bwN0bw middle m_mapS0bwN0bw right\
	left m_mapS0bwtN0bwt middle m_mapS0bwtN0bwt right\
	left m_mapS0bwcN0bwc middle m_mapS0bwcN0bwc right\
	left m_mapS0bwtN0t middle m_mapS0bwtN0t right\
	left m_mapS0cN0bwt middle m_mapS0cN0bwt right\
	left m_mapS0btN0bt middle m_mapS0btN0bt right\
	left m_mapS0ewN0ew middle m_mapS0ewN0ew right\
	left m_mapS0ewtN0ewt middle m_mapS0ewtN0ewt right\
	left m_mapS0ewcN0ewc middle m_mapS0ewcN0ewc right\
\
	left m_mapS0ewtN0t middle m_mapS0ewtN0t right\
	left m_mapS0cN0ewt middle m_mapS0cN0ewt right\
	left m_mapS0etN0et middle m_mapS0etN0et right\
	left m_mapS0N0Dist middle m_mapS0N0Dist right\
	left m_mapS0SentBeginN0SentBegin middle m_mapS0SentBeginN0SentBegin right\
	left m_mapS0SentBeginN0SentEnd middle m_mapS0SentBeginN0SentEnd right\
	left m_mapS0SentEndN0SentBegin middle m_mapS0SentEndN0SentBegin right\
	left m_mapS0SentEndN0SentEnd middle m_mapS0SentEndN0SentEnd right\
	left m_mapS0ParaBeginN0ParaBegin middle m_mapS0ParaBeginN0ParaBegin right\
	left m_mapS0ParaBeginN0ParaEnd middle m_mapS0ParaBeginN0ParaEnd right\
\
	left m_mapS0ParaEndN0ParaBegin middle m_mapS0ParaEndN0ParaBegin right\
	left m_mapS0ParaEndN0ParaEnd middle m_mapS0ParaEndN0ParaEnd right\
	left m_mapS1wN0w middle m_mapS1wN0w right\
	left m_mapS1wtN0wt middle m_mapS1wtN0wt right\
	left m_mapS1wcN0wc middle m_mapS1wcN0wc right\
	left m_mapS1cN0wt middle m_mapS1cN0wt right\
	left m_mapS1wcN0t middle m_mapS1wcN0t right\
	left m_mapS1cN0t middle m_mapS1cN0t right\
	left m_mapS1tN0t middle m_mapS1tN0t right\
	left m_mapS1N0HeadEDUSameSentence middle m_mapS1N0HeadEDUSameSentence right\
\
	left m_mapS1N0HeadEduSize middle m_mapS1N0HeadEduSize right\
	left m_mapS1scN0sc middle m_mapS1scN0sc right\
	left m_mapS1cN0sc middle m_mapS1cN0sc right\
	left m_mapS1scN0t middle m_mapS1scN0t right\
	left m_mapS1bwN0bw middle m_mapS1bwN0bw right\
	left m_mapS1bwtN0bwt middle m_mapS1bwtN0bwt right\
	left m_mapS1bwcN0bwc middle m_mapS1bwcN0bwc right\
	left m_mapS1bwtN0t middle m_mapS1bwtN0t right\
	left m_mapS1cN0bwt middle m_mapS1cN0bwt right\
	left m_mapS1btN0bt middle m_mapS1btN0bt right\
\
	left m_mapS1ewN0ew middle m_mapS1ewN0ew right\
	left m_mapS1ewtN0ewt middle m_mapS1ewtN0ewt right\
	left m_mapS1ewcN0ewc middle m_mapS1ewcN0ewc right\
	left m_mapS1ewtN0t middle m_mapS1ewtN0t right\
	left m_mapS1cN0ewt middle m_mapS1cN0ewt right\
	left m_mapS1etN0et middle m_mapS1etN0et right\
	left m_mapS1N0Dist middle m_mapS1N0Dist right\
	left m_mapS1SentBeginN0SentBegin middle m_mapS1SentBeginN0SentBegin right\
	left m_mapS1SentBeginN0SentEnd middle m_mapS1SentBeginN0SentEnd right\
	left m_mapS1SentEndN0SentBegin middle m_mapS1SentEndN0SentBegin right\
\
	left m_mapS1SentEndN0SentEnd middle m_mapS1SentEndN0SentEnd right\
	left m_mapS1ParaBeginN0ParaBegin middle m_mapS1ParaBeginN0ParaBegin right\
	left m_mapS1ParaBeginN0ParaEnd middle m_mapS1ParaBeginN0ParaEnd right\
	left m_mapS1ParaEndN0ParaBegin middle m_mapS1ParaEndN0ParaBegin right\
	left m_mapS1ParaEndN0ParaEnd middle m_mapS1ParaEndN0ParaEnd right\
	left m_mapS1wS2w middle m_mapS1wS2w right\
	left m_mapS1wcS2wc middle m_mapS1wcS2wc right\
	left m_mapS1wcS2c middle m_mapS1wcS2c right\
	left m_mapS1cS2wc middle m_mapS1cS2wc right\
	left m_mapS1cS2c middle m_mapS1cS2c right\
\
	left m_mapS1tS2t middle m_mapS1tS2t right\
	left m_mapS1wtS2wt middle m_mapS1wtS2wt right\
	left m_mapS1S2HeadEDUSameSentence middle m_mapS1S2HeadEDUSameSentence right\
	left m_mapS1S2Dist middle m_mapS1S2Dist right\
	left m_mapS1S2HeadEduSize middle m_mapS1S2HeadEduSize right\
	left m_mapS1scS2sc middle m_mapS1scS2sc right\
	left m_mapS1cS2sc middle m_mapS1cS2sc right\
	left m_mapS1scS2c middle m_mapS1scS2c right\
	left m_mapS1bwS2bw middle m_mapS1bwS2bw right\
	left m_mapS1bwtS2bwt middle m_mapS1bwtS2bwt right\
\
	left m_mapS1bwcS2bwc middle m_mapS1bwcS2bwc right\
	left m_mapS1bwtS2c middle m_mapS1bwtS2c right\
	left m_mapS1cS2bwt middle m_mapS1cS2bwt right\
	left m_mapS1btS2bt middle m_mapS1btS2bt right\
	left m_mapS1ewS2ew middle m_mapS1ewS2ew right\
	left m_mapS1ewtS2ewt middle m_mapS1ewtS2ewt right\
	left m_mapS1ewcS2ewc middle m_mapS1ewcS2ewc right\
	left m_mapS1ewtS2c middle m_mapS1ewtS2c right\
	left m_mapS1cS2ewt middle m_mapS1cS2ewt right\
	left m_mapS1etS2et middle m_mapS1etS2et right\
\
	left m_mapS1SentBeginS2SentBegin middle m_mapS1SentBeginS2SentBegin right\
	left m_mapS1SentBeginS2SentEnd middle m_mapS1SentBeginS2SentEnd right\
	left m_mapS1SentEndS2SentBegin middle m_mapS1SentEndS2SentBegin right\
	left m_mapS1SentEndS2SentEnd middle m_mapS1SentEndS2SentEnd right\
	left m_mapS1ParaBeginS2ParaBegin middle m_mapS1ParaBeginS2ParaBegin right\
	left m_mapS1ParaBeginS2ParaEnd middle m_mapS1ParaBeginS2ParaEnd right\
	left m_mapS1ParaEndS2ParaBegin middle m_mapS1ParaEndS2ParaBegin right\
	left m_mapS1ParaEndS2ParaEnd middle m_mapS1ParaEndS2ParaEnd right\
	left m_mapN0wN1w middle m_mapN0wN1w right\
	left m_mapN0wtN1wt middle m_mapN0wtN1wt right\
\
	left m_mapN0tN1wt middle m_mapN0tN1wt right\
	left m_mapN0wtN1t middle m_mapN0wtN1t right\
	left m_mapN0tN1t middle m_mapN0tN1t right\
	left m_mapN0N1HeadEduSize middle m_mapN0N1HeadEduSize right\
	left m_mapN0scN1sc middle m_mapN0scN1sc right\
	left m_mapN0tN1sc middle m_mapN0tN1sc right\
	left m_mapN0scN1t middle m_mapN0scN1t right\
	left m_mapN0bwN1bw middle m_mapN0bwN1bw right\
	left m_mapN0bwtN1bwt middle m_mapN0bwtN1bwt right\
	left m_mapN0bwtN1t middle m_mapN0bwtN1t right\
\
	left m_mapN0tN1bwt middle m_mapN0tN1bwt right\
	left m_mapN0btN1bt middle m_mapN0btN1bt right\
	left m_mapN0ewN1ew middle m_mapN0ewN1ew right\
	left m_mapN0ewtN1ewt middle m_mapN0ewtN1ewt right\
	left m_mapN0ewtN1t middle m_mapN0ewtN1t right\
	left m_mapN0tN1ewt middle m_mapN0tN1ewt right\
	left m_mapN0etN1et middle m_mapN0etN1et right\
	left m_mapS0wS1cN0t middle m_mapS0wS1cN0t right\
	left m_mapS0cS1wN0t middle m_mapS0cS1wN0t right\
	left m_mapS0cS1cN0w middle m_mapS0cS1cN0w right\
\
	left m_mapS0cS1cN0t middle m_mapS0cS1cN0t right\
	left m_mapS0tS1tN0t middle m_mapS0tS1tN0t right\
	left m_mapS0scS1scN0sc middle m_mapS0scS1scN0sc right\
	left m_mapS0btS1btN0bt middle m_mapS0btS1btN0bt right\
	left m_mapS0etS1etN0et middle m_mapS0etS1etN0et right\
	left m_mapS0wN0tN1t middle m_mapS0wN0tN1t right\
	left m_mapS0cN0wN1t middle m_mapS0cN0wN1t right\
	left m_mapS0cN0tN1w middle m_mapS0cN0tN1w right\
	left m_mapS0cN0tN1t middle m_mapS0cN0tN1t right\
	left m_mapS0tN0tN1t middle m_mapS0tN0tN1t right\
\
	left m_mapS0jN0tN1t middle m_mapS0jN0tN1t right\
	left m_mapS0scN0scN1sc middle m_mapS0scN0scN1sc right\
	left m_mapS0btN0btN1bt middle m_mapS0btN0btN1bt right\
	left m_mapS0etN0etN1et middle m_mapS0etN0etN1et right\
	left m_mapS0wS1cS2c middle m_mapS0wS1cS2c right\
	left m_mapS0cS1wS2c middle m_mapS0cS1wS2c right\
	left m_mapS0cS1cS2w middle m_mapS0cS1cS2w right\
	left m_mapS0cS1cS2c middle m_mapS0cS1cS2c right\
	left m_mapS0tS1tS2t middle m_mapS0tS1tS2t right\
	left m_mapS0scS1scS2sc middle m_mapS0scS1scS2sc right\
\
	left m_mapS0btS1btS2bt middle m_mapS0btS1btS2bt right\
	left m_mapS0etS1etS2et middle m_mapS0etS1etS2et right\
	left m_mapS0cS0RcN0t middle m_mapS0cS0RcN0t right\
	left m_mapS0cS0RjN0t middle m_mapS0cS0RjN0t right\
	left m_mapS0cS0RcN0w middle m_mapS0cS0RcN0w right\
	left m_mapS0cS0LcN0t middle m_mapS0cS0LcN0t right\
	left m_mapS0wS0LcN0t middle m_mapS0wS0LcN0t right\
	left m_mapS0cS0LcN0w middle m_mapS0cS0LcN0w right\
	left m_mapS0wS0RcN0t middle m_mapS0wS0RcN0t right\
	left m_mapS0cS0UcN0t middle m_mapS0cS0UcN0t right\
\
	left m_mapS0wS0UcN0t middle m_mapS0wS0UcN0t right\
	left m_mapS0cS0UcN0w middle m_mapS0cS0UcN0w right\
	left m_mapS0cS0LcS1c middle m_mapS0cS0LcS1c right\
	left m_mapS0cS0LjS1j middle m_mapS0cS0LjS1j right\
	left m_mapS0cS0LcS1w middle m_mapS0cS0LcS1w right\
	left m_mapS0wS0LcS1c middle m_mapS0wS0LcS1c right\
	left m_mapS0cS0RcS1c middle m_mapS0cS0RcS1c right\
	left m_mapS0wS0RcS1c middle m_mapS0wS0RcS1c right\
	left m_mapS0cS0RcS1w middle m_mapS0cS0RcS1w right\
	left m_mapS0cS0UcS1c middle m_mapS0cS0UcS1c right\
\
	left m_mapS0wS0UcS1c middle m_mapS0wS0UcS1c right\
	left m_mapS0cS0UcS1w middle m_mapS0cS0UcS1w right\
	left m_mapS0cS1cS1Rc middle m_mapS0cS1cS1Rc right\
	left m_mapS0jS1cS1Rj middle m_mapS0jS1cS1Rj right\
	left m_mapS0wS1cS1Rc middle m_mapS0wS1cS1Rc right\
	left m_mapS0cS1cS1Lc middle m_mapS0cS1cS1Lc right\
	left m_mapS0wS1cS1Lc middle m_mapS0wS1cS1Lc right\
	left m_mapS0cS1wS1Lc middle m_mapS0cS1wS1Lc right\
	left m_mapS0cS1wS1Rc middle m_mapS0cS1wS1Rc right\
	left m_mapS0cS1cS1Uc middle m_mapS0cS1cS1Uc right\
\
	left m_mapS0wS1cS1Uc middle m_mapS0wS1cS1Uc right\
	left m_mapS0cS1wS1Uc middle m_mapS0cS1wS1Uc right\
	left m_mapA1 middle m_mapA1 right\
	left m_mapA1A2 middle m_mapA1A2 right\
	left m_mapS0AllWord middle m_mapS0AllWord right\
	left m_mapS1AllWord middle m_mapS1AllWord right\
	left m_mapN0AllWord middle m_mapN0AllWord right

namespace TARGET_LANGUAGE {

namespace discourse {

//#include "discourse_macros.h"

//
// TYPE DEFINITIONS
//
typedef CScoreMapType<CWord, SCORE_TYPE, CAction::MAX> CWordMap;
typedef CScoreMapType<CTag, SCORE_TYPE, CAction::MAX> CTagMap;
typedef CScoreMapType<CTaggedWord<CTag, TAG_SEPARATOR>, SCORE_TYPE, CAction::MAX> CTaggedWordMap;
typedef CScoreMapType<std::pair<CWord, unsigned long>,  SCORE_TYPE, CAction::MAX> CWordIntMap;
typedef CScoreMapType<unsigned long, SCORE_TYPE, CAction::MAX> CIntMap;
typedef CScoreMapType<std::pair<unsigned long, unsigned long>, SCORE_TYPE, CAction::MAX> CTwoIntMap;
typedef CScoreMapType<CTwoWords, SCORE_TYPE, CAction::MAX> CTwoWordsMap;
typedef CScoreMapType<std::pair<CTwoWords, CActionType>, SCORE_TYPE, CAction::MAX> CTwoWordsActionTypeMap;
typedef CScoreMapType<CTuple3<CTwoWords, CTag, CActionType>, SCORE_TYPE, CAction::MAX> CTwoWordsTagActionTypeMap;
typedef CScoreMapType<CTuple2<CTwoWords, CDISCFGSet>, SCORE_TYPE, CAction::MAX> CTwoWordsCFGSetMap;
//typedef CScoreMapType<CTwoTaggedWords, SCORE_TYPE, CAction::MAX> CTwoWordsCFGSetMap;
typedef CScoreMapType<std::pair<CTwoTaggedWords, CActionType>, SCORE_TYPE, CAction::MAX> CTwoTaggedWordsActionTypeMap;
typedef CScoreMapType<CDISCFGSet, SCORE_TYPE, CAction::MAX> CCFGSetMap;
typedef CScoreMapType<std::pair<CDISCFGSet, unsigned long>, SCORE_TYPE, CAction::MAX> CCFGSetIntMap;
typedef CScoreMapType<CTuple2<CWord, CDISCFGSet>, SCORE_TYPE, CAction::MAX> CWordCFGSetMap;
typedef CScoreMapType<CTuple3<CWord, CDISCFGSet, CActionType>, SCORE_TYPE, CAction::MAX> CWordCFGSetActionTypeMap;
typedef CScoreMapType<std::pair<CWord, CDISCFGSet>, SCORE_TYPE, CAction::MAX> CWordCFGRuleMap;
typedef CScoreMapType<std::pair<CTwoWords, CDISCFGSet>, SCORE_TYPE, CAction::MAX> CTwoWordsCFGRuleMap;
typedef CScoreMapType<std::pair<CDISCFGSet, CActionType>, SCORE_TYPE, CAction::MAX> CCFGSetActionTypeMap;
typedef CScoreMapType<CTuple2<CWord, CConstituent>, SCORE_TYPE, CAction::MAX> CWordConstituentMap;
typedef CScoreMapType<CTuple2<CTag, CConstituent>, SCORE_TYPE, CAction::MAX> CTagConstituentMap;
typedef CScoreMapType<CTuple3<CTag, CTag, unsigned long>, SCORE_TYPE, CAction::MAX> CWordTagIntMap;
typedef CScoreMapType<CDisConstituent, SCORE_TYPE, CAction::MAX> CDisConstituentMap;
typedef CScoreMapType<std::pair<CConstituent, unsigned long>, SCORE_TYPE, CAction::MAX> CConstituentMap;
typedef CScoreMapType<CAction, SCORE_TYPE, CAction::MAX> CActionMap;
typedef CScoreMapType<CTuple2<CAction, CAction>, SCORE_TYPE, CAction::MAX> CAction2Map;

typedef CHashMap<CWord, unsigned long> CWordToIntMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:

   // S0
   CDisConstituentMap m_mapS0c;
   CTaggedWordMap m_mapS0wt;
   CTagConstituentMap m_mapS0tc;
   CWordConstituentMap m_mapS0wc;

   CTaggedWordMap m_mapS0bwt;
   CTagConstituentMap m_mapS0btc;
   CWordConstituentMap m_mapS0bwc;

   CTaggedWordMap m_mapS0ewt;
   CTagConstituentMap m_mapS0etc;
   CWordConstituentMap m_mapS0ewc;

   CConstituentMap m_mapS0sc;


   // S1
   CDisConstituentMap m_mapS1c;
   CTaggedWordMap m_mapS1wt;
   CTagConstituentMap m_mapS1tc;
   CWordConstituentMap m_mapS1wc;

   CTaggedWordMap m_mapS1bwt;
   CTagConstituentMap m_mapS1btc;
   CWordConstituentMap m_mapS1bwc;

   CTaggedWordMap m_mapS1ewt;
   CTagConstituentMap m_mapS1etc;
   CWordConstituentMap m_mapS1ewc;

   CConstituentMap m_mapS1sc;

   // S2
   CDisConstituentMap m_mapS2c;
   CTaggedWordMap m_mapS2wt;
   CTagConstituentMap m_mapS2tc;
   CWordConstituentMap m_mapS2wc;

   CTaggedWordMap m_mapS2bwt;
   CTagConstituentMap m_mapS2btc;
   CWordConstituentMap m_mapS2bwc;

   CTaggedWordMap m_mapS2ewt;
   CTagConstituentMap m_mapS2etc;
   CWordConstituentMap m_mapS2ewc;

   CConstituentMap m_mapS2sc;


   // N0
   CWordMap m_mapN0w;
   CTagMap m_mapN0t;
   CTaggedWordMap m_mapN0wt;

   CConstituentMap m_mapN0sc;

   CWordMap m_mapN0bw;
   CTagMap m_mapN0bt;
   CTaggedWordMap m_mapN0bwt;

   CWordMap m_mapN0ew;
   CTagMap m_mapN0et;
   CTaggedWordMap m_mapN0ewt;

   // N1
   CWordMap m_mapN1w;
   CTagMap m_mapN1t;
   CTaggedWordMap m_mapN1wt;

   CWordMap m_mapN1bw;
   CTagMap m_mapN1bt;
   CTaggedWordMap m_mapN1bwt;

   CWordMap m_mapN1ew;
   CTagMap m_mapN1et;
   CTaggedWordMap m_mapN1ewt;

   CConstituentMap m_mapN1sc;

   // N2
   CWordMap m_mapN2w;
   CTagMap m_mapN2t;
   CTaggedWordMap m_mapN2wt;

   CWordMap m_mapN2bw;
   CTagMap m_mapN2bt;
   CTaggedWordMap m_mapN2bwt;

   CWordMap m_mapN2ew;
   CTagMap m_mapN2et;
   CTaggedWordMap m_mapN2ewt;

   CConstituentMap m_mapN2sc;


   // S0L
   CWordConstituentMap m_mapS0Lwc;
   CTagConstituentMap m_mapS0Ltc;

   // S0R
   CWordConstituentMap m_mapS0Rwc;
   CTagConstituentMap m_mapS0Rtc;

   // S0U
   CWordConstituentMap m_mapS0Uwc;
   CTagConstituentMap m_mapS0Utc;

   // S1L
   CWordConstituentMap m_mapS1Lwc;
   CTagConstituentMap m_mapS1Ltc;

   // S1R
   CWordConstituentMap m_mapS1Rwc;
   CTagConstituentMap m_mapS1Rtc;

   // S1U
   CWordConstituentMap m_mapS1Uwc;
   CTagConstituentMap m_mapS1Utc;

   // S0 S1
   CTwoWordsMap m_mapS0wS1w;
   CTwoWordsCFGSetMap m_mapS0wcS1wc;
   CWordCFGSetMap m_mapS0wcS1c;
   CWordCFGSetMap m_mapS0cS1wc;
   CCFGSetMap m_mapS0cS1c;
   CCFGSetMap m_mapS0tS1t;
   CTwoWordsCFGSetMap m_mapS0wtS1wt;

   CIntMap m_mapS0S1HeadEDUSameSentence;
   CIntMap m_mapS0S1Dist;
   CTwoIntMap m_mapS0S1HeadEduSize;


   CCFGSetIntMap m_mapS0scS1sc;
   CCFGSetIntMap m_mapS0cS1sc;
   CCFGSetIntMap m_mapS0scS1c;

   CTwoWordsMap m_mapS0bwS1bw;
   CTwoWordsCFGSetMap m_mapS0bwtS1bwt;
   CTwoWordsCFGSetMap m_mapS0bwcS1bwc;
   CWordCFGSetMap m_mapS0bwtS1c;
   CWordCFGSetMap m_mapS0cS1bwt;
   CCFGSetMap m_mapS0btS1bt;

   CTwoWordsMap m_mapS0ewS1ew;
   CTwoWordsCFGSetMap m_mapS0ewtS1ewt;
   CTwoWordsCFGSetMap m_mapS0ewcS1ewc;
   CWordCFGSetMap m_mapS0ewtS1c;
   CWordCFGSetMap m_mapS0cS1ewt;
   CCFGSetMap m_mapS0etS1et;

   CTwoIntMap m_mapS0S1EDUNUMPairSize;

   CTwoIntMap m_mapS0SentBeginS1SentBegin;
   CTwoIntMap m_mapS0SentBeginS1SentEnd;
   CTwoIntMap m_mapS0SentEndS1SentBegin;
   CTwoIntMap m_mapS0SentEndS1SentEnd;

   CTwoIntMap m_mapS0ParaBeginS1ParaBegin;
   CTwoIntMap m_mapS0ParaBeginS1ParaEnd;
   CTwoIntMap m_mapS0ParaEndS1ParaBegin;
   CTwoIntMap m_mapS0ParaEndS1ParaEnd;



   // S0 N0
   CTwoWordsMap m_mapS0wN0w;
   CTwoWordsCFGSetMap m_mapS0wtN0wt;
   CTwoWordsCFGSetMap m_mapS0wcN0wc;
   CWordCFGSetMap m_mapS0cN0wt;
   CWordCFGSetMap m_mapS0wcN0t;
   CCFGSetMap m_mapS0cN0t;
   CCFGSetMap m_mapS0tN0t;

   CIntMap m_mapS0N0HeadEDUSameSentence;
   CTwoIntMap m_mapS0N0HeadEduSize;


   CCFGSetIntMap m_mapS0scN0sc;
   CCFGSetIntMap m_mapS0cN0sc;
   CCFGSetIntMap m_mapS0scN0t;

   CTwoWordsMap m_mapS0bwN0bw;
   CTwoWordsCFGSetMap m_mapS0bwtN0bwt;
   CTwoWordsCFGSetMap m_mapS0bwcN0bwc;
   CWordCFGSetMap m_mapS0bwtN0t;
   CWordCFGSetMap m_mapS0cN0bwt;
   CCFGSetMap m_mapS0btN0bt;

   CTwoWordsMap m_mapS0ewN0ew;
   CTwoWordsCFGSetMap m_mapS0ewtN0ewt;
   CTwoWordsCFGSetMap m_mapS0ewcN0ewc;
   CWordCFGSetMap m_mapS0ewtN0t;
   CWordCFGSetMap m_mapS0cN0ewt;
   CCFGSetMap m_mapS0etN0et;

   CIntMap m_mapS0N0Dist;

   CTwoIntMap m_mapS0SentBeginN0SentBegin;
   CTwoIntMap m_mapS0SentBeginN0SentEnd;
   CTwoIntMap m_mapS0SentEndN0SentBegin;
   CTwoIntMap m_mapS0SentEndN0SentEnd;

   CTwoIntMap m_mapS0ParaBeginN0ParaBegin;
   CTwoIntMap m_mapS0ParaBeginN0ParaEnd;
   CTwoIntMap m_mapS0ParaEndN0ParaBegin;
   CTwoIntMap m_mapS0ParaEndN0ParaEnd;

   // S1 N0
   CTwoWordsMap m_mapS1wN0w;
   CTwoWordsCFGSetMap m_mapS1wtN0wt;
   CTwoWordsCFGSetMap m_mapS1wcN0wc;
   CWordCFGSetMap m_mapS1cN0wt;
   CWordCFGSetMap m_mapS1wcN0t;
   CCFGSetMap m_mapS1cN0t;
   CCFGSetMap m_mapS1tN0t;

   CIntMap m_mapS1N0HeadEDUSameSentence;
   CTwoIntMap m_mapS1N0HeadEduSize;


   CCFGSetIntMap m_mapS1scN0sc;
   CCFGSetIntMap m_mapS1cN0sc;
   CCFGSetIntMap m_mapS1scN0t;

   CTwoWordsMap m_mapS1bwN0bw;
   CTwoWordsCFGSetMap m_mapS1bwtN0bwt;
   CTwoWordsCFGSetMap m_mapS1bwcN0bwc;
   CWordCFGSetMap m_mapS1bwtN0t;
   CWordCFGSetMap m_mapS1cN0bwt;
   CCFGSetMap m_mapS1btN0bt;

   CTwoWordsMap m_mapS1ewN0ew;
   CTwoWordsCFGSetMap m_mapS1ewtN0ewt;
   CTwoWordsCFGSetMap m_mapS1ewcN0ewc;
   CWordCFGSetMap m_mapS1ewtN0t;
   CWordCFGSetMap m_mapS1cN0ewt;
   CCFGSetMap m_mapS1etN0et;

   CIntMap m_mapS1N0Dist;

   CTwoIntMap m_mapS1SentBeginN0SentBegin;
   CTwoIntMap m_mapS1SentBeginN0SentEnd;
   CTwoIntMap m_mapS1SentEndN0SentBegin;
   CTwoIntMap m_mapS1SentEndN0SentEnd;

   CTwoIntMap m_mapS1ParaBeginN0ParaBegin;
   CTwoIntMap m_mapS1ParaBeginN0ParaEnd;
   CTwoIntMap m_mapS1ParaEndN0ParaBegin;
   CTwoIntMap m_mapS1ParaEndN0ParaEnd;


   // S1 S2
   CTwoWordsMap m_mapS1wS2w;
   CTwoWordsCFGSetMap m_mapS1wcS2wc;
   CWordCFGSetMap m_mapS1wcS2c;
   CWordCFGSetMap m_mapS1cS2wc;
   CCFGSetMap m_mapS1cS2c;
   CCFGSetMap m_mapS1tS2t;
   CTwoWordsCFGSetMap m_mapS1wtS2wt;

   CIntMap m_mapS1S2HeadEDUSameSentence;
   CIntMap m_mapS1S2Dist;
   CTwoIntMap m_mapS1S2HeadEduSize;


   CCFGSetIntMap m_mapS1scS2sc;
   CCFGSetIntMap m_mapS1cS2sc;
   CCFGSetIntMap m_mapS1scS2c;

   CTwoWordsMap m_mapS1bwS2bw;
   CTwoWordsCFGSetMap m_mapS1bwtS2bwt;
   CTwoWordsCFGSetMap m_mapS1bwcS2bwc;
   CWordCFGSetMap m_mapS1bwtS2c;
   CWordCFGSetMap m_mapS1cS2bwt;
   CCFGSetMap m_mapS1btS2bt;

   CTwoWordsMap m_mapS1ewS2ew;
   CTwoWordsCFGSetMap m_mapS1ewtS2ewt;
   CTwoWordsCFGSetMap m_mapS1ewcS2ewc;
   CWordCFGSetMap m_mapS1ewtS2c;
   CWordCFGSetMap m_mapS1cS2ewt;
   CCFGSetMap m_mapS1etS2et;


   CTwoIntMap m_mapS1SentBeginS2SentBegin;
   CTwoIntMap m_mapS1SentBeginS2SentEnd;
   CTwoIntMap m_mapS1SentEndS2SentBegin;
   CTwoIntMap m_mapS1SentEndS2SentEnd;

   CTwoIntMap m_mapS1ParaBeginS2ParaBegin;
   CTwoIntMap m_mapS1ParaBeginS2ParaEnd;
   CTwoIntMap m_mapS1ParaEndS2ParaBegin;
   CTwoIntMap m_mapS1ParaEndS2ParaEnd;



   // N0 N1
   CTwoWordsMap m_mapN0wN1w;
   CTwoWordsCFGSetMap m_mapN0wtN1wt;
   CWordCFGSetMap m_mapN0tN1wt;
   CWordCFGSetMap m_mapN0wtN1t;
   CCFGSetMap m_mapN0tN1t;

   CTwoIntMap m_mapN0N1HeadEduSize;

   CCFGSetIntMap m_mapN0scN1sc;
   CCFGSetIntMap m_mapN0tN1sc;
   CCFGSetIntMap m_mapN0scN1t;


   CTwoWordsMap m_mapN0bwN1bw;
   CTwoWordsCFGSetMap m_mapN0bwtN1bwt;
   CWordCFGSetMap m_mapN0bwtN1t;
   CWordCFGSetMap m_mapN0tN1bwt;
   CCFGSetMap m_mapN0btN1bt;

   CTwoWordsMap m_mapN0ewN1ew;
   CTwoWordsCFGSetMap m_mapN0ewtN1ewt;
   CWordCFGSetMap m_mapN0ewtN1t;
   CWordCFGSetMap m_mapN0tN1ewt;
   CCFGSetMap m_mapN0etN1et;

   // S0 S1N0
   CWordCFGSetMap m_mapS0wS1cN0t;
   CWordCFGSetMap m_mapS0cS1wN0t;
   CWordCFGSetMap m_mapS0cS1cN0w;
   CCFGSetMap m_mapS0cS1cN0t;
   CCFGSetMap m_mapS0tS1tN0t;


   CCFGSetIntMap m_mapS0scS1scN0sc;

   CCFGSetMap m_mapS0btS1btN0bt;
   CCFGSetMap m_mapS0etS1etN0et;

   // S0 N0N1
   CWordCFGSetMap m_mapS0wN0tN1t;
   CWordCFGSetMap m_mapS0cN0wN1t;
   CWordCFGSetMap m_mapS0cN0tN1w;
   CCFGSetMap m_mapS0cN0tN1t;
   CCFGSetMap m_mapS0tN0tN1t;
   CCFGSetMap m_mapS0jN0tN1t;

   CCFGSetIntMap m_mapS0scN0scN1sc;

   CCFGSetMap m_mapS0btN0btN1bt;
   CCFGSetMap m_mapS0etN0etN1et;

   // S0 S1S2
   CWordCFGSetMap m_mapS0wS1cS2c;
   CWordCFGSetMap m_mapS0cS1wS2c;
   CWordCFGSetMap m_mapS0cS1cS2w;
   CCFGSetMap m_mapS0cS1cS2c;
   CCFGSetMap m_mapS0tS1tS2t;

   CCFGSetIntMap m_mapS0scS1scS2sc;

   CCFGSetMap m_mapS0btS1btS2bt;
   CCFGSetMap m_mapS0etS1etS2et;

   // S0 S0LRUN0
   CCFGSetMap m_mapS0cS0RcN0t;
   CCFGSetMap m_mapS0cS0RjN0t;
   CWordCFGSetMap m_mapS0cS0RcN0w;

   CCFGSetMap m_mapS0cS0LcN0t;
   CWordCFGSetMap m_mapS0wS0LcN0t;
   CWordCFGSetMap m_mapS0cS0LcN0w;
   CWordCFGSetMap m_mapS0wS0RcN0t;
   CCFGSetMap m_mapS0cS0UcN0t;
   CWordCFGSetMap m_mapS0wS0UcN0t;
   CWordCFGSetMap m_mapS0cS0UcN0w;

   // S0 S0LRUS1
   CCFGSetMap m_mapS0cS0LcS1c;
   CCFGSetMap m_mapS0cS0LjS1j;
   CWordCFGSetMap m_mapS0cS0LcS1w;

   CWordCFGSetMap m_mapS0wS0LcS1c;
   CCFGSetMap m_mapS0cS0RcS1c;
   CWordCFGSetMap m_mapS0wS0RcS1c;
   CWordCFGSetMap m_mapS0cS0RcS1w;
   CCFGSetMap m_mapS0cS0UcS1c;
   CWordCFGSetMap m_mapS0wS0UcS1c;
   CWordCFGSetMap m_mapS0cS0UcS1w;

   // S0 S1LRUS1
   CCFGSetMap m_mapS0cS1cS1Rc;
   CCFGSetMap m_mapS0jS1cS1Rj;
   CWordCFGSetMap m_mapS0wS1cS1Rc;

   CCFGSetMap m_mapS0cS1cS1Lc;
   CWordCFGSetMap m_mapS0wS1cS1Lc;
   CWordCFGSetMap m_mapS0cS1wS1Lc;
   CWordCFGSetMap m_mapS0cS1wS1Rc;
   CCFGSetMap m_mapS0cS1cS1Uc;
   CWordCFGSetMap m_mapS0wS1cS1Uc;
   CWordCFGSetMap m_mapS0cS1wS1Uc;

   // past action
   CActionMap m_mapA1;
   CAction2Map m_mapA1A2;

   //bag-of-words
   CWordMap m_mapS0AllWord;
   CWordMap m_mapS1AllWord;
   CWordMap m_mapN0AllWord;

   // Rule dictionary
   unsigned long m_nMaxWordFrequency;
   CWordToIntMap m_mapWordFrequency;

public:

   CWeight(bool bTrain, unsigned TABLE_SIZE = DEFAULT_TABLE_SIZE) : 
                          CWeightBase(bTrain) ,

                          m_nMaxWordFrequency(0) ,
                          m_mapWordFrequency(TABLE_SIZE),

                          m_mapS0c("S0c", TABLE_SIZE),
                          m_mapS0wt("S0wt", TABLE_SIZE),
                          m_mapS0tc("S0tc", TABLE_SIZE),
                          m_mapS0wc("S0wc", TABLE_SIZE),
                          m_mapS0bwt("S0bwt", TABLE_SIZE),
                          m_mapS0btc("S0btc", TABLE_SIZE),
                          m_mapS0bwc("S0bwc", TABLE_SIZE),
                          m_mapS0ewt("S0ewt", TABLE_SIZE),
                          m_mapS0etc("S0etc", TABLE_SIZE),
                          m_mapS0ewc("S0ewc", TABLE_SIZE),
                          m_mapS0sc("S0sc", TABLE_SIZE),
                          m_mapS1c("S1c", TABLE_SIZE),
                          m_mapS1wt("S1wt", TABLE_SIZE),
                          m_mapS1tc("S1tc", TABLE_SIZE),
                          m_mapS1wc("S1wc", TABLE_SIZE),
                          m_mapS1bwt("S1bwt", TABLE_SIZE),
                          m_mapS1btc("S1btc", TABLE_SIZE),
                          m_mapS1bwc("S1bwc", TABLE_SIZE),
                          m_mapS1ewt("S1ewt", TABLE_SIZE),
                          m_mapS1etc("S1etc", TABLE_SIZE),
                          m_mapS1ewc("S1ewc", TABLE_SIZE),
                          m_mapS1sc("S1sc", TABLE_SIZE),
                          m_mapS2c("S2c", TABLE_SIZE),
                          m_mapS2wt("S2wt", TABLE_SIZE),
                          m_mapS2tc("S2tc", TABLE_SIZE),
                          m_mapS2wc("S2wc", TABLE_SIZE),
                          m_mapS2bwt("S2bwt", TABLE_SIZE),
                          m_mapS2btc("S2btc", TABLE_SIZE),
                          m_mapS2bwc("S2bwc", TABLE_SIZE),
                          m_mapS2ewt("S2ewt", TABLE_SIZE),
                          m_mapS2etc("S2etc", TABLE_SIZE),
                          m_mapS2ewc("S2ewc", TABLE_SIZE),
                          m_mapS2sc("S2sc", TABLE_SIZE),
                          m_mapN0w("N0w", TABLE_SIZE),
                          m_mapN0t("N0t", TABLE_SIZE),
                          m_mapN0wt("N0wt", TABLE_SIZE),
                          m_mapN0sc("N0sc", TABLE_SIZE),
                          m_mapN0bw("N0bw", TABLE_SIZE),
                          m_mapN0bt("N0bt", TABLE_SIZE),
                          m_mapN0bwt("N0bwt", TABLE_SIZE),
                          m_mapN0ew("N0ew", TABLE_SIZE),
                          m_mapN0et("N0et", TABLE_SIZE),
                          m_mapN0ewt("N0ewt", TABLE_SIZE),
                          m_mapN1w("N1w", TABLE_SIZE),
                          m_mapN1t("N1t", TABLE_SIZE),
                          m_mapN1wt("N1wt", TABLE_SIZE),
                          m_mapN1bw("N1bw", TABLE_SIZE),
                          m_mapN1bt("N1bt", TABLE_SIZE),
                          m_mapN1bwt("N1bwt", TABLE_SIZE),
                          m_mapN1ew("N1ew", TABLE_SIZE),
                          m_mapN1et("N1et", TABLE_SIZE),
                          m_mapN1ewt("N1ewt", TABLE_SIZE),
                          m_mapN1sc("N1sc", TABLE_SIZE),
                          m_mapN2w("N2w", TABLE_SIZE),
                          m_mapN2t("N2t", TABLE_SIZE),
                          m_mapN2wt("N2wt", TABLE_SIZE),
                          m_mapN2bw("N2bw", TABLE_SIZE),
                          m_mapN2bt("N2bt", TABLE_SIZE),
                          m_mapN2bwt("N2bwt", TABLE_SIZE),
                          m_mapN2ew("N2ew", TABLE_SIZE),
                          m_mapN2et("N2et", TABLE_SIZE),
                          m_mapN2ewt("N2ewt", TABLE_SIZE),
                          m_mapN2sc("N2sc", TABLE_SIZE),
                          m_mapS0Lwc("S0Lwc", TABLE_SIZE),
                          m_mapS0Ltc("S0Ltc", TABLE_SIZE),
                          m_mapS0Rwc("S0Rwc", TABLE_SIZE),
                          m_mapS0Rtc("S0Rtc", TABLE_SIZE),
                          m_mapS0Uwc("S0Uwc", TABLE_SIZE),
                          m_mapS0Utc("S0Utc", TABLE_SIZE),
                          m_mapS1Lwc("S1Lwc", TABLE_SIZE),
                          m_mapS1Ltc("S1Ltc", TABLE_SIZE),
                          m_mapS1Rwc("S1Rwc", TABLE_SIZE),
                          m_mapS1Rtc("S1Rtc", TABLE_SIZE),
                          m_mapS1Uwc("S1Uwc", TABLE_SIZE),
                          m_mapS1Utc("S1Utc", TABLE_SIZE),
                          m_mapS0wS1w("S0wS1w", TABLE_SIZE),
                          m_mapS0wcS1wc("S0wcS1wc", TABLE_SIZE),
                          m_mapS0wcS1c("S0wcS1c", TABLE_SIZE),
                          m_mapS0cS1wc("S0cS1wc", TABLE_SIZE),
                          m_mapS0cS1c("S0cS1c", TABLE_SIZE),
                          m_mapS0tS1t("S0tS1t", TABLE_SIZE),
                          m_mapS0wtS1wt("S0wtS1wt", TABLE_SIZE),
                          m_mapS0S1HeadEDUSameSentence("S0S1HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS0S1Dist("S0S1Dist", TABLE_SIZE),
                          m_mapS0S1HeadEduSize("S0S1HeadEduSize", TABLE_SIZE),
                          m_mapS0scS1sc("S0scS1sc", TABLE_SIZE),
                          m_mapS0cS1sc("S0cS1sc", TABLE_SIZE),
                          m_mapS0scS1c("S0scS1c", TABLE_SIZE),
                          m_mapS0bwS1bw("S0bwS1bw", TABLE_SIZE),
                          m_mapS0bwtS1bwt("S0bwtS1bwt", TABLE_SIZE),
                          m_mapS0bwcS1bwc("S0bwcS1bwc", TABLE_SIZE),
                          m_mapS0bwtS1c("S0bwtS1c", TABLE_SIZE),
                          m_mapS0cS1bwt("S0cS1bwt", TABLE_SIZE),
                          m_mapS0btS1bt("S0btS1bt", TABLE_SIZE),
                          m_mapS0ewS1ew("S0ewS1ew", TABLE_SIZE),
                          m_mapS0ewtS1ewt("S0ewtS1ewt", TABLE_SIZE),
                          m_mapS0ewcS1ewc("S0ewcS1ewc", TABLE_SIZE),
                          m_mapS0ewtS1c("S0ewtS1c", TABLE_SIZE),
                          m_mapS0cS1ewt("S0cS1ewt", TABLE_SIZE),
                          m_mapS0etS1et("S0etS1et", TABLE_SIZE),
                          m_mapS0S1EDUNUMPairSize("S0S1EDUNUMPairSize", TABLE_SIZE),
                          m_mapS0SentBeginS1SentBegin("S0SentBeginS1SentBegin", TABLE_SIZE),
                          m_mapS0SentBeginS1SentEnd("S0SentBeginS1SentEnd", TABLE_SIZE),
                          m_mapS0SentEndS1SentBegin("S0SentEndS1SentBegin", TABLE_SIZE),
                          m_mapS0SentEndS1SentEnd("S0SentEndS1SentEnd", TABLE_SIZE),
                          m_mapS0ParaBeginS1ParaBegin("S0ParaBeginS1ParaBegin", TABLE_SIZE),
                          m_mapS0ParaBeginS1ParaEnd("S0ParaBeginS1ParaEnd", TABLE_SIZE),
                          m_mapS0ParaEndS1ParaBegin("S0ParaEndS1ParaBegin", TABLE_SIZE),
                          m_mapS0ParaEndS1ParaEnd("S0ParaEndS1ParaEnd", TABLE_SIZE),
                          m_mapS0wN0w("S0wN0w", TABLE_SIZE),
                          m_mapS0wtN0wt("S0wtN0wt", TABLE_SIZE),
                          m_mapS0wcN0wc("S0wcN0wc", TABLE_SIZE),
                          m_mapS0cN0wt("S0cN0wt", TABLE_SIZE),
                          m_mapS0wcN0t("S0wcN0t", TABLE_SIZE),
                          m_mapS0cN0t("S0cN0t", TABLE_SIZE),
                          m_mapS0tN0t("S0tN0t", TABLE_SIZE),
                          m_mapS0N0HeadEDUSameSentence("S0N0HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS0N0HeadEduSize("S0N0HeadEduSize", TABLE_SIZE),
                          m_mapS0scN0sc("S0scN0sc", TABLE_SIZE),
                          m_mapS0cN0sc("S0cN0sc", TABLE_SIZE),
                          m_mapS0scN0t("S0scN0t", TABLE_SIZE),
                          m_mapS0bwN0bw("S0bwN0bw", TABLE_SIZE),
                          m_mapS0bwtN0bwt("S0bwtN0bwt", TABLE_SIZE),
                          m_mapS0bwcN0bwc("S0bwcN0bwc", TABLE_SIZE),
                          m_mapS0bwtN0t("S0bwtN0t", TABLE_SIZE),
                          m_mapS0cN0bwt("S0cN0bwt", TABLE_SIZE),
                          m_mapS0btN0bt("S0btN0bt", TABLE_SIZE),
                          m_mapS0ewN0ew("S0ewN0ew", TABLE_SIZE),
                          m_mapS0ewtN0ewt("S0ewtN0ewt", TABLE_SIZE),
                          m_mapS0ewcN0ewc("S0ewcN0ewc", TABLE_SIZE),
                          m_mapS0ewtN0t("S0ewtN0t", TABLE_SIZE),
                          m_mapS0cN0ewt("S0cN0ewt", TABLE_SIZE),
                          m_mapS0etN0et("S0etN0et", TABLE_SIZE),
                          m_mapS0N0Dist("S0N0Dist", TABLE_SIZE),
                          m_mapS0SentBeginN0SentBegin("S0SentBeginN0SentBegin", TABLE_SIZE),
                          m_mapS0SentBeginN0SentEnd("S0SentBeginN0SentEnd", TABLE_SIZE),
                          m_mapS0SentEndN0SentBegin("S0SentEndN0SentBegin", TABLE_SIZE),
                          m_mapS0SentEndN0SentEnd("S0SentEndN0SentEnd", TABLE_SIZE),
                          m_mapS0ParaBeginN0ParaBegin("S0ParaBeginN0ParaBegin", TABLE_SIZE),
                          m_mapS0ParaBeginN0ParaEnd("S0ParaBeginN0ParaEnd", TABLE_SIZE),
                          m_mapS0ParaEndN0ParaBegin("S0ParaEndN0ParaBegin", TABLE_SIZE),
                          m_mapS0ParaEndN0ParaEnd("S0ParaEndN0ParaEnd", TABLE_SIZE),
                          m_mapS1wN0w("S1wN0w", TABLE_SIZE),
                          m_mapS1wtN0wt("S1wtN0wt", TABLE_SIZE),
                          m_mapS1wcN0wc("S1wcN0wc", TABLE_SIZE),
                          m_mapS1cN0wt("S1cN0wt", TABLE_SIZE),
                          m_mapS1wcN0t("S1wcN0t", TABLE_SIZE),
                          m_mapS1cN0t("S1cN0t", TABLE_SIZE),
                          m_mapS1tN0t("S1tN0t", TABLE_SIZE),
                          m_mapS1N0HeadEDUSameSentence("S1N0HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS1N0HeadEduSize("S1N0HeadEduSize", TABLE_SIZE),
                          m_mapS1scN0sc("S1scN0sc", TABLE_SIZE),
                          m_mapS1cN0sc("S1cN0sc", TABLE_SIZE),
                          m_mapS1scN0t("S1scN0t", TABLE_SIZE),
                          m_mapS1bwN0bw("S1bwN0bw", TABLE_SIZE),
                          m_mapS1bwtN0bwt("S1bwtN0bwt", TABLE_SIZE),
                          m_mapS1bwcN0bwc("S1bwcN0bwc", TABLE_SIZE),
                          m_mapS1bwtN0t("S1bwtN0t", TABLE_SIZE),
                          m_mapS1cN0bwt("S1cN0bwt", TABLE_SIZE),
                          m_mapS1btN0bt("S1btN0bt", TABLE_SIZE),
                          m_mapS1ewN0ew("S1ewN0ew", TABLE_SIZE),
                          m_mapS1ewtN0ewt("S1ewtN0ewt", TABLE_SIZE),
                          m_mapS1ewcN0ewc("S1ewcN0ewc", TABLE_SIZE),
                          m_mapS1ewtN0t("S1ewtN0t", TABLE_SIZE),
                          m_mapS1cN0ewt("S1cN0ewt", TABLE_SIZE),
                          m_mapS1etN0et("S1etN0et", TABLE_SIZE),
                          m_mapS1N0Dist("S1N0Dist", TABLE_SIZE),
                          m_mapS1SentBeginN0SentBegin("S1SentBeginN0SentBegin", TABLE_SIZE),
                          m_mapS1SentBeginN0SentEnd("S1SentBeginN0SentEnd", TABLE_SIZE),
                          m_mapS1SentEndN0SentBegin("S1SentEndN0SentBegin", TABLE_SIZE),
                          m_mapS1SentEndN0SentEnd("S1SentEndN0SentEnd", TABLE_SIZE),
                          m_mapS1ParaBeginN0ParaBegin("S1ParaBeginN0ParaBegin", TABLE_SIZE),
                          m_mapS1ParaBeginN0ParaEnd("S1ParaBeginN0ParaEnd", TABLE_SIZE),
                          m_mapS1ParaEndN0ParaBegin("S1ParaEndN0ParaBegin", TABLE_SIZE),
                          m_mapS1ParaEndN0ParaEnd("S1ParaEndN0ParaEnd", TABLE_SIZE),
                          m_mapS1wS2w("S1wS2w", TABLE_SIZE),
                          m_mapS1wcS2wc("S1wcS2wc", TABLE_SIZE),
                          m_mapS1wcS2c("S1wcS2c", TABLE_SIZE),
                          m_mapS1cS2wc("S1cS2wc", TABLE_SIZE),
                          m_mapS1cS2c("S1cS2c", TABLE_SIZE),
                          m_mapS1tS2t("S1tS2t", TABLE_SIZE),
                          m_mapS1wtS2wt("S1wtS2wt", TABLE_SIZE),
                          m_mapS1S2HeadEDUSameSentence("S1S2HeadEDUSameSentence", TABLE_SIZE),
                          m_mapS1S2Dist("S1S2Dist", TABLE_SIZE),
                          m_mapS1S2HeadEduSize("S1S2HeadEduSize", TABLE_SIZE),
                          m_mapS1scS2sc("S1scS2sc", TABLE_SIZE),
                          m_mapS1cS2sc("S1cS2sc", TABLE_SIZE),
                          m_mapS1scS2c("S1scS2c", TABLE_SIZE),
                          m_mapS1bwS2bw("S1bwS2bw", TABLE_SIZE),
                          m_mapS1bwtS2bwt("S1bwtS2bwt", TABLE_SIZE),
                          m_mapS1bwcS2bwc("S1bwcS2bwc", TABLE_SIZE),
                          m_mapS1bwtS2c("S1bwtS2c", TABLE_SIZE),
                          m_mapS1cS2bwt("S1cS2bwt", TABLE_SIZE),
                          m_mapS1btS2bt("S1btS2bt", TABLE_SIZE),
                          m_mapS1ewS2ew("S1ewS2ew", TABLE_SIZE),
                          m_mapS1ewtS2ewt("S1ewtS2ewt", TABLE_SIZE),
                          m_mapS1ewcS2ewc("S1ewcS2ewc", TABLE_SIZE),
                          m_mapS1ewtS2c("S1ewtS2c", TABLE_SIZE),
                          m_mapS1cS2ewt("S1cS2ewt", TABLE_SIZE),
                          m_mapS1etS2et("S1etS2et", TABLE_SIZE),
                          m_mapS1SentBeginS2SentBegin("S1SentBeginS2SentBegin", TABLE_SIZE),
                          m_mapS1SentBeginS2SentEnd("S1SentBeginS2SentEnd", TABLE_SIZE),
                          m_mapS1SentEndS2SentBegin("S1SentEndS2SentBegin", TABLE_SIZE),
                          m_mapS1SentEndS2SentEnd("S1SentEndS2SentEnd", TABLE_SIZE),
                          m_mapS1ParaBeginS2ParaBegin("S1ParaBeginS2ParaBegin", TABLE_SIZE),
                          m_mapS1ParaBeginS2ParaEnd("S1ParaBeginS2ParaEnd", TABLE_SIZE),
                          m_mapS1ParaEndS2ParaBegin("S1ParaEndS2ParaBegin", TABLE_SIZE),
                          m_mapS1ParaEndS2ParaEnd("S1ParaEndS2ParaEnd", TABLE_SIZE),
                          m_mapN0wN1w("N0wN1w", TABLE_SIZE),
                          m_mapN0wtN1wt("N0wtN1wt", TABLE_SIZE),
                          m_mapN0tN1wt("N0tN1wt", TABLE_SIZE),
                          m_mapN0wtN1t("N0wtN1t", TABLE_SIZE),
                          m_mapN0tN1t("N0tN1t", TABLE_SIZE),
                          m_mapN0N1HeadEduSize("N0N1HeadEduSize", TABLE_SIZE),
                          m_mapN0scN1sc("N0scN1sc", TABLE_SIZE),
                          m_mapN0tN1sc("N0tN1sc", TABLE_SIZE),
                          m_mapN0scN1t("N0scN1t", TABLE_SIZE),
                          m_mapN0bwN1bw("N0bwN1bw", TABLE_SIZE),
                          m_mapN0bwtN1bwt("N0bwtN1bwt", TABLE_SIZE),
                          m_mapN0bwtN1t("N0bwtN1t", TABLE_SIZE),
                          m_mapN0tN1bwt("N0tN1bwt", TABLE_SIZE),
                          m_mapN0btN1bt("N0btN1bt", TABLE_SIZE),
                          m_mapN0ewN1ew("N0ewN1ew", TABLE_SIZE),
                          m_mapN0ewtN1ewt("N0ewtN1ewt", TABLE_SIZE),
                          m_mapN0ewtN1t("N0ewtN1t", TABLE_SIZE),
                          m_mapN0tN1ewt("N0tN1ewt", TABLE_SIZE),
                          m_mapN0etN1et("N0etN1et", TABLE_SIZE),
                          m_mapS0wS1cN0t("S0wS1cN0t", TABLE_SIZE),
                          m_mapS0cS1wN0t("S0cS1wN0t", TABLE_SIZE),
                          m_mapS0cS1cN0w("S0cS1cN0w", TABLE_SIZE),
                          m_mapS0cS1cN0t("S0cS1cN0t", TABLE_SIZE),
                          m_mapS0tS1tN0t("S0tS1tN0t", TABLE_SIZE),
                          m_mapS0scS1scN0sc("S0scS1scN0sc", TABLE_SIZE),
                          m_mapS0btS1btN0bt("S0btS1btN0bt", TABLE_SIZE),
                          m_mapS0etS1etN0et("S0etS1etN0et", TABLE_SIZE),
                          m_mapS0wN0tN1t("S0wN0tN1t", TABLE_SIZE),
                          m_mapS0cN0wN1t("S0cN0wN1t", TABLE_SIZE),
                          m_mapS0cN0tN1w("S0cN0tN1w", TABLE_SIZE),
                          m_mapS0cN0tN1t("S0cN0tN1t", TABLE_SIZE),
                          m_mapS0tN0tN1t("S0tN0tN1t", TABLE_SIZE),
                          m_mapS0jN0tN1t("S0jN0tN1t", TABLE_SIZE),
                          m_mapS0scN0scN1sc("S0scN0scN1sc", TABLE_SIZE),
                          m_mapS0btN0btN1bt("S0btN0btN1bt", TABLE_SIZE),
                          m_mapS0etN0etN1et("S0etN0etN1et", TABLE_SIZE),
                          m_mapS0wS1cS2c("S0wS1cS2c", TABLE_SIZE),
                          m_mapS0cS1wS2c("S0cS1wS2c", TABLE_SIZE),
                          m_mapS0cS1cS2w("S0cS1cS2w", TABLE_SIZE),
                          m_mapS0cS1cS2c("S0cS1cS2c", TABLE_SIZE),
                          m_mapS0tS1tS2t("S0tS1tS2t", TABLE_SIZE),
                          m_mapS0scS1scS2sc("S0scS1scS2sc", TABLE_SIZE),
                          m_mapS0btS1btS2bt("S0btS1btS2bt", TABLE_SIZE),
                          m_mapS0etS1etS2et("S0etS1etS2et", TABLE_SIZE),
                          m_mapS0cS0RcN0t("S0cS0RcN0t", TABLE_SIZE),
                          m_mapS0cS0RjN0t("S0cS0RjN0t", TABLE_SIZE),
                          m_mapS0cS0RcN0w("S0cS0RcN0w", TABLE_SIZE),
                          m_mapS0cS0LcN0t("S0cS0LcN0t", TABLE_SIZE),
                          m_mapS0wS0LcN0t("S0wS0LcN0t", TABLE_SIZE),
                          m_mapS0cS0LcN0w("S0cS0LcN0w", TABLE_SIZE),
                          m_mapS0wS0RcN0t("S0wS0RcN0t", TABLE_SIZE),
                          m_mapS0cS0UcN0t("S0cS0UcN0t", TABLE_SIZE),
                          m_mapS0wS0UcN0t("S0wS0UcN0t", TABLE_SIZE),
                          m_mapS0cS0UcN0w("S0cS0UcN0w", TABLE_SIZE),
                          m_mapS0cS0LcS1c("S0cS0LcS1c", TABLE_SIZE),
                          m_mapS0cS0LjS1j("S0cS0LjS1j", TABLE_SIZE),
                          m_mapS0cS0LcS1w("S0cS0LcS1w", TABLE_SIZE),
                          m_mapS0wS0LcS1c("S0wS0LcS1c", TABLE_SIZE),
                          m_mapS0cS0RcS1c("S0cS0RcS1c", TABLE_SIZE),
                          m_mapS0wS0RcS1c("S0wS0RcS1c", TABLE_SIZE),
                          m_mapS0cS0RcS1w("S0cS0RcS1w", TABLE_SIZE),
                          m_mapS0cS0UcS1c("S0cS0UcS1c", TABLE_SIZE),
                          m_mapS0wS0UcS1c("S0wS0UcS1c", TABLE_SIZE),
                          m_mapS0cS0UcS1w("S0cS0UcS1w", TABLE_SIZE),
                          m_mapS0cS1cS1Rc("S0cS1cS1Rc", TABLE_SIZE),
                          m_mapS0jS1cS1Rj("S0jS1cS1Rj", TABLE_SIZE),
                          m_mapS0wS1cS1Rc("S0wS1cS1Rc", TABLE_SIZE),
                          m_mapS0cS1cS1Lc("S0cS1cS1Lc", TABLE_SIZE),
                          m_mapS0wS1cS1Lc("S0wS1cS1Lc", TABLE_SIZE),
                          m_mapS0cS1wS1Lc("S0cS1wS1Lc", TABLE_SIZE),
                          m_mapS0cS1wS1Rc("S0cS1wS1Rc", TABLE_SIZE),
                          m_mapS0cS1cS1Uc("S0cS1cS1Uc", TABLE_SIZE),
                          m_mapS0wS1cS1Uc("S0wS1cS1Uc", TABLE_SIZE),
                          m_mapS0cS1wS1Uc("S0cS1wS1Uc", TABLE_SIZE),
                          m_mapA1("A1", TABLE_SIZE),
                          m_mapA1A2("A1A2", TABLE_SIZE),
						  m_mapS0AllWord("S0AllWord", TABLE_SIZE),
						  m_mapS1AllWord("S1AllWord", TABLE_SIZE),
						  m_mapN0AllWord("N0AllWord", TABLE_SIZE){ }
   ~CWeight() {
//      iterate_templates(,.freePoolMemory(););
//      CPackedScore<SCORE_TYPE, CAction::MAX>::freePoolMemory();
   }

   // MEHTODS
   virtual void loadScores(std::ifstream &is);
   virtual void saveScores(std::ofstream &os);
   void computeAverageFeatureWeights(int round);
   SCORE_TYPE dotProduct(CWeight &w);
   void clear() {
      iterate_templates(,.clear(););
   }
   void addCurrent(CWeight*w, int round);
   void subtractCurrent(CWeight*w, int round);
   void scaleCurrent(const SCORE_TYPE &scale, const int &round) {
      iterate_templates(,ID(.scaleCurrent(scale, round);));
   }
   SCORE_TYPE squareNorm() {
      static SCORE_TYPE retval;
      retval = 0;
      iterate_templates(retval+=,.squareNorm(););
      return retval;
   }
 
};

};
};

#endif
