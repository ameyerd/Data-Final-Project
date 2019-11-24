#ifndef HASH_HPP
#define HASH_HPP

#include <string>


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
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertGroup(string groupName,string memberName, string position, string birthday, string height, string fact);

    // hash function to map values to key
    unsigned int hashFunction(string groupName);

    void printTable();
    void printMembers();

    group* searchGroup(string groupName);
};

#endif
