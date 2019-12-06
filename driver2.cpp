#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include "project.hpp"

using namespace std;

void mainmenu()
{
  cout << "Select from the following" << endl;
  cout << "-------------------------" << endl;
  cout << "1. Display all group" << endl; // printTable()
  cout << "2. Display members from a group" << endl; // printMembers()
  cout << "3. Search an idol" << endl; //printIndividual
  cout << "4. Add favorite group" << endl;
  cout << "5. Add favorite idol" << endl;
  cout << "6. Delete a group from favorites" << endl;
  cout << "7. Delete an idol from favorites" << endl;
  cout << "8. Test your KNOWLEDGE" << endl;
  cout << "9. Log out" << endl;
}

int main(int argc, char* argv[])
{

  HashTable ht (15);
  ifstream fp (argv[1]);
  string s;
  string groupN;
  string memberN;
  string position;
  string bday;
  string height;
  string fact;
  string choice = "1";
  string username;
  string rank;
  if (fp.is_open())
  {
    while (getline(fp,s))
    {

      stringstream ss(s);
      getline(ss, groupN, ',');
      getline(ss, memberN, ',');
      getline(ss, position, ',');
      getline(ss, bday, ',');
      getline(ss, height,',');
      getline(ss, fact,',');
      ht.insertGroup(groupN, memberN, position, bday, height, fact);
    }


  }

  else
  {
    cout << "File does not exist." << endl;
    return 0;
  }

  cout << "WELCOME TO KPOP POP" << endl;
  cout << "Please insert your name: ";
  cin >> username;


  while(stoi(choice) != 9)
  {
    mainmenu();
    cin >> choice;

    switch(stoi(choice))
    {
      case 1:
        //print list of all groups
        ht.printGroups();
        break;
      case 2:
        // print members from a group
        cout << "Please insert a group: ";
        cin.ignore();
        getline(cin,groupN);
        cout << groupN << endl;
        ht.printMembers(groupN);
        break;
      case 3:
        //search info oF an idol
        cout << "Please insert the idol's name: ";
        // cin >> memberN;
        cin.ignore();
        getline(cin,memberN);
        ht.printIndividual(memberN);
        break;
      case 4:
        //add favorite group
        ht.printGroups();
        cout << "Here's your current favorite groups: " << endl;
        ht.printFavoriteGroup();
        cout << "Please insert your favorite Group Name and the rank: ";
        cin.ignore();
        getline(cin,groupN);
        cout << " , ";
        cin.ignore();
        getline(cin,rank);
        ht.addFavGroup(stoi(rank),groupN);
        cout << "Yay! Here's the updated list of your current favorite group(s)!" << endl;
        ht.printFavoriteGroup();
        break;
      case 5:
        //add favorite idol
        cout << "Here's your current favorite members: " << endl;
        ht.printFavoriteMember();
        cout << "Please insert your favorite Member Name and the rank: ";
        cin.ignore();
        getline(cin,memberN);
        cout << " , ";
        cin.ignore();
        getline(cin,memberN);
        ht.addFavMember(stoi(rank),memberN);
        cout << "Yay! Here's the updated list of your current favorite member(s)!" << endl;
        ht.printFavoriteMember();
        break;
      case 6:
        // delete group from favorites
        cout << "Here's your current favorite groups: " << endl;
        ht.printFavoriteGroup();
        cout << "Please insert the group you want to delete: ";
        cin.ignore();
        getline(cin,groupN);
        ht.deleteFavGroup(groupN);
        cout << "Yay! Here's the updated list of your current favorite group(s)!" << endl;
        ht.printFavoriteGroup();
        break;
      case 7:
        //delete idol from favorites
        cout << "Here's your current favorite members: " << endl;
        ht.printFavoriteMember();
        cout << "Please insert the member you want to delete: ";
        cin.ignore();
        getline(cin,memberN);
        ht.deleteFavMember(memberN);
        cout << "Yay! Here's the updated list of your current favorite member(s)!" << endl;
        ht.printFavoriteMember();
        break;
      case 8:
        //quiz
        cout << "Test your KNOWLEDGE to see if you really know your idols!" << endl;
        cout << "Please enter an idol's name: ";
        cin.ignore();
        getline(cin,memberN);
        ht.quiz(memberN);
        break;
      case 9:
        // quit
        cout << "POP POP POP KPOP POP! GOODBYE!";
        //cat?
        exit(0);
      default:
        //invalid response
        cout << "Oops! Try again!" << endl;
        break;
    }
  }



  return 0;
}

//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
