// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Integer.c++ TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Deque.h"

#define ALL_OF_IT   typedef typename TestFixture::deque_type      deque_type; \
                    typedef typename TestFixture::allocator_type  allocator_type; \
                    typedef typename TestFixture::value_type      value_type; \
                    typedef typename TestFixture::size_type       size_type; \
                    typedef typename TestFixture::difference_type difference_type; \
                    typedef typename TestFixture::pointer         pointer; \
                    typedef typename TestFixture::const_pointer   const_pointer; \
                    typedef typename TestFixture::reference       reference; \
                    typedef typename TestFixture::const_reference const_reference; \

// ---------
// TestDeque
// ---------

template <typename D>
struct TestDeque : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          D                  deque_type;
    typedef typename D::allocator_type  allocator_type;
    typedef typename D::value_type      value_type;
    typedef typename D::size_type       size_type;
    typedef typename D::difference_type difference_type;
    typedef typename D::pointer         pointer;
    typedef typename D::const_pointer   const_pointer;
    typedef typename D::reference       reference;
    typedef typename D::const_reference const_reference;};

typedef testing::Types<
            std::deque<int>,
            std::deque<double>,
            my_deque<int>,
            my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

// -----------
// Empty Tests
// -----------

TYPED_TEST(TestDeque, Empty_1) {
    ALL_OF_IT;

    deque_type x;
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Empty_2) {
    ALL_OF_IT;

    deque_type x(0);
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Empty_3) {
    ALL_OF_IT;

    deque_type x(1, 1);
    x.pop_back();
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Empty_4) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_back(1);
    x.pop_back();
    const bool b = x.empty();
    ASSERT_TRUE(b);}

// ----------------
// Assignment Tests
// ----------------

TYPED_TEST(TestDeque, Assignment_1) {
    ALL_OF_IT;

    deque_type x(3, 0);
    deque_type y(3, 1);
    x = y;
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Assignment_2) {
    ALL_OF_IT;

    deque_type x(3, 0);
    deque_type y(4, 1);
    x = y;
    const size_type s = x.size();
    ASSERT_EQ(4, s);}

TYPED_TEST(TestDeque, Assignment_3) {
    ALL_OF_IT;

    deque_type x;
    deque_type y(4, 3);
    x = y;
    const size_type s = x.size();
    ASSERT_EQ(4, s);}

TYPED_TEST(TestDeque, Assignment_4) {
    ALL_OF_IT;

    deque_type x(3);
    deque_type y(1);
    x = y;
    const size_type s = x.size();
    ASSERT_EQ(1, s);}

// --------------
// Indexing Tests
// --------------

TYPED_TEST(TestDeque, Indexing_1) {
    ALL_OF_IT;

    deque_type x(3, 1);
    value_type temp = x[2];
    ASSERT_EQ(1, temp);}

TYPED_TEST(TestDeque, Indexing_2) {
    ALL_OF_IT;

    const deque_type x(3, 2);
    deque_type c(x);
    value_type temp = c[1];
    ASSERT_EQ(2, temp);}

TYPED_TEST(TestDeque, Indexing_3) {
    ALL_OF_IT;

    deque_type x(3, 1);
    x.push_back(4);
    x.push_back(5);
    value_type temp = x[4];
    ASSERT_EQ(5, temp);}

TYPED_TEST(TestDeque, Indexing_4) {
    ALL_OF_IT;

    deque_type x(34, 2);
    value_type temp = x[33];
    ASSERT_EQ(2, temp);}

TYPED_TEST(TestDeque, Indexing_5) {
    ALL_OF_IT;

    deque_type x(24, 2);
    x.push_back(5);
    value_type temp = x[24];
    ASSERT_EQ(5, temp);}

// --------
// At Tests
// --------

TYPED_TEST(TestDeque, At_1) {
    ALL_OF_IT;

    deque_type x(11, 3);
    const value_type at = x.at(0);
    ASSERT_EQ(3, at);}

TYPED_TEST(TestDeque, At_2) {
    ALL_OF_IT;

    deque_type x(2);
    x.push_back(1);
    x.push_back(2);
    const value_type at = x.at(3);
    ASSERT_EQ(2, at);}

TYPED_TEST(TestDeque, At_3) {
    ALL_OF_IT;

    deque_type x(2);
    x.push_front(1);
    x.push_front(2);
    const value_type at = x.at(3);
    ASSERT_EQ(0, at);}

TYPED_TEST(TestDeque, At_4) {
    ALL_OF_IT;

    deque_type x(11);
    x.push_front(1);
    x.push_back(2);
    const value_type at = x.at(1);
    ASSERT_EQ(0, at);}

// ----------
// Back Tests
// ----------

TYPED_TEST(TestDeque, Back_1) {
    ALL_OF_IT;

    deque_type x(11, 3);
    const value_type back = x.back();
    ASSERT_EQ(3, back);}

TYPED_TEST(TestDeque, Back_2) {
    ALL_OF_IT;

    deque_type x(11, 3);
    x.pop_back();
    x.pop_back();
    const value_type back = x.back();
    ASSERT_EQ(3, back);}

TYPED_TEST(TestDeque, Back_3) {
    ALL_OF_IT;

    deque_type x(11, 3);
    x.pop_back();
    x.pop_back();
    x.push_back(4);
    const value_type back = x.back();
    ASSERT_EQ(4, back);}

TYPED_TEST(TestDeque, Back_4) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_back(4);
    const value_type back = x.back();
    ASSERT_EQ(4, back);}

// -----------
// Begin Tests
// -----------

TYPED_TEST(TestDeque, Begin_1) {
    ALL_OF_IT;

    deque_type x(23, 3);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(3, *it);}

TYPED_TEST(TestDeque, Begin_2) {
    ALL_OF_IT;

    deque_type x(3, 2);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(2, *it);}

TYPED_TEST(TestDeque, Begin_3) {
    ALL_OF_IT;

    deque_type x(3, 2);
    x.push_front(1);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(1, *it);}

 TYPED_TEST(TestDeque, Begin_4) {
    ALL_OF_IT;

    deque_type x(3, 2);
    x.push_front(1);
    x.pop_front();
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(2, *it);}   

 TYPED_TEST(TestDeque, Begin_5) {
    ALL_OF_IT;

    deque_type x(3, 2);
    x.pop_front();
    x.push_front(1);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(1, *it);}   

// -----------
// Clear Tests
// -----------

TYPED_TEST(TestDeque, Clear_1) {
    ALL_OF_IT;

    deque_type x(23, 23);
    x.clear();
    ASSERT_EQ(0, x.size());}

 TYPED_TEST(TestDeque, Clear_2) {
    ALL_OF_IT;

    deque_type x(9, 9);
    x.clear();
    ASSERT_EQ(0, x.size());}

TYPED_TEST(TestDeque, Clear_3) {
    ALL_OF_IT;

    deque_type x(5, 9);
    x.clear();
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Clear_4) {
    ALL_OF_IT;

    deque_type x(5, 9);
    x.clear();
    x.push_back(1);
    const size_type s = x.size();
    ASSERT_EQ(s, 1);}

// ---------
// End Tests
// ---------

TYPED_TEST(TestDeque, End_1) {
    ALL_OF_IT;

    deque_type x(23, 1);
    typename deque_type::iterator end = x.end();
    ASSERT_EQ(1, *(--end));}

TYPED_TEST(TestDeque, End_2) {
    ALL_OF_IT;

    deque_type x(3, 2);
    typename deque_type::iterator end = x.end();
    ASSERT_EQ(2, *(--end));}

TYPED_TEST(TestDeque, End_3) {
    ALL_OF_IT;

    deque_type x(10, 0);
    x.push_back(1);
    typename deque_type::iterator end = x.end();
    ASSERT_EQ(1, *(--end));}

TYPED_TEST(TestDeque, End_4) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_front(1);
    typename deque_type::iterator end = x.end();
    ASSERT_EQ(1, *(--end));}


TYPED_TEST(TestDeque, End_5) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.pop_back();
    typename deque_type::iterator end = x.end();
    ASSERT_EQ(1, *(--end));}

// -----------
// Erase Tests
// -----------

TYPED_TEST(TestDeque, Erase_1) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.erase(x.begin()); 
    const size_type s = x.size();
    ASSERT_EQ(1, s);}

TYPED_TEST(TestDeque, Erase_2) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.erase(x.end() - 1); 
    const size_type s = x.size();
    ASSERT_EQ(1, s);}

TYPED_TEST(TestDeque, Erase_3) {
    ALL_OF_IT;

    deque_type x(3, 1);
    x.erase((x.begin() + 1)); 
    const size_type s = x.size();
    ASSERT_EQ(2, s);}

TYPED_TEST(TestDeque, Erase_4) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_back(3);
    x.erase(x.begin()); 
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

// -----------
// Front Tests
// -----------

TYPED_TEST(TestDeque, Front_1) {
    ALL_OF_IT;

    deque_type x(2, 1);
    const value_type temp = x.front();
    ASSERT_EQ(1, temp);}

TYPED_TEST(TestDeque, Front_2) {
    ALL_OF_IT;

    deque_type x;
    x.push_front(9);
    const value_type temp = x.front();
    ASSERT_EQ(9, temp);}

TYPED_TEST(TestDeque, Front_3) {
    ALL_OF_IT;

    deque_type x;
    x.push_back(9);
    const value_type temp = x.front();
    ASSERT_EQ(9, temp);}

TYPED_TEST(TestDeque, Front_4) {
    ALL_OF_IT;

    deque_type x(3, 3);
    x.pop_front();
    const value_type temp = x.front();
    ASSERT_EQ(3, temp);}

// ------------
// Insert Tests
// ------------

TYPED_TEST(TestDeque, Insert_1) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.insert(x.begin(), 0); 
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Insert_2) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.insert(x.end(), 0); 
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Insert_3) {
    ALL_OF_IT;

    deque_type x(5);
    x.insert((x.begin() + 1), 1); 
    const size_type s = x.size();
    ASSERT_EQ(6, s);}

TYPED_TEST(TestDeque, Insert_4) {
    ALL_OF_IT;

    deque_type x(5);
    x.insert((x.begin() + 1), 1); 
    const value_type temp = x[1];
    ASSERT_EQ(1, temp);}   

// --------------
// Pop_Back Tests
// --------------

TYPED_TEST(TestDeque, Pop_Back_1) {
    ALL_OF_IT;

    deque_type x(5, 1);
    x.pop_back();
    x.pop_back();
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Pop_Back_2) {
    ALL_OF_IT;

    deque_type x(1, 1);
    x.push_back(2);
    x.push_back(3);
    x.pop_back();
    x.pop_back();
    const size_type s = x.size();
    ASSERT_EQ(1, s);}

TYPED_TEST(TestDeque, Pop_Back_3) {
    ALL_OF_IT;

    deque_type x(3, 1);
    x.push_back(2);
    x.push_back(3);
    x.pop_back();
    const size_type s = x.size();
    ASSERT_EQ(4, s);
    const value_type temp = x[3];
    ASSERT_EQ(2, temp);}

TYPED_TEST(TestDeque, Pop_Back_4) {
    ALL_OF_IT;

    deque_type x(11, 1);
    x.pop_back();
    const size_type s = x.size();
    ASSERT_EQ(10, s);
    const value_type temp = x[9];
    ASSERT_EQ(1, temp);}

// ---------------
// Pop_Front Tests
// ---------------

TYPED_TEST(TestDeque, Pop_Font_1) {
    ALL_OF_IT;

    deque_type x(5, 1);
    x.pop_front();
    x.pop_front();
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Pop_Font_2) {
    ALL_OF_IT;

    deque_type x(2, 1);
    x.pop_front();
    x.pop_front();
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TYPED_TEST(TestDeque, Pop_Font_3) {
    ALL_OF_IT;

    deque_type x(1, 1);
    x.push_back(2);
    x.pop_front();
    x.push_back(3);
    x.pop_front();
    const size_type s = x.size();
    ASSERT_EQ(1, s);
    const value_type temp = x[0];
    ASSERT_EQ(3, temp);}

TYPED_TEST(TestDeque, Pop_Font_4) {
    ALL_OF_IT;

    deque_type x(10, 0);
    x.pop_front();
    x.pop_front();
    const size_type s = x.size();
    ASSERT_EQ(8, s);
    const value_type temp = x[0];
    ASSERT_EQ(0, temp);}

// ---------------
// Push_Back Tests
// ---------------

TYPED_TEST(TestDeque, Push_Back_1) {
    ALL_OF_IT;

    deque_type x(3, 1);
    x.push_back(4);
    x.push_back(5);
    const size_type s = x.size();
    ASSERT_EQ(5, s);}

TYPED_TEST(TestDeque, Push_Back_2) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_back(4);
    x.push_back(5);
    const size_type s = x.size();
    ASSERT_EQ(2, s);
    const value_type temp = x[1];
    ASSERT_EQ(5, temp);}

TYPED_TEST(TestDeque, Push_Back_3) {
    ALL_OF_IT;

    deque_type x(1);
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    const size_type s = x.size();
    ASSERT_EQ(4, s);
    const value_type temp = x[3];
    ASSERT_EQ(3, temp);}

TYPED_TEST(TestDeque, Push_Back_4) {
    ALL_OF_IT;

    deque_type x(5, 0);
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.push_back(4);
    const size_type s = x.size();
    ASSERT_EQ(3, s);
    const value_type temp = x[2];
    ASSERT_EQ(4, temp);}

// ----------------
// Push_Front Tests
// ----------------

TYPED_TEST(TestDeque, Push_Front_1) {
    ALL_OF_IT;

    deque_type x(3, 0);
    x.push_front(1);
    x.push_front(2);
    const size_type s = x.size();
    ASSERT_EQ(5, s);}

TYPED_TEST(TestDeque, Push_Font_2) {
    ALL_OF_IT;

    deque_type x(3, 1);
    x.push_front(4);
    const value_type temp = x[0];
    ASSERT_EQ(4, temp);}

TYPED_TEST(TestDeque, Push_Font_3) {
    ALL_OF_IT;

    deque_type x(0);
    x.push_front(4);
    x.push_front(5);
    const value_type temp1 = x[0];
    ASSERT_EQ(5, temp1);
    const value_type temp2 = x[1];
    ASSERT_EQ(4, temp2);}

TYPED_TEST(TestDeque, Push_Font_4) {
    ALL_OF_IT;

    deque_type x(1);
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_front(4);
    const value_type temp1 = x[0];
    ASSERT_EQ(4, temp1);
    const value_type temp2 = x[4];
    ASSERT_EQ(0, temp2);}

// ------------
// Resize Tests
// ------------

TYPED_TEST(TestDeque, Resize_1) {
    ALL_OF_IT;

    deque_type x(1);
    x.resize(3);
    const size_type s = x.size();
    ASSERT_EQ(3, s);}

TYPED_TEST(TestDeque, Resize_2) {
    ALL_OF_IT;

    deque_type x(5);
    x.resize(25);
    const size_type s = x.size();
    ASSERT_EQ(25, s);}

TYPED_TEST(TestDeque, Resize_3) {
    ALL_OF_IT;

    deque_type x(5);
    x.resize(7);
    const size_type s = x.size();
    ASSERT_EQ(7, s);}

TYPED_TEST(TestDeque, Resize_4) {
    ALL_OF_IT;

    deque_type x(15);
    x.resize(5);
    const size_type s = x.size();
    ASSERT_EQ(5, s);}

// ----------
// Size Tests
// ----------

TYPED_TEST(TestDeque, Size_1) {
    ALL_OF_IT;

    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TYPED_TEST(TestDeque, Size_2) {
    ALL_OF_IT;

    deque_type x(0);
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TYPED_TEST(TestDeque, Size_3) {
    ALL_OF_IT;

    deque_type x(3);
    ASSERT_EQ(x.size(), 3);}

TYPED_TEST(TestDeque, Size_4) {
    ALL_OF_IT;

    deque_type x(15);
    ASSERT_EQ(x.size(), 15);}

TYPED_TEST(TestDeque, Size_5) {
    ALL_OF_IT;

    deque_type x(40);
    ASSERT_EQ(x.size(), 40);}

 TYPED_TEST(TestDeque, Size_6) {
    ALL_OF_IT;

    deque_type x(3, 2);
    x.push_back(2);
    ASSERT_EQ(x.size(), 4);}   

//---------------
// Swapping Tests
//---------------

TYPED_TEST(TestDeque, Swap_1) {
    ALL_OF_IT;

    deque_type x(3, 100);
    deque_type y(3, 200);
    x.swap(y);
    const value_type c1 = std::count (x.begin(), x.end(), 200);
    const value_type c2 = std::count (y.begin(), y.end(), 100);
    ASSERT_EQ(3, c1);
    ASSERT_EQ(3, c2);}

TYPED_TEST(TestDeque, Swap_2) {
    ALL_OF_IT;

    deque_type x(4, 10);
    deque_type y(5, 10);
    x.swap(y);
    const value_type c1 = std::count (x.begin(), x.end(), 10);
    const value_type c2 = std::count (y.begin(), y.end(), 10);
    ASSERT_EQ(5, c1);
    ASSERT_EQ(4, c2);}

TYPED_TEST(TestDeque, Swap_3) {
    ALL_OF_IT;

    deque_type x(1, 1);
    deque_type y(10, 0);
    x.swap(y);
    const value_type c1 = std::count (x.begin(), x.end(), 0);
    const value_type c2 = std::count (y.begin(), y.end(), 1);
    ASSERT_EQ(10, c1);
    ASSERT_EQ(1, c2);}

TYPED_TEST(TestDeque, Swap_4) {
    ALL_OF_IT;

    deque_type x(3, 3);
    deque_type y(4, 4);
    x.swap(y);
    ASSERT_EQ(3, y.size());
    ASSERT_EQ(4, x.size());}


// -------------
// Equality Test
// -------------

TYPED_TEST(TestDeque, Equality_1) {
    ALL_OF_IT;

    deque_type x;
    deque_type y;
    ASSERT_EQ( (x == y), true);}

TYPED_TEST(TestDeque, Equality_2) {
    ALL_OF_IT;

    deque_type x(3, 4);
    deque_type y(3, 4);
    ASSERT_EQ( (x == y), true);}

TYPED_TEST(TestDeque, Equality_3) {
    ALL_OF_IT;

    deque_type x(13);
    deque_type y(13);
    ASSERT_EQ( (x == y), true);}

// ----------------
// Operator < Tests
// ----------------

TYPED_TEST(TestDeque, Less_Than_1) {
    ALL_OF_IT;

    deque_type x;
    deque_type y;
    ASSERT_TRUE( !(x < y));}

TYPED_TEST(TestDeque, Less_Than_2) {
    ALL_OF_IT;

    deque_type x(1, 0);
    deque_type y(1, -1);
    ASSERT_TRUE(y < x);}

TYPED_TEST(TestDeque, Less_Than_3) {
    ALL_OF_IT;

    deque_type x(2, 0);
    deque_type y(2, 0);

    x[1] = -1;

    ASSERT_TRUE(x < y);}

// ********* Iterator Tests ********** //

// ---------------------
// Iterator Equals Tests
// ---------------------

TYPED_TEST(TestDeque, I_Equals_1) {
    ALL_OF_IT;

    deque_type x(4, 0);
    typename deque_type::iterator begin1 = x.begin();
    typename deque_type::iterator begin2 = x.begin();
    ASSERT_TRUE(begin1 == begin2);}

TYPED_TEST(TestDeque, I_Equals_2) {
    ALL_OF_IT;

    deque_type x(1);
    typename deque_type::iterator begin1 = x.begin();
    typename deque_type::iterator begin2 = x.begin();
    ASSERT_TRUE(begin1 == begin2);}


TYPED_TEST(TestDeque, I_Equals_3) {
    ALL_OF_IT;

    deque_type x(1, 0);
    typename deque_type::iterator y = x.begin();
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_TRUE(y == z);}

// ------------------------
// Iterator Not Equal Tests
// ------------------------

TYPED_TEST(TestDeque, I_Not_Equals_1) {
    ALL_OF_IT;

    deque_type x(4, 0);
    deque_type y(4, 1);
    typename deque_type::iterator begin1 = x.begin();
    typename deque_type::iterator begin2 = y.begin();
    ASSERT_TRUE(begin1 != begin2);}

TYPED_TEST(TestDeque, I_Not_Equals_2) {
    ALL_OF_IT;

    deque_type x(1);
    typename deque_type::iterator begin1 = x.begin();
    typename deque_type::iterator begin2 = x.begin();
    ASSERT_FALSE(begin1 != begin2);}

TYPED_TEST(TestDeque, I_Not_Equals_3) {
    ALL_OF_IT;

    deque_type x(1);
    typename deque_type::iterator y = x.begin();
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_FALSE(y != z);}

// ----------
// + Operator
// ----------

TYPED_TEST(TestDeque, I_Plus_1) {
    ALL_OF_IT;

    deque_type x(1);
    typename deque_type::iterator y = x.begin() + 1;
    typename deque_type::iterator z = x.end();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, I_Plus_2) {
    ALL_OF_IT;

    deque_type x(9);
    typename deque_type::iterator y = x.begin() + 9;
    typename deque_type::iterator z = x.end();
    ASSERT_TRUE(y == z);}


TYPED_TEST(TestDeque, I_Plus_3) {
    ALL_OF_IT;

    deque_type x(20);
    x.push_back(2);
    typename deque_type::iterator y = x.end() - 1;
    typename deque_type::iterator z = x.begin() + 20;
    ASSERT_TRUE(y == z);}

// ----------
// - Operator
// ----------

TYPED_TEST(TestDeque, I_Minus_1) {
    ALL_OF_IT;

    deque_type x(1);
    typename deque_type::iterator y = x.end() - 1;
    typename deque_type::iterator z = x.begin();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, I_Minus_2) {
    ALL_OF_IT;

    deque_type x(13);
    typename deque_type::iterator y = x.end() - 13;
    typename deque_type::iterator z = x.begin();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, I_Minus_3) {
    ALL_OF_IT;

    deque_type x(115);
    x.push_back(5);
    typename deque_type::iterator y = x.end() - 1;
    typename deque_type::iterator z = x.begin() + 115;
    ASSERT_TRUE(y == z);}

// ----------
// * Operator
// ----------

TYPED_TEST(TestDeque, I_Dereference_1) {
    ALL_OF_IT;

    deque_type x(1, 1);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(*it, 1);}

TYPED_TEST(TestDeque, I_Dereference_2) {
    ALL_OF_IT;

    deque_type x(13, 8);
    typename deque_type::iterator it = x.end() - 1;
    ASSERT_EQ(*it, 8);}

TYPED_TEST(TestDeque, I_Dereference_3) {
    ALL_OF_IT;

    deque_type x(13, 8);
    typename deque_type::iterator it = x.begin() + 5;
    ASSERT_EQ(*it, 8);}

// ------------------
// Increment operator
// ------------------

TYPED_TEST(TestDeque, I_Increment_1) {
    ALL_OF_IT;

    deque_type x(6, 2);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(*(it++), 2);}

TYPED_TEST(TestDeque, I_Increment_2) {
    ALL_OF_IT;

    deque_type x(2, 1);
    typename deque_type::iterator it = x.begin();
    ASSERT_EQ(*(it++), 1);}

TYPED_TEST(TestDeque, I_Increment_3) {
    ALL_OF_IT;

    deque_type x(5, 1);
    typename deque_type::iterator it = x.end() - 1;
    it++;
    ASSERT_TRUE(it == x.end());}

// ------------------
// Decrement operator
// ------------------

TYPED_TEST(TestDeque, I_Decrement_1) {
    ALL_OF_IT;

    deque_type x(5, 1);
    typename deque_type::iterator it = x.end();
    it--;
    ASSERT_EQ(*it, 1);}


TYPED_TEST(TestDeque, I_Decrement_2) {
    ALL_OF_IT;

    deque_type x(50);
    x.push_back(1);
    typename deque_type::iterator it = x.end();
    it--;
    ASSERT_TRUE(it == (x.end() - 1));}

// --------------------
// Plus_equals Operator
// --------------------

TYPED_TEST(TestDeque, I_Plus_Equals_1) {
    ALL_OF_IT;

    deque_type x(2);
    typename deque_type::iterator it = x.begin();
    it += 2;
    ASSERT_TRUE(it == x.end());}

TYPED_TEST(TestDeque, I_Plus_Equals_2) {
    ALL_OF_IT;

    deque_type x(12);
    x.push_back(3);
    typename deque_type::iterator it = x.begin();
    it += 12;
    ASSERT_EQ(*it, 3);}

TYPED_TEST(TestDeque, I_Plus_Equals_3) {
    ALL_OF_IT;

    deque_type x(100);
    x.push_back(1);
    typename deque_type::iterator it = x.begin();
    it += 100;
    it--;
    ASSERT_EQ(*it, 0);}

// ---------------------
// Minus_equals Operator
// ---------------------

TYPED_TEST(TestDeque, I_Minus_Equals_1) {
    ALL_OF_IT;

    deque_type x(2, 1);
    typename deque_type::iterator it = x.end();
    it -= 2;
    ASSERT_TRUE(it == x.begin());}

TYPED_TEST(TestDeque, I_Minus_Equals_2) {
    ALL_OF_IT;

    deque_type x(5, 1);
    typename deque_type::iterator it = x.end();
    it -= 3;
    ASSERT_EQ(*it, 1);}

TYPED_TEST(TestDeque, I_Minus_Equals_3) {
    ALL_OF_IT;

    deque_type x(100);
    x.push_back(1);
    typename deque_type::iterator it = x.end();
    it -= 3;
    ASSERT_EQ(*it, 0);}

// *********** Const Iterator ************ //

// ---------------------
// Iterator Equals Tests
// ---------------------

TYPED_TEST(TestDeque, CI_Equals_1) {
    ALL_OF_IT;

    const deque_type x(4, 0);
    typename deque_type::const_iterator begin1 = x.begin();
    typename deque_type::const_iterator begin2 = x.begin();
    ASSERT_TRUE(begin1 == begin2);}

TYPED_TEST(TestDeque, CI_Equals_2) {
    ALL_OF_IT;

    const deque_type x(1);
    typename deque_type::const_iterator begin1 = x.begin();
    typename deque_type::const_iterator begin2 = x.begin();
    ASSERT_TRUE(begin1 == begin2);}


TYPED_TEST(TestDeque, CI_Equals_3) {
    ALL_OF_IT;

    const deque_type x(1, 0);
    typename deque_type::const_iterator y = x.begin();
    typename deque_type::const_iterator z = x.end();
    ASSERT_TRUE(y == --z);}

// ------------------------
// Iterator Not Equal Tests
// ------------------------

TYPED_TEST(TestDeque, CI_Not_Equals_1) {
    ALL_OF_IT;

    const deque_type x(4, 0);
    const deque_type y(4, 1);
    typename deque_type::const_iterator begin1 = x.begin();
    typename deque_type::const_iterator begin2 = y.begin();
    ASSERT_TRUE(begin1 != begin2);}

TYPED_TEST(TestDeque, CI_Not_Equals_2) {
    ALL_OF_IT;

    const deque_type x(1);
    typename deque_type::const_iterator begin1 = x.begin();
    typename deque_type::const_iterator begin2 = x.begin();
    ASSERT_FALSE(begin1 != begin2);}

TYPED_TEST(TestDeque, CI_Not_Equals_3) {
    ALL_OF_IT;

    const deque_type x(1);
    typename deque_type::const_iterator y = x.begin();
    typename deque_type::const_iterator z = x.end();
    ASSERT_FALSE(y != --z);}

// ----------
// + Operator
// ----------

TYPED_TEST(TestDeque, CI_Plus_1) {
    ALL_OF_IT;

    const deque_type x(1);
    typename deque_type::const_iterator y = x.begin() + 1;
    typename deque_type::const_iterator z = x.end();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, CI_Plus_2) {
    ALL_OF_IT;

    const deque_type x(9);
    typename deque_type::const_iterator y = x.begin() + 9;
    typename deque_type::const_iterator z = x.end();
    ASSERT_TRUE(y == z);}


TYPED_TEST(TestDeque, CI_Plus_3) {
    ALL_OF_IT;

    const deque_type x(20);
    typename deque_type::const_iterator y = x.end();
    typename deque_type::const_iterator z = x.begin() + 20;
    ASSERT_TRUE(y == z);}

// ----------
// - Operator
// ----------

TYPED_TEST(TestDeque, CI_Minus_1) {
    ALL_OF_IT;

    const deque_type x(1);
    typename deque_type::const_iterator y = x.end();
    --y;
    typename deque_type::const_iterator z = x.begin();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, CI_Minus_2) {
    ALL_OF_IT;

    const deque_type x(13);
    typename deque_type::const_iterator y = x.end() - 13;
    typename deque_type::const_iterator z = x.begin();
    ASSERT_TRUE(y == z);}

TYPED_TEST(TestDeque, CI_Minus_3) {
    ALL_OF_IT;

    const deque_type x(115);
    typename deque_type::const_iterator y = x.end();
    typename deque_type::const_iterator z = x.begin() + 115;
    ASSERT_TRUE(y == z);}

// ----------
// * Operator
// ----------

TYPED_TEST(TestDeque, CI_Dereference_1) {
    ALL_OF_IT;

    const deque_type x(1, 1);
    typename deque_type::const_iterator it = x.begin();
    ASSERT_EQ(*it, 1);}

TYPED_TEST(TestDeque, CI_Dereference_2) {
    ALL_OF_IT;

    const deque_type x(13, 8);
    typename deque_type::const_iterator it = x.end() - 1;
    ASSERT_EQ(*it, 8);}

TYPED_TEST(TestDeque, CI_Dereference_3) {
    ALL_OF_IT;

    const deque_type x(13, 8);
    typename deque_type::const_iterator it = x.begin() + 5;
    ASSERT_EQ(*it, 8);}

// ------------------
// Increment operator
// ------------------

TYPED_TEST(TestDeque, CI_Increment_1) {
    ALL_OF_IT;

    const deque_type x(6, 2);
    typename deque_type::const_iterator it = x.begin();
    ASSERT_EQ(*(it++), 2);}

TYPED_TEST(TestDeque, CI_Increment_2) {
    ALL_OF_IT;

    const deque_type x(2, 1);
    typename deque_type::const_iterator it = x.begin();
    ASSERT_EQ(*(it++), 1);}

TYPED_TEST(TestDeque, CI_Increment_3) {
    ALL_OF_IT;

    const deque_type x(5, 1);
    typename deque_type::const_iterator it = x.end() - 1;
    it++;
    ASSERT_TRUE(it == x.end());}

// ------------------
// Decrement operator
// ------------------

TYPED_TEST(TestDeque, CI_Decrement_1) {
    ALL_OF_IT;

    const deque_type x(5, 1);
    typename deque_type::const_iterator it = x.end();
    it--;
    ASSERT_EQ(*it, 1);}


TYPED_TEST(TestDeque, CI_Decrement_2) {
    ALL_OF_IT;

    const deque_type x(50);
    typename deque_type::const_iterator it = x.end();
    it--;
    ASSERT_TRUE(it == (x.end() - 1));}

// --------------------
// Plus_equals Operator
// --------------------

TYPED_TEST(TestDeque, CI_Plus_Equals_1) {
    ALL_OF_IT;

    const deque_type x(2);
    typename deque_type::const_iterator it = x.begin();
    it += 2;
    ASSERT_TRUE(it == x.end());}

TYPED_TEST(TestDeque, CI_Plus_Equals_2) {
    ALL_OF_IT;

    const deque_type x(12, 3);
    typename deque_type::const_iterator it = x.begin();
    it += 10;
    ASSERT_EQ(*it, 3);}

TYPED_TEST(TestDeque, CI_Plus_Equals_3) {
    ALL_OF_IT;

    const deque_type x(100);
    typename deque_type::const_iterator it = x.begin();
    it += 99;
    it--;
    ASSERT_EQ(*it, 0);}

// ---------------------
// Minus_equals Operator
// ---------------------

TYPED_TEST(TestDeque, CI_Minus_Equals_1) {
    ALL_OF_IT;

    const deque_type x(2, 1);
    typename deque_type::const_iterator it = x.end();
    it -= 2;
    ASSERT_TRUE(it == x.begin());}

TYPED_TEST(TestDeque, CI_Minus_Equals_2) {
    ALL_OF_IT;

    const deque_type x(5, 1);
    typename deque_type::const_iterator it = x.end();
    it -= 3;
    ASSERT_EQ(*it, 1);}

TYPED_TEST(TestDeque, CI_Minus_Equals_3) {
    ALL_OF_IT;

    const deque_type x(100);
    typename deque_type::const_iterator it = x.end();
    it -= 3;
    ASSERT_EQ(*it, 0);}
