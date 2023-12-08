//
// Created by Francoise Hayek for CIS 4930 Enterprise Software Engineering at the University of Florida
//

#ifndef IN_MEMORY_DB_H
#define IN_MEMORY_DB_H

#include <unordered_map>
#include <string>

using namespace std;

class InMemoryDB {

  bool transactionInProg = false;
  unordered_map<string, int> myDB;
  unordered_map<string, int> tempDB;

  public:

    int begin_transaction();
    int put(string key, int value);
    int get(string key);
    int commit();
    int rollback();

};

#endif