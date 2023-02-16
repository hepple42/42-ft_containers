/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:09 by hepple            #+#    #+#             */
/*   Updated: 2023/02/16 11:44:55 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_MAP_HPP
#define FT_MAP_HPP


#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "red_black_tree.hpp"
#include "type_traits.hpp"
#include "utility.hpp"


namespace ft {


/* *** M A P **************************************************************** */

template < typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<Key const, T> > >
class map
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<Key const, T>						value_type;
	typedef Alloc										allocator_type;
	typedef Compare										key_compare;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;


/* *** SUBCLASSES *********************************************************** */

	public:

/* *** Value_Compare ******************************************************** */

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;

		public:

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		
		bool operator()(value_type const &lhs, value_type const &rhs) const
		{
			return _comp(lhs.first, rhs.first);
		}

		protected:
		
		key_compare	_comp;

		value_compare(key_compare kc) : _comp(kc) { }
	};


/* *** MEMBER TYPES ********************************************************* */

	private:

	typedef rb_tree<value_type, value_compare, allocator_type>	tree_type;

	public:

	typedef typename tree_type::iterator				iterator;
	typedef typename tree_type::const_iterator			const_iterator;
	typedef typename tree_type::reverse_iterator		reverse_iterator;
	typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	tree_type _tree;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit map(key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type()) : _tree(value_compare(comp), alloc) { }

	template < typename InputIter >
	map(InputIter first, InputIter last, key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type()) : _tree(value_compare(comp), alloc)
	{
		_tree.insert(first, last);
	}

	map(map const &src) : _tree(src._tree) { }

/* *** Destructor *********************************************************** */

	~map() { }

/* *** Assignment *********************************************************** */

	map &operator=(map const &src)
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

/* *** Element Access ******************************************************* */

	mapped_type &operator[](key_type const &key)
	{
		return (insert(ft::make_pair(key, mapped_type())).first)->second;
	}

	mapped_type &at(key_type const &key)
	{
		iterator it = find(key);

		if (it == end())
			throw std::out_of_range("ft::map::at");

		return it->second;
	}

	mapped_type const &at(key_type const &key) const
	{
		const_iterator it = find(key);

		if (it == end())
			throw std::out_of_range("ft::map::at");

		return it->second;
	}

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val)
	{
		return _tree.insert(val);
	}

	iterator insert(iterator pos, value_type const &val)
	{
		return _tree.insert(pos, val);
	}

	template < typename InputIter >
	void insert(InputIter first, InputIter last)
	{
		_tree.insert(first, last);
	}

	void erase(iterator pos)
	{
		_tree.erase(pos);
	}

	size_type erase(key_type const &key)
	{
		return _tree.erase(ft::make_pair(key, mapped_type()));
	}

	void erase(iterator first, iterator last)
	{
		_tree.erase(first, last);
	}

	void swap(map &m)
	{
		_tree.swap(m._tree);
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

	iterator find(key_type const &key)
	{
		return _tree.find(ft::make_pair(key, mapped_type()));
	}

	const_iterator find(key_type const &key) const
	{
		return _tree.find(ft::make_pair(key, mapped_type()));
	}

	size_type count(key_type const &key) const
	{
		return _tree.count(ft::make_pair(key, mapped_type()));
	}

	iterator lower_bound(key_type const &key)
	{
		return _tree.lower_bound(ft::make_pair(key, mapped_type()));
	}

	const_iterator lower_bound(key_type const &key) const
	{
		return _tree.lower_bound(ft::make_pair(key, mapped_type()));
	}

	iterator upper_bound(key_type const &key)
	{
		return _tree.upper_bound(ft::make_pair(key, mapped_type()));
	}

	const_iterator upper_bound(key_type const &key) const
	{
		return _tree.upper_bound(ft::make_pair(key, mapped_type()));
	}

	pair<iterator, iterator> equal_range(key_type const &key)
	{
		return _tree.equal_range(ft::make_pair(key, mapped_type()));
	}

	pair<const_iterator, const_iterator> equal_range(key_type const &key) const
	{
		return _tree.equal_range(ft::make_pair(key, mapped_type()));
	}

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _tree.get_allocator();
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator==(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator!=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator<(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator<=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator>(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return (rhs < lhs);
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator>=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

/* *** Swap ***************************************************************** */

template < typename Key, typename T, typename Compare, typename Alloc >
void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs)
{
	lhs.swap(rhs);
}


} // namespace ft


#endif // FT_MAP_HPP
