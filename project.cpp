#include <iostream>
#include <string>
#include "project.hpp"

using namespace std;
// this function is for case-sensitive input from the user
bool toLowerdouble(string input, string compare)
{
    string output = "";
    string check ="";
    if (input.length() != compare.length())
    {
        return false;
    }
    for (int i =1; i < input.length(); i++)
    {
        output += tolower(input[i]);
        check += tolower(compare[i]);
    }

    if (check == output)
    {
      return true;
    }

    return false;
}

//destrucutor?

//create node
group* HashTable::createGroup(string groupName, group* next)
{
  group* nw = new group;
  nw->groupName = groupName;
  nw->next = next;
  return nw;
}

//Constructor
HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new group*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}
//Deconstructor
HashTable::~HashTable()
{

  for (int i = 0; i < tableSize; i++)
  {
    group* n = table[i];
    group* temp;
    member* pres;
    while (n != NULL)
    {
      //cout << "Group-" << n->groupName << " ";
      while (n->head != NULL)
      {
        pres = n->head;
        n->head = pres->n;
        //cout << "Deleting: "<< pres->memberName << " -->";
        delete pres;
      }

      temp = n;
      n = n->next;
      //cout << "now delete group: " << temp->groupName<< endl;
      delete temp;

    }

  }

  tableSize = 0;

}

//function to calculate hash function
unsigned int HashTable::hashFunction(string groupName)
{
    int key = groupName.size();
    return ( key % tableSize);
}

group* HashTable::searchGroup(string groupName)
{
  group* tmp;
  //compute the index by using the hash function
  int index = hashFunction(groupName);
  // search the list at that specific index and return the node if found
  if(table[index] != NULL)
  {
    tmp = table[index];
    while(tmp != NULL)
    {
      if(toLowerdouble(groupName, tmp->groupName) == true)
      {
        return tmp;
      }
      else
      {
        tmp = tmp->next;
      }
    }
  }

  return NULL;
}

bool HashTable::insertGroup(string groupName, string memberName, string position, string birthday, string height, string fact)
{
  if(!searchGroup(groupName))
  {

    int index = hashFunction(groupName);
    group* hashElement = createGroup(groupName, NULL);
    //need to insert 1st member here
    if(table[index] == NULL)
    {
      table[index] = hashElement;

    }
    else
    {
      group* temp = table[index];
      hashElement->next = temp;
      table[index] = hashElement;

    }
    //need to insert 1st member here

    member *m = new member(memberName,position,birthday,height,fact);
    cout << "Added: " << memberName << endl;
    hashElement->head = m;

    return true;
  }

  else
  {
    cout << "Group already exists..." << endl;
    cout << "Checking members..." << endl;
    //here add the rest of the memebrs
    //first we need to find the group
    // then we need to store the members head of the group into temp


    group* groupN = searchGroup(groupName);
    member* membertemp =  groupN->head;
    member* beforetemp;

    while(membertemp != NULL)
    {
      if(membertemp->n == NULL)
      {
        cout << "Adding member..." << endl;
        membertemp->n = new member(memberName,position,birthday,height,fact);
        cout << "Added: " << memberName << endl;
        return true;
      }

      membertemp = membertemp->n;
    }
  }

  return false;
}

void HashTable::printTable()
{
  for(int i = 0; i < tableSize; i++)
  {
    cout << i << "|| ";

    group* n = table[i];
    while(n != NULL)
    {
      if(n->next == NULL)
      {
        cout << n->groupName;
      }
      else
      {
        cout << n->groupName << "-->";
      }
      n = n->next;
    }

    cout << endl;
  }
}

void HashTable::printMembers(string groupN)
{

    group* n = searchGroup(groupN);

      cout << n->groupName << ": ";
      member* m = n->head;
      while (m != NULL)
      {
        if(m->n == NULL)
        {
          cout << m->memberName;
        }
        else
        {
          cout << m->memberName << ", ";;
        }

        m = m->n;
      }

      cout << endl;
}

void HashTable::printIndividual(string memberN)
{

  for (int i =0; i < tableSize; i++)
  {
    group* n = table[i];

    while(n != NULL)
    {
      member* m = n->head;
      while (m != NULL)
      {
        if (toLowerdouble(memberN, m->memberName) == true)
        {
          cout << "Group: "<< n->groupName << endl;
          cout << "Name: " << m->memberName << endl;
          cout << "Position: " << m->position << endl;
          cout << "Birthday: " << m->birthday << endl;
          cout << "Height: " << m->height << endl;
          cout << "Fun Fact: " << m->fact << endl;
          return;
        }

        m = m->n;
      }

      n = n->next;
      cout << endl;
    }
  }

  cout << "Idol not Found." << endl;
}
