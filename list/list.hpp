#ifndef LIST_HPP
#define LIST_HPP
#include <memory>
#include <cstddef>
#include <iterator>
#include <limits>

namespace ft
{
    template<typename T, class Alloc = std::allocator <T> >
    class list
    {
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
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        struct Node
        {
            value_type data;
            Node *next;
            Node *prev;
        };

        typedef typename Alloc::template rebind<Node>::other _Node_Alloc;

        explicit list (const allocator_type& alloc = allocator_type()) : def_alloc(alloc)
        {
            mem = _Node_Alloc();
            this->head = mem.allocate(1);
            this->tail = mem.allocate(1);
            _size = 0;
            head->next = tail;
            head->prev = NULL;
            def_alloc.construct(&head->data, value_type());
            tail->prev = head;
            tail->next = NULL;
            def_alloc.construct(&tail->data, value_type());
        };

        explicit list (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type()) : def_alloc(alloc)
        {
            mem = _Node_Alloc();
            this->head = mem.allocate(1);
            this->tail = mem.allocate(1);
            _size = 0;
            head->next = tail;
            head->prev = NULL;
            def_alloc.construct(&head->data, value_type());
            tail->prev = head;
            tail->next = NULL;
            def_alloc.construct(&tail->data, value_type());
            for (size_t i = 0; i < n; ++i)
                push_back(val);
        };

        template <class InputIterator>
        list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
              typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0) : def_alloc(alloc) {
            mem = _Node_Alloc();
            this->head = mem.allocate(1);
            this->tail = mem.allocate(1);
            _size = 0;
            head->next = tail;
            head->prev = NULL;
            def_alloc.construct(&head->data, value_type());
            tail->prev = head;
            tail->next = NULL;
            def_alloc.construct(&tail->data, value_type());
            while (first != last) {
                push_back(*first);
                first++;
            }
        }

        list(list<T> const &src) : def_alloc(src.def_alloc), mem(src.mem){
            this->head = mem.allocate(1);
            this->tail = mem.allocate(1);
            _size = 0;
            head->next = tail;
            head->prev = NULL;
            def_alloc.construct(&head->data, value_type());
            tail->prev = head;
            tail->next = NULL;
            def_alloc.construct(&tail->data, value_type());
            *this = src;
        }

        ~list()
        {
            while (this->head != this->tail->prev)
                pop_front();
            def_alloc.destroy(&head->data);
            def_alloc.destroy(&tail->data);
            head->next = NULL;
            head->prev = NULL;
            mem.deallocate(tail, 1);
            mem.deallocate(head, 1);
        };

        list& operator= (const list& x){
            if (this == &x)
                return *this;
            insert(this->begin(), x.begin(), x.end());
            return *this;
        };

        class iterator
        {
        private:
            Node *_point;
        public:
            iterator() : _point(NULL)
            {};

            iterator(Node *val) : _point(val)
            {}

            iterator(iterator const &src) {
                *this = src;
            }

            iterator &operator=(iterator const &src)
            {
                if (this == &src)
                    return *this;
                this->_point = src._point;
                return *this;
            }

            T &operator*() const
            {
                return this->_point->data;
            };

            iterator operator++()
            {
                _point = _point->next;
                return *this;
            };

            iterator operator--()
            {
                _point = _point->prev;
                return *this;
            };

            iterator operator++(int)
            {
                _point = _point->next;
                return *this;
            };

            iterator operator--(int)
            {
                _point = _point->prev;
                return *this;
            };

            Node *operator->()
            {
                return _point;
            }

            bool operator!=(iterator const &end) const
            {
                return _point != end._point;
            }

            bool operator==(iterator const &end) const
            {
                return _point == end._point;
            }
        };

        class const_iterator
        {
        private:
            const Node *_point;
        public:
            const_iterator() : _point(NULL)
            {};

            const_iterator(Node *val) : _point(val)
            {}

            const_iterator(const_iterator const &src) {
                *this = src;
            }

            const_iterator &operator=(const_iterator const &src)
            {
                if (this == &src)
                    return *this;
                this->_point = src._point;
                return *this;
            }

            const T &operator*() const
            {
                return this->_point->data;
            };

            const_iterator operator++()
            {
                _point = _point->next;
                return *this;
            };

            const_iterator operator--()
            {
                _point = _point->prev;
                return *this;
            };

            const_iterator operator++(int)
            {
                _point = _point->next;
                return *this;
            };

            const_iterator operator--(int)
            {
                _point = _point->prev;
                return *this;
            };

            Node *operator->()
            {
                return _point;
            }

            bool operator!=(const_iterator const &end) const
            {
                return _point != end._point;
            }

            bool operator==(const_iterator const &end) const
            {
                return _point == end._point;
            }
        };

        class reverse_iterator
        {
        private:
            Node *_point;
        public:
            reverse_iterator() : _point(NULL)
            {};

            reverse_iterator(Node *val) : _point(val)
            {}

            reverse_iterator(reverse_iterator const &src) {
                *this = src;
            }

            reverse_iterator &operator=(reverse_iterator const &src)
            {
                if (this == &src)
                    return *this;
                this->_point = src._point;
                return *this;
            }

            T &operator*() const
            {
                return this->_point->data;
            };

            reverse_iterator operator++()
            {
                _point = _point->prev;
                return *this;
            };

            reverse_iterator operator--()
            {
                _point = _point->next;
                return *this;
            };

            reverse_iterator operator++(int)
            {
                _point = _point->prev;
                return *this;
            };

            reverse_iterator operator--(int)
            {
                _point = _point->next;
                return *this;
            };

            Node *operator->()
            {
                return _point;
            }

            bool operator!=(reverse_iterator const &end) const
            {
                return _point != end._point;
            }

            bool operator==(reverse_iterator const &end) const
            {
                return _point == end._point;
            }
        };

        class const_reverse_iterator
        {
        private:
            const Node *_point;
        public:
            const_reverse_iterator() : _point(NULL)
            {};

            const_reverse_iterator(Node *val) : _point(val)
            {}

            const_reverse_iterator(const_reverse_iterator const &src) {
                *this = src;
            }

            const_reverse_iterator &operator=(const_reverse_iterator const &src)
            {
                if (this == &src)
                    return *this;
                this->_point = src._point;
                return *this;
            }

            const T &operator*() const
            {
                return this->_point->data;
            };

            const_reverse_iterator operator++()
            {
                _point = _point->prev;
                return *this;
            };

            const_reverse_iterator operator--()
            {
                _point = _point->next;
                return *this;
            };

            const_reverse_iterator operator++(int)
            {
                _point = _point->prev;
                return *this;
            };

            const_reverse_iterator operator--(int)
            {
                _point = _point->next;
                return *this;
            };

            Node *operator->()
            {
                return _point;
            }

            bool operator!=(const_reverse_iterator const &end) const
            {
                return _point != end._point;
            }

            bool operator==(const_reverse_iterator const &end) const
            {
                return _point == end._point;
            }
        };

        iterator begin(){
            iterator begin(this->head->next);
            return begin;
        };

        const_iterator begin() const {
            const_iterator begin(this->head->next);
            return begin;
        }

        iterator end()
        {
            iterator end(this->tail);
            return end;
        }

        const_iterator end() const
        {
            const_iterator end(this->tail);
            return end;
        }

        reverse_iterator rbegin(){
            reverse_iterator begin(this->tail->prev);
            return begin;
        };

        const_reverse_iterator rbegin() const {
            const_reverse_iterator begin(this->tail->prev);
            return begin;
        }

        reverse_iterator rend()
        {
            reverse_iterator end(this->head);
            return end;
        }

        const_reverse_iterator rend() const
        {
            const_reverse_iterator end(this->head);
            return end;
        }

        bool empty() const
        {
            return (_size == 0);
        }

        size_type size() const{
            return this->_size;
        }

        size_type max_size() const {
            return std::numeric_limits<size_t>::max()/sizeof(Node)/2; // /2 для линукса хз почему -.-
        }

        T &front(){
            return this->head->next->data;
        };

        const T&front() const {
            return this->head->next->data;
        }

        T &back(){
            return this->tail->prev->data;
        }

        const T &back() const {
            return this->tail->prev->data;
        }

        void assign(size_t n, T const &val)
        {
            this->clear();
            this->resize(n, val);
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last, typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
        {
            this->clear();
            insert(this->begin(), first, last);
        }

        void push_front(const value_type&val)
        {
            Node *temp;

            temp = mem.allocate(1);
            head->next->prev = temp;
            temp->next = head->next;
            temp->prev = head;
            head->next = temp;
            def_alloc.construct(&temp->data, val);
            _size++;
        };

        void pop_front()
        {
            Node *temp;

            temp = head->next;
            head->next = temp->next;
            temp->next->prev = head;
            temp->prev = NULL;
            temp->next = NULL;
            def_alloc.destroy(&temp->data);
            mem.deallocate(temp, 1);
            _size--;
        };

        void push_back(const value_type&val)
        {
            Node *temp;

            temp = mem.allocate(1);
            temp->prev = tail->prev;
            tail->prev->next = temp;
            temp->next = tail;
            tail->prev = temp;
            def_alloc.construct(&temp->data, val);
            _size++;
        };

        void pop_back()
        {
            Node *temp;

            temp = tail->prev;
            tail->prev = temp->prev;
            temp->prev->next = tail;
            temp->next = NULL;
            temp->prev = NULL;
            def_alloc.destroy(&temp->data);
            mem.deallocate(temp, 1);
            _size--;
        };

        iterator insert(iterator position, const value_type&val)
        {
            Node *temp;

            temp = mem.allocate(1);
            temp->data = val;
            position.operator->()->prev->next = temp;
            temp->prev = position.operator->()->prev;
            position.operator->()->prev = temp;
            temp->next = position.operator->();
            _size++;
            --position;
            return position;
        }

        void insert(iterator position, size_t n, const value_type&val)
        {
            for (size_t i = 0; i < n; ++i)
                position = insert(position, val);
        }

        template<class InputIterator>
        void
        insert(iterator position, InputIterator first, InputIterator last, typename my_enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = 0)
        {
            while (first != last){
                insert(position, *first);
                first++;
            }
        }

        iterator erase(iterator position)
        {
            Node *prevN;
            Node *nextN;
            iterator temp = position.operator->()->next;

            nextN = position.operator->()->next;
            prevN = position.operator->()->prev;
            nextN->prev = prevN;
            prevN->next = nextN;
            position.operator->()->data = 0;
            position.operator->()->prev = NULL;
            position.operator->()->next = NULL;
            mem.deallocate(position.operator->(), 1);
            --_size;
            return temp;
        }

        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                first = erase(first);
            return last;
        }

        void swap(list &x)
        {
            Node *temp_head;
            Node *temp_tail;
            size_t temp_size;

            temp_head = this->head;
            temp_tail = this->tail;
            temp_size = this->_size;
            this->head = x.head;
            this->tail = x.tail;
            this->_size = x._size;
            x.head = temp_head;
            x.tail = temp_tail;
            x._size = temp_size;
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n == _size)
                return;
            else if (n < _size)
            {
                while (_size != n)
                    pop_back();
            }
            else
            {
                while (_size != n)
                    push_back(val);
            }
        }

        void clear()
        {
            erase(this->begin(), this->end());
        }

        void splice (iterator position, list& x, iterator i) {
            i.operator->()->next->prev = i.operator->()->prev;
            i.operator->()->prev->next = i.operator->()->next;
            x._size--;
            i.operator->()->prev = position.operator->()->prev;
            position.operator->()->prev->next = i.operator->();
            position.operator->()->prev = i.operator->();
            i.operator->()->next = position.operator->();
            _size++;
        }

        void splice (iterator position, list& x, iterator first, iterator last) {
            iterator temp_it = first;
            size_t count = 0;
            while (temp_it != last)
            {
                count++;
                ++temp_it;
            }
            Node *temp = first.operator->()->prev;
            --last;
            temp->next = last.operator->()->next;
            position.operator->()->prev->next = first.operator->();
            last.operator->()->next->prev = temp;
            first.operator->()->prev = position.operator->()->prev;
            last.operator->()->next = position.operator->();
            position.operator->()->prev = last.operator->();
            x._size -= count;
            _size += count;
        }

        void splice (iterator position, list& x) {
            splice(position, x, x.begin(), x.end()); //troubles with size for now
        };

        void remove (const value_type &val) {
            iterator start = this->begin();
            while (start != this->end())
            {
                if (*start == val)
                    start = erase(start);
                else
                    ++start;
            }
        }

        template <class Predicate>
        void remove_if (Predicate pred) {
            iterator start = this->begin();
            while (start != this->end())
            {
                if (pred(*start))
                    start = erase(start);
                else
                    ++start;
            }
        }

        void unique(){
            iterator pos = ++(this->begin());
            iterator before;
            while (pos != this->end())
            {
                before = --pos;
                ++pos;
                if (*pos == *before)
                    pos = erase(pos);
                else
                    ++pos;
            }
        }

        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred) {

            iterator pos = ++(this->begin());
            iterator before;
            while (pos != this->end())
            {
                before = --pos;
                ++pos;
                if (binary_pred(*pos, *before))
                    pos = erase(pos);
                else
                    ++pos;
            }
        }

        void  merge(list& x) {
            iterator start = x.begin();
            iterator pos = this->begin();
            while (start != x.end()){
                if (*start < *pos || pos == this->end()){
                    splice(pos, x, start);
                    start = x.begin();
                }
                else if (pos != this->end())
                    ++pos;
            }
        }

        template <class Compare>
         void merge (list& x, Compare comp) {
            iterator start = x.begin();
            iterator pos = this->begin();
            while (start != x.end()){
                if (comp(*start, *pos) || pos == this->end()){
                    splice(pos, x, start);
                    start = x.begin();
                }
                else if (pos != this->end())
                    pos++;
            }
        };

        void sort() {
            for (iterator pos = this->begin(); pos != this->end() && pos.operator->()->next->next != NULL; ++pos)
            {
                if (*pos > pos.operator->()->next->data)
                    swap(pos.operator->(), pos.operator->()->next);
                else
                    ++pos;
            }
            iterator pos = this->begin();
            size_t itersize;
            for (itersize = 2; itersize < _size; itersize *= 2 ){
                iterator start = this->begin();
                size_t count = 0;
                while (count < _size/(itersize * 2))
                {
                    merge(start, pos = move_iterator(itersize, start), itersize);
                    start = this->begin();
                    count++;
                    start = move_iterator(count * (itersize * 2), start);
                }
                if (itersize < find_size_of_sublist(start))
                {
                    pos = move_iterator(itersize, start); //передал так на линуксе, так не отрабатывало нормально в аргументах фукнции merge
                    count = find_size_of_sublist(pos); //передал так на линуксе, так не отрабатывало нормально в аргументах фукнции merge
                    merge(start, pos , count);
                }
            }
        }
        template <class Compare>
         void sort (Compare comp) {
            for (iterator pos = this->begin(); pos != this->end() && pos.operator->()->next->next != NULL; ++pos)
            {
                if (comp(pos.operator->()->next->data, *pos))
                    swap(pos.operator->(), pos.operator->()->next);
                else
                    ++pos;
            }
            iterator pos = this->begin();
            size_t itersize;
            for (itersize = 2; itersize < _size; itersize *= 2 ){
                iterator start = this->begin();
                size_t count = 0;
                while (count < _size/(itersize * 2))
                {
                    merge(start, pos = move_iterator(itersize, start), itersize);
                    start = this->begin();
                    count++;
                    start = move_iterator(count * (itersize * 2), start);
                }
                if (itersize < find_size_of_sublist(start))
                {
                    pos = move_iterator(itersize, start); //передал так на линуксе, так не отрабатывало нормально в аргументах фукнции merge
                    count = find_size_of_sublist(pos); //передал так на линуксе, так не отрабатывало нормально в аргументах фукнции merge
                    merge(start, pos , count);
                }
            }
        }

        void reverse() {
            unsigned int counter = 0;
            iterator first = this->begin();
            iterator last = --(this->end());
            iterator temp;
            while (counter != (_size / 2))
            {
                temp = first;
                swap(first.operator->(), last.operator->());
                first = last;
                last = temp;
                ++first;
                --last;
                counter++;
            }
        }

        allocator_type get_allocator() const{
            return def_alloc;
        }

    private:
        Node *head;
        Node *tail;
        size_type _size;
        Alloc def_alloc;
        _Node_Alloc mem;

        size_t find_size_of_sublist(iterator start){
            size_t count;
            for (count = 0; start != this->end(); ++count)
                ++start;
            return count;
        }

        void swap(Node *first, Node *second){
            if (first->next == second)
            {
                first->next = second->next;
                second->prev = first->prev;
                first->prev->next = second;
                second->next->prev = first;
                first->prev = second;
                second->next = first;
            }
            else {
                Node *temp_first_next = first->next;
                Node *temp_first_prev = first->prev;
                first->next->prev = second;
                first->prev->next = second;
                second->next->prev = first;
                second->prev->next = first;
                first->next = second->next;
                first->prev = second->prev;
                second->next = temp_first_next;
                second->prev = temp_first_prev;
            }
        }

        iterator move_iterator (size_t n, iterator iter)
        {
            for (size_t count = 0; count < n; ++count)
                ++iter;
            return iter;
        }

        void merge(iterator first, iterator second, size_t size) {
            size_t count_first = 0;
            size_t count_second = 0;
            iterator temp;
            size_t first_size = 0;

            temp = first;
            while (temp != second)
            {
                ++temp;
                ++first_size;
            }
            while (count_second < size && first != this->end())
            {
                if (*second < *first)
                {
                    temp = second.operator->()->next;
                    splice(first, *this, second);
                    second = temp;
                    count_second++;
                }
                else if (count_first < first_size)
                {
                    ++count_first;
                    ++first;
                }
                else if (count_first == first_size)
                {
                    ++second;
                    count_second++;
                }
            }
        }
    };

    template <class T, class Alloc>
    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        if (&lhs == &rhs)
            return true;
        if (lhs.size() != rhs.size())
            return false;
        else
        {
            typename list<T, Alloc>::const_iterator first = lhs.begin();
            typename list<T, Alloc>::const_iterator second = rhs.begin();
            while (first != lhs.end() || second != rhs.end())
            {
                if (*first == *second) {
                    first++;
                    second++;
                }
                else
                    return false;
            }
            return true;
        }
    }

    template <class T, class Alloc>
    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return false;
        else
            return true;
    }

    template <class T, class Alloc>
    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        if (&lhs == &rhs)
            return false;
        if (lhs.size() != rhs.size()) {
            if (lhs.size() < rhs.size())
                return true;
            else
                return false;
        }
        else {
            typename list<T, Alloc>::const_iterator first = lhs.begin();
            typename list<T, Alloc>::const_iterator second = rhs.begin();
            while (first != lhs.end() || second != rhs.end()) {
                if (*first < *second)
                    return true;
                else if (*first > *second)
                    return false;
                else if (*first == *second){
                    first++;
                    second++;
                }
            }
            return false;
        }
    }

    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
        x.swap(y);
    }
} //namespace ft
#endif