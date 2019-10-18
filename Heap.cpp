#include <iostream>
using namespace std;
#include <vector>
#include "Heap.hpp"

Heap :: Heap(int cap)
{
  currentSize = 0;
  capacity = cap;
  heapArr = new heapSong[capacity];
}

Heap :: ~Heap()
{
  delete [] heapArr;
}

/*
Returns the parent of a node
*/
int Heap::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int Heap::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int Heap::rightChild(int index)
{
  return ((2*index) + 2);
}

void swap(heapSong *a, heapSong *b)
{
  heapSong temp = *a;
  *a = *b;
  *b = temp;
}

void Heap :: repairUpward(int index)
{
    int parentIndex = parent(index);

    if(index < 1)
    {
      return;
    }

    if(heapArr[index].globalPlays >= heapArr[parentIndex].globalPlays)
    {
      swap(&heapArr[index], &heapArr[parentIndex]);
      repairUpward(parentIndex);
    }
    return;
}

void Heap :: addheapSong(string newtitle, string newgenre, string newartist, int gPlays)
{
  if(currentSize == capacity)
  {
    cout << "Library is full! " << endl;
    return;
  }

  heapSong insert = heapSong();
  insert.title = newtitle;
  insert.genre = newgenre;
  insert.artist = newartist;
  insert.globalPlays = gPlays;

  heapArr[currentSize] = insert;
  repairUpward(currentSize);
  currentSize++;

}

void Heap :: repairDownward(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);

    int largest = index;
    //TODO
    if(l < currentSize && heapArr[l].globalPlays > heapArr[index].globalPlays)
    {
      largest = l;
    }
    if(r < currentSize && heapArr[r].globalPlays > heapArr[largest].globalPlays)
    {
      largest = r;
    }

    if(largest != index)
    {
      swap(&heapArr[index], &heapArr[largest]);
      repairDownward(largest);
    }
}

heapSong *Heap :: deleteheapSong()
{
  if(currentSize == 0)
  {
    cout << "No more heapSongs in the library!" << endl;
    return NULL;
  }
  heapSong *temp = new heapSong();

  temp->title = heapArr[0].title;
  temp->genre = heapArr[0].genre;
  temp->artist = heapArr[0].artist;
  temp->globalPlays = heapArr[0].globalPlays;
  temp->next = heapArr[0].next;
  temp->shuffleNext = heapArr[0].shuffleNext;
  //cout << "HeapArr[0]: " << heapArr[0].title << endl;
  heapArr[0] = heapArr[currentSize-1];
  currentSize--;
  repairDownward(0);
  //cout << "HeapArr[0]: " << heapArr[0].title << endl;
  //cout << "Delete song returns: " << temp->title << endl;
  return temp;
}

void Heap :: printTopN()
{
  string stop;
  int top = 1;

  cout << "How many songs from the Top Charts would you like to see? " << endl;
  getline(cin, stop);
  top = stoi(stop);

  if(top == 0)
  {
    return ;
  }

  vector <heapSong*> deleted;

  for(int i =0; i < top; i++)
  {
    heapSong *temp = deleteheapSong();
    if(temp!=NULL)
    {
      cout << "Title: " << temp->title << " Global Plays: " << temp->globalPlays << endl;
      deleted.push_back(temp);
    }
    else
      break;
      //cout << "Temp: " << temp->title << endl;
  }

  cout << endl;
  //cout << "Printing deleted vector!" << endl;
  for(int i = 0; i < deleted.size(); i++)
  {
    //cout << "Title: " << deleted[i]->title << " Global Plays: " << deleted[i]->globalPlays << endl;
    addheapSong(deleted[i]->title, deleted[i]->genre, deleted[i]->artist, deleted[i]->globalPlays);
  }
}

//string newtitle, string newgenre, string newartist, int gPlays

void Heap :: printHeapArray()
{
    for(int i =0; i < currentSize; i++)
    {
      cout << "Title: " << heapArr[i].title << " Global Plays:" << heapArr[i].globalPlays << endl;
    }
}
