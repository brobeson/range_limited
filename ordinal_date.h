#ifndef od_h
#define od_h

namespace od
{
    class ordinal_date
    {
    public:
        using year = int;
        using day = int;
        
        ordinal_date() = default;
        
        template <class Rep, class Period>
        ordinal_date(const year y,
                     const day d,
                     const std::chrono::duration<Rep, Period>& time);
    
    private:
        year m_y;
        day m_d;
        

#endif
