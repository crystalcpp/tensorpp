/*
 *  Copyright (C) 2018
 *  @author Ayan Das
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __TENSORPP_LOGGER__
#define __TENSORPP_LOGGER__

// Without this, the function templates won't work
// TODO: need to redo this later
#include <fmt/time.h>
using namespace fmt::literals;

// standard library includes
#include <string>
#include <map>

namespace tensorpp {

// the 'utils' namespace to contain version
// related routines and meta information
namespace utils {

    // Not 'enum class' because the integers associated
    // are required for level comparison
    enum LogLevel {
        Debug,  // debugging info
        Info,   // milestones etc.
        Warn,   // wanring
        Error,  // logical error
        Fatal   // serious trouble
    };

    static const std::map<LogLevel, const char*> LogLevel2Label {
        { LogLevel::Debug, "Debug" },
        { LogLevel::Info , "Info " },
        { LogLevel::Warn , "Warn " },
        { LogLevel::Error, "Error" },
        { LogLevel::Fatal, "Fatal" }
    };

    /* The main logger class of Tensor++, which
    * depends on the 'fmt' library for formatting
    * purpose. */
    class Logger {

    private:
        
        // unique name for a logger object
        const std::string _name = "base";
        // current logging level
        LogLevel _level;

    public:

        // constructor of Logger class
        explicit Logger(const char* loggername, LogLevel defaultlevel = LogLevel::Info)
            : _level(defaultlevel), _name(loggername) {	}

        template<typename ...Args>
        void operator() (LogLevel&& level, const char* onlymsg, Args&&... args) const noexcept {
            // get current time/data
            std::time_t now;

            if ( level >= _level )
            {
                now = std::time(nullptr);

                // The entire log message line consists of two parts:
                // A prefix (containing name of logger, loglevel, and timestamp) ...
                std::string prefix = fmt::format("[{loggername}: {loglevel}][{timestamp:%T}]",
                    "loggername"_a = _name,
                    "loglevel"_a = LogLevel2Label.at(level),
                    "timestamp"_a = *std::localtime(&now)
                );
                
                // ... and the content of the logging message
                std::string content = fmt::format(onlymsg, std::forward<Args>(args)...);

                fmt::print("{prefix}: {content}\n",
                    "prefix"_a = prefix.c_str(),
                    "content"_a = content.c_str()
                );
            }
        }

    };

} // namespace 'utils'
	
    /*
     * This is a part of the "logger registry" defined in
     * 'logger.cpp'; READ 'logger.cpp' for more detail
     */
    namespace utils { extern utils::Logger logger; }

} // namespace 'tensorpp'

#ifdef TENSORPP_DEBUG
    #define TPP_DEBUG(...) logger(LogLevel::Debug, __VA_ARGS__)
    #define TPP_INFO(...) logger(LogLevel::Info, __VA_ARGS__)
    #define TPP_WARN(...) logger(LogLevel::Warn, __VA_ARGS__)
    #define TPP_ERROR(...) logger(LogLevel::Error, __VA_ARGS__)
    #define TPP_FATAL(...) logger(LogLevel::Fatal, __VA_ARGS__)
#else
    #define TPP_DEBUG(...)
    #define TPP_INFO(...)
    #define TPP_WARN(...)
    #define TPP_ERROR(...)
    #define TPP_FATAL(...)
#endif

#endif // __TENSORPP_LOGGER__
