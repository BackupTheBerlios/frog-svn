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


#include <cstdio>
#include <string>

#include <frog/Object.h>

namespace frog
{
	namespace sys
	{
		//--------------------------------------------------------------
		Object::Object() throw()
			: hash_(0)
		{
		}

		//--------------------------------------------------------------
		Object::~Object() throw()
		{
		}

		//--------------------------------------------------------------
		uint32_t Object::hashCode() const throw()
		{
			if(hash_ == 0)
			{
				uint32_t* hash_p = const_cast<uint32_t*>(&hash_);
				uint32_t key = (uint32_t)this;
				key += ~(key << 15);
				key ^= (key >> 10);
				key += (key << 3);
				key ^= (key >> 6);
				key += ~(key << 11);
				key ^= (key >> 16);

				*hash_p = key;
			}
			return hash_;
		}
		
		//--------------------------------------------------------------
		bool Object::sameObject(const Object* obj) const throw()
		{
			return (this->hashCode() == obj->hashCode());
		}
		
		//--------------------------------------------------------------
		bool Object::sameObject(const Object* objA, const Object* objB) throw()
		{
			return (objA->hashCode() == objB->hashCode());
		}

		//--------------------------------------------------------------
		std::string Object::toString() const throw()
		{
			char hashValue[8];
			memset(hashValue, 0, 8);
			::sprintf(hashValue, "%x", hashCode());
			return std::string("Object") + "@" + hashValue;
		}
	} // sys ns
} // frog ns
