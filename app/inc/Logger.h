#pragma once
#include <cstdio>
#include <string>

std::string getTimestampNow();

#define LOG(level,msg) \
        std::printf("%s : [%s] %s:%d: %s\n", \
        getTimestampNow().c_str(), level,__FUNCTION__, __LINE__, msg)

#define LOG_INF(msg) LOG("INF", msg)
#define LOG_DBG(msg) LOG("DBG", msg)
#define LOG_WRN(msg) LOG("WRN", msg)
#define LOG_ERR(msg) LOG("ERR", msg)