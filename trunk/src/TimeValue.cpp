// C++ implementation file -----------------------------------------------//
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

#include <frog/TimeValue.h>
#include <climits>

namespace frog
{
	namespace util
	{
		//--------------------------------------------------------------
		TimeValue::TimeValue() throw()
		{
			this->set(0, 0);
		}

		//--------------------------------------------------------------
		TimeValue::TimeValue(const int32_t sec, const int32_t usec) throw()
		{
			this->set(sec, usec);
		}

		//--------------------------------------------------------------
		TimeValue::TimeValue(const struct timeval& t) throw()
		{
			this->set(t);
		}

		//--------------------------------------------------------------
		TimeValue::TimeValue(const struct timespec& t) throw()
		{
			this->set(t);
		}
		//--------------------------------------------------------------
		void TimeValue::normalize() throw()
		{
			if(tv_.tv_usec >= ONE_SECOND_IN_USECS)
			{
				// TODO: Need to optimize
				do
				{
					++tv_.tv_sec;
					tv_.tv_usec -= ONE_SECOND_IN_USECS;
				} while(tv_.tv_usec >= ONE_SECOND_IN_USECS);
			}
			else if(tv_.tv_usec <= -ONE_SECOND_IN_USECS)
			{
				// TODO: Need to optimize
				do
				{
					--tv_.tv_sec;
					tv_.tv_usec += ONE_SECOND_IN_USECS;
				} while(tv_.tv_usec <= -ONE_SECOND_IN_USECS);
			}

			if(tv_.tv_sec >= 1 && tv_.tv_usec < 0)
			{
				--tv_.tv_sec;
				tv_.tv_usec += ONE_SECOND_IN_USECS;
			}
		}

		//--------------------------------------------------------------
		void TimeValue::set(const int32_t sec, const int32_t usec) throw()
		{
			tv_.tv_sec = static_cast<long>(sec);
			tv_.tv_usec = static_cast<long>(usec);
			this->normalize();
		}

		//--------------------------------------------------------------
		void TimeValue::set(const timeval& tv) throw()
		{
			tv_.tv_sec = tv.tv_sec;
			tv_.tv_usec = tv.tv_usec;
			this->normalize();
		}	

		//--------------------------------------------------------------
		void TimeValue::set(const struct timespec& tv) throw()
		{
			tv_.tv_sec = static_cast<long>(tv.tv_sec);
			// Convert nanoseconds into microseconds.
			tv_.tv_usec = tv.tv_nsec / 1000;
			this->normalize();
		}	

		//--------------------------------------------------------------
		void TimeValue::set(const double d) throw()
		{
			int32_t i = static_cast<long>(d);
			tv_.tv_sec = i;
			tv_.tv_usec = static_cast<long>((d - static_cast<double>(i)) * ONE_SECOND_IN_USECS + 0.5);
			this->normalize();
		}

		//--------------------------------------------------------------
		uint32_t TimeValue::msec() const throw()
		{
			return this->tv_.tv_sec * 1000 + this->tv_.tv_usec / 1000;
		}

#if defined(HAVE_LONG_LONG)	
		//--------------------------------------------------------------
		void TimeValue::msec(uint64_t& ms) const throw()
		{
			ms = static_cast<uint32_t> (this->tv_.tv_sec);
			ms *= 1000;
			ms += (this->tv_.tv_usec / 1000);
		}
#endif

		//--------------------------------------------------------------
		void TimeValue::msec(int32_t ms) throw()
		{
			// Convert millisecond units to seconds
			this->tv_.tv_sec = ms / 1000;
			// Convert remainder to microseconds
			this->tv_.tv_usec = (ms - (this->tv_.tv_sec * 1000)) * 1000;

		}

		//--------------------------------------------------------------
		TimeValue::operator timespec() const
		{
			struct timespec tv;
			tv.tv_sec = this->sec();
			// Convert microseconds into nanoseconds.
			tv.tv_nsec= this->tv_.tv_usec * 1000;
		}

		//--------------------------------------------------------------
		TimeValue::operator timeval() const
		{
			return this->tv_;
		}

		//--------------------------------------------------------------
		int32_t TimeValue::sec() const
		{
			return this->tv_.tv_sec;
		}

		//--------------------------------------------------------------
		void TimeValue::sec(int32_t sec)
		{
			this->tv_.tv_sec = sec;
		}

		//--------------------------------------------------------------
		int32_t TimeValue::usec() const
		{
			return this->tv_.tv_usec;
		}

		//--------------------------------------------------------------
		void TimeValue::usec(int32_t usec)
		{
			this->tv_.tv_usec = usec;
		}

		//--------------------------------------------------------------
		TimeValue& TimeValue::operator+=(const TimeValue& tv)
		{
			this->sec(this->sec() + tv.sec());
			this->usec(this->usec() + tv.usec());
			this->normalize();
			return *this;
		}

		//--------------------------------------------------------------
		TimeValue& TimeValue::operator=(const TimeValue& tv)
		{
			this->sec(tv.sec());
			this->usec(tv.usec());
			return *this;
		}

		//--------------------------------------------------------------
		TimeValue& TimeValue::operator-=(const TimeValue& tv)
		{
			this->sec(this->sec() - tv.sec());
			this->usec(this->usec() - tv.usec());
			this->normalize();
			return *this;
		}

		//--------------------------------------------------------------
		TimeValue& TimeValue::operator*=(double d)
		{
			// double is long enough (16 digits) to not lose the accuracy.
			double time_total = 
				(this->sec() + 
				 static_cast<double> (this->usec()) / ONE_SECOND_IN_USECS) * d;

			// Shall we saturate the result?
			static const double max_int = INT_MAX + 0.999999;
			static const double min_int = INT_MIN - 0.999999;

			if (time_total > max_int)
				time_total = max_int;
			if (time_total < min_int)
				time_total = min_int;

			const int32_t time_sec = static_cast<int32_t>(time_total);

			time_total -= time_sec;
			time_total *= ONE_SECOND_IN_USECS;

			int32_t time_usec = static_cast<int32_t>(time_total);

			// Round up the result to save the last usec
			if (time_usec > 0 && (time_total - time_usec) >= 0.5)
				++time_usec;
			else if (time_usec < 0 && (time_total - time_usec) <= -0.5)
				--time_usec;

			this->set(time_sec, time_usec);
			this->normalize(); // Protect against future changes in normalization

			return *this;
		}
	} // util ns
} // frog ns
