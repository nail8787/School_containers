#include <map>
#include "map.hpp"
#include <iostream>
#include <algorithm>
#define RED "\x1b[41;37m"
#define GREEN "\x1b[42;30m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;30m"
#define RESET "\x1b[0m"

template <class T, class B>
void print_map(ft::map<T, B> &ft_exmpl){
    typedef typename ft::map<T, B>::iterator iterator;
    iterator ft_it = ft_exmpl.begin();
    iterator ft_it_end = ft_exmpl.end();
    std::cout << RED << "FT_MAP" << RESET << std::endl;
    while (ft_it != ft_it_end)
    {
        std::cout << "|" << ft_it->first << " " << ft_it->second << "|" << std::endl;
        ft_it++;
    }
}

int main() {
    {
        std::cout << BLUE << "CHECK FOR RANGE CONSTRUCTOR AND ITERATOR" << RESET << std::endl;
        typedef ft::pair<float, int> value_type;
        value_type ft_init[] = {ft::make_pair(1.01f, 1), ft::make_pair(2.02f, 2),
                             ft::make_pair(3.03f, 3), ft::make_pair(4.04f, 4),
                             ft::make_pair(5.05f, 5), ft::make_pair(6.06f, 6),
                             ft::make_pair(7.07f, 7), ft::make_pair(8.08f, 8),
                             ft::make_pair(9.09f, 9), ft::make_pair(10.10f, 10)};
        ft::map<float, int> ft_exmpl(ft_init, ft_init + 10);
        print_map(ft_exmpl);
        std::cout << BLUE << "CHECK FOR COPY CONSTRUCTOR" << RESET << std::endl;
        ft::map<float, int> ft_copy(ft_exmpl);
        print_map(ft_copy);
    }
    {
        ft::pair<int, int> pair1(5, 0);
        ft::pair<int, int> pair2(10, 1);
        ft::pair<int, int> pair3(4, 2);
        ft::pair<int, int> pair4(7, 3);
        ft::pair<int, int> pair5(15, 4);
        ft::pair<int, int> pair6(20, 5);
        ft::pair<int, int> pair7(17, 6);
        ft::map<int, int> ft_exmpl;
        std::cout << YELLOW << "| First insert |" << RESET << std::endl;
        ft_exmpl.insert(pair1);
        ft::map<int, int>::iterator chit = ft_exmpl.begin();
        print_map(ft_exmpl);
        std::cout << YELLOW << "| Second insert |" << RESET << std::endl;
        ft_exmpl.insert(pair2);
        print_map(ft_exmpl);
        std::cout << YELLOW << "| Third insert |" << RESET << std::endl;
        ft_exmpl.insert(pair3);
        print_map(ft_exmpl);
        std::cout << "iterator still valid -> " << (*chit).first << " Next element -> " << (++chit)->first << std::endl;
        std::cout << YELLOW << "| Fourth insert |" << RESET << std::endl;
        ft_exmpl.insert(pair4);
        print_map(ft_exmpl);
        std::cout << YELLOW << "| Fifth insert |" << RESET << std::endl;
        ft_exmpl.insert(pair5);
        print_map(ft_exmpl);
        std::cout << YELLOW << "| Sixth insert |" << RESET << std::endl;
        ft_exmpl.insert(pair6);
        print_map(ft_exmpl);
        std::cout << YELLOW << "| Seventh insert |" << RESET << std::endl;
        ft_exmpl.insert(pair7);
        print_map(ft_exmpl);
        std::cout << GREEN << "| SIZE |" << ft_exmpl.size() << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR RANGE INSERT AND RANGE CONSTRUCTOR |" << RESET << std::endl;
        ft::map<int, int>::iterator first = ft_exmpl.begin();
        ft::map<int, int>::iterator last = ft_exmpl.end();
        ft::map<int, int> ft_exmpl_range_construct(first, last);
        print_map(ft_exmpl_range_construct);
        std::cout << GREEN << "| SIZE |" << ft_exmpl_range_construct.size() << RESET << std::endl;
        std::cout << GREEN << "| EMPTY |" << ft_exmpl_range_construct.empty() << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR FIND |" << RESET << std::endl;
        std::cout << YELLOW << (*ft_exmpl.find(17)).second << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR COUNT |" << RESET << std::endl;
        std::cout << YELLOW << "Matching key |" << ft_exmpl.count(17) << RESET << std::endl;
        std::cout << YELLOW << "Non-matching key |" << ft_exmpl.count(1413) << RESET << std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR EMPTY | OPERATOR [] | LOWER_BOUND | UPPER_BOUND" << RESET << std::endl;
        ft::map<char, int> ft_mymap;
        ft::map<char, int>::iterator ft_itlow, ft_itup;

        std::cout << "Empty ft -> " << ft_mymap.empty() << std::endl;

        ft_mymap['a'] = 20;
        ft_mymap['b'] = 40;
        ft_mymap['c'] = 60;
        ft_mymap['d'] = 80;
        ft_mymap['e'] = 100;

        std::cout << "After [] Empty ft -> " << ft_mymap.empty() << std::endl;

        ft_itlow = ft_mymap.lower_bound('b');  // itlow points to b
        ft_itup = ft_mymap.upper_bound('d');   // itup points to e (not d!)

        while (ft_itlow != ft_itup) {
            std::cout << "FT MAP lower('b') upper('d') -> " << ft_itlow->first << " => " << ft_itlow->second
                      << std::endl;
            ft_itlow++;
        }
    }
    {
        std::cout << BLUE << " | FT_EQUAL_RANGE |" << RESET << std::endl;
        ft::map<char, int> ft_mymap;

        ft_mymap['a'] = 10;
        ft_mymap['b'] = 20;
        ft_mymap['c'] = 30;

        ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ft_ret;
        ft_ret = ft_mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ft_ret.first->first << " => " << ft_ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ft_ret.second->first << " => " << ft_ret.second->second << '\n';

        std::cout << GREEN << "MAX_SIZE FT  " << ft_mymap.max_size() << RESET << std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR WORKING WITH ALGROTIHM" << RESET << std::endl;
        ft::map<char, int> ft_mymap;

        ft_mymap['a'] = 20;
        ft_mymap['b'] = 40;
        ft_mymap['c'] = 60;
        ft_mymap['d'] = 80;
        ft_mymap['e'] = 100;

        std::cout << std::min_element(ft_mymap.begin(), ft_mymap.end())->second << std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR WORKING WITH OBJECT" << RESET << std::endl;
        ft::map<int, std::string> ft_mymap;

        std::string first("abc");
        std::string second("zxc");
        ft_mymap[1] = first;
        ft_mymap[10] = second;

        print_map(ft_mymap);
        std::cout << YELLOW << "Erase 1 element" << RESET << std::endl;
        ft_mymap.erase(1);
        print_map(ft_mymap);
    }
    {
        std::cout << BLUE << "CHECK FOR INSERT KEY THAT ALREADY EXIST AND INSERT WITH A HINT" << RESET << std::endl;
        ft::map<char, int> ft_map;
        ft_map['a'] = 1;
        ft_map['b'] = 2;
        ft_map['c'] = 3;
        ft_map['e'] = 4;
        ft_map['f'] = 5;
//        ft::map<char, int>::const_iterator cit = ft_map.begin(); //Check for const iterator
//        cit->second = 3; //Trying to assign new value to const iterator | compilation error
        ft::pair<ft::map<char, int>::iterator, bool> res;
        ft::map<char, int>::iterator result;
        ft::map<char, int>::iterator hint = ft_map.find('b');
        res = ft_map.insert(ft::make_pair('a', 100));
        result = ft_map.insert(hint, ft::make_pair('d', 100));
        std::cout << "result " << result->first << " " << result->second << std::endl;
        std::cout << "bool -> " << res.second << "| key - > " << res.first->first
                  << " value -> " << res.first->second << " |" << std::endl;
        std::cout << BLUE << "CHECK FOR REVERSE_ITERATOR" << RESET << std::endl;
        ft::map<char, int>::reverse_iterator it = ft_map.rbegin();
        ft::map<char, int>::reverse_iterator rend = ft_map.rend();
        while (it != rend){
            std::cout << "| key - > " << it->first << " value -> " << it->second << " |" << std::endl;
            it++;
        }
    }
    {
        std::cout << BLUE << "CHECK FOR SWAP AND ITERATORS AFTER SWAP" << RESET << std::endl;
        ft::map<char,int> foo,bar;
        foo['x']=100;
        foo['y']=200;
        bar['a']=11;
        bar['b']=22;
        bar['c']=33;
        ft::map<char,int>::iterator fit = foo.begin();
        std::cout << "before swap foo iterator " << fit.operator->()->second << std::endl;
        foo.swap(bar);
        fit++;
        std::cout << "after swap and ++ foo iterator " << fit.operator->()->second << std::endl;

        std::cout << "foo contains:\n";
        for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR KEY COMP" << RESET << std::endl;
        ft::map<char,int> mymap;
        ft::map<char,int>::key_compare mycomp = mymap.key_comp();
        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;
        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );
        std::cout << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR VALUE COMP" << RESET << std::endl;
        ft::map<char,int> mymap;
        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;
        std::cout << "mymap contains:\n";
        ft::pair<char,int> highest = *mymap.rbegin();          // last element
        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
    {
        std::cout << BLUE << "CHECK FOR ERASE AND ERASE RANGE" << RESET << std::endl;
        ft::map<char, int> mymap;

        mymap['a'] = 1;
        mymap['c'] = 3;
        mymap['e'] = 5;
        mymap['b'] = 2;
        mymap['d'] = 4;
        mymap['f'] = 6;
        mymap['g'] = 7;
        ft::map<char, int>::iterator chit = mymap.find('b');
        std::cout << YELLOW << "BEFORE" << RESET << std::endl;
        print_map(mymap);
        std::cout << YELLOW << "AFTER ERASE KEY VALUE ('c')" << RESET << std::endl;
        mymap.erase('c');
        print_map(mymap);
        std::cout << "iterator still valid -> " << (*chit).first << " Next element -> " << (++chit)->first << std::endl;
        ft::map<char, int>::iterator it = mymap.find('e');
        std::cout << YELLOW << "AFTER ERASE ITERATOR ('e')" << RESET << std::endl;
        mymap.erase(it);
        print_map(mymap);
        std::cout << YELLOW << "AFTER ERASE RANGE" << RESET << std::endl;
        mymap.erase(mymap.begin(), mymap.find('g'));
        print_map(mymap);
    }
    {
        std::cout << BLUE << "CHECK FOR GET ALLOCATOR" << RESET << std::endl;
        int psize;
        ft::map<char,int> ft_mymap;
        ft::pair<const char,int>* ft_p;
        // allocate an array of 5 elements using mymap's allocator:
        ft_p=ft_mymap.get_allocator().allocate(5);
        // assign some values to array
        psize = sizeof(std::map<char,int>::value_type)*5;
        std::cout << "The allocated array has a size of " << psize << " bytes.\n";
        ft_mymap.get_allocator().deallocate(ft_p,5);
    }
}