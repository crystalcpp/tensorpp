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

#ifndef __TENSORPP__VERSION__
#define __TENSORPP__VERSION__

/* standard library includes
 * must go at the very begining */
#include <string>

#include <tensorpp/utils/meta_structs.hpp>

namespace tensorpp {
// the 'version' namespace to contain version
// related routines and meta information
namespace utils {

    // get current Tensor++ version
    VersionStruct get_tensorpp_version() {
        return VersionStruct(TENSORPP_VERSION_MAJOR,
                            TENSORPP_VERSION_MINOR,
                            TENSORPP_VERSION_PATCH);
    }
    
    // get the system name; i.e. OS
    std::string get_system_name() {
        return std::string(TENSORPP_SYSTEM);
    }
    
    // get platform architecture
    SysArch get_system_arch() {
        #ifdef TENSORPP_64BIT
            return SysArch::BIT_64;
        #else
            return SysArch::BIT_32;
        #endif
    }

    // print configuration info
    void print_info(bool system = true, bool compiler = true) {
        // a local logger
        auto logger = spdlog::stdout_color_st(TENSORPP);
        logger->set_pattern("[%n:%L] %v");

        // start logging
        logger->info("Project: {}", TENSORPP);
        auto tensorpp_version = get_tensorpp_version();
        logger->info("Version: {}.{}.{}", 
            tensorpp_version._major,
            tensorpp_version._minor,
            tensorpp_version._patch);
        
        if (system) {
            logger->info("System: {}", get_system_name());
            
            if (get_system_arch() == SysArch::BIT_64)
                logger->info("Built with 64 bit");
            else
                logger->info("Built with 32 bit");
        }
        
        if (compiler)
            logger->info("{} ({}) compiler with C++{}", TENSORPP_CXX_COMPILER_ID,
                TENSORPP_CXX_COMPILER_VERSION, TENSORPP_CXX_STANDARD);
    }
    
    
} // namespace 'version'

} // namespace 'tensorpp'

#endif