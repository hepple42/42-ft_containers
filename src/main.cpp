/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:44 by hepple            #+#    #+#             */
/*   Updated: 2023/02/15 11:26:14 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "../include/map.hpp"
#include "../include/set.hpp"
#include "../include/stack.hpp"
#include "../include/vector.hpp"

#include "../include/red_black_tree.hpp"

int main(void)
{
	// {
	// std::vector<int> vector;
	// std::vector<int> v;
    // std::vector<int> tmp0(vector);
    // std::vector<int> tmp(1000 * 1, 4), tmp2(1000 * 1, 5);
    // tmp = tmp2;
    // std::vector<int> tmp3(tmp);
    // std::vector<int> tmp4(tmp.begin(), tmp.end());
    // v.push_back(tmp4.size());
    // v.push_back(tmp4.capacity());
    // v.push_back(tmp[2]);
    // v.push_back(tmp3[2]);
    // v.push_back(tmp4[2]);
    // try { std::vector<int> tmp5(-1, -1); }
    // catch (std::exception &e) { v.push_back(1); }
	// for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	// }
	// {
	// ft::vector<int> vector;
	// std::vector<int> v;
	// ft::vector<int> tmp0(vector);
    // ft::vector<int> tmp(1000 * 1, 4), tmp2(1000 * 1, 5);
	// std::cout << "tmp capacity(): " << tmp.capacity() << std::endl;
    // tmp = tmp2;
	// std::cout << "tmp capacity(): " << tmp.capacity() << std::endl;
    // ft::vector<int> tmp3(tmp);
    // ft::vector<int> tmp4(tmp.begin(), tmp.end());
	// std::cout << "tmp4 capacity(): " << tmp4.capacity() << std::endl;
    // v.push_back(tmp4.size());
    // v.push_back(tmp4.capacity());
    // v.push_back(tmp[2]);
    // v.push_back(tmp3[2]);
    // v.push_back(tmp4[2]);
    // try { ft::vector<int> tmp5(-1, -1); }
    // catch (std::exception &e) { v.push_back(1); }
	// for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	// }

	// ft::map<int, int> map;
	// ft::set<int> set;

	{
		std::less<int> comp;
		std::allocator<int> alloc;
		ft::rb_tree<int, std::less<int>, std::allocator<int> > tree(comp, alloc);

		// std::cout << tree.size() << std::endl;
		// tree.insert(42);
		// std::cout << tree.size() << std::endl;
		// tree.insert(42);
		// std::cout << tree.size() << std::endl;
		// tree.insert(7);
		// std::cout << tree.size() << std::endl;


		tree.insert(10);
		tree.print();

		tree.insert(18);
		tree.print();

		tree.insert(7);
		tree.print();

		tree.insert(15);
		tree.print();

		tree.insert(16);
		tree.print();

		tree.insert(30);
		tree.print();

		tree.insert(25);
		tree.print();

		tree.insert(40);
		tree.print();

		tree.insert(60);
		tree.print();

		tree.insert(2);
		tree.print();

		tree.insert(1);
		tree.print();

		tree.insert(70);
		tree.print();
	}
	
	std::cout << "Blub." << std::endl;
	return 0;

}
