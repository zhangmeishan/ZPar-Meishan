// Copyright (C) University of Oxford 2010
#ifndef _MACHINE_TRANSLATION_STATEITEM
#define _MACHINE_TRANSLATION_STATEITEM

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce. 
 *
 *
 *==============================================================*/

class CStateItem {

public:
   int m_StackX[8*MAX_SENTENCE_SIZE+1];                     // stack of target words that are currently  processed
   int m_StackY[MAX_SENTENCE_SIZE+1];                     // stack of source words that are currently  processed
   int m_PhraseYMarks[MAX_SENTENCE_SIZE+1];              // stack of align map start position that are currently processed (consecutive m v.s. random n map)
   int m_StackXAlign[8*MAX_SENTENCE_SIZE+1];              // stack of align map length that are currently  processed (consecutive m v.s. random n map)


   //Buffer, save sentences by reversed order
   int m_BufferX[MAX_SENTENCE_SIZE+1];                    // buffer of target words that are not processed (consecutive m v.s. random n map)
   int m_BufferXAlign[MAX_SENTENCE_SIZE+1];             // buffer of align map length that are currently  processed (consecutive m v.s. random n map)

   int m_nStackXSize;
   int m_nPhraseYNum;
   int m_nStackYSize;
   int m_nBufferXSize;


   unsigned long m_Action[16*MAX_SENTENCE_SIZE+1];
   unsigned long m_ActionType[16*MAX_SENTENCE_SIZE+1];
   int m_nActionSize;
   int m_nCurrentIndexInStackX;               // index for the next target word to be processed
   int m_nCurrentIndexInStackY;               // index for the next source word to be translated

   unsigned long m_nLastAction;                  // the last stack action
   int m_nLastInsertWordXPosition;

   const std::vector <CWord>* m_lCache;



public:
   SCORE_TYPE score;                        // score of stack - predicting how potentially this is the correct one

public:
   // constructors and destructor
   // actually need a parameter that represents input source sentence sequence
   CStateItem(const std::vector <CWord>*cache=0) : m_lCache(cache) { clear(); }
   ~CStateItem() { }
   CStateItem(CStateItem& item) : m_lCache(0) { std::cerr<<"CStateItem does not support copy constructor!"; std::cerr.flush(); assert(1==0); }

public:
   // comparison
   inline bool operator < (const CStateItem &item) const { return score < item.score; }
   inline bool operator > (const CStateItem &item) const { return score > item.score; }
   inline bool operator == (const CStateItem &item) const {
      int i;
      if ( m_nCurrentIndexInStackX != item.m_nCurrentIndexInStackX )
         return false;
      if ( m_nCurrentIndexInStackY != item.m_nCurrentIndexInStackY )
         return false;
      //if ( m_nStackXGapId != item.m_nStackXGapId )
      //   return false;
      if ( m_nStackXSize != item.m_nStackXSize )
         return false;
      if ( m_nStackXSize>0 )
      {
    	  for( i = 0; i <= m_nStackXSize; i++)
    	  {
    		  if (m_StackX[i] != item.m_StackX[i] ||
    				  m_StackXAlign[i] != item.m_StackXAlign[i])
    		  {
    			  return false;
    		  }
    	  }
      }


      if ( m_nStackYSize != item.m_nStackYSize )
         return false;
      if ( m_nStackYSize>0 )
      {
    	  for( i = 0; i <= m_nStackYSize; i++)
    	  {
    		  if (m_StackY[i] != item.m_StackY[i])
    		  {
    			  return false;
    		  }
    	  }
      }


      if ( m_nPhraseYNum != item.m_nPhraseYNum )
         return false;
      if ( m_nPhraseYNum>0 )
      {
    	  for( i = 0; i <= m_nPhraseYNum; i++)
    	  {
    		  if (m_PhraseYMarks[i] != item.m_PhraseYMarks[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nBufferXSize != item.m_nBufferXSize )
         return false;
      if ( m_nBufferXSize>0 )
      {
    	  for( i = 0; i <= m_nBufferXSize; i++)
    	  {
    		  if (m_BufferX[i] != item.m_BufferX[i] ||
    				  m_BufferXAlign[i] != item.m_BufferXAlign[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nActionSize != item.m_nActionSize )
         return false;
      if ( m_nActionSize > 0 )
      {
    	  for(i = 0; i <= m_nActionSize; i++)
    	  {
    		  if (m_Action[i] != item.m_Action[i] || m_ActionType[i] != item.m_ActionType[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nLastInsertWordXPosition != item.m_nLastInsertWordXPosition )
         return false;

      if ( m_nLastAction != item.m_nLastAction )
         return false;


      return true;
   }

   inline bool operator != (const CStateItem &item) const {
      return ! ((*this)==item);
   }


   void clear() {

	  m_nCurrentIndexInStackX = 0;
	  m_nCurrentIndexInStackY = 0;
      m_nStackXSize = 0;
      m_StackX[m_nStackXSize] = -2; //-2 denotes not a valid value, -1 denotes gap
      m_nStackYSize = 0;
      m_StackY[m_nStackXSize] = -1;
      m_StackXAlign[m_nStackXSize] = -2; // -2 denotes invalid, -1 denotes none

      m_nPhraseYNum = 1;
      m_PhraseYMarks[0] = 0;
      m_PhraseYMarks[m_nPhraseYNum] = -1;

      m_nBufferXSize = 0;
      m_BufferX[m_nBufferXSize] = -1;
      m_BufferXAlign[m_nBufferXSize] = -2; // -2 denotes invalid, -1 denotes none


      m_nLastInsertWordXPosition = -1;

      m_nActionSize = 0;
      m_Action[m_nActionSize] = -1;
      m_ActionType[m_nActionSize] = -1;
      score = 0; 
      m_nLastAction = CAction::encodeNone();


   }

   void operator = ( const CStateItem &item ) {
	   int i;
	   m_nCurrentIndexInStackX = item.m_nCurrentIndexInStackX;
	   m_nCurrentIndexInStackY = item.m_nCurrentIndexInStackY;

	   m_nStackXSize = item.m_nStackXSize;
	   for(i = 0; i < m_nStackXSize; i++)
	   {
		   m_StackX[i] = item.m_StackX[i];
		   m_StackXAlign[i] = item.m_StackXAlign[i];
	   }

	   m_nStackYSize = item.m_nStackYSize;
	   for(i = 0; i < m_nStackYSize; i++)
	   {
		   m_StackY[i] = item.m_StackY[i];
	   }

	   m_nPhraseYNum = item.m_nPhraseYNum;
	   for(i = 0; i < m_nPhraseYNum; i++)
	   {
		   m_PhraseYMarks[i] = item.m_PhraseYMarks[i];
	   }


	   m_nBufferXSize = item.m_nBufferXSize;
	   for(i = 0; i < m_nBufferXSize; i++)
	   {
		   m_BufferX[i] = item.m_BufferX[i];
		   m_BufferXAlign[i] = item.m_BufferXAlign[i];
	   }

	   m_nLastInsertWordXPosition = item.m_nLastInsertWordXPosition;

	   m_nActionSize = item.m_nActionSize;
	   for(i = 0; i < m_nActionSize; i++)
	   {
		   m_Action[i] = item.m_Action[i];
		   m_ActionType[i] = item.m_ActionType[i];
	   }

	  score = item.score;
	  m_nLastAction = item.m_nLastAction;

	  m_lCache = item.m_lCache;


	  ClearNext();
   }

   // the clear next action is used to clear the next word, used with forwarding the next word index
   void ClearNext() {
	m_StackX[m_nStackXSize] = -2;
	//m_StackXGap[m_nStackXGapSize] = -1;
	m_StackY[m_nStackYSize] = -1;
	m_StackXAlign[m_nStackXSize] = -2;
	m_PhraseYMarks[m_nPhraseYNum] = -1;
	m_BufferX[m_nBufferXSize] = -1;
	m_BufferXAlign[m_nBufferXSize] = -2;
	m_Action[m_nActionSize]=-1;
	m_ActionType[m_nActionSize]=-1;
   }


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

public:
   // currently this action is of no use.
   // It is useful when y_i ... y_(i+m) ===> x_(a[1]) .... x_(a[n]), m>0
   bool ShiftY()
   {
	   assert(m_nStackYSize < m_lCache->size());
	   m_StackY[m_nStackYSize] = (*m_lCache)[m_nStackYSize].code();
	   m_nStackYSize++;

	   m_nLastAction = CAction::encodeShiftY();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::SHIFT_Y;
	   m_nActionSize++;

	   ClearNext();
	   return true;
   }

   bool ShiftX()
   {
	   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
	   assert(m_nBufferXSize > 0 && m_nCurrentIndexInStackX > m_nLastInsertWordXPosition);
	   if(m_nCurrentIndexInStackX == m_nStackXSize || m_StackX[m_nCurrentIndexInStackX] != -1)
	   {
		   for(int i = m_nStackXSize; i > m_nCurrentIndexInStackX; i--)
		   {
			   m_StackX[i] = m_StackX[i-1];
			   m_StackXAlign[i] = m_StackXAlign[i-1];
		   }
		   m_nStackXSize++;
	   }

	   m_nLastInsertWordXPosition = m_nCurrentIndexInStackX;
	   m_StackX[m_nCurrentIndexInStackX] = m_BufferX[m_nBufferXSize-1];
	   m_StackXAlign[m_nCurrentIndexInStackX] = m_BufferXAlign[m_nBufferXSize-1];
	   m_nBufferXSize--;
	   m_nCurrentIndexInStackX++;

	   m_nLastAction = CAction::encodeShiftX();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::SHIFT_X;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }


   bool GenerateXY(const std::vector<CWord>& translated_words, int rule_id)
   {
	   assert(m_nStackYSize < m_lCache->size() && m_nBufferXSize == 0);
	   m_StackY[m_nStackYSize] = (*m_lCache)[m_nStackYSize].code();
	   m_nStackYSize++;

	   m_nLastInsertWordXPosition = m_nCurrentIndexInStackX;
	   if (m_nCurrentIndexInStackX == m_nStackXSize)
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();

		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum-1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
		   m_nStackXSize++;
	   }
	   else if(m_StackX[m_nCurrentIndexInStackX] == -1)
	   {
		   //assert(m_StackXGap[m_nStackXGapId] == m_nCurrentIndexInStackX);
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();
		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum -1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
		   //MarkGapFilled();
	   }
	   else
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   for(int i = m_nStackXSize; i > m_nCurrentIndexInStackX; i--)
		   {
			   m_StackX[i] = m_StackX[i-1];
			   m_StackXAlign[i] = m_StackXAlign[i-1];
		   }
		   m_nStackXSize++;
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();
		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum -1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
	   }
	   int gapNum = 0;
	   for(int i = 0; i < m_nStackXSize; i++)
	   {
		   if(m_StackX[i] == -1)gapNum++;
	   }

	   if(translated_words.size() > 1)
	   {
		   for(int i = translated_words.size()-1; i > 0; i--)
		   {
			   if(m_nBufferXSize + m_nStackXSize - gapNum >= 8*MAX_SENTENCE_SIZE)
			   {
				   break;
			   }
			   m_BufferX[m_nBufferXSize] = translated_words[i].code();
			   m_BufferXAlign[m_nBufferXSize] = m_nPhraseYNum-2;
			   m_nBufferXSize++;
		   }
	   }


	   m_nCurrentIndexInStackY = m_nStackYSize;


	   m_nLastAction = CAction::encodeGenerateXY(rule_id);
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::GENERATE_XY;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }


   bool GenerateXX()
   {
	   assert(m_nStackYSize < m_lCache->size() && m_nBufferXSize == 0);
	   m_StackY[m_nStackYSize] = (*m_lCache)[m_nStackYSize].code();
	   m_nStackYSize++;

	   m_nLastInsertWordXPosition = m_nCurrentIndexInStackX;
	   if (m_nCurrentIndexInStackX == m_nStackXSize)
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   m_StackX[m_nCurrentIndexInStackX] = m_StackY[m_nCurrentIndexInStackY];
		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum -1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
		   m_nStackXSize++;
	   }
	   else if(m_StackX[m_nCurrentIndexInStackX] == -1)
	   {
		   //assert(m_StackXGap[m_nStackXGapId] == m_nCurrentIndexInStackX);
		   m_StackX[m_nCurrentIndexInStackX] = m_StackY[m_nCurrentIndexInStackY];
		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum -1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
		   //MarkGapFilled();
	   }
	   else
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   for(int i = m_nStackXSize; i > m_nCurrentIndexInStackX; i--)
		   {
			   m_StackX[i] = m_StackX[i-1];
			   m_StackXAlign[i] = m_StackXAlign[i-1];
		   }
		   m_nStackXSize++;
		   m_StackX[m_nCurrentIndexInStackX] = m_StackY[m_nCurrentIndexInStackY];
		   m_StackXAlign[m_nCurrentIndexInStackX] = m_nPhraseYNum -1;
		   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
		   m_nPhraseYNum++;
		   m_nCurrentIndexInStackX++;
	   }

	   int gapNum = 0;
	   for(int i = 0; i < m_nStackXSize; i++)
	   {
		   if(m_StackX[i] == -1)gapNum++;
	   }

	   if(m_nStackYSize - m_nCurrentIndexInStackY > 1)
	   {
		   for(int i = m_nStackYSize-2; i >= m_nCurrentIndexInStackY; i--)
		   {
			   if(m_nBufferXSize + m_nStackXSize - gapNum >= 8*MAX_SENTENCE_SIZE)
			   {
				   break;
			   }
			   m_BufferX[m_nBufferXSize] = m_StackY[i];
			   m_BufferXAlign[m_nBufferXSize] = m_nPhraseYNum -2;
			   m_nBufferXSize++;
		   }
	   }


	   m_nCurrentIndexInStackY = m_nStackYSize;

	   m_nLastAction = CAction::encodeGenerateXX();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::GENERATE_XX;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }

   bool GenerateX(const std::vector<CWord> translated_words, int rule_id)
   {
	   //is not possible for m_nBufferXSize == 0 ;
	   //assert(m_nCurrentIndexInStackY == m_nStackYSize);
	   if(m_nCurrentIndexInStackX < m_nStackXSize)
	   {
		   if(m_nBufferXSize == 0 && m_nStackYSize == m_lCache->size())
		   {
			   //std::cout << "cannot happen in conversion function" << std::endl;
		   }
		   else
		   {
			   assert(m_StackX[m_nCurrentIndexInStackX] >=0);
		   }
	   }

	   m_nLastInsertWordXPosition = m_nCurrentIndexInStackX;
	   if (m_nCurrentIndexInStackX == m_nStackXSize)
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();
		   m_StackXAlign[m_nCurrentIndexInStackX] = -1;
		   m_nCurrentIndexInStackX++;
		   m_nStackXSize++;
	   }
	   else if(m_StackX[m_nCurrentIndexInStackX] == -1)
	   {
		   //assert(m_StackXGap[m_nStackXGapId] == m_nCurrentIndexInStackX);
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();
		   m_StackXAlign[m_nCurrentIndexInStackX] = -1;
		   m_nCurrentIndexInStackX++;
		   //MarkGapFilled();
	   }
	   else
	   {
		   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
		   for(int i = m_nStackXSize; i > m_nCurrentIndexInStackX; i--)
		   {
			   m_StackX[i] = m_StackX[i-1];
			   m_StackXAlign[i] = m_StackXAlign[i-1];
		   }
		   m_nStackXSize++;
		   m_StackX[m_nCurrentIndexInStackX] = translated_words[0].code();
		   m_StackXAlign[m_nCurrentIndexInStackX] = -1;
		   m_nCurrentIndexInStackX++;
	   }

	   int gapNum = 0;
	   for(int i = 0; i < m_nStackXSize; i++)
	   {
		   if(m_StackX[i] == -1)gapNum++;
	   }
	   if(translated_words.size() > 1)
	   {
		   for(int i = translated_words.size()-1; i > 0; i--)
		   {
			   if(m_nBufferXSize + m_nStackXSize - gapNum >= 8*MAX_SENTENCE_SIZE)
			   {
				   break;
			   }
			   m_BufferX[m_nBufferXSize] = translated_words[i].code();
			   m_BufferXAlign[m_nBufferXSize] = -1;
			   m_nBufferXSize++;
		   }
	   }

	   m_nLastAction = CAction::encodeGenerateX(rule_id);
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::GENERATE_X;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }

   bool GenerateY(int rule_id)
   {
	   assert(m_nStackYSize < m_lCache->size() && m_nBufferXSize == 0);
	   m_StackY[m_nStackYSize] = (*m_lCache)[m_nStackYSize].code();
	   m_nStackYSize++;


	   m_nCurrentIndexInStackY = m_nStackYSize;

	   m_PhraseYMarks[m_nPhraseYNum] = m_nStackYSize;
	   m_nPhraseYNum++;


	   m_nLastAction = CAction::encodeGenerateY(rule_id);
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::GENERATE_Y;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }

   bool mustInsertStackX() const
   {
	   if(m_nCurrentIndexInStackX > 0
		  && m_StackX[m_nCurrentIndexInStackX-1] == -1
		  && m_StackX[m_nCurrentIndexInStackX] == -1)
	   {
		   assert( m_nLastAction == CAction::encodeInsertGap());
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   bool InsertGap()
   {
	   if(m_nStackXSize >= 8*MAX_SENTENCE_SIZE) return false;
	   // Usually it is not allowed for two continue gaps,
	   // except that there is a shift or generate after current operaction.
	   if( (m_nCurrentIndexInStackX > 0
			&& m_StackX[m_nCurrentIndexInStackX-1] == -1)
	        || (m_nCurrentIndexInStackX +1 < m_nStackXSize
			&& m_StackX[m_nCurrentIndexInStackX] == -1
			&& m_StackX[m_nCurrentIndexInStackX+1] == -1))
	   {
		   assert(0);
	   }

	   for(int i = m_nStackXSize; i > m_nCurrentIndexInStackX; i--)
	   {
		   m_StackX[i] = m_StackX[i-1];
		   m_StackXAlign[i] = m_StackXAlign[i-1];
	   }
	   m_StackX[m_nCurrentIndexInStackX] = -1;
	   m_nStackXSize++;
	   if(m_nStackXSize <= 0)
	   {
		   std::cout << "strange" << std::endl;
	   }
	   m_nCurrentIndexInStackX++;


	   m_nLastAction = CAction::encodeInsertGap();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::INSERT_GAP;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }


   bool JumpBack()
   {
	   int gapIndex = m_nCurrentIndexInStackX-1;
	   for(; gapIndex >= 0; gapIndex--)
	   {
		   if(m_StackX[gapIndex] == -1)
		   {
			   break;
		   }
	   }
	   if(gapIndex < 0)
	   {
		   std::cout << "error" << std::endl;
	   }
	   m_nCurrentIndexInStackX = gapIndex;

	   m_nLastAction = CAction::encodeJumpBack();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::JUMP_BACK;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }


   bool JumpForward()
   {
	   assert(m_nCurrentIndexInStackX < m_nStackXSize);

	   //m_nCurrentIndexInStackX = m_nStackXSize;
	   int i = m_nCurrentIndexInStackX+1;
	   while(i < m_nStackXSize)
	   {
		   if(m_StackX[i] == -1) break;
		   i++;
	   }
	   m_nCurrentIndexInStackX = i;

	   m_nLastAction = CAction::encodeJumpForward();
	   m_Action[m_nActionSize]=m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::JUMP_FORWARD;
	   m_nActionSize++;

	   ClearNext();

	   return true;
   }


   bool Finish()
   {
	   assert(m_nBufferXSize == 0 && m_nStackYSize == m_lCache->size());
	   for(int i = 0; i < m_nStackXSize; i++)
	   {
		   assert(m_StackX[i]>=0);
	   }

	   assert(m_nCurrentIndexInStackX == m_nStackXSize);

	   m_nLastAction = CAction::encodeFinish();
	   m_Action[m_nActionSize]= m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::FINISH;
	   m_nActionSize++;
	   ClearNext();

	   return true;
   }


   bool Idle()
   {
	   assert(m_nLastAction == CAction::encodeFinish() || m_nLastAction == CAction::encodeIdle());
	   m_nLastAction = CAction::encodeIdle();
	   m_Action[m_nActionSize] = m_nLastAction;
	   m_ActionType[m_nActionSize]=CActionType::IDLE;
	   m_nActionSize++;
	   ClearNext();
	   return true;
   }



public:

   // the move action is a simple call to do action according to the action code
   bool Move (const unsigned long &ac, const std::vector<CWord> *translated_words, CTranslateTypeVector& mapTranslateRuleTypes) {


	   CAction action = ac;
	   int rule_id =action.getRuleID();

	   if(m_nActionSize >= 16*MAX_SENTENCE_SIZE)return false;

	   if(action.isNone(mapTranslateRuleTypes))
	   {
		   return false;
	   }
	   else if(action.isIdle(mapTranslateRuleTypes))
	   {
	    	 return Idle();
	   }
	   else if(action.isFinish(mapTranslateRuleTypes))
	   {
	         return Finish();

	   }
	   else if(action.isInsertGap(mapTranslateRuleTypes))
	   {

		   return InsertGap();
	   }
	   else if(action.isJumpBack(mapTranslateRuleTypes))
	   {
		   return JumpBack();
	   }
	   else if(action.isJumpForward(mapTranslateRuleTypes))
	   {
	         return JumpForward();
	   }
	   else if(action.isShiftY(mapTranslateRuleTypes))
	   {
	    	 return ShiftY();
	   }
	   else if(action.isShiftX(mapTranslateRuleTypes))
	   {
	    	 return ShiftX();
	   }
	   else if(action.isGenerateXX(mapTranslateRuleTypes))
	   {
	    	 return GenerateXX();
	   }
	   else if(action.isGenerateXY(mapTranslateRuleTypes))
	   {
	         return GenerateXY(*translated_words, rule_id);
	   }
	   else if(action.isGenerateX(mapTranslateRuleTypes))
	   {
	         return GenerateX(*translated_words, rule_id);
	   }
	   else if(action.isGenerateY(mapTranslateRuleTypes))
	   {
	         return GenerateY(rule_id);
	   }
	   else
	   {
		   THROW("unknown action: " << ac << '.');
	   }

   }

//-----------------------------------------------------------------------------

public:
   // returns true is the next word advances -- by shift or arcright. 


   bool StandardMoveStep( CAction& goldac, const CAlignedSentencePair &sentpair) {
	   for(int i = 0; i < m_nActionSize && i < sentpair.m_actions.size(); i++)
	   {
		   if(m_Action[i] != sentpair.m_actions[i])
		   {
			   return false;
		   }
	   }

	   if(m_nActionSize < sentpair.m_actions.size())
	   {
		   goldac = sentpair.m_actions[m_nActionSize];
	   }
	   else
	   {
		   goldac = CAction::encodeIdle();
	   }

	   return true;
   }



   bool FollowMove( const CStateItem *item, CAction& next_action) {
	   if(m_nActionSize >= item->m_nActionSize)
	   {
		   std::cout << "error" << std::endl;
	   }
	   for(int i = 0; i < m_nActionSize; i++)
	   {
		   if(m_Action[i] != item->m_Action[i])
		   {
			   return false;
		   }
	   }

	   next_action = item->m_Action[m_nActionSize];

	   return true;
   }

   void GenerateTree(CAlignedSentencePair &output ) const {
	   //assert(m_nLastAction == CAction::encodeFinish() || m_nLastAction == CAction::encodeIdle());
	   output.clear();
	   for(int i = 0; i < m_lCache->size(); i++)
	   {
		   output.m_src_sent.push_back((*m_lCache)[i].str());
	   }

	   for(int i = 0; i < m_nStackXSize; i++)
	   {
		   if(m_StackX[i] >= 0)
		   {
			   output.m_tgt_sent.push_back(CWord(m_StackX[i]).str());
			   output.m_alignmap_target.push_back(m_StackXAlign[i]);
		   }
	   }

	   for(int i = m_nBufferXSize-1; i>=0; i--)
	   {
		   output.m_tgt_sent.push_back(CWord(m_BufferX[i]).str());
		   output.m_alignmap_target.push_back(m_BufferXAlign[i]);
	   }


	   for(int i = 0; i < m_nPhraseYNum; i++)
	   {
		   output.m_alignmap_pos.push_back(m_PhraseYMarks[i]);
	   }


	   for(int i = 0; i < m_nActionSize; i++)
	   {
		   output.m_actions.push_back(m_Action[i]);
	   }
	   output.ComputeAlignMap();
   }

};


inline std::ostream & operator <<(std::ostream &os,
		const CStateItem &node) {
	if(node.m_nStackXSize > 0)
	{
		if(node.m_StackX[0] == -1) os << "[#GAP#]0";
		else os << CWord(node.m_StackX[0]).str() << "[" << node.m_StackXAlign[0] << "]0";
		for (int i = 1; i < node.m_nStackXSize; i++)
		{
			if(node.m_StackX[i] == -1) os << " [#GAP#]" << i;
			else os << " " << CWord(node.m_StackX[i]).str() << "[" << node.m_StackXAlign[i] << "]" << i;
			if(i%50 == 0)os << std::endl;
		}
		os.flush();
	}
	os << std::endl;
	if(node.m_nActionSize > 0)
	{
		os << node.m_Action[0];
		for (int i = 1; i < node.m_nActionSize; i++)
		{
			os << " " << node.m_Action[i];
			if(i%50 == 0)os << std::endl;
		}
		os.flush();
	}
}




#endif
