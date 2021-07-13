#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP
#include "../vector/vector.hpp"

namespace ft {
    template <class T, class Container = vector<T> >
    class stack {
    public:
        typedef T           value_type;
        typedef Container   container_type;
        typedef size_t      size_type;

        explicit stack(const container_type& ctnr = container_type()) : arr(ctnr) {
        }

        bool empty() const{
            return arr.empty();
        };

        size_type size() const {
            return arr.size();
        }

        value_type& top() {
            return arr.back();
        }

        const value_type& top() const {
//            const value_type top_elem = arr.back();
            return (arr.back());
        }

        void push (const value_type& val) {
            arr.push_back(val);
        }

        void pop() {
            arr.pop_back();
        }

        template<class T1, class Container1>
        friend
        bool operator== (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

        template<class T1, class Container1>
        friend
        bool operator<  (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

    protected:
        Container arr;
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.arr == rhs.arr;
    };
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs == rhs);
    };
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.arr < rhs.arr;
    };
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(rhs < lhs);
    };
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return rhs < lhs;
    };
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs < rhs);
    };
}

#endif //CONTAINERS_STACK_HPP
