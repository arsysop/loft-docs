/*******************************************************************************
 * Copyright (c) 2022 ArSysOp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Contributors:
 *     (ArSysOp) - initial API and implementation
 *******************************************************************************/

#ifndef FANCY_PTR_H
#define FANCY_PTR_H


#include <vector>
#include <memory>

using std::nullptr_t;
using std::true_type;

namespace my {


template<class Tp>
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
ptrdiff_t operator-(const Ptr<T>& a, const Ptr<T> b) {
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


template<class Tp>
class custom_allocator;

template<>
class custom_allocator<void> {
public:
    typedef void *pointer;
    typedef const void *const_pointer;
    typedef void value_type;

    template<class Up>
    struct rebind {
        typedef custom_allocator<Up> other;
    };
};

template<class Tp>
class custom_allocator {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Ptr<Tp> pointer; // was: typedef Tp *pointer;
//    typedef const CPtr<Tp> const_pointer; // typedef const Tp *const_pointer;
    typedef const Ptr<Tp> const_pointer; // typedef const Tp *const_pointer;
    typedef Tp &reference;
    typedef const Tp &const_reference;
    typedef Tp value_type;

    typedef true_type propagate_on_container_move_assignment;
    typedef true_type is_always_equal;

    custom_allocator() noexcept {}

    template<class _Up>
    custom_allocator(const custom_allocator<_Up> &) noexcept {}

    pointer address(reference __x) const noexcept { return std::addressof(__x); }

    const_pointer address(const_reference __x) const noexcept {
        return std::addressof(__x);
    }

    pointer allocate(size_type n, custom_allocator<void>::const_pointer = 0) {
        if (n > max_size())
            std::__throw_length_error("custom_allocatorator<T>::allocate(size_t n)"
                                      " 'n' exceeds maximum supported size");
        return static_cast<Tp *>(std::__libcpp_allocate(n * sizeof(Tp), alignof(Tp)));
    }

    void deallocate(pointer p, size_type n) noexcept {
        std::__libcpp_deallocate((void *) p.p_, n * sizeof(Tp), alignof(Tp));
    }

    size_type max_size() const noexcept { return size_type(~0) / sizeof(Tp); }

    template<class Up, class... Args>
    void
    construct(Up *p, Args &&... args) {
        ::new((void *) p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~Tp(); }
};

} // namespace my

#endif //FANCY_PTR_H
