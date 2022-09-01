/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 03:30:15 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 05:37:05 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
    /**
     * @brief Random-access iterators are iterators that can be used to access elements at an arbitrary offset position relative to the element they point to, offering the same functionality as pointers. Random-access iterators are the most complete iterators in terms of functionality. All pointer types are also valid random-access iterators.
     * 
     * Random-access iterators are one of the five main types of iterators present in C++ Standard Library others being:
     * 1) Input iterator
     * 2) Output iterator
     * 3) Forward iterator 
     * 4) Bidirectional iterator
     * 
     * For detailed information:
     * @link https://www.geeksforgeeks.org/random-access-iterators-in-cpp/ @endlink
     * @link https://en.cppreference.com/w/cpp/iterator/random_access_iterator @endlink
     */

    // Class Declaretion
    template <typename It, typename Container>
	class random_access_iterator
    {
        // Public Member Types (same as pointers)
        public:
            typedef It iterator_type;
		    typedef typename iterator_traits<It>::iterator_category iterator_category;
		    typedef typename iterator_traits<It>::value_type value_type;
		    typedef typename iterator_traits<It>::pointer pointer;
		    typedef typename iterator_traits<It>::reference reference;
		    typedef typename iterator_traits<It>::difference_type difference_type;
        
        protected:
		    It _ptr;
		
        // Constructors
        public:
            random_access_iterator() : _ptr(iterator_type()) {}

            explicit random_access_iterator(iterator_type const &it) : _ptr(it)
            {
            }
		
            template <typename Iter>
            random_access_iterator(
                const random_access_iterator<
                Iter, typename enable_if<is_same<Iter,
                typename Container::pointer>::value,
                Container>::type> &it)
                : _ptr(it.base())
            {
            }

            ~random_access_iterator() {}

            random_access_iterator &operator=(random_access_iterator const &rhs)
            {
                if (this != &rhs)
                    _ptr = rhs._ptr;
                return *this;
            }
        
        // Public Member Functions
        public:
            const iterator_type &base() const
            {
                return _ptr;
            }
            
            reference operator*()
            {
                return *_ptr;
            }
            
            /**
             * @brief An Arrow operator in C/C++ allows to access elements in Structures and Unions. It is used with a pointer variable pointing to a structure or union.
             * Operation: The -> operator in C or C++ gives the value held by variable to structure or union variable pointer.
             * 
             * Difference between Dot(.) and Arrow(->) operator:
             * - The Dot(.) operator is used to normally access members of a structure or union.
             * - The Arrow(->) operator exists to access the members of the structure or the unions using pointers.
             * 
             * Related article:
             * @link https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/ @endlink
             * 
             */
            pointer operator->()
            {
                return _ptr;
            }
            
            random_access_iterator &operator++()
            {
                ++_ptr;
                return *this;
            }
            
            random_access_iterator operator++(int)
            {

                return random_access_iterator(_ptr++);
            }
            
            random_access_iterator &operator--()
            {
                --_ptr;
                return *this;
            }
            
            random_access_iterator operator--(int)
            {
                return random_access_iterator(_ptr--);
            }
            
            random_access_iterator operator+(difference_type n)
            {
                return random_access_iterator(_ptr + n);
            }
            
            random_access_iterator operator-(difference_type n)
            {
                return random_access_iterator(_ptr - n);
            }
            
            random_access_iterator &operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }
            
            random_access_iterator &operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }
            
            reference operator[](difference_type n)
            {
                return *(_ptr + n);
            }
    };

    // Comparing operators
    template <typename ItL, typename ItR, typename Container>
    inline bool operator==(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator==(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename ItL, typename ItR, typename Container>
    inline bool operator!=(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator!=(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename ItL, typename ItR, typename Container>
    inline bool operator<(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator<(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename ItL, typename ItR, typename Container>
    inline bool operator<=(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator<=(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename ItL, typename ItR, typename Container>
    inline bool operator>(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator>(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename ItL, typename ItR, typename Container>
    inline bool operator>=(const random_access_iterator<ItL, Container> &lhs,
                        const random_access_iterator<ItR, Container> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename It, typename Container>
    inline bool operator>=(const random_access_iterator<It, Container> &lhs,
                        const random_access_iterator<It, Container> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    // Adding and Substraction Between Iterators
	template <typename ItL, typename ItR, typename Container>
	inline typename random_access_iterator<ItL, Container>::difference_type
	operator-(const random_access_iterator<ItL, Container> &lhs, const random_access_iterator<ItR, Container> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename Container>
	inline typename random_access_iterator<It, Container>::difference_type
	operator-(const random_access_iterator<It, Container> &lhs, const random_access_iterator<It, Container> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename Container>
	inline random_access_iterator<It, Container>
	operator+(typename random_access_iterator<It, Container>::difference_type n,
			  const random_access_iterator<It, Container> &it)
	{
		return random_access_iterator<It, Container>(it.base() + n);
	}

} // namespace ft

#endif