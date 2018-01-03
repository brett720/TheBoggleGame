

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include <set>
#include "baseboggleplayer.h"
#include "boggleutil.h"
using namespace std;


#define STEPDIRECTIONS 8

class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  void getAllValidWordsRecur(string prefixStr, int position, 
        unsigned int mininumLength, int steppedCheck[],
        set<string>* words);
  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows,
      unsigned int *cols);

  BogglePlayer() {
    lexicon = 0;
    isSetBoard = false;
    isBuildLex = false;
    setRow = 0;
    setCol = 0;
  }
  
  ~BogglePlayer() {
    delete lexicon;
  }

  private:
    string* board;
    bool isSetBoard;
    bool isBuildLex;
    
    bool foundWordOnBoard;
    
    TernaryTrie* lexicon;

    int setRow;
    int setCol;
    int count;
    void findOnBoardRecur(string word, int &position, 
         vector<int> &result, int steppedCheck[]);
    void checkStepBoundries(int stepArray[], int position); 
};

#endif
