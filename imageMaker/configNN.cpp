
#include "configNN.h"

#ifdef __ANDROID__
#include <android/log.h>
#endif //__ANDROID__ 

#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif


namespace imgmaker
{
	static std::string formatString(const char* fmt, va_list args)
	{
		std::string content;
		//int vsnprintf(char *str, size_t size, const char *format, va_list ap);	
		//函数说明：将可变参数格式化输出到一个字符数组
		//参数：str输出到的数组，size指定大小，防止越界，format格式化参数，ap可变参数列表函数用
		const int size = vsnprintf(NULL, 0, fmt, args);
		if (size > 0) {
			content.resize(size);
			vsprintf(const_cast<char*>(content.data()), fmt, args);
		}
		return content;
	}
	//level转字符串
	static std::string level2str(const LogLevel level)
	{
		switch (level)
		{
		case LogLevel::IMGMAKER_LOG_LEVEL_VERBOSE:
			return "verbose";
		case LogLevel::IMGMAKER_LOG_LEVEL_CRITICAL:
			return "critical";
		case LogLevel::IMGMAKER_LOG_LEVEL_FATAL:
			return "fatal";
		default:
			break;
		}
		return "unknown";
	}
	static std::string buildInnerContent(const LogLevel level, const std::string& content)
	{
		std::stringstream ss;
		const auto t = time(nullptr);
		const auto local = localtime(&t);
		ss << "[" <<
			std::setw(4) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_year + 1990 << "/" <<
			std::setw(2) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_mon + 1 << "/" <<
			std::setw(2) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_mday << " " <<
			std::setw(2) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_hour << ":" <<
			std::setw(2) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_min << ":" <<
			std::setw(2) << std::setfill('0') << std::setiosflags(std::ios::fixed) << local->tm_sec << "]";
		ss << "[" << level2str(level) << "] " << content << std::endl;
		return ss.str();
	}
	static void defaultLogRoute(const LogLevel level, const std::string& content)
	{
		const std::string innerContent = buildInnerContent(level, content);
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "digit", "log : %s", innerContent.c_str());
#else
		std::cout << innerContent;
		std::cout.flush();
#endif //__ANDROID__
	}

	//////////////////////////////////////////////////////////////////////////
	static LogLevel globalLogLevel = LogLevel::IMGMAKER_LOG_LEVEL_VERBOSE;
	static std::function<void(const LogLevel, const std::string)> globalLogCb = defaultLogRoute;
	//log level setting
	void setLogLevel(const LogLevel level)
	{
		globalLogLevel = level;
	}
	LogLevel getLogLevel()
	{
		return globalLogLevel;
	}
	//log route setting
	void setLogRedirect(std::function<void(const LogLevel, const std::string)> logCb)
	{
		globalLogCb = logCb;
	}
	//log function
	void logVerbose(const char* fmt, ...)
	{
		const LogLevel level = LogLevel::IMGMAKER_LOG_LEVEL_VERBOSE;
		if (globalLogLevel > level)
		{
			return;
		}
		va_list args;
		va_start(args, fmt);
		globalLogCb(level, formatString(fmt, args));
		va_end(args);
	}
	void logCritical(const char* fmt, ...)
	{
		const LogLevel level = LogLevel::IMGMAKER_LOG_LEVEL_CRITICAL;
		if (globalLogLevel > level)
		{
			return;
		}
		va_list args;
		va_start(args, fmt);
		globalLogCb(level, formatString(fmt, args));
		va_end(args);
	}
	void logFatal(const char* fmt, ...)
	{
		const LogLevel level = LogLevel::IMGMAKER_LOG_LEVEL_FATAL;
		if (globalLogLevel > level)
		{
			return;
		}
		va_list args;
		va_start(args, fmt);
		globalLogCb(level, formatString(fmt, args));
		va_end(args);
	}

	//Assert-----------------------------------------------------------------------
	static void* globalAssertFatalUserData = nullptr;
	static void(*globalAssertFatalCB)(void* userData, const std::string& errorStr) = nullptr;

	void setAssertFatalCallback(void(*cb)(void* userData, const std::string& errorStr), void* userData)
	{
		globalAssertFatalCB = cb;
		globalAssertFatalUserData = userData;
	}
	static std::string formatString(const char* fmt, ...)//静态全局变量
	{
		std::string s;
		va_list ap;//char*
		va_start(ap, fmt);
		int size = vsnprintf(NULL, 0, fmt, ap);//统计字符串长度
		va_end(ap);
		if (size > 0) 
		{
			s.resize(size);
			va_start(ap, fmt);
			// Writes the trailing '\0' as well, but we don't care.写入string:s
			vsprintf(const_cast<char*>(s.data()), fmt, ap);
			va_end(ap);
		}
		return s;
	}
	void easyAssertCore(const std::string& file, const std::string& function, const long line,const bool condition, const char* fmt, ...)
	{
		if (!condition)
		{
			va_list args;
			va_start(args, fmt);
			const std::string errorStr = formatString(fmt, args);
			logFatal("FILE:%s,FUNCTION:%s,LINE:%d", file.c_str(), function.c_str(), line);
			logFatal(fmt, args);
			va_end(args);
			if (globalAssertFatalCB)
			{
				globalAssertFatalCB(globalAssertFatalUserData, errorStr);
			}
			else
			{
				assert(false);
				exit(0);
			}
		}
	}
}