#include "HuffTree.hpp"

void HuffTree::createHuffTree(HuffTree*& t, vector<pair<wstring, int>>& data)
{
  priority_queue<HuffTree*, vector<HuffTree*>, comp> pq;

  for (const pair<wstring, int>& word : data)
  {
    HuffTree* aux = new HuffTree;

    pair<wstring, int> data;

    data.second = word.second;
    data.first = word.first;

    aux->prob = word.second;

    aux->data = data;

    aux->left = nullptr;
    aux->right = nullptr;

    pq.push(aux);
  }

  while (pq.size() > 1)
  {
    HuffTree* left = pq.top();
    pq.pop();

    HuffTree* right = pq.top();
    pq.pop();

    HuffTree* aux = new HuffTree;

    aux->prob = left->prob + right->prob;
    aux->left = left;
    aux->right = right;

    pq.push(aux);
  }

  t = pq.top();
}

void HuffTree::destroyHuffTree(HuffTree* t)
{
  if (t == nullptr)
  {
    return;
  }

  destroyHuffTree(t->left);
  destroyHuffTree(t->right);

  delete t;
}


void HuffTree::printHuffTreePosOrdem(HuffTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;

  if (t == nullptr)
  {
    return;
  }

  printHuffTreePosOrdem(t->left, outputFile, code + "0");
  printHuffTreePosOrdem(t->right, outputFile, code + "1");

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }
}

void HuffTree::printHuffTreePreOrdem(HuffTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  
  if (t == nullptr)
  {
    return;
  }

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }

  printHuffTreePreOrdem(t->left, outputFile, code + "0");
  printHuffTreePreOrdem(t->right, outputFile, code + "1");
}

void HuffTree::printHuffTreeInOrdem(HuffTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;

  if (t == nullptr)
  {
    return;
  }

  printHuffTreeInOrdem(t->left, outputFile, code + "0");

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }

  printHuffTreeInOrdem(t->right, outputFile, code + "1");
}

void HuffTree::printHuffTree(HuffTree* t, ofstream& outputFile)
{
  outputFile << "]\n\nHuffman Tree (Pos-Ordem):\n[";
  printHuffTreePosOrdem(t, outputFile, ""); 

  outputFile << "]\n\nHuffman Tree (Pre-Ordem):\n[";
  printHuffTreePreOrdem(t, outputFile, "");

  outputFile << "]\n\nHuffman Tree (In-Ordem):\n[";
  printHuffTreeInOrdem(t, outputFile, "");
  outputFile << "]\n-----------------------------------------------------------------------------\n\n";
}
