// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;
        std::allocator<pointer> _pa;

        pointer* _bl;
        pointer* _el;

        pointer* _b;
        pointer _bi;
        size_type _size;
        size_type _outer_size;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return (!_bl && !_el && !_b && !_bi) || ((_bl <= _b) && (_b <= _el));}

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::pointer         pointer;
                typedef typename my_deque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return ((lhs._p == rhs._p) && (lhs._i == rhs._i));}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                my_deque* _p;
                difference_type _i;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return (_p && (_i >= 0));}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                iterator (my_deque* p, difference_type i) : _p(p), _i(i) {
                    _p = p;
                    _i = i;
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    return _p->operator[](_i);}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {
                    ++_i;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -- () {
                    --_i;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    _i = _i + d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    _i = _i - d;
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::const_pointer   pointer;
                typedef typename my_deque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return ((lhs._p == rhs._p) && (lhs._i == rhs._i));}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                const my_deque* _p;
                difference_type _i;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return (_p && (_i >= 0));}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (const my_deque* p, difference_type i) : _p(p), _i(i) {
                    _p = p;
                    _i = i;
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    return _p->operator[](_i);}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    ++_i;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    --_i;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) {
                    _i = _i + d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) {
                    _i = _i - d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        explicit my_deque (const allocator_type& a = allocator_type()) : _a(a) {
            _bl = _el = _b = 0;
            _bi = 0;
            _size = _outer_size = 0;
            assert(valid());}

        /**
         * <your documentation>
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : _a(a) {
            _size = s; //_size - 1 is the laste index into the deque

            if(_size == 0){
                _bl = _el = _b = 0;
                _bi = 0;
                _size = _outer_size = 0;
            }
            else {
                if((_size % 10) == 0){
                    _outer_size = _size / 10;
                }
                else{
                    _outer_size = (_size / 10) + 1;
                }

                _bl = _b = _pa.allocate(_outer_size);
                _el = _bl + _outer_size;

                pointer* copy = _bl;
                while(copy != _el){
                    *copy = _a.allocate(10);
                    ++copy;
                }

                _bi = *_bl;

                uninitialized_fill(_a, begin(), end(), v);
            }
            assert(valid());}

        /**
         * <your documentation>
         */
        my_deque (const my_deque& that) : _a(that._a) {
            _size = that.size(); //_size - 1 is the laste index into the deque

            if(_size == 0){
                _bl = _el = _b = 0;
                _bi = 0;
                _size = _outer_size = 0;
            }
            else{ 
                if((_size % 10) == 0){
                    _outer_size = _size / 10;
                }
                else{
                    _outer_size = (_size / 10) + 1;
                }

                _bl = _b = _pa.allocate(_outer_size);
                _el = _bl + _outer_size;

                pointer* copy = _bl;
                while(copy != _el){
                    *copy = _a.allocate(10);
                    ++copy;
                }

                _bi = *_bl;

                uninitialized_copy(_a, that.begin(), that.end(), begin());
            }
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~my_deque () {
            if(_bl){
                clear();
                pointer* copy = _bl;
                while(copy != _el){
                    _a.deallocate(*copy, 10);
                    ++copy;
                }
                _pa.deallocate(_bl, _outer_size);
            }
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        my_deque& operator = (const my_deque& rhs) {
            size_type right_capacity;

            if(!empty()){
                right_capacity = ((_el - _b) * 10) - (_bi - *_b + 1);

                if(this == &rhs){
                    return *this;
                }
                if(size() == rhs.size()){
                    std::copy(rhs.begin(), rhs.end(), begin());
                }
                else if(rhs.size() < size()){
                    std::copy(rhs.begin(), rhs.end(), begin());
                    resize(rhs.size());
                }
                else if(rhs.size() <= right_capacity){
                    std::copy(rhs.begin(), rhs.begin() + size(), begin());
                    uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
                    _size = rhs.size();
                }
                else{
                    clear();
                    resize(rhs.size());
                    uninitialized_copy(_a, rhs.begin(), rhs.end(), begin());
                }
            }
            else{
                resize(rhs.size());
                uninitialized_copy(_a, rhs.begin(), rhs.end(), begin());
            }
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            size_type oi = index / 10;
            size_type ii = index % 10;

            size_type offset = (_bi - *_b);

            if((offset + ii) > 9){
                pointer* copy = _b + oi + 1;
                pointer pos = *copy + (offset + ii - 10);
                return *pos;
            }
            else{
                pointer* copy = _b + oi;
                pointer pos = *copy + offset + ii;
                return *pos;
            }
        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            if(index >= size()){
                throw std::out_of_range("deque");
            }
            return (this)->operator[](index);}

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            assert(!empty());
            return *(end() - 1);}

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            return iterator(this, 0);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            return const_iterator(this, 0);}

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            return iterator(this, (this)->size());}

        /**
         * <your documentation>
         */
        const_iterator end () const {
            return const_iterator(this, (this)->size());}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator i) {
            iterator e = end() - 1;
            iterator copy = i;
            while(copy != e){
                *copy = *(copy + 1);
                ++copy;
            }
            destroy(_a, copy, copy + 1);
            --_size;
            assert(valid());
            return i;}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            assert(!empty());
            return *begin();}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator i, const_reference v) {
            if(_outer_size == 0){
                resize(1);
                *(begin()) = v;
                return begin();
            }
            else if(empty()){
                *(begin()) = v;
                ++_size;
                return begin();
            }
            else{
                size_type right_capacity = ((_el - _b) * 10) - (_bi - *_b + 1);
                if(size() == right_capacity){
                    resize(size() + 1);
                }
                iterator e = end();
                while(i != e){
                    *e = *(e - 1);
                    --e;
                }
                *i = v;
                ++_size;
            }
            assert(valid());
            return i;}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            assert(!empty());
            resize(size() - 1);
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            assert(!empty());
            destroy(_a, begin(), begin() + 1);
            if((*_b + 9) == _bi){
                ++_b;
                _bi = *(_b);
            }
            else{
                ++_bi;
            }
            --_size;
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference v) {
            if(empty()){
                my_deque x(1, v);
                swap(x);
            }
            else{
                resize(size() + 1, v);
            }
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference v) {
            if(empty()){
                my_deque x(1, v);
                swap(x);
            }
            else{
                if((*_bl) == _bi){
                    size_type remember = _size;
                    my_deque x((_outer_size * 10) * 3);
                    swap(x);
                    uninitialized_copy(_a, x.begin(), x.end(), begin() + (x._outer_size * 10));

                    _b = _bl + (x._outer_size) - 1;
                    _bi = *_b + 9;
                    uninitialized_fill(_a, begin(), begin() + 1, v);
                    _size = remember + 1;
                }
                else if((*_b) == _bi){
                    --_b;
                    _bi = *_b + 9;
                    uninitialized_fill(_a, begin(), begin() + 1, v);
                    ++_size;
                }
                else{
                    --_bi;
                    uninitialized_fill(_a, begin(), begin() + 1, v);
                    ++_size;
                }
            }
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            size_type right_capacity;

            if(s == size()){
                return;
            }
            else if(s == 0){
                destroy(_a, begin(), end());
                _size = 0;
            }
            else if(empty()){
                my_deque x(s, v);
                swap(x);
            }
            else if(s < size()){
                destroy(_a, begin() + s, end());
                _size = s;
            }
            else{
                right_capacity = ((_el - _b) * 10) - (_bi - *_b + 1);
                if(s < right_capacity){
                    uninitialized_fill(_a, end(), begin() + s, v);
                    _size = s;
                }
                else{
                    if((s - (right_capacity)) < (_outer_size * 10)){
                        my_deque x((_outer_size * 10) * 3);
                        swap(x);
                        size_type new_bi = ((2 * (x._outer_size * 10)) - right_capacity);
                        uninitialized_copy(_a, x.begin(), x.end(), begin() + new_bi);
                        _size = x.size();

                        _b = _bl + ((x._outer_size) + (x._b - x._bl));
                        _bi = *_b + (x._bi - *(x._b));

                        resize(s , v);
                    }
                    else{
                        size_type new_size = ((s / 10) + 1) * 10;

                        my_deque x((_outer_size * 10) + (2 * new_size));
                        swap(x);
                        size_type new_bi = (new_size + (x._outer_size * 10) - right_capacity);
                        uninitialized_copy(_a, x.begin(), x.end(), begin() + new_bi);
                        _size = x.size();

                        _b = _bl + ((new_size / 10) + (x._b - x._bl));
                        _bi = *_b + (x._bi - *(x._b));

                        resize(s, v);
                    }
                }
            }

            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            return _size;}

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (my_deque& that) {
            if(_a == that._a){
                std::swap(_b, that._b);
                std::swap(_bl, that._bl);
                std::swap(_el, that._el);
                std::swap(_bi, that._bi);
                std::swap(_size, that._size);
                std::swap(_outer_size, that._outer_size);
            }
            else{
                my_deque x(*this);
                *this = that;
                that = x;
            }
            assert(valid());}};

#endif // Deque_h
