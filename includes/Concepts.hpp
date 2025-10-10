/**
 * @file Concept.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-10-08
 */

#pragma once

#include <tuple>
#include <concepts>

/**
 * @brief 
 * 
 * @tparam T 
 */
template <typename T>
struct is_tuple : std::false_type {};

template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

template <typename T>
concept IsTuple = is_tuple<T>::value;