/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_containers.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:14 by hepple            #+#    #+#             */
/*   Updated: 2023/02/20 16:23:27 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void print_line(T t)
{
	std::cout << t << std::endl;
}

void print_bool(bool b)
{
	if (b)
		std::cout << "true";
	else
		std::cout << "false";
}


template < typename T >
void print_vector(NAMESPACE::vector<T> v)
{
	for (typename NAMESPACE::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << "->" << *it << "<-" << std::endl;
}

template < typename Key, typename T, typename Compare >
void print_map(NAMESPACE::map<Key, T, Compare> m)
{
	for (typename NAMESPACE::map<Key, T, Compare>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << "->" << it->first << ", " << it->second << "<-" << std::endl;
}

template < typename T, typename Compare >
void print_set(NAMESPACE::vector<T> s)
{
	for (typename NAMESPACE::set<T>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << "->" << *it << "<-" << std::endl;
}


int main()
{
#ifdef FT
	std::cout << "ft" << std::endl;
#endif
	return 0;
}
