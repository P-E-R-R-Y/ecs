/**
 * @file SparseArray.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-01-27
 */

#ifndef SPARSE_ARRAY_HPP
#define SPARSE_ARRAY_HPP

//local

//global
#include <iostream>
#include <vector>
#include <optional>

namespace ecs {

    /**
     * @brief help to print the optional value
     * 
     * @tparam Component 
     * @param os 
     * @param c 
     * @return std::ostream& 
     */
    template <typename Component>
    std::ostream& operator<<(std::ostream& os, std::optional<Component> const &c)
    {
        if (c)
            os << c.value();
        else
            os << "nullopt";
        return os;
    }

    /**
     * @brief SparseArray class

     * @class SparseArray
     * @tparam Component 
     */
    template <typename Component>
    class SparseArray {

        public: 

            using value_type = std::optional<Component>;
            using reference_type = value_type &;
            using const_reference_type = value_type const &;

            using container_t = std::vector<value_type>;

            using size_type = typename container_t::size_type;

            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;
        
        public:

            /**
             * @brief construct a new SparseArray object
             * 
             */
            SparseArray() = default;

            /**
             * @brief copy constructor
             * 
             * @param size 
             */
            SparseArray(SparseArray const &) = default;

            /**
             * @brief move constructor
             * 
             * @param size 
             */
            SparseArray(SparseArray &&) noexcept = default;

            /**
             * @brief Destroy the Sparse Array object
             */
            ~SparseArray() = default;

            /**
             * @brief copy operator=
             * 
             * @param other
             * @return SparseArray& 
             */
            SparseArray &operator=(SparseArray const &) = default;

            /**
             * @brief move operator=
             * 
             * @param other
             * @return SparseArray& 
             */
            SparseArray &operator=(SparseArray &&) noexcept = default;

            /**
             * @brief give the value at the index idx of the SparseArray
             * 
             * @param idx
             * @return reference_type 
             */
            inline reference_type operator[](size_t idx) { return _data[idx]; }
            
            /**
             * @brief give the value at the index idx of the SparseArray (const)
             * 
             * @param idx 
             * @return const_reference_type 
             */
            const_reference_type operator[](size_t idx) const { return _data.at(idx); }

            /**
             * @brief give a iterator at the begining of the SparseArray
             * 
             * @return iterator 
             */
            inline iterator begin() { return _data.begin(); }

            /**
             * @brief give a const_iterator at the begining of the SparseArray
             * 
             * @return const_iterator 
             */
            inline const_iterator begin() const { return _data.begin(); }

            /**
             * @brief give a const_iterator at the begining of the SparseArray
             * 
             * @return const_iterator 
             */
            inline const_iterator cbegin() const { return _data.cbegin(); }

            /**
             * @brief give a iterator at the end of the SparseArray
             * 
             * @return iterator 
             */
            inline iterator end() { return _data.end(); }

            /**
             * @brief give a const_iterator at the end of the SparseArray
             * 
             * @return const_iterator 
             */
            inline const_iterator end() const { return _data.end(); }

            /**
             * @brief give a const_iterator at the end of the SparseArray
             * 
             * @return const_iterator 
             */
            inline const_iterator cend() const { return _data.cend(); }

            /**
             * @brief give the size of the SparseArray
             * 
             * @return size_type
             */
            inline size_type size() const { return _data.size(); }

            /**
             * @brief insert a component at the given position & return a reference to it
             * 
             * @param pos
             * @param c
             * 
             * @return reference_type
             */
            reference_type insertAt(size_type pos, Component const &c) {
                if (_data.size() <= pos)
                    _data.resize(pos + 1);
                _data[pos] = std::make_optional(c);
                return _data[pos];
            };

            /**
             * @brief insert a component at the given position & return a reference to it
             * 
             * @param pos 
             * @param c 
             * @return reference_type 
             */
            reference_type insertAt(size_type pos, Component &&c) {
                if (_data.size() <= pos)
                    _data.resize(pos + 1);
                _data[pos] = std::make_optional(std::move(c));
                return _data[pos];
            };

            /**
             * @brief emplace a component at the given position & return a reference to it
             * 
             * @tparam Params 
             * @param pos 
             * @param args 
             * @return reference_type 
             */
            template <class ... Params>
            reference_type emplaceAt(size_type pos, Params &&...args) {
                container_t vecArgs = {args...};

                size_type i = vecArgs.size();
                if (_data.size() <= pos + i)
                    _data.resize(pos + i);
                i = 0;
                for (value_type v : vecArgs) {
                    _data[pos + i] = v;
                    ++i;
                }
                return _data[pos];
            };

            /**
             * @brief erase the component at the given position
             * 
             * @param pos 
             */
            void erase(size_type pos) {
                if (pos >= 0 && pos < _data.size()) {
                    _data[pos] = std::nullopt;
                }
            };

            /**
             * @brief get the index of the given value
             * 
             * @param v 
             * @return size_type 
             */
            size_type getIndex(const value_type &v) const {
                auto it = std::find(_data.begin(), _data.end(), v);
                if (it != _data.end())
                    return std::distance(_data.begin(), it);
                return -1;  // return 0 if not found
            };

            /**
             * @brief print the SparseArray
             */
            void print() const {
                bool first = true;
                std::cout << "{ ";
                for (auto const &v : _data) {
                    if (!first) {
                        std::cout << ", " << v;
                    } else {
                        std::cout << v;
                        first = false;
                    }
                }
                std::cout << " }" << std::endl;
            };

        private:

            container_t _data;
    };
    
} // namespace name


#endif // SPARSE_ARRAY_HPP