#include <list>
#include <iostream>
#include "list.hpp"
#include <cstdlib>
#include <unistd.h>
#include <algorithm>

template <typename T>
void myfunc(T i){
    std::cout << " " << i ;
}

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    return ( first.length() < second.length() );
}
// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// compare only integral part:
bool mycomparison (double first, double second) { return ( int(first)<int(second) ); }

// a predicate implemented as a class:
struct is_odd {
    bool operator() (const int& value) { return (value%2)==1; }
};

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

void output(std::list<int>::iterator std_start, std::list<int>::iterator std_end, ft::list<int>::iterator ft_start, ft::list<int>::iterator ft_end)
{
    std::cout << "\x1b[44;30m|...~LIST~...|\x1b[0m" << std::endl;
    int count = 0;
    while (std_start != std_end){
        std::cout << *std_start << " | ";
        ++std_start;
        count++;
        if ((count % 25) == 0)
            std::cout << " * 25 elements" << std::endl;
    }
    std::cout << std::endl;
    count = 0;
    std::cout << "\x1b[44;30m|...~FT_LIST~...|\x1b[0m" << std::endl;
    while (ft_start != ft_end){
        std::cout << *ft_start << " | ";
        ++ft_start;
        count++;
        if ((count % 25) == 0)
            std::cout << " * 25 elements" << std::endl;
    }
    std::cout << std::endl;
}

template <typename type>
void output_ft_one(ft::list<type> &ft_exmpl, int number)
{
    int count = 0;
    typename ft::list<type>::iterator ft_start = ft_exmpl.begin();
    typename ft::list<type>::iterator ft_end = ft_exmpl.end();
    std::cout << "\x1b[44;30m|...~FT_LIST" << number << "~...|\x1b[0m" << std::endl;
    while (ft_start != ft_end){
        std::cout << *ft_start << " | ";
        ++ft_start;
        count++;
        if ((count % 25) == 0)
            std::cout << " * 25 elements" << std::endl;
    }
    std::cout << std::endl;
}

template <typename type>
void output_std_one(std::list<type> &std_exmpl, int number)
{
    int count = 0;
    typename std::list<type>::iterator std_start = std_exmpl.begin();
    typename std::list<type>::iterator std_end = std_exmpl.end();
    std::cout << "\x1b[44;30m|...~LIST" << number << "~...|\x1b[0m" << std::endl;
    while (std_start != std_end){
        std::cout << *std_start << " | ";
        ++std_start;
        count++;
        if ((count % 25) == 0)
            std::cout << " * 25 elements" << std::endl;
    }
    std::cout << std::endl;
}

template <typename Iterator>
Iterator move_iterator(int n, std::string plus_or_minus, Iterator iter)
{
    if (plus_or_minus == "plus"){
        for (int i = 1; i < n; ++i)
            ++iter;
    }
    else if (plus_or_minus == "minus"){
        for (int i = 1; i < n; ++i)
            --iter;
    }
    else
        std::cout << "WRONG ARGUMENT FOR INCREMENT OR DECREMENT" << std::endl;
    return iter;
}


int main()
{
    {
        //Defaut constructor, front (need to add back), push_back
        ft::list<int> ft_exmpl;
        std::list<int> std_exmpl;

        std::cout << "\x1b[41;30m|....Default constructor....|\x1b[0m" << std::endl;
        std::cout << "\x1b[42;30mCHECK FOR SIZE, MAX_SIZE AND FRONT ELEMENT\x1b[0m"<< std::endl;
        std::cout << "ft_max_size --> " << ft_exmpl.max_size() << std::endl;
        std::cout << "std_max_size -> " << std_exmpl.max_size() << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "list front()-----> " << std_exmpl.front() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        std::cout << "ft_list front()--> " << ft_exmpl.front() << std::endl;
        std::cout << "\x1b[42;30mCHECK FOR PUSH_BACK\x1b[0m" << std::endl;
        for (int i = 1; i <= 100; ++i)
            std_exmpl.push_back(i);
        for (int i = 1; i <= 100; ++i)
            ft_exmpl.push_back(i);
        ft::list<int>::iterator ft_start = ft_exmpl.begin();
        ft::list<int>::iterator ft_end = ft_exmpl.end();
        std::list<int>::iterator std_start = std_exmpl.begin();
        std::list<int>::iterator std_end = std_exmpl.end();
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        output(std_start, std_end, ft_start, ft_end);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR RANGE AND COPY CONSTRUCTOR\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30m|....Range constructor....|\x1b[0m" << std::endl;
        float values[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f};
        ft::list<int> ft_exmpl(values, values + 10);
        std::list<int> std_exmpl(values, values + 10);
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
        ft::list<int> ft_exmpl_copy(ft_exmpl);
        std::list<int> std_exmpl_copy(std_exmpl);
        output_ft_one(ft_exmpl_copy, 2);
        output_std_one(std_exmpl_copy, 2);
    }
    {
        //Iterators and inserts
        std::cout << "\x1b[41;30m|....Fill constructor....|\x1b[0m" << std::endl;
        std::cout << "\x1b[42;30mCHECK FOR SIZE AND EVERY ELEMENTS OUTPUT (via iterators)\x1b[0m" << std::endl;
        ft::list<int> ft_exmpl(100, 1);
        std::list<int> std_exmpl(100, 1);
        ft::list<int>::iterator ft_start = ft_exmpl.begin();
        ft::list<int>::iterator ft_end = ft_exmpl.end();
        std::list<int>::iterator std_start = std_exmpl.begin();
        std::list<int>::iterator std_end = std_exmpl.end();
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        output(std_start, std_end, ft_start, ft_end);
        std::cout << "\x1b[42;30mCHECK FOR INSERT (1)(2)(3)\x1b[0m" << std::endl;
        std::cout << "\x1b[42;30mCHECK(1) 1 element 1 value\x1b[0m" << std::endl;
        ft_start = move_iterator(2, "plus", ft_start);
        std_start = move_iterator(2, "plus", std_start);
        ft_exmpl.insert(ft_start, 1234);
        std_exmpl.insert(std_start, 1234);
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        output(std_start, std_end, ft_start, ft_end);
        std::cout << "\x1b[42;30mCHECK(2) n elements 1 value\x1b[0m" << std::endl;
        ft_start = move_iterator(10, "plus", ft_start);
        std_start = move_iterator(10, "plus", std_start);
        ft_exmpl.insert(ft_start, 10,3); // Как сделать, чтобы он выбирал нужную перегрузку
        std_exmpl.insert(std_start, 10, 3);
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        output(std_start, std_end, ft_start, ft_end);
    }
    {
        //INSERT RANGE
        ft::list<int> ft_exmpl;
        std::list<int> std_exmpl;

        std::cout << "\x1b[42;30mCHECK FOR INSERT RANGE\x1b[0m" << std::endl;
        for (int i = 1; i <= 100; ++i)
            std_exmpl.push_back(i);
        for (int i = 1; i <= 100; ++i)
            ft_exmpl.push_back(i);
        ft::list<int>::iterator ft_pos = ft_exmpl.begin();
        ft::list<int>::iterator ft_start = ft_exmpl.begin();
        ft::list<int>::iterator ft_end = ft_exmpl.end();
        std::list<int>::iterator std_pos = std_exmpl.begin();
        std::list<int>::iterator std_start = std_exmpl.begin();
        std::list<int>::iterator std_end = std_exmpl.end();
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output(std_start, std_end, ft_start, ft_end);
        ft_pos = move_iterator(15, "plus", ft_pos);
        std_pos = move_iterator(15, "plus", std_pos);
        std_start = move_iterator(50, "plus", std_start);
        ft_start = move_iterator(50, "plus", ft_start);
        ft_exmpl.insert(ft_pos, ft_start, ft_end);
        std_exmpl.insert(std_pos, std_start, std_end);
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        output(std_start, std_end, ft_start, ft_end);
        std::cout << "\x1b[42;30mCHECK FOR ERASE\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_pos = ft_exmpl.begin();
        std_pos = std_exmpl.begin();
        ft_pos = move_iterator(15, "plus", ft_pos);
        std_pos = move_iterator(15, "plus", std_pos);
        ft_exmpl.erase(ft_pos);
        std_exmpl.erase(std_pos);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        output(std_start, std_end, ft_start, ft_end);
        std::cout << "\x1b[42;30mCHECK FOR ERASE RANGE\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_pos = ft_exmpl.begin();
        std_pos = std_exmpl.begin();
        ft_pos = move_iterator(15, "plus", ft_pos);
        std_pos = move_iterator(15, "plus", std_pos);
        ft_exmpl.erase(ft_start, ft_pos);
        std_exmpl.erase(std_start, std_pos);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        output(std_start, std_end, ft_start, ft_end);
        std::cout << "\x1b[42;30mCHECK FOR RESIZE (1 parameter)\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_exmpl.resize(50);
        std_exmpl.resize(50);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        output(std_start, std_end, ft_start, ft_end); //потом можно убрать наверное
        std::cout << "\x1b[42;30mCHECK FOR RESIZE (2 parameters)\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_exmpl.resize(100, 11);
        std_exmpl.resize(100, 11);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "list size -------> " << std_exmpl.size() << std::endl;
        std::cout << "ft_list size ----> " << ft_exmpl.size() << std::endl;
        ft_start = ft_exmpl.begin();
        std_start = std_exmpl.begin();
        output(std_start, std_end, ft_start, ft_end); //потом можно убрать наверное
    }
    {
        ft::list<int> ft_exmpl1(3, 100);
        ft::list<int> ft_exmpl2(5, 200);
        std::list<int> std_exmpl1(3,100);
        std::list<int> std_exmpl2(5,200);
        std::cout << "\x1b[42;30mCHECK FOR SWAP\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list1 size -------> " << std_exmpl1.size() << std::endl;
        std::cout << "ft_list1 size ----> " << ft_exmpl1.size() << std::endl;
        std::cout << "list2 size -------> " << std_exmpl2.size() << std::endl;
        std::cout << "ft_list2 size ----> " << ft_exmpl2.size() << std::endl;
        output_ft_one(ft_exmpl1, 1);
        output_ft_one(ft_exmpl2, 2);
        output_std_one(std_exmpl1, 1);
        output_std_one(std_exmpl2, 2);
        ft_exmpl1.swap(ft_exmpl2);
        std_exmpl1.swap(std_exmpl2);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "list1 size -------> " << std_exmpl1.size() << std::endl;
        std::cout << "ft_list1 size ----> " << ft_exmpl1.size() << std::endl;
        std::cout << "list2 size -------> " << std_exmpl2.size() << std::endl;
        std::cout << "ft_list2 size ----> " << ft_exmpl2.size() << std::endl;
        output_ft_one(ft_exmpl1, 1);
        output_ft_one(ft_exmpl2, 2);
        output_std_one(std_exmpl1, 1);
        output_std_one(std_exmpl2, 2);
        std::cout << "\x1b[42;30mCHECK FOR CLEAR\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "list1 size -------> " << std_exmpl1.size() << std::endl;
        std::cout << "ft_list1 size ----> " << ft_exmpl1.size() << std::endl;
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        ft_exmpl1.clear();
        std_exmpl1.clear();
        std::cout << "list1 size -------> " << std_exmpl1.size() << std::endl;
        std::cout << "ft_list1 size ----> " << ft_exmpl1.size() << std::endl;
        output_ft_one(ft_exmpl1, 1);
        output_std_one(std_exmpl1, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR ASSIGN\x1b[0m" << std::endl;
        ft::list<int> first;
        ft::list<int> second;
        first.assign (7,100);
        second.assign (first.begin(),first.end());
        output_ft_one(first, 1);
        output_ft_one(second, 2);
        int myints[]={1776,7,4,7,10,133,423,33,21,54,6};
        first.assign (myints,myints+11);            // assigning from array
        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        output_ft_one(first, 1);
        output_ft_one(second, 2);
        std::cout << "\x1b[42;30mCHECK FOR REMOVE\x1b[0m" << std::endl;
        first.remove(7);
        std::cout << "Size of first: " << int (first.size()) << '\n';
        output_ft_one(first, 1);
        std::cout << "\x1b[42;30mCHECK FOR REMOVE_IF\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mAFTER REMOVING SINGLE DIGITS VALUES\x1b[0m" << std::endl;
        first.remove_if(single_digit);
        output_ft_one(first, 1);
        std::cout << "\x1b[41;30mAFTER REMOVING ODD VALUES\x1b[0m" << std::endl;
        first.remove_if(is_odd());
        output_ft_one(first, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR REVERSE\x1b[0m" << std::endl;
        ft::list<int> ft_exmpl;
        std::list<int> std_exmpl;
        for (int i = 1; i <= 101; ++i)
            std_exmpl.push_back(i);
        for (int i = 1; i <= 101; ++i)
            ft_exmpl.push_back(i);
//        ft::list<int>::iterator ft_start = ft_exmpl.begin();
//        ft::list<int>::iterator ft_second = ft_exmpl.begin();
//        std::list<int>::iterator std_start = std_exmpl.begin();
//        ft_start = move_iterator(15, "plus", ft_start);
//        ft_second = move_iterator(5, "plus", ft_second);
//        std_start = move_iterator(15, "plus", std_start);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
        std_exmpl.reverse();
        ft_exmpl.reverse();
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
//        ft_exmpl.swap(ft_start.operator->(), ft_second.operator->());
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR UNIQUE\x1b[0m" << std::endl;
        ft::list<int> ft_exmpl;
        std::list<int> std_exmpl;
        for (int i = 1; i <= 10; ++i)
            std_exmpl.push_back(i);
        for (int i = 11; i <= 20; ++i)
            std_exmpl.push_back(0);
        for (int i = 21; i <= 100; ++i)
            std_exmpl.push_back(i);
        for (int i = 1; i <= 10; ++i)
            ft_exmpl.push_back(i);
        for (int i = 11; i <= 20; ++i)
            ft_exmpl.push_back(0);
        for (int i = 21; i <= 100; ++i)
            ft_exmpl.push_back(i);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
        std_exmpl.unique();
        ft_exmpl.unique();
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR UNIQUE WITH OUTSOURCE BINARY PREDICATE\x1b[0m" << std::endl;
        double mydoubles[]={ 2.41,  2.72, 3.95, 4.55, 12.33, 12.77, 12.77, 72.35, 72.45, 124.134, 123.444 };
        ft::list<double> ft_exmpl;
        std::list<double> std_exmpl;
        ft_exmpl.assign(mydoubles, mydoubles+11); //надо будет потом переделать в конструктор!
        std_exmpl.assign(mydoubles, mydoubles+11);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
        ft_exmpl.unique(same_integral_part);
        std_exmpl.unique(same_integral_part);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_exmpl, 1);
        output_std_one(std_exmpl, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR SPLICE (SINGLE ELEMENT)\x1b[0m" << std::endl;
        ft::list<int> mylist1, mylist2;
        std::list<int> stdlist1, stdlist2;
        ft::list<int>::iterator it;
        std::list<int>::iterator stdit;
        for (int i=1; i<=6; ++i)
            mylist1.push_back(i);
        for (int i=1; i<=9; ++i)
            mylist2.push_back(i*10);
        for (int i=1; i<=6; ++i)
            stdlist1.push_back(i);
        for (int i=1; i<=9; ++i)
            stdlist2.push_back(i*10);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "ft_list1 size ----> " << mylist1.size() << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        output_ft_one(mylist1, 1);
        output_ft_one(mylist2, 2);
        std::cout << "std_list1 size ----> " << stdlist1.size() << std::endl;
        std::cout << "std_list2 size ----> " << stdlist2.size() << std::endl;
        output_std_one(stdlist1, 1);
        output_std_one(stdlist2, 2);
        it = mylist1.begin();
        ++it;
        stdit = stdlist1.begin();
        ++stdit;
        mylist2.splice (move_iterator(2, "plus", mylist2.begin()),mylist1, it);
        stdlist2.splice (move_iterator(2, "plus", stdlist2.begin()), stdlist1, stdit);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "ft_list1 size ----> " << mylist1.size() << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        output_ft_one(mylist1, 1);
        output_ft_one(mylist2, 2);
        std::cout << "std_list1 size ----> " << stdlist1.size() << std::endl;
        std::cout << "std_list2 size ----> " << stdlist2.size() << std::endl;
        output_std_one(stdlist1, 1);
        output_std_one(stdlist2, 2);
        std::cout << "\x1b[42;30mCHECK FOR SPLICE (RANGE)\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        std::cout << "std_list2 size ----> " << stdlist2.size() << std::endl;
        output_std_one(stdlist2, 2);
        output_ft_one(mylist2, 2);
        stdit = stdlist2.begin();
        stdit = move_iterator(5, "plus", stdit);
        stdlist2.splice(stdlist2.begin(), stdlist2, stdit, stdlist2.end());
        it = mylist2.begin();
        it = move_iterator(5,"plus", it);
        mylist2.splice(mylist2.begin(), mylist2, it, mylist2.end());
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        std::cout << "std_list2 size ----> " << stdlist2.size() << std::endl;
        output_std_one(stdlist2, 2);
        output_ft_one(mylist2, 2);
        std::cout << "\x1b[42;30mCHECK FOR SPLICE (ALL)\x1b[0m" << std::endl;
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        std::cout << "ft_list1 size ----> " << mylist1.size() << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        output_ft_one(mylist1, 1);
        output_ft_one(mylist2, 2);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        it = mylist2.begin();
        ++it;
        mylist2.splice(it, mylist1);
        std::cout << "ft_list1 size ----> " << mylist1.size() << std::endl;
        std::cout << "ft_list2 size ----> " << mylist2.size() << std::endl;
        output_ft_one(mylist1, 1);
        output_ft_one(mylist2, 2);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR MERGE\x1b[0m" << std::endl;
        int list[] = {1, 10, 14, 32};
        int mylist[] = {4, 6, 7, 15};
        ft::list<int>my;
        my.assign(mylist, mylist+4);
        ft::list<int> mylist2;
        mylist2.assign(list,list+4);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output_ft_one(my, 1);
        output_ft_one(mylist2, 2);
        my.merge(mylist2);
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        output_ft_one(my, 1);
        output_ft_one(mylist2, 2);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR SORT\x1b[0m" << std::endl;
        srand(time(0));
        int number = 1000;
        int list[number];
        for (int i = 0; i < number; ++i)
            list[i] = rand() % 100;
//        int list[] = {84, 47, 43, 98, 86, 90, 42, 10, 6, 23};
        ft::list<int>ft_list;
        ft_list.assign(list, list + number);
        std::cout << "\x1b[41;30mBEFORE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_list, 1);
        ft_list.sort();
        std::cout << "\x1b[41;30mAFTER\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_list, 1);
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR REVERSE_ITERATOR\x1b[0m" << std::endl;
        int values[] = {1, 2, 3};
        const ft::list<int> ft_exmpl(values, values + 3);
        const std::list<int> std_exmpl(values, values + 3);
        for (ft::list<int>::const_reverse_iterator ft_riter = ft_exmpl.rbegin(); ft_riter != ft_exmpl.rend(); ft_riter++)
            std::cout << "| " << *ft_riter;
        std::cout << std::endl;
        for (std::list<int>::const_reverse_iterator std_riter = std_exmpl.rbegin(); std_riter != std_exmpl.rend(); std_riter++)
            std::cout << "| " << *std_riter;
        std::cout << std::endl;
    }
    {
        std::cout << "\x1b[42;30mCHECK FOR RELATIONAL OPERATORS\x1b[0m" << std::endl;
        std::cout << "\x1b[43;30m   OPERATOR (==)   \x1b[0m" << std::endl;
        int values[] = {1, 2, 3};
        ft::list<int> ft_1(values, values + 3);
        ft::list<int> ft_2(values, values + 3);
        std::cout << "\x1b[41;30mEQUAL\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 == ft_2) << std::endl;
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mNOT EQUAL BY SIZE AND VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 == ft_2) << std::endl;
        ft_2.pop_back();
        ft_2.pop_back();
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mEQUAL BY SIZE BUT NOT BY VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 == ft_2) << std::endl;
    }
    {
        std::cout << "\x1b[43;30m   OPERATOR (!=)   \x1b[0m" << std::endl;
        int values[] = {1, 2, 3};
        ft::list<int> ft_1(values, values + 3);
        ft::list<int> ft_2(values, values + 3);
        std::cout << "\x1b[41;30m EQUAL\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 != ft_2) << std::endl;
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mNOT EQUAL BY SIZE AND VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 != ft_2) << std::endl;
        ft_2.pop_back();
        ft_2.pop_back();
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mEQUAL BY SIZE BUT NOT BY VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 != ft_2) << std::endl;
    }
    {
        std::cout << "\x1b[43;30m   OPERATOR (<)   \x1b[0m" << std::endl;
        int values[] = {1, 2, 3};
        ft::list<int> ft_1(values, values + 3);
        ft::list<int> ft_2(values, values + 3);
        std::cout << "\x1b[41;30m EQUAL\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 < ft_2) << std::endl;
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mFIRST LESS THAN SECOND BY SIZE AND VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 < ft_2) << std::endl;
        ft_2.pop_back();
        ft_2.pop_back();
        ft_2.push_back(4);
        std::cout << "\x1b[41;30mFIRST LESS THAN SECOND BY VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_1 < ft_2) << std::endl;
        std::cout << "\x1b[41;30mSECOND MORE THAN FIRST BY VALUE\x1b[0m" << std::endl << std::endl;
        output_ft_one(ft_1, 1);
        output_ft_one(ft_2, 2);
        std::cout << std::endl << "RESULT --> " << (ft_2 < ft_1) << std::endl;
    }
    {
        int values[] = {10, 20 ,30};
        ft::list<int> a(values, values + 3);
        ft::list<int> b(values, values + 3);
        ft::list<int> c;
        c.push_back(30);
        c.push_back(20);
        c.push_back(10);

        if (a==b) std::cout << "a and b are equal\n";
        if (b!=c) std::cout << "b and c are not equal\n";
        if (b<c) std::cout << "b is less than c\n";
        if (c>b) std::cout << "c is greater than b\n";
        if (a<=b) std::cout << "a is less than or equal to b\n";
        if (a>=b) std::cout << "a is greater than or equal to b\n";
    }
    {
        ft::list<int> x(10, 123);
        ft::list<int> y(5, 999);
        output_ft_one(x, 1);
        output_ft_one(y, 2);
        ft::swap(x,y);
        output_ft_one(x, 1);
        output_ft_one(y, 2);
    }
    {
        std::cout << "\x1b[43;30m   SORT WITH PREDICATE   \x1b[0m" << std::endl;
        std::list<std::string> mylist;
        std::list<std::string>::iterator it;
        mylist.push_back ("one");
        mylist.push_back ("two");
        mylist.push_back ("Three");
        mylist.sort();
        std::cout << "std_mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        mylist.sort(compare_nocase);
        std::cout << "std_mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        
        ft::list<std::string> ft_mylist;
        ft::list<std::string>::iterator ft_it;
        ft_mylist.push_back ("one");
        ft_mylist.push_back ("two");
        ft_mylist.push_back ("Three");
        ft_mylist.sort();
        std::cout << "ft_mylist contains:";
        for (ft_it=ft_mylist.begin(); ft_it!=ft_mylist.end(); ++ft_it)
            std::cout << ' ' << *ft_it;
        std::cout << '\n';
        ft_mylist.sort(compare_nocase);
        std::cout << "ft_mylist contains:";
        for (ft_it=ft_mylist.begin(); ft_it!=ft_mylist.end(); ++ft_it)
            std::cout << ' ' << *ft_it;
        std::cout << '\n';
    }
    {
        std::cout << "\x1b[43;30m   MERGE WITH PREDICATE   \x1b[0m" << std::endl;
        std::list<double> first, second;

        first.push_back (3.1);
        first.push_back (2.2);
        first.push_back (2.9);

        second.push_back (3.7);
        second.push_back (7.1);
        second.push_back (1.4);

        first.sort();
        second.sort();

        first.merge(second);

        // (second is now empty)

        second.push_back (2.1);

        first.merge(second,mycomparison);

        std::cout << "std_first contains:";
        for (std::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        std::cout << "\x1b[44;30m| MERGE FT_ONE |\x1b[0m" << std::endl;
        ft::list<double> ft_first, ft_second;

        ft_first.push_back (3.1);
        ft_first.push_back (2.2);
        ft_first.push_back (2.9);

        ft_second.push_back (3.7);
        ft_second.push_back (7.1);
        ft_second.push_back (1.4);

        ft_first.sort();
        ft_second.sort();

        ft_first.merge(ft_second);

        // (ft_second is now empty)

        ft_second.push_back (2.1);

        ft_first.merge(ft_second,mycomparison);

        std::cout << "ft_first contains:";
        for (ft::list<double>::iterator ft_it=ft_first.begin(); ft_it!=ft_first.end(); ++ft_it)
            std::cout << ' ' << *ft_it;
        std::cout << '\n';
    }
    {
        std::cout << "\x1b[43;30m  CHECK FOR ALGORITHMS   \x1b[0m" << std::endl;
        std::string abc("abc");
        ft::list<std::string> ft_list(5, abc);
        std::for_each(ft_list.begin(), ft_list.end(), myfunc<std::string>);
        std::cout << std::endl;
    }
}
