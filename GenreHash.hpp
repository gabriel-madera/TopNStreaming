#include <iostream>
#include <vector>
using namespace std;

#ifndef GENREHASH_HPP
#define GENREHASH_HPP


struct Song
{
    string title;
    string genre;
    string artist;
    int globalPlays;
    Song *next = NULL;
    Song *shuffleNext = NULL;
};

struct User
{
	string username;
	Song* playlistHead;
	Song* recommendListHead;
	int numberSongs;
};


class GenreHash
{
  public:
  //Constructor
  GenreHash(int hashTableSize);
  //Destructor
  ~GenreHash();
  void add(string title, string genre, string artist, int gPlays);
  //void addFromHeap(Song *temp);
  void printTable();
  void getGenreCount();
  void printGenreTop10(string);

  Song* searchSong(string, string);
  void addSongToPlaylist(Song*, User*);
  void deleteSongFromPlaylist(Song*, User*);
  void printUserPlaylist(User*);
  void deleteRecommendedPlaylist(User*);

  int recommend_helper(Song*);
  bool isInPlaylist(Song* head, Song* check);
  void recommend_songs(User* u1);

  User* addUser(string);
  User* searchUser(string);

  private:
  unsigned int getHash(int word);

  Song** hashTable;
  int hashTableSize;
  int numSongs;

  vector <User*> users;

};
#endif
