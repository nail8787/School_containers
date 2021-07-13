#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP
#include <stddef.h>
#include <utility>
#include <memory>
#include "pair.h"
#include <iostream>
#include "map_iterator.hpp"
#include "../reverse_iterator.hpp"
//needed for linux
#include <limits>
#define RED_NODE "\x1b[31m"
#define GREEN_NODE "\x1b[32m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;30m"
#define RESET "\x1b[0m"

namespace ft {

    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map {
    public:
        typedef const Key key_type;
        typedef T   mapped_type;
        typedef ft::pair<key_type, mapped_type> value_type;
        typedef tree_Node<value_type> Node;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef map_iterator<value_type> iterator;
        typedef const_map_iterator<value_type> const_iterator;
        typedef my_reverse_iterator<iterator> reverse_iterator;
        typedef my_reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

//        struct Node {
//            bool color; // RED == 1 || BLACK == 0
//            Node *parent;
//            Node *left_child;
//            Node *right_child;
//            value_type *data;
//        };

        typedef typename Alloc::template rebind<Node>::other _Node_Alloc; //Для выделение памяти под структуру Node, а не просто pair<const Key, T>

        //empty (1)
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _key_comp(comp){
            _node_allocator = _Node_Alloc(); //Надо ещё проверить
            _root = NULL;
            _size = 0;
        };
        //range (2)
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _key_comp(comp)
        {
            _node_allocator = _Node_Alloc();
            _root = NULL;
            _size = 0;
            insert(first, last);
        };

        //copy (3)
        map (const map& x) {
            _root = NULL;
            _size = 0;
            *this = x;
        };

        ~map() {
            if (_size > 0 && _root != NULL)
                this->clear();
        }

        map& operator= (const map& x) {
            if (this != &x) {
                if (_root != NULL)
                    this->clear();
                this->insert(x.begin(), x.end());
                this->_size = x._size;
            }
            return *this;
        }

        class value_compare: public std::binary_function<value_type, value_type, bool>
        {
//            friend class map<Key, T, Compare, Alloc>;
        public:
                Compare comp;
                explicit value_compare(Compare c) : comp(c) {}

            public:
                bool operator()(const value_type& x, const value_type& y) const {
                    return comp(x.first, y.first);
                }
        };

        iterator begin() {
            if (_root == NULL)
                return iterator(&empty_ptr);
            Node *current = _root;
            while (current->left_child->data != NULL)
                current = current->left_child;
            iterator it(current);
            return it;
        }

        const_iterator begin() const {
            if (_root == NULL)
                return const_iterator(&empty_ptr);
            Node *cur = _root;
            while (cur->left_child->data != NULL)
                cur = cur->left_child;
            const_iterator it(cur);
            return it;
        }

        iterator end() {
            if (_root == NULL)
                return iterator(&empty_ptr);
            Node *current = _root;
            while (current->right_child->data != NULL)
                current = current->right_child;
            current = current->right_child;
            iterator it(current);
            return it;
        }

        const_iterator end() const {
            if (_root == NULL)
                return const_iterator(&empty_ptr);
            Node *current = _root;
            while (current->right_child->data != NULL)
                current = current->right_child;
            current = current->right_child;
            const_iterator it(current);
            return it;
        }

        reverse_iterator rbegin() {
            reverse_iterator rit(this->end());
            return rit;
        }

        const_reverse_iterator rbegin() const {
            const_reverse_iterator rit(this->end());
            return rit;
        }

        reverse_iterator rend() {
            reverse_iterator rit(this->begin());
            return rit;
        }

        const_reverse_iterator rend() const {
            const_reverse_iterator rit(this->begin());
            return rit;
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return std::numeric_limits<size_t>::max()/sizeof(Node)/2; // /2 для линукса хз почему -.-
        }

        bool empty() const {
            return _size == 0;
        }

        iterator lower_bound (const key_type& k) {
            iterator current(this->begin());
            while (comp(current.operator->()->first, k))
                current++;
            return current;
        }

        const_iterator lower_bound (const key_type& k) const{
            iterator current(this->begin());
            while (comp(current.operator->()->first, k))
                current++;
            return current;
        }

        iterator upper_bound(const key_type& k) {
            iterator current(this->begin());
            while (!comp(k, current.operator->()->first))
                current++;
            return current;
        }

        const_iterator upper_bound(const key_type& k) const{
            iterator current(this->begin());
            while (!comp(k, current.operator->()->first))
                current++;
            return current;
        }

        mapped_type& operator[] (const key_type& k) {
            Node *current(_root);
            while (current != NULL && current->data != NULL)
            {
                if (k == current->data->first)
                    return current->data->second;
                else if (k < current->data->first)
                    current = current->left_child;
                else
                    current = current->right_child;
            }
            return (insert(value_type(k, mapped_type())).first.operator*().second);
        }

        iterator find (const key_type &k) {
            Node *current = _root;
            while (current->data != NULL){
                if (comp(k, current->data->first) == 0 && comp(current->data->first, k) == 0){
                    iterator it(current);
                    return it;
                }
                else if (comp(k, current->data->first))
                    current = current->left_child;
                else
                    current = current->right_child;
            }
            return this->end();
        }

        const_iterator find(const key_type &k ) const{
            Node *current = _root;
            while (current->data != NULL){
                if (comp(k, current->data->first) == 0 && comp(current->data->first, k) == 0){
                    const_iterator it(current);
                    return it;
                }
                else if (comp(k, current->data->first))
                    current = current->left_child;
                else
                    current = current->right_child;
            }
            return this->end();
        };

        size_type count (const key_type& k) const{
            size_type count = 0;
            if (this->find(k) != this->end())
                count++;
            return count;
        }

        ft::pair<iterator, iterator> equal_range (const key_type& k) {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }
        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        key_compare key_comp() const {
            return comp;
        }

        value_compare value_comp() const {
            return value_compare(comp);
        }

        ft::pair<iterator,bool> insert (const value_type& val) {
            if (_root == NULL) {
                _root = allocate_new_node(0);
                _root->parent = NULL;
                _root->data = _allocator.allocate(1);
                _allocator.construct(_root->data, val);
                _root->color = 0;
                _size++;
                iterator current(_root);
                return ft::pair<iterator, bool>(current, 1);
            }
            Node* current(_root);
            while (current->data != NULL)
            {
                if (comp(val.first, current->data->first))
                    current = current->left_child;
                else if (val.first == current->data->first){
                    iterator it(current);
                    return (ft::pair<iterator, bool>(it, 0));
                }
                else
                    current = current->right_child;
            }
            int for_allocate;
            if (current == current->parent->left_child)
                for_allocate = 1;
            else
                for_allocate = 2;
            Node *new_node = allocate_new_node(for_allocate);
            new_node->parent = current->parent;
            new_node->color = 1;
            new_node->data = _allocator.allocate(1);
            _allocator.construct(new_node->data, val);
            Node *current_parent = current->parent;
            if (current == current_parent->left_child) {
                current_parent->left_child = new_node;
                new_node->left_child = current;
                current->parent = new_node;
            }
            else {
                current_parent->right_child = new_node;
                new_node->right_child = current;
                current->parent = new_node;
            }
            iterator new_node_it(new_node);
            _size++;
            tree_fixup(new_node);
            return (ft::pair<iterator, bool>(new_node_it, 1));
        };

        //with hint (2)
        iterator insert (iterator position, const value_type& val) {
            if (_root == NULL) {
                _root = allocate_new_node(0);
                _root->parent = NULL;
                _root->data = _allocator.allocate(1);
                _allocator.construct(_root->data, val);
                _root->color = 0;
                _size++;
                iterator current(_root);
                return current;
            }
            Node* current;
            if (comp((*position).first, val.first) && position._point->left_child != NULL && position._point->left_child->data == NULL) {
                    current = position._point->left_child;
            }
            else {
                current = _root;
                while (current->data != NULL) {
                    if (comp(val.first, current->data->first))
                        current = current->left_child;
                    else if (val.first == current->data->first) {
                        iterator it(current);
                        return it;
                    } else
                        current = current->right_child;
                }
            }
            int for_allocate;
            if (current == current->parent->left_child)
                for_allocate = 1;
            else
                for_allocate = 2;
            Node *new_node = allocate_new_node(for_allocate);
            new_node->parent = current->parent;
            new_node->color = 1;
            new_node->data = _allocator.allocate(1);
            _allocator.construct(new_node->data, val);
            Node *current_parent = current->parent;
            if (current == current_parent->left_child) {
                current_parent->left_child = new_node;
                new_node->left_child = current;
            }
            else {
                current_parent->right_child = new_node;
                new_node->right_child = current;
            }
            iterator new_node_it(new_node);
            _size++;
            tree_fixup(new_node);
            return new_node_it;
        };

        //range (3)

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last){
                insert(*first);
                first++;
            }
        };

        void erase (iterator position) {
            erase(position.operator->()->first);
        }

        size_type erase (const key_type& k){
            Node *del_node = _root;
            while (del_node != NULL && del_node->data != NULL && del_node->data->first != k) {
                if (comp(k, del_node->data->first)) {
                    del_node = del_node->left_child;
                }
                else {
                    del_node = del_node->right_child;
                }
            }
            Node *temp = del_node;
            bool save_color = temp->color;
            if (del_node->data == NULL) {
                return (0);
            }
            if (del_node->data->first == k && _size == 1) {
                this->clear();
                return (1);
            }
            Node *save;
            if (del_node->left_child->data == NULL) {
                save = del_node->right_child;
                transplant(del_node, del_node->right_child);
                _node_allocator.destroy(del_node->left_child);
                _node_allocator.deallocate(del_node->left_child, 1);
            }
            else if (del_node->right_child->data == NULL) {
                save = del_node->left_child;
                transplant(del_node, del_node->left_child);
                _node_allocator.destroy(del_node->right_child);
                _node_allocator.deallocate(del_node->right_child, 1);
            }
            else {
                temp = min(del_node->right_child);
                save_color = temp->color;
                save = temp->right_child;
                if (temp->parent == del_node)
                    save->parent = temp;
                else {
                    transplant(temp, temp->right_child);
                    temp->right_child = del_node->right_child;
                    temp->right_child->parent = temp;
                }
                transplant(del_node, temp);
                one_leaf_delete(temp->left_child);
                temp->left_child = del_node->left_child;
                temp->left_child->parent = temp;
                temp->color = del_node->color;
            }
            _allocator.destroy(del_node->data);
            _allocator.deallocate(del_node->data, 1);
            _node_allocator.destroy(del_node);
            _node_allocator.deallocate(del_node, 1);
            _size--;
            if (save_color == 0)
                delete_fixup(save);
            return (1);
        }

        void erase (iterator first, iterator last) {
            while (first != last && _size > 1) {
                iterator delete_node = first;
                first++;
                erase(delete_node);
            }
            if (first != last && _size == 1) {
                leaf_delete(first._point);
                value_type *temp = first._point->data;
                _node_allocator.destroy(first._point);
                _node_allocator.deallocate(first._point, 1);
                _allocator.destroy(temp);
                _allocator.deallocate(temp, 1);
                _size = 0;
                _root = NULL;
            }
        }

        void clear () {
            erase(this->begin(), this->end());

        }

        void swap (map& x) {
            Node *temp_root = x._root;
            size_type temp_size = x._size;
            x._root = this->_root;
            x._size = this->_size;
            this->_root = temp_root;
            this->_size = temp_size;
        }

        allocator_type get_allocator() const{
            return _allocator;
        }

        Compare comp;
    private:
        Node *_root;
        Node empty_ptr;
        size_type _size;
        _Node_Alloc _node_allocator;
        Alloc _allocator;
        key_compare _key_comp;

        void one_leaf_delete(Node *leaf) {
            _node_allocator.destroy(leaf);
            _node_allocator.deallocate(leaf, 1);
        }
        void leaf_delete(Node *node_to_delete){
            if (node_to_delete->left_child != NULL && node_to_delete->left_child->data == NULL) {
                _node_allocator.destroy(node_to_delete->left_child);
                _node_allocator.deallocate(node_to_delete->left_child, 1);
            }
            if (node_to_delete->right_child != NULL && node_to_delete->right_child->data == NULL) {
                _node_allocator.destroy(node_to_delete->right_child);
                _node_allocator.deallocate(node_to_delete->right_child, 1);
            }
        }

        void leaf_node_construct(Node *leaf, Node *parent) {
            leaf->right_child = NULL;
            leaf->left_child = NULL;
            leaf->data = NULL;
            leaf->color = 0;
            leaf->parent = parent;
        }

        Node *allocate_new_node(int root_or_child) {
            // 0 == root, 1 == left_child, 2 == right_child
            Node *node;
            Node *left_leaf;
            Node *right_leaf;
            node = _node_allocator.allocate(1);
            if (root_or_child == 0 || root_or_child == 2) {
                left_leaf = _node_allocator.allocate(1);
                leaf_node_construct(left_leaf, node);
                node->left_child = left_leaf;
            }
            if (root_or_child == 0 || root_or_child == 1) {
                right_leaf = _node_allocator.allocate(1);
                leaf_node_construct(right_leaf, node);
                node->right_child = right_leaf;
            }
            return node;
        }

        Node *min(Node *x) {
            while (x->left_child->data != NULL)
                x = x->left_child;
            return x;
        }

        void transplant(Node *first, Node *second) {
            if (first->parent == NULL)
                _root = second;
            else if (first == first->parent->left_child)
                first->parent->left_child = second;
            else
                first->parent->right_child = second;
            second->parent = first->parent;
        }

        void left_rotate(Node *x) {
            Node *y = x->right_child;
            x->right_child = y->left_child;
            y->left_child->parent = x;
            y->left_child = x;
            y->parent = x->parent;
            if (x == _root) {
                y->parent = NULL;
                _root = y;
            } else if (x->parent->left_child == x)
                x->parent->left_child = y;
            else
                x->parent->right_child = y;
            x->parent = y;
        }

        void right_rotate(Node *x) {
            Node *y = x->left_child;
            x->left_child = y->right_child;
            y->right_child->parent = x;
            y->right_child = x;
            y->parent = x->parent;
            if (x == _root) {
                y->parent = NULL;
                _root = y;
            }
            else if (x->parent->left_child == x)
                x->parent->left_child = y;
            else
                x->parent->right_child = y;
            x->parent = y;
        }

        void tree_fixup(Node *z){
            while (z->parent != NULL && z->parent->color == 1){
                if (z->parent == z->parent->parent->left_child){
                    Node *uncle = z->parent->parent->right_child;
                    if (uncle->color == 1){
                        z->parent->color = 0;
                        uncle->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    }
                    else{
                        if (z == z->parent->right_child){
                            z = z->parent;
                            left_rotate(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        right_rotate(z->parent->parent);
                    }
                }
                else {
                    Node *uncle = z->parent->parent->left_child;
                    if (uncle->color == 1){
                        z->parent->color = 0;
                        uncle->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    }
                    else{
                        if (z == z->parent->left_child)
                        {
                            z = z->parent;
                            right_rotate(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        left_rotate(z->parent->parent);
                    }
                }
            }
            _root->color = 0;
        }

        void delete_fixup(Node *x) {
            while (x != _root && x->color == 0) {
                if (x == x->parent->left_child)
                {
                    Node *bro = x->parent->right_child;
                    if (bro->color == 1)
                    {
                        bro->color = 0;
                        x->parent->color = 1;
                        left_rotate(x->parent);
                        bro = x->parent->right_child;
                    }
                    if (bro->left_child->color == 0 && bro->right_child->color == 0)
                    {
                        bro->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (bro->right_child->color == 0)
                        {
                            bro->left_child->color = 0;
                            bro->color = 1;
                            right_rotate(bro);
                            bro = x->parent->right_child;
                        }
                        bro->color = x->parent->color;
                        x->parent->color = 0;
                        bro->right_child->color = 0;
                        left_rotate(x->parent);
                        x = _root;
                    }
                }
                else {
                    Node *bro = x->parent->left_child;
                    if (bro->color == 1) {
                        bro->color = 0;
                        x->parent->color = 1;
                        right_rotate(x->parent);
                        bro = x->parent->left_child;
                    }
                    if (bro->right_child->color == 0 && bro->left_child->color == 0) {
                        bro->color = 1;
                        x = x->parent;
                    }
                    else {
                        if (bro->left_child->color == 0) {
                            bro->right_child->color = 0;
                            bro->color = 1;
                            left_rotate(bro);
                            bro = x->parent->left_child;
                        }
                        bro->color = x->parent->color;
                        x->parent->color = 0;
                        bro->left_child->color = 0;
                        right_rotate(x->parent);
                        x = _root;
                    }
                }
            }
        x->color = 0;
        }
    };
}
#endif //CONTAINERS_MAP_HPP
