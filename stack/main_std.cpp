#include <stack>
#include <iostream>
#include <list>
#include <vector>
#define RED "\x1b[41;37m"
#define GREEN "\x1b[42;30m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;30m"
#define RESET "\x1b[0m"

int main() {
    {
        std::vector<int> myvector(3, 100);          // vector with 3 elements
        std::list<int> mylist(2, 200);        // list with 2 elements

        std::stack<int> first;                    // empty stack
        std::stack<int, std::vector<int> > second(myvector);         // stack initialized to copy of deque

        std::stack<int, std::list<int> > third;  // empty stack using list
        std::stack<int, std::list<int> > fourth(mylist);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR PUSH, EMPTY, TOP, POP" << RESET << std::endl;
        std::stack<int> mystack;
        int sum (0);
        for (int i=1;i<=10;i++) mystack.push(i);
        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }
        std::cout << "total std: " << sum << '\n';
    }
    {
        std::cout << BLUE << "ONE MORE CHECK FOR PUSH | POP | SIZE " << RESET << std::endl;
        std::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
    }
    {
        std::stack<int> ints;
        std::stack<int> reverse_ints;
        std::stack<int> int_equal;

        for (int i=0; i<5; i++)
            ints.push(i);
        for (int i=4; i>=0; i--)
            reverse_ints.push(i);
        for (int i=0; i<5; i++)
            int_equal.push(i);

        if (ints == int_equal)
            std::cout << "ints and inst_equal equal" << std::endl;

        if (ints < reverse_ints)
            std::cout << "ints less than reverse_ints" << std::endl;
        if (ints > reverse_ints)
            std::cout << "ints bigger than reverse_ints" << std::endl;
    }
}