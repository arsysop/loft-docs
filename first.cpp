#include <iostream>
#include <type_traits>

using namespace std;

int incr(int i) { return i + 1; }
int decr(int i) { return i - 1; }

template <bool T> int add(int i);
template <> int add<true>(int i) { return incr(i); }
template <> int add<false>(int i) { return decr(i); }

template <class T> int incr_or_decr(T t) {
    return add< std::is_standard_layout<T>::value>(t.i);
}

struct Good {
    int i = 0;
};

struct Bad {
    int i = 0;
    virtual ~Bad() {}
};

int main() {
    Good good;
    Bad bad;

    std::cout << "Good: " << incr_or_decr(good) << endl;
    std::cout <<  "Bad: " << incr_or_decr(bad) << endl;
    return 0;
}
