#include <map>
#include <iostream>
#include <algorithm>
#define RED "\x1b[41;37m"
#define GREEN "\x1b[42;30m"
#define YELLOW "\x1b[43;30m"
#define BLUE "\x1b[44;30m"
#define RESET "\x1b[0m"

template <class T, class B>
void print_map_std(std::map<T, B> &ft_exmpl){
    typedef typename std::map<T, B>::iterator iterator;
    iterator ft_it = ft_exmpl.begin();
    iterator ft_it_end = ft_exmpl.end();
    std::cout << RED << "STD_MAP" << RESET << std::endl;
    while (ft_it != ft_it_end)
    {
        std::cout << "|" << ft_it->first << " " << ft_it->second << "|" << std::endl;
        ft_it++;
    }
}

int main() {
    {
        std::cout << BLUE << "CHECK FOR RANGE CONSTRUCTOR AND ITERATOR" << RESET << std::endl;
        typedef std::pair<float, int> value_type_std;
        value_type_std init[] = {std::make_pair(1.01f, 1), std::make_pair(2.02f, 2),
                                 std::make_pair(3.03f, 3), std::make_pair(4.04f, 4),
                                 std::make_pair(5.05f, 5), std::make_pair(6.06f, 6),
                                 std::make_pair(7.07f, 7), std::make_pair(8.08f, 8),
                                 std::make_pair(9.09f, 9), std::make_pair(10.10f, 10)};
        std::map<float, int> std_exmpl(init, init + 10);
        print_map_std(std_exmpl);
        std::cout << BLUE << "CHECK FOR COPY CONSTRUCTOR" << RESET << std::endl;
        std::map<float, int> std_copy(std_exmpl);
        print_map_std(std_copy);
    }
    {
        std::pair<int, int> pair1(5, 0);
        std::pair<int, int> pair2(10, 1);
        std::pair<int, int> pair3(4, 2);
        std::pair<int, int> pair4(7, 3);
        std::pair<int, int> pair5(15, 4);
        std::pair<int, int> pair6(20, 5);
        std::pair<int, int> pair7(17, 6);
        std::map<int, int> std_exmpl;
        std::cout << YELLOW << "| First insert |" << RESET << std::endl;
        std_exmpl.insert(pair1);
        print_map_std(std_exmpl);
        std::map<int, int>::iterator chit = std_exmpl.begin();
        std::cout << YELLOW << "| Second insert |" << RESET << std::endl;
        std_exmpl.insert(pair2);
        print_map_std(std_exmpl);
        std::cout << YELLOW << "| Third insert |" << RESET << std::endl;
        std_exmpl.insert(pair3);
        print_map_std(std_exmpl);
        std::cout << "iterator still valid -> " << (*chit).first << " Next element -> " << (++chit)->first << std::endl;
        std::cout << YELLOW << "| Fourth insert |" << RESET << std::endl;
        std_exmpl.insert(pair4);
        print_map_std(std_exmpl);
        std::cout << YELLOW << "| Fifth insert |" << RESET << std::endl;
        std_exmpl.insert(pair5);
        print_map_std(std_exmpl);
        std::cout << YELLOW << "| Sixth insert |" << RESET << std::endl;
        std_exmpl.insert(pair6);
        print_map_std(std_exmpl);
        std::cout << YELLOW << "| Seventh insert |" << RESET << std::endl;
        std_exmpl.insert(pair7);
        print_map_std(std_exmpl);
        std::cout << GREEN << "| SIZE |" << std_exmpl.size() << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR RANGE INSERT AND RANGE CONSTRUCTOR |" << RESET << std::endl;
        std::map<int, int>::iterator first = std_exmpl.begin();
        std::map<int, int>::iterator last = std_exmpl.end();
        std::map<int, int> std_exmpl_range_construct(first, last);
        print_map_std(std_exmpl_range_construct);
        std::cout << GREEN << "| SIZE |" << std_exmpl_range_construct.size() << RESET << std::endl;
        std::cout << GREEN << "| EMPTY |" << std_exmpl_range_construct.empty() << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR FIND |" << RESET << std::endl;
        std::cout << YELLOW << (*std_exmpl.find(17)).second << RESET << std::endl;
        std::cout << BLUE << " | CHECK FOR COUNT |" << RESET << std::endl;
        std::cout << YELLOW << "Matching key |" << std_exmpl.count(17) << RESET << std::endl;
        std::cout << YELLOW << "Non-matching key |" << std_exmpl.count(1413) << RESET << std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR EMPTY | OPERATOR [] | LOWER_BOUND | UPPER_BOUND" << RESET << std::endl;
        std::map<char, int> mymap;
        std::map<char, int>::iterator itlow, itup;

        std::cout << "Empty std -> " << mymap.empty() << std::endl;

        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;

        std::cout << "After [] Empty std -> " << mymap.empty() << std::endl;

        itlow = mymap.lower_bound('b');  // itlow points to b
        itup = mymap.upper_bound('d');   // itup points to e (not d!)

        while (itlow != itup) {
            std::cout << "MY MAP lower('b') upper('d') -> " << itlow->first << " => " << itlow->second << std::endl;
            itlow++;
        }
        std::cout << '\n';
    }
    {
        std::cout << BLUE << " | STD_EQUAL_RANGE |" << RESET << std::endl;
        std::map<char, int> mymap;


        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        mymap.value_comp();

        std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';

        std::cout << GREEN << "MAX_SIZE STD " << mymap.max_size() << RESET <<std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR WORKING WITH ALGROTIHM" << RESET << std::endl;
        std::map<char, int> std_mymap;

        std_mymap['a'] = 20;
        std_mymap['b'] = 40;
        std_mymap['c'] = 60;
        std_mymap['d'] = 80;
        std_mymap['e'] = 100;

        std::cout << std::min_element(std_mymap.begin(), std_mymap.end())->second << std::endl;
    }
    {
        std::cout << BLUE << "CHECK FOR WORKING WITH OBJECT" << RESET << std::endl;
        std::map<int, std::string> std_mymap;

        std::string first("abc");
        std::string second("zxc");
        std_mymap[1] = first;
        std_mymap[10] = second;

        std::cout << BLUE << "CHECK FOR MAP WITH OBJECTS" << RESET << std::endl;
        print_map_std(std_mymap);
        std::cout << YELLOW << "Erase 1 element" << RESET << std::endl;
        std_mymap.erase(1);
        print_map_std(std_mymap);
    }
    {
        std::cout << BLUE << "CHECK FOR INSERT KEY THAT ALREADY EXIST AND INSERT WITH A HINT" << RESET << std::endl;
        std::map<char, int> std_map;
        std_map['a'] = 1;
        std_map['b'] = 2;
        std_map['c'] = 3;
        std_map['e'] = 4;
        std_map['f'] = 5;
//        std::map<char, int>::const_iterator cit = std_map.begin(); //Check for const iterator
//        cit->second = 3; //Trying to assign new value to const iterator | compilation error
        std::pair<std::map<char, int>::iterator, bool> res;
        std::map<char, int>::iterator result;
        std::map<char, int>::iterator hint = std_map.find('b');
        res = std_map.insert(std::make_pair('a', 100));
        result = std_map.insert(hint, std::make_pair('d', 100));
        std::cout << "result " << result->first << " " << result->second << std::endl;
        std::cout << "bool -> " << res.second << "| key - > " << res.first->first
                  << " value -> " << res.first->second << " |" << std::endl;
        std::cout << BLUE << "CHECK FOR REVERSE_ITERATOR" << RESET << std::endl;
        std::map<char, int>::reverse_iterator it = std_map.rbegin();
        std::map<char, int>::reverse_iterator rend = std_map.rend();
        while (it != rend){
            std::cout << "| key - > " << it->first << " value -> " << it->second << " |" << std::endl;
            it++;
        }
    }
    {
        std::cout << BLUE << "CHECK FOR SWAP AND ITERATORS AFTER SWAP" << RESET << std::endl;
        std::map<char,int> foo,bar;
        foo['x']=100;
        foo['y']=200;
        bar['a']=11;
        bar['b']=22;
        bar['c']=33;
        std::map<char,int>::iterator fit = foo.begin();
        std::cout << "before swap foo iterator " << fit.operator->()->second << std::endl;
        foo.swap(bar);
        fit++;
        std::cout << "after swap and ++ foo iterator " << fit.operator->()->second << std::endl;

        std::cout << "foo contains:\n";
        for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR KEY COMP" << RESET << std::endl;
        std::map<char,int> mymap;
        std::map<char,int>::key_compare mycomp = mymap.key_comp();
        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;
        std::cout << "mymap contains:\n";
        char highest = mymap.rbegin()->first;     // key value of last element
        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );
        std::cout << '\n';
    }
    {
        std::cout << BLUE << "CHECK FOR VALUE COMP" << RESET << std::endl;
        std::map<char,int> mymap;
        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;
        std::cout << "mymap contains:\n";
        std::pair<char,int> highest = *mymap.rbegin();          // last element
        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
    {
        std::cout << BLUE << "CHECK FOR ERASE AND ERASE RANGE" << RESET << std::endl;
        std::map<char, int> mymap;

        mymap['a'] = 1;
        mymap['c'] = 3;
        mymap['e'] = 5;
        mymap['b'] = 2;
        mymap['d'] = 4;
        mymap['f'] = 6;
        mymap['g'] = 7;
        std::map<char, int>::iterator chit = mymap.find('b');
        std::cout << YELLOW << "BEFORE" << RESET << std::endl;
        print_map_std(mymap);
        std::cout << YELLOW << "AFTER ERASE KEY VALUE ('c')" << RESET << std::endl;
        mymap.erase('c');
        print_map_std(mymap);
        std::cout << "iterator still valid -> " << (*chit).first << " Next element -> " << (++chit)->first << std::endl;
        std::map<char, int>::iterator it = mymap.find('e');
        std::cout << YELLOW << "AFTER ERASE ITERATOR ('e')" << RESET << std::endl;
        mymap.erase(it);
        print_map_std(mymap);
        std::cout << YELLOW << "AFTER ERASE RANGE" << RESET << std::endl;
        mymap.erase(mymap.begin(), mymap.find('g'));
        print_map_std(mymap);
    }
    {
        std::cout << BLUE << "CHECH FOR GET ALLOCATOR" << RESET << std::endl;
        int psize;
        std::map<char,int> mymap;
        std::pair<const char,int>* p;
        // allocate an array of 5 elements using mymap's allocator:
        p=mymap.get_allocator().allocate(5);
        // assign some values to array
        psize = sizeof(std::map<char,int>::value_type)*5;
        std::cout << "The allocated array has a size of " << psize << " bytes.\n";
        mymap.get_allocator().deallocate(p,5);
    }
}