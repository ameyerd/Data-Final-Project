#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct member
{
  string memberName;
  string position;
  string birthday;
  string height;
  string fact;

  struct member* n;

};

struct group
{
    string groupName;
    struct group* next;
    member* head = NULL;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    group* *table;

    group* createNode(string groupName, group* next);
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertItem(string groupName);

    // hash function to map values to key
    unsigned int hashFunction(string groupName);

    void printTable();

    group* searchItem(string groupName);
};

#endif
