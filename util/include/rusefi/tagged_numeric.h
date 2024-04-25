//
// Created by kifir on 4/25/24.
//

#pragma once

#include <type_traits>

template<typename tag_type> class tagged_numeric_t {
public:
    using value_type = typename tag_type::value_type;

    tagged_numeric_t();
    tagged_numeric_t(const value_type& val); // implicit to allow init from numeric value (for backward compatibility)

    explicit operator value_type() const;
    explicit operator int() const;
    explicit operator float() const;

    bool operator ==(const tagged_numeric_t& val) const;
    bool operator ==(const value_type& val) const;
    bool operator !=(const value_type& val) const;
    bool operator >(const tagged_numeric_t& val) const;

    tagged_numeric_t operator -(const tagged_numeric_t& val) const;
    tagged_numeric_t operator +(const tagged_numeric_t& val) const;
    tagged_numeric_t operator +(const int& val) const;
private:
    value_type value;
};

#include "tagged_numeric.inl"
