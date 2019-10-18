#include <iostream>
using namespace std;
#include "Heap.hpp"
#include <fstream>
#include <sstream>
#include "GenreHash.hpp"

int main()
{
  Heap heap_test(80);
  GenreHash test(9);
  string title, artist, genre, plays, filename;
  filename = "ReadFile.txt";
  ifstream inFile;
  inFile.open(filename);
  if(inFile.fail())
  {
    cout << "Read File Failed";
    return 0;
  }
  else
  {
    string line;
    while(getline(inFile,line))
    {
        stringstream ss;
        ss<<line;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, plays, ',');

        test.add(title, genre, artist, stoi(plays));
        heap_test.addheapSong(title, genre, artist, stoi(plays));
    }
  }

  while(true)
  {
  string userN;
  cout << endl << "Please enter your username or enter (q) to quit the program." << endl;
  getline(cin, userN);

  if(userN == "q")
  {
    cout << "Goodbye! " << endl;
    return 0;
  }

  User *curr_user = test.searchUser(userN);
  if(curr_user == NULL)
  {
    curr_user =test.addUser(userN);
  }

  string sChoice;
  int choice = 1;
  while(choice != 9)
  {
    cout << endl;
    cout << "You are currently logged in as: " << curr_user->username << endl;
    cout << "============Main Menu============" << endl;
    cout << "Please select an option." << endl;
    cout << "1. Print entire library" << endl;
    cout << "2. Get Genre Counts" << endl;
    cout << "3. Add Song to my Playlist" << endl;
    cout << "4. Delete Song from my Playlist" << endl;
    cout << "5. Print my library" << endl;
    cout << "6. Get Recommended Playlist" << endl;
    cout << "7. See Global Top Charts" << endl;
    cout << "8. See Genre Top 10s" << endl;
    cout << "9. Log Out" << endl;
    cout << "0. Quit Program" << endl;
    getline(cin, sChoice);
    choice = stoi(sChoice);

    if(choice == 1)
    {
      test.printTable();
    }
    else if(choice == 2)
    {
      test.getGenreCount();
    }
    else if(choice == 3)
    {
      string stitle, sgenre;
      cout << "Enter a song you would like to add." << endl;
      getline(cin, stitle);
      cout << "What genre is this song? " << endl;
      getline(cin, sgenre);
      Song *sSong = test.searchSong(stitle, sgenre);
      //cout << "sSong " << sSong->title << endl;
      test.addSongToPlaylist(sSong, curr_user);
    }
    else if(choice == 4)
    {
      string stitle, sgenre;
      cout << "Enter a song you would like to delete." << endl;
      getline(cin, stitle);
      cout << "What genre is this song? " << endl;
      getline(cin, sgenre);
      Song *deleteS = test.searchSong(stitle, sgenre);
      test.deleteSongFromPlaylist(deleteS, curr_user);
    }
    else if(choice == 5)
    {
      test.printUserPlaylist(curr_user);
    }
    else if(choice == 6)
    {
      test.recommend_songs(curr_user);
    }
    else if(choice == 7)
    {
      heap_test.printTopN();
    }
    else if(choice == 8)
    {
        string genre;
        cout << "Which genre's Top 10 would you like to see? " << endl;
        getline(cin, genre);
        test.printGenreTop10(genre);
    }

    if(choice == 0)
    {
      cout << "Goodbye!" << endl;
      return 0;
    }
  }
}
}
