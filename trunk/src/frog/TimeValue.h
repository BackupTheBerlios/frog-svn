// C++ header file -------------------------------------------------------//
//   Frog Framework - A useful framework for C++ applications.
//   Copyright (C) 2005 by Janvier D. Anonical <janvier@users.berlios.de>
//
//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public
//   License as published by the Free Software Foundation; either
//   version 2.1 of the License, or (at your option) any later version.
//
//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Lesser General Public License for more details.
//
//   You should have received a copy of the GNU Lesser General Public
//   License along with this library; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
//   MA  02110-1301  USA
//------------------------------------------------------------------------//


#ifndef FROG_UTIL_TIMEVALUE
#define FROG_UTIL_TIMEVALUE

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * @namespace frog::util Contains miscellaneous utility classes.
	 */
	namespace util
	{
		/**
		 * This class centralizes all operations on <TT>timeval</TT>
		 * structures, which express time in seconds (secs) and
		 * microseconds (usecs).
		 *
		 * This class is based on the timeval wrapper class in
		 * ADAPTIVE Communication Environment (ACE) that was written
		 * by Douglas C. Schmidt. The web page can be found at
		 * http://www.cs.wustl.edu/~schmidt/ACE.html
		 */
		class TimeValue
		{
		}; // TimeValue cls
	} // util ns
} // frog ns

#endif // FROG_UTIL_TIMEVALUE
