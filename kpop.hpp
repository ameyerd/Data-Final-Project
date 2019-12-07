#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <vector>


using namespace std;

//Linked list struct for members
struct member
{
  string memberName;
  string position;
  string birthday;
  string height;
  string fact;

  struct member* n;

  member(string m, string p, string b, string h, string f) : memberName(m), position(p),
  birthday(b), height(h), fact(f), n(NULL) {}
};

//linked list struct for groups
struct group
{
    string groupName; //key
    struct group* next;
    member* head = NULL;
};

//hash table class
class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    group* *table;

    //create group function to store data
    group* createGroup(string groupName, group* next);

    //vectors for User favorites
    vector<string> favoriteGroup;
    vector<string> favoriteMember;
public:
    HashTable(int bsize);  // Constructor

    ~HashTable(); //Deconstructor

    // insert group into the hash table
    bool insertGroup(string groupName,string memberName, string position, string birthday, string height, string fact);

    // hash function to map values to key
    unsigned int hashFunction(string groupName);

    void printTable(); //print the hash table (not used in driver)
    void printGroups(); // print all the groups
    void printMembers(string GroupN); //print all the members of a certain group

    group* searchGroup(string groupName); //search to see if a group exists within the hash table
    member* searchMember(string memberName); //search to see if a member exists
    void printIndividual(string memberN); // print the individual stats of a member

    void addFavGroup(int rank, string groupName); //add favorite group to user's favorites
    void addFavMember(int rank, string memberName); //add favorite member to user's favorites
    void deleteFavGroup(string groupname); // delete a group from user's favorites
    void deleteFavMember(string membername); //delete a member from user's favorites
    void printFavoriteGroup(); //print all the user's favorite groups
    void printFavoriteMember(); //print all the user's favorite memebers
    int numofFavM(); //returns the number of favorite groups
    int numofFavG(); //returns the number of favorite memebers
    void quiz(string idolname); //quiz function


};

#endif
