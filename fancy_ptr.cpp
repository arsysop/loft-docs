
#include "fancy_ptr.h"

#include <vector>
#include <memory>
#include <iostream>
using namespace std;

int foo(const int* buf, unsigned long n);
int test_1(const vector<int>& v) {
    return foo(&v[0], v.size());
}

typedef vector<int, alloc<int>> FancyVec;
int test_2(const FancyVec& v) {
    return foo(&v[0], v.size());
}
