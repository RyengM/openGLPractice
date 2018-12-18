#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <spdlog/spdlog.h>


class Logger
{
public:
    static void initialize(const std::string& tag)
    {
        tag_ = tag;
        console_ = spdlog::stdout_color_mt(tag_);
    }

    static std::shared_ptr<spdlog::logger>& get_logger()
    {
        return console_;
    }

    template<typename T>
    static void trace(const T& message)
    {
        console_->trace(message);
    }

    template<typename T>
    static void debug(const T& message)
    {
        console_->debug(message);
    }

    template<typename T>
    static void info(const T& message)
    {
        console_->info(message);
    }

    template<typename T>
    static void warn(const T& message)
    {
        console_->warn(message);
    }

    template<typename T>
    static void error(const T& message)
    {
        console_->error(message);
    }

    template<typename T>
    static void critical(const T& message)
    {
        console_->critical(message);
    }

    template<typename Arg1, typename... Args>
    static void trace(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->trace(fmt, arg1, args...);
    }

    template<typename Arg1, typename... Args>
    static void debug(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->debug(fmt, arg1, args...);
    }

    template<typename Arg1, typename... Args>
    static void info(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->info(fmt, arg1, args...);
    }

    template<typename Arg1, typename... Args>
    static void warn(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->warn(fmt, arg1, args...);
    }

    template<typename Arg1, typename... Args>
    static void error(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->error(fmt, arg1, args...);
    }

    template<typename Arg1, typename... Args>
    static void critical(const char *fmt, const Arg1 &arg1, const Args &... args)
    {
        console_->critical(fmt, arg1, args...);
    }

private:
    static std::string tag_;
    static std::shared_ptr<spdlog::logger> console_;
};

#endif // _LOGGER_HPP_