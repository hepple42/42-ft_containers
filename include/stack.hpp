/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:15:36 by hepple            #+#    #+#             */
/*   Updated: 2023/01/26 15:37:11 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_STACK_HPP
#define FT_STACK_HPP


#include <vector> // TEST!!!

// #include "vector.hpp"


namespace ft {


/* *** S T A C K ************************************************************ */

template < typename T, typename Container = std::vector<T> > // TEST!!!
class stack
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::size_type			size_type;
	typedef typename container_type::reference			reference; // C++11 ???
	typedef typename container_type::const_reference	const_reference; // C++11 ???


/* *** MEMBER VARIABLES ***************************************************** */

	protected:

	container_type	_c;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit stack(container_type const &cont = container_type()) : _c(cont) { }

	stack(stack const &src) : _c(src._c) { }

/* *** Destructor *********************************************************** */

	~stack() { }

/* *** Assignment *********************************************************** */

	stack &operator=(stack const &src)
	{
		_c = src._c;
		return *this;
	}

/* *** Capacity ************************************************************* */

	bool empty() const
	{
		return _c.empty();
	}

	size_type size() const
	{
		return _c.size();
	}

/* *** Element Access ******************************************************* */

	reference top()
	{
		return _c.back();
	}

	const_reference top() const
	{
		return _c.back();
	}

/* *** Modifiers ************************************************************ */

	void push(const_reference val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_back();
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
	return (lhs._c == rhs._c);
}

template < typename T, typename Container >
bool operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return !(lhs == rhs);
}

template < typename T, typename Container >
bool operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
{
	return (lhs._c < rhs._c);
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
