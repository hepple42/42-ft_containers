/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:28:52 by hepple            #+#    #+#             */
/*   Updated: 2023/01/25 15:21:59 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP


#include <memory>
#include <stdexcept>

#include "../iterators/iterator.hpp"


namespace ft {


/* *** V E C T O R ********************************************************** */

template < typename T, typename Alloc = std::allocator<T> >
class vector
{
	
/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::differece_type		difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	// typedef iterator;
	// typedef const_iterator;
	// typedef reverse_iterator;
	// typedef const_reverse_iterator;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit vector(allocator_type const &alloc = allocator_type());
	explicit vector(size_type n, value_type const &val = value_type(), allocator_type const &alloc = allocator_type());
	template < typename InputIterator >
	vector (InputIterator first, InputIterator last, allocator_type const &alloc = allocator_type());
	vector (vector const &x);

/* *** Destructor *********************************************************** */

	~vector();

/* *** Assignment *********************************************************** */

	vector &operator=(vector const &x);

/* *** Iterators ************************************************************ */

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const;

/* *** Capacity ************************************************************* */

	size_type size() const;

	size_type max_size() const;

	void resize(size_type n, value_type val = value_type());

	size_type capacity() const;

	bool empty() const;

	void reserve(size_type n);

/* *** Element Access ******************************************************* */

	reference operator[](size_type n);
	const_reference operator[](size_type n) const;

	reference at(size_type n);
	const_reference at(size_type n) const;

	reference front();
	const_reference front() const;

	reference back();
	const_reference back() const;

	value_type *data();
	value_type const *data() const;

/* *** Modifiers ************************************************************ */

	void assign(size_type n, value_type const &val);
	template < class InputIterator >
	void assign(InputIterator first, InputIterator last);

	void push_back(value_type const &val);

	void pop_back();

	iterator insert(iterator position, value_type const &val);
	void insert(iterator position, size_type n, value_type const &val);
	template < class InputIterator >
	void insert(iterator position, InputIterator first, InputIterator last);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	void swap(vector &x);

	void clear();

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const;


/* *** MEMBER VARIABLES ***************************************************** */

	protected:  // PRIVATE???

	allocator_type	_alloc;
	pointer			_start;
	pointer			_finish;
	pointer			_cap;

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename T, typename Alloc >
bool operator==(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

template < typename T, typename Alloc >
bool operator!=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

template < typename T, typename Alloc >
bool operator<(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

template < typename T, typename Alloc >
bool operator<=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

template < typename T, typename Alloc >
bool operator>(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

template < typename T, typename Alloc >
bool operator>=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs);

/* *** Swap ***************************************************************** */

template < typename T, typename Alloc >
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);


} // namespace ft


#endif // FT_VECTOR_HPP
