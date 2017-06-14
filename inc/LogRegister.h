#include <log4cplus/logger.h>  
#include <log4cplus/loggingmacros.h>  
#include <log4cplus/configurator.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/layout.h>  
using namespace std;  
using namespace log4cplus;  

class LogRegister {
	public :
		static void setLogProperty(Logger &logger, 
					string path="./service", 
					string patten="%d{%Y-%m-%d %H:%M:%S.%Q} [%t] %-5p - %m%n", 
					LogLevel level=ALL_LOG_LEVEL){
			SharedAppenderPtr append(new  DailyRollingFileAppender(path, DAILY, true, 5));
			auto_ptr<Layout> layout(new PatternLayout(patten));
			append->setLayout(layout);
			logger.addAppender(append);
			logger.setLogLevel(ALL_LOG_LEVEL);
		}
};
