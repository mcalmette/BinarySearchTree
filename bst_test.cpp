//----------------------------------------------------------------------
// Author: Michael Calmette
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   hw9_test.cpp
//
// TODO:   add your own description
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  BSTCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());
}

// Test 2
TEST(BasicListTest, SimpleFind) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("d", v));  
}


// Test 4
TEST(BasicListTest, SimpleRange) {
  BSTCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}


// Test 5
TEST(BasicListTest, SimpleSort) {
  BSTCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}


TEST(BasicListTest, LargerAddAndFind) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(0, c.size());
  c.add("d", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 9.0);
  c.add("g", 15.0);
  c.add("c", 12.0);
  c.add("e", 13.0);
  c.add("b", 1.0);
  c.add("f", 2.0);
  ASSERT_EQ(7, c.size());
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("g", v));
  ASSERT_EQ(true, c.find("e", v));
  ASSERT_EQ(true, c.find("f", v));
}

//Test that height function works
TEST(BasicListTest, HeightTest) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(0, c.size());
  c.add("d", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 9.0);
  c.add("g", 15.0);
  c.add("c", 12.0);
  c.add("e", 13.0);
  c.add("b", 1.0);
  c.add("f", 2.0);
  ASSERT_EQ(7, c.size());
  ASSERT_EQ(4, c.height());
  c.add("ab",4.5); //multistrings work too
  ASSERT_EQ(5, c.height()); 
}

//more indepth remove
TEST(BasicListTest, ComplexRemoveElems) {
  BSTCollection<string,int> c;
  c.add("k", 10);
  c.add("a", 20);
  c.add("l", 30);
  c.add("c", 30);
  c.add("b", 20);
  c.add("u", 30);
  ASSERT_EQ(6, c.size());
  int v;
  c.remove("k");
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(false, c.find("k", v));
  c.remove("l");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(false, c.find("l", v));
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
}


TEST(BasicCollectionTest, EqualTest) {
  BSTCollection<string,double> c;
  BSTCollection<string,double> d;
  double v;
  c = d;
  c.add("h",1.0);
  c.add("b",1.0);
  c.add("l",1.0);
  d = c;
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(3, d.size());
  ASSERT_EQ(true, c.find("h", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("l", v));
  ASSERT_EQ(true, d.find("h", v));
  ASSERT_EQ(true, d.find("b", v));
  ASSERT_EQ(true, d.find("l", v));
}


// TODO: ... additional tests ...

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

