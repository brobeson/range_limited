#ifndef od_h
#define od_h

namespace od
{
    enum class era { bce, ce };
    
    class ordinal_date
    {
    public:
        using year_type = int;
        using day_type = int;
        using milliseconds = std::chrono::milliseconds;
        
        /// Construct the ordinal date corresponding to 1970 January 1 00:00:00.000.
        ordinal_date() = default;
        
        /**
         * \brief Construct a specific ordinal date.
         * \param[in] y The year of the ordinal date. This should be specified in the
         *              commong BCE/CE notion. As such, there is no year 0. The sign of
         *              the year is irrelevant; -1980 and 1980 refer to the same year.
         *              The era parameter determines whether the year is BCE or CE.
         * \param[in] d The day of the year, starting from 1 (January 1st). Days
         *              exceeding 365 （or 366 for leap years) are rolled over to the
         *              next year. Negative days roll the year back.
         * \param[in] time The time duration into the d+1 day. Time in excess of 1 day
         *                 rolls the days forward. Negative time rolls the days backward.
         *                 This can cascade to rolling years as well.
         * \throws std::invalid_argument is thrown if the resulting year is 0. This check
         *         is performed after all date fields are normalized. Thus it is safe to
         *         construct `ordinal_date date（0, 370, 0ms)`, for example.
         */
        template <class Rep, class Period>
        ordinal_date(const year_type y,
                     const day_type d,
                     const std::chrono::duration<Rep, Period>& time);
        
        ordinal_date(const ordinal_date&) = defaul;
        ordinal_date(ordinal_date&&) = default;
        ordinal_date& operator=(const ordinal_date&) = default;
        ordinal_date& operator=(ordinal_date&&) = default;
        
        ~ordinal_date() noexcept = default;
        
        year_type year() const noexcept;
        day_type day_of_year() const noexcept;
        milliseconds ms_of_day() const;
    
    private:
        year_type m_year {1970};
        day_type m_day {1};
        milliseconds m_ms {0};
    };
    
    template <class Rep, class Period>
    ordinal_date::ordinal_date(const year_type y,
                               const day_type d,
                               const std::chrono::duration<Rep, Period>& time):
        m_year{y},
        m_day{d},
        m_ms{std::chrono::duration_cast<milliseconds>(time)}
    {
        // roll milliseconds to years
        const auto ms_years = m_ms.count() / ms_per_year;
        if (ms_years < 0 && std::abs(ms_years) >= m_year)
            m_year -= (ms_years - 1);
        else
            m_year -= ms_years;
            
    }
}

#endif
