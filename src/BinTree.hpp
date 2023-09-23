#include <bits/stdc++.h>

#ifndef BINTREE_HPP
#define BINTREE_HPP

using namespace std;

class BinTree
{
  private:
    pair<string, int> data;
    BinTree* left;
    BinTree* right;

  public:
    BinTree();

    void insertBinTree(BinTree **t, const pair<string, int>& word);
    void destroyBinTree(BinTree *t);
    void printBinTreePosOrdem(BinTree *t, ofstream& outputFile);
    void printBinTreePreOrdem(BinTree *t, ofstream& outputFile);
    void printBinTreeInOrdem(BinTree *t, ofstream& outputFile);
    void printBinTree(BinTree *t, ofstream& outputFile);
};

#endif

