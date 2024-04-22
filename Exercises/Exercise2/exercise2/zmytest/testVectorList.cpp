#include <iostream>

/* ************************************************************************** */

#include "test.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"

#include "../zlasdtest/vector/vector.hpp"

#include "../zlasdtest/list/list.hpp"

/* ************************************************************************** */

//using namespace std;

/* ************************************************************************** */

void testVector(uint & testnum, uint & testerr);
void testVectorInt(uint & testnum, uint & testerr);
void testVectorDouble(uint & testnum, uint & testerr);
void testVectorString(uint & testnum, uint & testerr);

void testList(uint & testnum, uint & testerr);
void testListInt(uint & testnum, uint & testerr);
void testListDouble(uint & testnum, uint & testerr);
void testListString(uint & testnum, uint & testerr);

void testVectorList(uint & testnum, uint & testerr);
void testVectorListInt(uint & testnum, uint & testerr);
void testVectorListDouble(uint & testnum, uint & testerr);
void testVectorListString(uint & testnum, uint & testerr);

void Clear(uint &testnum, uint &testerr, lasd::ClearableContainer &con, bool chk);
void Resize(uint &testnum, uint &testerr, lasd::ResizableContainer &con, bool chk, ulong newSize);

/* ************************************************************************** */

void TestVectorList(unsigned int & testnum, unsigned int & testerr){
    uint loctestnum = 0, loctesterr = 0;
    testVector(loctestnum, loctesterr);
    testList(testnum, loctesterr);
    testVectorList(testnum, testerr);

    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "My personal test for Vector and List (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

/* ************************************************************************** */

void testVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testVectorInt(loctestnum, loctesterr);
  testVectorDouble(loctestnum, loctesterr);
  testVectorString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testVectorInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<int> Test:" << endl;
  try {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
    }
    {
      lasd::SortableVector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);

      SetAt(loctestnum, loctesterr, vec, true, 0, 4);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1);

      GetFront(loctestnum, loctesterr, vec, true, 4);
      GetBack(loctestnum, loctesterr, vec, true, 1);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 4);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 12);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 60);

      vec.Sort();

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      vec.Resize(2);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 12);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testVectorDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);

    GetFront(loctestnum, loctesterr, vec, true, 5.5);
    GetBack(loctestnum, loctesterr, vec, true, 1.1);

    Exists(loctestnum, loctesterr, vec, true, 3.3);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 9.9);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 19.965);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testVectorString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;
  try {
    lasd::SortableVector<string> vec(2);

    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 2);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

    GetFront(loctestnum, loctesterr, vec, true, string("A"));
    GetBack(loctestnum, loctesterr, vec, true, string("B"));

    Exists(loctestnum, loctesterr, vec, true, string("A"));

    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XA B "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XB A "));

    Exists(loctestnum, loctesterr, vec, false, string("A"));

    lasd::SortableVector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string("!")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = move(vec);
    FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?A !B !"));

    lasd::SortableVector<string> movvec(move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?A B "));
    movvec.Sort();
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?A B "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
    vec.Resize(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void Clear(uint &testnum, uint &testerr, lasd::ClearableContainer &con, bool chk) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Clearing container, size is now: ";
  try {
    con.Clear();
    std::cout << con.Size() << ": " << ((tst = ((con.Size() == 0) == chk)) ? "Correct" : "Error (expected 0)!") << std::endl;
  } catch (std::exception &exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  } catch (...) {
    std::cout << "A non-exception type was thrown, that's strange..." << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

void Resize(uint &testnum, uint &testerr, lasd::ResizableContainer &con, bool chk, ulong newSize) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Resizing container, size is now ";
  try {
    con.Resize(newSize);
    std::cout << con.Size() << ": " << ((tst = ((con.Size() == newSize) == chk)) ? "Correct" :  ("Error (expected " + std::to_string(newSize) +")!")) << std::endl;
  } catch (std::exception &exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  } catch (...) {
    std::cout << "A non-exception type was thrown, that's strange..." << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

void testList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testListInt(loctestnum, loctesterr);
  testListDouble(loctestnum, loctesterr);
  testListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testListInt(uint & testnum, uint & testerr) {
      uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<int> Test:" << endl;
  try {
    lasd::List<int> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    GetFront(loctestnum, loctesterr, lst, false, 0);
    GetBack(loctestnum, loctesterr, lst, false, 0);

    Exists(loctestnum, loctesterr, lst, false, 0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, 4);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 9);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);

    GetFront(loctestnum, loctesterr, lst, true, 1);
    GetBack(loctestnum, loctesterr, lst, true, 2);
    SetFront(loctestnum, loctesterr, lst, true, 2);
    SetBack(loctestnum, loctesterr, lst, true, 6);

    GetAt(loctestnum, loctesterr, lst, true, 3, 4);
    SetAt(loctestnum, loctesterr, lst, true, 3, 3);

    Exists(loctestnum, loctesterr, lst, false, 4);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 25);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 1620);

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 9);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 90);

    lasd::List<int> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    FrontNRemove(loctestnum, loctesterr, coplst, true, 6);
    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 11);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 17);

    lasd::List<int> movlst(move(lst));
    MapPreOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 0, 14);

    InsertC(loctestnum, loctesterr, movlst, true, 6);
    InsertC(loctestnum, loctesterr, movlst, false, 8);
    Remove(loctestnum, loctesterr, movlst, true, 6);
    InsertC(loctestnum, loctesterr, movlst, true, 7);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 22);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testListDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<double> Test:" << endl;
  try {
    lasd::List<double> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, -2.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2.5);

    lst.Clear();

    InsertAtBack(loctestnum, loctesterr, lst, true, 0.5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 3.3);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 1.1);

    GetFront(loctestnum, loctesterr, lst, true, 5.5);
    GetBack(loctestnum, loctesterr, lst, true, 1.1);

    Exists(loctestnum, loctesterr, lst, false, 0.0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 10.4);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 1.0, 9.9825);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<string> Test:" << endl;
  try {
    lasd::List<string> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("B"));

    GetFront(loctestnum, loctesterr, lst, true, string("A"));
    GetBack(loctestnum, loctesterr, lst, true, string("B"));

    Exists(loctestnum, loctesterr, lst, true, string("B"));

    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XA B "));
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XB A "));

    Exists(loctestnum, loctesterr, lst, false, string("B"));

    lasd::List<string> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    lst = coplst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("C"));
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string("?"), string("?CB A"));
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testVectorList(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testVectorListInt(loctestnum, loctesterr);
    testVectorListDouble(loctestnum, loctesterr);
    testVectorListString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Vector/List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testVectorListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<int> Test:" << endl;
  try {
    lasd::SortableVector<int> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, -1);
    SetAt(loctestnum, loctesterr, vec, true, 1, 0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1);

    lasd::List<int> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);
    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtFront(loctestnum, loctesterr, lst, true, -1);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<int> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<int> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */
void testVectorListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, -0.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 0.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 0.5);

    lasd::List<double> lst;
    InsertAtBack(loctestnum, loctesterr, lst, true, -0.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0.0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0.5);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<double> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<double> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<double> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<double> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testVectorListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector/List<string> Test:" << endl;
    try {
        lasd::SortableVector<string> vec(3);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("C"));

        lasd::List<string> lst;
        InsertAtFront(loctestnum, loctesterr, lst, true, string("B"));
        InsertAtBack(loctestnum, loctesterr, lst, true, string("C"));
        InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));

        EqualLinear(loctestnum, loctesterr, vec, lst, true);

        lasd::SortableVector<string> copvec(lst);
        EqualVector(loctestnum, loctesterr, vec, copvec, true);
        lasd::SortableVector<string> copvecx(vec);
        EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

        lasd::List<string> coplst(vec);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        lasd::List<string> coplstx(lst);
        EqualList(loctestnum, loctesterr, coplstx, coplst, true);

        lasd::List<string> coplsty(move(vec));
        EqualList(loctestnum, loctesterr, coplst, coplsty, true);
        EqualVector(loctestnum, loctesterr, vec, copvec, false);

        lasd::SortableVector<string> copvecy(move(lst));
        EqualVector(loctestnum, loctesterr, copvec, copvecy, true);
        EqualList(loctestnum, loctesterr, lst, coplst, false);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector/List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */