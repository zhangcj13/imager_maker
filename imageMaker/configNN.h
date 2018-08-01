#ifndef CONFIGNN_H_
#define CONFIGNN_H_


#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>
#include <cstdarg>
#include <functional>

#include <cassert>
#include <cstdlib>

#define WITH_OPENCV_DEBUG 0
#define WITH_ENCRYPT_MODEL 0
namespace imgmaker
{
	//逻辑日志 级别判断
	enum LogLevel
	{
		IMGMAKER_LOG_LEVEL_VERBOSE,
		IMGMAKER_LOG_LEVEL_CRITICAL,
		IMGMAKER_LOG_LEVEL_FATAL,
		IMGMAKER_LOG_LEVEL_NONE
	};

	void setLogLevel(const LogLevel level);
	LogLevel getLogLevel();
	//default : console
	void setLogRedirect(std::function<void(const LogLevel, const std::string)> logCb);
	//
	void logVerbose(const char* fmt, ...);
	void logCritical(const char* fmt, ...);
	void logFatal(const char* fmt, ...);

	//----------------------------------------------------------easy_Assert
	void setAssertFatalCallback(void(*cb)(void* userData, const std::string& errorStr), void* userData);
	void easyAssertCore(const std::string& file, const std::string& function, const long line, const bool condition, const char* fmt, ...);
#define easyAssert(condition,fmt,...) \
	imgmaker::easyAssertCore(__FILE__,__FUNCTION__,__LINE__,(condition),(fmt),##__VA_ARGS__);
}
#endif