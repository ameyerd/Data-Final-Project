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

//menu function
void mainmenu()
{
  cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ M A I N  M E N U ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << right << setw(65) << endl;
  cout << endl;
  cout << "1. Display all groups" << right << setw(75) << endl; // printTable()
  cout << "2. Display members from a group" << right << setw(61) <<endl; // printMembers()
  cout << "3. Search an idol" << right << setw(65) <<endl; //printIndividual
  cout << "4. Add favorite group" << right << setw(64) <<endl;
  cout << "5. Add favorite idol" << right << setw(76) <<endl;
  cout << "6. Delete a group from favorites" << right << setw(76) <<endl;
  cout << "7. Delete an idol from favorites" << right << setw(66) <<endl;
  cout << "8. Test your KNOWLEDGE" << right << setw(69) <<endl;
  cout << "9. See your GROUP RANKING" << right << setw(69) <<endl;
  cout << "10. See your IDOL RANKING" << right << setw(55) <<endl;
  cout << "11. LOG OUT" <<endl;
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

  //read in file
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

  cout << endl;
  cout << endl;
  cout << right << setw(105) << endl;

  cout << " (=^･ｪ･^=))ﾉ彡☆ WELCOME TO KPOP POP (=^･ｪ･^=))ﾉ彡☆" << right << setw(67) << endl;
  cout << "Please insert your name: ";
  cin.ignore();
  getline(cin, username);

  cout << endl;
  cout << endl;
  while(choice != "11")
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mainmenu();
    cin >> choice;
    if (isnumber(choice) == true)
    {
      switch(stoi(choice))
      {
        case 1:
          //print list of all groups
          ht.printGroups();
          cout << endl;
          break;
        case 2:
          // print members from a group
          cout << "Please insert a group: ";
          cin.ignore();
          getline(cin,groupN);
          ht.printMembers(groupN);
          cout << endl;
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
          cout << endl;
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
          cout << endl;
          ht.addFavGroup(stoi(rank),groupN);
          if (ht.numofFavG () !=0 && ht.numofFavG() != track)
          {
            cout << "Yay! Here's the updated list of your current favorite group(s)!" << endl;
            ht.printFavoriteGroup();
          }

          cout << endl;
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
          cout << endl;
          ht.addFavMember(stoi(rank),memberN);
          if (ht.numofFavM() != 0 && track != ht.numofFavM())
          {
              cout << "Yay! Here's the updated list of your current favorite member(s)!" << endl;
              ht.printFavoriteMember();
          }

          cout << endl;

          break;
        case 6:
          // delete group from favorites
          track = ht.numofFavG();
          if (ht.numofFavG() != 0)
          {
            cout << "Here's your current favorite groups: " << endl;
            ht.printFavoriteGroup();
            cout << endl;
          }
          else
          {
            cout << "You currently have no favorite group to delete!" << endl;
            cout << endl;
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
          else if(ht.numofFavG() == 0)
          {
            cout << "You deleted EVERYTHING!!!!!" << endl;
          }
          cout << endl;
          break;
        case 7:
          //delete idol from favorites
          track = ht.numofFavM();
          if (ht.numofFavM() != 0)
          {
            cout << "Here's your current favorite members: " << endl;
            ht.printFavoriteMember();
            cout << endl;
          }
          else
          {
            cout << "You currently have no favorite member to delete!" << endl;
            cout << endl;
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
            cout << endl;
          }

          if (ht.numofFavM() == 0)
          {
            cout << "You deleted EVERYTHING!!!!!" << endl;
          }
          cout << endl;
          break;
        case 8:
          //quiz
          cout << "Test your KNOWLEDGE to see if you really know your idols!" << endl;
          cout << "Please enter an idol's name: ";
          cin.ignore();
          getline(cin,memberN);
          ht.quiz(memberN);
          cout << endl;
          break;
        case 9:
          //output all favorite groups
          if (ht.numofFavG() == 0)
          {
            cout << "Oops! You currently have no favorite GROUPS!" << endl;
          }

          else
          {
            ht.printFavoriteGroup();
          }
          cout << endl;
          break;

        case 10:
          //output all favorite memebers
          if (ht.numofFavM() == 0)
          {
            cout << "Oops! You currently have no favorite MEMBER!" << endl;
          }

          else
          {
            ht.printFavoriteMember();
          }

          cout << endl;
          break;

        case 11:
        // quit
        cout << right << setw(105) << endl;
          cout << " (^･o･^)ﾉ” POP POP POP KPOP POP! GOODBYE! (^･o･^)ﾉ” " << endl;
          cout << endl;
          cout << endl;
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
