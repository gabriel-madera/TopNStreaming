#include <iostream>
using namespace std;

#ifndef HEAP_HPP
#define HEAP_HPP


struct heapSong
{
    string title;
    string genre;
    string artist;
    int globalPlays;
    heapSong *next = NULL;
    heapSong *shuffleNext = NULL;
};

class Heap
{
    public:
      Heap(int capacity);
      ~Heap();

      int parent(int index);
      int leftChild(int index);
      int rightChild(int index);

      void addheapSong(string title, string genre, string artist, int gPlays);
      heapSong* deleteheapSong();
      void repairUpward(int index);
      void repairDownward(int index);

      void printTopN();
      void printHeapArray();

    private:
      heapSong* heapArr;
      int currentSize;
      int capacity;
};

#endif
