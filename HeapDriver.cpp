#include <iostream>
using namespace std;
#include "Heap.hpp"

int main()
{
  Heap test(10);

  test.addheapSong("old town road", "rap", "lil nas X", 2934496);
  test.addheapSong("bad guy", "alternative", "billie eilish", 1871234);
  test.addheapSong("sunflower", "pop","post malone", 1181345);
  test.addheapSong("middle child", "rap", "j cole", 1121875);
  test.addheapSong("wish you were gay", "alternative", "billie eilish", 1115261);
  test.addheapSong("swervin", "rap", "a boogie wit da hoodie", 1059969);
  test.addheapSong("sanguine paradise", "rap", "lil uzi vert", 1064364);  //

  //cout << endl << endl;
  //test.printHeapArray();

  cout << endl << endl;

   test.printTopN();

   //test.printHeapArray();



}
