#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP
#include <cmath>
#include <stdexcept>
#include <limits>
#include "vector_iterator.hpp"
#include "../reverse_iterator.hpp"

namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector{
    private:
        template<bool, typename _Tp = void>
        struct my_enable_if
        { };
        template<typename _Tp>
        struct my_enable_if<true, _Tp>
        { typedef _Tp type; };
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef vector_iterator<value_type> iterator;
        typedef const_vector_iterator<value_type> const_iterator;
        typedef my_reverse_iterator<iterator> reverse_iterator;
        typedef my_reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

        //default (1)
        explicit vector(const allocator_type& alloc = allocator_type()) : allocator(alloc) {
            start = NULL;
            _size = 0;
            _capacity = 0;
        };
        //fill (2)
        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type()) : allocator(alloc){
            start = allocator.allocate(n);
            _size = n;
            _capacity = n;
            for (size_type  i = 0; i < n; ++i)
                allocator.construct(&start[i], val);
        };
//        //range (3)
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type(), typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) : allocator(alloc) {
            start = NULL;
            this->_size = 0;
            this->_capacity = 0;
            assign(first, last);
        };
//        //copy (4)
        vector (const vector& x) {
            start = NULL;
            this->_size = 0;
            this->_capacity = 0;
            *this = x;
        };

        ~vector() {
            for (size_type i = 0; i < this->_size; ++i)
                allocator.destroy(&this->start[i]);
            if (this->start)
                allocator.deallocate(this->start, this->_capacity);
        }

        vector& operator= (const vector& x) {
            if (this == &x)
                return *this;
            for (size_type i = 0; i < this->_size; ++i)
                allocator.destroy(&this->start[i]);
            if (this->start)
                allocator.deallocate(this->start, this->_capacity);
            start = allocator.allocate(x.capacity());
            this->_capacity = x._capacity;
            this->_size = x._size;
            for (size_type i = 0; i < this->_capacity; ++i)
                start[i] = x[i];
            return *this;
        };

        //ITERATORS
        iterator begin() {
            return iterator (this->start);
        }

        iterator end() {
            return iterator(this->start + _size);
        }

        const_iterator begin() const {
            const_iterator i(this->start);
            return i;
        }

        const_iterator end() const {
            const_iterator i(this->start + _size);
            return i;
        }
        //REVERSE ITERATORS
        reverse_iterator rbegin() {
            reverse_iterator i(this->end());
            return i;
        }

        reverse_iterator rend() {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator rbegin() const {
            const_reverse_iterator i(this->end());
            return i;
        }

        const_reverse_iterator rend() const {
            const_reverse_iterator i(this->begin());
            return i;
        }

        size_type size() const {
            return this->_size;
        }

        size_type max_size() const {
            size_type res;
            res = (pow(2,64)/sizeof(value_type)/2); // /2 linux problem
            res -= 1;
            return res;
        }

        void resize (size_type n, value_type val = value_type()) {
            if (n < _size)
                erase(this->begin() + n, this->end());
            if (n > _size)
                insert(this->end(), n - _size, val);
        };

        size_type capacity() const {
            return this->_capacity;
        }

        bool empty() const {
            return (_size == 0);
        }

        void reserve(size_type n) {
            if (n > this->max_size())
                throw std::length_error("Capacity for reserve is too big");
            if (n > _capacity){
                value_type *temp = allocator.allocate(n);
                for (size_type i = 0; i < n; i++){
                    if (i < _size)
                        allocator.construct(&temp[i], start[i]);
                    else
                        allocator.construct(&temp[i], value_type());
                }
                for (size_type i = 0; i < _size; ++i)
                    allocator.destroy(&start[i]);
                allocator.deallocate(start, _capacity);
                start = temp;
                temp = NULL;
                _capacity = n;
            }
        }

        reference operator[] (size_type n) {
            return *(start + n);
        }

        const_reference  operator[] (size_type n) const {
            return *(start + n);
        }

        reference at (size_type n) {
            if (n >= this->_size)
                throw std::out_of_range("Out of range: n >= this->size()");
            else
                return this->start[n];
        };

        const_reference at (size_type n) const {
            if (n >= this->_size)
                throw std::out_of_range("Out of range: n >= this->size()");
            else
                return this->start[n];
        };

        reference front() {
            return this->start[0];
        }

        const_reference front() const {
            return this->start[0];
        }

        reference back() {
            return this->start[this->_size - 1];
        }

        const_reference back() const {
            return this->start[this->_size - 1];
        }

        //range (1)
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) {
            for (size_type i = 0; i < _size; ++i)
                allocator.destroy(&start[i]);
            _size = 0;
            size_type ins_size = find_iter_interval(first, last);
            size_type i = 0;
            if (ins_size > _capacity)
                this->reserve(ins_size);
            while (first != last) {
                start[i++] = *first;
                first++;
                _size++;
            }
        };

        //fill (2)

        void assign (size_type n, const value_type& val) {
            for (size_type i = 0; i < _size; ++i)
                allocator.destroy(&start[i]);
            if (n <= _capacity){
                for (size_type i = 0; i < n; ++i)
                    start[i] = val;
                _size = n;
            }
            else
            {
                allocator.deallocate(start, _capacity);
                _capacity *= 2;
                start = allocator.allocate(_capacity);
                for (size_type i = 0; i < n; ++i)
                    start[i] = val;
                _size = n;
            }
        };

        void push_back (const value_type& val) {
            if (_capacity == 0)
                reserve(2);
            if (_size == _capacity)
                reserve(_capacity * 2);
            allocator.construct(&start[_size], val);
            _size++;
        };

        void pop_back(){
            allocator.destroy(&start[_size - 1]);
            _size--;
        }
        //single element (1)
        iterator insert (iterator position, const value_type& val) {
            if (_size + 1 > _capacity)
                position = reallocation_with_saved_iterator(position, _capacity * 2);
            for (size_type i = _size; i > 0; i--) {
                if (position.operator->() == &start[i]) {
                    allocator.destroy(&start[i]);
                    allocator.construct(&start[i], val);
                    break;
                }
                start[i] = start[i - 1];
            }
            _size++;
            return position;
        };
        //fill (2)
        void insert (iterator position, size_type n, const value_type& val){
            if (_size + n > _capacity)
                position = reallocation_with_saved_iterator(position, _capacity * 2);
            iterator move = this->end();
            while (move != position)
            {
                *(move.operator->() + n) = *move;
                move--;
            }
            *(move.operator->() + n) = *move;
            for (size_type i = 0; i < n; ++i)
            {
                *move = val;
                move++;
            }
            _size += n;
        }
        //range (3)
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0){
            size_type ins_size = find_iter_interval(first, last);
            if (_size + ins_size > _capacity)
            {
                difference_type offset = position.operator->() - this->begin().operator->();
                value_type *temp;
                value_type *saving_start_for_deallocation;
                size_type prev_cap = _capacity;
                if (_size + ins_size <= _capacity * 2) {
                    temp = allocator.allocate(_capacity * 2);
                    _capacity *= 2;
                }
                else {
                    temp = allocator.allocate(_size + ins_size);
                    _capacity = _size + ins_size;
                }
                for (size_type i = 0; i < _size; ++i)
                    temp[i] = start[i];
                for (size_type i = _size; i < _capacity; i++)
                    allocator.construct(&temp[i], value_type());
                saving_start_for_deallocation = start;
                start = temp;
                position = this->begin() + offset;
                while (first != last) {
                    insert(position, *first);
                    position++;
                    first++;
                }
                for (size_type i = 0; i < _size; ++i)
                    allocator.destroy(&saving_start_for_deallocation[i]);
                allocator.deallocate(saving_start_for_deallocation, prev_cap);
            }
            else {
                while (first != last) {
                    insert(position, *first);
                    position++;
                    first++;
                }
            }
        };

        iterator erase (iterator position) {
            allocator.destroy(position.operator->());
            _size--;
            iterator move = position;
            if (move != this->end() - 1){
                while (move != this->end()) {
                    *move = *(move.operator->() + 1);
                    move++;
                }
            }
            return position;
        };

        iterator erase (iterator first, iterator last) {
            size_type erase_size = find_iter_interval(first, last);
            iterator save_end = this->end();
            while (first != last) {
                allocator.destroy(first.operator->());
                _size--;
                first++;
            }
            while (first != save_end){
                *(first.operator->() - erase_size) = *first;
                first++;
            }
            return last;
        };

        void swap (vector& x){
            value_type *temp_start = x.start;
            Alloc temp_allocator = x.allocator;
            size_type temp_size = x._size;
            size_type temp_capacity = x._capacity;
            x.start = this->start;
            x._size = this->_size;
            x._capacity = this->_capacity;
            x.allocator = this->allocator;
            this->start = temp_start;
            this->_size = temp_size;
            this->_capacity = temp_capacity;
            this->allocator = temp_allocator;
        };

        void clear() {
            if (_size != 0)
            {
                iterator pos = this->begin();
                while (pos != this->end()) {
                    allocator.destroy(pos.operator->());
                    pos++;
                }
                _size=0;
            }
        }


        allocator_type get_allocator() const{
            return allocator;
        }

    private:
        Alloc allocator;
        value_type *start;
        size_type _size;
        size_type _capacity;
        iterator reallocation_with_saved_iterator(iterator position, size_type new_capacity){
            difference_type offset = position.operator->() - this->begin().operator->();
            this->reserve(new_capacity);
            position = this->begin() + offset;
            return position;
        }
        template <class InputIterator>
        size_type find_iter_interval (InputIterator first, InputIterator last){
            InputIterator temp = first;
            size_type count = 0;
            while (temp != last){
                temp++;
                count++;
            }
            return count;
        }
    };

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        x.swap(y);
    }

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return false;
        else{
            typename vector<T,Alloc>::const_iterator lhs_start = lhs.begin();
            typename vector<T,Alloc>::const_iterator rhs_start = rhs.begin();
            while (lhs_start != lhs.end()){
                if (*lhs_start != *rhs_start)
                    return false;
                else{
                    lhs_start++;
                    rhs_start++;
                }
            }
            return true;
        }
    };

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename vector<T,Alloc>::const_iterator lhs_start = lhs.begin();
        typename vector<T,Alloc>::const_iterator rhs_start = rhs.begin();
        while (lhs_start != lhs.end()){
            if (rhs_start == rhs.end() || *lhs_start > *rhs_start)
                return false;
            if (*lhs_start < *rhs_start)
                return true;
            lhs_start++;
            rhs_start++;
        }
        return (lhs_start == lhs.end());
    };

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return !(lhs == rhs);
    };

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return rhs < lhs;
    };

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return !(rhs < lhs);
    };

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return !(lhs < rhs);
    };
}

#endif //CONTAINERS_VECTOR_HPP
