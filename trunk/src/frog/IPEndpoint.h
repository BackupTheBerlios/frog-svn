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


#ifndef FROG_SYS_NET_IPENDPOINT_H
#define FROG_SYS_NET_IPENDPOINT_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdint.h>
#include <netinet/in.h>

#include <string>

#include <frog/Endpoint.h>
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
			 * Implements a network endpoint that is an
			 * IP socket address (IP address + port).
			 * <HR>
			 * <H3>Inherits from:</H3>
			 *     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			 *     Endpoint
			 * <HR>
			 */
			class IPEndpoint : public Endpoint
			{
			  public:
				  /**
				   * Constructs an IP endpoint from an IP address and port.
				   */
				  IPEndpoint(InetAddress& ipAddress, in_port_t portNo) throw();

				  /**
				   * Copies an IP endpoint to another IP endpoint.
				   */
				  IPEndpoint& operator=(const IPEndpoint& ep) throw();
				 
				  /**
				   * Default destructor.
				   */
				  virtual ~IPEndpoint() throw() { }
				  
				  /**
				   * Tests for IP endpoint equality.
				   */
				  bool operator==(const IPEndpoint& ep) const throw();
				  
				  /**
				   * Tests for IP endpoint inequality.
				   */
				  bool operator!=(const IPEndpoint& ep) const throw();

				  /**
				   * Converts this IPEndpoint to its textual representation.
				   * IPv4 Endpoints are represented as <I>ipv4-address:port</I> while
				   * IPv6 Endpoints are respresented as <I>[ipv6-address\%scope-id]:port</I>.
				   * The <I>scope-id</I> for IPv6 appears only if it was set in during
				   * InetAddress construction.
				   * @retval std::string The textual representation
				   * of this IPEndpoint.
				   */
				  virtual std::string toString() const throw();
				  
				  /**
				   * IP address of this endpoint. The address is a
				   * @e read-write attribute.
				   */
				  InetAddress address;

				  /**
				   * The port number of this endpoint. The port is a
				   * @e read-write attribute.
				   */
				  in_port_t port;
			  private:
				  /**
				   * Default constructor.
				   */
				  IPEndpoint() throw();
			}; // IPEndpoint cls
		}  // net ns
	} // sys ns
}  // frog ns

#endif // FROG_SYS_NET_IPENDPOINT_H
