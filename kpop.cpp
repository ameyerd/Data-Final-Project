#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
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
    for (int i =0; i < input.length(); i++)
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

//create node in linked list
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
//Decontructor
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

//function to search the hash to see if a group exists
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

//function to search if a member exists
member* HashTable::searchMember(string memberName)
{
    // cout << "member" <<endl;
    for (int i =0; i < tableSize; i++)
    {
      group* n = table[i];

      while(n != NULL)
      {
        member* m = n->head;
        while (m != NULL)
        {
          if (toLowerdouble(memberName, m->memberName) == true)
          {
            return m;
          }

          m = m->n;
        }

        n = n->next;
      }
    }

    return NULL;
}

//function to insert member into hash table
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

    // insert 1st member here
    member *m = new member(memberName,position,birthday,height,fact);
    // cout << "Added: " << memberName << endl;
    hashElement->head = m;

    return true;
  }

  else
  {
    // cout << "Group already exists..." << endl;
    // cout << "Checking members..." << endl;
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
        // cout << "Adding member..." << endl;
        membertemp->n = new member(memberName,position,birthday,height,fact);
        // cout << "Added: " << memberName << endl;
        return true;
      }

      membertemp = membertemp->n;
    }
  }

  return false;
}

//print the hash table (not used in the driver)
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

//function to print all the groups
void HashTable::printGroups()
{
  int counter =0;
  cout << endl;

  cout <<  "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ 🅚 🅟 🅞 🅟  🅖 🅡 🅞 🅤 🅟 🅢 ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << right << setw(16)<< endl;
  for(int i = 0; i < tableSize; i++)
  {
    group* n = table[i];
    while(n != NULL)
    {
        if (counter == 3)
        {
          cout << " ✭ " << left << setw(20) << n->groupName << right << setw(16) << endl;
          counter =0;
        }
        else
        {
          cout << " ✭ " << left << setw(20) << n->groupName;
          counter++;
        }
      n = n->next;
    }

  }
  cout << endl;

  //cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << endl;
}

//function to print all the members in a certain group
void HashTable::printMembers(string groupN)
{

  cout<<endl;
  group* n = searchGroup(groupN);

  if(n)
  {
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ⋆⋅☆⋅⋆ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << right << setw(56) << endl;
    cout <<  n->groupName << right << setw(47)<< endl;


        // cout << n->groupName << ": ";
        member* m = n->head;
        int counter = 0;
        while (m != NULL)
        {
          if(counter == 1)
          {
            cout << " ♬♪ " << left << setw(10) << m->memberName <<  right << setw(47)<< endl;
            counter = 0;
          }
          else
          {
            cout << " ♬♪ " << left << setw(10) << m->memberName;
            counter++;
          }

          m = m->n;
        }

        cout << endl;
    }
    else
    {
      cout << "Group doesn't exist." << endl;
    }

      //cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ⋆⋅☆⋅⋆ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << endl;
}

//print an individual member's stats
void HashTable:: printIndividual(string memberN)
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

          cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ⋆⋅☆⋅⋆ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << right << setw(55) << endl;
          cout << m->memberName << right << setw(17) << endl;

          cout << "Group: "<< n->groupName << right << setw(20) << endl;
          cout << "Position: " << m->position << right << setw(20) <<endl;
          cout << "Birthday: " << m->birthday << right << setw(18) <<endl;
          cout << "Height: " << m->height << right << setw(20) <<endl;
          cout << "Fun Fact: " << m->fact << right << setw(20) <<endl;
          cout << endl;
          return;
        }

        m = m->n;
      }

      n = n->next;
    }
  }

  cout << "!🅴 🆁 🆁 O 🆁 ! Idol not Found." << endl;
}

// function to add group to user's favorites
void HashTable::addFavGroup(int rank, string groupName)
{

  // //first check if group exists
  group* temp = searchGroup(groupName);
  if(!searchGroup(groupName))
  {
    cout << "Group doesn't exist." << endl;
    return;
  }

  if (favoriteGroup.size() == 0)
  {
    if (rank != 1) //if user puts anything other than 1 and favorite groups is empty, add it at rank 1 anyways
    {
      cout << "Oops! You do not have anything in here! We will put this at #1. Teehee" << endl;
    }
    favoriteGroup.push_back(temp->groupName);
    return;
  }

  if(rank >= favoriteGroup.size()+1)
  {
    if (rank > favoriteGroup.size()+1)
    {
      cout << "You do not have enough favorite group for it to be place at rank #" << rank << ". We will place " << temp->groupName << " at the end!" << endl;
    }
    favoriteGroup.push_back(temp->groupName);
  }

  else
  {
    favoriteGroup.insert(favoriteGroup.begin()+rank-1, temp->groupName);
  }

}

//function to delete favorite group from user's favorites
void HashTable::deleteFavGroup(string groupname)
{
  if(favoriteGroup.size() == 0) //if empty
  {
    cout << "You have nothing to delete" << endl;
    return;
  }

  for (int i =0; i < favoriteGroup.size(); i++)
  {
    if (toLowerdouble(groupname, favoriteGroup[i]))
    {
      favoriteGroup.erase(favoriteGroup.begin() + i);
      return;
    }
  }

  cout << "Your input was invalid. Group does not exist within your favorites!" << endl;
}

// function returning the number of favorite groups
int HashTable:: numofFavG()
{
  return favoriteGroup.size();
}

// function to add a member to user's favorites
void HashTable::addFavMember(int rank, string memberName)
{
  for (int i =0; i < tableSize; i++)
  {
    group* n = table[i];

    while(n != NULL)
    {
      member* m = n->head;
      while (m != NULL)
      {
        if (toLowerdouble(memberName, m->memberName) == true)
        {
          if(favoriteMember.size() == 0) //if empty
          {
            if (rank !=1)
            {
              cout << "Oops! You do not have anything in here! We will put this at #1. Teehee" << endl;
            }
            favoriteMember.push_back(m->memberName);
            return;
          }

          if(rank >= favoriteMember.size()+1)
          {
            if(rank >favoriteMember.size())
            {
              cout << "You do not have enough favorite group for it to be place at rank #" << rank << ". We will place " << m->memberName << " at the end!" << endl;
            }
            favoriteMember.push_back(m->memberName);
          }

          else
          {
            favoriteMember.insert(favoriteMember.begin()+rank-1, m->memberName);
          }


          return;
        }

        m = m->n;
      }

      n = n->next;
    }
  }

  cout << "!🅴 🆁 🆁 O 🆁 ! Idol not Found." << endl;

}

//delete member from favorites
void HashTable::deleteFavMember(string membername)
{
  if(favoriteMember.size() == 0)
  {
    return;
  }
  for (int i =0; i < favoriteMember.size(); i++)
  {
    if (toLowerdouble(membername, favoriteMember[i]))
    {
      favoriteMember.erase(favoriteMember.begin() + i);
      return;
    }
  }
  cout << "Your input was invalid. Group does not exist within your favorites!" << endl;
}

//print all favorite members
void HashTable:: printFavoriteMember()
{
  if(favoriteMember.size() == 0)
  {
    return;
  }
  cout <<"--- RANKING --- " << endl;
  for (int i =0; i < favoriteMember.size(); i++)
  {
    cout << i +1 << ". " << favoriteMember[i] << endl;
  }
}

//print all favorite groups
void HashTable:: printFavoriteGroup()
{
  if (favoriteGroup.size() == 0)
  {
    return;
  }

  cout <<"--- RANKINGS ---" << endl;
  for (int i =0; i < favoriteGroup.size(); i++)
  {
    cout << i +1 << ". " << favoriteGroup[i] << endl;
  }
}

//returns total number of current favorite members
int HashTable:: numofFavM()
{
  return favoriteMember.size();
}

//helper function to return random number in range
int randomizer(int num)
{
  return (rand() % num) + 1;
}

//quiz funtion
void HashTable:: quiz (string idolname)
{
  // cout << "start quiz " << endl;
  int placeholder =0;
  int wrongholder;
  string trials;
  string trials2;

  if(searchMember(idolname)) //if member exists
  {

    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ⋆⋅☆⋅⋆ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"  << endl;
    // cout << "founded" << endl;
    member* right;
    member* wrong;
    int wrongchoice =-1;
    int y =0;

  for (int i =0; i < tableSize; i++)
  {
      group* n = table[i];

      while(n != NULL)
      {
        member* m = n->head;
        while (m != NULL)
        {
          if (toLowerdouble(idolname, m->memberName) == true)
          {

            while(wrongchoice == i || wrongchoice == -1)
            {
              wrongchoice = randomizer(tableSize);

            }
            trials = n->groupName;

            right = m;
          }

          m = m->n;
        }

        n = n->next;
      }

  }
  // cout << "wwrong choice" << wrongchoice << endl;
    int num = randomizer(5);
    // cout << "numm:" << num << endl;
    int counter =0;
    for (int i =0; i < wrongchoice; i++)
    {
      counter =0;
      group* n = table[i];

      while(n != NULL)
      {
        member* m = n->head;
        while (m != NULL && counter != num)
        {
          wrong = m;
          m = m->n;
          counter++;
          trials2 = n->groupName;
        }

        n = n->next;
      }
    }

    int typeofquestion = randomizer(4);
    int other = randomizer(3);
    int taller = stoi(wrong->height);
    string answer;
    string otherchoice;
    int checkingchecking = 0;

    //cout << placeholder << " Place Holder" << endl;
    switch (typeofquestion) //types of questions
    {
      case 1:
        cout <<  "What is " << right->memberName << "'s height?"<< endl;

        if(wrong->height == right->height)
        {
          taller = stoi(wrong->height) + 1;
        }
        if (other == 1)
        {

          cout << "a. " << right->height << endl;
          cout << "b. " << taller << " cm"  << endl;
          cout << "Answer (a/b): ";
          cin >> answer;
          if (answer == "a" || answer == "A")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }
        }

        else
        {
          cout << "a. " << taller << " cm" << endl;
          cout << "b. " << right->height << endl;

          cout << "Answer (a/b): ";
          cin >> answer;
          if (answer == "b" || answer == "B")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }
        }


        break;

      case 2:
        cout <<  "What is " << right->memberName << "'s birthday?"<< endl;

        if (other == 1)
        {

          cout << "a. " << right->birthday << endl;
          cout << "b. " << wrong->birthday << endl;
          cout << "Answer (a/b): ";
          cin >> answer;
          if (answer == "a" || answer == "A")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }
        }

        else
        {
          cout << "a. " << wrong->birthday << endl;
          cout << "b. " << right->birthday << endl;

          cout << "Answer (a/b): ";
          cin >> answer;
          if (answer == "b" || answer == "B")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }
        }
        break;
      case 3:
        cout << "What is " << right->memberName << "'s position" << endl;
        if (other == 1)
        {

          cout << "a. " << right->position << endl;
          if (right->position == wrong->position)
          {
            otherchoice = "Main Rapper";
            checkingchecking =1;
          }

          if (right->position == "Main Rapper" && otherchoice == "Main Rapper")
          {
            otherchoice = "Main Dancer";
          }
          if (checkingchecking == 0)
          {
            cout << "b. " << wrong->position << endl;
          }
          else
          {
            cout << "b. " << otherchoice << endl;
          }

          cout << "Answer (a/b): ";
          cin >> answer;
          if (answer == "a" || answer == "A")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }

        }
      else
      {
        if (right->position == wrong->position)
        {
          otherchoice = "Main Rapper";
          checkingchecking =1;
        }

        if (right->position == "Main Rapper" && otherchoice == "Main Rapper")
        {
          otherchoice = "Main Dancer";
        }
        if (checkingchecking == 0)
        {
          cout << "a. " << wrong->position << endl;
        }
        else
        {
          cout << "a. " << otherchoice << endl;
        }

        cout << "b. " << right->position << endl;

        cout << "Answer (a/b): ";
        cin >> answer;

        if (answer == "b" || answer == "B")
        {
          cout << "Correct! (:" << endl;
        }
        else
        {
          cout << "Wrong! ):<" << endl;
        }

      }


      break;

      case 4:
        cout <<  "What group is " << right->memberName << " in?"<< endl;

        if (other == 1)
       {
     //     cout << "first" << endl;

            if (trials == trials2)
            {
              trials2 = "BTS";
              if (trials == "BTS")
              {
                trials2 = "NCT 127";
              }
            }
          cout << "a. " << trials << endl;
          cout << "b. " << trials2 << endl;
          cout << "Answer (a/b): ";
          cin >> answer;

          if (answer == "a" || answer == "A")
          {
            cout << "Correct! (:" << endl;
          }
          else
          {
            cout << "Wrong! ):<" << endl;
          }
       }

       else
       {

             if (trials == trials2)
             {
               trials2 = "BTS";
               if (trials == "BTS")
               {
                 trials2 = "NCT 127";
               }
             }
         cout << "a. " <<trials2 << endl;
         cout << "b. " << trials << endl;

         cout << "Answer (a/b): ";
         cin >> answer;

         if (answer == "b" || answer == "B")
         {
           cout << "Correct! (:" << endl;
         }
         else
         {
           cout << "Wrong! ):<" << endl;
         }
       }
       break;


    }

  }
  else
  {
    cout << "!🅴 🆁 🆁 O 🆁 ! Idol not Found." << endl;
  }
}
