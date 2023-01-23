/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:16:05 by hepple            #+#    #+#             */
/*   Updated: 2023/01/23 13:47:31 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP


#include <cstddef>
#include <iterator>


namespace ft {


/* *** ITERATOR_TAGS ******************************************************** */

typedef std::input_iterator_tag			input_iterator_tag;
typedef std::output_iterator_tag		output_iterator_tag;
typedef std::forward_iterator_tag		forward_iterator_tag;
typedef std::bidirectional_iterator_tag	bidirectional_iterator_tag;
typedef std::random_access_iterator_tag	random_access_iterator_tag;

// struct input_iterator_tag { };
// struct output_iterator_tag { };
// struct forward_iterator_tag : public input_iterator_tag { };
// struct bidirectional_iterator_tag : public forward_iterator_tag { };
// struct random_access_iterator_tag : public bidirectional_iterator_tag { };


/* *** ITERATOR ************************************************************* */

template < typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T *, typename Reference = T & >
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
}


/* *** ITERATOR_TRAITS ****************************************************** */

template < typename Iterator >
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
}

template < typename T >
struct iterator_traits<T *>
{
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef T *							pointer;
	typedef T &							reference;
	typedef random_access_iterator_tag	iterator_category;
}

template < typename T >
struct iterator_traits<T const *>
{
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef T const *					pointer;
	typedef T const &					reference;
	typedef random_access_iterator_tag	iterator_category;
}

} // namespace ft


#endif // ITERATOR_HPP
