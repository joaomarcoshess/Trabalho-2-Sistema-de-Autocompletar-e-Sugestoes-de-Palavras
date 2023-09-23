#include "BinTree.hpp"

BinTree::BinTree()
{
}

void BinTree::insertBinTree(BinTree **t, const pair<string, int>& word)
{
  if (*t == nullptr)
  {
    *t = new BinTree;
    (*t)->data = word;
    (*t)->left = nullptr;
    (*t)->right = nullptr;
  }
  else
  {
    BinTree *aux = *t;
    
    while(aux != nullptr)
    {
      if(word.second <= aux->data.second)
      {
        if (aux->left == nullptr)
        {
          aux->left = new BinTree;
          aux = aux->left;
          aux->data = word;
          aux->left = nullptr;
          aux->right = nullptr;
        }
        aux = aux->left;
      }
      else
      {
        if (aux->right == nullptr)
        {
          aux->right = new BinTree;
          aux = aux->right;
          aux->data = word;
          aux->left = nullptr;
          aux->right = nullptr;
        }
        aux = aux->right;
      }
    }
  }
}

void BinTree::destroyBinTree(BinTree *t)
{
  if (t == nullptr)
  {
    return;
  }
  
  destroyBinTree(t->left);
  destroyBinTree(t->right);
  
  delete t;
}

void BinTree::printBinTreePosOrdem(BinTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printBinTreePosOrdem(t->left, outputFile); 
    printBinTreePosOrdem(t->right, outputFile); 
    outputFile << t->data.first << " : " << t->data.second << " / ";
  }
}

void BinTree::printBinTreePreOrdem(BinTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printBinTreePreOrdem(t->left, outputFile);
    printBinTreePreOrdem(t->right, outputFile);
  }
}

void BinTree::printBinTreeInOrdem(BinTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printBinTreeInOrdem(t->left, outputFile);
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printBinTreeInOrdem(t->right, outputFile);
  }
}

void BinTree::printBinTree(BinTree *t, ofstream& outputFile)
{
  outputFile << "Binary Tree (Pós-Ordem):\n[";
  printBinTreePosOrdem(t, outputFile); 

  outputFile << "]\n\nBinary Tree (Pré-Ordem):\n[";
  printBinTreePreOrdem(t, outputFile);

  outputFile << "]\n\nBinary Tree (In-Ordem):\n[";
  printBinTreeInOrdem(t, outputFile);
}

