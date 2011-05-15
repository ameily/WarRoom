#
#   This file is part of the War Room project
#   Url: https://github.com/ameily/WarRoom
#   Copyright (C) 2011  Adam Meily <meily.adam@gmail.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

project(WarRoom)
cmake_minimum_required(VERSION 2.6)

if(MINGW)
    set(DIST_LIBDIR win)
    set(DIST_BINDIR win)
else(MINGW)
    set(DIST_LIBDIR unix/lib)
    set(DIST_BINDIR unix/bin)
endif(MINGW)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/dist)

add_subdirectory(libwar)
add_subdirectory(waredit)

add_subdirectory(armoury)