#include <vector>
#include "vector.hpp"
#include <iostream>
#include <algorithm>
#include <exception>

#define RED "\x1b[41;37m"
#define GREEN "\x1b[42;37m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;37m"
#define RESET "\x1b[0m"

template <typename T>
void myfunc(T i){
    std::cout << " " << i ;
}

template <typename T>
void output_ft(ft::vector<T> &out){
    size_t i = 0;
    std::cout << BLUE << "FT_VECTOR" << RESET << std::endl << "| ";
    while (i < out.size())
        std::cout << out[i++] << " | ";
    std::cout << std::endl;
}

template <typename T>
void output_std(std::vector<T> &out){
    size_t i = 0;
    std::cout << BLUE << "STD_VECTOR" << RESET << std::endl << "| ";
    while (i < out.size())
        std::cout << out[i++] << " | ";
    std::cout << std::endl;
}

int main() {
    {
        ft::vector<float> ft_vector;
        std::cout << GREEN << "| CHECK FOR EMPTY CONSTRUCTOR AND EMPTY FUNC WITH EMPTY CONTAINER |" << RESET << std::endl;
        std::cout << "EMPTY? " << ft_vector.empty() << std::endl;
    }
    {
        std::cout << GREEN << "CHECK FOR CONSTRUCTOR FILL, CAPACITY, SIZE, [], MAX_SIZE, EMPTY WITH FILLED CONTAINER"  << RESET << std::endl;
        ft::vector<float> ft_vector(10, 1.1f);
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "First element " << ft_vector[0] << std::endl;
        std::cout << "MAX_SIZE " << ft_vector.max_size() << std::endl;
        std::cout << "EMPTY? (Should be 0, because it's not empty) " << ft_vector.empty() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR RANGE CONSTRUCTOR AND COPY CONSTRUCTOR |" << RESET << std::endl;
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        ft::vector<int> ft_vector(values, values + 10);
        std::cout << RED << "Range constructed vector" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << RED << "Construct new vector using copy of one before" << RESET << std::endl;
        ft::vector<int> ft_copy(ft_vector);
        output_ft(ft_copy);
    }
    {
        std::cout << GREEN << "| CHECK FOR OPERATOR= |" << RESET << std::endl;
        ft::vector<int> real(10, 123);
        ft::vector<int> copy(1, 999);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        std::cout << "SIZE OF COPY: " << copy.size() << std::endl;
        std::cout << "CAPACITY OF COPY: " << copy.capacity() << std::endl;
        output_ft(real);
        output_ft(copy);
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        copy = real;
        std::cout << "SIZE: " << copy.size() << std::endl;
        std::cout << "CAPACITY: " << copy.capacity() << std::endl;
        output_ft(real);
        output_ft(copy);
    }
    {
        std::cout << GREEN << "| CHECK FOR RESIZE|" << RESET << std::endl;
        ft::vector<int> ft_vector(10, 1);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        ft_vector.resize(5, 2);
        std::cout << RED << "|AFTER RESIZE (N < SIZE)|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER RESIZE (N > SIZE && N < CAPACITY)|" << RESET << std::endl;
        ft_vector.resize(7, 3);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER RESIZE (N > SIZE && N > CAPACITY)|" << RESET << std::endl;
        ft_vector.resize(15, 5);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR RESERVE |" << RESET << std::endl;
        ft::vector<char> ft_vector(10, 'Z');
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        output_ft(ft_vector);
        ft_vector.reserve(25);
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        output_ft(ft_vector);
    }
    {
        std::cout << GREEN << "| CHECK FOR ELEMENT ACCESS |" << RESET << std::endl;
        int values[] = {1, 2, 3, 4, 5};
        ft::vector<int> ft_vector(values, values + 5);
        output_ft(ft_vector);
        std::cout << RED << "Valid [1]" << RESET << std::endl;
        std::cout << "-> " << ft_vector[1] << std::endl;
//        std::cout << RED << "NOT Valid [n] causes undefined behavior" << RESET << std::endl;
//        std::cout << ft_vector[10] << std::endl;
        std::cout << RED << "At(1) valid" << RESET << std::endl;
        std::cout << "-> " << ft_vector.at( 1 ) << std::endl;
        std::cout << RED << "At(10) greater then size of container" << RESET << std::endl;
        try {
            std::cout << ft_vector.at(10) << std::endl;
        }
        catch (std::exception& exc){
            std::cout << "exception caught: " << exc.what() << std::endl;
        }
        std::cout << RED << "Front" << RESET << std::endl;
        std::cout << "-> " << ft_vector.front() << std::endl;
        std::cout << RED << "Back" << RESET << std::endl;
        std::cout << "-> " << ft_vector.back() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR PUSH_BACK |" << RESET << std::endl;
        ft::vector<int> ft_vector(5, 111);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft_vector.push_back(999);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << GREEN << "|CHECK FOR POP_BACK|" << RESET << std::endl;
        ft_vector.pop_back();
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
        {
        std::cout << GREEN << "| CHECK FOR ASSIGN |" << RESET << std::endl;
        ft::vector<int> ft_vector(5, 1);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft_vector.assign(10, 2);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR ASSIGN RANGE |" << RESET << std::endl;
        int exmpl[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        ft::vector<int> ft_vector(5, 1);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft_vector.assign(exmpl, exmpl + 10);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << GREEN << "| CHECK FOR ERASE [begin + 3] |" << RESET << std::endl;
        ft::vector<int>::iterator ft_pos = ft_vector.begin() + 3;
        ft_pos = ft_vector.erase(ft_pos);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << "ITERATOR AFTER ERASE: " << *ft_pos << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR INSERT SINGLE AND FILL |" << RESET << std::endl;
        int values[] = {1, 2, 3, 4, 5};
        ft::vector<int> ft_vector(values, values + 5);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << RED << "|AFTER SINGLE INSERT|" << RESET << std::endl;
        ft::vector<int>::iterator start = ft_vector.begin() + 1;
        start = ft_vector.insert(start, 66);
        std::cout << "RETURN POSITION " << *start << std::endl;
        output_ft(ft_vector);
        std::cout << RED << "|AFTER FILL INSERT|" << RESET << std::endl;
        start++;
        ft_vector.insert(start, 3, 10);
        output_ft(ft_vector);
    }
    {
        std::cout << GREEN << "| CHECK FOR INSERT WITH REALLOCATIONS|" << RESET << std::endl;
        ft::vector<int> ft_vector(5, 1);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft::vector<int>::iterator start = ft_vector.begin() + 3;
        ft_vector.insert(start, 3);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR INSERT FILL WITH REALLOCATION |" << RESET << std::endl;
        ft::vector<int> ft_vector(5, 1);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft::vector<int>::iterator start = ft_vector.begin() + 3;
        ft_vector.insert(start, 3, 10);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR INSERT RANGE WITH REALLOCATION |" << RESET << std::endl;
        int vector[] = {1, 2, 3, 4, 5};
        int vector2[] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
        std::cout << YELLOW << "| INSERT RANGE IN THE SAME VECTOR |" << RESET << std::endl;
        ft::vector<int> ft_vector(vector, vector + 5);
        ft::vector<int>::iterator ft_first = ft_vector.begin() + 3;
        ft::vector<int>::iterator ft_last = ft_vector.begin() + 5;
        ft::vector<int>::iterator ft_pos = ft_vector.begin() + 4;
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft_vector.insert(ft_pos, ft_first, ft_last);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << YELLOW << "| INSERT RANGE OUTSIDE THE VECTOR |" << RESET << std::endl;
        ft_pos = ft_vector.begin() + 1;
        ft_vector.insert(ft_pos, vector2, vector2 + 9);
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << GREEN << "| CHECK FOR ERASE [1] |" << RESET << std::endl;
        ft_pos = ft_vector.erase((ft_vector.begin() + 1));
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "ITER_POS AFTER ERASE: " << *ft_pos << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR RANGE ERASE |" << RESET << std::endl;
        int vector[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        ft::vector<int> ft_vector(vector, vector + 9);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft::vector<int>::iterator ft_first = ft_vector.begin() + 2;
        ft::vector<int>::iterator ft_last = ft_vector.begin() + 7;
        ft_first = ft_vector.erase(ft_first, ft_last);
        std::cout << "<POSITIONS CHECK>" << "FT -> " << *ft_first << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR SWAP|" << RESET << std::endl;
        int values_x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int values_y[] = {56, 57, 58, 59, 60};
        ft::vector<int> ft_vector(values_x, values_x + 10);
        ft::vector<int> ft_vector2(values_y, values_y + 5);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        std::cout << YELLOW << "VECTOR X" << RESET << std::endl;
        ft::vector<int>::iterator in_x = ft_vector.begin();
        std::cout << "ITERATOR in_X before swap -> " << *in_x << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE X: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY X: " << ft_vector.capacity() << std::endl;
        std::cout << YELLOW << "VECTOR Y" << RESET << std::endl;
        ft::vector<int>::iterator in_y = ft_vector2.begin();
        std::cout << "ITERATOR in_Y before swap -> " << *in_y << std::endl;
        output_ft(ft_vector2);
        std::cout << "SIZE Y: " << ft_vector2.size() << std::endl;
        std::cout << "CAPACITY Y: " << ft_vector2.capacity() << std::endl;
        std::cout << RED << "|AFTER SWAP|" << RESET << std::endl;
        ft_vector.swap(ft_vector2);
        std::cout << YELLOW << "VECTOR X" << RESET << std::endl;
        std::cout << "ITERATOR in_X after swap -> " << *in_x << std::endl;
        std::cout << "ITERATOR ++ after swap -> " << *(in_x++) << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE X: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY X: " << ft_vector.capacity() << std::endl;
        std::cout << YELLOW << "VECTOR Y" << RESET << std::endl;
        std::cout << "ITERATOR in_Y after swap -> " << *in_y << std::endl;
        std::cout << "ITERATOR ++ after swap -> " << *(in_y++) << std::endl;
        output_ft(ft_vector2);
        std::cout << "SIZE Y: " << ft_vector2.size() << std::endl;
        std::cout << "CAPACITY Y: " << ft_vector2.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR CLEAR |" << RESET << std::endl;
        ft::vector<int> ft_vector(5, 11);
        std::cout << RED << "|BEFORE|" << RESET << std::endl;
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
        std::cout << RED << "|AFTER|" << RESET << std::endl;
        ft_vector.clear();
        output_ft(ft_vector);
        std::cout << "SIZE: " << ft_vector.size() << std::endl;
        std::cout << "CAPACITY: " << ft_vector.capacity() << std::endl;
    }
    {
        std::cout << GREEN << "| CHECK FOR RELATIONS OPERATORS|" << RESET << std::endl;
        ft::vector<int> foo(3, 100);   // three ints with a value of 100
        ft::vector<int> bar(2, 200);   // two ints with a value of 200

        if (foo == bar) std::cout << "foo and bar are equal\n";
        if (foo != bar) std::cout << "foo and bar are not equal\n";
        if (foo < bar) std::cout << "foo is less than bar\n";
        if (foo > bar) std::cout << "foo is greater than bar\n";
        if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
        if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
    }
    {
        std::cout << GREEN << "| CHECK FOR ITERATOR |" << RESET << std::endl;
        ft::vector<float> ft_vector(5, 1.24f);
        ft_vector.push_back(9.99f);
        ft::vector<float>::iterator start = ft_vector.begin();
        while (start != ft_vector.end()) {
            std::cout << *start << " | ";
            start++;
        };
        std::cout << std::endl;
        std::cout << GREEN << "| CHECK FOR COMPARING ITERATOR AND CONST_ITERATOR|" << RESET << std::endl;
        ft::vector<float>::const_iterator cit = ft_vector.begin();
        ft::vector<float>::iterator it = ft_vector.begin();
        if (cit == it) std::cout << "it-" << *it << " and cit-" << *cit << " are equal" << std::endl;
        if (it <= cit) std::cout << "it-" << *it << " <= cit-" << *cit << std::endl;
        it = ft_vector.end() - 1;
        if (it > cit) std::cout << "it-" << *it << " > cit-" << *cit << std::endl;
        if (it == cit)  std::cout << "it-" << *it << " and cit-" << *cit << " are equal" << std::endl;
//        *cit = 10.0f;//cannot assign because it's const_iterator
    }
    {
        std::cout << GREEN << "| CHECK FOR REVERSE_ITERATOR |" << RESET << std::endl;
        ft::vector<float> ft_vector(5, 1.24f);
        ft_vector.push_back(9.99f);
        ft::vector<float>::reverse_iterator start = ft_vector.rbegin();
        while (start != ft_vector.rend()) {
            std::cout << *start << " | ";
            start++;
        };
        std::cout << std::endl;
    }
    {
        std::cout << GREEN << "| FT |" << RESET << std::endl;
        ft::vector<int> first;
        ft::vector<int> second;
        first.push_back(1);
        first.push_back(2);
        first.push_back(3);
        second.push_back(2);
        second.push_back(2);
        output_ft(first);
        output_ft(second);
        if (first < second) std::cout << "first < second" << std::endl;
        if (second < first) std::cout << "second < first" << std::endl;
    }
    {
        std::cout << GREEN << "ALGORITHM FOR EACH TEST" << RESET << std::endl;
        double my[] = {1, 2, 3, 3, 3, 4, 7, 3, 9};
        ft::vector<double> ft_ex(my, my + 9);
        std::for_each(ft_ex.begin(), ft_ex.end(), myfunc<double>);
        std::cout << std::endl;
        std::cout << "count val 3 in ft_container is " << std::count(ft_ex.begin(), ft_ex.end(), 3) << std::endl;
    }
    {
        std::cout << GREEN << "VECTOR WITH DIFFERENT STRINGS" << RESET << std::endl;
        std::string first("Hello"), second("mir"), third("world!");
        ft::vector<std::string> ft_one;
        ft_one.push_back(first);
        ft_one.push_back(second);
        ft_one.pop_back();
        ft_one.push_back(third);
        std::for_each(ft_one.begin(), ft_one.end(), myfunc<std::string>);
        std::cout << std::endl;
    }
    {
        std::string one("top");
        ft::vector<std::string> ft_one(10, one);
        std::for_each(ft_one.begin(), ft_one.end(), myfunc<std::string>);
        std::cout << std::endl;
        ft_one.insert(ft_one.begin() + 4, std::string ("asd"));
        std::for_each(ft_one.begin(), ft_one.end(), myfunc<std::string>);
        std::cout << std::endl;
    }
}