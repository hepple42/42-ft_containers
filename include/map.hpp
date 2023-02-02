/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:09 by hepple            #+#    #+#             */
/*   Updated: 2023/02/02 17:27:32 by hepple           ###   ########.fr       */
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

/* *** Destructor *********************************************************** */

/* *** Assignment *********************************************************** */

/* *** Iterators ************************************************************ */

/* *** Capacity ************************************************************* */

/* *** Element Access ******************************************************* */

/* *** Modifiers ************************************************************ */

/* *** Observers ************************************************************ */

/* *** Operations *********************************************************** */

/* *** Allocator ************************************************************ */

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Relational Operators ************************************************* */

/* *** Swap ***************************************************************** */


} // namespace ft


#endif // FT_MAP_HPP
