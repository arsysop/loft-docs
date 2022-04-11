namespace equality {

using value_type = int;

//! Avoid defining default operations
class Base {
	typedef value_type T;
public:
	Base() = default;
	Base(const value_type& x) : x_(x) {}

protected:
	value_type  x_;
};

class AlwaysFalse {
public:
	bool operator==(const AlwaysFalse& other) const { return false; }
};

class AlwaysTrue {
public:
	bool operator==(const AlwaysTrue& other) const { return true; }
};

class Comparable : public Base {
public:
	bool operator==(const Comparable& other) const { return x_ == other.x_; }
	bool operator!=(const Comparable& other) const { return !operator==(other); } // optional
};

class NotComparable : public Base {
	// no equality operator, or private one
};

}

#include <vector>
#include <iostream>

using namespace equality;
using namespace std;

template <class T>
bool test_equal() {
	std::vector<T> a(10), b(10);
	return a == b;
};

/**
 * Is it required to fail for NotComparable type?
 */
template <class T>
bool test_equalTrue() {
	std::vector<T> a, b;
	return a == b;
};

/**
 * Corner case: the following shall return false for any type.
 * Is it required to fail to compile for the type NotComparable?
 * Hint: the comparison may be optimized out by the implementation.
 * Is it implementation-specific behavior?
 */
template <class T>
bool test_equalFalse() {
	std::vector<T> a(1), b(2);
	return a == b;
};

template class std::vector<Comparable>;

int main() {
	cout << "test_equal<int>() returns " << (test_equal<int>() ? "true" : "false") << endl;
	cout << "test_equal<Comparable>() returns " << (test_equal<Comparable>() ? "true" : "false") << endl;

	// Evaluated as `true` even if the actual comparison for the type is always false
	cout << "test_equalTrue<AlwaysFalse>() returns " << (test_equalTrue<AlwaysFalse>() ? "true" : "false") << endl;

	// Evaluated as `false` even if the actual comparison for the type is always true
	cout << "test_equalFalse<AlwaysTrue>() returns " << (test_equalFalse<AlwaysTrue>() ? "true" : "false") << endl;

//	test_equal<NotComparable>(); // Shall fail to compile
//	test_equalFalse<NotComparable>();  // ???
//	test_equalFalse<NotComparable>();  // ???

}