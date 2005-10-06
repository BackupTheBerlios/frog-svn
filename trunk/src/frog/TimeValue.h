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

#include <frog/stdint.h>

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#if !defined(HAVE_STRUCT_TIMESPEC)
// Definition per POSIX.
typedef struct timespec
{
	// Seconds
	time_t tv_sec;
	// Nanoseconds
	long tv_nsec;
} timespec_t;
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
		#define ONE_SECOND_IN_MSECS 1000L /**< Milliseconds in one second */
		#define ONE_SECOND_IN_USECS 1000000L /**< Microseconds in one second */
		#define ONE_SECOND_IN_NSECS 1000000000L /**< Nanoseconds in one second */
		
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
		  public:
			/**
			 * Default constructor.
			 */
			TimeValue() throw();

			/**
			 * Create a TimeValue given the second and subsecond value.
			 * @param[in] sec Seconds value.
			 * @param[in] usec Subseconds value.
			 */
			TimeValue(const int32_t sec, const int32_t usec = 0) throw();

			/**
			 * Create a TimeValue from a <TT>timeval</TT>
			 * @param[in] t A <TT>timeval</TT> structure
			 */
			TimeValue(const struct timeval& t) throw();

			/**
			 * Create a TimeValue from a <TT>timespec_t</TT>
			 * @param[in] t A <TT>timespec</TT> structure
			 */
			TimeValue(const struct timespec& t) throw();
		
			/**
			 * Initialize TimeValue from @p sec and @p usec.
			 * @param[in] sec Seconds value.
			 * @param[in] usec Subseconds value.
			 */
			void set(const int32_t sec, const int32_t usec = 0) throw();

			/**
			 * Initialize TimeValue from a @p timeval.
			 * @param[in] tv A <TT>timeval</TT> structure.
			 */
			void set(const timeval& tv) throw();

			/**
			 * Initialize TimeValue from a @p timespec_t.
			 * @param[in] tv A <TT>timespec</TT> structure.
			 */
			void set(const timespec& tv) throw();

			/**
			 * Initialize TimeValue from a <TT>double</TT>, which is
			 * assumed to be in seconds format, with any remainder treated
			 * as microseconds.
			 */
			void set(const double d) throw();

			/**
			 * Convert from TimeValue format into millisecond format.
			 * @return Sum of second field (in milliseconds) and microsecond
			 * field (in milliseconds). Note that this method can overflow if
			 * the second and microsecond field values are large, so use the
			 * msec(uint64_t& ms) instead (that is if your system supports
			 * 64 bit types).
			 * @note The semantics of this method differs from the sec() and
			 * usec() methods.  There is no analogous "millisecond"
			 * component in a TimeValue.
			 */
			uint32_t msec() const throw();

#if defined(HAVE_LONG_LONG)
			/**
			 * Convert from TimeValue format into millisecond format.
			 * Sum of second field (in milliseconds) and microsecond
			 * field (in milliseconds) are returned via @p ms paramter.
			 * @note The semantics of this method differs from the sec() and
			 * usec() methods.  There is no analogous "millisecond"
			 * component in a TimeValue.
			 * @param[out] Millisecond value of this TimeValue.
			 */
			void msec(uint64_t& ms) const throw();
#endif

			/**
			 * Convert from millisecond format into TimeValue format.
			 * @note The semantics of this method differs from the sec() and
			 * usec() methods.  There is no analogous "millisecond"
			 * component in a TimeValue.
			 */
			void msec(int32_t ms) throw();

			/**
			 * Zero time.
			 */
			static const TimeValue zero;
		  private:
			/**
			 * Puts <TT>timeval</TT> in canonical form.
			 */
			void normalize() throw();
			
			timeval tv_; /**< Values are stored as <TT>timeval</tt> */
		}; // TimeValue cls
	} // util ns
} // frog ns

#endif // FROG_UTIL_TIMEVALUE
