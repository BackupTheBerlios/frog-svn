// C++ header file -------------------------------------------------------//
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


#ifndef FROG_SYS_NET_NETWORKINTERFACE_H
#define FROG_SYS_NET_NETWORKINTERFACE_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <frog/Object.h>
#include <frog/InetAddress.h>


/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * @namespace frog::sys Contains fundamental classes and base classes
	 * that define commonly used value and data types, interfaces,
	 * attributes, and processing exceptions.
	 */
	namespace sys
	{
		/**
		 * @namespace frog::sys::net Provides a simple programming
		 * interface for many of the protocols used on networking
		 * applications.
		 */
		namespace net
		{
			/**
			 * This class represents a network interface made up of a
			 * name, and a list of IP addresses assigned to this
			 * interface. It is used to identify the local interface
			 * on which a multicast group is joined. Interfaces are
			 * normally known by names such as "le0".
			 */
			class NetworkInterface : public Object
			{
			  public:
				  /**
				   * Construct a network interface that has the specified
				   * Internet Protocol (IP) address bound to it. If the
				   * specified IP address is bound to multiple interfaces it
				   * is not defined which network interface is returned.
				   * @param[in] addr The InetAddress to search with.
				   * @return A NetworkInterface
				   */
				  NetworkInterface(const InetAddress& addr);

				  /**
				   * Returns all the interfaces on this machine.
				   * @return A list of NetworkInterface%s on this machine.
				   */
				  static std::vector<NetworkInterface> getNetworkInterfaces() const;

				  /**
				   * Get the name of this network interface.
				   * @return The name of this network interface.
				   */
				  std::string getName() const;

				  /**
				   * Get the display name of this network interface. A display name
				   * is a human-readable string describing the network device.
				   */
				  std::string getDisplayName() const;
			  private:
				  NetworkInterface() { }
			};
		} // net ns
	} // sys ns
} // frog ns
#endif // FROG_SYS_NET_NETWORKINTERFACE_H
