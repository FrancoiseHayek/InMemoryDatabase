//
// Created by Francoise Hayek for CIS 4930 Enterprise Software Engineering at the University of Florida
//

#include "./InMemoryDB.h"
#include <iostream>
#include <string>

int main() {

  // Initialize DB
  InMemoryDB myDB;

  cout << "--------------------" << endl;
  cout << "Database initialized.\n" << endl;
  bool run = true;

  while (run) {

    cout << "Choose an option:\n" << endl;

    cout << "1. Begin transaction." << endl;
    cout << "2. Update database." << endl;
    cout << "3. Get value associated with a key." << endl;
    cout << "4. Commit changes to database." << endl;
    cout << "5. Rollback changes for this transaction." << endl;
    cout << "6. Exit.\n" << endl;

    string input;
    getline(cin, input);

    int choice = stoi(input);

    string key;
    string value;
    int ret;



    switch (choice) {

      case 1:

        ret = myDB.begin_transaction();

        if (ret == -1) { run = false; }

        break;

      case 2: 

        cout << "Enter key: ";
        getline(cin, key);
        cout << "Enter value: ";
        getline(cin, value);

        ret = myDB.put(key, stoi(value));

        if (ret == -1) { run = false; }
        
        break;

      case 3:

        cout << "Enter key: ";
        getline(cin, key);

        ret = myDB.get(key);

        if (ret == -1) { break; }

        cout << "Value associated with " << key << " is " << ret << "." << endl;

        break;

      case 4: 

        ret = myDB.commit();

        if (ret == -1) { run = false; }

        break;

      case 5: 

        ret = myDB.rollback();

        if (ret == -1) { run = false; }

        break;

      case 6:

        run = false;

        cout << "Exiting program..." << endl;

        break;

      default:

        cout << "Please enter a valid choice from 1 - 6. " << endl;

        break;

    }

    cout << endl;

  }

  return 0;

}
