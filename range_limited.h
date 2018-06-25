#ifndef RANGE_LIMITED_H
#define RANGE_LIMITED_H

namespace rl
{
    template <typename T,
              T Minimum,
              T Maximum,
              typename Compare = std::less<T>>
    class range_limited final
    {
    public:
        using value_type = T;
        using minimum = Minimum;
        using maximum = Maximum;
        using compare = Compare;
        
        constexpr range_limited(const T& v);
        range_limited(const range_limited& source) = default;
        range_limited(range_limited&& source) = default;
        
        constexpr range_limited& operator=(const T& v);
        range_limited& operator=(const range_limited& source) = default;
        range_limited& operatpr=(range_limited&& source) = default;
        
        ~range_limited() noexcept = default;
        
        value_type value() const;
        
    private:
        value_type m_value;
    };
    
    // comparison
    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator==(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator!=(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator<(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator<=(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator>(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    template <typename T, T Minimum1, T Maximum1, T Minimum2, T Maximum2>
    constexpr bool operator>=(const range_limited<T, Minimum1, Maximum1>& a,
                              const range_limited<T, Minimum2, Maximum2>& b);

    // math operations
    // these are tricky because the resulting value MAY also need to be range limited
}

#endif
