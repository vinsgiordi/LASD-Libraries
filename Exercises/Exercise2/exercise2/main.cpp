#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

int main() {
  cout << endl << endl;
  cout << "LASD - LIBRARIES 2024 - Giordano Vincenzo N86003039" << endl << endl;

  unsigned long choice = 0;

  do {
    cout << "WHAT DO YOU WANT TO DO?" << endl
         << "1) Teacher's test" << endl
         << "2) Personal test" << endl << endl
         << "Choice: ";
    cin >> choice;
    cout << endl;

    if(choice == 1) {
      lasdtest();
    }
    else if(choice == 2) {
      myTest();
      break;
    }
    else {
      cout << "Unavailable choice!" << endl << endl;
    }
  } while ((choice != 1) && (choice != 2));
  
  return 0;
}