/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:05:57 by hepple            #+#    #+#             */
/*   Updated: 2023/01/26 13:43:24 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP


namespace ft {


/* *** P A I R ************************************************************** */

template < typename T1, typename T2 >
struct pair
{

/* *** MEMBER TYPES ********************************************************* */

	typedef T1	first_type;
	typedef T2	second_type;


/* *** MEMBER VARIABLES ***************************************************** */

	first_type	first;
	second_type	second;


/* *** MEMBER FUNCTIONS ***************************************************** */

/* *** Constructor ********************************************************** */

	pair() : first(), second() { }

	template < typename U, typename V>
	pair (pair<U, V> const &src) : first(src.first), second(src.second) { }

	pair (first_type const &a, second_type const &b) : first(a) , second(b) { }

/* *** Destructor *********************************************************** */

	~pair() { }

/* *** Assignment *********************************************************** */

	pair &operator=(pair const &src)
	{
		first = src.first;
		second = src.second;
		return *this;
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename T1, typename T2 >
bool operator==(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template < typename T1, typename T2 >
bool operator!=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return !(lhs == rhs);
}

template < typename T1, typename T2 >
bool operator<(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template < typename T1, typename T2 >
bool operator<=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return !(rhs < lhs);
}

template < typename T1, typename T2 >
bool operator>(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return (rhs < lhs);
}

template < typename T1, typename T2 >
bool operator>=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
{
	return !(lhs < rhs);
}


/* *** MAKE_PAIR ************************************************************ */

template < typename T1, typename T2 >
pair<T1, T2> make_pair(T1 a, T2 b)
{
	return pair<T1, T2>(a, b);
}


} // namespace ft


#endif // FT_UTILITY_HPP
