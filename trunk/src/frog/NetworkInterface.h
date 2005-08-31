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


#ifndef FROG_SYS_NET_NETWORKINTERFACE_H
#define FROG_SYS_NET_NETWORKINTERFACE_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <vector>

#include <frog/Object.h>
#include <frog/InetAddress.h>
#include <frog/SocketException.h>


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
				   * Container for the unicast, netmask, and broadcast addresses
				   * found by NetworkInterface.
				   */
				  class InterfaceAddress
				  {
					public:
					  InetAddress unicast; /**< Unicast address */
					  InetAddress netmask; /**< Netmask address */
					  InetAddress broadcast; /**< Broadcast address */
					  uint32_t index; /**< Address index */

					  /**
					   * Provided here to satisfy STL.
					   */
					  bool operator==(const InterfaceAddress& other) const throw();

					  /**
					   * Provided here to satisfy STL.
					   */
					  bool operator!=(const InterfaceAddress& other) const throw();
				  };

				  /**
				   * Type of InterfaceAddress list.
				   */
				  typedef std::vector<InterfaceAddress> InterfaceAddrList;

				  /**
				   * Iterator for InterfaceAddrList.
				   */
				  typedef std::vector<InterfaceAddress>::iterator InterfaceAddrListIterator;

				  /**
				   * Constant iterator for InterfaceAddrList.
				   */
				  typedef std::vector<InterfaceAddress>::const_iterator InterfaceAddrListConstIterator;

				  /**
				   * Get the name of this network interface.
				   */
				  const std::string& name;

				  /**
				   * Get the display name of this network interface. A display name
				   * is a human-readable string describing the network device.
				   */
				  const std::string& displayName;

				  /**
				   * Construct a network interface that has the specified
				   * Internet Protocol (IP) address bound to it. If the
				   * specified IP address is bound to multiple interfaces it
				   * is not defined which network interface is returned.
				   * @param[in] addr The InetAddress to search with.
				   * @return A NetworkInterface
				   * @exception frog::sys::net::SocketException I/O error occurred.
				   */
				  static NetworkInterface getByInetAddress(const InetAddress& addr)
					  throw(SocketException);
				  
				  /**
				   * Searches for the network interface with the specified name.
				   */
				  static NetworkInterface getByName(const std::string& intfaceName)
					  throw(SocketException);

				  /**
				   * Default destructor.
				   */
				  ~NetworkInterface() throw();

				  /**
				   * Copy constructor.
				   */
				  NetworkInterface(const NetworkInterface& netInterface) throw();

				  /**
				   * Copies one network interface to another.
				   */
				  NetworkInterface& operator=(const NetworkInterface& netInterface) throw();

				  /**
				   * Compares two network interfaces.
				   */
				  bool operator==(const NetworkInterface& netInterface) const throw();

				  /**
				   * Tests for network interface inequality.
				   */
				  bool operator!=(const NetworkInterface& netInterface) const throw();

				  /**
				   * Returns all the interfaces on this machine.
				   * @return A list of NetworkInterface%s on this machine.
				   */
				  static std::vector<NetworkInterface> getNetworkInterfaces();

				  /**
				   * Returns all the IP addresses bound to this network interface.
				   * These includes the unicast, netmask, and broadcast addresses
				   * if available.
				   */
				  NetworkInterface::InterfaceAddrList getInterfaceAddresses() const;

				  /**
				   * Returns the string representation of this object.
				   */
				  std::string toString() const throw();
			  private:
				  /**
				   * Default do nothing constructor.
				   */
				  NetworkInterface() : name(name_), displayName(displayName_) { }

				  /**
				   * Finds the network interface associated with either the
				   * IP address or the interface name.
				   */
				  static NetworkInterface find(const InetAddress* addr,
						  const std::string name = "") throw(SocketException);

				  /**
				   * Finds all the network interfaces in this machine.
				   */
				  static std::vector<NetworkInterface> findAll() throw(SocketException);


				  /**
				   * Interface name
				   */
				  std::string name_;

				  /**
				   * Interface display name
				   */
				  std::string displayName_;


				  /**
				   * InetAddress(es) assigned to this interface.
				   */
				  InterfaceAddrList addressList_;
			};
		} // net ns
	} // sys ns
} // frog ns
#endif // FROG_SYS_NET_NETWORKINTERFACE_H
