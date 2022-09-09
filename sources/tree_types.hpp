/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 03:59:31 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/08 04:25:57 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_TYPES_HPP
# define TREE_TYPES_HPP

# include <cstddef>

namespace ft
{
    template <typename T>
    class tree_end_node;

    template <typename T>
    class tree_node;

    template <typename T>
    struct tree_node_types
    {
        typedef tree_end_node<T> end_node_type;
        typedef end_node_type *end_node_pointer;
        typedef tree_node<T> node_type;  // normal node_tpye
        typedef node_type *node_pointer; // normal node pointer
    };

    template <typename T>
    class tree_end_node
    {
    public:
        typedef typename tree_node_types<T>::node_pointer node_pointer;

    public:
        node_pointer left;

    public:
        tree_end_node() : left(NULL)
        {
        }
    };

    template <typename T>
    class tree_node : public tree_node_types<T>::end_node_type
    {
    public:
        typedef typename tree_node_types<T>::end_node_pointer end_node_pointer;
        typedef typename tree_node_types<T>::node_pointer node_pointer;

    public:
        node_pointer right;      // Right leaf
        end_node_pointer parent; // Parent node
        bool is_black;           // Not used (bonus)
        T value;                 // Value of node

    public:
        tree_node()
            : right(NULL),
              parent(NULL),
              is_black(false)
        {
        }

        node_pointer get_parent() const
        {
            return static_cast<node_pointer>(parent);
        }

        void set_parent(node_pointer ptr)
        {
            parent = static_cast<end_node_pointer>(ptr);
        }
    };
} // namespace ft


#endif