#include "test.hpp"

/* ************************************************************************** */

#include <string>
#include <random>

/* ************************************************************************** */

void myTest() {
  std::cout << "Welcome to the Giordano Vincenzo N86003039 LASD Test Suite" << std::endl;
  
  std::cout << std::endl;
  std::cout << "To exit enter 0 otherwise enter any character: " << std::endl << std::endl;
  std::string ex = "";
  std::getline(std::cin, ex);
  if(ex == "0") return;
  
  std::string structure = chooseStructure();
  std::string type = chooseType();
  if (structure == "1")
  {
    if (type == "1")
    {
      lasd::HashTableClsAdr<int> htcls;
      menuHashTableClsAdr(htcls);
    }
    else if (type == "2")
    {
      lasd::HashTableClsAdr<double> htcls;
      menuHashTableClsAdr(htcls);
    }
    else if (type == "3")
    {
      lasd::HashTableClsAdr<std::string> htcls;
      menuHashTableClsAdr(htcls);
    }
  }
  else if (structure == "2")
  {
    if (type == "1")
    {
      lasd::HashTableOpnAdr<int> htopn;
      menuHashTableOpnAdr(htopn);
    }
    else if (type == "2")
    {
      lasd::HashTableOpnAdr<double> htopn;
      menuHashTableOpnAdr(htopn);
    }
    else if (type == "3")
    {
      lasd::HashTableOpnAdr<std::string> htopn;
      menuHashTableOpnAdr(htopn);
    }
  }
}

/* ************************************************************************** */

template <typename T>
void menuHashTableClsAdr(lasd::HashTableClsAdr<T> &htcls)
{
  NextActionHTC:
  std::cout << std::endl;
  std::cout << "1: Size" << std::endl;
  std::cout << "2: Empty" << std::endl;
  std::cout << "3: Insert" << std::endl;
  std::cout << "4: Remove" << std::endl;
  std::cout << "5: Resize" << std::endl;
  std::cout << "6: Clear" << std::endl;
  std::cout << "7: Exists" << std::endl;
  std::cout << "8: Popolate structure" << std::endl;
  std::cout << "0: Back" << std::endl;
  std::cout << "\nEnter the number corresponding to the choice: ";

  invalidHTC:
  std::cout << "\n\n";
  std::string choice = "";
  std::getline(std::cin, choice);
  if (choice == "1")
  {
    funSize(htcls);
    goto NextActionHTC;
  }
  else if (choice == "2")
  {
    funEmpty(htcls);
    goto NextActionHTC;
  }
  else if (choice == "3")
  {
    funInsertD(htcls);
    goto NextActionHTC;
  }
  else if (choice == "4")
  {
    funRemoveD(htcls);
    goto NextActionHTC;
  }
  else if (choice == "5")
  {
    funResize(htcls);
    goto NextActionHTC;
  }
  else if (choice == "6")
  {
    funClear(htcls);
    goto NextActionHTC;
  }
  else if (choice == "7")
  {
    funExists(htcls);
    goto NextActionHTC;
  }
  else if (choice == "8")
  {
    populateHTC(htcls);
    goto NextActionHTC;
  }
  else if (choice == "0")
  {
    return;
  }
  else
  {
    std::cout << "\nInvalid choice, try again:" << std::endl;
    goto invalidHTC;
  }
}

/* ************************************************************************** */

template <typename T>
void menuHashTableOpnAdr(lasd::HashTableOpnAdr<T> &htopn)
{
  NextActionHTO:
  std::cout << "1: Size" << std::endl;
  std::cout << "2: Empty" << std::endl;
  std::cout << "3: Insert" << std::endl;
  std::cout << "4: Remove" << std::endl;
  std::cout << "5: Resize" << std::endl;
  std::cout << "6: Clear" << std::endl;
  std::cout << "7: Exists" << std::endl;
  std::cout << "8: Popolate structure" << std::endl;
  std::cout << "0: Back" << std::endl;
  std::cout << "\nEnter the number corresponding to the choice: ";
  
  invalidHTO:
  std::cout << "\n\n";
  std::string choice = "";
  std::getline(std::cin, choice);
  if (choice == "1")
  {
    funSize(htopn);
    goto NextActionHTO;
  }
  else if (choice == "2")
  {
    funEmpty(htopn);
    goto NextActionHTO;
  }
  else if (choice == "3")
  {
    funInsertD(htopn);
    goto NextActionHTO;
  }
  else if (choice == "4")
  {
    funRemoveD(htopn);
    goto NextActionHTO;
  }
  else if (choice == "5")
  {
    funResize(htopn);
  }
  else if (choice == "6")
  {
    funClear(htopn);
    goto NextActionHTO;
  }
  else if (choice == "7")
  {
    funExists(htopn);
    goto NextActionHTO;
  }
  else if (choice == "8")
  {
    populateHTO(htopn);
    goto NextActionHTO;
  }
  else if (choice == "0")
  {
    return;
  }
  else
  {
    std::cout << "\nInvalid choice, try again:" << std::endl;
    goto invalidHTO;
  }
}

/* ************************************************************************** */

// Specific member functions 
template <typename T>
void funInsertD(lasd::HashTable<T> &con)
{
  T value;
  bool stay = false;
  do
  {
    std::cout << "\nEnter the value you want to enter in the hashtable: ";
    std::cin >> value;
    if (con.Insert(value))
    {
      std::cout << "\nInserted!\n" << std::endl;
    }
    else
    {
      std::cout << "\nValue not inserted!\n" << std::endl;
    }

    std::cout << "Do you want to add another item? (y/n): ";
    char res;
    std::cin >> res;
    stay = (res == 'y' || res == 'Y');
  } while (stay);
}

template <typename T>
void funRemoveD(lasd::HashTable<T> &con)
{
  T value;
  bool stay = false;
  do
  {
    std::cout << "\nEnter the value you want to remove from the hashtable: ";
    std::cin >> value;
    if (con.Remove(value))
    {
      std::cout <<"\nRemoved!\n"<< std::endl;
    }
    else
    {
      std::cout << "\nValue not removed!\n"<< std::endl;
    }

    std::cout << "Do you want to add another item? (y/n): ";
    char res;
    std::cin >> res;
    stay = (res == 'y' || res == 'Y');
  } while (stay);
}

template <typename T>
void funResize(lasd::HashTable<T> &ht)
{
  std::cout << "\nEnter a new size for the hash table: " << std::endl;
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  ht.Resize(n);
  std::cout << "\nResize carried out!" << std::endl;
}

template <typename T>
void funExists(lasd::HashTable<T> &ht)
{
  T value;
  bool stay = false;
  do
  {
    std::cout << "\nEnter the value you want to check: ";
    std::cin >> value;
    std::string text = ht.Exists(value) ? ("The item is present") : ("The item isn't present");
    std::cout << text << std::endl;

    std::cout << "Do you want to add another item? (y/n): ";
    char res;
    std::cin >> res;
    stay = (res == 'y' || res == 'Y');
  } while (stay);
}

template <typename T>
void funClear(lasd::HashTable<T> &ht)
{
  ht.Clear();
  std::cout << "\nHashTable emptied" << std::endl;
}

template <typename T>
void funSize(lasd::HashTable<T> &ht)
{
  std::cout << "\nThe HashTable has size: " << ht.Size() << std::endl;
}

template <typename T>
void funEmpty(lasd::HashTable<T> &ht)
{
  bool res;
  std::cout << "\nThe HashTable " << ((res = ht.Empty()) ? "is empty" : "isn't empty") << std::endl;
}

/* ************************************************************************** */

// Selectors
std::string chooseStructure()
{
  std::cout << "Choose the type of data structure:\n" << std::endl;
  std::cout << "1: HashTableClsAdr" << std::endl;
  std::cout << "2: HashTableOpnAdr" << std::endl;
  std::cout << "\nEnter the number corresponding to the choice: ";
  
  invalidStruct:
  std::string choice = "0";
  std::getline(std::cin, choice);

  if (choice == "1" || choice == "2"){
    return choice;
  }
  else
  {
    std::cout << "\nInvalid choice, try again: " << std::endl;
    goto invalidStruct;
  }
}

std::string chooseType()
{
  std::cout << "\nChoose the type of data:\n" << std::endl;
  std::cout << "1: Int" << std::endl;
  std::cout << "2: Double" << std::endl;
  std::cout << "3: String" << std::endl;
  std::cout << "\nEnter the number corresponding to the choice: ";
  
  invalidType:
  std::string choice = "0";
  std::getline(std::cin, choice);

  if (choice == "1" || choice == "2" || choice == "3") {
    return choice;
  }
  else
  {
    std::cout << "\nInvalid choice, try again: " << std::endl;
    goto invalidType;
  }
}

/* ************************************************************************** */

// Specific functions for populating the structure - HashTableClsAdr
template <>
void populateHTC(lasd::HashTableClsAdr<int> &htcls)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000) ?: " << std::endl;
  
  invalidHTCint:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (int i : generateInt(n))
    {
      htcls.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again: " << std::endl;
    goto invalidHTCint;
  }
}

template <>
void populateHTC(lasd::HashTableClsAdr<double> &htcls)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000) ?: " << std::endl;
  
  invalidHTCdouble:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (double i : generateDouble(n))
    {
      htcls.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again: " << std::endl;
    goto invalidHTCdouble;
  }
}

template <>
void populateHTC(lasd::HashTableClsAdr<std::string> &htcls)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000) ?: " << std::endl;

  invalidHTCstring:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (std::string i : generateString(n))
    {
      htcls.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again: " << std::endl;
    goto invalidHTCstring;
  }
}

/* ************************************************************************** */

// Specific functions for populating the structure - HashTableOpnAdr

template <>
void populateHTO(lasd::HashTableOpnAdr<int> &htopn)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000) ?: " << std::endl;
  
  invalidHTOint:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (int i : generateInt(n))
    {
      htopn.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again:" << std::endl;
    goto invalidHTOint;
  }
}

template <>
void populateHTO(lasd::HashTableOpnAdr<double> &htopn)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000): ? " << std::endl;
  
  invalidHTOdouble:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (double i : generateInt(n))
    {
      htopn.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again:" << std::endl;
    goto invalidHTOdouble;
  }
}

template <>
void populateHTO(lasd::HashTableOpnAdr<std::string> &htopn)
{
  std::cout << "\nHow many items do you want to generate (min:1) (max:1.000.000) ?: " << std::endl;
  
  invalidHTOstring:
  std::string num = "";
  std::getline(std::cin, num);
  unsigned long n = std::stoul(num);
  if (n > 0 && n <= 1000000)
  {
    for (std::string i : generateString(n))
    {
      htopn.Insert(i);
    }
  }
  else
  {
    std::cout << "\nInvalid choice, try again:" << std::endl;
    goto invalidHTOstring;
  }
}

/* ************************************************************************** */

// Generators
std::vector<int> generateInt(unsigned long dim)
{
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution<int> distr(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());

  std::vector<int> vec;

  for (unsigned long i = 0; i < dim; i++)
  {
    vec.push_back(distr(generator));
  }
  std::cout << "\nRandom generation completed\n"
            << std::endl;
  return vec;
}

std::vector<double> generateDouble(unsigned long dim)
{
  std::default_random_engine generator(std::random_device{}());
  std::uniform_real_distribution<double> distr(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());

  std::vector<double> vec;

  for (unsigned long i = 0; i < dim; i++)
  {
    vec.push_back(distr(generator));
  }
  std::cout << "\nRandom generation completed\n"
            << std::endl;
  return vec;
}

std::vector<std::string> generateString(unsigned long dim)
{
  static const char charset[] = "0123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution<int> distr(0, sizeof(charset) - 1);

  std::vector<std::string> vec;

  for (unsigned long i = 0; i < dim; i++)
  {
    std::string str = "";
    uint charsToGenerate = distr(generator);
    while (str.length() < charsToGenerate || str.length() < 4)
    {
      str += (charset[distr(generator)]);
    }
    vec.push_back(str);
  }
  std::cout << "\nGRandom generation completed\n"
            << std::endl;
  return vec;
}