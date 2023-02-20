/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:20:12 by hepple            #+#    #+#             */
/*   Updated: 2023/02/20 13:02:00 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_SET_HPP
#define FT_SET_HPP


#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "red_black_tree.hpp"
#include "type_traits.hpp"
#include "utility.hpp"


namespace ft {


/* *** S E T **************************************************************** */

/* ************************************************************************** **
** SET                                                                        **
**                                                                            **
** Sets are associative containers that store elements following some         **
** specific order. The value of an element also identifies it, therefore it   **
** must be unique. Values cannot be modified once an element has been added   **
** to the container.                                                          **
**                                                                            **
** Internally, the elements of a set are sorted by their values, following a  **
** strict weak ordering defined through its internal comparison object.       **
** Using this ordering, iterations over subsets are possible.                 **
**                                                                            **
** Sets are typically implemented as binary search trees. This set uses a red **
** black tree as an underlying data structure, which offers a balance between **
** fast insertion or deletion and fast element search.                        **
**                                                                            **
** [https://cplusplus.com/reference/set/set/]                                 **
** ************************************************************************** */

template < typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
class set
{

/* *** MEMBER TYPES ********************************************************* */

  public:

	typedef T											key_type;
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef Compare										key_compare;
	typedef Compare										value_compare;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

  private:

	typedef rb_tree<value_type, value_compare, allocator_type>	tree_type;

  public:

	typedef typename tree_type::difference_type			difference_type;
	typedef typename tree_type::size_type				size_type;
	typedef typename tree_type::const_iterator			iterator;
	typedef typename tree_type::const_iterator			const_iterator;
	typedef typename tree_type::const_reverse_iterator	reverse_iterator;
	typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;


/* *** MEMBER VARIABLES ***************************************************** */

  private:

	tree_type _tree; // red black tree


/* *** MEMBER FUNCTIONS ***************************************************** */

  public:

/* *** Constructor ********************************************************** */

	explicit set(key_compare const &comp = key_compare(),
				 allocator_type const &alloc = allocator_type())
		: _tree(comp, alloc) { }

	template < typename InputIter >
	set(InputIter first, InputIter last, key_compare const &comp = key_compare(),
		allocator_type const &alloc = allocator_type())
		: _tree(comp, alloc)
	{
		_tree.insert(first, last);
	}

	set(set const &src)
		: _tree(src._tree) { }

/* *** Destructor *********************************************************** */

	~set() { }

/* *** Assignment *********************************************************** */

	set &operator=(set const &src)
	{
		if (this != &src)
			_tree = src._tree;

		return *this;
	}

/* *** Iterators ************************************************************ */

	iterator begin()
	{
		return _tree.begin();
	}

	const_iterator begin() const
	{
		return _tree.begin();
	}

	iterator end()
	{
		return _tree.end();
	}

	const_iterator end() const
	{
		return _tree.end();
	}

	reverse_iterator rbegin()
	{
		return _tree.rbegin();
	}

	const_reverse_iterator rbegin() const
	{
		return _tree.rbegin();
	}

	reverse_iterator rend()
	{
		return _tree.rend();
	}

	const_reverse_iterator rend() const
	{
		return _tree.rend();
	}

/* *** Capacity ************************************************************* */

	bool empty() const
	{
		return _tree.empty();
	}

	size_type size() const
	{
		return _tree.size();
	}

	size_type max_size() const
	{
		return _tree.max_size();
	}

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val)
	{
		return _tree.insert(val);
	}

	iterator insert(__attribute__((unused)) iterator pos, value_type const &val)
	{
		return (_tree.insert(val)).first;
	}

	template < typename InputIter >
	void insert(InputIter first, InputIter last)
	{
		_tree.insert(first, last);
	}

	void erase(iterator pos)
	{
		_tree.erase(*pos);
	}

	size_type erase(value_type const &val)
	{
		return _tree.erase(val);
	}

	void erase(iterator first, iterator last)
	{
		for (iterator tmp = first; tmp != last; tmp = first)
		{
			++first;
			_tree.erase(*tmp);
		}
	}

	void swap(set &s)
	{
		_tree.swap(s._tree);
	}

	void clear()
	{
		_tree.clear();
	}

/* *** Observers ************************************************************ */

	key_compare key_comp() const
	{
		return key_compare();
	}

	value_compare value_comp() const
	{
		return _tree.value_comp();
	}

/* *** Operations *********************************************************** */

	iterator find(value_type const &val) const
	{
		return _tree.find(val);
	}

	size_type count(value_type const &val) const
	{
		return _tree.count(val);
	}

	iterator lower_bound(value_type const &val) const
	{
		return _tree.lower_bound(val);
	}

	iterator upper_bound(value_type const &val) const
	{
		return _tree.upper_bound(val);
	}

	pair<iterator, iterator> equal_range(value_type const &val) const
	{
		return _tree.equal_range(val);
	}

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _tree.get_allocator();
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename T, typename Compare, typename Alloc >
bool operator==(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template < typename T, typename Compare, typename Alloc >
bool operator!=(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

template < typename T, typename Compare, typename Alloc >
bool operator<(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template < typename T, typename Compare, typename Alloc >
bool operator<=(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

template < typename T, typename Compare, typename Alloc >
bool operator>(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return (rhs < lhs);
}

template < typename T, typename Compare, typename Alloc >
bool operator>=(set<T, Compare, Alloc> const &lhs, set<T, Compare, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

/* *** Swap ***************************************************************** */

template < typename T, typename Compare, typename Alloc >
void swap(set<T, Compare, Alloc> &lhs, set<T, Compare, Alloc> &rhs)
{
	lhs.swap(rhs);
}


} // namespace ft


#endif // FT_SET_HPP
