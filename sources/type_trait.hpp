/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_trait.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabduvak <aabduvak@42ISTANBUL.COM.TR>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 06:02:34 by aabduvak          #+#    #+#             */
/*   Updated: 2022/09/01 07:08:57 by aabduvak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAIT_HPP
# define TYPE_TRAIT_HPP

namespace ft
{
    template <bool B, typename T = void>
    struct enable_if
    {
    };

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    struct true_type
    {
        static const bool value = true;
        typedef true_type type;
    };

    struct false_type
    {
        static const bool value = false;
        typedef false_type type;
    };

    template <typename>
    struct is_integral : public false_type
    {
    };

    template <>
    struct is_integral<bool> : public true_type
    {
    };

    template <>
    struct is_integral<char> : public true_type
    {
    };

    template <>
    struct is_integral<signed char> : public true_type
    {
    };

    template <>
    struct is_integral<short int> : public true_type
    {
    };

    template <>
    struct is_integral<int> : public true_type
    {
    };

    template <>
    struct is_integral<long int> : public true_type
    {
    };

    template <>
    struct is_integral<unsigned char> : public true_type
    {
    };

    template <>
    struct is_integral<unsigned short int> : public true_type
    {
    };

    template <>
    struct is_integral<unsigned int> : public true_type
    {
    };

    template <>
    struct is_integral<unsigned long int> : public true_type
    {
    };

    template <typename T, typename U>
    struct is_same : public false_type
    {
    };

    template <typename T>
    struct is_same<T, T> : public true_type
    {
    };

} // namespace ft

#endif