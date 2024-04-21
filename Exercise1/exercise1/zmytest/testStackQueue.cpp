#include <iostream>

/* ************************************************************************** */

#include "test.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/linear.hpp"


#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"

#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

#include "../zlasdtest/stack/stack.hpp"
#include "../zlasdtest/queue/queue.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void testStack(uint & testnum, uint & testerr);

template <typename Stk>
void testStackInt(Stk & stk, uint & testnum, uint & testerr);
void testStackInt(uint & testnum, uint & testerr);

template <typename Stk>
void testStackFloat(Stk & stk, uint & testnum, uint & testerr);
void testStackFloat(uint & testnum, uint & testerr);

template <typename Stk>
void testStackString(Stk & stk, uint & testnum, uint & testerr);
void testStackString(uint & testnum, uint & testerr);

/* ************************************************************************** */

void testQueue(uint & testnum, uint & testerr);

template <typename Queue>
void testQueueInt(Queue & queue, uint & testnum, uint & testerr);
void testQueueInt(uint & testnum, uint & testerr);

template <typename Queue>
void testQueueFloat(Queue & queue, uint & testnum, uint & testerr);
void testQueueFloat(uint & testnum, uint & testerr);

template <typename Queue>
void testQueueString(Queue & queue, uint & testnum, uint & testerr);
void testQueueString(uint & testnum, uint & testerr);

/* ************************************************************************** */

void TestStackQueue(unsigned int & testnum, unsigned int & testerr){
    uint loctestnum = 0, loctesterr = 0;
    testStack(loctestnum, loctesterr);
    testQueue(testnum, loctesterr);

    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "My personal test for Stack and Queue (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

/* ************************************************************************** */

void testStack(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testStackInt(loctestnum, loctesterr);
    testStackFloat(loctestnum, loctesterr);
    testStackString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Stack (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

template <typename Stk>
void testStackInt(Stk & stk, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  try {
    Empty(loctestnum, loctesterr, stk, true);
    Size(loctestnum, loctesterr, stk, true, 0);

    Top(loctestnum, loctesterr, stk, false, 0);
    TopNPop(loctestnum, loctesterr, stk, false, 0);

    PushC(loctestnum, loctesterr, stk, 4);
    PushC(loctestnum, loctesterr, stk, 0);
    PushC(loctestnum, loctesterr, stk, 3);
    PushC(loctestnum, loctesterr, stk, 1);
    PushC(loctestnum, loctesterr, stk, 2);

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 5);

    TopNPop(loctestnum, loctesterr, stk, true, 2);
    Top(loctestnum, loctesterr, stk, true, 1);
    Top(loctestnum, loctesterr, (const Stk) stk, true, 1);

    Stk copstk(stk);
    EqualStack(loctestnum, loctesterr, stk, copstk, true);
    PushC(loctestnum, loctesterr, stk, 5);
    NonEqualStack(loctestnum, loctesterr, stk, copstk, true);

    copstk = stk;
    EqualStack(loctestnum, loctesterr, stk, copstk, true);
    PushC(loctestnum, loctesterr, copstk, 6);
    NonEqualStack(loctestnum, loctesterr, stk, copstk, true);

    Top(loctestnum, loctesterr, copstk, true, 6);
    copstk = move(stk);
    TopNPop(loctestnum, loctesterr, copstk, true, 5);
    Pop(loctestnum, loctesterr, copstk, true);
    Top(loctestnum, loctesterr, copstk, true, 3);

    Stk movstk(move(stk));
    Top(loctestnum, loctesterr, stk, false, 0);

    movstk.Clear();
    Pop(loctestnum, loctesterr, movstk, false);
    Empty(loctestnum, loctesterr, movstk, true);
    Size(loctestnum, loctesterr, movstk, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Stack<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testStackInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<int> stkvec;
  cout << endl << "Begin of StackVec<int> Test:" << endl;
  testStackInt(stkvec, loctestnum, loctesterr);
  lasd::StackLst<int> stklst;
  cout << endl << "Begin of StackLst<int> Test:" << endl;
  testStackInt(stklst, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */
template <typename Stk>
void testStackFloat(Stk & stk, uint & testnum, uint & testerr) {
   uint loctestnum = 0, loctesterr = 0;
  try {
    PushC(loctestnum, loctesterr, stk, 5.9);
    PushC(loctestnum, loctesterr, stk, 4.4);
    PushC(loctestnum, loctesterr, stk, 9.5);

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 3);

    TopNPop(loctestnum, loctesterr, stk, true, 9.5);
    Top(loctestnum, loctesterr, stk, true, 4.4);
    Pop(loctestnum, loctesterr, stk, true);
    TopNPop(loctestnum, loctesterr, stk, true, 5.9);
    Pop(loctestnum, loctesterr, stk, false);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Stack<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testStackFloat(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<double> stkvec;
  cout << endl << "Begin of StackVec<double> Test:" << endl;
  testStackFloat(stkvec, loctestnum, loctesterr);
  lasd::StackLst<double> stklst;
  cout << endl << "Begin of StackLst<double> Test:" << endl;
  testStackFloat(stklst, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */
template <typename Stk>
void testStackString(Stk & stk, uint & testnum, uint & testerr) {
   uint loctestnum = 0, loctesterr = 0;
  try {
    PushM(loctestnum, loctesterr, stk, string("A"));
    PushM(loctestnum, loctesterr, stk, string("B"));

    Empty(loctestnum, loctesterr, stk, false);
    Size(loctestnum, loctesterr, stk, true, 2);

    TopNPop(loctestnum, loctesterr, stk, true, string("B"));
    Top(loctestnum, loctesterr, stk, true, string("A"));
    Pop(loctestnum, loctesterr, stk, true);
    Pop(loctestnum, loctesterr, stk, false);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Stack<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testStackString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<string> stkvec;
  cout << endl << "Begin of StackVec<string> Test:" << endl;
  testStackString(stkvec, loctestnum, loctesterr);
  lasd::StackLst<string> stklst;
  cout << endl << "Begin of StackLst<string> Test:" << endl;
  testStackString(stklst, loctestnum, loctesterr);
  cout << endl;
  try {
    lasd::Vector<string> vec(2);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

    PushM(loctestnum, loctesterr, stkvec, string("A"));
    PushM(loctestnum, loctesterr, stkvec, string("B"));
    lasd::StackVec<string> newstkvec(vec);
    EqualStack(loctestnum, loctesterr, stkvec, newstkvec, true);

    PushM(loctestnum, loctesterr, stklst, string("B"));
    PushM(loctestnum, loctesterr, stklst, string("A"));
    lasd::StackLst<string> newstklst(vec);
    EqualStack(loctestnum, loctesterr, stklst, newstklst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testQueue(uint & testnum, uint & testerr) {

    uint loctestnum = 0, loctesterr = 0;
    testQueueInt(loctestnum, loctesterr);
    testQueueFloat(loctestnum, loctesterr);
    testQueueString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Queue (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */
template <typename Queue>
void testQueueInt(Queue & queue, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  try {
    Empty(loctestnum, loctesterr, queue, true);
    Size(loctestnum, loctesterr, queue, true, 0);

    Head(loctestnum, loctesterr, queue, false, 0);
    HeadNDequeue(loctestnum, loctesterr, queue, false, 0);

    EnqueueC(loctestnum, loctesterr, queue, 4);
    EnqueueC(loctestnum, loctesterr, queue, 0);
    EnqueueC(loctestnum, loctesterr, queue, 3);
    EnqueueC(loctestnum, loctesterr, queue, 1);
    EnqueueC(loctestnum, loctesterr, queue, 2);

    Empty(loctestnum, loctesterr, queue, false);
    Size(loctestnum, loctesterr, queue, true, 5);

    HeadNDequeue(loctestnum, loctesterr, queue, true, 4);
    Head(loctestnum, loctesterr, queue, true, 0);
    Head(loctestnum, loctesterr, (const Queue) queue, true, 0);

    Queue copque(queue);
    EqualQueue(loctestnum, loctesterr, queue, copque, true);
    EnqueueC(loctestnum, loctesterr, queue, 5);
    NonEqualQueue(loctestnum, loctesterr, queue, copque, true);

    copque = queue;
    EqualQueue(loctestnum, loctesterr, queue, copque, true);
    EnqueueC(loctestnum, loctesterr, copque, 6);
    NonEqualQueue(loctestnum, loctesterr, queue, copque, true);

    Head(loctestnum, loctesterr, copque, true, 0);
    copque = move(queue);
    HeadNDequeue(loctestnum, loctesterr, copque, true, 0);
    Dequeue(loctestnum, loctesterr, copque, true);
    Head(loctestnum, loctesterr, copque, true, 1);

    Queue movque(move(queue));
    Head(loctestnum, loctesterr, queue, false, 0);

    movque.Clear();
    Dequeue(loctestnum, loctesterr, movque, false);
    Empty(loctestnum, loctesterr, movque, true);
    Size(loctestnum, loctesterr, movque, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Queue<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testQueueInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    lasd::QueueVec<int> quevec;
    cout << endl << "Begin of QueueVec<int> Test:" << endl;
    testQueueInt(quevec, loctestnum, loctesterr);
    lasd::QueueLst<int> quelst;
    cout << endl << "Begin of QueueLst<int> Test:" << endl;
    testQueueInt(quelst, loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    }

/* ************************************************************************** */
template <typename Queue>
void testQueueFloat(Queue & queue, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  try {
    EnqueueC(loctestnum, loctesterr, queue, 5.9);
    EnqueueC(loctestnum, loctesterr, queue, 4.4);
    EnqueueC(loctestnum, loctesterr, queue, 9.5);

    Empty(loctestnum, loctesterr, queue, false);
    Size(loctestnum, loctesterr, queue, true, 3);

    HeadNDequeue(loctestnum, loctesterr, queue, true, 5.9);
    Head(loctestnum, loctesterr, queue, true, 4.4);
    Dequeue(loctestnum, loctesterr, queue, true);
    HeadNDequeue(loctestnum, loctesterr, queue, true, 9.5);
    Dequeue(loctestnum, loctesterr, queue, false);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Queue<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testQueueFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    lasd::QueueVec<double> quevec;
    cout << endl << "Begin of QueueVec<double> Test:" << endl;
    testQueueFloat(quevec, loctestnum, loctesterr);
    lasd::QueueLst<double> quelst;
    cout << endl << "Begin of QueueLst<double> Test:" << endl;
    testQueueFloat(quelst, loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */
template <typename Queue>
void testQueueString(Queue & queue, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
  try {
    EnqueueM(loctestnum, loctesterr, queue, string("A"));
    EnqueueM(loctestnum, loctesterr, queue, string("B"));

    Empty(loctestnum, loctesterr, queue, false);
    Size(loctestnum, loctesterr, queue, true, 2);

    HeadNDequeue(loctestnum, loctesterr, queue, true, string("A"));
    Head(loctestnum, loctesterr, queue, true, string("B"));
    Dequeue(loctestnum, loctesterr, queue, true);
    Dequeue(loctestnum, loctesterr, queue, false);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "End of Queue<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testQueueString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    lasd::QueueVec<string> quevec;
    cout << endl << "Begin of QueueVec<string> Test:" << endl;
    testQueueString(quevec, loctestnum, loctesterr);
    lasd::QueueLst<string> quelst;
    cout << endl << "Begin of QueueLst<string> Test:" << endl;
    testQueueString(quelst, loctestnum, loctesterr);
    cout << endl;
    try {
        lasd::Vector<string> vec(2);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

        EnqueueM(loctestnum, loctesterr, quevec, string("A"));
        EnqueueM(loctestnum, loctesterr, quevec, string("B"));
        lasd::QueueVec<string> newquevec(vec);
        EqualQueue(loctestnum, loctesterr, quevec, newquevec, true);

        EnqueueM(loctestnum, loctesterr, quelst, string("A"));
        EnqueueM(loctestnum, loctesterr, quelst, string("B"));
        lasd::QueueLst<string> newquelst(vec);
        EqualQueue(loctestnum, loctesterr, quelst, newquelst, true);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}
