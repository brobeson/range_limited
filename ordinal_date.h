#ifndef od_h
#define od_h

namespace od
{
    enum class era_t { bce, ce };
    
    class year_t
    {
    public:
        year_t() = default;
        year_t(const int y, const era_t e): year(std::abs(y)), era(e) {}
        year_t(const year_t&) = default;
        year_t(year_t&&) = default;
        year_t& operator=(const year_t&) = default;
        year_t& operator=(year_t&&) = default;
        ~year_t() noexcept = default;
        
        int year() const noexcept { return m_year; }
        era_t era() const noexcept { return m_era; }
        
    private:
        int m_year {1970};
        era_t m_era {era_t::ce};
    };
    
    class ordinal_date
    {
    public:
        using year_type = year_t;
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
    
    namespace details
    {
        // wrap milliseconds exceeding 1 day into years, days, and remaining milliseconds
        using need_a_name = std::tuple<ordinal_date::year_type, ordinal_date::day_type, ordinal_date::milliseconds>;
        need_a_name wrap_milliseconds(ordinal_date::milliseconds ms);
        
        // wrap days exceeding 1 year into years and remaining days
        using another_name = std::pair<ordinal_date::year_type, ordinal_date::day_type>;
        another_name wrap_days(ordinal_date::day_type days);
    }
    
    template <class Rep, class Period>
    ordinal_date::ordinal_date(const year_type y,
                               const day_type d,
                               const std::chrono::duration<Rep, Period>& time):
        m_year{y},
        m_day{d},
        m_ms{std::chrono::duration_cast<milliseconds>(time)}
    {
        auto [years, days, ms] = details::wrap_milliseconds(m_ms);
        [years, days] = details::wrap_days(m_day);
    }
}

#endif
