/*
 * Logger.h
 *
 *  Created on: Jul 29, 2021
 *      Author: reedt
 */

#ifndef SRC_SHARED_LOGGING_LOGGER_H_
#define SRC_SHARED_LOGGING_LOGGER_H_

#include <vector>
#include <string>
#include <cstring>
#include <stdarg.h>
#include <cinttypes>

#include "logging.h"

#define HEX_BYTE	"#04X"
#define HEX_SHORT	"#06X"
#define HEX_WORD	"#010lX"
#define HEX_LONG	"#018llX"

class Logger
{
public:
	/*!
	 \brief Default logging level.
	 */
	static const LogLevel DEFAULT_LEVEL = LOG_LEVEL_INFO;

	/*!
	 \brief Constructor.
	 \param name Category name.

	 Default-constructed logger uses category name specified at module level (typically, "app").
	 */
	explicit Logger(const char *name = LOG_MODULE_CATEGORY);
	/*!
	 \brief Generates trace message.
	 \param fmt Format string.
	 */
	void trace(const char *fmt, ...) const
			__attribute__((format(printf, 2, 3))); // First argument is implicit 'this'

	void debug(const char *fmt, ...) const
			__attribute__((format(printf, 2, 3)));

	/*!
	 \brief Generates info message.
	 \param fmt Format string.
	 */
	void info(const char *fmt, ...) const __attribute__((format(printf, 2, 3)));
	/*!
	 \brief Generates warning message.
	 \param fmt Format string.
	 */
	void warn(const char *fmt, ...) const __attribute__((format(printf, 2, 3)));
	/*!
	 \brief Generates error message.
	 \param fmt Format string.
	 */
	void error(const char *fmt, ...) const
			__attribute__((format(printf, 2, 3)));
	/*!
	 \brief Generates log message.
	 \param fmt Format string.

	 This method uses default logging level (\ref DEFAULT_LEVEL).
	 */
	void log(const char *fmt, ...) const __attribute__((format(printf, 2, 3)));
	/*!
	 \brief Generates log message.
	 \param level Logging level.
	 \param fmt Format string.
	 */
	void log(LogLevel level, const char *fmt, ...) const
			__attribute__((format(printf, 3, 4)));
	/*!
	 \brief Writes formatted string to log.
	 \param fmt Format string.

	 This method uses default logging level (\ref DEFAULT_LEVEL).
	 */
	void printf(const char *fmt, ...) const
			__attribute__((format(printf, 2, 3)));
	/*!
	 \brief Writes formatted string to log.
	 \param level Logging level.
	 \param fmt Format string.
	 */
	void printf(LogLevel level, const char *fmt, ...) const
			__attribute__((format(printf, 3, 4)));
	/*!
	 \brief Writes string to log.
	 \param str String.

	 This method uses default logging level (\ref DEFAULT_LEVEL).
	 */
	void print(const char *str) const;
	/*!
	 \brief Writes string to log.
	 \param level Logging level.
	 \param str String.
	 */
	void print(LogLevel level, const char *str) const;
	/*!
	 \brief Writes character buffer to log.
	 \param data Buffer.
	 \param size Buffer size.

	 This method uses default logging level (\ref DEFAULT_LEVEL).
	 */
	void write(const char *data, size_t size) const;
	/*!
	 \brief Writes character buffer to log.
	 \param level Logging level.
	 \param data Buffer.
	 \param size Buffer size.
	 */
	void write(LogLevel level, const char *data, size_t size) const;
	/*!
	 \brief Encodes data buffer in hex and writes resulting string to log.
	 \param data Buffer.
	 \param size Buffer size.

	 This method uses default logging level (\ref DEFAULT_LEVEL).
	 */
	void dump(const void *data, size_t size) const;
	/*!
	 \brief Encodes data buffer in hex and writes resulting string to log.
	 \param level Logging level.
	 \param data Buffer.
	 \param size Buffer size.
	 */
	void dump(LogLevel level, const void *data, size_t size) const;
	/*!
	 \brief Returns `true` if trace level is enabled for this logger.
	 */
	bool isTraceEnabled() const;
	/*!
	 \brief Returns `true` if info level is enabled for this logger.
	 */
	bool isInfoEnabled() const;
	/*!
	 \brief Returns `true` if warning level is enabled for this logger.
	 */
	bool isWarnEnabled() const;
	/*!
	 \brief Returns `true` if error level is enabled for this logger.
	 */
	bool isErrorEnabled() const;
	/*!
	 \brief Returns `true` if specified level is enabled for this logger.
	 \param level Logging level.
	 */
	bool isLevelEnabled(LogLevel level) const;
	/*!
	 \brief Returns category name set for this logger.
	 */
	const char* name() const;
	/*!
	 \brief This method is an alias for \ref log(const char*, ...).
	 */
	void operator()(const char *fmt, ...) const
	__attribute__((format(printf, 2, 3)))
	{
		va_list args;
		va_start(args, fmt);
		log(DEFAULT_LEVEL, fmt, args);
		va_end(args);
	}
	/*!
	 \brief This method is an alias for \ref log(LogLevel, const char*, ...).
	 */
	void operator()(LogLevel level, const char *fmt, ...) const
	__attribute__((format(printf, 3, 4)))
	{
		va_list args;
		va_start(args, fmt);
		log(level, fmt, args);
		va_end(args);
	}

	// This class is non-copyable
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

private:
	const char *const name_; // Category name

	void log(LogLevel level, const char *fmt, va_list args) const;
};

inline Logger::Logger(const char *name) :
		name_(name)
{
}

inline void Logger::trace(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(LOG_LEVEL_TRACE, fmt, args);
	va_end(args);
}

inline void Logger::debug(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(DEBUG_LEVEL, fmt, args);
	va_end(args);
}

inline void Logger::info(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(LOG_LEVEL_INFO, fmt, args);
	va_end(args);
}

inline void Logger::warn(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(LOG_LEVEL_WARN, fmt, args);
	va_end(args);
}

inline void Logger::error(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(LOG_LEVEL_ERROR, fmt, args);
	va_end(args);
}

inline void Logger::log(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(DEFAULT_LEVEL, fmt, args);
	va_end(args);
}

inline void Logger::log(LogLevel level, const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log(level, fmt, args);
	va_end(args);
}

inline void Logger::printf(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log_printf_v(DEFAULT_LEVEL, name_, nullptr, fmt, args);
	va_end(args);
}

inline void Logger::printf(LogLevel level, const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	log_printf_v(level, name_, nullptr, fmt, args);
	va_end(args);
}

inline void Logger::print(const char *str) const
{
	print(DEFAULT_LEVEL, str);
}

inline void Logger::print(LogLevel level, const char *str) const
{
	write(level, str, strlen(str));
}

inline void Logger::write(const char *data, size_t size) const
{
	write(DEFAULT_LEVEL, data, size);
}

inline void Logger::write(LogLevel level, const char *data, size_t size) const
{
	if (data)
	{
		log_write(level, name_, data, size, nullptr);
	}
}

inline void Logger::dump(const void *data, size_t size) const
{
	dump(DEFAULT_LEVEL, data, size);
}

inline void Logger::dump(LogLevel level, const void *data, size_t size) const
{
	if (data)
	{
		log_dump(level, name_, data, size, 0, nullptr);
	}
}

inline bool Logger::isTraceEnabled() const
{
	return isLevelEnabled(LOG_LEVEL_TRACE);
}

inline bool Logger::isInfoEnabled() const
{
	return isLevelEnabled(LOG_LEVEL_INFO);
}

inline bool Logger::isWarnEnabled() const
{
	return isLevelEnabled(LOG_LEVEL_WARN);
}

inline bool Logger::isErrorEnabled() const
{
	return isLevelEnabled(LOG_LEVEL_ERROR);
}

inline bool Logger::isLevelEnabled(LogLevel level) const
{
	return log_enabled(level, name_, nullptr);
}

inline const char* Logger::name() const
{
	return name_;
}

inline void Logger::log(LogLevel level, const char *fmt, va_list args) const
{
	LogAttributes attr;
	attr.size = sizeof(LogAttributes);
	attr.flags = 0;
	log_message_v(level, name_, &attr, nullptr, fmt, args);
}

#endif /* SRC_SHARED_LOGGING_LOGGER_H_ */
