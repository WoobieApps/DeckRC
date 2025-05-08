#include "Logger.h"
#include <ctime>
#include <iomanip>
#include <chrono>
#include <iostream>


std::string getTimestampNow()
{
    static char buffer[13];
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;
    
    time_t now_time = std::chrono::system_clock::to_time_t(now);
    struct tm tm_buf;
    localtime_r(&now_time, &tm_buf);
    
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d.%03d",
        tm_buf.tm_hour,
        tm_buf.tm_min, 
        tm_buf.tm_sec,
        static_cast<int>(now_ms.count()));
        
    return std::string(buffer);
}