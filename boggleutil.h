

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <string>
#include <vector>
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be 
//declared within your data structures.
//
//
using std::string;
using std::vector;
class TernaryNode
{
  public :
    TernaryNode(char c);
    bool end;

    TernaryNode* left;
    TernaryNode* right;
    TernaryNode* middle;
    char key;
};
class TernaryTrie
{

  public:
    TernaryTrie();

    void deleteTNode(TernaryNode* node);
//    void insertToTrie(TernaryNode* root, string word);
    TernaryNode* insert(TernaryNode* newNode, string word, unsigned int i);
    int find(string word);
    
    bool isChar(char c);
    bool isWord(string s);

  //  void buildTrie(TernaryTrie* trie, vector<string> wordList);
    ~TernaryTrie();

    
     
    TernaryNode *root;
};



#endif
