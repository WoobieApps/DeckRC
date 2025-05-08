#pragma once
#include <cstdio>
#include <string>

std::string getTimestampNow();

#define LOG(level, fmt, ...) \
        std::printf("%s [%s] %s:%d: " fmt "\n", \
        getTimestampNow().c_str(), level, __FUNCTION__, __LINE__, ##__VA_ARGS__);

#define LOG_INF(fmt, ...) LOG("INF", fmt, ##__VA_ARGS__)
#define LOG_DBG(fmt, ...) LOG("DBG", fmt, ##__VA_ARGS__)
#define LOG_WRN(fmt, ...) LOG("WRN", fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) LOG("ERR", fmt, ##__VA_ARGS__)
