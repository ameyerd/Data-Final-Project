#include <iostream>
#include "project.hpp"

using namespace std;

int main()
{

  HashTable ht(10);

  cout << "inserting group..." << endl;
  ht.insertGroup("BTS","Jin","Vocalist","december 4 1992","179 cm","Jin is a very good cook");
  ht.insertGroup("BTS","Jimin","Main vocalist","feb 4 2019","4 cm","Jimin likes Vananh");

  ht.insertGroup("ATEEZ","San","Vocalist","dec 8 2018","170 cm","san likes butterflies");

  if(ht.searchGroup("BTS"))
  {
    cout << "found them" << endl;
    ht.printMembers();
  }
  else
  {
    cout << "no jin ):" << endl;
  }

  ht.printTable();


}
