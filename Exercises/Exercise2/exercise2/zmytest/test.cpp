#include "test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void myTest() {
  cout << endl << "Welcome to the Giordano Vincenzo N86003039 LASD Test Suite  " << endl;

  uint loctestnum, loctesterr;
  uint testnum = 0, testerr = 0;
  
  loctestnum = 0; loctesterr = 0;
  TestVectorList(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  TestStackQueue(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  cout << endl << "My Test (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

/* ************************************************************************** */
