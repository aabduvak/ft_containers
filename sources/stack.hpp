/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:04:11 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/07 15:14:45 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
    // Public Member Objects
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	// Protected Member Object	
	protected:
		container_type c;
    
    // Constructors
    public:
		explicit stack(const container_type &ctnr = container_type())
			: c(ctnr)
		{
		}

		stack(const stack &rhs) : c(rhs.c)
		{
		}

		stack &operator=(const stack &rhs)
		{
			if (this != &rhs)
				c = rhs.c;
			return *this;
		}

		~stack()
		{
		}
	
    // Public Member Functions
    public:
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		value_type &top()
		{
			return c.back();
		}
        
		const value_type &top() const
		{
			return c.back();
		}

		void push(const value_type &val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

        /**
         * @brief Friend Function
         * Friend Function a friend function can be given a special grant to access private and protected members. A friend function can be: 
         * a) A member of another class
         * b) A global function 
         * A friend function is a special function in C++ which in-spite of not being member function of a class has privilege to access private and protected data of a class.
         * A friend function is a non member function or ordinary function of a class, which is declared as a friend using the keyword “friend” inside the class. By declaring a function as a friend, all the access permissions are given to the function.
         * The keyword “friend” is placed only in the function declaration of the friend function and not in the function definition.
         * When friend function is called neither name of object nor dot operator is used. However it may accept the object as argument whose value it want to access.
         * Friend function can be declared in any section of the class i.e. public or private or protected.
         * 
         * @link https://www.geeksforgeeks.org/friend-class-function-cpp/ @endlink
         */
        
		template <typename T1, typename C1>
		friend bool operator==(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);

		template <typename T1, typename C1>
		friend bool operator<(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);

	}; // end of stack

    // Operators    
	template <typename T1, typename C1>
	inline bool operator==(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return lhs.c == rhs.c;
	}

	template <typename T1, typename C1>
	inline bool operator!=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename C1>
	inline bool operator<(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return lhs.c < rhs.c;
	}

	template <typename T1, typename C1>
	inline bool operator<=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T1, typename C1>
	inline bool operator>(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T1, typename C1>
	inline bool operator>=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
	{
		return !(lhs < rhs);
	}
} // end of namesapce

#endif