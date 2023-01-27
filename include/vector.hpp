/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:28:52 by hepple            #+#    #+#             */
/*   Updated: 2023/01/27 14:46:22 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP


#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"


namespace ft {


/* *** V E C T O R ********************************************************** */

template < typename T, typename Alloc = std::allocator<T> >
class vector
{
	
/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::normal_iterator<pointer>				iterator;
	typedef ft::normal_iterator<const_pointer>			const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	allocator_type	_alloc;
	pointer			_begin;
	pointer			_end;
	pointer			_cap;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit vector(allocator_type const &alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL) { }
	
	explicit vector(size_type n, value_type const &val = value_type(), allocator_type const &alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL)
	{
		if (n > 0)
		{
			if (n > max_size())
				throw std::length_error("ft::vector");

			_begin = _alloc.allocate(n);
			_end = _begin;
			_cap = _begin + n;

			while (_end != _cap)
			{
				_alloc.construct(_end, val);
				++_end;
			}
		}
	}

	template < typename InputIterator >
	vector(InputIterator first, InputIterator last, allocator_type const &alloc = allocator_type());
	vector(vector const &src);

/* *** Destructor *********************************************************** */

	~vector()
	{
		if (_begin != NULL)
		{
			while(_end != _begin)
			{
				--_end;
				_alloc.destroy(_end);
			}

			_alloc.deallocate(_begin, capacity());

			_begin = NULL;
			_end = NULL;
			_cap = NULL;
		}
	}

/* *** Assignment *********************************************************** */

	// vector &operator=(vector const &src)
	// {
	// 	if (this != &src)
	// 	{
	// 		_alloc = src.get_allocator();
	// 		// ASSIGN!!!
	// 	}

	// 	return *this;
	// }

/* *** Iterators ************************************************************ */

	iterator begin()
	{
		return iterator(_begin);
	}

	const_iterator begin() const
	{
		return const_iterator(_begin);
	}

	iterator end()
	{
		return iterator(_end);
	}

	const_iterator end() const
	{
		return const_iterator(_end);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(_begin);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(_begin);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_end);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_end);
	}

/* *** Capacity ************************************************************* */

	size_type size() const
	{
		return static_cast<size_type>(_end - _begin);
	}

	size_type max_size() const;

	void resize(size_type n, value_type val = value_type());

	size_type capacity() const
	{
		return static_cast<size_type>(_cap - _begin);
	}

	bool empty() const
	{
		return (_begin == _end);
	}

	// void reserve(size_type n)
	// {
	// 	if (n > capacity())
	// 	{
	// 		if (n > max_size())
	// 			throw std::length_error("ft::vector");

	// 		ft::vector tmp(_alloc);

	// 		tmp._begin = tmp._alloc.allocate(n);
	// 		tmp._end = tmp._begin;
	// 		tmp._cap = tmp._begin + n;

	// 		while (_end != _cap)
	// 		{
	// 			_alloc.construct(_end, val);
	// 			++_end;
	// 		}
	// 	}
	// }

/* *** Element Access ******************************************************* */

	reference operator[](size_type n)
	{
		return *(_begin + n);
	}

	const_reference operator[](size_type n) const
	{
		return *(_begin + n);
	}

	reference at(size_type n)
	{
		if (n > size())
			throw std::out_of_range("ft::vector");
		return *(_begin + n);
	}

	const_reference at(size_type n) const
	{
		if (n > size())
			throw std::out_of_range("ft::vector");
		return *(_begin + n);
	}

	reference front()
	{
		return *_begin;
	}

	const_reference front() const
	{
		return *_begin;
	}

	reference back()
	{
		return *(_end - 1);
	}

	const_reference back() const
	{
		return *(_end - 1);
	}

	value_type *data()
	{
		return _begin;
	}

	value_type const *data() const
	{
		return _begin;
	}

/* *** Modifiers ************************************************************ */

	void assign(size_type n, value_type const &val);
	template < class InputIterator >
	void assign(InputIterator first, InputIterator last);

	void push_back(value_type const &val);

	void pop_back()
	{
		--_end;
		_alloc.destroy(_end);
	}

	iterator insert(iterator position, value_type const &val);
	void insert(iterator position, size_type n, value_type const &val);
	template < class InputIterator >
	void insert(iterator position, InputIterator first, InputIterator last);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	void swap(vector &v);

	void clear()
	{
		while(_end != _begin)
		{
			--_end;
			_alloc.destroy(_end);
		}
	}

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _alloc;
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename T, typename Alloc >
bool operator==(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template < typename T, typename Alloc >
bool operator!=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

template < typename T, typename Alloc >
bool operator<(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template < typename T, typename Alloc >
bool operator<=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

template < typename T, typename Alloc >
bool operator>(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return (rhs < lhs);
}

template < typename T, typename Alloc >
bool operator>=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

/* *** Swap ***************************************************************** */

template < typename T, typename Alloc >
void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
{
	lhs.swap(rhs);
}


} // namespace ft


#endif // FT_VECTOR_HPP
