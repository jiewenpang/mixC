#include <log4cplus/logger.h>  
#include <LogRegister.h>
using namespace std;  
using namespace log4cplus;  

int main()  
{  
	Logger logger = Logger::getInstance("putong");
	LogRegister::setLogProperty(logger, "./log/service", "%d{%Y-%m-%d %H:%M:%S.%Q} %-5p - %m%n");
	LOG4CPLUS_DEBUG(logger, "I am testing" );

	Logger stlogger = Logger::getInstance("tongji");
	LogRegister::setLogProperty(stlogger, "./log/statistics");
	LOG4CPLUS_DEBUG(stlogger, "I am testing" );
	LOG4CPLUS_DEBUG(stlogger, "I am testing" );
	return 0;  
} 
