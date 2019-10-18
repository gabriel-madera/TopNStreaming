#include <iostream>
#include <vector>
using namespace std;
#include "GenreHash.hpp"

//Genre Key
//Rap == 0
//Alternative == 1
//Country == 2
//Hip Hop == 3
//Pop == 4
//Rock == 5
//EDM == 6
//r&b == 7

GenreHash :: GenreHash(int hashTableSize)
{
    hashTable = new Song*[hashTableSize];
    this->hashTableSize = hashTableSize;
    numSongs = 0;
    for(int i =0; i < hashTableSize;i++)
    {
        hashTable[i] = NULL;
    }

    // userPlaylistHead = NULL;
    // recommendedPlaylistHead = NULL;
}

GenreHash:: ~GenreHash()
{
    for(int i =0; i < hashTableSize;i++)
    {
        while(hashTable[i] != NULL)
        {
            Song *temp = hashTable[i];
             hashTable[i] = hashTable[i]->next;
             delete temp;
        }
    }
}

unsigned int hashFunction(string genre)
{
    if(genre == "rap")
    {
        return 0;
    }
    else if(genre == "alternative")
    {
        return 1;
    }
    else if(genre == "country")
    {
        return 2;
    }
    else if(genre == "hip-hop")
    {
        return 3;
    }
    else if(genre == "pop")
    {
        return 4;
    }
    else if(genre == "rock")
    {
        return 5;
    }
    else if(genre == "edm")
    {
        return 6;
    }
    else if(genre == "r&b")
    {
        return 7;
    }
    else
    {
      return 8;
    }
}

User* GenreHash :: addUser(string name)
{
    User *insert = new User();
    insert->username = name;
    insert->numberSongs = 10;
    insert->playlistHead = NULL;
    insert->recommendListHead = NULL;

    users.push_back(insert);

    return insert;
}

User* GenreHash :: searchUser(string name)
{
    for(int i =0 ;i < users.size();i++)
    {
      if(users[i]->username == name)
      {
        return users[i];
      }
    }
    return NULL;
}

void GenreHash :: add(string newTitle, string newGenre, string newArtist, int gPlays)
{
     int index = hashFunction(newGenre);
      Song *insert = new Song();
      insert->title = newTitle;
      insert->genre = newGenre;
      insert->artist = newArtist;
      insert->globalPlays = gPlays;

    if (hashTable[index]== NULL)
    {
        hashTable[index] = insert;
        numSongs++;
        return;
    }
      Song* temp = hashTable[index];
      if(temp->globalPlays<insert->globalPlays)
      {
        insert->next = hashTable[index];
        hashTable[index] = insert;
        numSongs++;
        return;
      }
      while(temp != NULL)
      {
        if((temp->next == NULL)||(temp->next->globalPlays<insert->globalPlays))
        {
            break;
        }
        temp=temp->next;
      }
      insert->next = temp->next;
      temp->next = insert;
      numSongs++;
}

void GenreHash :: printTable()
{
  Song *temp;
  cout << "Songs will be printed according to genre. Rap -> Alternative -> Country -> Hip-Hop -> Pop -> Rock -> EDM -> R&B -> Other Genres" << endl;
  for(int i =0; i < hashTableSize;i++)
  {
      temp = hashTable[i];
      cout << "-----------------------------------------------------------------" << endl;
      if(temp != NULL)
      {
        while(temp != NULL)
        {
            cout <<"|Title: " << temp->title <<" Artist: " << temp->artist << " Genre: " << temp->genre << " Plays: " << temp->globalPlays << endl;
            temp = temp->next;
        }
        cout << endl;
      }
  }
}
void GenreHash::getGenreCount()
{
  cout << "Genre Counts: " << endl;
  Song *temp;
  for(int i =0; i < hashTableSize-1;i++)//Wont get OTHER genre counts
  {
    int count = 0;
      temp = hashTable[i];
      cout << "genre: " << temp->genre;
      while(temp != NULL)
      {
          //cout <<"|Title: " << temp->title << " Genre: " << temp->genre << " Plays: " << temp->globalPlays << "| ->    ";
          count = count + 1;
          temp = temp->next;
      }
      cout << " -> count: " << count << endl;
  }
  //gets count for other Genres
  cout << "Other Genres";
  int count = 0;
  temp = hashTable[hashTableSize-1];
  while(temp != NULL)
  {
    count = count + 1;
    temp = temp->next;
  }
  cout << " -> count: " << count << endl;
}

void GenreHash :: printGenreTop10(string word)
{
  int index = hashFunction(word);
  Song *temp = hashTable[index];
  int count = 0;

  while(temp != NULL && count < 10)
  {
    cout << "Title: " << temp->title << " Artist: " << temp->artist << " Plays: " << temp->globalPlays << endl;
    temp = temp->next;
    count++;
  }
}

Song* GenreHash :: searchSong(string ntitle, string ngenre)
{
  int index = hashFunction(ngenre);
  Song *current = hashTable[index];
  if(hashTable[index] == NULL)
  {
    return NULL;
  }

  while(current != NULL)
  {
    if(current->title == ntitle)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

int GenreHash :: recommend_helper(Song* head)
{
    int genreBreakdown[hashTableSize] = {0};
    Song* temp = head;
    while(temp!=NULL)
    {
        genreBreakdown[hashFunction(temp->genre)]++;
        temp = temp->next;
    }
    delete temp;
    int max_temp = 0;
    int max_genre = 0;
    for( int i=0; i<hashTableSize; i++)
    {
        if(genreBreakdown[i]>max_temp)
        {
            max_temp = genreBreakdown[i];
            max_genre = i;
        }
    }
    return max_genre;
}

bool GenreHash ::isInPlaylist(Song* head, Song* check)
    {
        Song* temp = head;
        while(temp!=NULL)
        {
            if((temp->title==check->title)&&(temp->artist==check->artist))
            {
                return true;
            }
            temp=temp->next;
        }
        delete temp;
        return false;
    }

void GenreHash :: deleteRecommendedPlaylist(User* u1)
{
  if(u1->recommendListHead == NULL)
  {
    return;
  }
  Song *temp;
    while(u1->recommendListHead != NULL)
    {
      temp = u1->recommendListHead;
      u1->recommendListHead = u1->recommendListHead->next;
    }
}

void GenreHash :: recommend_songs(User* u1)
{
    //deleteRecommendedPlaylist(u1);
    int rec_genre = recommend_helper(u1->playlistHead);
    int recommended = 0;
    Song* genreHead = hashTable[rec_genre];
    Song* temp = genreHead;
    Song* adder;
    while((recommended<u1->numberSongs)&&(temp!=NULL))
    {
        if(!isInPlaylist(u1->playlistHead, temp))
           {
              Song* added = new Song();
              added->title = temp->title;
              added->artist = temp->artist;
              added->genre = temp->genre;
              added->globalPlays = temp->globalPlays;
              added->next = NULL;
               if(u1->recommendListHead == NULL)
               {

                   u1->recommendListHead = added;
                   adder = u1->recommendListHead;
               }
               else
               {
                   adder->next = added;
                   adder = adder->next;
               }
               recommended++;
           }
       temp=temp->next;
    }
    Song* current = u1->recommendListHead;
    while(current!=NULL)
    {
      cout << "| Title: " << current->title << "  Artist: " << current->artist << "  Genre: " << current->genre << "  Global Plays: " << current->globalPlays << endl;
      current = current->next;
    }
}
void GenreHash:: addSongToPlaylist(Song *name, User* curr_user)
{
    Song *insert = new Song();
    insert->title = name->title;
    insert->artist = name->artist;
    insert->genre = name->genre;
    insert->globalPlays = name->globalPlays;
    insert->next = NULL;

    if(curr_user->playlistHead == NULL)
    {
      curr_user->playlistHead = insert;
      return;
    }

      Song *current = curr_user->playlistHead;
      while(current != NULL)
      {
        if(current->next == NULL)
        {
          current->next = insert;
          return;
        }
        current = current->next;
      }
}
void GenreHash :: printUserPlaylist(User* curr_user)
{
  if(curr_user->playlistHead == NULL)
  {
    cout << "Nothing in your playlist" << endl;
    return;
  }
  Song *current = curr_user->playlistHead;
  while(current != NULL)
  {
    cout << "| Title: " << current->title << "  Artist: " << current->artist << "  Genre: " << current->genre << "  Global Plays: " << current->globalPlays << endl;
    current = current->next;
  }

}

void GenreHash :: deleteSongFromPlaylist(Song *deleteS, User* u1)
{
  Song* current = u1->playlistHead;
  Song *prev = NULL;
  while(current != NULL && current->title != deleteS->title)
  {
    prev = current;
    current = current->next;
  }

  if(current == NULL)
  {
    cout << "Song is not in playlist" << endl;
  }
  else
  {
    if(prev == NULL)
    {
      u1->playlistHead = current->next;
      delete current;
    }
    else
    {
      prev->next = current->next;
      delete current;
    }
  }
}
