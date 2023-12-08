//
// Created by Francoise Hayek for CIS 4930 Enterprise Software Engineering at the University of Florida
//

#include "InMemoryDB.h"
#include <iostream>
#include <stdexcept>

// Starts a new transaction. Only a single transaction may exist at a time.
int InMemoryDB::begin_transaction() {

  try {

    if (!transactionInProg) {

      transactionInProg = true;

      // Create a deep copy of the existing DB
      for (const auto& pair : myDB) {
        tempDB[pair.first] = pair.second;
      }

      cout << "Begin transaction." << endl;

    } else {

      throw runtime_error("Transaction already in progress. Commit or rollback current changes to begin a new transaction.");

    }
    
  } catch (const exception& e) {

    cerr << "Error occurred when attempting to start a new transaction: " << e.what() << endl;

    return -1;

  }

  return 0;

}


// Create a new key with the provided value if a key doesn’t exist. Otherwise it will update the value of an existing key.
// If called when a transaction is not in progress, throw an exception
int InMemoryDB::put(string key, int value) {

  try {

    if (transactionInProg) {

      tempDB[key] = value;

    } else {

      throw runtime_error("Transaction not in progress. Start a transaction by calling begin_transaction before attempting to make any changes to the database.");

    }

  } catch (const exception& e) {

    cerr << "Error: " << e.what() << endl;

    return -1;

  }

  return 0;

}

// Will return the value associated with the key or null if the key doesn’t exist.
// Can be called anytime even when a transaction is not in progress
int InMemoryDB::get(string key) {

  if (myDB.find(key) != myDB.end()) {

    return myDB[key];

  } 

  cout << "No value assocaited with that key." << endl;

  return -1;

}

// Applies changes made within the transaction to the main state. Allowing any future gets() to “see” the changes made within the transaction.
// Ends transaction.
int InMemoryDB::commit() {

  if (transactionInProg) {
    
    for (const auto& pair : tempDB) {

      myDB[pair.first] = pair.second;

    }

    transactionInProg = false;

    cout << "Database updated." << endl;


    return 0;

  }

  cout << "No transaction changes to commit. " << endl;

  return -1;

}

// Should abort all the changes made within the transaction and everything should go back to the way it was before.
// Ends transaction.
int InMemoryDB::rollback() {

  if (transactionInProg) {

    for (const auto& pair : myDB) {

      tempDB[pair.first] = pair.second;

    }

    transactionInProg = false;

    return 0;

  }

  cout << "No transaction changes to rollback." << endl;

  return -1;

}
