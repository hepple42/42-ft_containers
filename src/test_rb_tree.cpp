/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:44 by hepple            #+#    #+#             */
/*   Updated: 2023/02/22 14:16:26 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <functional>
#include <iostream>
#include <memory>

#include "../include/red_black_tree.hpp"


int main(void)
{
	std::less<int> comp;
	std::allocator<int> alloc;
	ft::rb_tree<int, std::less<int>, std::allocator<int> > tree(comp, alloc);

	int x;

	x = 10;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 18;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 7;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 15;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 16;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 30;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 25;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 40;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 60;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 2;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 1;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 70;
	std::cout << "Inserting " << x << ":" << std::endl;
	tree.insert(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;

	x = 10;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 18;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 7;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 15;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 16;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 30;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 25;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 40;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 60;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 2;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 1;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;
	x = 70;
	std::cout << "Erasing " << x << ":" << std::endl;
	tree.erase(x);
	tree.print();
	std::cout << "- - - - - - - - - - - - - - -" << std::endl;

	return 0;
}
