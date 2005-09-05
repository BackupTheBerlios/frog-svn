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


#ifndef FROG_SYS_NET_ENDPOINT_H
#define FROG_SYS_NET_ENDPOINT_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include <frog/Object.h>
#include <frog/AddressFamily.h>

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
		 * Represents a network resource or service without protocol
		 * attachments. This is a class that is meant to be subclassed
		 * with a specific, protocol dependent implementation.
		 *
		 * <HR>
		 *      <H3>Direct Known Subclasses:</H3>
		 *          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		 *              IPEndpoint
		 * <HR>
		 * 
		 */
		class Endpoint : public sys::Object
		{
		  public:
			  /**
			   * Default destructor.
			   */
			  virtual ~Endpoint() throw() { }

			  /**
			   * Address family property of this endpoint. This
			   * address family is a @e read-only attribute.
			   */
			  const AddressFamily::TYPE& addressFamily;
		  protected:
			  /**
			   * Default constructor. The address family is set
			   * to AddressFamily::Unspecified.
			   */
			  Endpoint() : addressFamily(addressFamily_), 
						   addressFamily_(AddressFamily::Unspecified) { }

			  /**
			   * Sets the address family.
			   */
			  void setAddressFamily(AddressFamily::TYPE af)
			  {
				  addressFamily_ = af;
			  }
		  private:
			  AddressFamily::TYPE addressFamily_; /**< The underlying address family */
		}; // Endpoint cls
	} // net ns
} // frog ns

#endif // FROG_SYS_NET_ENDPOINT_H
