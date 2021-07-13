
#include "../vector/vector.hpp"
#include <list>
#include "stack.hpp"
#include <iostream>
#define RED "\x1b[41;37m"
#define GREEN "\x1b[42;30m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;30m"
#define RESET "\x1b[0m"

int main() {
    {
        ft::vector<int> myvector(3, 100);          // vector with 3 elements
        std::list<int> mylist(2, 200);        // list with 2 elements

        ft::stack<int> first;                    // empty stack
        ft::stack<int> second(myvector);         // stack initialized to copy of deque

        ft::stack<int, std::list<int> > third;  // empty stack using list
        ft::stack<int, std::list<int> > fourth(mylist);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR PUSH, EMPTY, TOP, POP" << RESET << std::endl;
        ft::stack<int> ft_mystack;
        int ft_sum (0);
        for (int i=1;i<=10;i++) ft_mystack.push(i);
        while (!ft_mystack.empty())
        {
            ft_sum += ft_mystack.top();
            ft_mystack.pop();
        }
        std::cout << "total ft: " << ft_sum << '\n';
    }
    {
        std::cout << BLUE << "ONE MORE CHECK FOR PUSH | POP | SIZE " << RESET << std::endl;
        ft::stack<int> ft_myints;
        std::cout << "0. ft_size: " << ft_myints.size() << '\n';

        for (int i=0; i<5; i++) ft_myints.push(i);
        std::cout << "1. ft_size: " << ft_myints.size() << '\n';

        ft_myints.pop();
        std::cout << "2. ft_size: " << ft_myints.size() << '\n';
    }
    {
        ft::stack<int> ft_ints;
        ft::stack<int> ft_reverse_ints;
        ft::stack<int> ft_int_equal;

        for (int i=0; i<5; i++)
            ft_ints.push(i);
        for (int i=4; i>=0; i--)
            ft_reverse_ints.push(i);
        for (int i=0; i<5; i++)
            ft_int_equal.push(i);

        if (ft_ints == ft_int_equal)
            std::cout << "ft_ints and ft_inst_equal equal" << std::endl;

        if (ft_ints < ft_reverse_ints)
            std::cout << "ints less than reverse_ints" << std::endl;
        if (ft_ints > ft_reverse_ints)
            std::cout << "ft_ints bigger than ft_reverse_ints" << std::endl;
    }
}