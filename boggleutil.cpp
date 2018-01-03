/*
 *
 *
 * Author: Tianyi Li
 * PID: A12002286
 *
 *
 * The file boggleutil contains the function of Ternary tire. 
 * 
 */
#include <stdio.h>
#include <iostream>
#include"boggleutil.h"

using namespace std;
//In this file, implement all of the operations your data structures 
//support (you have declared these operations in boggleutil.h).
//
//
// TernaryNode: left right middle  end key
// root

TernaryTrie::TernaryTrie()
{
  root = 0;
}

TernaryTrie::~TernaryTrie()
{
  deleteTNode(root);
}

// delete  all the node of Ternary trie.
//
void TernaryTrie::deleteTNode(TernaryNode* node)
{
  if(node == 0)
  {
    return;
  }

  deleteTNode(node->left);
  deleteTNode(node->right);
  deleteTNode(node->middle);

  delete node;
}


// Insert the word into correct position of Ternary trie.
//
TernaryNode* TernaryTrie::insert(TernaryNode* node, string word, unsigned int i)
{
  if(node == 0)
  {
    node = new TernaryNode(word[i]);
  }
  
  // the value less than, go left.
  //
  if(word[i] < node->key)
  {
    node->left = insert(node->left, word, i);
  }
  // larger than, go right.
  //
  else if(word[i] > node->key)
  {
    node->right = insert(node->right, word, i);
  }
  // else. put char under the middle.
  //
  else
  {
    if(word.length() == i + 1)
    {
      node->end = true;
    }
    else
    {
      node->middle = insert(node->middle, word, i + 1);
    }
  }

  return node;
}

int TernaryTrie::find(string word)
{
  unsigned int i = 0;

  TernaryNode* curr = root;
  
  while(curr != 0)
  {
   
    if(word[i] < curr->key)
    {
      curr = curr->left;
    }
    else if(word[i] > curr->key)
    {
      curr = curr->right;
    }
    else
    {
      if( word.length() == i + 1 && curr->end)
      {
        return 1;
      }
      
      if(word.length() == i + 1)
      {
        return -1;
      }
      i++;
      curr = curr->middle;
    }
  }
  
  return 0;
}


bool TernaryTrie::isChar(char c)
{
  return 'a' <= c && c <= 'z';
}

bool TernaryTrie::isWord(string s)
{
  for(unsigned int i = 0; i < s.length(); i++)
  {
    if(!isChar(s[i]))
    {
      return false;
    }
  }

  return true;
}



TernaryNode::TernaryNode(char c)
{
  middle = 0;
  left = 0;
  right = 0;
  key = c;
  end = false;

}
