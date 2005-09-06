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


#ifndef FROG_SYS_NULLPTR_H
#define FROG_SYS_NULLPTR_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * A null-pointer type.
	 *
	 * @note Adapted from Item 25 of <I>Effective C++</I> by Scott Meyers.
	 */
	const class
	{
	  public:
		  /**
		   * Used to convert to any type of null non-member pointer. 
		   */
		  template<typename T> operator T*() const { return 0; }

		  /**
		   * Used to convert to any type of null member pointer.
		   */
		  template<typename C, typename T> operator T C::*() const { return 0; }
	  private:
		  /**
		   * Address cannot be taken.
		   */
		  void operator&() const;
	} nullptr = {};
} // frog ns

#endif // FROG_SYS_NULLPTR_H
