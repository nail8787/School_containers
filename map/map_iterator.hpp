#ifndef NEW_CONTAINERS_MAP_ITERATOR_HPP
#define NEW_CONTAINERS_MAP_ITERATOR_HPP

#include <cstddef>
#include "../iterator_tags.hpp"

namespace ft {
    template <typename value_type>
    struct tree_Node {
        bool color; // RED == 1 || BLACK == 0
        tree_Node *parent;
        tree_Node *left_child;
        tree_Node *right_child;
        value_type *data;
    };

    template <typename T>
    class map_iterator {
    public:
        typedef map_iterator<T> _self;
        typedef T         value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T*   pointer;
        typedef T& reference;
        typedef bidirectional_iterator_tag  iterator_category;

        typedef tree_Node<T>* node_ptr;

        node_ptr _point;

        map_iterator() : _point(NULL) {}

        map_iterator(node_ptr val) : _point(val) {}

        map_iterator(_self const &src) {
            _point = NULL;
            *this = src;
        }

        _self &operator=(_self const &src) {
            if (this == &src)
                return *this;
            this->_point = src._point;
            return *this;
        }

        reference operator*() const { return *(_point->data); };
        pointer operator->() const { return _point->data; }

        _self &operator++() {
            if (_point->right_child != NULL && _point->right_child->data != NULL) {
                _point = _point->right_child;
                while (_point->left_child != NULL && _point->left_child->data != NULL)
                    _point = _point->left_child;
            } else {
                while (_point->parent != NULL && _point == _point->parent->right_child) {
                    _point = _point->parent;
                }
                if (_point->parent == NULL) /* для прохода к элементу после последнего,
 *                                          без этого алгоритм пойдет к корню и попытается получить доступ к элементу перед корнем
 *                                          получим сегу */
                {
                    while (_point->right_child->data != NULL)
                        _point = _point->right_child;
                    _point = _point->right_child;
                    return *this;
                }
                if (_point->right_child != _point->parent)
                    _point = _point->parent;
            }
            return *this;
        };

        _self &operator--() {
            if (_point->left_child != NULL && _point->left_child->data != NULL) {
                _point = _point->left_child;
                while (_point->right_child != NULL && _point->right_child->data != NULL)
                    _point = _point->right_child;
            } else {
                while (_point == _point->parent->left_child) {
                    _point = _point->parent;
                }
                if (_point->left_child != _point->parent)
                    _point = _point->parent;
            }
            return *this;
        };

        _self operator++(int) {
            map_iterator tmp = *this;
            *this = this->operator++();
            return tmp;
        };

        _self operator--(int) {
            map_iterator tmp = *this;
            *this = this->operator--();
            return tmp;
        };

        bool operator !=(_self const &end) const { return _point != end._point; }
        bool operator==(_self const &end) const { return _point == end._point; }
    };

    template <typename T>
    class const_map_iterator {
    public:
        typedef map_iterator<T> iterator;

        typedef const_map_iterator<T> _self;
        typedef T         value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T*   pointer;
        typedef const T& reference;
        typedef bidirectional_iterator_tag  iterator_category;

        typedef const tree_Node<T>* node_ptr;

        node_ptr _point;

        const_map_iterator() : _point(NULL) {}

        const_map_iterator(node_ptr val) : _point(val) {}

        const_map_iterator(_self const &src) {
            _point = NULL;
            *this = src;
        }

        const_map_iterator(iterator const &src) : _point(src._point) {}

        _self &operator=(_self const &src) {
            if (this == &src)
                return *this;
            this->_point = src._point;
            return *this;
        }

        reference operator*() const { return *(_point->data); };
        pointer operator->() const { return _point->data; }

        _self &operator++() {
            if (_point->right_child != NULL && _point->right_child->data != NULL) {
                _point = _point->right_child;
                while (_point->left_child != NULL && _point->left_child->data != NULL)
                    _point = _point->left_child;
            } else {
                while (_point->parent != NULL && _point == _point->parent->right_child) {
                    _point = _point->parent;
                }
                if (_point->parent == NULL) /* для прохода к элементу после последнего,
 *                                          без этого алгоритм пойдет к корню и попытается получить доступ к элементу перед корнем
 *                                          получим сегу */
                {
                    while (_point->right_child->data != NULL)
                        _point = _point->right_child;
                    _point = _point->right_child;
                    return *this;
                }
                if (_point->right_child != _point->parent)
                    _point = _point->parent;
            }
            return *this;
        };

        _self &operator--() {
            if (_point->left_child != NULL && _point->left_child->data != NULL) {
                _point = _point->left_child;
                while (_point->right_child != NULL && _point->right_child->data != NULL)
                    _point = _point->right_child;
            } else {
                while (_point == _point->parent->left_child) {
                    _point = _point->parent;
                }
                if (_point->left_child != _point->parent)
                    _point = _point->parent;
            }
            return *this;
        };

        _self operator++(int) {
            const_map_iterator tmp = *this;
            *this = this->operator++();
            return tmp;
        };

        _self operator--(int) {
            const_map_iterator tmp = *this;
            *this = this->operator--();
            return tmp;
        };

        bool operator !=(_self const &end) const { return _point != end._point; }
        bool operator==(_self const &end) const { return _point == end._point; }
    };

    template <typename IteratorL, typename IteratorR>
    bool operator!=(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator*() != rhs.operator*(); }
    template <typename IteratorL, typename IteratorR>
    bool operator==(const IteratorL& lhs, const IteratorR &rhs) { return lhs.operator*() == rhs.operator*(); }
}

#endif //NEW_CONTAINERS_MAP_ITERATOR_HPP
