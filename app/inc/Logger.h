#pragma once
#include <cstdio>
#include <string>
#include <thread>
#include <cstdarg>

std::string getTimestampNow();

// Define log levels
enum class LogLevel {
    DISABLED = -1,
	ERR = 0,
	WRN = 1,
	INF = 2,
	DBG = 3
};
    
// Set current log level - change this to filter logs
const LogLevel k_LogLevel{ LogLevel::DBG };

void LOG(LogLevel level, const char* levelStr, const char* file, int line, const char* fmt, ...); 

#define LOG_ERR(fmt, ...) LOG(LogLevel::ERR, "ERR", __FILE_NAME__, __LINE__,fmt, ##__VA_ARGS__)
#define LOG_WRN(fmt, ...) LOG(LogLevel::WRN, "WRN", __FILE_NAME__, __LINE__,fmt, ##__VA_ARGS__)
#define LOG_INF(fmt, ...) LOG(LogLevel::INF, "INF", __FILE_NAME__, __LINE__,fmt, ##__VA_ARGS__)
#define LOG_DBG(fmt, ...) LOG(LogLevel::DBG, "DBG", __FILE_NAME__, __LINE__,fmt, ##__VA_ARGS__)
