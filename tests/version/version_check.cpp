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

// the Tensor++ headers
#include <tensorpp/tensorpp.hpp>
using namespace tensorpp;

// GoogleTest headers
#include <gtest/gtest.h>

// standard headers
#include <string>

TEST(version, version_check_simple)
{
	auto tensorpp_version = version::get_tensorpp_version();
    ASSERT_EQ(tensorpp_version._major, PROJECT_VERSION_MAJOR);
    ASSERT_EQ(tensorpp_version._minor, PROJECT_VERSION_MINOR);
    ASSERT_EQ(tensorpp_version._patch, PROJECT_VERSION_PATCH);
}
