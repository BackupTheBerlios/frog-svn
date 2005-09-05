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


#ifndef FROG_SYS_NET_INETADDRESS_H
#define FROG_SYS_NET_INETADDRESS_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <netinet/in.h>
#include <string>

#include <frog/stdint.h>
#include <frog/Object.h>
#include <frog/AddressFamily.h>
#include <frog/ArgumentOutOfBoundsException.h>
#include <frog/NotImplementedException.h>


/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * @namespace frog::sys::net Provides a simple programming
	 * interface for many of the protocols used on networking
	 * applications.
	 */
	namespace net
	{
		/**
		 * This class represents an Internet Protocol (IP) address.
		 * @note Support for IPv6 is not fully tested.
		 */
		class InetAddress : public sys::Object
		{
		  public:
			  /**
			   * Creates an InetAddress that is undefined. Its address
			   * family is set to AddressFamily::Unspecified.
			   */
			  InetAddress() throw();

			  /**
			   * Copy constructor.
			   */
			  InetAddress(const InetAddress& addr) throw();

			  /**
			   * Creates an InetAddress given the textual representation
			   * of an IP Address.
			   * @param[in] ipAddress A textual representation of an IP address.
			   * @param[in] index The scope id for an IPv6 address. The scope id
			   * referes to an interface on the local system.
			   * @exception frog::sys::IllegalArgumentException Thrown when the
			   * IP address is out of bounds or is not allowed.
			   */
			  InetAddress(const std::string& ipAddress, uint32_t index = 0)
				  throw(sys::IllegalArgumentException);

			  /**
			   * Creates an IPv4 address.
			   * @param[in] ipAddress The raw IP address in @c in_addr format.
			   * @exception frog::sys::ArgumentOutOfBoundsException Thrown when
			   * the IP address is out of range.
			   */
			  InetAddress(const struct in_addr& ipAddress) throw(sys::ArgumentOutOfBoundsException);

#ifdef HAVE_IPV6_SUPPORT
			  /**
			   * Creates an IPv6 address.
			   * @param[in] ipAddress The raw IP address in @c in6_addr format.
			   * @param[in] index The scope id for an IPv6 address. The scope id
			   * referes to an interface on the local system.
			   * @exception frog::sys::ArgumentOutOfBoundsException Thrown when
			   * the IP address is out of range.
			   */
			  InetAddress(const struct in6_addr& ipAddress, uint32_t index = 0) throw(sys::ArgumentOutOfBoundsException);
#endif

			  virtual ~InetAddress() throw() {}

			  /**
			   * Checks if this IP address is a
			   * wildcard addess.
			   * @return Returns @c true if this address
			   * is a wildcard address.
			   */
			  bool isAnyLocalAddress() throw();

			  /**
			   * Checks to see if this is a loopback address.
			   * @return Returns @c true if the address is a
			   * loopback address.
			   */
			  bool isLoopbackAddress() throw();

			  /**
			   * Checks if this is an IP multicast address.
			   * @return Returns @c true if the address is a
			   * multicast address.
			   */
			  bool isMulticastAddress() throw();

			  /**
			   * Checks to see if this is a link local
			   * unicast address.
			   * @return Returns @c true if the address is a
			   * link local unicast address.
			   */
			  bool isLinkLocalAddress() throw();

			  /**
			   * Checks to see if this is a site local
			   * unicast address.
			   * @return Returns @c true if the address is a
			   * site local unicast address.
			   */
			  bool isSiteLocalAddress() throw();

			  /**
			   * Checks to see if this if a multicast address
			   * has global scope.
			   * @return Returns @c true if the multicast address
			   * has a global scope; @c false if is not or if the
			   * address is not a multicast address.
			   */
			  bool isMulticastGlobal() throw();

			  /**
			   * Checks to see if this if a multicast address
			   * has node scope.
			   * @return Returns @c true if the multicast address
			   * has a node-local scope; @c false if it is not or
			   * if the address is not a multicast address.
			   */
			  bool isMulticastNodeLocal() throw();

			  /**
			   * Checks to see if the multicast address
			   * has link scope.
			   * @return Returns @c true if the multicast address
			   * has link-local scope; @c false if it is not or
			   * if the address is not a multicast address.
			   */
			  bool isMulticastLinkLocal() throw();

			  /**
			   * Checks to see if the multicast address
			   * has site-local scope.
			   * @return Returns @c true if the multicast address
			   * has site-local scope; @c false if it is not or
			   * if the address is not a multicast address.
			   */
			  bool isMulticastSiteLocal() throw();

			  /**
			   * Checks to see if the multicast address
			   * has organization scope.
			   * @return Returns @c true if the multicast address
			   * has organization-local scope; @c false if it is not
			   * or if the address is not a multicast address.
			   */
			  bool isMulticastOrgLocal() throw();

			  /**
			   * Gives the raw IPv4 address wrapped in a <TT>struct in_addr</TT>.
			   * @param[out] rawIPAddress The raw IPv4 Address in network byte order.
			   */
			  void getPrimitive(struct in_addr& rawIPAddress) const;

			  /**
			   * Gives the raw IPv6 address wrapped in a <TT>struct in_addr</TT>.
			   * @param[out] rawIPAddress The raw IPv6 Address in network byte order.
			   */
			  void getPrimitive(struct in6_addr& rawIPAddress) const;

			  /**
			   * Returns the IP address in textual presentation.
			   * @return The raw IP address in a string format.
			   */
			  std::string getHostAddress() const throw();

			  /**
			   * Tests for InetAddress equality.
			   */
			  bool operator==(const InetAddress& addr) const throw();

			  /**
			   * Tests for InetAddress inequality.
			   */
			  bool operator!=(const InetAddress& addr) const throw();

			  /**
			   * Copies an InetAddress to another InetAddress.
			   */
			  InetAddress& operator=(const InetAddress& addr) throw();

			  /**
			   * Converts this InetAddress to a string. The string
			   * returned is the same as the return value of 
			   * InetAddress::getHostAddress().
			   * @retval std::string The textual representation
			   * of this InetAddress.
			   */
			  virtual std::string toString() const throw();

			  /**
			   * Gives the address family of the IP address. This is a
			   * @e read-only attribute and can only be assigned during
			   * construction.
			   */
			  const AddressFamily::TYPE& addressFamily;

			  /**
			   * This is set to @e true if the InetAddress is an IPv4-compatible
			   * IPv6 address, or @e false if not. If the InetAddress is already
			   * an IPv4 address, this is set to @e true.
			   */
			  const bool& ipv4Compatible;
		  private:
			  /**
			   * The address family. For InetAddress,
			   * this is either AddressFamily::InterNetwork
			   * or AddressFamily::InterNetworkV6.
			   */
			  AddressFamily::TYPE addressFamily_;

			  /**
			   * This is set to @e true if the InetAddress is an IPv4-compatible
			   * IPv6 address, or @e false if not. If the InetAddress is already
			   * an IPv4 address, this is set to @e true.
			   */
			  bool ipv4Compatible_;

			  /**
			   * Maximum address size. So far max size is only 16
			   * because of IPv6.
			   */
			  static const uint16_t MAX_ADDR_SIZE = 16U;

			  /**
			   * IPv4 address size.
			   */
			  static const uint16_t INADDRSZ = 4U;

#ifdef HAVE_IPV6_SUPPORT
			  /**
			   * IPv6 address size.
			   */
			  static const uint16_t INADDRSZ6 = MAX_ADDR_SIZE;
#endif

			  /**
			   * Address index as seen in <I>ifconfig</I>.
			   */
			  uint32_t index_;

			  /**
			   * Starting offset of the IPv4 address in address_[].
			   */
			  static const uint16_t IPV4_OFFSET = (MAX_ADDR_SIZE - INADDRSZ);

			  /**
			   * The raw IP address. The address is stored in network byte order: the
			   * highest order byte of the address is in address_[0] and address_[12]
			   * for IPv6 and IPv4 respectively. The address is 16 bytes (128 bits) long
			   * so we can handle both IPv4 and IPv6. For IPv4, only the the last 4 bytes
			   * (bottom 32 bits) are used, for IPv6 all 16 bytes are used.
			   */
			  uint8_t address_[MAX_ADDR_SIZE];

			  /**
			   * Initializes the underlying IP address with an IPv4 address.
			   */
			  void initIPv4(const struct in_addr& ipAddress)
				  throw(sys::ArgumentOutOfBoundsException);

#ifdef HAVE_IPV6_SUPPORT
			  /**
			   * Initializes the underlying IP address with an IPv6 address.
			   */
			  void initIPv6(const struct in6_addr& ipAddress, uint32_t index)
				  throw(sys::ArgumentOutOfBoundsException);
#endif
		}; // InetAddress cls
	} // net ns
} // frog ns


#endif // FROG_SYS_NET_INETADDRESS_H
