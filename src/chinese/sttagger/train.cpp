// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * train.cpp - the training of the Chinese tagger.              *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2006.10                        *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "tagger.h"
#include "reader.h"
#include "writer.h"
#include "charcat.h"

using namespace chinese;

/*----------------------------------------------------------------
 *
 * recordSegmentation - record a segmented sentence with bitarr.
 * 
 * Input raw is the raw format of input tagged, it is provided
 * here because the caller already did UntagAndDesegmentSent
 * 
 *---------------------------------------------------------------*/

void recordSegmentation(const CStringVector *raw, const CTwoStringVector* tagged, CBitArray &retval) {
   std::vector<unsigned> indice;
   indice.clear(); 
   for (unsigned i=0; i<raw->size(); ++i) {
      for (unsigned j=0; j<raw->at(i).size(); ++j)
         indice.push_back(i);
   }
   retval.clear();
   unsigned start=0;
   for (unsigned i=0; i<tagged->size(); ++i) {
      unsigned word_start = indice[start];
      unsigned word_end = indice[start+tagged->at(i).first.size()-1];
      start += tagged->at(i).first.size();
      retval.set(word_end);
   }
}

/*===============================================================
 *
 * auto_train
 *
 *==============================================================*/

void auto_train(const std::string &sOutputFile, const std::string &sFeatureFile, const unsigned long &nBest, const unsigned long &nMaxSentSize, const std::string &sKnowledgePath, const bool &bFWCDRule, const std::string &sStackingPath) {
   static CCharCatDictionary charcat ; // don't know why there is a segmentation fault when this is put as a global variable. The error happens when charcat.h CCharcat() is called and in particular when (*this)[CWord(letters[i])] = eFW is executed (if an empty CWord(letters[i]) line is put before this line then everything is okay. Is it static initialization fiasco? Not sure really.

   CTagger decoder(sFeatureFile, true, nMaxSentSize, bFWCDRule);
   if (!sKnowledgePath.empty()) decoder.loadKnowledge(sKnowledgePath);
   CSentenceReader outout_reader(sOutputFile);
   CStringVector *input_sent = new CStringVector;
   CTwoStringVector *outout_sent = new CTwoStringVector; 

   unsigned nCount=0;
   unsigned nErrorCount=0;

   CBitArray word_ends(tagger::MAX_SENTENCE_SIZE);

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
       isstack.open(sStackingPath.c_str());
       assert(isstack.is_open());
   }

#ifdef DEBUG
   CSentenceWriter outout_writer("");
#endif
   //
   // Read the next sentence
   //
   while( outout_reader.readTaggedSentence(outout_sent) ) {

       if(isstack.is_open())
       {
            stackfeats.clear();
            std::string line;
            getline(isstack, line);

            while(isstack && !line.empty())
            {
                CStackFeats node;
                std::istringstream iss(rstrip(line));
                iss >> node ;
                stackfeats.push_back( node );
                getline(isstack, line);
            }
       }

      if (bFWCDRule)
         UntagAndDesegmentSentence(outout_sent, input_sent, charcat);
      else
         UntagAndDesegmentSentence(outout_sent, input_sent);
      TRACE("Sentence " << nCount);
#ifdef DEBUG
      outout_writer.writeSentence(input_sent);
#endif
      ++nCount;
      //
      // Find the decoder outout
      //
      if (decoder.train(input_sent, stackfeats, outout_sent)) ++nErrorCount;
   }
   delete input_sent;
   delete outout_sent;
   std::cout << "Completing the training process." << std::endl;
   decoder.finishTraining(nCount);
   std::cout << "Done. Total errors: " << nErrorCount << std::endl;
}

/*===============================================================
 *
 * dumpfeatures
 *
 *==============================================================*/

void dumpfeatures(const std::string &sOutputFile, const std::string &sFeatureFile, const unsigned long &nMaxSentSize, const std::string &sKnowledgePath, const bool &bFWCDRule, const std::string &sStackingPath) {
   static CCharCatDictionary charcat ; // don't know why there is a segmentation fault when this is put as a global variable. The error happens when charcat.h CCharcat() is called and in particular when (*this)[CWord(letters[i])] = eFW is executed (if an empty CWord(letters[i]) line is put before this line then everything is okay. Is it static initialization fiasco? Not sure really.

   CTagger decoder(sFeatureFile, true, nMaxSentSize, bFWCDRule);
   if (!sKnowledgePath.empty()) decoder.loadKnowledge(sKnowledgePath);
   CSentenceReader outout_reader(sOutputFile);
   CStringVector *input_sent = new CStringVector;
   CTwoStringVector *outout_sent = new CTwoStringVector; 

   unsigned nCount=0;
   unsigned nErrorCount=0;

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
       isstack.open(sStackingPath.c_str());
       assert(isstack.is_open());
   }

   //
   // Read the next sentence
   //
   while( outout_reader.readTaggedSentence(outout_sent) ) {
       if(isstack.is_open())
       {
            stackfeats.clear();
            std::string line;
            getline(isstack, line);

            while(isstack && !line.empty())
            {
                CStackFeats node;
                std::istringstream iss(rstrip(line));
                iss >> node ;
                stackfeats.push_back( node );
                getline(isstack, line);
            }
       }

      if (bFWCDRule)
         UntagAndDesegmentSentence(outout_sent, input_sent, charcat);
      else
         UntagAndDesegmentSentence(outout_sent, input_sent);
      TRACE("Sentence " << nCount);
      ++nCount;
      //
      // Dump features now
      //
      decoder.dumpfeatures(input_sent, stackfeats, outout_sent);
   }
   delete input_sent;
   decoder.finishTraining(nCount);
   std::cout << "Done. " << std::endl;
}

/*===============================================================
 *
 * train
 *
 *==============================================================*/

void train(const std::string &sOutputFile, const std::string &sFeatureFile, const unsigned long &nBest, const unsigned long &nMaxSentSize, const bool &bEarlyUpdate, const bool &bSegmented, const std::string &sKnowledgePath, const bool &bFWCDRule, const std::string &sStackingPath) {
   static CCharCatDictionary charcat ; // don't know why there is a segmentation fault when this is put as a global variable. The error happens when charcat.h CCharcat() is called and in particular when (*this)[CWord(letters[i])] = eFW is executed (if an empty CWord(letters[i]) line is put before this line then everything is okay. Is it static initialization fiasco? Not sure really.

   CTagger decoder(sFeatureFile, true, nMaxSentSize, bFWCDRule);
   CSentenceReader outout_reader(sOutputFile);
#ifdef DEBUG
   CSentenceWriter outout_writer("");
   CSentenceWriter tagged_writer("");
#endif
   CStringVector *input_sent = new CStringVector;
   CTwoStringVector *tagged_sent = new CTwoStringVector[nBest];
   CTwoStringVector *outout_sent = new CTwoStringVector; 

   unsigned nCount=0;
   unsigned nErrorCount=0;
   unsigned nEarlyUpdateRepeat=0;

   CBitArray word_ends(tagger::MAX_SENTENCE_SIZE);

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
       isstack.open(sStackingPath.c_str());
       assert(isstack.is_open());
   }

   //
   // Read the next sentence
   //
   while( outout_reader.readTaggedSentence(outout_sent) ) {

       if(isstack.is_open())
       {
            stackfeats.clear();
            std::string line;
            getline(isstack, line);

            while(isstack && !line.empty())
            {
                CStackFeats node;
                std::istringstream iss(rstrip(line));
                iss >> node ;
                stackfeats.push_back( node );
                getline(isstack, line);
            }
       }

      if (bFWCDRule && !bSegmented)
         UntagAndDesegmentSentence(outout_sent, input_sent, charcat);
      else
         UntagAndDesegmentSentence(outout_sent, input_sent);
      TRACE("Sentence " << nCount);
      ++nCount;
      //
      // Find the decoder outout
      //
      if (bSegmented) {
         recordSegmentation( input_sent, outout_sent, word_ends );
         decoder.tag(input_sent, stackfeats, tagged_sent, NULL, nBest, &word_ends);
      }
      else {
         decoder.tag(input_sent, stackfeats, tagged_sent, NULL, nBest);
      }
      if (bEarlyUpdate) {
      //------------------------------------------------
      //
      // Early update
      //
      //------------------------------------------------
         if ( *tagged_sent != *outout_sent ) 
            ++nErrorCount;

         nEarlyUpdateRepeat = 0;
         while ( *tagged_sent != *outout_sent && nEarlyUpdateRepeat < 200 ) {
            //
            // Debug outout
            //
#ifdef DEBUG
            outout_writer.writeSentence(outout_sent);
#endif
            TRACE("------");
            for (unsigned i=0; i<nBest; ++i) if (*(tagged_sent+i)!=*outout_sent)
            {
#ifdef DEBUG
               tagged_writer.writeSentence(tagged_sent+i);
#endif
               decoder.updateScores(tagged_sent+i, outout_sent, nCount);
            }
            //
            // Find the decoder outout
            //
            if (bSegmented) {
               recordSegmentation( input_sent, outout_sent, word_ends );
               decoder.tag(input_sent, stackfeats, tagged_sent, NULL, nBest, &word_ends);
            }
            else 
               decoder.tag(input_sent, stackfeats, tagged_sent, NULL, nBest);

            nEarlyUpdateRepeat ++ ;
         } // while the sentence wrong
      }
      else {
      //------------------------------------------------
      //
      // Normal update
      //
      //------------------------------------------------
         if (*tagged_sent!=*outout_sent) {
#ifdef DEBUG
            outout_writer.writeSentence(input_sent);
            outout_writer.writeSentence(outout_sent);
#endif
            TRACE("------");  
            ++nErrorCount;
         }
         for (unsigned i=0; i<nBest; ++i) 
         {
#ifdef DEBUG
            if (*(tagged_sent+i)!=*outout_sent) tagged_writer.writeSentence(tagged_sent+i);
#endif
            decoder.updateScores(tagged_sent+i, outout_sent, nCount);
         }
      }
   }
   delete input_sent;
   delete outout_sent;
   delete [] tagged_sent;
   std::cout << "Completing the training process." << std::endl;
   decoder.finishTraining(nCount);
   std::cout << "Done. Total errors: " << nErrorCount << std::endl;
}

/*===============================================================
 *
 * main
 *
 *==============================================================*/

int main(int argc, char* argv[]) {
   try {
      COptions options(argc, argv);
      CConfigurations configurations;
      configurations.defineConfiguration("k", "Path", "use knowledge from the given path", "");
      std::ostringstream out; out << tagger::MAX_SENTENCE_SIZE;
      configurations.defineConfiguration("m", "M", "maximum sentence size", out.str());
      configurations.defineConfiguration("n", "N", "N best list train", "1");
      configurations.defineConfiguration("u", "", "early update", "");
      configurations.defineConfiguration("r", "", "do not use rules to segment numbers and letters", "");
      configurations.defineConfiguration("f", "", "dump features", "");
      configurations.defineConfiguration("e", "path", "external features for stacking", "");

      if (options.args.size() != 4) {
         std::cout << "\nUsage: " << argv[0] << " training_data model num_iterations" << std::endl ;
         std::cout << configurations.message() << std::endl;
         return 1;
      } 
      std::string warning = configurations.loadConfigurations(options.opts);
      if (!warning.empty()) {
         std::cout << "Warning: " << warning << std::endl;
      }

      unsigned long nBest, nMaxSentSize;
      if (!fromString(nMaxSentSize, configurations.getConfiguration("m"))) {
         std::cerr<<"Error: the max size of sentence is not integer." << std::endl; return 1;
      }
      if (!fromString(nBest, configurations.getConfiguration("n"))) {
         std::cerr<<"Error: the number of N best is not integer." << std::endl; return 1;
      }  
      bool bEarlyUpdate = configurations.getConfiguration("u").empty() ? false : true;
      bool bFWCDRule = configurations.getConfiguration("r").empty() ? true : false;
      std::string sKnowledgePath = configurations.getConfiguration("k");
      bool bDumpFeatures = configurations.getConfiguration("f").empty() ? false : true;
      std::string sStackingPath = configurations.getConfiguration("e");
      bool bSegmented = false;
#ifdef SEGMENTED
      bSegmented = true; // compile option
#endif

      unsigned training_rounds;
      if (!fromString(training_rounds, options.args[3])) {
         std::cerr << "Error: the number of training iterations must be an integer." << std::endl;
         return 1;
      }
      std::cout << "Training started." << std::endl;
      unsigned time_start = clock();
   if (bDumpFeatures) {
         // one single iteration: load knowledge
      std::cout << "Dumping features; only one iteration; no early update." << std::endl;
         dumpfeatures(argv[1], argv[2], nMaxSentSize, sKnowledgePath, bFWCDRule, sStackingPath);
   }
      else if (bSegmented) {
         // the first iteration: load knowledge
         train(argv[1], argv[2], nBest, nMaxSentSize, bEarlyUpdate, bSegmented, sKnowledgePath, bFWCDRule, sStackingPath);
         // from the next iteration knowledge will be loaded from the model
         // and therefore sKnowledgePath is set to "". Thus separate 'for'
         for (unsigned i=1; i<training_rounds; ++i)
            train(argv[1], argv[2], nBest, nMaxSentSize, bEarlyUpdate, bSegmented, "", bFWCDRule, sStackingPath);
      }
      else {
         // the first iteration: load knowledge
         auto_train(argv[1], argv[2], nBest, nMaxSentSize, sKnowledgePath, bFWCDRule, sStackingPath);
         // from the next iteration knowledge will be loaded from the model
         // and therefore sKnowledgePath is set to "". Thus separate 'for'
         for (unsigned i=1; i<training_rounds; ++i)
            auto_train(argv[1], argv[2], nBest, nMaxSentSize, "", bFWCDRule, sStackingPath);
      }
      std::cout << "Training has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
      return 0;
   } catch (const std::string &e) {
      std::cerr << "Error: " << e << std::endl;
      return 1;
   }
}

