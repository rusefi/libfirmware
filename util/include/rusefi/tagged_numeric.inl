template<typename tag_type>
tagged_numeric_t<tag_type>::tagged_numeric_t()
    : tagged_numeric_t(0) {
}

template<typename tag_type>
tagged_numeric_t<tag_type>::tagged_numeric_t(const value_type& val)
    : value(val) {
    static_assert(std::is_arithmetic_v<value_type>);
    static_assert(sizeof(tagged_numeric_t) == sizeof(value_type));
}

template<typename tag_type>
tagged_numeric_t<tag_type>::operator value_type() const {
    return value;
}

template<typename tag_type>
tagged_numeric_t<tag_type>::operator int() const {
    return static_cast<int>(value);
}

template<typename tag_type>
tagged_numeric_t<tag_type>::operator float() const {
    return static_cast<float>(value);
}

template<typename tag_type>
bool tagged_numeric_t<tag_type>::operator ==(const tagged_numeric_t& val) const {
    return value == val;
}

template<typename tag_type>
bool tagged_numeric_t<tag_type>::operator ==(const value_type& val) const {
    return value == val;
}

template<typename tag_type>
bool tagged_numeric_t<tag_type>::operator !=(const value_type& val) const {
    return value != val;
}

template<typename tag_type>
bool tagged_numeric_t<tag_type>::operator >(const tagged_numeric_t& val) const {
    return value > val.value;
}

template<typename tag_type>
tagged_numeric_t<tag_type> tagged_numeric_t<tag_type>::operator -(
    const tagged_numeric_t& val
) const {
    return tagged_numeric_t(value - val.value);
}

template<typename tag_type>
tagged_numeric_t<tag_type> tagged_numeric_t<tag_type>::operator +(const tagged_numeric_t& val) const {
    return tagged_numeric_t(value + val.value);
}

template<typename tag_type>
tagged_numeric_t<tag_type> tagged_numeric_t<tag_type>::operator +(const int& val) const {
    return tagged_numeric_t(value + val);
}
