#include "AVLTree.hpp"
#include "BinTree.hpp"
#include "Funcoes.hpp"
#include "HuffTree.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
  
  setlocale(LC_ALL, "pt_BR.UTF-8");
  locale loc(locale(), new codecvt_utf8<wchar_t>);

  int k = 20;
  int numFiles = 6;
  
  Funcoes u;
  BinTree t;
  AVLTree AVLt;
  HuffTree Ht;
  
  unordered_set<wstring> input =
      u.getInput(loc); 
  vector<vector<pair<wstring, int>>> minHeap;
  vector<unordered_map<wstring, int>> frequenceMap;
  vector<unordered_map<wstring, int>>
      auxMap; 
  vector<pair<wstring, int>> proxTopK; 
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  
  auto start = chrono::high_resolution_clock::now();
  
  u.Welcome();
  u.makeFrequenciesMaps(
      loc, numFiles, frequenceMap); 
  u.makeHeaps(k, numFiles, frequenceMap, minHeap,
              proxTopK); 
  for (int i = 0; i < numFiles; i++) {
    unordered_map<wstring, int> dataMap;

    for (auto j = 0u; j < minHeap[i].size(); j++) {
      dataMap[minHeap[i][j].first] = j;
    }
    auxMap.push_back(dataMap);
  }

  ofstream File("output.txt", ios::out | ios::trunc);

  if (!File) {
    cerr << "Erro ao abrir o arquivo..." << endl;
    return 1;
  }

  for (auto aux : input) {
    for (int i = 0; i < numFiles; i++) {
      BinTree *raiz = nullptr;
      AVLTree *AVLRaiz = nullptr;
      HuffTree *HuffmanRaiz = nullptr;

      if (frequenceMap[i].find(aux) == frequenceMap[i].end()) {
        File << converter.to_bytes(aux) << endl
             << endl
             << "in" << i + 1 << endl
             << endl;
        File << "Esta palavra não existe no texto...!\n";
        File << "-----------------------------------------------"
                "---------------\n\n";
      } else {
        if (auxMap[i].find(aux) != auxMap[i].end()) {
          vector<pair<wstring, int>> auxMinHeap = minHeap[i];
          u.swapMinHeap(auxMinHeap, auxMap[i][aux], proxTopK, i);

          File << converter.to_bytes(aux) << endl
               << endl
               << "in" << i + 1 << endl
               << endl;
          Ht.createHuffTree(HuffmanRaiz, auxMinHeap);
          for (auto w : auxMinHeap) {
            t.insertBinTree(&raiz,
                            make_pair(converter.to_bytes(w.first), w.second));
            AVLt.insertAVLTree(
                &AVLRaiz, make_pair(converter.to_bytes(w.first), w.second));
          }
          t.printBinTree(raiz, File);
          t.destroyBinTree(raiz);

          AVLt.printAVLTree(AVLRaiz, File);
          AVLt.destroyAVLTree(AVLRaiz);

          Ht.printHuffTree(HuffmanRaiz, File);
          Ht.destroyHuffTree(HuffmanRaiz);
        } else {
          File << converter.to_bytes(aux) << endl
               << endl
               << "in" << i + 1 << endl
               << endl;
          Ht.createHuffTree(HuffmanRaiz, minHeap[i]);
          for (auto w : minHeap[i]) {
            t.insertBinTree(&raiz,
                            make_pair(converter.to_bytes(w.first), w.second));
            AVLt.insertAVLTree(
                &AVLRaiz, make_pair(converter.to_bytes(w.first), w.second));
          }
          t.printBinTree(raiz, File);
          t.destroyBinTree(raiz);

          AVLt.printAVLTree(AVLRaiz, File);
          AVLt.destroyAVLTree(AVLRaiz);

          Ht.printHuffTree(HuffmanRaiz, File);
          Ht.destroyHuffTree(HuffmanRaiz);
        }
      }
    }
  }
  File.close();
  u.printHeap(minHeap[0]);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  wcout << endl << "Latencia: " << duration.count() << " ms" << endl;
  
  return 0;
}
