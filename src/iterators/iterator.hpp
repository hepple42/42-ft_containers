/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:16:05 by hepple            #+#    #+#             */
/*   Updated: 2023/01/25 13:43:54 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP


#include <cstddef>
#include <iterator>

#include "type_traits.hpp"


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


/* *** ITERATOR_TRAITS ****************************************************** */

template < typename Iterator >
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template < typename T >
struct iterator_traits<T *>
{
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef T *							pointer;
	typedef T &							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template < typename T >
struct iterator_traits<T const *>
{
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef T const *					pointer;
	typedef T const &					reference;
	typedef random_access_iterator_tag	iterator_category;
};


/* *** ITERATOR ************************************************************* */

template < typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T *, typename Reference = T & >
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};


/* *** R E V E R S E _ I T E R A T O R ************************************** */

template < typename Iter >
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category, typename ft::iterator_traits<Iter>::value_type, typename ft::iterator_traits<Iter>::difference_type, typename ft::iterator_traits<Iter>::pointer, typename ft::iterator_traits<Iter>::reference>
{
	protected:

/* *** MEMBER VARIABLES ***************************************************** */

	Iter	_current;


	public:
	
/* *** MEMBER TYPES ********************************************************* */

	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;


/* *** MEMBER FUNCTIONS ***************************************************** */

/* *** Constructor ********************************************************** */

	reverse_iterator() : _current() { }

	explicit reverse_iterator(Iter it) : _current(it) { }

	template < typename Iter >
	reverse_iterator(reverse_iterator<Iter> const &rev_it) : _current(rev_it.base()) { }

/* *** Destructor *********************************************************** */

	~reverse_iterator() {}

/* *** Assignment *********************************************************** */

	template < typename Iter >
	reverse_iterator &operator=(reverse_iterator<Iter> const &rev_it)
	{
		_current = rev_it.base();
		return *this;
	}

/* *** Access *************************************************************** */

	iterator_type base() const
	{
		return _current;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator*() const
	{
		iterator_type tmp = _current;
		return *(--tmp);
	}

/* *** Increment / Decrement ************************************************ */

	reverse_iterator &operator++()
	{
		--_current;
		return *this;
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp(*this);
		--_current;
		return tmp;
	}

	reverse_iterator &operator+= (difference_type n)
	{
		_current -= n;
		return *this;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(_current - n);
	}

	reverse_iterator &operator--()
	{
		++_current;
		return *this;
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp(*this);
		++_current;
		return tmp;
	}

	reverse_iterator &operator-= (difference_type n)
	{
		_current += n;
		return *this;
	}

	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(_current + n);
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename IterL, typename IterR >
bool operator==(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename IterL, typename IterR >
bool operator!=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() != lhs.base());
}

template < typename IterL, typename IterR >
bool operator<(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() > lhs.base());
}

template < typename IterL, typename IterR >
bool operator<=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() >= lhs.base());
}

template < typename IterL, typename IterR >
bool operator>(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() < lhs.base());
}

template < typename IterL, typename IterR >
bool operator>=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() <= lhs.base());
}

/* *** Increment / Decrement ************************************************ */

template < class Iter >
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const &rev_it)
{
	return reverse_iterator<Iter>(it.base() - n);
}

template < class Iter >
typename reverse_iterator<Iter>::difference_type operator-(reverse_iterator<Iter> const &lhs, reverse_iterator<Iter> const &rhs)
{
	return (rhs.base() - lhs.base());
}


} // namespace ft


#endif // FT_ITERATOR_HPP
