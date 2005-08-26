// C++ implementation file -----------------------------------------------//
//   Frog Framework - A useful framework for C++ applications.
//   Copyright (C) 2005 by Janvier D. Anonical <janvier@gmail.com>
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


#include <frog/NetworkInterface.h>

namespace frog
{
	namespace sys
	{
		namespace net
		{
			//--------------------------------------------------------------
			NetworkInterface::NetworkInterface(const InetAddress& addr)
			{
			}

			//--------------------------------------------------------------
			static std::vector<NetworkInterface> NetworkInterface::getNetworkInterfaces() const
			{
			}

			//--------------------------------------------------------------
			std::string NetworkInterface::getName() const
			{
			}
			
			//--------------------------------------------------------------
			std::string NetworkInterface::getDisplayName() const
			{
			}
		} // net ns
	} // sys ns
} // frog ns
