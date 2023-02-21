/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_containers.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:14 by hepple            #+#    #+#             */
/*   Updated: 2023/02/21 15:59:49 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <string>

#include <map>
#include <set>
#include <stack>
#include <vector>


#ifdef FT
# include "../include/map.hpp"
# include "../include/set.hpp"
# include "../include/stack.hpp"
# include "../include/vector.hpp"
#endif


#ifdef FT
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

/* *** P R I N T ************************************************************ */

template < typename T >
void print_line(T const &t)
{
	std::cout << t << std::endl;
}

void print_bool(std::string const &name, bool b)
{
	std::cout << name << ": ";
	if (b)
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << std::endl;
}

template < typename T >
void print_value(std::string const &name, T const &val)
{
	std::cout << name << ": " << val << std::endl;
}

void print_title(std::string title)
{
	std::cout << title << std::endl << std::endl;
}

void print_seperator()
{
	std::cout << "- - - - - - - - - - - - - - - - - - - -"<< std::endl << std::endl;
}

template < typename T >
void print_vector(NAMESPACE::vector<T> const &v, std::string name = "vector")
{
	print_line(name + ":");

	print_value("size", v.size());

	print_value("capacity", v.capacity());

	print_value("max_size", v.max_size());

	print_bool("empty", v.empty());

	if (v.size() > 0)
		print_value("front", v.front());
	else
		print_line("front: -");

	if (v.size() > 0)
		print_value("back", v.back());
	else
		print_line("back: -");

	print_line("content by index:");
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << name << "[" << i << "] = " << v[i] << std::endl;

	print_line("content by iterator:");
	for (typename NAMESPACE::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << name << "[" << it - v.begin() << "] = " << *it << std::endl;

	print_line("");
}

// template < typename Key, typename T, typename Compare >
// void print_map(NAMESPACE::map<Key, T, Compare> m)
// {
// 	for (typename NAMESPACE::map<Key, T, Compare>::iterator it = m.begin(); it != m.end(); ++it)
// 		std::cout << "->" << it->first << ", " << it->second << "<-" << std::endl;
// }

// template < typename T, typename Compare >
// void print_set(NAMESPACE::vector<T> s)
// {
// 	for (typename NAMESPACE::set<T>::iterator it = s.begin(); it != s.end(); ++it)
// 		std::cout << "->" << *it << "<-" << std::endl;
// }


/* *** V E C T O R ********************************************************** */

void vector_construction_and_assignment()
{
	print_title("VECTOR - CONSTRUCTION AND ASSIGNMENT");

	{
		NAMESPACE::vector<int> v1;
		print_vector(v1, "v1");

		NAMESPACE::vector<int> v2(3, 42);
		print_vector(v2, "v2");

		NAMESPACE::vector<int> v3(v2);
		print_vector(v3, "v3");
		
		NAMESPACE::vector<int> v4 = v3;
		print_vector(v4, "v4");

		NAMESPACE::vector<int> v5;
		print_vector(v5, "v5");
		v5.push_back(7);
		v5.push_back(-1);
		print_vector(v5, "v5");
		v5[0] = 8;
		print_vector(v5, "v5");

		NAMESPACE::vector<int> v6(v5.begin(), v5.end());
		print_vector(v6, "v6");
	}

	{
		NAMESPACE::vector<std::string> v1;
		print_vector(v1, "v1");

		NAMESPACE::vector<std::string> v2(3, "Blub");
		print_vector(v2, "v2");

		NAMESPACE::vector<std::string> v3(v2);
		print_vector(v3, "v3");
		
		NAMESPACE::vector<std::string> v4 = v3;
		print_vector(v4, "v4");

		NAMESPACE::vector<std::string> v5;
		print_vector(v5, "v5");
		v5.push_back("Test");
		v5.push_back("...");
		print_vector(v5, "v5");
		v5[0] = "?";
		print_vector(v5, "v5");

		NAMESPACE::vector<std::string> v6(v5.begin(), v5.end());
		print_vector(v6, "v6");
	}

	print_seperator();
}

void vector_iterators()
{
	print_title("VECTOR - ITERATORS");

	NAMESPACE::vector<int> v;
	print_vector(v, "v");

	print_bool("begin() != end()", v.begin() != v.end());
	print_bool("begin() >= end()", v.begin() >= v.end());
	print_bool("begin() <= end()", v.begin() <= v.end());
	print_line("");
	
	for (size_t i = 0; i < 8; ++i)
		v.push_back(i);
	print_vector(v, "v");

	print_bool("begin() == end()", v.begin() == v.end());
	print_bool("begin() > end()", v.begin() > v.end());
	print_bool("begin() < end()", v.begin() < v.end());
	print_line("");

	for (NAMESPACE::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::iterator it = v.end(); it != v.begin(); --it)
		std::cout << *(it - 1) << " ";
	std::cout << std::endl << std::endl;
	
	for (NAMESPACE::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::reverse_iterator it = v.rend(); it != v.rbegin(); --it)
		std::cout << *(it - 1) << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::const_iterator it = v.end(); it != v.begin(); --it)
		std::cout << *(it - 1) << " ";
	std::cout << std::endl << std::endl;
	
	for (NAMESPACE::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::const_reverse_iterator it = v.rend(); it != v.rbegin(); --it)
		std::cout << *(it - 1) << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::iterator it = v.begin(); it != v.end(); it = it + 2)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	for (NAMESPACE::vector<int>::iterator it = v.end(); it != v.begin(); it = it - 4)
		std::cout << *(it - 1) << " ";
	std::cout << std::endl << std::endl;

	print_seperator();
}

void vector_resize()
{
	print_title("VECTOR - RESIZE");

	NAMESPACE::vector<int> v;
	print_vector(v, "v");

	v.resize(3, 3);
	print_vector(v, "v");

	v.resize(5, 5);
	print_vector(v, "v");

	v.resize(8);
	print_vector(v, "v");

	v.resize(0);
	print_vector(v, "v");

	print_seperator();
}

void vector_reserve()
{
	print_title("VECTOR - RESERVE");

	NAMESPACE::vector<int> v;
	print_vector(v, "v");

	for (size_t i = 0; i < 4; ++i)
		v.push_back(i);
	print_vector(v, "v");

	v.reserve(1);
	print_vector(v, "v");

	v.reserve(10);
	print_vector(v, "v");

	v.reserve(6);
	print_vector(v, "v");

	print_seperator();
}

void vector_access()
{
	print_title("VECTOR - ACCESS");

	NAMESPACE::vector<int> v;
	print_vector(v, "v");

	for (size_t i = 0; i < 5; ++i)
		v.push_back(i);
	print_vector(v, "v");

	print_value("v.at(0)", v.at(0));
	print_value("v[3]", v[3]);
	print_bool("v.at(2) == v[2]", v.at(2) == v[2]);

	try
	{
		v.at(5);
	}
	catch(std::exception const &e)
	{
		print_line("Exception: v.at(5)");
	}
	try
	{
		v.at(999999);
	}
	catch(std::exception const &e)
	{
		print_line("Exception: v.at(999999)");
	}
	print_line("");

	print_seperator();
}

void vector_assign()
{
	print_title("VECTOR - ASSIGN");

	NAMESPACE::vector<int> v1;
	print_vector(v1, "v1");

	v1.assign(3, 3);
	print_vector(v1, "v1");

	v1.assign(1, 1);
	print_vector(v1, "v1");

	v1.assign(0, 42);
	print_vector(v1, "v1");

	v1.assign(7, 7);
	print_vector(v1, "v1");

	NAMESPACE::vector<int> v2;
	for (size_t i = 0; i < 5; ++i)
		v2.push_back(i);
	v1.assign(v2.begin(), v2.end());
	print_vector(v1, "v1");

	v1.assign(v1.begin() + 1, v1.end() - 1);
	print_vector(v1, "v1");

	print_seperator();
}

void vector_push_and_pop()
{
	print_title("VECTOR - PUSH AND POP");

	NAMESPACE::vector<int> v;
	print_vector(v, "v");

	v.push_back(42);
	for (size_t i = 1; i < 5; ++i)
		v.push_back(i);
	print_vector(v, "v");

	v.pop_back();
	print_vector(v, "v");

	while (!(v.empty()))
		v.pop_back();
	print_vector(v, "v");

	print_seperator();
}

void vector_insert()
{
	print_title("VECTOR - INSERT");

	NAMESPACE::vector<int> v1;
	print_vector(v1, "v1");

	v1.insert(v1.begin(), 0);
	v1.insert(v1.begin(), 1);
	v1.insert(v1.end(), 2);
	v1.insert(v1.begin() + 1, 3);
	print_vector(v1, "v1");

	v1.insert(v1.end() - 1, 3, 42);
	print_vector(v1, "v1");

	NAMESPACE::vector<int> v2;
	for (size_t i = 4; i < 8; ++i)
		v2.push_back(i);
	v1.insert(v1.begin() + 2, v2.begin(), v2.end());
	print_vector(v1, "v1");

	print_seperator();
}

void vector_erase()
{
	print_title("VECTOR - ERASE");

	NAMESPACE::vector<int> v;
	for (size_t i = 0; i < 8; ++i)
		v.push_back(i);
	print_vector(v, "v");

	v.erase(v.begin());
	print_vector(v, "v");

	v.erase(v.end() - 1);
	print_vector(v, "v");

	v.erase(v.begin() + 1);
	print_vector(v, "v");

	v.erase(v.begin() + 2, v.end());
	print_vector(v, "v");

	while(!(v.empty()))
		v.erase(v.begin());
	print_vector(v, "v");

	print_seperator();
}

void vector_swap()
{
	print_title("VECTOR - SWAP");

	NAMESPACE::vector<int> v1(2, 2);
	NAMESPACE::vector<int> v2(7, 7);
	print_vector(v1, "v1");
	print_vector(v2, "v2");

	v1.swap(v2);
	print_vector(v1, "v1");
	print_vector(v2, "v2");

	v1.reserve(42);
	v2.swap(v1);
	print_vector(v1, "v1");
	print_vector(v2, "v2");

	v1.swap(v1);
	print_vector(v1, "v1");
	print_vector(v2, "v2");

	print_seperator();
}

void vector_clear()
{
	print_title("VECTOR - CLEAR");

	NAMESPACE::vector<int> v(7, 7);
	v.clear();
	print_vector(v, "v");

	v.assign(100, 42);
	v.clear();
	print_vector(v, "v");

	v.clear();
	print_vector(v, "v");

	print_seperator();
}

void vector_relational_operators()
{
	print_title("VECTOR - RELATIONAL OPERATORS");

	NAMESPACE::vector<int> v1(7, 7);
	print_vector(v1, "v1");
	NAMESPACE::vector<int> v2(v1);
	print_vector(v2, "v2");

	print_bool("v1 == v2", v1 == v2);
	print_bool("v1 != v2", v1 != v2);
	print_bool("v1 < v2", v1 < v2);
	print_bool("v1 <= v2", v1 <= v2);
	print_bool("v1 > v2", v1 > v2);
	print_bool("v1 >= v2", v1 >= v2);
	print_line("");

	NAMESPACE::vector<int> v3;
	for (size_t i = 0; i < 4; ++i)
		v3.push_back(i);
	print_vector(v3, "v3");
	NAMESPACE::vector<int> v4;
	for (size_t i = 0; i < 5; ++i)
		v4.push_back(i);
	print_vector(v4, "v4");

	print_bool("v3 == v4", v3 == v4);
	print_bool("v3 != v4", v3 != v4);
	print_bool("v3 < v4", v3 < v4);
	print_bool("v3 <= v4", v3 <= v4);
	print_bool("v3 > v4", v3 > v4);
	print_bool("v3 >= v4", v3 >= v4);
	print_line("");

	NAMESPACE::vector<int> v5(3, 3);
	print_vector(v5, "v5");
	NAMESPACE::vector<int> v6(v5);
	v6[1] = 2;
	print_vector(v6, "v6");

	print_bool("v5 == v6", v5 == v6);
	print_bool("v5 != v6", v5 != v6);
	print_bool("v5 < v6", v5 < v6);
	print_bool("v5 <= v6", v5 <= v6);
	print_bool("v5 > v6", v5 > v6);
	print_bool("v5 >= v6", v5 >= v6);
	print_line("");

	print_seperator();
}

void vector_benchmark()
{
	NAMESPACE::vector<int> v;
	for (size_t i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 99999; ++j)
			v.push_back(rand());
		v.insert(v.begin(), rand());
	}
	for (size_t i = 0; i < 10; ++i)
	{
		v.erase(v.begin());
		for (size_t j = 0; j < 99999; ++j)
			v.pop_back();
	}

	print_vector(v, "v");
}


/* *** M A I N ************************************************************** */

int main(int argc, char **argv)
{
	(void)argv;
	srand(42);
	clock_t start;


#ifdef FT
	print_line("**** F T ****");
#else
	print_line("*** S T D ***");
#endif
	print_line("");

	print_title("VECTOR");

	start = std::clock();

	vector_construction_and_assignment();
	vector_iterators();
	vector_resize();
	vector_reserve();
	vector_access();
	vector_assign();
	vector_push_and_pop();
	vector_insert();
	vector_erase();
	vector_swap();
	vector_clear();
	vector_relational_operators();
	vector_benchmark();

	std::cout << "time (vector): " 
			  << static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1000
			  << "ms"
			  << std::endl;

	if (argc > 1)
	{
#ifdef FT
		system("leaks test_ft");
#else
		system("leaks test_std");
#endif
	}

	return 0;
}
