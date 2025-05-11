#include "Logger.h"

int main(int argc, char *argv[])
{
    LOG_INF("Starting application with %d arguments", argc);
    LOG_DBG("Debugging information: %s", argv[0]);
    LOG_WRN("Warning: This is a warning message");
    LOG_ERR("Error: This is an error message");
    return 0;  
}