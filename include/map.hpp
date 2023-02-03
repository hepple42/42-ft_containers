/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:09 by hepple            #+#    #+#             */
/*   Updated: 2023/02/03 10:32:49 by hepple           ###   ########.fr       */
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

/* *** SUBCLASSES *********************************************************** */

/* *** Value_Compare ******************************************************** */


/* *** MEMBER TYPES ********************************************************* */

	private:

	// typedef tree_type;
	// typedef value_type_compare;

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
	// typedef tree_type::iterator							iterator;
	// typedef tree_type::const_iterator					const_iterator;
	// typedef tree_type::reverse_iterator					reverse_iterator;
	// typedef tree_type::const_reverse_iterator			const_reverse_iterator;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	// tree_type _tree;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit map(key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type());

	template < typename InputIter >
	map(InputIter first, InputIter last, key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type());

	map(map const &src);

/* *** Destructor *********************************************************** */

	~map() { }

/* *** Assignment *********************************************************** */

	map &operator=(map const &src);

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

/* *** Element Access ******************************************************* */

	mapped_type &operator[](key_type const &key);

	mapped_type &at(key_type const &key);

	mapped_type const &at(key_type const &key) const;

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val);

	iterator insert(iterator pos, value_type const &val);

	template < typename InputIter >
	void insert(InputIter first, InputIter last);

	void erase(iterator pos);

	size_type erase(key_type const &key);

	void erase(iterator first, iterator last);

	void swap(map &m);

	void clear();

/* *** Observers ************************************************************ */

	key_compare key_comp() const;

	value_compare value_comp() const;

/* *** Operations *********************************************************** */

	iterator find(key_type const &key);

	const_iterator find(key_type const &key) const;

	size_type count(key_type const &key) const;

	iterator lower_bound(key_type const &key);

	const_iterator lower_bound(key_type const &key) const;

	iterator upper_bound(key_type const &key);

	const_iterator upper_bound(key_type const &key) const;

	pair<const_iterator, const_iterator> equal_range(key_type const &key) const;

	pair<iterator,iterator> equal_range(key_type const &key);

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const;

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator==(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator!=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator<(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator<=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator>(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

template < typename Key, typename T, typename Compare, typename Alloc >
bool operator>=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs);

/* *** Swap ***************************************************************** */

template < typename Key, typename T, typename Compare, typename Alloc >
void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs);


} // namespace ft


#endif // FT_MAP_HPP
