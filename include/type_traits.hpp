/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:45:41 by hepple            #+#    #+#             */
/*   Updated: 2023/01/26 15:50:03 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP


namespace ft {


/* *** ENABLE_IF ************************************************************ */

template < bool B, typename T = void >
struct enable_if { };

template < typename T>
struct enable_if<true, T>
{
	typedef T	type;
};


/* *** REMOVE CV TYPE QUALIFIERS ******************************************** */

template < typename T >
struct remove_const
{
	typedef T	type;
};

template < typename T >
struct remove_const<T const>
{
	typedef T	type;
};

template < typename T >
struct remove_volatile
{
	typedef T	type;
};

template < typename T >
struct remove_volatile<T volatile>
{
	typedef T	type;
};

template < typename T >
struct remove_cv
{
	typedef typename remove_volatile<typename remove_const<T>::type>::type	type;
};


/* *** TRUE_TYPE / FALSE_TYPE *********************************************** */

/* *** Integral Constant **************************************************** */

template < typename T, T v >
struct integral_constant
{
	static T const	value = v;

	typedef T						value_type;
	typedef integral_constant<T, v>	type;

	operator const value_type() const
	{
		return value;
	}
};

/* *** True / False Type **************************************************** */

typedef ft::integral_constant<bool, true>	true_type;
typedef ft::integral_constant<bool, false>	false_type;


// struct true_type
// {
// 	typedef true_type	type;
// 	static bool const	value = true;
// };

// struct false_type
// {
// 	typedef false_type	type;
// 	static bool const	value = false;
// };


/* *** IS_INTEGRAL ********************************************************** */

/* *** Base Case Without CV Type Qualifiers ********************************* */

template < typename T >
struct is_integral_no_cv : public false_type { };

template < >
struct is_integral_no_cv<bool> : public true_type { };

template < >
struct is_integral_no_cv<char> : public true_type { };

template < >
struct is_integral_no_cv<char16_t> : public true_type { };

template < >
struct is_integral_no_cv<char32_t> : public true_type { };

template < >
struct is_integral_no_cv<wchar_t> : public true_type { };

template < >
struct is_integral_no_cv<signed char> : public true_type { };

template < >
struct is_integral_no_cv<short int> : public true_type { };

template < >
struct is_integral_no_cv<int> : public true_type { };

template < >
struct is_integral_no_cv<long int> : public true_type { };

template < >
struct is_integral_no_cv<long long int> : public true_type { };

template < >
struct is_integral_no_cv<unsigned char> : public true_type { };

template < >
struct is_integral_no_cv<unsigned short int> : public true_type { };

template < >
struct is_integral_no_cv<unsigned int> : public true_type { };

template < >
struct is_integral_no_cv<unsigned long int> : public true_type { };

template < >
struct is_integral_no_cv<unsigned long long int> : public true_type { };

/* *** Wrapper for CV Type Qualifiers *************************************** */

template < typename T >
struct is_integral : public is_integral_no_cv<typename remove_cv<T>::type> { };


} // namespace ft


#endif // FT_TYPE_TRAITS_HPP
