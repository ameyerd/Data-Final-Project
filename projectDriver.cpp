#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "project.hpp"

using namespace std;

void mainmenu ()
{
  cout << "Select from the following" << endl;
  cout << "-------------------------" << endl;
  cout << "1. Display all group" << endl; // printTable()
  cout << "2. Display members from a group" << endl; // printMembers()
  cout << "3. Search an idol" << endl; //printIndividual
  cout << "4. Add favorite group" << endl;
  cout << "5. Add favorite idol" << endl;
  cout << "6. Delete a group" << endl;
  cout << "7. Log out" << endl;
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
  if (fp.is_open())
  {

    while (getline(fp,s))
    {

      stringstream ss(s);
      getline(ss, groupN, ',');
      getline(ss, memberN, ',');
      getline(ss, position, ',');
      getline(ss, bday, ',');
      getline(ss, height, ',');
      getline(ss, fact, ',');
      cout << fact << endl;
      ht.insertGroup(groupN, memberN, position, bday, height, fact);
    }


  }

  else
  {
    cout << "Error." << endl;
    return 0;
  }
  cout << "---------------------------------------------------------------" << endl;
  ht.printMembers("nct 127");
  ht.printTable();
  ht.printIndividual("Jungkook");
  ht.~HashTable();
  ht.printTable();
  ht.addFavGroup(1, "NCT 127");
  ht.addFavGroup(1, "ATEEZ");
}
