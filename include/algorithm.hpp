/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:33:09 by hepple            #+#    #+#             */
/*   Updated: 2023/02/20 13:27:35 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP


namespace ft {


/* *** EQUAL **************************************************************** */

template < typename InputIterator1, typename InputIterator2 >
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

template < typename InputIterator1, typename InputIterator2 , typename BinaryPredicate >
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1)
	{
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}


/* *** LEXICOGRAPHICAL_COMPARE ********************************************** */

template < typename InputIterator1, typename InputIterator2 >
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
							 InputIterator2 last2)
{
	while (first1 != last1 && first2 != last2)
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
		++first1;
		++first2;
	}
	return (first1 == last1 && first2 != last2);
}

template < typename InputIterator1, typename InputIterator2, typename Compare >
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
							 InputIterator2 last2, Compare comp)
{
	while (first1 != last1 && first2 != last2)
	{
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
		++first1;
		++first2;
	}
	return (first1 == last1 && first2 != last2);
}


/* *** SWAP ***************************************************************** */

template < typename T >
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}


} // namespace ft


#endif // FT_ALGORITHM_HPP
