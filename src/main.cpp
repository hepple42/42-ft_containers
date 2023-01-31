/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:44 by hepple            #+#    #+#             */
/*   Updated: 2023/01/31 13:59:50 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>

#include "../include/stack.hpp"
#include "../include/vector.hpp"

int main(void)
{
	{
	std::vector<int> vector;
	std::vector<int> v;
    std::vector<int> tmp0(vector);
    std::vector<int> tmp(1000 * 1, 4), tmp2(1000 * 1, 5);
    tmp = tmp2;
    std::vector<int> tmp3(tmp);
    std::vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { std::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	}
	{
	ft::vector<int> vector;
	std::vector<int> v;
	ft::vector<int> tmp0(vector);
    ft::vector<int> tmp(1000 * 1, 4), tmp2(1000 * 1, 5);
	std::cout << "tmp capacity(): " << tmp.capacity() << std::endl;
    tmp = tmp2;
	std::cout << "tmp capacity(): " << tmp.capacity() << std::endl;
    ft::vector<int> tmp3(tmp);
    ft::vector<int> tmp4(tmp.begin(), tmp.end());
	std::cout << "tmp4 capacity(): " << tmp4.capacity() << std::endl;
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { ft::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	}
	std::cout << "Blub." << std::endl;
	return 0;
}
