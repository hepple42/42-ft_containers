/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_containers.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:14 by hepple            #+#    #+#             */
/*   Updated: 2023/02/22 12:42:50 by hepple           ###   ########.fr       */
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


template < typename T >
struct map_more : std::binary_function <T, T, bool>
{
	bool operator()(T const &x, T const &y) const
	{
		return (x > y);
	}
};

template< typename T >
class mutant_stack : public NAMESPACE::stack<T>
{
  public:

	mutant_stack() { }

	mutant_stack(mutant_stack<T> const &src)
	{
		*this = src;
	}

	mutant_stack<T> &operator=(mutant_stack<T> const &rhs)
	{
		this->c = rhs.c;
		return *this;
	}

	~mutant_stack() { }

	typedef typename NAMESPACE::stack<T>::container_type::iterator iterator;

	iterator begin()
	{
		return this->c.begin();
	}
	
	iterator end()
	{
		return this->c.end();
	}
};


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

void print_separator()
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

template < typename Key, typename T, typename Compare >
void print_map(NAMESPACE::map<Key, T, Compare> m, std::string name = "map")
{
	print_line(name + ":");

	print_value("size", m.size());

	print_value("max_size", m.max_size());

	print_bool("empty", m.empty());

	print_line("content:");
	for (typename NAMESPACE::map<Key, T, Compare>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << name << "[" << (*it).first << "] = " << (*it).second << std::endl;

	print_line("");
}

template < typename T >
void print_stack(NAMESPACE::stack<T> const &s, std::string name = "stack")
{
	print_line(name + ":");

	print_value("size", s.size());

	print_bool("empty", s.empty());

	if (s.size() > 0)
		print_value("top", s.top());
	else
		print_line("top: -");

	print_line("content:");
	NAMESPACE::stack<T> tmp(s);
	while (!(tmp.empty()))
	{
		std::cout << tmp.top() << std::endl;
		tmp.pop();
	}

	print_line("");
}

template < typename T, typename Compare >
void print_set(NAMESPACE::set<T, Compare> const &s, std::string name = "set")
{
	print_line(name + ":");

	print_value("size", s.size());

	print_value("max_size", s.max_size());

	print_bool("empty", s.empty());

	print_line("content:");
	for (typename NAMESPACE::set<T, Compare>::const_iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << std::endl;

	print_line("");
}


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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
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

	print_separator();
}

void vector_swap()
{
	print_title("VECTOR - SWAP");

	NAMESPACE::vector<int> v1(2, 2);
	print_vector(v1, "v1");
	NAMESPACE::vector<int> v2(7, 7);
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

	print_separator();
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

	print_separator();
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

	print_separator();
}

void vector_benchmark()
{
	srand(42);

	print_title("VECTOR - BENCHMARK");

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

	print_separator();
}


/* *** M A P **************************************************************** */

void map_construction_and_assignment()
{
	print_title("MAP - CONSTRUCTION AND ASSIGNMENT");

	{
		NAMESPACE::map<int, char> m1;
		print_map(m1, "m1");

		NAMESPACE::map<int, char> m2;
		for (size_t i = 0; i < 7; ++i)
			m2[i] = 'a' + 2 * i;
		print_map(m2, "m2");

		NAMESPACE::map<int, char> m3(m2);
		print_map(m3, "m3");

		NAMESPACE::map<int, char> m4(m3.begin(), m3.end());
		print_map(m4, "m4");

		NAMESPACE::map<int, char> m5 = m4;
		print_map(m5, "m5");
	}

	{
		NAMESPACE::map<std::string, double> m1;
		print_map(m1, "m1");

		NAMESPACE::map<std::string, double> m2;
		m2["Blub"] = 7.77;
		m2["Test"] = -1.0;
		m2["42"] = 42;
		print_map(m2, "m2");

		NAMESPACE::map<std::string, double> m3(m2);
		print_map(m3, "m3");

		NAMESPACE::map<std::string, double> m4(m3.begin(), m3.end());
		print_map(m4, "m4");

		NAMESPACE::map<std::string, double> m5 = m4;
		print_map(m5, "m5");
	}

	print_separator();
}

void map_compare()
{
	print_title("MAP - COMPARE");

	NAMESPACE::map<int, char> m1;
	for (size_t i = 0; i < 8; ++i)
		m1[i] = 'a' + i;
	print_map(m1, "m1");

	NAMESPACE::map<int, char, map_more<int> > m2;
	for (size_t i = 0; i < 8; ++i)
		m2[i] = 'a' + i;
	print_map(m2, "m2");

	print_separator();
}

void map_iterators()
{
	print_title("MAP - ITERATORS");

	NAMESPACE::map<int, char> m;
	print_map(m, "m");

	print_bool("begin() == end()", m.begin() == m.end());
	print_bool("begin() != end()", m.begin() != m.end());
	print_line("");

	for (size_t i = 0; i < 8; ++i)
		m[i] = 'a' + i;
	print_map(m, "m");

	print_bool("begin() == end()", m.begin() == m.end());
	print_bool("begin() != end()", m.begin() != m.end());
	print_line("");

	for (NAMESPACE::map<int, char>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << "[" << it->first << "," << it->second << "] ";
	std::cout << std::endl << std::endl;

	NAMESPACE::map<int, char>::iterator it1 = m.end();
	while (it1 != m.begin())
	{
		--it1;
		std::cout << "[" << it1->first << "," << it1->second << "] ";
	}
	std::cout << std::endl << std::endl;

	for (NAMESPACE::map<int, char>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it)
		std::cout << "[" << it->first << "," << it->second << "] ";
	std::cout << std::endl << std::endl;

	NAMESPACE::map<int, char>::reverse_iterator it2 = m.rend();
	while (it2 != m.rbegin())
	{
		--it2;
		std::cout << "[" << it2->first << "," << it2->second << "] ";
	}
	std::cout << std::endl << std::endl;

	for (NAMESPACE::map<int, char>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << "[" << it->first << "," << it->second << "] ";
	std::cout << std::endl << std::endl;

	NAMESPACE::map<int, char>::const_iterator it3 = m.end();
	while (it3 != m.begin())
	{
		--it3;
		std::cout << "[" << it3->first << "," << it3->second << "] ";
	}
	std::cout << std::endl << std::endl;

	for (NAMESPACE::map<int, char>::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it)
		std::cout << "[" << it->first << "," << it->second << "] ";
	std::cout << std::endl << std::endl;

	NAMESPACE::map<int, char>::const_reverse_iterator it4 = m.rend();
	while (it4 != m.rbegin())
	{
		--it4;
		std::cout << "[" << it4->first << "," << it4->second << "] ";
	}
	std::cout << std::endl << std::endl;

	print_separator();
}

void map_access()
{
	print_title("MAP - ACCESS");

	NAMESPACE::map<int, char> m;
	print_map(m, "m");

	for (size_t i = 0; i < 5; ++i)
		m[i] = 'a' + i;
	print_map(m, "m");

	print_value("m.at(0)", m.at(0));
	print_value("m[3]", m[3]);
	print_bool("m.at(2) == m[2]", m.at(2) == m[2]);

	try
	{
		m.at(5);
	}
	catch(std::exception const &e)
	{
		print_line("Exception: m.at(5)");
	}
	try
	{
		m.at(999999);
	}
	catch(std::exception const &e)
	{
		print_line("Exception: m.at(999999)");
	}
	print_line("");

	print_separator();
}

void map_insert()
{
	print_title("MAP - INSERT");

	NAMESPACE::map<int, char> m1;
	print_map(m1, "m1");

	m1.insert(NAMESPACE::make_pair(3, 'a'));
	m1.insert(NAMESPACE::make_pair(0, 'b'));
	m1.insert(NAMESPACE::make_pair(2, 'c'));
	m1.insert(NAMESPACE::make_pair(1, 'd'));
	print_map(m1, "m1");

	m1.insert(m1.begin(), NAMESPACE::make_pair(4, 'e'));
	print_map(m1, "m1");

	NAMESPACE::map<int, char> m2;
	for (size_t i = 3; i < 8; ++i)
		m2[i] = 'a' + 2 * i;
	m1.insert(m2.begin(), m2.end());
	print_map(m1, "m1");

	print_separator();
}

void map_erase()
{
	print_title("MAP - ERASE");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 8; ++i)
		m[i] = 'a' + i;
	print_map(m, "m");

	m.erase(m.begin());
	print_map(m, "m");

	m.erase(--(m.end()));
	print_map(m, "m");

	m.erase(4);
	print_map(m, "m");

	m.erase(++(m.begin()), --(m.end()));
	print_map(m, "m");

	while (!(m.empty()))
		m.erase(m.begin());
	print_map(m, "m");

	print_separator();
}

void map_swap()
{
	print_title("MAP - SWAP");

	NAMESPACE::map<int, char> m1;
	for (size_t i = 0; i < 8; ++i)
		m1[i + 42] = 'a' + i;
	print_map(m1, "m1");
	NAMESPACE::map<int, char> m2;
	for (size_t i = 0; i < 3; ++i)
		m2[i] = 'a' + 3 * i;
	print_map(m2, "m2");

	m1.swap(m2);
	print_map(m1, "m1");
	print_map(m2, "m2");

	m2.swap(m1);
	print_map(m1, "m1");
	print_map(m2, "m2");

	m1.swap(m1);
	print_map(m1, "m1");
	print_map(m2, "m2");

	print_separator();
}

void map_clear()
{
	print_title("MAP - CLEAR");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 8; ++i)
		m[i] = 'a' + i;
	m.clear();
	print_map(m, "m");

	m.insert(NAMESPACE::make_pair(3, 'a'));
	m.insert(NAMESPACE::make_pair(0, 'b'));
	m.insert(NAMESPACE::make_pair(2, 'c'));
	m.insert(NAMESPACE::make_pair(1, 'd'));
	m.clear();
	print_map(m, "m");

	m.clear();
	print_map(m, "m");

	print_separator();
}

void map_find()
{
	print_title("MAP - FIND");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 8; ++i)
		m[i] = 'a' + (3 * i) % 8;
	print_map(m, "m");

	print_value("(m.find(0))->first", (m.find(0))->first);
	print_value("(m.find(0))->second", (m.find(0))->second);

	print_value("(m.find(7))->first", (m.find(7))->first);
	print_value("(m.find(7))->second", (m.find(7))->second);

	print_value("(m.find(2))->first", (m.find(2))->first);
	print_value("(m.find(2))->second", (m.find(2))->second);

	print_bool("m.find(0) == m.end()", m.find(0) == m.end());
	print_bool("m.find(42) == m.end()", m.find(42) == m.end());

	print_separator();
}

void map_count()
{
	print_title("MAP - COUNT");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 8; ++i)
		m[i] = 'a' + (5 * i) % 8;
	print_map(m, "m");

	print_value("m.count(0)", m.count(0));
	print_value("m.count(7)", m.count(7));
	print_value("m.count(2)", m.count(2));
	print_value("m.count(42)", m.count(42));

	print_separator();
}

void map_bounds()
{
	print_title("MAP - BOUNDS");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 8; ++i)
		m[2 * i] = 'a' + (5 * i) % 8;
	print_map(m, "m");

	print_value("(m.lower_bound(4))->first", (m.lower_bound(4))->first);
	print_value("(m.lower_bound(4))->second", (m.lower_bound(4))->second);
	print_value("(m.upper_bound(4))->first", (m.upper_bound(4))->first);
	print_value("(m.upper_bound(4))->second", (m.upper_bound(4))->second);
	print_value("((m.equal_range(4)).first)->first", ((m.equal_range(4)).first)->first);
	print_value("((m.equal_range(4)).first)->second", ((m.equal_range(4)).first)->second);
	print_value("((m.equal_range(4)).second)->first", ((m.equal_range(4)).second)->first);
	print_value("((m.equal_range(4)).second)->second", ((m.equal_range(4)).second)->second);
	print_line("");

	print_value("(m.lower_bound(7))->first", (m.lower_bound(7))->first);
	print_value("(m.lower_bound(7))->second", (m.lower_bound(7))->second);
	print_value("(m.upper_bound(7))->first", (m.upper_bound(7))->first);
	print_value("(m.upper_bound(7))->second", (m.upper_bound(7))->second);
	print_value("((m.equal_range(7)).first)->first", ((m.equal_range(7)).first)->first);
	print_value("((m.equal_range(7)).first)->second", ((m.equal_range(7)).first)->second);
	print_value("((m.equal_range(7)).second)->first", ((m.equal_range(7)).second)->first);
	print_value("((m.equal_range(7)).second)->second", ((m.equal_range(7)).second)->second);
	print_line("");

	print_bool("m.lower_bound(42) == m.end()", m.lower_bound(42) == m.end());
	print_bool("m.upper_bound(42) == m.end()", m.upper_bound(42) == m.end());
	print_bool("(m.equal_range(42)).first == m.end()", (m.equal_range(42)).first == m.end());
	print_bool("(m.equal_range(42)).second == m.end()", (m.equal_range(42)).second == m.end());
	print_line("");

	print_separator();
}

void map_relational_operators()
{
	print_title("MAP - RELATIONAL OPERATORS");

	NAMESPACE::map<int, char> m1;
	for (size_t i = 0; i < 8; ++i)
		m1[i] = 'a' + (3 * i) % 8;
	print_map(m1, "m1");
	NAMESPACE::map<int, char> m2(m1);
	print_map(m2, "m2");

	print_bool("m1 == m2", m1 == m2);
	print_bool("m1 != m2", m1 != m2);
	print_bool("m1 < m2", m1 < m2);
	print_bool("m1 <= m2", m1 <= m2);
	print_bool("m1 > m2", m1 > m2);
	print_bool("m1 >= m2", m1 >= m2);
	print_line("");

	NAMESPACE::map<int, char> m3;
	for (size_t i = 0; i < 6; ++i)
		m3[i] = 'a' + (3 * i) % 8;
	print_map(m1, "m1");
	NAMESPACE::map<int, char> m4;
	for (size_t i = 0; i < 5; ++i)
		m4[i] = 'a' + (3 * i) % 8;
	print_map(m4, "m4");

	print_bool("m3 == m4", m3 == m4);
	print_bool("m3 != m4", m3 != m4);
	print_bool("m3 < m4", m3 < m4);
	print_bool("m3 <= m4", m3 <= m4);
	print_bool("m3 > m4", m3 > m4);
	print_bool("m3 >= m4", m3 >= m4);
	print_line("");

	NAMESPACE::map<int, char> m5;
	for (size_t i = 0; i < 6; ++i)
		m5[i] = 'a' + (5 * i) % 8;
	print_map(m5, "m5");
	NAMESPACE::map<int, char> m6(m5);
		m6[1] = 'a';
	print_map(m6, "m6");

	print_bool("m5 == m6", m5 == m6);
	print_bool("m5 != m6", m5 != m6);
	print_bool("m5 < m6", m5 < m6);
	print_bool("m5 <= m6", m5 <= m6);
	print_bool("m5 > m6", m5 > m6);
	print_bool("m5 >= m6", m5 >= m6);
	print_line("");

	print_separator();
}

void map_benchmark()
{
	srand(42);

	print_title("MAP - BENCHMARK");

	NAMESPACE::map<int, char> m;
	for (size_t i = 0; i < 100000; ++i)
		m.insert(NAMESPACE::make_pair(i, 'a' + rand() % 26));
	for (size_t i = 0; i < 100000; ++i)
		m.find(i);
	for (size_t i = 0; i < 100000; ++i)
		m.erase(i);

	print_map(m, "m");

	print_separator();
}


/* *** S T A C K ************************************************************ */

void stack_construction_and_assignment()
{
	print_title("STACK - CONSTRUCTION AND ASSIGNMENT");

	NAMESPACE::stack<int> s1;
	print_stack(s1, "s1");

	NAMESPACE::stack<int> s2;
	for (size_t i = 0; i < 8; ++i)
		s2.push(100 * i);
	print_stack(s2, "s2");

	NAMESPACE::stack<int> s3(s2);
	print_stack(s3, "s3");

	NAMESPACE::stack<int> s4 = s3;
	print_stack(s4, "s4");

	print_separator();
}

void stack_mutant()
{
	print_title("STACK - MUTANT");

	mutant_stack<char> ms;
	for(char c = 'a'; c <= 'z'; ++c)
		ms.push(c);
	std::cout << "ms:" << std::endl << "content:" << std::endl;
	for(mutant_stack<char>::iterator it = ms.begin(); it != ms.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	print_separator();
}

void stack_push_and_pop()
{
	print_title("STACK - PUSH AND POP");

	NAMESPACE::stack<int> s;
	print_stack(s, "s");

	s.push(42);
	for (size_t i = 0; i < 8; ++i)
		s.push(i);
	print_stack(s, "s");

	s.push(42);
	print_stack(s, "s");

	s.pop();
	print_stack(s, "s");

	while (!(s.empty()))
		s.pop();
	print_stack(s, "s");

	print_separator();
}

void stack_relational_operators()
{
	print_title("STACK - RELATIONAL OPERATORS");

	NAMESPACE::stack<int> s1;
	for (size_t i = 0; i < 6; ++i)
		s1.push(i);
	print_stack(s1, "s1");
	NAMESPACE::stack<int> s2(s1);
	print_stack(s2, "s2");

	print_bool("s1 == s2", s1 == s2);
	print_bool("s1 != s2", s1 != s2);
	print_bool("s1 < s2", s1 < s2);
	print_bool("s1 <= s2", s1 <= s2);
	print_bool("s1 > s2", s1 > s2);
	print_bool("s1 >= s2", s1 >= s2);
	print_line("");

	NAMESPACE::stack<int> s3;
	for (size_t i = 0; i < 4; ++i)
		s3.push(i);
	print_stack(s3, "s3");
	NAMESPACE::stack<int> s4;
	for (size_t i = 0; i < 5; ++i)
		s4.push(i);
	print_stack(s4, "s4");

	print_bool("s3 == s4", s3 == s4);
	print_bool("s3 != s4", s3 != s4);
	print_bool("s3 < s4", s3 < s4);
	print_bool("s3 <= s4", s3 <= s4);
	print_bool("s3 > s4", s3 > s4);
	print_bool("s3 >= s4", s3 >= s4);
	print_line("");

	NAMESPACE::stack<int> s5;
	print_stack(s5, "s5");
	NAMESPACE::stack<int> s6(s5);
	print_stack(s6, "s6");

	print_bool("s5 == s6", s5 == s6);
	print_bool("s5 != s6", s5 != s6);
	print_bool("s5 < s6", s5 < s6);
	print_bool("s5 <= s6", s5 <= s6);
	print_bool("s5 > s6", s5 > s6);
	print_bool("s5 >= s6", s5 >= s6);
	print_line("");

	print_separator();
}

void stack_benchmark()
{
	print_title("STACK - BENCHMARK");

	NAMESPACE::stack<int> s;
	for (size_t i = 0; i < 1000000; ++i)
		s.push((i + 100) % 1000000);
	for (size_t i = 0; i < 1000000; ++i)
		s.pop();

	print_stack(s, "s");

	print_separator();
}


/* *** M A I N ************************************************************** */

int main(int argc, char **argv)
{
	(void)argv;
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
			  
	print_line("");
	print_separator();
	print_separator();


	print_title("MAP");
	
	start = std::clock();
	
	map_construction_and_assignment();
	map_compare();
	map_iterators();
	map_access();
	map_insert();
	map_erase();
	map_swap();
	map_clear();
	map_find();
	map_count();
	map_bounds();
	map_relational_operators();
	map_benchmark();
	
	std::cout << "time (map): " 
			  << static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1000
			  << "ms"
			  << std::endl;

	print_line("");
	print_separator();
	print_separator();

	
	print_title("STACK");
	
	start = std::clock();
	
	stack_construction_and_assignment();
	stack_mutant();
	stack_push_and_pop();
	stack_relational_operators();
	stack_benchmark();
	
	std::cout << "time (stack): " 
			  << static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1000
			  << "ms"
			  << std::endl;

	print_line("");
	print_separator();
	print_separator();

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
