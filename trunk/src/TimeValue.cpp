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
		TimeValue::TimeValue(const struct timeval& tv) throw()
		{
			this->set(tv);
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
		void TimeValue::set(const double d) throw()
		{
			int32_t i = static_cast<long>(d);
			tv_.tv_sec = i;
			tv_.tv_usec = static_cast<long>((d - static_cast<double>(i)) * ONE_SECOND_IN_USECS + 0.5);
			this->normalize();
		}
	} // util ns
} // frog ns
