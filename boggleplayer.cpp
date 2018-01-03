/*
 * Author: Tianyi Li
 * PID: A12002286
 *
 * Program: boggle game.
 * 
 * Description: this file contains the functions for boggle player which 
 *        response to calculate all the path of the board. and check 
 *        whether the word is exist in board or list. return message to
 *        the user.
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "boggleplayer.h"
#include "boggleutil.h"

using namespace std;



/* Function: buildLexicon
 * This function is going to take a list of word to build a lexicon 
 * by using Ternary trie. In the progress of building a trie, it shuffle
 * the sequence of list to avoid worst case of trie.
 *  
 */
void BogglePlayer::buildLexicon(const set<string>& word_list)
{
  // set up random seed.
  //
  std::srand(time(0));
  
  // if the lexicon already built. delete the current.
  //
  if(isBuildLex == true)
  {
    delete lexicon;
  }
  
  
  set<string>::iterator it;
  vector<string> shuffledVector;
  
  // push all words into a vector to shuffle it.
  //
  for(it = word_list.begin(); it != word_list.end(); ++it)
  {
    shuffledVector.push_back(*it);
  }
   
  // shuffling.
  //
  random_shuffle(shuffledVector.begin(), shuffledVector.end());
  
  // call the constructor of Ternary trie, and get ready to build lexicon.
  //
  lexicon = new TernaryTrie();
  
  // using iterator to call insertion of lexicon.
  //
  for(it = word_list.begin(); it != word_list.end(); ++it)
  {
    lexicon->root = lexicon->insert(lexicon->root, *it, 0);
  }

  // set the flag for check after function.
  //
  isBuildLex = true;

}


/* Function: setBoard()
 * Description: This function is going to build board by passed in rows and
 *        columns. using dice array as the face of dice in boggle game.
 *        Also using tolower for them to make sure all the letters in game
 *        are lower case.
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols,
    string** diceArray) 
{  
  // get the size of board.
  //
  
  setRow = rows;
  setCol = cols;
  int count = rows * cols;
  // create a board contains strings.
  //
  board = new string[count];
  unsigned int index = 0;

  for(unsigned int i = 0; i < rows; i++)
  {
    for(unsigned int j = 0; j < cols; j++)
    {
      string lowerStr = diceArray[i][j];

      // using an extra loop to implement tolower.
      //
      for(unsigned int k = 0; k < lowerStr.length(); k++)
      {
        lowerStr[k] = tolower(lowerStr[k]);
      }
      board[index] = lowerStr;

      index++;
    }
  }
  
  // set up a flag
  //
  isSetBoard = true;
  
}

// Function: getAllValidWords()
// Description: This function is going to reach all the possible of word
//      on the board recursively. if it reach the non-board word. it will
//      return from current recursion. If the board and lexicon not built
//      yet. return false. otherwise return true.
//      
// Minimum_word_length: the minimum word legnth we will search.
// words: a set of strings which will contains the result of search.
//
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, 
    set<string>* words) 
{
  // if not built yet, return false.
  //
  if(isSetBoard == false || isBuildLex == false)
  {
    return false;
  }
  
  // setup a int array to show which string we already met.
  //
  
  int count = setRow * setCol;
  int* stepped = new int[count];
  //int stepped[count];
  
  // traverse each letter on board as a head of words.
  //
  for(int i = 0; i < count; i++)
  {
    // reset stepped string of board.
    //
    for(int j = 0; j < count; j++)
    {
      stepped[j] = 0;
    }
    stepped[i] = 1;
    
    // call the function recursively, to find other step around the first.
    //
    getAllValidWordsRecur(board[i],i, minimum_word_length, stepped, words);
  }
  
  delete stepped;
  return true;
}

void BogglePlayer::getAllValidWordsRecur(string prefixStr, int position, 
    unsigned int mininumLength,  int steppedCheck[], set<string>* words)
{

  // if the prefix string reach the mininum length of required
  //
  if(prefixStr.length() + 1 >  mininumLength)
  { 
    int findWord = lexicon->find(prefixStr);
    // if word is found, insert the word into result set.
    //
    if(findWord == 1)
    {
      words->insert(prefixStr);
    }
    // if the prefix is found, but is not the final word we tried to search.
    // therefore the word not in the lexicon.
    //
    if(findWord == 0)
    {
      return;
    }
  }
  // locate the next step, starts on 12'oclock by clockwise.
  //
  int stepArray[STEPDIRECTIONS] = 
  { 
    position - setCol, position - setCol + 1, position + 1,
    position + setCol + 1, position + setCol, position + setCol - 1,
    position - 1, position - setCol - 1
  };
  
  // if the step located is out of boundries of board, set them to -1.
  //
  checkStepBoundries(stepArray, position);
  
  // traverse all near step if available.
  //
  for(int i = 0; i < STEPDIRECTIONS; i++)
  {
    if(stepArray[i] >= 0 && steppedCheck[stepArray[i]] != 1)
    { 
      // call next step recursively.
      //
      steppedCheck[stepArray[i]] = 1;
      getAllValidWordsRecur(prefixStr + board[stepArray[i]], stepArray[i], 
          mininumLength, steppedCheck, words);
      steppedCheck[stepArray[i]] = 0;
    }
  }
}

// using find() to return the result of search word in lexicon(trie)
//
bool BogglePlayer::isInLexicon(const string& word_to_check) {
  if(lexicon->find(word_to_check) == 1)
   {
      return true;
   }
  else
  {
    return false;
  }
}

// Function: isOnBoard()
// Description: This function is going to find the parameter word. recursively
//      to check whether exist on the board.
//
vector<int> BogglePlayer::isOnBoard(const string& word) 
{
  // using vector to store the result position of word.
  //
  vector<int> result;
  string stringLeft = "";

  int count = setRow * setCol;
  //int stepped[count];
  //
  int* stepped = new int[count];
  
  // initialize the step check on board.
  //
  for(int i = 0; i < count; i++)
  {
    stepped[i] = 0;
  }
  
  // for the special case that the word only has 1 string length.
  //
  bool onlyOneString = false;

  if(isSetBoard == false)
  {
    delete stepped;
    return result;
  }
  
  // to lower of word search.
  //
  for(unsigned int i = 0; i < word.length(); i++)
  {
    stringLeft += tolower(word[i]);  
  }  

 
  // traverse all the letters in the board as first prefix.
  //
  for(int i = 0; i < count; i++)
  {

    // if the string at the position of word equal to current letter of 
    // board.
    //
    if(strcmp(board[i].c_str(),
          stringLeft.substr(0,board[i].length()).c_str()) == 0)
    {
      foundWordOnBoard = false;
      
      // check the step.
      //
      stepped[i] = 1;
      result.push_back(i);
      
      // if the length is equal before call the recursion. therefore
      // the length is equal to each other. there is only one string exist.
      //
      if(board[i].length() == stringLeft.length())
      {
        onlyOneString = true;
      }
      // recusively find the next step.
      //
      findOnBoardRecur(stringLeft.substr(
            board[i].length(), stringLeft.length()), i,result, stepped);
    }
    
    // return the result of found.
    //
    if(result.size() > 1)
    {
      delete stepped;
      return result;
    }
    
    // if one string only. return result.
    //
    if(onlyOneString == true && result.size() == 1)
    {
      delete stepped;
      return result;
    }
  }
    
    // otherwise we didnot find the word. clear the result.
    //
    delete stepped;
    result.clear();
    return result;
}

void BogglePlayer::findOnBoardRecur( string word, int& position, 
     vector<int> &result, int steppedCheck[])
{
  // have a flag to return immidiately if find the word already.
  //
  bool foundInLoop = false;
  
  // if found the word, therefore the postfix of string is null.
  //
  if(word.length() == 0)
  {
    foundWordOnBoard = true;
    return;
  }
  
  // find the steps and check the boundries.
  //
  int stepArray[STEPDIRECTIONS] = 
  { 
    position - setCol, position - setCol + 1, position + 1,
    position + setCol + 1, position + setCol, position + setCol - 1,
    position - 1, position - setCol - 1
  };

  checkStepBoundries(stepArray, position);
  
  // go over 8 directions.
  //
  for(int i = 0; i < STEPDIRECTIONS; i++)
  {
    if(stepArray[i] >= 0 && steppedCheck[stepArray[i]] != 1)
    {
      // if not found the word and found the same string in the position
      //
      if( foundWordOnBoard == false &&
          strcmp(board[stepArray[i]].c_str(), word.substr(0, 
              board[stepArray[i]].length()).c_str()) == 0)
      {
        // push the substring into result.
        //
        result.push_back(stepArray[i]);
        steppedCheck[stepArray[i]] = 1;

          foundInLoop = true;
          // searching for next step.
          //
          findOnBoardRecur(word.substr(board[stepArray[i]].length(),
                word.length()),
             stepArray[i], result, steppedCheck);
      }
    }
  }
  
  // if not found any same substring inthe loop, pop back the last sub str.
  //
  if(foundInLoop == false)
  {
    steppedCheck[position] = 0;
    result.pop_back();
  }

  

}

void BogglePlayer::checkStepBoundries(int stepArray[], int position)
{
  for(int i = 0; i < STEPDIRECTIONS; i++)
  {
    if(stepArray[i] < 0 || stepArray[i] >= (setCol * setRow))
    {
      stepArray[i] = -1;
    }
  }

  if( position % setCol == 0)
  {
    stepArray[5] = -1;
    stepArray[6] = -1;
    stepArray[7] = -1;
  }

  if(position % setCol == (setCol - 1))
  {
    stepArray[1] = -1;
    stepArray[2] = -1;
    stepArray[3] = -1;
  }
}




void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows,
    unsigned int *cols) 
{
  
  *rows = 4;
  *cols = 4;
//  const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
  new_board = new string*[*rows];

  for(unsigned int i = 0; i < *rows; i++)
  {
    new_board[i] = new string[*cols];
  }
  
  new_board[0][0] = "o";
  new_board[0][1] = "w";
  new_board[0][2] = "r";
  new_board[0][3] = "n";

  new_board[1][0] = "s";
  new_board[1][1] = "s";
  new_board[1][2] = "t";
  new_board[1][3] = "i";

  new_board[2][0] = "r";
  new_board[2][1] = "a";
  new_board[2][2] = "l";
  new_board[2][3] = "r";

  new_board[3][0] = "s";
  new_board[3][1] = "k";
  new_board[3][2] = "c";
  new_board[3][3] = "e";
  //std::srand(time(0));
  /*
  for(unsigned int i = 0; i < *rows; i++)
  {
    for(unsigned int j = 0; j < *cols; j++)
    {
      new_board[i][j] = alpha[rand() % 26];
    }
  }
  */

}


