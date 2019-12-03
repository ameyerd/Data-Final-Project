#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
  // ht.printMembers();
  //ht.printTable();
  ht.printGroups();

  ht.printIndividual("Mingi");

  ht.addFavGroup(1, "NCT 127");
  ht.addFavGroup(1, "Van");
  ht.addFavGroup(2, "Twice");
  ht.addFavGroup(3, "red velvet");
  ht.addFavGroup(2, "day6");

  ht.addFavMember(1, "yeri");
  ht.addFavMember(2, "j-hope");
  ht.addFavMember(1, "mark"); //this
  ht.addFavMember(3, "joy");

}
