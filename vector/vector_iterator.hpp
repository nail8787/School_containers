#ifndef NEW_CONTAINERS_VECTOR_ITERATOR_HPP
#define NEW_CONTAINERS_VECTOR_ITERATOR_HPP

#include <cstddef>
#include "../iterator_tags.hpp"

namespace ft {
    template <typename T>
    class vector_iterator
    {
    public:
        typedef vector_iterator<T> _self;
        typedef T         value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T*   pointer;
        typedef T& reference;
        typedef random_access_iterator_tag  iterator_category;

        pointer _point;

        vector_iterator() : _point(NULL) {};

        vector_iterator(value_type *val) : _point(val) {}

        vector_iterator(_self const &src) { *this = src;}

        _self &operator=(_self const &src) {
            if (this == &src)
                return *this;
            this->_point = src._point;
            return *this;
        }

        reference operator*() const { return *_point; };
        pointer operator->() const { return _point; }

        _self operator++() {
            _point++;
            return *this;
        };

        _self operator--() {
            _point--;
            return *this;
        };

        _self operator++(int) {
            _point++;
            return *this;
        };

        _self operator--(int) {
            _point--;
            return *this;
        };

        _self operator+=(int val) {
            _point += val;
            return *this;
        }

        _self operator-=(int val) {
            _point -= val;
            return *this;
        }

        _self operator+(difference_type val) {
            _point += val;
            return *this;
        }

        _self operator-(difference_type val) {
            _point -= val;
            return *this;
        }

        reference operator[](difference_type n) const { return _point[n]; }

        bool operator!=(_self const &end) const { return _point != end._point; }
        bool operator==(_self const &end) const { return _point == end._point; }
        bool operator<(_self const &end) const { return _point < end._point; }
        bool operator>(_self const &end) const { return _point > end._point; }
        bool operator<=(_self const &end) const { return _point <= end._point; }
        bool operator>=(_self const &end) const { return _point >= end._point; }
    };

    template <typename IteratorL, typename IteratorR>
    bool operator!=(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() != rhs.operator->(); }
    template <typename IteratorL, typename IteratorR>
    bool operator==(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() == rhs.operator->(); }
    template <typename IteratorL, typename IteratorR>
    bool operator<(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() < rhs.operator->(); }
    template <typename IteratorL, typename IteratorR>
    bool operator>(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() > rhs.operator->(); }
    template <typename IteratorL, typename IteratorR>
    bool operator<=(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() <= rhs.operator->(); }
    template <typename IteratorL, typename IteratorR>
    bool operator>=(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator->() >= rhs.operator->(); }

    template <class T>
    class const_vector_iterator
    {

    public:
        typedef const_vector_iterator<T> _self;
        typedef vector_iterator<T> iterator;
        typedef T         value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T*   pointer;
        typedef const T& reference;
        typedef random_access_iterator_tag  iterator_category;
        
        const value_type *_point;
        
        const_vector_iterator() : _point(NULL) {}

        const_vector_iterator(value_type *val) : _point(val) {}

        const_vector_iterator(_self const &src) {
            *this = src;
        }
        
        const_vector_iterator(iterator const &src) : _point(src._point) {}

        _self &operator=(_self const &src)
        {
            if (this == &src)
                return *this;
            this->_point = src._point;
            return *this;
        }

        reference operator*() const { return *_point; };
        pointer operator->() const { return _point; }

        _self operator++() {
            _point++;
            return *this;
        };

        _self operator--() {
            _point--;
            return *this;
        };

        _self operator++(int) {
            _point++;
            return *this;
        };

        _self operator--(int) {
            _point--;
            return *this;
        };

        _self operator+=(int val) {
            _point += val;
            return *this;
        }

        _self operator-=(int val) {
            _point -= val;
            return *this;
        }

        _self operator+(difference_type val) {
            _point += val;
            return *this;
        }

        _self operator-(difference_type val) {
            _point -= val;
            return *this;
        }

        reference operator[](difference_type n) const { return _point[n]; }

        bool operator!=(_self const &end) const { return _point != end._point; }
        bool operator==(_self const &end) const { return _point == end._point; }
        bool operator<(_self const &end) const { return _point < end._point; }
        bool operator>(_self const &end) const { return _point > end._point; }
        bool operator<=(_self const &end) const { return _point <= end._point; }
        bool operator>=(_self const &end) const { return _point >= end._point; }
    };
}


#endif //NEW_CONTAINERS_VECTOR_ITERATOR_HPP
