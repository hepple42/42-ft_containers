/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:15:36 by hepple            #+#    #+#             */
/*   Updated: 2023/02/17 14:10:45 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_STACK_HPP
#define FT_STACK_HPP


#include "vector.hpp"


namespace ft {


/* *** S T A C K ************************************************************ */

template < typename T, typename Container = ft::vector<T> >
class stack
{

/* *** MEMBER TYPES ********************************************************* */

  public:

	typedef Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::size_type			size_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;


/* *** MEMBER VARIABLES ***************************************************** */

  protected:

	container_type	c;


/* *** MEMBER FUNCTIONS ***************************************************** */

  public:

/* *** Constructor ********************************************************** */

	explicit stack(container_type const &cont = container_type()) : c(cont) { }

	stack(stack const &src) : c(src.c) { }

/* *** Destructor *********************************************************** */

	~stack() { }

/* *** Assignment *********************************************************** */

	stack &operator=(stack const &src)
	{
		c = src.c;
		return *this;
	}

/* *** Capacity ************************************************************* */

	bool empty() const
	{
		return c.empty();
	}

	size_type size() const
	{
		return c.size();
	}

/* *** Element Access ******************************************************* */

	reference top()
	{
		return c.back();
	}

	const_reference top() const
	{
		return c.back();
	}

/* *** Modifiers ************************************************************ */

	void push(const_reference val)
	{
		c.push_back(val);
	}

	void pop()
	{
		c.pop_back();
	}


/* *** FRIEND FUNCTIONS ***************************************************** */

	template < typename U, typename Cont >
	friend bool operator==(stack<U, Cont> const &lhs, stack<U, Cont> const &rhs);

	template < typename U, typename Cont >
	friend bool operator<(stack<U, Cont> const &lhs, stack<U, Cont> const &rhs);

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename T, typename Container >
bool operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return (lhs.c == rhs.c);
}

template < typename T, typename Container >
bool operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return !(lhs == rhs);
}

template < typename T, typename Container >
bool operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return (lhs.c < rhs.c);
}

template < typename T, typename Container >
bool operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return !(rhs < lhs);
}

template < typename T, typename Container >
bool operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return (rhs < lhs);
}

template < typename T, typename Container >
bool operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return !(lhs < rhs);
}


} // namespace ft


#endif // FT_STACK_HPP
