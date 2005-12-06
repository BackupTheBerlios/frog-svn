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
         * This class centralizes all operations on @c timeval
         * structures, which express time in seconds (secs) and
         * microseconds (usecs).
         *
         * This class is based on the @c timeval wrapper class in
         * <A HREF="http://www.cs.wustl.edu/~schmidt/ACE.html">ADAPTIVE
         * Communication Environment (ACE)</A> that was written
         * by Douglas C. Schmidt.
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
               * @param[in] sec seconds value.
               * @param[in] usec subseconds value.
               */
              TimeValue(const int32_t sec, const int32_t usec = 0) throw();

              /**
               * Create a TimeValue from a @p timeval.
               * @param[in] t a @p timeval structure
               */
              TimeValue(const struct timeval& t) throw();

              /**
               * Create a TimeValue from a @p timespec.
               * @param[in] t a @p timespec structure
               */
              TimeValue(const struct timespec& t) throw();

              /**
               * Initialize TimeValue from @p sec and @p usec.
               * @param[in] sec seconds value.
               * @param[in] usec subseconds value.
               */
              void set(const int32_t sec, const int32_t usec = 0) throw();

              /**
               * Initialize TimeValue from a @p timeval.
               * @param[in] tv a @p timeval structure.
               */
              void set(const timeval& tv) throw();

              /**
               * Initialize TimeValue from a @p timespec.
               * @param[in] tv a @p timespec structure.
               */
              void set(const struct timespec& tv) throw();

              /**
               * Initialize TimeValue from a @c double, which is
               * assumed to be in seconds format, with any remainder treated
               * as microseconds.
               */
              void set(const double d) throw();

              /**
               * Convert from TimeValue format into millisecond format.
               * @return Sum of second field (in milliseconds) and microsecond
               * field (in milliseconds). Note that this method can overflow if
               * the second and microsecond field values are large, so use the
               * @c msec(uint64_t& ms) instead (that is if your system supports
               * 64 bit types).
               * @note The semantics of this method differs from the @c sec() and
               * @c usec() methods.  There is no analogous "millisecond"
               * component in a TimeValue.
               */
              uint32_t msec() const throw();

#if defined(HAVE_LONG_LONG)
              /**
               * Convert from TimeValue format into millisecond format.
               * Sum of second field (in milliseconds) and microsecond
               * field (in milliseconds) are returned via @p ms paramter.
               * @note The semantics of this method differs from the @c sec()
               * and @c usec() methods.  There is no analogous "millisecond"
               * component in a TimeValue.
               * @param[out] millisecond value of this TimeValue.
               */
              void msec(uint64_t& ms) const throw();
#endif

              /**
               * Convert from millisecond format into TimeValue format.
               * @note The semantics of this method differs from the @c sec()
               * and @c usec() methods.  There is no analogous "millisecond"
               * component in a TimeValue.
               */
              void msec(int32_t ms) throw();

              /**
               * Returns the value of the object as a @c timespec.
               */
              operator timespec() const;

              /**
               * Returns the value of the object as a @c timeval.
               */
              operator timeval() const;

              /**
               * Get seconds.
               * @return The second field/component of this TimeValue.
               * @note The semantics of this method differs from @c TimeValue::msec() method.
               */
              int32_t sec() const;

              /**
               * Set seconds.
               * @param[in] sec the seconds value.
               */
              void sec(int32_t sec);

              /**
               * Get microseconds.
               * @return The microsecond field/component of this TimeValue.
               * @note The semantics of this method differs from @c TimeValue::msec() method.
               */
              int32_t usec() const;

              /**
               * Set microseconds.
               * @param[in] usec the microseconds value.
               */
              void usec(int32_t usec);

              /**
               * Add @p tv to this.
               * @param[in] tv the TimeValue to add.
               */
              TimeValue& operator+=(const TimeValue& tv);

              /**
               * Assign @p tv to this.
               * @param[in] tv the TimeValue to assign.
               */
              TimeValue& operator=(const TimeValue& tv);

              /**
               * Subtract @p tv to this.
               * @param[in] tv the TimeValue to subtract.
               */
              TimeValue& operator-=(const TimeValue& tv);

              /**
               * Multiply the time value by the @p d factor.
               * @param[in] d the value to multiply TimeValue with.
               * @note The result of the operator is valid for
               * results from range <TT> (INT_MIN, -999999),
               * (INT_MAX, 999999)</TT>. The result outside this
               * range is saturated to a limit.
               */
              TimeValue& operator*=(double d);

              /**
               * Adds two TimeValue objects together, returns the sum.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return The sum of the first and second TimeValue.
               */
              friend TimeValue operator+(const TimeValue& tv1, const TimeValue& tv2)
              {
                  TimeValue sum(tv1);
                  sum += tv2;
              }

              /**
               * Subtracts two TimeValue objects together, returns the difference.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return The difference of the first and second TimeValue.
               */
              friend TimeValue operator-(const TimeValue& tv1, const TimeValue& tv2)
              {
                  TimeValue sum(tv1);
                  sum -= tv2;
              }

              /**
               * Returns @c true if @p tv1 < @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 < @p tv2
               */
              friend bool operator<(const TimeValue& tv1, const TimeValue& tv2)
              {
                  return tv2 > tv1;
              }

              /**
               * Returns @c true if @p tv1 > @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 > @p tv2.
               */
              friend bool operator>(const TimeValue& tv1, const TimeValue& tv2)
              {
                  if (tv1.sec() > tv2.sec())
                      return true;
                  else if (tv1.sec() == tv2.sec()
                          && tv1.usec() > tv2.usec())
                      return true;
                  else
                      return false;

              }

              /**
               * Returns @c true if @p tv1 <= @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 <= @p tv2.
               */
              friend bool operator<=(const TimeValue& tv1, const TimeValue& tv2)
              {
                  return tv2 >= tv1;
              }

              /**
               * Return @c true if @p tv1 >= @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 >= @p tv2.
               */
              friend bool operator>=(const TimeValue& tv1, const TimeValue& tv2)
              {
                  if (tv1.sec() > tv2.sec())
                      return true;
                  else if (tv1.sec() == tv2.sec()
                          && tv1.usec() > tv2.usec())
                      return true;
                  else
                      return false;
              }

              /**
               * Returns @c true if @p tv1 == @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 == @p tv2.
               */
              friend bool operator==(const TimeValue& tv1, const TimeValue& tv2)
              {
                  return tv1.sec() == tv2.sec()
                      && tv1.usec() == tv2.usec();
              }

              /**
               * Returns @c true if @p tv1 != @p tv2.
               * @param[in] tv1 first TimeValue parameter.
               * @param[in] tv2 second TimeValue parameter.
               * @return true if @p tv1 != @p tv2.
               */
              friend bool operator!=(const TimeValue& tv1, const TimeValue& tv2)
              {
                  return !(tv1 == tv2);
              }

              //@{
              /**
               * Multiplies a TimeValue by @p d.
               */
              friend TimeValue operator*(double d, const TimeValue &tv)
              {
                  return TimeValue(tv) *= d;
              }
              friend TimeValue operator*(const TimeValue &tv, double d)
              {
                  return TimeValue(tv) *= d;
              }
              //@}

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
