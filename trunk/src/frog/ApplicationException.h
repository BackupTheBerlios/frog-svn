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


#ifndef FROG_SYS_APPLICATIONEXCEPTION_H
#define FROG_SYS_APPLICATIONEXCEPTION_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <frog/Exception.h>

/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * @namespace frog::sys Contains fundamental classes and base classes that
	 * define commonly used value and data types, interfaces, attributes,
	 * and processing exceptions.
	 */
	namespace sys
	{
		/**
		 * This is the base class for all exceptions defined by applications.
		 *
		 * This class represents application-defined errors detected during the
		 * execution of an application. It is provided as a means to
		 * differentiate between exceptions defined by applications versus
		 * exceptions defined by the framework.
		 *
		 * @sa SystemException
		 *
		 * <HR>
		 * <H3>Inherits from:</H3>
		 *     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		 *     Exception
		 * <HR>
		 */
		class ApplicationException : public Exception
		{
		  public:
			  /**
			   * Constructs a new exception.
			   */
			  explicit ApplicationException() throw()
				  : Exception("ApplicationException") {}

			  /**
			   * Constructs a new exception with the specified description.
			   * @param[in] description The description of this exception
			   */
			  explicit ApplicationException(const std::string& description) throw()
				  : Exception(description) {}

			  /**
			   * Constructs a new exception with the specified description.
			   * @param[in] description The description of this exception
			   */
			  explicit ApplicationException(const char* description) throw()
				  : Exception(description) {}
			  /**
			   * Does nothing.
			   */
			  virtual ~ApplicationException() throw() {}

			  /**
			   * Returns the textual representation of the current object. In
			   * general, the toString function returns a string that
			   * "textually represent" the object. The result should be a
			   * concise but informative representation that is easy for a person
			   * to read. It is recommended that all subclasses override this
			   * method otherwise it can be misleading if this function is called
			   * on a sublcass of Object.
			   */
			  virtual std::string toString() const throw()
			  {
				  return std::string("frog::sys::ApplicationException") + ": " +
					std::string(getDescription());  
			  }
		}; // ApplicationException cls
	} // sys ns
} // frog ns

#endif // FROG_SYS_APPLICATIONEXCEPTION_H
