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
  cout << "---------------------------------------------------------------" << endl;
  ht.printMembers("exo");
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ht.printMembers("txt");
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  //ht.printTable();
  ht.printGroups();

  srand(time(0));

  ht.quiz("mingi");
  ht.quiz("yeonjun");


  //ht.printIndividual("yeri");
  // ht.printIndividual("taeyong");
  // ht.printIndividual("umji");
  // ht.printIndividual("haechan");
  // ht.printIndividual("amey");

  //
  // ht.addFavGroup(1, "NCT 127");
  // ht.addFavGroup(1, "Van");
  // ht.addFavGroup(2, "Twice");
  // ht.addFavGroup(3, "red velvet");
  // ht.addFavGroup(2, "day6");
  //
  // ht.addFavMember(1, "yeri");
  // ht.addFavMember(2, "j-hope");
  // ht.addFavMember(1, "mark"); //this
  // ht.addFavMember(3, "joy");

  return 0;
}
