/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:16:05 by hepple            #+#    #+#             */
/*   Updated: 2023/01/27 12:19:59 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP


#include <cstddef>
#include <iterator> // ITERATOR TAGS

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

template < typename Iterator >
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_traits<Iterator>::difference_type, typename ft::iterator_traits<Iterator>::pointer, typename ft::iterator_traits<Iterator>::reference>
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;


/* *** MEMBER VARIABLES ***************************************************** */

	protected:

	iterator_type	_current;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	reverse_iterator() : _current() { }

	explicit reverse_iterator(iterator_type it) : _current(it) { }

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
	return (lhs.base() != rhs.base());
}

template < typename IterL, typename IterR >
bool operator<(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename IterL, typename IterR >
bool operator<=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() >= rhs.base());
}

template < typename IterL, typename IterR >
bool operator>(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename IterL, typename IterR >
bool operator>=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (lhs.base() <= rhs.base());
}

/* *** Increment / Decrement ************************************************ */

template < typename Iter >
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const &rev_it)
{
	return reverse_iterator<Iter>(rev_it.base() - n);
}

template < typename IterL, typename IterR >
typename reverse_iterator<IterL>::difference_type operator-(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
{
	return (rhs.base() - lhs.base());
}


/* *** N O R M A L _ I T E R A T O R **************************************** */

template < typename Iterator >
class normal_iterator
{
	
/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	iterator_type	_current;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	normal_iterator() : _current() { }

	explicit normal_iterator(iterator_type it) : _current(it) { }

	template < typename Iter >
	normal_iterator(normal_iterator<Iter> const &n_it) : _current(n_it.base()) { }

/* *** Destructor *********************************************************** */

	~normal_iterator() {}

/* *** Assignment *********************************************************** */

	template < typename Iter >
	normal_iterator &operator=(normal_iterator<Iter> const &n_it)
	{
		_current = n_it.base();
		return *this;
	}

/* *** Access *************************************************************** */

	iterator_type base() const
	{
		return _current;
	}

	reference operator[](difference_type n) const
	{
		return _current[n];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator*() const
	{
		return *_current;
	}

/* *** Increment / Decrement ************************************************ */

	normal_iterator &operator++()
	{
		++_current;
		return *this;
	}

	normal_iterator operator++(int)
	{
		normal_iterator tmp(*this);
		++_current;
		return tmp;
	}

	normal_iterator &operator+= (difference_type n)
	{
		_current += n;
		return *this;
	}

	normal_iterator operator+(difference_type n) const
	{
		return normal_iterator(_current + n);
	}

	normal_iterator &operator--()
	{
		--_current;
		return *this;
	}

	normal_iterator operator--(int)
	{
		normal_iterator tmp(*this);
		--_current;
		return tmp;
	}

	normal_iterator &operator-= (difference_type n)
	{
		_current -= n;
		return *this;
	}

	normal_iterator operator-(difference_type n) const
	{
		return normal_iterator(_current - n);
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename IterL, typename IterR >
bool operator==(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename IterL, typename IterR >
bool operator!=(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() != rhs.base());
}

template < typename IterL, typename IterR >
bool operator<(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename IterL, typename IterR >
bool operator<=(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() <= rhs.base());
}

template < typename IterL, typename IterR >
bool operator>(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename IterL, typename IterR >
bool operator>=(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() >= rhs.base());
}

/* *** Increment / Decrement ************************************************ */

template < typename Iter >
normal_iterator<Iter> operator+(typename normal_iterator<Iter>::difference_type n, normal_iterator<Iter> const &n_it)
{
	return normal_iterator<Iter>(n_it.base() + n);
}

template < typename IterL, typename IterR >
typename normal_iterator<IterL>::difference_type operator-(normal_iterator<IterL> const &lhs, normal_iterator<IterR> const &rhs)
{
	return (lhs.base() - rhs.base());
}


} // namespace ft


#endif // FT_ITERATOR_HPP
