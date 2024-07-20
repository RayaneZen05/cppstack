#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "stack.hpp"
#include "doctest.h"
#include <exception>
using namespace std;
template <typename T>
stack<T>::stack() {
    // conversion du pointeur en pointeur vers T
    stk = static_cast<T*>(malloc(sizeof(T)*4096));
    BP = stk;
    SP = stk;
    pos = 0;
    bpos = 0;
    size = 4096;
}
template <typename T>
stack<T>::stack(size_t stksize) {
    stk = static_cast<T*>(malloc(sizeof(T)*stksize));
    BP = stk;
    SP = stk;
    bpos = 0;
    pos = 0;
    size = stksize;
}
template <typename T>
T* stack<T>::getBP() const{
    if (BP == nullptr) {
        throw runtime_error("base pointer is null");
    }
    return BP;
}
template <typename T>
T stack<T>::top() const{
    if (SP == BP) {
        throw out_of_range("stack top is empty");
    }
    // get the last value before incrementing the SP
    return *(SP); // 1 voulant dire 1 T déja, car SP est de type T*
}
template <typename T>
T* stack<T>::getSP() const{
    if (SP == nullptr) {
        throw runtime_error("stack pointer is null");
    }
    return SP;
}
template <typename T>
T* stack<T>::push(T v) {
    if (pos+1 > size) {
        resize();
    }
    pos++;
    stk[pos] = v; // TODO: first position is skipped
    //! SP += sizeof(T); CPP is already aware of the type of SP (T*), 
    //! so it already increments by 4bytes  
    SP++;
    return SP;
}
template <typename T>
T* stack<T>::pop() {
    if (pos == 0) {
        throw out_of_range("stack is empty");
    }
    if (pos == bpos) {
        throw out_of_range("stack top is at base");
    }
    SP--;
    pos--;
    return SP;
}
template <typename T>
T* stack<T>::setBP() {
    bpos = pos;
    BP = SP;
    return BP;
}
template <typename T>
void stack<T>::free() {
    SP = nullptr;
    BP = nullptr;
    std::free(stk);
    stk = nullptr;
}

// TESTS
TEST_CASE("Stack - Initialization and Size") {
    SUBCASE("Default constructor") {
        stack<int> s;
        CHECK(s.getSP() != nullptr);
        CHECK(s.getBP() != nullptr);
        CHECK_THROWS_AS(s.top(), std::out_of_range); 
    }

    SUBCASE("Constructor with size") {
        stack<double> s(100);
        CHECK(s.getSP() != nullptr);
        CHECK(s.getBP() != nullptr);
        CHECK_THROWS_AS(s.top(), std::out_of_range);
    }
}

TEST_CASE("Stack - Push and Top") {
    SUBCASE("Pushing elements") {
        stack<int> s;
        s.push(10);
        CHECK_EQ(s.top(), 10);
        s.push(20);
        CHECK_EQ(s.top(), 20);
    }
}

TEST_CASE("Stack - Pop") {
    SUBCASE("Popping elements") {
        stack<int> s;
        s.push(10);
        s.push(20);
        CHECK_EQ(s.pop(), s.getSP());
        CHECK_EQ(s.top(), 10);
        CHECK_EQ(s.pop(), s.getSP());
        CHECK_THROWS_AS(s.top(), std::out_of_range);
    }
}

TEST_CASE("Stack - Base Pointer") {
    SUBCASE("Setting and using base pointer") {
        stack<int> s;
        s.push(10);
        s.push(20);
        s.setBP(); // Set base pointer here
        s.push(30);
        s.pop(); 
        // Even after popping, we should still be able to access 20
        CHECK_EQ(s.top(), 20);
    }
}

TEST_CASE("Stack - Resize") {
    SUBCASE("Automatic resize when pushing") {
        stack<int> s(2); // Small initial size
        s.push(1);
        s.push(2);
        // Should resize without error
        CHECK_NOTHROW(s.push(3));
        CHECK_EQ(s.top(), 3); 
    }
}

TEST_CASE("Stack - Free") {
    SUBCASE("Freeing stack memory") {
        stack<int> s;
        s.push(10);
        s.free();
        CHECK_THROWS_AS(s.top(), std::runtime_error); // Accessing after free should throw
        CHECK_THROWS_AS(s.push(20), std::runtime_error); 
    }
}