#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

/* ************************************************************************** */

#include "string"
#include <iostream>

/* ************************************************************************** */

void myTest();

/* ************************************************************************** */

// Menu
template <typename T>
void menuHashTableClsAdr(lasd::HashTableClsAdr<T>&);

template <typename T>
void menuHashTableOpnAdr(lasd::HashTableOpnAdr<T>&);

/* ************************************************************************** */

// Selector
std::string chooseStructure();
std::string chooseType();

/* ************************************************************************** */

// Functions
template <typename T>
void funInsertD(lasd::HashTable<T>&);

template <typename T>
void funRemoveD(lasd::HashTable<T>&);

template <typename T>
void funResize(lasd::HashTable<T>&);

template <typename T>
void funExists(lasd::HashTable<T>&);

template <typename T>
void funClear(lasd::HashTable<T>&);

template <typename T>
void funEmpty(lasd::HashTable<T>&);

template <typename T>
void funSize(lasd::HashTable<T>&);

/* ************************************************************************** */

// Specific functions for populating the structure - HashTableClsAdr
template <typename T>
void populateHTC(lasd::HashTableClsAdr<T>&) {}

template <>
void populateHTC(lasd::HashTableClsAdr<int>&);

template <>
void populateHTC(lasd::HashTableClsAdr<double>&);

template <>
void populateHTC(lasd::HashTableClsAdr<std::string>&);

// Specific functions for populating the structure - HashTableOpnAdr
template <typename T>
void populateHTO(lasd::HashTableOpnAdr<T>&) {}

template <>
void populateHTO(lasd::HashTableOpnAdr<int>&);

template <>
void populateHTO(lasd::HashTableOpnAdr<double>&);

template <>
void populateHTO(lasd::HashTableOpnAdr<std::string>&);

/* ************************************************************************** */

// Generators
template <typename T>
std::vector<T> generateData() {};

std::vector<int> generateInt(unsigned long);

std::vector<double> generateDouble(unsigned long);

std::vector<std::string> generateString(unsigned long);


/* ************************************************************************** */

#endif