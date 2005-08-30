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


#ifndef FROG_SYS_OBJECT_H
#define FROG_SYS_OBJECT_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDINT_H
#include <stdint.h>
#else
#include <frog/stdint.h>
#endif

#include <string>

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
		 * The class Object is root of the class hierarchy. Every class
		 * in this framework has Object as its ultimate base class.
		 */
		class Object
		{
		  public:
			  /**
			   * Initializes a new instance of the Object class.
			   */
			  Object() throw();
			  virtual ~Object() throw();

			  /**
			   * Returns a 32-bit hash code for the object. This returns
			   * distinct integers for distinct objects. This is typically
			   * implemented by converting the internal address of an object
			   * into an integer, but this implementation technique is not
			   * required. Note that two objects are "the same" if their
			   * hash codes are equal.
			   */
			  virtual uint32_t hashCode() const throw();

			  /**
			   * Indicates whether some other object is the same as
			   * this one. The term "same object" means both objects
			   * have the same hash code. Note that it is necessary
			   * to override the hashCode() function whenever this
			   * function is overriden, so as to maintain the general
			   * contract for the hashCode() function, which states that
			   * two objects are the same if their hash codes are equal.
			   * @param[in] obj The object with which to compare.
			   * @return Returns @e true if this object is the same as
			   * the @arg obj argument; @e false otherwise.
			   */
			  virtual bool sameObject(const Object* obj) const throw();

			  /**
			   * Indicates whether some other object is the same as
			   * another object. The term "same object" means both objects
			   * have the same hash code. These objects are considered
			   * "the same" if their hash codes are equal.
			   * @param[in] objA The first object to compare.
			   * @param[in] objB The second object to compare.
			   * @return Returns @e true if @arg objA is the same as
			   * the @arg objB and vice-versa; @e false otherwise.
			   */
			  static bool sameObject(const Object* objA, const Object* objB) throw();
			  
			  /**
			   * Returns the textual representation of the current object. In
			   * general, the toString function returns a string that
			   * "textually represent" the object. The result should be a
			   * concise but informative representation that is easy for a person
			   * to read. It is recommended that all subclasses override this
			   * method otherwise it can be misleading if this function is called
			   * on a sublcass of Object.
			   */
			  virtual std::string toString() const throw();
		  private:
			  uint32_t hash_;
		}; // Object cls
	} // sys ns
} // frog ns

#endif // FROG_SYS_OBJECT_H
