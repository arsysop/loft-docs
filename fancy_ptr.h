//
// Created by Vladimir on 21.12.2021.
//

#ifndef UNTITLED_FANCY_PTR_H
#define UNTITLED_FANCY_PTR_H


#include <vector>
#include <memory>

using std::nullptr_t;
using std::true_type;

template<class Tp_>
class Ptr;

template<class T>
struct Ptr {
    using P = T *;
    T *p_;

    Ptr(nullptr_t) : p_(nullptr) {}

    Ptr(T *p) : p_(p) {}

    Ptr(const T *&p) : p_(p) {}

    Ptr(const Ptr<T> &) = default;

    Ptr(Ptr<T> &&) = default;

    Ptr &operator=(const Ptr<T> &) = default;

    Ptr &operator=(Ptr<T> &&) = default;

    T &operator[](size_t n) { return *(p_ + n); }

    const T &operator[](size_t n) const { return *(p_ + n); }

    template<class U>
    Ptr(Ptr<U> other) : Ptr(static_cast<T *>(other.p_)) {}

    T *operator->() { return p_; }

    T *operator->() const { return p_; }

    bool operator==(const Ptr<T> other) const { return p_ == other.p_; }

    bool operator==(nullptr_t) const { return p_ == nullptr; }

    bool operator!=(const Ptr<T> other) const { return !operator==(other); }

    bool operator!=(nullptr_t) const { return p_ != nullptr; }

    Ptr &operator++() {
        ++p_;
        return *this;
    }

    Ptr operator++(int) {
        Ptr t(*this);
        ++p_;
        return t;
    }

    Ptr &operator--() {
        --p_;
        return *this;
    }

    Ptr operator--(int) {
        Ptr t(*this);
        --p_;
        return t;
    }

    Ptr operator+(size_t n) {
        return Ptr(p_ + n);
    }

    Ptr operator-(size_t n) { return Ptr(p_ - n); }

};


template<class T>
ptrdiff_t operator-(const Ptr<T> a, const Ptr<T> &b) {
    return a.p_ - b.p_;
}

template<class T>
struct CPtr {
    const T *p_;

    CPtr(T *p) : p_(p) {}

    CPtr(Ptr<T> ptr) : CPtr(ptr.p_) {}

    template<class U>
    CPtr(CPtr<U> other) : CPtr(static_cast<const T *>(other.p_)) {}

    const T *operator->() const { return p_; }
};


template<class Tp_>
class alloc;

template<>
class _LIBCPP_TEMPLATE_VIS alloc<void> {
public:
    typedef void *pointer;
    typedef const void *const_pointer;
    typedef void value_type;

    template<class Up_>
    struct rebind {
        typedef alloc<Up_> other;
    };
};

template<class Tp_>
class _LIBCPP_TEMPLATE_VIS alloc {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Ptr<Tp_> pointer; // typedef Tp_ *pointer;
//    typedef const CPtr<Tp_> const_pointer; // typedef const Tp_ *const_pointer;
    typedef const Ptr<Tp_> const_pointer; // typedef const Tp_ *const_pointer;
    typedef Tp_ &reference;
    typedef const Tp_ &const_reference;
    typedef Tp_ value_type;

    typedef true_type propagate_on_container_move_assignment;
    typedef true_type is_always_equal;

    alloc() noexcept {}

    template<class _Up>
    alloc(const alloc<_Up> &) noexcept {}

    pointer address(reference __x) const noexcept { return _VSTD::addressof(__x); }

    const_pointer address(const_reference __x) const noexcept {
        return _VSTD::addressof(__x);
    }

    pointer allocate(size_type n, alloc<void>::const_pointer = 0) {
        if (n > max_size())
            std::__throw_length_error("allocator<T>::allocate(size_t n)"
                                      " 'n' exceeds maximum supported size");
        return static_cast<Tp_ *>(_VSTD::__libcpp_allocate(n * sizeof(Tp_), _LIBCPP_ALIGNOF(Tp_)));
    }

    void deallocate(pointer p, size_type n) noexcept {
        _VSTD::__libcpp_deallocate((void *) p.p_, n * sizeof(Tp_), _LIBCPP_ALIGNOF(Tp_));
    }

    size_type max_size() const noexcept { return size_type(~0) / sizeof(Tp_); }

    template<class _Up, class... _Args>

    void
    construct(_Up *__p, _Args &&... __args) {
        ::new((void *) __p) _Up(_VSTD::forward<_Args>(__args)...);
    }

    void destroy(pointer p) { p->~Tp_(); }
};

#endif //UNTITLED_FANCY_PTR_H
