/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:28:52 by hepple            #+#    #+#             */
/*   Updated: 2023/02/20 12:01:01 by hepple           ###   ########.fr       */
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

/* ************************************************************************** **
** VECTOR                                                                     **
**                                                                            **
** Vectors are sequence containers representing arrays that can dynamically   **
** change in size. Like normal arrays, vectors use continuous blocks of       **
** memory for their elements. The storage is handled by the container itself  **
** automatically, potentially allocating some extra storage to accommodate    **
** for possible growth.                                                       **
**                                                                            **
** Due to this memory management system, vectors consume more memory than     **
** arrays, but offer the ability to dynamically change in size.               **
**                                                                            **
** Compared to other containers, the elements of vectors can be accessed very **
** efficiently (constant time), and elements can efficiently be added or      **
** removed at the end of the container. However, when inserting or removing   **
** elements at other positions, vectors perform worse. Also, when running out **
** of memory, all vector elements have to be copied.                          **
**                                                                            **
** [https://cplusplus.com/reference/vector/vector/]                           **
** ************************************************************************** */

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
	pointer			_begin; // begin of allocated and used memory
	pointer			_end; // end of used memory
	pointer			_cap; // end of allocated memory


/* *** MEMBER FUNCTIONS ***************************************************** */

  public:

/* *** Constructor ********************************************************** */

	explicit vector(allocator_type const &alloc = allocator_type())
		: _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL) { }

	explicit vector(size_type n, value_type const &val = value_type(),
					allocator_type const &alloc = allocator_type())
		: _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL)
	{
		if (n > 0)
		{
			_allocate(n);
			_construct(n, val);
		}
	}

	template < typename InputIter >
	vector(InputIter first, InputIter last, allocator_type const &alloc = allocator_type(),
		   typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = 0)
		: _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL)
	{
		_range_init(first, last, iterator_category(first));
	}

	vector(vector const &src)
		: _alloc(src.get_allocator()), _begin(NULL), _end(NULL), _cap(NULL)
	{
		size_type n = src.size();
		if (n > 0)
		{
			_allocate(n);
			_construct(src.begin(), src.end(), ft::iterator_category(src.begin()));
		}
	}

/* *** Destructor *********************************************************** */

	~vector()
	{
		_deallocate();
	}

/* *** Assignment *********************************************************** */

	vector &operator=(vector const &src)
	{
		if (this != &src)
		{
			_alloc = src.get_allocator();
			assign(src.begin(), src.end());
		}

		return *this;
	}

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
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

/* *** Capacity ************************************************************* */

	size_type size() const
	{
		return static_cast<size_type>(_end - _begin);
	}

	size_type max_size() const
	{
		size_type alloc_max = _alloc.max_size();
		size_type type_max = static_cast<size_type>(std::numeric_limits<difference_type>::max());

		if (alloc_max < type_max)
			return alloc_max;
		else
			return type_max;
	}

	void resize(size_type n, value_type val = value_type())
	{
		size_type size_old = size();
		if (size_old < n)
		{
			reserve(_new_capacity(n));
			_construct(n - size_old, val);
		}
		else if (size_old > n)
			_destroy(_begin + n);
	}

	size_type capacity() const
	{
		return static_cast<size_type>(_cap - _begin);
	}

	bool empty() const
	{
		return (_begin == _end);
	}

	void reserve(size_type n)
	{
		if (n > capacity())
		{
			vector tmp(_alloc);
			tmp._allocate(n);
			tmp._construct(_begin, _end, ft::iterator_category(_begin));

			swap(tmp);
		}
	}

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
		if (n >= size())
			throw std::out_of_range("ft::vector");

		return *(_begin + n);
	}

	const_reference at(size_type n) const
	{
		if (n >= size())
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

	void assign(size_type n, value_type const &val)
	{
		if (n > capacity())
		{
			vector tmp(n, val);
			swap(tmp);
		}
		else
		{
			size_type size_old = size();
			if (n > size_old)
			{
				for (size_type i = 0; i < size_old; ++i)
					*(_begin + i) = val;
				_construct(n - size_old, val);
			}
			else
			{
				for (size_type i = 0; i < n; ++i)
					*(_begin + i) = val;
				_destroy(_begin + n);
			}
		}
	}

	template < class InputIter >
	void assign(InputIter first, InputIter last,
				typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = 0)
	{
		_range_assign(first, last, ft::iterator_category(first));
	}

	void push_back(value_type const &val)
	{
		if (_end == _cap)
			reserve(_new_capacity(size() + 1));
		_construct(1, val);
	}

	void pop_back()
	{
		_destroy(_end - 1);
	}

	iterator insert(iterator pos, value_type const &val)
	{
		difference_type diff = pos - begin();
		insert(pos, 1, val);

		return begin() + diff;
	}

	void insert(iterator pos, size_type n, value_type const &val)
	{
		if (n > 0)
		{
			size_type pos_insert = pos - begin();
			size_type size_old = size();
			resize(size_old + n);

			iterator first_from = begin() + pos_insert;
			iterator last_from = begin() + size_old;
			iterator last_to = begin() + size();
			while (last_from != first_from)
			{
				--last_to;
				--last_from;
				*last_to = *last_from;
			}

			for (size_type i = 0; i < n; ++i)
				*(_begin + pos_insert + i) = val;
		}
	}

	template < class InputIter >
	void insert(iterator pos, InputIter first, InputIter last,
				typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = 0)
	{
		_range_insert(pos, first, last, ft::iterator_category(first));
	}

	iterator erase(iterator pos)
	{
		for (size_type i = pos - begin(); i < size() - 1; ++i)
			*(_begin + i) = *(_begin + i + 1);
		pop_back();

		return pos;
	}

	iterator erase(iterator first, iterator last)
	{
		size_type dist = last - first;
		for (size_type i = first - begin(); i < size() - dist; ++i)
			*(_begin + i) = *(_begin + i + dist);
		_destroy(_end - dist);

		return first;
	}

	void swap(vector &v)
	{
		if (this == &v)
			return;

		ft::swap(_alloc, v._alloc);
		ft::swap(_begin, v._begin);
		ft::swap(_end, v._end);
		ft::swap(_cap, v._cap);
	}

	void clear()
	{
		_destroy(_begin);
	}

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _alloc;
	}


  private:

/* *** Allocation / Deallocation ******************************************** */

	void _allocate(size_type n)
	{
		if (n > max_size())
			throw std::length_error("ft::vector");

		_begin = _alloc.allocate(n);
		_end = _begin;
		_cap = _begin + n;
	}

	void _deallocate()
	{
		if (_begin == NULL)
			return;

		clear();

		_alloc.deallocate(_begin, capacity());
		_begin = NULL;
		_end = NULL;
		_cap = NULL;
	}

/* *** Construction / Destruction ******************************************* */

	void _construct(size_type n, const_reference val = value_type())
	{
		for (size_type i = 0; i < n; ++i)
		{
			_alloc.construct(_end, val);
			++_end;
		}
	}

	template < typename FwdIter >
	void _construct(FwdIter first, FwdIter last, ft::forward_iterator_tag)
	{
		while (first != last)
		{
			_alloc.construct(_end, *first);
			++_end;
			++first;
		}
	}

	void _destroy(pointer new_end)
	{
		while (_end != new_end)
		{
			--_end;
			_alloc.destroy(_end);
		}
	}

/* *** Range **************************************************************** */

	template < typename InputIter >
	void _range_init(InputIter first, InputIter last, ft::input_iterator_tag)
	{
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	template < typename FwdIter >
	void _range_init(FwdIter first, FwdIter last, ft::forward_iterator_tag)
	{
		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			_allocate(n);
			_construct(first, last, ft::iterator_category(first));
		}
	}

	template < typename InputIter >
	void _range_assign(InputIter first, InputIter last, ft::input_iterator_tag)
	{
		clear();

		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	template < typename FwdIter >
	void _range_assign(FwdIter first, FwdIter last, ft::forward_iterator_tag)
	{
		clear();

		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			if (n > capacity())
			{
				_deallocate();
				_allocate(n);
			}
			_construct(first, last, ft::iterator_category(first));
		}
	}

	template < typename InputIter >
	void _range_insert(iterator pos, InputIter first, InputIter last, ft::input_iterator_tag)
	{
		if (pos == end())
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		else
		{
			vector tmp(first, last);
			insert(pos, tmp.begin(), tmp.end());
		}
	}

	template < typename FwdIter >
	void _range_insert(iterator pos, FwdIter first, FwdIter last, ft::forward_iterator_tag)
	{
		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			size_type pos_insert = pos - begin();
			size_type size_old = size();
			resize(size_old + n);

			iterator first_from = begin() + pos_insert;
			iterator last_from = begin() + size_old;
			iterator last_to = begin() + size();
			while (last_from != first_from)
			{
				--last_to;
				--last_from;
				*last_to = *last_from;
			}

			for (size_type i = 0; i < n; ++i)
			{
				*(_begin + pos_insert + i) = *first;
				++first;
			}
		}
	}

/* *** Capacity ************************************************************* */

	size_type _new_capacity(size_type size_new) const
	{
		size_type size_max = max_size();
		if (size_new > size_max)
			throw std::length_error("ft::vector");

		size_type cap_old = capacity();
		size_type cap_new = cap_old * 2;
		if (cap_old >= size_new)
			return cap_old;
		else if (cap_new > size_max)
			return size_max;
		else if (cap_new < size_new)
			return size_new;
		else
			return cap_new;
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
