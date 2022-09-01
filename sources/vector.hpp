/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:41:21 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 17:20:17 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "type_trait.hpp"
# include "iterator.hpp"
# include "random_access_iterator.hpp"
# include "utility.hpp"
# include <iostream>
# include <stdexcept>
# include <algorithm>
# include <limits>
# include <iterator>

namespace ft
{
    /**
     * @brief Allocators are objects responsible for encapsulating memory management. std::allocator is used when you want to separate allocation and do construction in two steps. It is also used when separate destruction and deallocation is done in two steps. All the STL containers in C++ have a type parameter Allocator that is by default std::allocator. The default allocator simply uses the operators new and delete to obtain and release memory.
     * 
     * Member Types of std::allocator:                                               |  Definition:
     * - value_type	                                                                 |  T
     * - pointer (deprecated in C++17)(removed in C++20)	                         |  T*
     * - const_pointer (deprecated in C++17)(removed in C++20)	                     |  const T*
     * - reference (deprecated in C++17)(removed in C++20)	                         |  T&
     * - const_reference (deprecated in C++17)(removed in C++20)	                 |  const T&
     * - size_type	                                                                 |  std::size_t
     * - difference_type std::ptrdiff_tpropagate_on_container_move_assignment(C++11) |  std::true_type
     * 
     * @link https://en.cppreference.com/w/cpp/memory/allocator @endlink
     * @link https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/ @endlink
     * @link https://cplusplus.com/reference/memory/allocator/ @endlink
     * @link https://youtu.be/LIb3L4vKZ7U @endlink
     */
    
    template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
        // Public Member Types
        public:
            typedef T value_type;
            typedef Allocator allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef random_access_iterator<pointer, vector> iterator;
            typedef random_access_iterator<const_pointer, vector> const_iterator;
            typedef typename allocator_type::size_type size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        // Member Objects
        private:
            allocator_type  _alloc;
            pointer         _start;	  // first element (pointer) of vector
            pointer         _end;	  // last element (pointer) of vector
            pointer         _end_cap; // last pointer of capacity of vector

        // Contructors
        public:
            vector()
                : _alloc(allocator_type()), _start(NULL), _end(NULL), _end_cap(NULL)
            {
            }

            vector(const vector &other)
                : _alloc(other._alloc),
                _start(NULL),
                _end(NULL),
                _end_cap(NULL)
            {
                const size_type cap = other.capacity();
                if (cap == 0)
                {
                    return;
                }
                _start = _alloc.allocate(cap);
                _end_cap = _start + cap;
                _end = construct_range(_start, other._start, other._end);
            }

            explicit vector(const Allocator &alloc)
                : _alloc(alloc), _start(NULL), _end(NULL), _end_cap(NULL)
            {
            }

            explicit vector(size_type count,
                            const value_type &value = value_type(),
                            const allocator_type &alloc = allocator_type())
                : _alloc(alloc), _start(NULL), _end(NULL), _end_cap(NULL)
            {
                if (count == 0)
                    return;
                check_size(count);

                _start = _alloc.allocate(count);
                _end = _start + count;
                _end_cap = _end;
                construct_range(_start, _end, value);
            }

            template <class InputIt>
            vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, 
                InputIt>::type last, const Allocator &alloc = Allocator())
                : _alloc(alloc), _start(NULL), _end(NULL), _end_cap(NULL)
            {
                typedef typename iterator_traits<InputIt>::iterator_category category;
                range_init(first, last, category());
            }

            ~vector()
            {
                deallocate_vector();
            }
            vector &operator=(const vector &rhs)
            {
                if (this != &rhs)
                    assign(rhs.begin(), rhs.end());

                return *this;
            }
    };
} // namespace ft

#endif