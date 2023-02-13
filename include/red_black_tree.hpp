/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:21:26 by hepple            #+#    #+#             */
/*   Updated: 2023/02/13 18:34:42 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_RED_BLACK_TREE_HPP
#define FT_RED_BLACK_TREE_HPP


#include <cstddef>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"


namespace ft {


template < typename T, typename DiffType >
class tree_iterator;

template < typename T, typename DiffType >
class const_tree_iterator;


/* *** NODE_COLOR *********************************************************** */

enum NODE_COLOR
{
	BLACK = 0,
	RED = 1
};


/* *** N O D E ************************************************************** */

template < typename T >
struct node
{

/* *** MEMBER TYPES ********************************************************* */

	typedef T				value_type;
	typedef node<T> *		pointer;
	typedef node<T> const *	const_pointer;


/* *** MEMBER VARIABLES ***************************************************** */

	NODE_COLOR	color;
	pointer		parent;
	pointer		left;
	pointer		right;
	value_type	value;


/* *** MEMBER FUNCTIONS ***************************************************** */

/* *** Constructor ********************************************************** */

	node() : color(BLACK), parent(NULL), left(NULL), right(NULL), value() { }

	node(value_type val, NODE_COLOR col = BLACK) : color(col), parent(NULL), left(NULL), right(NULL), value(val) { }

	node(node const &src) : color(src.color), parent(src.parent), left(src.left), right(src.right), value(src.value) { }

/* *** Destructor *********************************************************** */

	~node() { }

/* *** Assignment *********************************************************** */

	node &operator=(node const &src)
	{
		if (this != &src)
		{
			color = src.color;
			parent = src.parent;
			left = src.left;
			right = src.right;
			value = src.value;
		}

		return *this;
	}

/* *** Color **************************************************************** */

	void flip_color()
	{
		if (color = BLACK)
			color = RED;
		else
			color = BLACK;
	}

};


/* *** RED_BLACK_TREE ALGORITHMS ******************************************** */

/* *** Min / Max ************************************************************ */

template < typename NodePtr >
NodePtr rbt_min_node(NodePtr node)
{
	while (node->left != NULL)
		node = node->left;
	return node;
}

template < typename NodePtr >
NodePtr rbt_max_node(NodePtr node)
{
	while (node->right != NULL)
		node = node->right;
	return node;
}

/* *** Previous / Next ****************************************************** */

template < typename NodePtr >
NodePtr rbt_prev_node(NodePtr node)
{
	if (node->left != NULL)
		return rbt_max_node(node->left);

	while (node == node->parent->left)
		node = node->parent;
	return node->parent;
}

template < typename NodePtr >
NodePtr rbt_next_node(NodePtr node)
{
	if (node->right != NULL)
		return rbt_min_node(node->right);

	while (node == node->parent->right)
		node = node->parent;
	return node->parent;
}


/* *** T R E E _ I T E R A T O R ******************************************** */

template < typename T, typename DiffType >
class tree_iterator
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef T										value_type;
	typedef DiffType								difference_type;
	typedef T *										pointer;
	typedef T &										reference;
	typedef bidirectional_iterator_tag				iterator_category;
	typedef ft::const_tree_iterator<T, DiffType>	const_iterator;

	private:

	typedef typename ft::node<T>::pointer		node_pointer;
	typedef typename ft::node<T>::const_pointer	const_node_pointer;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	node_pointer	_current;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	tree_iterator() : _current(NULL) { }

	tree_iterator(node_pointer node) : _current(node) { }

	tree_iterator(tree_iterator const &src) : _current(src._current) { }

/* *** Destructor *********************************************************** */

	~tree_iterator() { }

/* *** Assignment *********************************************************** */

	tree_iterator &operator=(tree_iterator const &src)
	{
		_current = src._current;
		return *this;
	}

/* *** Access *************************************************************** */

	node_pointer base() const
	{
		return _current;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator*() const
	{
		return _current->value;
	}

/* *** Increment / Decrement ************************************************ */

	tree_iterator &operator++()
	{
		_current = rbt_next_node<node_pointer>(_current);
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	tree_iterator &operator--()
	{
		_current = rbt_prev_node<node_pointer>(_current);
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		--(*this);
		return tmp;
	}

/* *** Relational Operators ************************************************* */

	bool operator==(tree_iterator const &rhs) const
	{
		return (_current == rhs._current);
	}

	bool operator==(const_iterator const &rhs) const
	{
		return (_current == rhs.base());
	}

	bool operator!=(tree_iterator const &rhs) const
	{
		return !(*this == rhs);
	}

	bool operator!=(const_iterator const &rhs) const
	{
		return !(*this == rhs);
	}

};


/* *** C O N S T _ T R E E _ I T E R A T O R ******************************** */

template < typename T, typename DiffType >
class const_tree_iterator
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef T								value_type;
	typedef DiffType						difference_type;
	typedef T const *						pointer;
	typedef T const &						reference;
	typedef bidirectional_iterator_tag		iterator_category;
	typedef ft::tree_iterator<T, DiffType>	non_const_iterator;

	private:

	typedef typename ft::node<T>::pointer		node_pointer;
	typedef typename ft::node<T>::const_pointer	const_node_pointer;


/* *** MEMBER VARIABLES ***************************************************** */

	private:

	const_node_pointer	_current;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	const_tree_iterator() : _current(NULL) { }

	const_tree_iterator(const_node_pointer node) : _current(node) { }

	const_tree_iterator(const_tree_iterator const &src) : _current(src._current) { }

	const_tree_iterator(non_const_iterator const &src) : _current(src.base()) { }

/* *** Destructor *********************************************************** */

	~const_tree_iterator() { }

/* *** Assignment *********************************************************** */

	const_tree_iterator &operator=(const_tree_iterator const &src)
	{
		_current = src._current;
		return *this;
	}

/* *** Access *************************************************************** */

	const_node_pointer base() const
	{
		return _current;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator*() const
	{
		return _current->value;
	}

/* *** Increment / Decrement ************************************************ */

	const_tree_iterator &operator++()
	{
		_current = rbt_next_node<const_node_pointer>(_current);
		return *this;
	}

	const_tree_iterator operator++(int)
	{
		const_tree_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	const_tree_iterator &operator--()
	{
		_current = rbt_prev_node<const_node_pointer>(_current);
		return *this;
	}

	const_tree_iterator operator--(int)
	{
		const_tree_iterator tmp(*this);
		--(*this);
		return tmp;
	}

/* *** Relational Operators ************************************************* */

	bool operator==(const_tree_iterator const &rhs) const
	{
		return (_current == rhs._current);
	}

	bool operator==(non_const_iterator const &rhs) const
	{
		return (_current == rhs.base());
	}

	bool operator!=(const_tree_iterator const &rhs) const
	{
		return !(*this == rhs);
	}

	bool operator!=(non_const_iterator const &rhs) const
	{
		return !(*this == rhs);
	}

};


/* *** R B _ T R E E ******************************************************** */

template < typename T, typename Compare, typename Alloc >
class rb_tree
{

/* *** MEMBER TYPES ********************************************************* */

	public:

	typedef T															value_type;
	typedef Compare														value_compare;
	typedef Alloc														allocator_type;
	typedef typename allocator_type::difference_type					difference_type;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef ft::node<value_type>										node_type;
	typedef typename node_type::pointer									node_pointer;
	typedef typename node_type::const_pointer							const_node_pointer;
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;
	typedef ft::tree_iterator<value_type, difference_type>				iterator;
	typedef ft::const_tree_iterator<value_type, difference_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;


/* *** MEMBER VARIABLES ***************************************************** */

	private: // protected ???

	value_compare		_comp;
	allocator_type		_value_alloc;
	node_allocator_type	_node_alloc;
	size_type			_size;
	node_pointer		_nil;
	node_pointer		_head;
	node_pointer		_leftmost;


/* *** MEMBER FUNCTIONS ***************************************************** */

	public:

/* *** Constructor ********************************************************** */

	explicit rb_tree(value_compare const &comp, allocator_type const &alloc) : _comp(comp), _value_alloc(alloc), _node_alloc(alloc), _size(0)
	{
		_create_nil();
		_head = _construct_node(value_type(), BLACK);
		_head->parent = _head;
		_leftmost = _head;
	}

	rb_tree(rb_tree const &src) : _comp(src._comp), _value_alloc(src._value_alloc), _node_alloc(src._node_alloc), _size(src._size)
	{
		create_nil();
		_head = _construct_node(value_type(), BLACK);
		_head->parent = _head;
		_leftmost = _head;

		*this = src;
	}

/* *** Destructor *********************************************************** */

	~rb_tree();

/* *** Assignment *********************************************************** */

	rb_tree &operator=(rb_tree const &src);

/* *** Iterators ************************************************************ */

	iterator begin()
	{
		return iterator(_leftmost);
	}

	const_iterator begin() const
	{
		return const_iterator(_leftmost);
	}

	iterator end()
	{
		return iterator(_head);
	}

	const_iterator end() const
	{
		return const_iterator(_head);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(_head);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(_head);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_leftmost);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_leftmost);
	}

/* *** Capacity ************************************************************* */

	bool empty() const
	{
		return (_size == 0);
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return _value_alloc.max_size();
	}

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val);

	iterator insert(iterator pos, value_type const &val);

	template < typename InputIter >
	void insert(InputIter first, InputIter last);

	void erase(iterator pos);

	size_type erase(value_type const &val);

	void erase(iterator first, iterator last);

	void swap(rb_tree &t);

	void clear();

/* *** Observers ************************************************************ */

	value_compare value_comp() const
	{
		return _comp;
	}

/* *** Operations *********************************************************** */

	iterator find(value_type const &val)
	{
		node_pointer tmp = _root();
		while (tmp != _nil)
		{
			if (_comp(val, tmp->_value))
				tmp = tmp->_left;
			else if (_comp(tmp->_value, val))
				tmp = tmp->right;
			else
				return iterator(tmp);
		}
		return end();
	}

	const_iterator find(value_type const &val) const
	{
		const_node_pointer tmp = _root();
		while (tmp != _nil)
		{
			if (_comp(val, tmp->_value))
				tmp = tmp->_left;
			else if (_comp(tmp->_value, val))
				tmp = tmp->right;
			else
				return const_iterator(tmp);
		}
		return end();
	}

	size_type count(value_type const &val) const;

	iterator lower_bound(value_type const &val);

	const_iterator lower_bound(value_type const &val) const;

	iterator upper_bound(value_type const &val);

	const_iterator upper_bound(value_type const &val) const;

	pair<iterator, iterator> equal_range(value_type const &val);

	pair<const_iterator, const_iterator> equal_range(value_type const &val) const;

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _value_alloc;
	}


	private:

	node_pointer _root() const
	{
		return _head->_left;
	}

	void _create_nil()
	{
		_nil = _node_alloc.allocate(1);
		_value_alloc.construct(&(_nil->value), value_type());
		new_node->color = BLACK;
		new_node->parent = NULL;
		new_node->left = NULL;
		new_node->right = NULL;
	}

	node_pointer _construct_node(value_type const &val, NODE_COLOR color = RED)
	{
		node_pointer new_node = _node_alloc.allocate(1);
		_value_alloc.construct(&(new_node->value), val); // !!!
		new_node->color = color;
		new_node->parent = _nil;
		new_node->left = _nil;
		new_node->right = _nil;

		return new_node;
	}

};


/* *** NON-MEMBER FUNCTION OVERLOADS **************************************** */

/* *** Swap ***************************************************************** */

template < typename T, typename Compare, typename Alloc >
void swap(rb_tree<T, Compare, Alloc> &lhs, rb_tree<T, Compare, Alloc> &rhs)
{
	lhs.swap(rhs);
}


} // namespace ft


#endif // FT_RED_BLACK_TREE_HPP
