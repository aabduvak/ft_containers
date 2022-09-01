/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:41:21 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 17:32:56 by aabduvak         ###   ########.fr       */
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

        // Private Member Functions
        private:

            // Constructing values between start and end iterators
            template <typename It>
            pointer construct_range(pointer dst, It start, It end)
            {
                for (; start != end; ++dst, (void)++start)
                    _alloc.construct(dst, *start);
                return dst;
            }

            // Construct iterators between dst and end with given value 
            pointer construct_range(pointer dst, const_pointer end, const_reference value)
            {
                for (; dst != end; ++dst)
                    _alloc.construct(dst, value);
                return dst;
            }

            template <typename InputIt>
            void range_init(InputIt first, InputIt last, std::input_iterator_tag)
            {
                for (; first != last; ++first)
                    push_back(*first);
            }

            template <typename ForwardIt>
            void range_init(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
            {
                const size_type count = std::distance(first, last);
                if (count == 0)
                    return;
                check_size(count);

                _start = _alloc.allocate(count);
                _end_cap = _start + count;
                _end = construct_range(_start, first, last);
            }

            template <typename InputIt>
            void range_insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
            {
                if (pos == end())
                    for (; first != last; ++first)
                        push_back(*first);
                else if (first != last)
                {
                    vector tmp(first, last);
                    insert(pos, tmp.begin(), tmp.end());
                }
            }

            template <typename ForwardIt>
            void range_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
            {
                if (first != last)
                {
                    const size_type count = std::distance(first, last);
                    check_size(count);
                    const size_type extra_space = _end_cap - _end;

                    if (extra_space >= count)
                    {
                        const size_type elems_after = end() - pos;
                        pointer old_end = _end;

                        if (elems_after > count)
                        {
                            _end = construct_range(_end, _end - count, _end);
                            std::copy_backward(pos.base(), old_end - count, old_end);
                            std::copy(first, last, pos);
                        }
                        else
                        {
                            ForwardIt mid = first;
                            std::advance(mid, elems_after);
                            _end = construct_range(_end, mid, last);
                            _end = construct_range(_end, pos.base(), old_end);
                            std::copy(first, mid, pos);
                        }
                    }
                    else
                    {
                        const size_type new_size = calculate_growth(count);
                        pointer new_start = _alloc.allocate(new_size);
                        pointer new_end = new_start;

                        new_end = construct_range(new_start, _start, pos.base());
                        new_end = construct_range(new_end, first, last);
                        new_end = construct_range(new_end, pos.base(), _end);

                        deallocate_vector();
                        _start = new_start;
                        _end = new_end;
                        _end_cap = new_start + new_size;
                    }
                }
            }

            template <typename InputIt>
            void range_assign(InputIt first, InputIt last, std::input_iterator_tag)
            {
                clear();
                for (; first != last; ++first)
                    push_back(*first);
            }

            template <typename ForwardIt>
            void range_assign(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
            {
                const size_type count = std::distance(first, last);

                if (count < size())
                {
                    iterator it = std::copy(first, last, begin());
                    erase_at_end(it.base());
                }
                else
                {
                    ForwardIt it = first;
                    std::advance(it, size());
                    std::copy(first, it, begin());
                    insert(end(), it, last);
                }
            }

            size_type calculate_growth(size_type extra) const
            {
                const size_type max = max_size();
                const size_type cap = capacity();
                if (max - cap < extra)
                    length_exception();

                if (cap >= max / 2)
                    return max;
                return std::max(size() + extra, cap * 2);
            }

            void destroy_range(pointer pos, pointer end)
            {
                for (; pos != end; ++pos)
                    _alloc.destroy(pos);
            }

            void erase_at_end(pointer pos)
            {
                destroy_range(pos, _end);
                _end = pos;
            }

            void length_exception() const
            {
                throw std::length_error("cannot create ft::vector larger than max_size()");
            }

            void check_size(size_type count) const
            {
                if (count > _alloc.max_size())
                    length_exception();
            }

            void check_range(size_type pos) const
            {
                if (pos >= size())
                    throw std::out_of_range("Index is out of vector range");
            }

            // If _end and _end_cap are equal returns true
            bool should_grow()
            {
                return _end == _end_cap;
            }

            void deallocate_vector()
            {
                if (_start != NULL)
                {
                    pointer tmp = _start;
                    for (; tmp != _end; ++tmp)
                        _alloc.destroy(tmp);
                    _alloc.deallocate(_start, capacity());
                }
            }
    };
} // namespace ft

#endif