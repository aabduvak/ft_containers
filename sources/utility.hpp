/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:54:56 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 15:25:02 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "type_trait.hpp"

namespace ft
{
    template <typename T1, typename T2>
	struct pair
	{
		// Member Types
		typedef T1 first_type;
		typedef T2 second_type;

		// Member Objects
		first_type first;
		second_type second;

        // Constructors
		pair() : first(first_type()), second(second_type())
		{
		}

		pair(const first_type &f, const second_type &s) : first(f), second(s)
		{
		}

		template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second)
		{
		}

		pair(const pair &other) : first(other.first), second(other.second)
		{
		}

		pair &operator=(const pair &other)
		{
			if (this != &other)
			{
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};

    // Operators
    template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <typename T1, typename T2>
	inline bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	// Reverse logic with (==) operator
	template <typename T1, typename T2>
	inline bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

    template <typename T1, typename T2>
	inline bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <typename T1, typename T2>
	inline bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T1, typename T2>
	inline bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	inline bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

    // Compare functions
    // Checking all iterator's data if they are not the same returns false, otherwise true
	template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1,
	           InputIt2 first2)
	{
		for (; first1 != last1; ++first1, (void)++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}

    // Checking all iterator's data by "p" function if they are not the same returns false, otherwise true
	template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1,
	           InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, (void)++first2)
			if (!p(*first1, *first2))
				return false;
		return true;
	}

    /**
     * @brief Almost same as strcmp function in C
     * 
     * More detailed info below:
     * @link https://www.geeksforgeeks.org/lexicographical_compare-in-cpp/ @endlink
     */
    template <typename InputIt1, typename InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2,
								 Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
} // namespace ft

#endif