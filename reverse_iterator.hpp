#ifndef NEW_CONTAINERS_REVERSE_ITERATOR_HPP
#define NEW_CONTAINERS_REVERSE_ITERATOR_HPP

namespace ft {

    template<typename _Category, typename _Tp, typename _Distance = std::ptrdiff_t,
            typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
        typedef _Category  iterator_category;
        typedef _Tp        value_type;
        typedef _Distance  difference_type;
        typedef _Pointer   pointer;
        typedef _Reference reference;
    };

    template<typename _Iterator>
    struct my_iterator_traits
    {
        typedef typename _Iterator::iterator_category iterator_category;
        typedef typename _Iterator::value_type        value_type;
        typedef typename _Iterator::difference_type   difference_type;
        typedef typename _Iterator::pointer           pointer;
        typedef typename _Iterator::reference         reference;
    };



    template <typename _iterator>
    class my_reverse_iterator : iterator<  typename my_iterator_traits<_iterator>::iterator_category,
                                        typename my_iterator_traits<_iterator>::value_type,
                                        typename my_iterator_traits<_iterator>::difference_type,
                                        typename my_iterator_traits<_iterator>::pointer,
                                        typename my_iterator_traits<_iterator>::reference>
    {
    public:
        _iterator current;

        typedef my_iterator_traits<_iterator>		traits;

        typedef _iterator					iterator_type;
        typedef typename traits::difference_type	difference_type;
        typedef typename traits::pointer		pointer;
        typedef typename traits::reference		reference;

        my_reverse_iterator() : current() {}
        explicit my_reverse_iterator(iterator_type it) : current(it) {}

        template<class Iter>
                my_reverse_iterator(const my_reverse_iterator<Iter>& rev_it) : current(rev_it.current) {}

        iterator_type base() const { return current; }

        reference operator*() const {
            iterator_type tmp = current;
            return *(--tmp);
        }

        my_reverse_iterator operator+(difference_type n) const { return my_reverse_iterator(current - n); }

        my_reverse_iterator& operator++() {
            --current;
            return *this;
        }

        my_reverse_iterator operator++(int) {
            my_reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        my_reverse_iterator& operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        my_reverse_iterator operator-(difference_type n) const { return my_reverse_iterator(current + n); }

        my_reverse_iterator& operator--() {
            ++current;
            return *this;
        }

        my_reverse_iterator operator--(int) {
            my_reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }

        my_reverse_iterator& operator-=(difference_type n) {
            current += n;
            return *this;
        }
        
        pointer operator->() const { return &(operator*());}

        reference operator[](difference_type n) const {return *(*this + n); }


    };
    template <class Iterator>
    bool operator== (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return lhs.base() == rhs.base();
    };

    template <class Iterator>
    bool operator!= (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return !(lhs == rhs);
    };

    template <class Iterator>
    bool operator< (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return rhs.base() < lhs.base();
    };

    template <class Iterator>
    bool operator<= (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return !(rhs < lhs);
    };

    template <class Iterator>
    bool operator> (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return (rhs < lhs);
    };

    template <class Iterator>
    bool operator>= (const my_reverse_iterator<Iterator>& lhs, const my_reverse_iterator<Iterator>& rhs){
        return !(lhs < rhs);
    };
    //Relation opertors for my_reverse_iterator and const my_reverse_iterator
    template <class IteratorL, class IteratorR>
    bool operator==(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() == rhs.base();
    }

    template <class IteratorL, class IteratorR>
    bool operator<(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() > rhs.base();
    }

    template <class IteratorL, class IteratorR>
    bool operator!=(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() != rhs.base();
    }

    template <class IteratorL, class IteratorR>
    bool operator>(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() < rhs.base();
    }

    template <class IteratorL, class IteratorR>
    bool operator<=(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() >= rhs.base();
    }

    template <class IteratorL, class IteratorR>
    bool operator>=(const my_reverse_iterator<IteratorL>& lhs, const my_reverse_iterator<IteratorR>& rhs){
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    my_reverse_iterator<Iterator> operator+ (typename my_reverse_iterator<Iterator>::difference_type n, const my_reverse_iterator<Iterator> rev_it){
        return my_reverse_iterator<Iterator>(rev_it.base() - n);
    }

    template <class Iterator>
    typename my_reverse_iterator<Iterator>::difference_type operator-( const my_reverse_iterator<Iterator>&lhs, const my_reverse_iterator<Iterator>& rhs){
        return (rhs.base() - lhs.base());
    }
}

#endif //NEW_CONTAINERS_REVERSE_ITERATOR_HPP
