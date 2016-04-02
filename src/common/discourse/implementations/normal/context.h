// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * context.h - the definition of context                        *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

class CStateNode; 
class CStateItem;

const CConstituent g_noneConstituent(CConstituent::NONE);
const CConstituent g_beginConstituent(CConstituent::SENTENCE_BEGIN);
const CDisConstituent g_noneDisConstituent(CDisConstituent::NONE);
const CDisConstituent g_beginDisConstituent(CDisConstituent::SENTENCE_BEGIN);
const CTag g_noneTag(CTag::NONE);
const CWord g_emptyWord("");

//#define constituent_or_none(x) ((x).is_constituent() ? (x).constituent.code() : CConstituent::NONE)
#define constituent_or_none(x) ((x).constituent.code())


//===============================================================
//
// CContext 
//
//===============================================================

class CContext {
public:
   const CDisNode *s0, *s1, *s2, *s3;
   const CDisNode *s0l, *s0r, *s0u;
   const CDisNode *s1l, *s1r, *s1u;
   int n0, n1, n2, n3;
   int n0b1, n1b1, n2b1, n3b1, n0b2, n1b2, n2b2, n3b2;
   int n0e1, n1e1, n2e1, n3e1, n0e2, n1e2, n2e2, n3e2;
   int s0b1, s1b1, s2b1, s3b1, s0b2, s1b2, s2b2, s3b2;
   int s0e1, s1e1, s2e1, s3e1, s0e2, s1e2, s2e2, s3e2;
   int s0ld, s0rd;
   int s1ld, s1rd;

   const CWord *s0w, *s1w, *s2w, *s3w;
   CDisConstituent s0c, s1c, s2c, s3c;
   CTag s0t, s1t, s2t, s3t;
   CConstituent s0sc, s1sc, s2sc, s3sc;
   const CTaggedWord<CTag, TAG_SEPARATOR> *s0wt, *s1wt, *s2wt, *s3wt;

   const CWord *s0b1w, *s1b1w, *s2b1w, *s3b1w;
   const CWord *s0b2w, *s1b2w, *s2b2w, *s3b2w;
   const CWord *s0e1w, *s1e1w, *s2e1w, *s3e1w;
   const CWord *s0e2w, *s1e2w, *s2e2w, *s3e2w;
   CTag s0b1t, s1b1t, s2b1t, s3b1t;
   CTag s0b2t, s1b2t, s2b2t, s3b2t;
   CTag s0e1t, s1e1t, s2e1t, s3e1t;
   CTag s0e2t, s1e2t, s2e2t, s3e2t;
   const CTaggedWord<CTag, TAG_SEPARATOR> *s0b1wt, *s1b1wt, *s2b1wt, *s3b1wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *s0b2wt, *s1b2wt, *s2b2wt, *s3b2wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *s0e1wt, *s1e1wt, *s2e1wt, *s3e1wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *s0e2wt, *s1e2wt, *s2e2wt, *s3e2wt;

   const CWord *n0b1w, *n1b1w, *n2b1w, *n3b1w;
   const CWord *n0b2w, *n1b2w, *n2b2w, *n3b2w;
   const CWord *n0e1w, *n1e1w, *n2e1w, *n3e1w;
   const CWord *n0e2w, *n1e2w, *n2e2w, *n3e2w;
   CTag n0b1t, n1b1t, n2b1t, n3b1t;
   CTag n0b2t, n1b2t, n2b2t, n3b2t;
   CTag n0e1t, n1e1t, n2e1t, n3e1t;
   CTag n0e2t, n1e2t, n2e2t, n3e2t;
   const CTaggedWord<CTag, TAG_SEPARATOR> *n0b1wt, *n1b1wt, *n2b1wt, *n3b1wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *n0b2wt, *n1b2wt, *n2b2wt, *n3b2wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *n0e1wt, *n1e1wt, *n2e1wt, *n3e1wt;
   const CTaggedWord<CTag, TAG_SEPARATOR> *n0e2wt, *n1e2wt, *n2e2wt, *n3e2wt;

   const CWord *n0w, *n1w, *n2w, *n3w;
   CTag n0t, n1t, n2t, n3t;
   CConstituent n0sc, n1sc, n2sc, n3sc;
   const CTaggedWord<CTag, TAG_SEPARATOR>  *n0wt, *n1wt, *n2wt, *n3wt;


   const CWord *s0lw, *s0rw, *s1lw, *s1rw;
   CDisConstituent s0lc, s0rc;
   CConstituent s0lsc, s0rsc;
   CTag s0lt, s0rt;
   CDisConstituent s1lc, s1rc;
   CConstituent s1lsc, s1rsc;
   CTag s1lt, s1rt;


   const CTaggedWord<CTag, TAG_SEPARATOR> *s0lwt, *s0rwt, *s0uwt, *s1lwt, *s1rwt, *s1uwt;

   unsigned long stacksize;

   CDISCFGSet s0ts1t, n0tn1t, s0tn0t, s1tn0t, s1ts2t,
              s0bts1bt, n0btn1bt, s0btn0bt, s1btn0bt, s1bts2bt,
              s0ets1et, n0etn1et, s0etn0et, s1etn0et, s1ets2et,
              s0cs1c,  s0cn0t, s1cn0t, s1cs2c,
              s0cs1bt, s0bts1c, s0cs1et, s0ets1c,
              s1cs2bt, s1bts2c, s1cs2et, s1ets2c,
              s0cn0bt, s0btn0t, s0cn0et, s0etn0t,
              s1cn0bt, s1btn0t, s1cn0et, s1etn0t,
              n0tn1bt, n0btn1t, n0tn1et, n0etn1t;

   CDISCFGSet s0scs1sc, s0scs1c, s0cs1sc, s0scn0sc, s0cn0sc, s0scn0t,
              s1scn0sc, s1cn0sc, s1scn0t, n0scn1sc, n0tn1sc, n0scn1t,
              s1scs2sc, s1scs2c, s1cs2sc,
              s0scs1scn0sc, s0scn0scn1sc, s0scs1scs2sc;

   CDISCFGSet s0cs1cn0t, s0cn0tn1t, s0cs1cs2c,
              s0ts1tn0t, s0tn0tn1t, s0ts1ts2t,
              s0js1jn0t, s0jn0tn1t, s0js1js2j;

   CDISCFGSet s0scs1bt, s0scs1et, s0bts1sc, s0ets1sc,
              s0scn0bt, s0scn0et, s1scn0bt, s1scn0et,
              s1scs2bt, s1scs2et, s1bts2sc, s1ets2sc;

   CDISCFGSet s0bts1btn0bt, s0ets1etn0et, s0btn0btn1bt, s0etn0etn1et, s0bts1bts2bt, s0ets1ets2et;
   // here j means the combination of c and t -- t with non-constituent
   CDISCFGSet s0cs0lc, s0cs0rc, s1cs1rc,
              s0cs0rcn0t, s0cs0rjn0t, s0cs0lcs1c, s0cs0ljs1j, s0cs1cs1rc, s0js1cs1rj;

   CTwoWords s0ws1w, s0wn0w, n0wn1w, s1wn0w, s1ws2w,
             s0bws1bw, s0bwn0bw, n0bwn1bw, s1bwn0bw, s1bws2bw,
             s0ews1ew, s0ewn0ew, n0ewn1ew, s1ewn0ew, s1ews2ew;

   unsigned long s0m, s1m, s2m, n0m, n1m, n2m; //head span match: first, left, right, exact, unmatch

   unsigned long s0s1_dist, s1s2_dist, s0n0_dist, s1n0_dist;
   unsigned long s0s1_type, s1s2_type, s0n0_type, s1n0_type; // in same sentence, paragraph?
   unsigned long s0length, s1length, s2length, n0length, n1length;
   unsigned long s0edunum, s1edunum;
   unsigned long s0_sent_begin_dist, s1_sent_begin_dist, s2_sent_begin_dist, n0_sent_begin_dist,
                 s0_sent_end_dist, s1_sent_end_dist, s2_sent_end_dist, n0_sent_end_dist;

   unsigned long s0_para_begin_dist, s1_para_begin_dist, s2_para_begin_dist, n0_para_begin_dist,
                 s0_para_end_dist, s1_para_end_dist, s2_para_end_dist, n0_para_end_dist;

//public:
//   CContext() {}
//   ~CContext() {}
public:
   bool load(const CStateItem *item, const bool &modify) {

	   //will be added after decoding can be run through.

	  stacksize = item->stacksize();
      //if (stacksize==0) return; // must shift; no feature updates, no comparisons for different actions
      static int tmp_i;
      static int i, j;
      n0 = item->current_edu >= (*item->m_edu_starts).size() ? -1 : item->current_edu;
      n1 = item->current_edu+1 >= (*item->m_edu_starts).size() ? -1 : item->current_edu+1;
      if( n1 != -1 && (*item->m_edu_sentids)[n1] != (*item->m_edu_sentids)[n0]) n1 = -1;
      n2 = item->current_edu+2 >= (*item->m_edu_starts).size() ? -1 : item->current_edu+2;
      if( n2 != -1 && (*item->m_edu_sentids)[n2] != (*item->m_edu_sentids)[n0]) n2 = -1;
      n3 = item->current_edu+3 >= (*item->m_edu_starts).size() ? -1 : item->current_edu+3;
      if( n3 != -1 && (*item->m_edu_sentids)[n3] != (*item->m_edu_sentids)[n0]) n3 = -1;

      n0b1 = n0==-1 ? -1 : (*item->m_edu_starts)[n0];
      n0e1 = n0==-1 ? -1 : (*item->m_edu_ends)[n0];
      if(n0e1!=-1&&(*item->m_sent)[n0e1].tag == 0)n0e1--;
      n0b2 = n0==-1||n0b1==n0e1? -1 : n0b1+1;
      n0e2 = n0==-1||n0b1==n0e1? -1 : n0e1-1;

      n1b1 = n1==-1 ? -1 : (*item->m_edu_starts)[n1];
      n1e1 = n1==-1 ? -1 : (*item->m_edu_ends)[n1];
      if(n1e1!=-1&&(*item->m_sent)[n1e1].tag == 0)n1e1--;
      n1b2 = n1==-1||n1b1==n1e1? -1 : n1b1+1;
      n1e2 = n1==-1||n1b1==n1e1? -1 : n1e1-1;

      n2b1 = n2==-1 ? -1 : (*item->m_edu_starts)[n2];
      n2e1 = n2==-1 ? -1 : (*item->m_edu_ends)[n2];
      if(n2e1!=-1&&(*item->m_sent)[n2e1].tag == 0)n2e1--;
      n2b2 = n2==-1||n2b1==n2e1? -1 : n2b1+1;
      n2e2 = n2==-1||n2b1==n2e1? -1 : n2e1-1;

      n3b1 = n3==-1 ? -1 : (*item->m_edu_starts)[n3];
      n3e1 = n3==-1 ? -1 : (*item->m_edu_ends)[n3];
      if(n3e1!=-1&&(*item->m_sent)[n3e1].tag == 0)n3e1--;
      n3b2 = n3==-1||n3b1==n3e1? -1 : n3b1+1;
      n3e2 = n3==-1||n3b1==n3e1? -1 : n3e1-1;

      s0 = stacksize<1 ? 0 : &(item->node);
      s1 = stacksize<2 ? 0 : &(item->stackPtr->node);
      s2 = stacksize<3 ? 0 : &(item->stackPtr->stackPtr->node);
      s3 = stacksize<4 ? 0 : &(item->stackPtr->stackPtr->stackPtr->node);

      s0b1 = s0==0 ? -1 : s0->headword_start;
      s0e1 = s0==0 ? -1 : s0->headword_end;
      if(s0e1!=-1&&(*item->m_sent)[s0e1].tag == 0)s0e1--;
      s0b2 = s0==0||s0b1==s0e1 ? -1 : s0b1+1;
      s0e2 = s0==0||s0b1==s0e1 ? -1 : s0e1-1;

      s1b1 = s1==0 ? -1 : s1->headword_start;
      s1e1 = s1==0 ? -1 : s1->headword_end;
      if(s1e1!=-1&&(*item->m_sent)[s1e1].tag == 0)s1e1--;
      s1b2 = s1==0||s1b1==s1e1 ? -1 : s1b1+1;
      s1e2 = s1==0||s1b1==s1e1 ? -1 : s1e1-1;

      s2b1 = s2==0 ? -1 : s2->headword_start;
      s2e1 = s2==0 ? -1 : s2->headword_end;
      if(s2e1!=-1&&(*item->m_sent)[s2e1].tag == 0)s2e1--;
      s2b2 = s2==0||s2b1==s2e1 ? -1 : s2b1+1;
      s2e2 = s2==0||s2b1==s2e1 ? -1 : s2e1-1;

      s3b1 = s3==0 ? -1 : s3->headword_start;
      s3e1 = s3==0 ? -1 : s3->headword_end;
      if(s3e1!=-1&&(*item->m_sent)[s3e1].tag == 0)s3e1--;
      s3b2 = s3==0||s3b1==s3e1 ? -1 : s3b1+1;
      s3e2 = s3==0||s3b1==s3e1 ? -1 : s3e1-1;

      s0l = s0==0 ? 0 : ( s0->is_constituent() ? (s0->head_left() ? 0 : s0->left_child) : 0 );
      s0r = s0==0 ? 0 : ( s0->is_constituent() ? (!s0->head_left() ? 0 : s0->right_child) : 0 );

      s1l = s1==0 ? 0 : ( s1->is_constituent() ? (s1->head_left() ? 0 : s1->left_child) : 0 );
      s1r = s1==0 ? 0 : ( s1->is_constituent() ? (!s1->head_left() ? 0 : s1->right_child) : 0 );
   
      const CConNode* s0syn = s0 == 0 ? 0 : s0->headspans[0];
      s0c.load(  s0==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s0) );
      s0wt = s0 == 0 ? 0 : &((*item->m_sent)[s0syn->headword] );
      s0w = s0 == 0 ? &g_emptyWord : &(s0wt->word);
      s0t = s0 == 0 ? g_noneTag : s0wt->tag;
      s0sc.load(  s0==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s0syn) );
   
      const CConNode* s1syn = s1 == 0 ? 0 : s1->headspans[0];
      s1c.load( s1==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s1) );
      s1wt = s1 == 0 ? 0 : &( (*item->m_sent)[s1syn->headword] );
      s1w = s1 == 0 ? &g_emptyWord : &(s1wt->word);
      s1t = s1 == 0 ? g_noneTag : s1wt->tag;
      s1sc.load( s1==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s1syn) );

      const CConNode* s2syn = s2 == 0 ? 0 : s2->headspans[0];
      s2c.load( s2==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s2) );
      s2wt = s2 == 0 ? 0 : &( (*item->m_sent)[s2syn->headword] );
      s2w = s2 == 0 ? &g_emptyWord : &(s2wt->word);
      s2t = s2 == 0 ? g_noneTag : s2wt->tag;
      s2sc.load( s2==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s2syn) );

      const CConNode* s3syn = s3 == 0 ? 0 : s3->headspans[0];
      s3c.load( s3==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s3) );
      s3wt = s3 == 0 ? 0 : &( (*item->m_sent)[s3syn->headword] );
      s3w = s3 == 0 ? &g_emptyWord : &(s3wt->word);
      s3t = s3 == 0 ? g_noneTag : s3wt->tag;
      s3sc.load( s3==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s3syn) );


      const CConNode* s0lsyn = s0l == 0 ? 0 : s0l->headspans[0];
      s0lc.load( s0l==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s0l) );
      s0lwt = s0l == 0 ? 0 : &( (*item->m_sent)[s0lsyn->headword] );
      s0lw = s0l == 0 ? &g_emptyWord : &(s0lwt->word);
      s0lt = s0l == 0 ? g_noneTag : s0lwt->tag;
      s0lsc.load( s0l==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s0lsyn) );

      const CConNode* s0rsyn = s0r == 0 ? 0 : s0r->headspans[0];
      s0rc.load( s0r==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s0r) );
      s0rwt = s0r == 0 ? 0 : &( (*item->m_sent)[s0rsyn->headword] );
      s0rw = s0r == 0 ? &g_emptyWord : &(s0rwt->word);
      s0rt = s0r == 0 ? g_noneTag : s0rwt->tag;
      s0rsc.load( s0r==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s0rsyn) );

      const CConNode* s1lsyn = s1l == 0 ? 0 : s1l->headspans[0];
      s1lc.load( s1l==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s1l) );
      s1lwt = s1l == 0 ? 0 : &( (*item->m_sent)[s1lsyn->headword] );
      s1lw = s1l == 0 ? &g_emptyWord : &(s1lwt->word);
      s1lt = s1l == 0 ? g_noneTag : s1lwt->tag;
      s1lsc.load( s1l==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s1lsyn) );

      const CConNode* s1rsyn = s1r == 0 ? 0 : s1r->headspans[0];
      s1rc.load( s1r==0 ? CDisConstituent::SENTENCE_BEGIN : constituent_or_none(*s1r) );
      s1rwt = s1r == 0 ? 0 : &( (*item->m_sent)[s1rsyn->headword] );
      s1rw = s1r == 0 ? &g_emptyWord : &(s1rwt->word);
      s1rt = s1r == 0 ? g_noneTag : s1rwt->tag;
      s1rsc.load( s1r==0 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*s1rsyn) );

      const CConNode* n0syn = n0 == -1 ? 0 : (*item->m_edu_headspans)[n0][0];
      n0wt = n0 == -1 ? 0 : &( (*item->m_sent)[n0syn->headword]);
      n0t = n0==-1 ? g_noneTag : n0wt->tag;
      n0w = n0 == -1 ? 0 : &(n0wt->word);
      n0sc.load(n0==-1 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*n0syn));

      const CConNode* n1syn = n1 == -1 ? 0 : (*item->m_edu_headspans)[n1][0];
      n1wt = n1 == -1 ? 0 : &((*item->m_sent)[n1syn->headword]);
      n1t = n1==-1 ? g_noneTag : n1wt->tag;
      n1w = n1 == -1 ? 0 : &(n1wt->word);
      n1sc.load(n1==-1 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*n1syn));

      const CConNode* n2syn = n2 == -1 ? 0 : (*item->m_edu_headspans)[n2][0];
      n2wt = n2 == -1 ? 0 : &( (*item->m_sent)[n2syn->headword]);
      n2t = n2==-1 ? g_noneTag : n2wt->tag;
      n2w = n2 == -1 ? 0 : &(n2wt->word);
      n2sc.load(n2==-1 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*n2syn));

      const CConNode* n3syn = n3 == -1 ? 0 : (*item->m_edu_headspans)[n3][0];
      n3wt = n3 == -1 ? 0 : &((*item->m_sent)[n3syn->headword]);
      n3t = n3==-1 ? g_noneTag : n3wt->tag;
      n3w = n3 == -1 ? 0 : &(n3wt->word);
      n3sc.load(n3==-1 ? CConstituent::SENTENCE_BEGIN : constituent_or_none(*n3syn));

      s0b1wt = s0b1==-1 ? 0 : &((*item->m_sent)[s0b1]);
      s0b1t = s0b1==-1 ? g_noneTag : s0b1wt->tag;
      s0b1w = s0b1==-1 ? 0 : &(s0b1wt->word);
      s0b2wt = s0b2==-1 ? 0 : &((*item->m_sent)[s0b2]);
      s0b2t = s0b2==-1 ? g_noneTag : s0b2wt->tag;
      s0b2w = s0b2==-1 ? 0 : &(s0b2wt->word);
      s0e1wt = s0e1==-1 ? 0 : &((*item->m_sent)[s0e1]);
      s0e1t = s0e1==-1 ? g_noneTag : s0e1wt->tag;
      s0e1w = s0e1==-1 ? 0 : &(s0e1wt->word);
      s0e2wt = s0e2==-1 ? 0 : &((*item->m_sent)[s0e2]);
      s0e2t = s0e2==-1 ? g_noneTag : s0e2wt->tag;
      s0e2w = s0e2==-1 ? 0 : &(s0e2wt->word);

      s1b1wt = s1b1==-1 ? 0 : &((*item->m_sent)[s1b1]);
      s1b1t = s1b1==-1 ? g_noneTag : s1b1wt->tag;
      s1b1w = s1b1==-1 ? 0 : &(s1b1wt->word);
      s1b2wt = s1b2==-1 ? 0 : &((*item->m_sent)[s1b2]);
      s1b2t = s1b2==-1 ? g_noneTag : s1b2wt->tag;
      s1b2w = s1b2==-1 ? 0 : &(s1b2wt->word);
      s1e1wt = s1e1==-1 ? 0 : &((*item->m_sent)[s1e1]);
      s1e1t = s1e1==-1 ? g_noneTag : s1e1wt->tag;
      s1e1w = s1e1==-1 ? 0 : &(s1e1wt->word);
      s1e2wt = s1e2==-1 ? 0 : &((*item->m_sent)[s1e2]);
      s1e2t = s1e2==-1 ? g_noneTag : s1e2wt->tag;
      s1e2w = s1e2==-1 ? 0 : &(s1e2wt->word);

      s2b1wt = s2b1==-1 ? 0 : &((*item->m_sent)[s2b1]);
      s2b1t = s2b1==-1 ? g_noneTag : s2b1wt->tag;
      s2b1w = s2b1==-1 ? 0 : &(s2b1wt->word);
      s2b2wt = s2b2==-1 ? 0 : &((*item->m_sent)[s2b2]);
      s2b2t = s2b2==-1 ? g_noneTag : s2b2wt->tag;
      s2b2w = s2b2==-1 ? 0 : &(s2b2wt->word);
      s2e1wt = s2e1==-1 ? 0 : &((*item->m_sent)[s2e1]);
      s2e1t = s2e1==-1 ? g_noneTag : s2e1wt->tag;
      s2e1w = s2e1==-1 ? 0 : &(s2e1wt->word);
      s2e2wt = s2e2==-1 ? 0 : &((*item->m_sent)[s2e2]);
      s2e2t = s2e2==-1 ? g_noneTag : s2e2wt->tag;
      s2e2w = s2e2==-1 ? 0 : &(s2e2wt->word);

      s3b1wt = s3b1==-1 ? 0 : &((*item->m_sent)[s3b1]);
      s3b1t = s3b1==-1 ? g_noneTag : s3b1wt->tag;
      s3b1w = s3b1==-1 ? 0 : &(s3b1wt->word);
      s3b2wt = s3b2==-1 ? 0 : &((*item->m_sent)[s3b2]);
      s3b2t = s3b2==-1 ? g_noneTag : s3b2wt->tag;
      s3b2w = s3b2==-1 ? 0 : &(s3b2wt->word);
      s3e1wt = s3e1==-1 ? 0 : &((*item->m_sent)[s3e1]);
      s3e1t = s3e1==-1 ? g_noneTag : s3e1wt->tag;
      s3e1w = s3e1==-1 ? 0 : &(s3e1wt->word);
      s3e2wt = s3e2==-1 ? 0 : &((*item->m_sent)[s3e2]);
      s3e2t = s3e2==-1 ? g_noneTag : s3e2wt->tag;
      s3e2w = s3e2==-1 ? 0 : &(s3e2wt->word);

      n0b1wt = n0b1==-1 ? 0 : &((*item->m_sent)[n0b1]);
      n0b1t = n0b1==-1 ? g_noneTag : n0b1wt->tag;
      n0b1w = n0b1==-1 ? 0 : &(n0b1wt->word);
      n0b2wt = n0b2==-1 ? 0 : &((*item->m_sent)[n0b2]);
      n0b2t = n0b2==-1 ? g_noneTag : n0b2wt->tag;
      n0b2w = n0b2==-1 ? 0 : &(n0b2wt->word);
      n0e1wt = n0e1==-1 ? 0 : &((*item->m_sent)[n0e1]);
      n0e1t = n0e1==-1 ? g_noneTag : n0e1wt->tag;
      n0e1w = n0e1==-1 ? 0 : &(n0e1wt->word);
      n0e2wt = n0e2==-1 ? 0 : &((*item->m_sent)[n0e2]);
      n0e2t = n0e2==-1 ? g_noneTag : n0e2wt->tag;
      n0e2w = n0e2==-1 ? 0 : &(n0e2wt->word);

      n1b1wt = n1b1==-1 ? 0 : &((*item->m_sent)[n1b1]);
      n1b1t = n1b1==-1 ? g_noneTag : n1b1wt->tag;
      n1b1w = n1b1==-1 ? 0 : &(n1b1wt->word);
      n1b2wt = n1b2==-1 ? 0 : &((*item->m_sent)[n1b2]);
      n1b2t = n1b2==-1 ? g_noneTag : n1b2wt->tag;
      n1b2w = n1b2==-1 ? 0 : &(n1b2wt->word);
      n1e1wt = n1e1==-1 ? 0 : &((*item->m_sent)[n1e1]);
      n1e1t = n1e1==-1 ? g_noneTag : n1e1wt->tag;
      n1e1w = n1e1==-1 ? 0 : &(n1e1wt->word);
      n1e2wt = n1e2==-1 ? 0 : &((*item->m_sent)[n1e2]);
      n1e2t = n1e2==-1 ? g_noneTag : n1e2wt->tag;
      n1e2w = n1e2==-1 ? 0 : &(n1e2wt->word);

      n2b1wt = n2b1==-1 ? 0 : &((*item->m_sent)[n2b1]);
      n2b1t = n2b1==-1 ? g_noneTag : n2b1wt->tag;
      n2b1w = n2b1==-1 ? 0 : &(n2b1wt->word);
      n2b2wt = n2b2==-1 ? 0 : &((*item->m_sent)[n2b2]);
      n2b2t = n2b2==-1 ? g_noneTag : n2b2wt->tag;
      n2b2w = n2b2==-1 ? 0 : &(n2b2wt->word);
      n2e1wt = n2e1==-1 ? 0 : &((*item->m_sent)[n2e1]);
      n2e1t = n2e1==-1 ? g_noneTag : n2e1wt->tag;
      n2e1w = n2e1==-1 ? 0 : &(n2e1wt->word);
      n2e2wt = n2e2==-1 ? 0 : &((*item->m_sent)[n2e2]);
      n2e2t = n2e2==-1 ? g_noneTag : n2e2wt->tag;
      n2e2w = n2e2==-1 ? 0 : &(n2e2wt->word);

      n3b1wt = n3b1==-1 ? 0 : &((*item->m_sent)[n3b1]);
      n3b1t = n3b1==-1 ? g_noneTag : n3b1wt->tag;
      n3b1w = n3b1==-1 ? 0 : &(n3b1wt->word);
      n3b2wt = n3b2==-1 ? 0 : &((*item->m_sent)[n3b2]);
      n3b2t = n3b2==-1 ? g_noneTag : n3b2wt->tag;
      n3b2w = n3b2==-1 ? 0 : &(n3b2wt->word);
      n3e1wt = n3e1==-1 ? 0 : &((*item->m_sent)[n3e1]);
      n3e1t = n3e1==-1 ? g_noneTag : n3e1wt->tag;
      n3e1w = n3e1==-1 ? 0 : &(n3e1wt->word);
      n3e2wt = n3e2==-1 ? 0 : &((*item->m_sent)[n3e2]);
      n3e2t = n3e2==-1 ? g_noneTag : n3e2wt->tag;
      n3e2w = n3e2==-1 ? 0 : &(n3e2wt->word);
   
      if (modify==false) {
         if (s1!=0){
        	 s0ws1w.refer(s0w, s1w);
        	 s0bws1bw.refer(s0b1w, s1b1w);
        	 s0ews1ew.refer(s0e1w, s1e1w);
         }
         if (s0!=0 && n0!=-1){
        	 s0wn0w.refer(s0w, n0w);
        	 s0bwn0bw.refer(s0b1w, n0b1w);
        	 s0ewn0ew.refer(s0e1w, n0e1w);
         }
         if (n1!=-1){
        	 n0wn1w.refer(n0w, n1w);
        	 n0bwn1bw.refer(n0b1w, n1b1w);
        	 n0ewn1ew.refer(n0e1w, n1e1w);
         }
         if (s1!=0&&n0!=-1) {
        	 s1wn0w.refer(s1w, n0w);
        	 s1bwn0bw.refer(s1b1w, n0b1w);
        	 s1ewn0ew.refer(s1e1w, n0e1w);
         }
         if(s2!=0)
         {
        	 s1ws2w.refer(s1w, s2w);
        	 s1bws2bw.refer(s1b1w, s2b1w);
        	 s1ews2ew.refer(s1e1w, s2e1w);
         }
      }
      else {
          if (s1!=0){
         	 s0ws1w.allocate(*s0w, *s1w);
         	 s0bws1bw.allocate(*s0b1w, *s1b1w);
         	 s0ews1ew.allocate(*s0e1w, *s1e1w);
          }
          if (s0!=0 && n0!=-1){
         	 s0wn0w.allocate(*s0w, *n0w);
         	 s0bwn0bw.allocate(*s0b1w, *n0b1w);
         	 s0ewn0ew.allocate(*s0e1w, *n0e1w);
          }
          if (n1!=-1){
         	 n0wn1w.allocate(*n0w, *n1w);
         	 n0bwn1bw.allocate(*n0b1w, *n1b1w);
         	 n0ewn1ew.allocate(*n0e1w, *n1e1w);
          }
          if (s1!=0&&n0!=-1) {
         	 s1wn0w.allocate(*s1w, *n0w);
         	 s1bwn0bw.allocate(*s1b1w, *n0b1w);
         	 s1ewn0ew.allocate(*s1e1w, *n0e1w);
          }
          if(s2!=0)
          {
         	 s1ws2w.allocate(*s1w, *s2w);
         	 s1bws2bw.allocate(*s1b1w, *s2b1w);
         	 s1ews2ew.allocate(*s1e1w, *s2e1w);
          }
      }

      s0ts1t.load(s0t, s1t); s1ts2t.load(s1t, s2t); n0tn1t.load(n0t, n1t);
      s0tn0t.load(s0t, n0t); s1tn0t.load(s1t, n0t);

      s0bts1bt.load(s0b1t, s1b1t); s1bts2bt.load(s1b1t, s2b1t); n0btn1bt.load(n0b1t, n1b1t);
      s0btn0bt.load(s0b1t, n0b1t); s1btn0bt.load(s1b1t, n0b1t);

      s0ets1et.load(s0e1t, s1e1t); s1ets2et.load(s1e1t, s2e1t); n0etn1et.load(n0e1t, n1e1t);
      s0etn0et.load(s0e1t, n0e1t); s1etn0et.load(s1e1t, n0e1t);

      s0cs1c.load(s0c, s1c); s1cs2c.load(s1c, s2c); s0cn0t.load(s0c, n0t); s1cn0t.load(s1c, n0t);

      s0cs1bt.load(s0c, s1b1t); s0bts1c.load(s0b1t, s1c);
      s0cs1et.load(s0c, s1e1t); s0ets1c.load(s0e1t, s1c);

      s1cs2bt.load(s1c, s2b1t); s1bts2c.load(s1b1t, s2c);
      s1cs2et.load(s1c, s2e1t); s1ets2c.load(s1e1t, s2c);

      s0cn0bt.load(s0c, n0b1t); s0btn0t.load(s0b1t, n0t);
      s0cn0et.load(s0c, n0e1t); s0etn0t.load(s0e1t, n0t);

      s1cn0bt.load(s1c, n0b1t); s1btn0t.load(s1b1t, n0t);
      s1cn0et.load(s1c, n0e1t); s1etn0t.load(s1e1t, n0t);

      n0tn1bt.load(n0t, n1b1t); n0btn1t.load(n0b1t, n1t);
      n0tn1et.load(n0t, n1e1t); n0etn1t.load(n0e1t, n1t);

      s0scs1sc.load(s0sc, s1sc); s0scs1c.load(s0sc, s1c); s0cs1sc.load(s0c, s1sc);
      s1scs2sc.load(s1sc, s2sc); s1scs2c.load(s1sc, s2c); s1cs2sc.load(s1c, s2sc);
      s0scn0sc.load(s0sc, n0sc); s0cn0sc.load(s0c, n0sc); s0scn0t.load(s0sc, n0t);

      s0scs1bt.load(s0sc, s1b1t); s0bts1sc.load(s0b1t, s1sc);
      s0scs1et.load(s0sc, s1e1t); s0ets1sc.load(s0e1t, s1sc);

      s1scs2bt.load(s1sc, s2b1t); s1bts2sc.load(s1b1t, s2sc);
      s1scs2et.load(s1sc, s2e1t); s1ets2sc.load(s1e1t, s2sc);

      s0scn0bt.load(s0sc, n0b1t); s0scn0et.load(s0sc, n0e1t);
      s1scn0bt.load(s1sc, n0b1t); s1scn0et.load(s1sc, n0e1t);

      s1scn0sc.load(s1sc, n0sc); s1cn0sc.load(s1c, n0sc); s1scn0t.load(s1sc, n0t);
      n0scn1sc.load(n0sc, n1sc); n0tn1sc.load(n0t, n1sc); n0scn1t.load(n0sc, n1t);

      s0scs1scn0sc.copy(s0scs1sc); s0scs1scn0sc.add(n0sc);
      s0scn0scn1sc.copy(s0scn0sc); s0scn0scn1sc.add(n1sc);
      s0scs1scs2sc.copy(s0scs1sc); s0scs1scs2sc.add(s2sc);

      s0cs1cn0t.copy(s0cs1c); s0cs1cn0t.add(n0t);
      s0cn0tn1t.copy(s0cn0t); s0cn0tn1t.add(n1t);
      s0cs1cs2c.copy(s0cs1c); s0cs1cs2c.add(s2c);

      s0ts1tn0t.copy(s0ts1t); s0ts1tn0t.add(n0t);
      s0ts1ts2t.copy(s0ts1t); s0ts1ts2t.add(s2t);
      s0tn0tn1t.copy(s0tn0t); s0tn0tn1t.add(n1t);

      s0bts1btn0bt.copy(s0bts1bt); s0bts1btn0bt.add(n0b1t);
      s0bts1bts2bt.copy(s0bts1bt); s0bts1bts2bt.add(s2b1t);
      s0btn0btn1bt.copy(s0btn0bt); s0btn0btn1bt.add(n1b1t);

      s0ets1etn0et.copy(s0ets1et); s0ets1etn0et.add(n0e1t);
      s0ets1ets2et.copy(s0ets1et); s0ets1ets2et.add(s2e1t);
      s0etn0etn1et.copy(s0etn0et); s0etn0etn1et.add(n1e1t);

      if (s0c.empty()) s0js1jn0t.load(s0t); else s0js1jn0t.load(s0c);
      if (s1c.empty()) s0js1jn0t.add(s1t); else s0js1jn0t.add(s1c);
      s0js1jn0t.add(n0t);

      if (s0c.empty()) s0jn0tn1t.load(s0t); else s0jn0tn1t.load(s0c);
      s0jn0tn1t.add(n0t);
      s0jn0tn1t.add(n1t);

      if (s0c.empty()) s0js1js2j.load(s0t); else s0js1js2j.load(s0c);
      if (s1c.empty()) s0js1js2j.add(s1t); else s0js1js2j.add(s1c);
      if (s2c.empty()) s0js1js2j.add(s2t); else s0js1js2j.add(s2c);

      // s0 s0r and n0 -- by presuming that n0 exists!
      // s0rc is used when s0r exists, while s0rj is used all times
      // s0rc can be empty is s0r is not a constituent
      // s0rj is s0rc when s0rc not empty, and s0rt otherwise
      // s0rj empty only when s0r non existant

      s0cs0rc.load(s0c, s0rc);
      s0cs0rcn0t.copy(s0cn0t); s0cs0rcn0t.add(s0rc);

      s0cs0rjn0t.copy(s0cn0t);
      if (s0rc.empty()) s0cs0rjn0t.add(s0rt); else s0cs0rjn0t.add(s0rc);


      // s0 s0l and s1 -- by presuming that s1 exists!
      // see comments above
      s0cs0lc.load(s0c, s0lc);
      s0cs0lcs1c.copy(s0cs1c);
      s0cs0lcs1c.add(s0lc);

      s0cs0ljs1j.load(s0c);
      if (s0lc.empty()) s0cs0ljs1j.add(s0lt); else s0cs0ljs1j.add(s0lc);
      if (s1c.empty()) s0cs0ljs1j.add(s1t); else s0cs0ljs1j.add(s1c);

      // s0 slr and s1 -- by presuming that s1 exists!
      s1cs1rc.load(s1c, s1rc);
      s0cs1cs1rc.copy(s0cs1c);
      s0cs1cs1rc.add(s1rc);

      if (s0c.empty()) s0js1cs1rj.load(s0t); else s0js1cs1rj.load(s0c);
      s0js1cs1rj.add(s1c);
      if (s1rc.empty()) s0js1cs1rj.add(s1rt); else s0js1cs1rj.add(s1rc);

      s0s1_type = s1==0 ? 0 : ( s1->headsent_id == s0->headsent_id ? 1 : (s1->headpara_id == s0->headpara_id ? 2 : 3));
      s1s2_type = s2==0 ? 0 : ( s2->headsent_id == s1->headsent_id ? 1 : (s2->headpara_id == s1->headpara_id ? 2 : 3));
      s0n0_type = n0==-1 || s0==0 ? 0 : ( n0syn->headsent_id == s0->headsent_id ? 1 : (n0syn->headpara_id == s0->headpara_id ? 2 : 3));
      s1n0_type = n0==-1 || s1==0 ? 0 : (n0syn->headsent_id == s1->headsent_id ? 1 : (n0syn->headpara_id == s1->headpara_id ? 2 : 3));

      s0s1_dist = s1==0 ? 6 : std::min(s0->headedu_id - s1->headedu_id, 5);
      s1s2_dist = s2==0 ? 6 : std::min(s1->headedu_id - s2->headedu_id, 5);
      s0n0_dist = s0==0 || n0==-1 ? 6 : std::min(n0 - s0->headedu_id, 5);
      s1n0_dist = s1==0 || n0==-1 ? 6 : std::min(n0 - s1->headedu_id, 5);

      s0length = s0==0 ? 6 : std::min((s0e1 - s0b1 + 1)/5 + 1, 5);
      s1length = s1==0 ? 6 : std::min((s1e1 - s1b1 + 1)/5 + 1, 5);
      s2length = s2==0 ? 6 : std::min((s2e1 - s2b1 + 1)/5 + 1, 5);
      n0length = n0==-1 ? 6 : std::min((n0e1 - n0b1 + 1)/5 + 1, 5);
      n1length = n1==-1 ? 6 : std::min((n1e1 - n1b1 + 1)/5 + 1, 5);

      s0edunum = s0==0 ? 6: std::min(s0->edu_end - s0->edu_start + 1, 5);
      s1edunum = s1==0 ? 6: std::min(s1->edu_end - s1->edu_start + 1, 5);


      s0_sent_begin_dist = s0==0 ? 3: std::min( s0->edu_start- (*item->m_sent_first_edus)[s0->sent_start] + 1, 2);
      s1_sent_begin_dist = s1==0 ? 3: std::min( s1->edu_start - (*item->m_sent_first_edus)[s1->sent_start] + 1, 2);
      s2_sent_begin_dist = s2==0 ? 3: std::min( s2->edu_start - (*item->m_sent_first_edus)[s2->sent_start] + 1, 2);
      n0_sent_begin_dist = n0==-1 ? 3: std::min( n0 - (*item->m_sent_first_edus)[(*item->m_edu_sentids)[n0]] + 1, 2);

      s0_sent_end_dist = s0==0 ? 3: std::min( (*item->m_sent_first_edus)[s0->sent_end+1] - s0->edu_end + 1, 2);
      s1_sent_end_dist = s1==0 ? 3: std::min( (*item->m_sent_first_edus)[s1->sent_end+1] - s1->edu_end + 1, 2);
      s2_sent_end_dist = s2==0 ? 3: std::min( (*item->m_sent_first_edus)[s2->sent_end+1] - s2->edu_end + 1, 2);
      n0_sent_end_dist = n0==-1 ? 3: std::min( (*item->m_sent_first_edus)[(*item->m_edu_sentids)[n0]+1] - n0 + 1, 2);

      s0_para_begin_dist = s0==0 ? 3: std::min( (s0->edu_start - (*item->m_para_first_edus)[s0->para_start] + 1)/3 +1, 2);
      s1_para_begin_dist = s1==0 ? 3: std::min( (s1->edu_start - (*item->m_para_first_edus)[s1->para_start] + 1)/3+1, 2);
      s2_para_begin_dist = s2==0 ? 3: std::min( (s2->edu_start - (*item->m_para_first_edus)[s2->para_start] + 1)/3+1, 2);
      n0_para_begin_dist = n0==-1 ? 3: std::min( (n0 - (*item->m_para_first_edus)[(*item->m_edu_paraids)[n0]] + 1)/3+1, 2);

      s0_para_end_dist = s0==0 ? 3: std::min( ((*item->m_para_first_edus)[s0->para_end+1] - s0->edu_end + 1)/3+1, 2);
      s1_para_end_dist = s1==0 ? 3: std::min( ((*item->m_para_first_edus)[s1->para_end+1] - s1->edu_end + 1)/3+1, 2);
      s2_para_end_dist = s2==0 ? 3: std::min( ((*item->m_para_first_edus)[s2->para_end+1] - s2->edu_end + 1)/3+1, 2);
      n0_para_end_dist = n0==-1 ? 3: std::min( ((*item->m_para_first_edus)[(*item->m_edu_paraids)[n0]+1] - n0 + 1)/3+1, 2);

      s0m = 0;
      if(s0!=0)
      {
    	  if( (s0syn->word_start>s0b1 && s0syn->word_end<=s0e1)
    		|| (s0syn->word_start>=s0b1 && s0syn->word_end<s0e1))
    	  {
    		  s0m = 1;
    	  }
          else if(s0syn->word_start==s0b1 && s0syn->word_end==s0e1)
    	  {
    		  s0m = 4;
    	  }
    	  else if(s0syn->word_start==s0b1 && s0syn->word_end>s0e1)
    	  {
    		  s0m = 2;
    	  }
    	  else if(s0syn->word_start<s0b1 && s0syn->word_end==s0e1)
    	  {
    		  s0m = 3;
    	  }
    	  else
    	  {
    		  s0m = 5;
    	  }
      }

      s1m = 0;
      if(s1!=0)
      {
    	  if( (s1syn->word_start>s1b1 && s1syn->word_end<=s1e1)
    		|| (s1syn->word_start>=s1b1 && s1syn->word_end<s1e1))
    	  {
    		  s1m = 1;
    	  }
          else if(s1syn->word_start==s1b1 && s1syn->word_end==s1e1)
    	  {
    		  s1m = 4;
    	  }
    	  else if(s1syn->word_start==s1b1 && s1syn->word_end>s1e1)
    	  {
    		  s1m = 2;
    	  }
    	  else if(s1syn->word_start<s1b1 && s1syn->word_end==s1e1)
    	  {
    		  s1m = 3;
    	  }
    	  else
    	  {
    		  s1m = 5;
    	  }
      }

      s2m = 0;
      if(s2!=0)
      {
    	  if( (s2syn->word_start>s2b1 && s2syn->word_end<=s2e1)
    		|| (s2syn->word_start>=s2b1 && s2syn->word_end<s2e1))
    	  {
    		  s2m = 1;
    	  }
          else if(s2syn->word_start==s2b1 && s2syn->word_end==s2e1)
    	  {
    		  s2m = 4;
    	  }
    	  else if(s2syn->word_start==s2b1 && s2syn->word_end>s2e1)
    	  {
    		  s2m = 2;
    	  }
    	  else if(s2syn->word_start<s2b1 && s2syn->word_end==s2e1)
    	  {
    		  s2m = 3;
    	  }
    	  else
    	  {
    		  s2m = 5;
    	  }
      }

      n0m = 0;
      if(n0!=-1)
      {
    	  if( (n0syn->word_start>n0b1 && n0syn->word_end<=n0e1)
    		|| (n0syn->word_start>=n0b1 && n0syn->word_end<n0e1))
    	  {
    		  n0m = 1;
    	  }
          else if(n0syn->word_start==n0b1 && n0syn->word_end==n0e1)
    	  {
    		  n0m = 4;
    	  }
    	  else if(n0syn->word_start==n0b1 && n0syn->word_end>n0e1)
    	  {
    		  n0m = 2;
    	  }
    	  else if(n0syn->word_start<n0b1 && n0syn->word_end==n0e1)
    	  {
    		  n0m = 3;
    	  }
    	  else
    	  {
    		  n0m = 5;
    	  }
      }

      n1m = 0;
       if(n1!=-1)
       {
     	  if( (n1syn->word_start>n1b1 && n1syn->word_end<=n1e1)
     		|| (n1syn->word_start>=n1b1 && n1syn->word_end<n1e1))
     	  {
     		  n1m = 1;
     	  }
           else if(n1syn->word_start==n1b1 && n1syn->word_end==n1e1)
     	  {
     		  n1m = 4;
     	  }
     	  else if(n1syn->word_start==n1b1 && n1syn->word_end>n1e1)
     	  {
     		  n1m = 2;
     	  }
     	  else if(n1syn->word_start<n1b1 && n1syn->word_end==n1e1)
     	  {
     		  n1m = 3;
     	  }
     	  else
     	  {
     		  n1m = 5;
     	  }
       }

       n2m = 0;
       if(n2!=-1)
       {
		  if( (n2syn->word_start>n2b1 && n2syn->word_end<=n2e1)
			|| (n2syn->word_start>=n2b1 && n2syn->word_end<n2e1))
		  {
			  n2m = 1;
		  }
			else if(n2syn->word_start==n2b1 && n2syn->word_end==n2e1)
		  {
			  n2m = 4;
		  }
		  else if(n2syn->word_start==n2b1 && n2syn->word_end>n2e1)
		  {
			  n2m = 2;
		  }
		  else if(n2syn->word_start<n2b1 && n2syn->word_end==n2e1)
		  {
			  n2m = 3;
		  }
		  else
		  {
			  n2m = 5;
		  }
       }



       //std::cout << "strange...." << std::endl;
      return true;
   }
};
