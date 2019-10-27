#ifndef         TIMER_H
#define         TIMER_H

#include        <chrono>
#include        <iostream>

class   Timer {

    private: 
        std::chrono::high_resolution_clock::time_point      m_start, m_end;
    public: 

        Timer () {
            std::cout << "timer start" << std::endl;
            m_start = std::chrono::high_resolution_clock::now();
        }

        ~Timer () {
            std::cout << "elapsed time = " << stop () << " seconds" << std::endl;
            std::cout << "timer stop" << std::endl;
        }

        double  stop () {
            m_end = std::chrono::high_resolution_clock::now();

            std::chrono::nanoseconds elTime = m_end - m_start;
            double  fElTime = elTime.count();

            return fElTime*1e-9;
        }
};



#endif
