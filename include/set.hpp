/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:20:12 by hepple            #+#    #+#             */
/*   Updated: 2023/02/14 10:52:13 by hepple           ###   ########.fr       */
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

	explicit set(key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type());

	template < typename InputIter >
	set(InputIter first, InputIter last, key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type());

	set(set const &src);

/* *** Destructor *********************************************************** */

	~set() { }

/* *** Assignment *********************************************************** */

	set &operator=(set const &src);

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

	bool empty() const;

	size_type size() const;

	size_type max_size() const;

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val);

	iterator insert(iterator pos, value_type const &val);

	template < typename InputIter >
	void insert(InputIter first, InputIter last);

	void erase(iterator pos);

	size_type erase(value_type const &val);

	void erase(iterator first, iterator last);

	void swap(set &s);

	void clear();

/* *** Observers ************************************************************ */

	key_compare key_comp() const;

	value_compare value_comp() const;

/* *** Operations *********************************************************** */

	iterator find(value_type const &val) const;

	size_type count(value_type const &val) const;

	iterator lower_bound(value_type const &val) const;

	iterator upper_bound(value_type const &val) const;

	pair<iterator, iterator> equal_range(value_type const &val) const;

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const;

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
