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

// checking if input is an integer
bool isnumber(string checking)
{
  bool dec= true;
  if (checking.size() ==1 && checking[0] == 48)
  {
    return false;
  }
  for (int i = 0; i < checking.size(); i++)
  {
    if (checking[i] < 48 || checking[i] > 57)
    {
      return false;
    }
  }

  return true;
}

void mainmenu()
{
  cout << "Select from the following" << endl;
  cout << "-------------------------" << endl;
  cout << "1. Display all groups" << endl; // printTable()
  cout << "2. Display members from a group" << endl; // printMembers()
  cout << "3. Search an idol" << endl; //printIndividual
  cout << "4. Add favorite group" << endl;
  cout << "5. Add favorite idol" << endl;
  cout << "6. Delete a group from favorites" << endl;
  cout << "7. Delete an idol from favorites" << endl;
  cout << "8. Test your KNOWLEDGE" << endl;
  cout << "9. See your GROUP RANKING" << endl;
  cout << "10. See your IDOL RANKING" <<endl;
  cout << "11. LOG OUT" << endl;
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
  int track;
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
  cin.ignore();
  getline(cin, username);


  while(choice != "11")
  {
    mainmenu();
    cin >> choice;
    if (isnumber(choice) == true)
    {
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
          track = ht.numofFavG();
          if (ht.numofFavG() != 0)
          {
            cout << "Here's your current favorite groups: " << endl;
          }
          ht.printFavoriteGroup();
          cout << "Please insert your favorite group: ";
          cin.ignore();
          getline(cin,groupN);
          cout << "Please insert the rank: ";
          getline(cin,rank);
          if (isnumber(rank) != true)
          {
            while (isnumber(rank) != true)
            {
              cout << "Invalid input! Please try again!"<< endl;
              cout << "Please enter the rank: ";
              getline(cin,rank);
            }
          }

          ht.addFavGroup(stoi(rank),groupN);
          if (ht.numofFavG () !=0 && ht.numofFavG() != track)
          {
            cout << "Yay! Here's the updated list of your current favorite group(s)!" << endl;
            ht.printFavoriteGroup();
          }

          break;
        case 5:
          //add favorite idol
          track = ht.numofFavM();
          if (ht.numofFavM() != 0)
          {
            cout << "Here's your current favorite members: " << endl;
          }
          ht.printFavoriteMember();
          cout << "Please insert your favorite member: ";
          cin.ignore();
          getline(cin,memberN);
          cout << "Please insert their rank: ";
          getline(cin,rank);
          if (isnumber(rank) != true)
          {
            while (isnumber(rank) != true)
            {
              cout << "Invalid input! Please try again!"<< endl;
              cout << "Please enter the rank: ";
              getline(cin,rank);
            }
          }
          ht.addFavMember(stoi(rank),memberN);
          if (ht.numofFavM() != 0 && track != ht.numofFavM())
          {
              cout << "Yay! Here's the updated list of your current favorite member(s)!" << endl;
              ht.printFavoriteMember();
          }


          break;
        case 6:
          // delete group from favorites
          track = ht.numofFavG();
          if (ht.numofFavG() != 0)
          {
            cout << "Here's your current favorite groups: " << endl;
            ht.printFavoriteGroup();
          }
          else
          {
            cout << "You currently have no favorite group to delete!" << endl;
            break;
          }

          cout << "Please insert the group you want to delete: ";
          cin.ignore();
          getline(cin,groupN);
          cout << endl;
          ht.deleteFavGroup(groupN);
          if (track != ht.numofFavG() && ht.numofFavG() > 0)
          {
            cout << "Yay! Here's the updated list of your current favorite group(s)!" << endl;
            ht.printFavoriteGroup();
          }
          else
          {
            cout << "You deleted EVERYTHING!!!!!" << endl;
          }
          break;
        case 7:
          //delete idol from favorites
          track = ht.numofFavM();
          if (ht.numofFavM() != 0)
          {
            cout << "Here's your current favorite members: " << endl;
            ht.printFavoriteMember();
          }
          else
          {
            cout << "You currently have no favorite member to delete!" << endl;
            break;
          }
          cout << "Please insert the member you want to delete: ";
          cin.ignore();
          getline(cin,memberN);
          ht.deleteFavMember(memberN);
          if (track != ht.numofFavM() && ht.numofFavM() >0)
          {
            cout << "Yay! Here's the updated list of your current favorite member(s)!" << endl;
            ht.printFavoriteMember();
          }

          if (ht.numofFavM() == 0)
          {
            cout << "You deleted EVERYTHING!!!!!" << endl;
          }
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
          if (ht.numofFavG() == 0)
          {
            cout << "Oops! You currently have no favorite GROUP!" << endl;
          }

          else
          {
            ht.printFavoriteGroup();
          }
          break;

        case 10:
          if (ht.numofFavM() == 0)
          {
            cout << "Oops! You currently have no favorite MEMBER!" << endl;
          }

          else
          {
            ht.printFavoriteMember();
          }
            break;

        case 11:
        // quit
          cout << "POP POP POP KPOP POP! GOODBYE!" << endl;
        //cat?
          exit(0);
        default:
          //invalid response
          cout << "Oops! Try again!" << endl;
          break;
      }
    }

    else
    {
      cout << "Please input a numerical value!" << endl;
    }

  }



  return 0;
}
