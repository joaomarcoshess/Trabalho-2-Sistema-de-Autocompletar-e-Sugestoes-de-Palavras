#include <bits/stdc++.h>

#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

using namespace std;

class HuffTree
{
  private:
    pair<wstring, int> data;
    int prob;
    HuffTree* left;
    HuffTree* right;

    struct comp
    {
      constexpr bool operator()(HuffTree* const& a, HuffTree* const& b) const noexcept
      {
        return a->prob >= b->prob;
      }
    };

  public:
    void createHuffTree(HuffTree*& t, vector<pair<wstring, int>>& data);
    void destroyHuffTree(HuffTree* t);
    void printHuffTreePosOrdem(HuffTree* t, ofstream& outputFile, string code);
    void printHuffTreePreOrdem(HuffTree* t, ofstream& outputFile, string code);
    void printHuffTreeInOrdem(HuffTree* t, ofstream& outputFile, string code);
    void printHuffTree(HuffTree* t, ofstream& outputFile);
    
};

#endif
