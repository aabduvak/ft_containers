/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:20:51 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 03:13:42 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cstddef> // in the C standard library as <stddef.h>. Types: size_t, ptrdiff_t, nullptr_t

namespace ft
{
    /**
     * @brief std::iterator_traits
     * std::iterator_traits is the type trait class that provides uniform interface to the properties of LegacyIterator types. This makes it possible to implement algorithms only in terms of iterators.
     * The template can be specialized for user-defined iterators so that the information about the iterator can be retrieved even if the type does not provide the usual typedefs.
     *
     * @tparam 	Iter - the iterator type to retrieve properties for
     *
     * @link https://en.cppreference.com/w/cpp/iterator/iterator_traits @endlink
     */
    template <typename Iter>
    struct iterator_traits
    {
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::iterator_category iterator_category;
    };

    template <typename T>
    struct iterator_traits<T *>
    {
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T *>
    {
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // Class Decloration
    template <typename It>
    class reverse_iterator
        : public std::iterator< // Inherits from std::iterator
              typename iterator_traits<It>::iterator_category, typename iterator_traits<It>::value_type,
              typename iterator_traits<It>::difference_type, typename iterator_traits<It>::pointer,
              typename iterator_traits<It>::reference>
    {

        // Public Member Types
    public:
        typedef It iterator_type;
        typedef typename iterator_traits<It>::iterator_category iterator_category;
        typedef typename iterator_traits<It>::value_type value_type;
        typedef typename iterator_traits<It>::difference_type difference_type;
        typedef typename iterator_traits<It>::pointer pointer;
        typedef typename iterator_traits<It>::reference reference;

    protected:
        It _current;

        // Constructors
    public:
        reverse_iterator() : _current()
        {
        }

        reverse_iterator(const reverse_iterator &rhs) : _current(rhs._current)
        {
        }

        /**
         * @brief explicit keyword - in C++ is used to mark constructors to not implicitly convert types in C++. It is optional for constructors that take exactly one argument and work on constructors(with a single argument) since those are the only constructors that can be used in typecasting.
         *
         * @example
         * explicit Example::Example(int a, int b) -> decloration of explicit constructor
         *
         * Example test(3, 0); -> Initializing Example class
         *
         * if (test == (Example)3)  -> Usage of constructor like typecaster
         *     ....
         *
         * @link https://www.geeksforgeeks.org/use-of-explicit-keyword-in-cpp/#:~:text=Explicit%20Keyword%20in%20C%2B%2B%20is%20used%20to%20mark%20constructors,can%20be%20used%20in%20typecasting. @endlink
         */
        explicit reverse_iterator(iterator_type it) : _current(it)
        {
        }

        template <typename Iter>
        reverse_iterator(const reverse_iterator<Iter> &rev_it) : _current(rev_it.base())
        {
        }

        ~reverse_iterator()
        {
        }

        reverse_iterator &operator=(reverse_iterator const &rhs)
        {
            if (this != &rhs)
                _current = rhs._current;
            return *this;
        }

        // Public Member Functions
    public:
        iterator_type base() const
        {
            return _current;
        }

        reference operator*() const
        {
            It tmp = _current;
            return *--tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[](difference_type n) const
        {
            return (base()[-n - 1]);
        }

        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(base() - n);
        }

        // Pre increment
        reverse_iterator &operator++()
        {
            --_current;
            return *this;
        }

        // Post increment
        reverse_iterator operator++(int)
        {
            return reverse_iterator(_current--);
        }

        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(base() + n);
        }

        // Pre decrement
        reverse_iterator &operator--()
        {
            ++_current;
            return *this;
        }

        // Post decrement
        reverse_iterator operator--(int)
        {
            return reverse_iterator(_current++);
        }

        reverse_iterator &operator+=(difference_type n)
        {
            _current -= n;
            return *this;
        }

        reverse_iterator &operator-=(difference_type n)
        {
            _current += n;
            return *this;
        }
    }; // End of reverse_iterator class

    /**
     * @brief inline functions - C++ provides an inline functions to reduce the function call overhead. Inline function is a function that is expanded in line when it is called. When the inline function is called whole code of the inline function gets inserted or substituted at the point of inline function call. This substitution is performed by the C++ compiler at compile time. Inline function may increase efficiency if it is small.
     *
     * @code {C}
     * inline return-type function-name(parameters)
        {
            // function code
        } 
     * @endcode
     * 
     * @attention Compiler can ignore the request for inlining.
     * 
     *
     * @link https://www.geeksforgeeks.org/inline-functions-cpp/ @endlink
     */

    // Operator overriding with two arguments
    // Example -> Class A == Class B
    template <typename Iterator>
    inline bool operator==(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator==(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator>
    inline bool operator!=(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator!=(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator>
    inline bool operator<(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator<(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator>
    inline bool operator<=(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator<=(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator>
    inline bool operator>(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator>(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator>
    inline bool operator>=(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename ItL, typename ItR>
    inline bool operator>=(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }

    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename ItL, typename ItR>
    typename reverse_iterator<ItL>::difference_type operator-(
        const reverse_iterator<ItL> &lhs,
        const reverse_iterator<ItR> &rhs)
    {
        return rhs.base() - lhs.base();
    }

} // namespace ft

#endif