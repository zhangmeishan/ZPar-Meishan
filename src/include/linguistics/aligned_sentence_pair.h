// Copyright (C) SUTD 2014
/****************************************************************
 *                                                              *
 * aligned_sentence_pair.h - the word-aligned sentence pair     *
 *                                                              *
 * Author: Meishan Zhang                                        *
 *                                                              *
 * SUTD. 2014.12                                                *
 *                                                              *
 ****************************************************************/

#ifndef _ALIGNEDSENTPAIR_H
#define _ALIGNEDSENTPAIR_H

#include "sentence_string.h"


class CAlignedSentencePair
{
public:
	CStringVector m_src_sent;
	CStringVector m_tgt_sent;
	// split source sentences into phrases, only records the begin positions
	std::vector<int> m_alignmap_pos;
	std::vector<int> m_alignmap_target;  // for target, index to m_alignmap_pos;
	std::vector<std::vector<int> > m_alignmap_source; //for source
	std::vector<unsigned long> m_actions;


	CAlignedSentencePair()
	{
		m_src_sent.clear();
		m_tgt_sent.clear();
		m_alignmap_pos.clear();
		m_alignmap_target.clear();
		m_alignmap_source.clear();
		m_actions.clear();
	}

	void clear()
	{
		m_src_sent.clear();
		m_tgt_sent.clear();
		m_alignmap_pos.clear();
		m_alignmap_target.clear();
		m_alignmap_source.clear();
		m_actions.clear();
	}


	virtual ~CAlignedSentencePair() {}

	bool operator !=(const CAlignedSentencePair &item) const {
		return ! ((*this)==item);
	}

	bool operator ==(const CAlignedSentencePair &item) const {
	   if(m_src_sent.size() != item.m_src_sent.size() ||
		  m_tgt_sent.size() != item.m_tgt_sent.size() ||
		  m_alignmap_pos.size() != item.m_alignmap_pos.size() ||
		  m_alignmap_target.size() != item.m_alignmap_target.size() ||
		  m_alignmap_source.size() != item.m_alignmap_source.size())
		  //m_actions.size() != item.m_actions.size())
	   {
		   return false;
	   }

	   for(int i = 0; i < m_src_sent.size(); i++)
	   {
		   if(m_src_sent[i] != item.m_src_sent[i]) return false;
	   }

	   for(int i = 0; i < m_tgt_sent.size(); i++)
	   {
		   if(m_tgt_sent[i] != item.m_tgt_sent[i]) return false;
	   }

	   for(int i = 0; i < m_alignmap_pos.size(); i++)
	   {
		   if(m_alignmap_pos[i] != item.m_alignmap_pos[i]) return false;
	   }

	   for(int i = 0; i < m_alignmap_target.size(); i++)
	   {
		   if(m_alignmap_target[i] != item.m_alignmap_target[i]) return false;
	   }

	   for(int i = 0; i < m_alignmap_source.size(); i++)
	   {
		   if(m_alignmap_source[i].size() != item.m_alignmap_source[i].size()) return false;
		   for(int j = 0; j < m_alignmap_source[i].size(); j++)
		   {
			   if(m_alignmap_source[i][j] != item.m_alignmap_source[i][j]) return false;
		   }
	   }

	   //for(int i = 0; i < m_actions.size(); i++)
	   //{
		//   if(m_actions[i] != item.m_actions[i]) return false;
	   //}



		return true;
	}

	void ComputeAlignMap()
	{
		m_alignmap_source.clear();

		for(int i = 0; i < m_alignmap_pos.size(); i++)
		{
			std::vector<int> onemap;
			for(int j = 0; j < m_alignmap_target.size(); j++)
			{
				if(m_alignmap_target[j] == i)
				{
					onemap.push_back(j);
				}
			}
			m_alignmap_source.push_back(onemap);
		}
	}

};


//==============================================================

inline std::istream & operator >> (std::istream &is, CAlignedSentencePair &node) {
	int line_number;
	node.m_src_sent.clear();
	node.m_tgt_sent.clear();
	node.m_alignmap_pos.clear();
	node.m_alignmap_target.clear();
	char cTemp;
	std::string sWord;                    // std::string for next word
	while (is.get(cTemp)) {
		  if (cTemp == '\r')
			 continue;
		  if (cTemp == '\n') {                      // if we meet EOL, return std::string
			 if (!sWord.empty()) {                  // we have found another word
				node.m_src_sent.push_back(sWord);
				sWord="";
			 }
			 break;
		  }
	      if (cTemp == ' ' || cTemp == '\t') {                       // otherwise, if we meet " "
	         if (!sWord.empty()) {                  // we have found another word
	            node.m_src_sent.push_back(sWord);
	            sWord = "";
	         }
	      }
	      else                                      // otherwise
	         sWord += cTemp;
	}
	// second line: phrases marks in source sentence
	while (is.get(cTemp)) {
		  if (cTemp == '\r')
			 continue;
		  if (cTemp == '\n') {                      // if we meet EOL, return std::string
			 if (!sWord.empty()) {                  // we have found another word
				node.m_alignmap_pos.push_back(atoi(sWord.c_str()));
				sWord="";
			 }
			 break;
		  }
	      if (cTemp == ' ' || cTemp == '\t') {                       // otherwise, if we meet " "
	         if (!sWord.empty()) {                  // we have found another word
	            node.m_alignmap_pos.push_back(atoi(sWord.c_str()));
	            sWord = "";
	         }
	      }
	      else                                      // otherwise
	         sWord += cTemp;
	}

	// third line: target sentence
	while (is.get(cTemp)) {
		  if (cTemp == '\r')
			 continue;
		  if (cTemp == '\n') {                      // if we meet EOL, return std::string
			 if (!sWord.empty()) {                  // we have found another word
				node.m_tgt_sent.push_back(sWord);
				sWord="";
			 }
			 assert(node.m_tgt_sent.size()>0);
			 break;
		  }
	      if (cTemp == ' ' || cTemp == '\t') {                       // otherwise, if we meet " "
	         if (!sWord.empty()) {                  // we have found another word
	            node.m_tgt_sent.push_back(sWord);
	            sWord = "";
	         }
	      }
	      else                                      // otherwise
	         sWord += cTemp;
	}

// fourth line: target sentence align
	while (is.get(cTemp)) {
		  if (cTemp == '\r')
			 continue;
		  if (cTemp == '\n') {                      // if we meet EOL, return std::string
			 if (!sWord.empty()) {                  // we have found another word
//				 std::cout << atoi(sWord.c_str()) << " ";
//				 std::cout.flush();
				 node.m_alignmap_target.push_back(atoi(sWord.c_str()));
				 sWord="";
			 }
			 break;
		  }
	      if (cTemp == ' ' || cTemp == '\t') {                       // otherwise, if we meet " "
	         if (!sWord.empty()) {                  // we have found another word
//	        	 std::cout << atoi(sWord.c_str()) << " ";
//	        	 std::cout.flush();
	        	 node.m_alignmap_target.push_back(atoi(sWord.c_str()));
	            sWord = "";
	         }
	      }
	      else                                      // otherwise
	         sWord += cTemp;
	}
//	std::cout << std::endl;
	assert(node.m_alignmap_target.size() == node.m_tgt_sent.size());
//	for (int i = 0; i < node.m_alignmap_target.size(); i++) {
//		std::cout << node.m_alignmap_target[i] << " ";
//	}
//	std::cout << std::endl;
	node.ComputeAlignMap();

//	for (int i = 0; i < node.m_alignmap_target.size(); i++) {
//		std::cout << node.m_alignmap_target[i] << " ";
//	}
//	std::cout << std::endl;
//	std::cout.flush();

	return is;
}

inline std::ostream & operator <<(std::ostream &os,
		const CAlignedSentencePair &node) {

	for (int i = 0; i < node.m_src_sent.size(); i++) {
		os << node.m_src_sent[i] << " ";
	}
	os << std::endl;

	for (int i = 0; i < node.m_alignmap_pos.size(); i++) {
		os << node.m_alignmap_pos[i] << " ";
	}
	os << std::endl;

	for (int i = 0; i < node.m_tgt_sent.size(); i++) {
		os << node.m_tgt_sent[i] << " ";
	}
	os << std::endl;

	for (int i = 0; i < node.m_alignmap_target.size(); i++) {
		os << node.m_alignmap_target[i] << " ";
	}
	//os << std::endl;
	os.flush();
	return os;
}

#endif
