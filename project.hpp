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

    group* createGroup(string groupName, group* next);

    vector<string> favoriteGroup;
    vector<string> favoriteMember;
public:
    HashTable(int bsize);  // Constructor

    ~HashTable();
    // inserts a key into hash table
    bool insertGroup(string groupName,string memberName, string position, string birthday, string height, string fact);

    // hash function to map values to key
    unsigned int hashFunction(string groupName);

    void printTable();
    void printGroups();
    void printMembers(string GroupN);

    group* searchGroup(string groupName);
    member* searchMember(string memberName);
    void printIndividual(string memberN);

    void addFavGroup(int rank, string groupName);
    void addFavMember(int rank, string memberName);
    void deleteFavGroup(string groupname);
    void deleteFavMember(string membername);
    void printFavoriteGroup();
    void printFavoriteMember();

    void quiz(string idolname);
    // WWE NEED DELETE FUNCTION


};

//favorite struct
// struct bubble {
//   int rank;
//   string groupFavN;
//   string memberFavN;
// };
//
// class user
// {
//   public:
//     user (int cap);
//     ~user();
//
//     //heap functions
//     int parent(int i);
//     int right(int i);
//
//     void printSelect(int i);
//     void printAll();
//     void heapify(int i);
//     void insertFavGroup(int rank, string groupFavN, string memberFavN);
//     void deleteFavGroup(int rank);
//   private:
//     string username;
//     //data type
//
//     //heap
//     int *heapArr;
//     int capacity;
//     int currentSize;
// }

#endif
