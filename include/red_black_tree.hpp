/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:21:26 by hepple            #+#    #+#             */
/*   Updated: 2023/02/20 11:05:01 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_RED_BLACK_TREE_HPP
#define FT_RED_BLACK_TREE_HPP


#include <cstddef>
#include <iostream>
#include <string>

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

	value_type	value;
	NODE_COLOR	color;
	pointer		parent;
	pointer		left;
	pointer		right;


/* *** MEMBER FUNCTIONS ***************************************************** */

/* *** Constructor ********************************************************** */

	node() : color(BLACK), parent(NULL), left(NULL), right(NULL), value() { }

	explicit node(value_type val, NODE_COLOR col = BLACK) : color(col), parent(NULL), left(NULL), right(NULL), value(val) { }

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

};


/* *** RED_BLACK_TREE ALGORITHMS ******************************************** */

/* *** Min / Max ************************************************************ */

template < typename NodePtr >
NodePtr rbt_min_node(NodePtr node)
{
	// min node is leftmost node
	while (node != NULL && node->left != NULL && node->left->right != NULL) // node->left == _nil
		node = node->left;

	return node;
}

template < typename NodePtr >
NodePtr rbt_max_node(NodePtr node)
{
	// max node is rightmost node
	while (node != NULL && node->right != NULL && node->right->right != NULL) // node->right == _nil
		node = node->right;

	return node;
}

/* *** Previous / Next ****************************************************** */

template < typename NodePtr >
NodePtr rbt_prev_node(NodePtr node)
{
	if (node == NULL || node->left == NULL)
		return node;

	// if left subtree is non-empty, prev node is max node of this subtree
	if (node->left->right != NULL) // node->left == _nil
		return rbt_max_node(node->left);

	// else prev node is lowest ancestor whose right child is also an ancestor
	while (node == node->parent->left)
		node = node->parent;
	return node->parent;
}

template < typename NodePtr >
NodePtr rbt_next_node(NodePtr node)
{
	if (node == NULL || node->right == NULL)
		return node;

	// if right subtree is non-empty, next node is min node of this subtree
	if (node->right->right != NULL) // node->right == _nil
		return rbt_min_node(node->right);

	// else next node is lowest ancestor whose left child is also an ancestor
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

	reference operator*() const
	{
		return _current->value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

/* *** Increment / Decrement ************************************************ */

	tree_iterator &operator++()
	{
		_current = rbt_next_node<node_pointer>(_current);
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp = *this;
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
		tree_iterator tmp = *this;
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

	reference operator*() const
	{
		return _current->value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

/* *** Increment / Decrement ************************************************ */

	const_tree_iterator &operator++()
	{
		_current = rbt_next_node<const_node_pointer>(_current);
		return *this;
	}

	const_tree_iterator operator++(int)
	{
		const_tree_iterator tmp = *this;
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
		const_tree_iterator tmp = *this;
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

/* ************************************************************************** **
** RED BLACK TREE                                                             **
**                                                                            **
** - A red black tree (RBT) is a self-balancing binary search tree (BST)      **
** - Every tree node has an additional property, its color, which can be      **
**   either red or black.                                                     **
** - The balancing of the RBT is based on rules for the node colors, and is   **
**   performed using rotations and recoloring                                 **
** - The balancing is not perfect, but guarantees a compromise between fast   **
**   insertion or deletion (O(log n)) and fast searching (O(log n)).          **
**                                                                            **
** - Rules for RBTs:                                                          **
**   1. Every node is either red or black                                     **
**   2. The root node is black                                                **
**   3. Every leaf node (nil) is black                                        **
**   4. Both children of each red node are black                              **
**   5. Every path from a given node down to every of its descendant nil      **
**      nodes contains the same number of black nodes                         **
**                                                                            **
** Implementation based on                                                    **
** Cormen, Leiserson, Rivest, and Stein:                                      **
** Introduction to Algorithms - Third Edition                                 **
** ************************************************************************** */

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

  private:

	value_compare		_comp;
	allocator_type		_value_alloc;
	node_allocator_type	_node_alloc;
	size_type			_size;
	node_pointer		_nil; // nil node, root node is its left child
	node_pointer		_begin_node; // leftmost node of tree


/* *** MEMBER FUNCTIONS ***************************************************** */

  public:

/* *** Constructor ********************************************************** */

	explicit rb_tree(value_compare const &comp, allocator_type const &alloc) : _comp(comp), _value_alloc(alloc), _node_alloc(alloc), _size(0)
	{
		_create_nil();
		_begin_node = _end_node();
	}

	rb_tree(rb_tree const &src) : _comp(src._comp), _value_alloc(src._value_alloc), _node_alloc(src._node_alloc), _size(0)
	{
		_create_nil();
		_begin_node = _end_node();

		*this = src;
	}

/* *** Destructor *********************************************************** */

	~rb_tree()
	{
		_destroy(_root());

		_value_alloc.destroy(&(_nil->value));
		_node_alloc.deallocate(_nil, 1);
	}

/* *** Assignment *********************************************************** */

	rb_tree &operator=(rb_tree const &src)
	{
		if (this == &src)
			return *this;

		clear();

		_comp = src._comp;

		if (src._root() != src._nil)
		{
			_root() = _copy(src, src._root());
			_root()->parent = _nil;
			_begin_node = rbt_min_node(_root());
		}

		return *this;
	}

/* *** Iterators ************************************************************ */

	iterator begin()
	{
		return iterator(_begin_node);
	}

	const_iterator begin() const
	{
		return const_iterator(_begin_node);
	}

	iterator end()
	{
		return iterator(_end_node());
	}

	const_iterator end() const
	{
		return const_iterator(_end_node());
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(_end_node());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(_end_node());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_begin_node);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_begin_node);
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
		return _node_alloc.max_size();
	}

/* *** Modifiers ************************************************************ */

	pair<iterator, bool> insert(value_type const &val)
	{
		return _insert(val);
	}

	iterator insert(__attribute__((unused)) iterator pos, value_type const &val)
	{
		return _insert(val).first;
	}

	template < typename InputIter >
	void insert(InputIter first, InputIter last)
	{
		while (first != last)
		{
			_insert(*first);
			++first;
		}
	}

	void erase(iterator pos)
	{
		_erase(pos.base());
	}

	size_type erase(value_type const &val)
	{
		iterator found = find(val);

		if (found == end())
			return 0;

		_erase(found.base());
		return 1;
	}

	void erase(iterator first, iterator last)
	{
		for (iterator tmp = first; tmp != last; tmp = first)
		{
			++first;
			_erase(tmp.base());
		}
	}

	void swap(rb_tree &t)
	{
		if (this == &t)
			return;

		ft::swap(_comp, t._comp);
		ft::swap(_value_alloc, t._value_alloc);
		ft::swap(_node_alloc, t._node_alloc);
		ft::swap(_size, t._size);
		ft::swap(_nil, t._nil);
		ft::swap(_begin_node, t._begin_node);
	}

	void clear()
	{
		_destroy(_root());
		_root() = _nil;
		_begin_node = _end_node();
	}

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
			if (_comp(val, tmp->value))
				tmp = tmp->left;
			else if (_comp(tmp->value, val))
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
			if (_comp(val, tmp->value))
				tmp = tmp->left;
			else if (_comp(tmp->value, val))
				tmp = tmp->right;
			else
				return const_iterator(tmp);
		}

		return end();
	}

	size_type count(value_type const &val) const
	{
		if (find(val) == end())
			return 0;
		else
			return 1;
	}

	iterator lower_bound(value_type const &val)
	{
		node_pointer result = _end_node();

		node_pointer node = _root();
		while (node != _nil)
		{
			if (!_comp(node->value, val))
			{
				result = node;
				node = node->left;
			}
			else
				node = node->right;
		}

		return iterator(result);
	}

	const_iterator lower_bound(value_type const &val) const
	{
		const_node_pointer result = _end_node();

		const_node_pointer node = _root();
		while (node != _nil)
		{
			if (!_comp(node->value, val))
			{
				result = node;
				node = node->left;
			}
			else
				node = node->right;
		}

		return const_iterator(result);
	}

	iterator upper_bound(value_type const &val)
	{
		node_pointer result = _end_node();

		node_pointer node = _root();
		while (node != _nil)
		{
			if (_comp(val, node->value))
			{
				result = node;
				node = node->left;
			}
			else
				node = node->right;
		}

		return iterator(result);
	}

	const_iterator upper_bound(value_type const &val) const
	{
		const_node_pointer result = _end_node();

		const_node_pointer node = _root();
		while (node != _nil)
		{
			if (_comp(val, node->value))
			{
				result = node;
				node = node->left;
			}
			else
				node = node->right;
		}

		return const_iterator(result);
	}

	pair<iterator, iterator> equal_range(value_type const &val)
	{
		return ft::make_pair(lower_bound(val), upper_bound(val));
	}

	pair<const_iterator, const_iterator> equal_range(value_type const &val) const
	{
		return ft::make_pair(lower_bound(val), upper_bound(val));
	}

/* *** Allocator ************************************************************ */

	allocator_type get_allocator() const
	{
		return _value_alloc;
	}

/* *** Print **************************************************************** */

	void print()
	{
		_print(_root(), "", false, true);
	}


  private:

/* *** Root / End Node ****************************************************** */

	node_pointer &_root()
	{
		return _nil->left;
	}

	node_pointer _root() const
	{
		return _nil->left;
	}

	node_pointer &_end_node()
	{
		return _nil;
	}

	node_pointer _end_node() const
	{
		return _nil;
	}

/* *** Construction / Destruction ******************************************* */

	void _create_nil()
	{
		_nil = _node_alloc.allocate(1);
		_value_alloc.construct(&(_nil->value), value_type());
		_nil->color = BLACK;
		_nil->parent = _nil;
		_nil->left = _nil;
		_nil->right = NULL;
	}

	node_pointer _construct_node(value_type const &val, NODE_COLOR color = RED)
	{
		node_pointer new_node = _node_alloc.allocate(1);
		_value_alloc.construct(&(new_node->value), val);
		new_node->color = color;
		new_node->parent = _nil;
		new_node->left = _nil;
		new_node->right = _nil;

		++_size;

		return new_node;
	}

	node_pointer _construct_node(node_pointer const &src)
	{
		return _construct_node(src->value, src->color);
	}

	void _destroy_node(node_pointer node)
	{
		_value_alloc.destroy(&(node->value));
		_node_alloc.deallocate(node, 1);

		--_size;
	}

	void _destroy(node_pointer node)
	{
		if (node != _nil)
		{
			_destroy(node->left);
			_destroy(node->right);
			_destroy_node(node);
		}
	}

/* *** Copy ***************************************************************** */

	node_pointer _copy(rb_tree const &src_tree, node_pointer const &src_node)
	{
		if (src_node == src_tree._nil)
			return _nil;

		node_pointer new_node = _construct_node(src_node);

		new_node->left = _copy(src_tree, src_node->left);
		if (new_node->left != _nil)
			new_node->left->parent = new_node;

		new_node->right = _copy(src_tree, src_node->right);
		if (new_node->right != _nil)
			new_node->right->parent = new_node;

		return new_node;
	}

/* *** Rotate *************************************************************** */

/* ************************************************************************** **
** ROTATE LEFT                                                                **
**                                                                            **
**     |                 |                                                    **
**     x                 y                                                    **
**    / \               / \                                                   **
**   a   y     -->     x   c                                                  **
**      / \           / \                                                     **
**     b   c         a   b                                                    **
**                                                                            **
** a, b, c: arbitrary subtrees                                                **
** ************************************************************************** */

	void _rotate_left(node_pointer x)
	{
		node_pointer y = x->right;

		// turn left subtree of y into right subtree of x
		x->right = y->left;
		if (y->left != _nil)
			y->left->parent = x;

		// link y and parent of x
		y->parent = x->parent;
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		// put x as left child of y
		y->left = x;
		x->parent = y;
	}

/* ************************************************************************** **
** ROTATE RIGHT                                                               **
**                                                                            **
**       |             |                                                      **
**       x             y                                                      **
**      / \           / \                                                     **
**     y   c   -->   a   x                                                    **
**    / \               / \                                                   **
**   a   b             b   c                                                  **
**                                                                            **
** a, b, c: arbitrary subtrees                                                **
** ************************************************************************** */

	void _rotate_right(node_pointer x)
	{
		node_pointer y = x->left;

		// turn right subtree of y into left subtree of x
		x->left = y->right;
		if (y->right != _nil)
			y->right->parent = x;

		// link y and parent of x
		y->parent = x->parent;
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		// put x as right child of y
		y->right = x;
		x->parent = y;
	}

/* *** Insert *************************************************************** */

	ft::pair<iterator, bool> _insert(value_type const &val)
	{
		node_pointer x = _root();
		node_pointer y = _nil;
		node_pointer z = _construct_node(val);

		// search for nil node to replace with new node z with value val
		while (x != _nil)
		{
			y = x;
			if (_comp(z->value, x->value))
				x = x->left;
			else if (_comp(x->value, z->value))
				x = x->right;
			else
			{
				// tree already contains a node with value val
				_destroy_node(z);
				return ft::make_pair<iterator, bool>(iterator(x), false);
			}
		}

		// link new node z to tree
		z->parent = y;
		if (y == _nil)
			_root() = z;
		else if (_comp(z->value, y->value))
			y->left = z;
		else
			y->right = z;

		// restore red black tree properties if necessary
		_insert_fixup(z);

		// update pointer to leftmost node
		if (_begin_node->left == z)
			_begin_node = z;

		return ft::make_pair<iterator, bool>(iterator(z), true);
	}

/* ************************************************************************** **
** INSERT FIXUP                                                               **
**                                                                            **
** There are 3 cases in the main loop (plus mirrored versions):               **
**                                                                            **
** - Case 1: y, uncle of z, is red                                            **
**                                                                            **
**             |                                 |                            **
**             Cb                                Cr <- new z                  **
**           /   \                             /   \                          **
**         /       \                         /       \                        **
**       Ar          Dr <- y     -->       Ab          Db                     **
**      / \         / \                   / \         / \                     **
**     a   Br <- z d   e                 a   Br      d   e                    **
**        / \                               / \                               **
**       b   c                             b   c                              **
**                                                                            **
** - Case 2: y, uncle of z, is black                                          **
**           z is right child                                                 **
**                                                                            **
**                     |                                   |                  **
**                     Cb                                  Cb                 **
**                   /   \                               /   \                **
**                 /       \                           /       \              **
**     ROTATE -> Ar          Db <- y     -->         Br          Db <- y      **
**     LEFT     / \         / \                     / \         / \           **
**             a   Br <- z d   e          new z -> Ar  c       d   e          **
**                / \                             / \                         **
**               b   c                           a   b                        **
**                                                                            **
**   --> continue with Case 3                                                 **
**                                                                            **
** - Case 3: y, uncle of z, is black                                          **
**           z is left child                                                  **
**                                                                            **
**                  |                                 |                       **
**        ROTATE -> Cb                                Bb                      **
**        RIGHT   /   \                             /   \                     **
**              /       \                         /       \                   **
**            Br          Db <- y     -->       Ar <- z     Cr                **
**           / \         / \                   / \         / \                **
**     z -> Ar  c       d   e                 a   b       c   Db <- y         **
**         / \                                               / \              **
**        a   b                                             d   e             **
**                                                                            **
**   A, B, C, D: nodes                                                        **
**   r, b: color (red / black)                                                **
**   a, b, c, d, e: arbitrary subtrees                                        **
** ************************************************************************** */

	void _insert_fixup(node_pointer z)
	{
		node_pointer y;

		// node z is always red, so rule 4 is violated if its parent is red
		while (z->parent->color == RED)
		{
			// parent of z is left child of its parent
			if (z->parent == z->parent->parent->left)
			{
				y = z->parent->parent->right;
				// case 1
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					// case 2
					if (z == z->parent->right)
					{
						z = z->parent;
						_rotate_left(z);
					}

					// case 3
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					_rotate_right(z->parent->parent);
				}
			}
			// parent of z is right child of its parent (mirrored)
			else
			{
				y = z->parent->parent->left;
				// case 1 (mirrored)
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					// case 2 (mirrored)
					if (z == z->parent->left)
					{
						z = z->parent;
						_rotate_right(z);
					}

					// case 3 (mirrored)
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					_rotate_left(z->parent->parent);
				}
			}
		}

		// ensure that rule 2 is fulfilled by coloring the root node black
		_root()->color = BLACK;
	}

/* *** Delete *************************************************************** */

	void _transplant(node_pointer u, node_pointer v)
	{
		// replace subtree as child of its parent by another subtree
		if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void _erase(node_pointer z)
	{
		// nil node cannot be deleted
		if (z == _nil)
			return;

		node_pointer x;
		node_pointer y = z;
		NODE_COLOR y_color_original = y->color;

		// node z has only a right child or no children
		if (z->left == _nil)
		{
			// replace z by its right child
			x = z->right;
			_transplant(z, z->right);
		}
		// node z has only a left child
		else if (z->right == _nil)
		{
			// replace z by its left child
			x = z->left;
			_transplant(z, z->left);
		}
		// node z has two children
		else
		{
			// find y, successor of z, to replace z in the tree
			y = rbt_min_node(z->right);
			y_color_original = y->color;
			x = y->right;

			// replace y by the right child of y
			if (y->parent == z)
				x->parent = y;
			else
			{
				_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			// replace z by y
			_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		// restore red black tree properties if necessary
		if (y_color_original == BLACK)
			_erase_fixup(x);

		// update pointer to leftmost node
		if (z == _begin_node)
		{
			if (z->right == _nil)
				_begin_node = z->parent;
			else
				_begin_node = rbt_min_node(z->right);
		}

		_destroy_node(z);
	}

/* ************************************************************************** **
** ERASE FIXUP                                                                **
**                                                                            **
** There are 4 cases in the main loop (plus mirrored versions):               **
**                                                                            **
** - Case 1: w, sibling of x, is red                                          **
**                                                                            **
**                  |                                         |               **
**        ROTATE -> Bb                                        Db              **
**        LEFT    /   \                                     /   \             **
**              /       \                                 /       Eb          **
**            /           \                             /        / \          **
**     x -> Ab              Dr <- w     -->           Br        e   f         **
**         / \            /   \                     /   \                     **
**        a   b         Cb      Eb           x -> Ab      Cb <- new w         **
**                     / \     / \               / \     / \                  **
**                    c   d   e   f             a   b   c   d                 **
**                                                                            **
**   --> continue with Case 2, 3, or 4                                        **
**                                                                            **
** - Case 2: w, sibling of x, is black                                        **
**           both children of w are black                                     **
**                                                                            **
**                |                                 |                         **
**                Bc                       new x -> Bc                        **
**              /   \                             /   \                       **
**            /       \                         /       \                     **
**     x -> Ab          Db <- w     -->       Ab          Dr <- w             **
**         / \        /   \                  / \        /   \                 **
**        a   b     Cb      Eb              a   b     Cb      Eb              **
**                 / \     / \                       / \     / \              **
**                c   d   e   f                     c   d   e   f             **
**                                                                            **
** - Case 3: w, sibling of x, is black                                        **
**           left child of w is red                                           **
**           right child of w is black                                        **
**                                                                            **
**                |                              |                            **
**                Bc                             Bc                           **
**              /   \                          /   \                          **
**            /       \       ROTATE    x -> Ab      Cb <- new w              **
**     x -> Ab     w -> Db <- RIGHT         / \     / \                       **
**         / \        /   \         -->    a   b   c   Dr                     **
**        a   b     Cr      Eb                        / \                     **
**                 / \     / \                       d   Eb                   **
**                c   d   e   f                         / \                   **
**                                                     e   f                  **
**                                                                            **
**   --> continue with Case 4                                                 **
**                                                                            **
** - Case 4: w, sibling of x, is black                                        **
**           right child of w is red                                          **
**                                                                            **
**                  |                                         |               **
**        ROTATE -> Bc                                        Dc <- w         **
**        LEFT    /   \                                     /   \             **
**              /       \                                 /       Eb          **
**            /           \                             /        / \          **
**     x -> Ab              Db <- w     -->           Bb        e   f         **
**         / \            /   \                     /   \                     **
**        a   b         Cc'     Er                Ab      Cc'     new x       **
**                     / \     / \               / \     / \        =         **
**                    c   d   e   f             a   b   c   d   root node     **
**                                                                            **
**   A, B, C, D: nodes                                                        **
**   r, b, c, c': color (red / black / any / any)                             **
**   a, b, c, d, e: arbitrary subtrees                                        **
** ************************************************************************** */

	void _erase_fixup(node_pointer x)
	{
		node_pointer w;

		// while x is black and not root node, rule 5 is violated
		while (x != _root() && x->color == BLACK)
		{
			// node x is left child of its parent
			if (x == x->parent->left)
			{
				w = x->parent->right;

				// case 1
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					_rotate_left(x->parent);
					w = x->parent->right;
				}

				// case 2
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					// case 3
					if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						_rotate_right(w);
						w = x->parent->right;
					}

					// case 4
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					_rotate_left(x->parent);
					x = _root();
				}
			}
			// node x is right child of its parent
			else
			{
				w = x->parent->left;

				// case 1 (mirrored)
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					_rotate_right(x->parent);
					w = x->parent->left;
				}

				// case 2 (mirrored)
				if (w->right->color == BLACK && w->left->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					// case 3 (mirrored)
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						_rotate_left(w);
						w = x->parent->left;
					}

					// case 4 (mirrored)
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					_rotate_right(x->parent);
					x = _root();
				}
			}
		}

		// color x black to ensure that rules 2 and 4 are fulfilled
		x->color = BLACK;
	}

/* *** Print **************************************************************** */

	void _print(node_pointer node, std::string const &spaces, bool is_left_child, bool is_root)
	{
		if (node != _nil)
		{
			if (is_root)
				_print(node->right, spaces, false, false);
			else
				_print(node->right, spaces + "     ", false, false);

			std::cout << spaces;

			if (is_root)
				std::cout << "\033[0;34m" << "──" << "\033[0m";
			else
			{
				std::cout << "  ";
				if (is_left_child)
					std::cout << "\033[0;34m" << "└────" << "\033[0m";
				else
					std::cout << "\033[0;34m" << "┌────" << "\033[0m";
			}

			if (node->color == BLACK)
				std::cout << "\033[0;90m" << node->value << "\033[0m" << std::endl;
			else
				std::cout << "\033[0;31m" << node->value << "\033[0m" << std::endl;

			if (is_root)
				_print(node->left, spaces, true, false);
			else
				_print(node->left, spaces + "     ", true, false);
		}
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
