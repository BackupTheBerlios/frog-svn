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


#ifndef FROG_SYS_EXCEPTION_H
#define FROG_SYS_EXCEPTION_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <frog/Object.h>

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
         * This class and its subclasses indicate conditions
         * that a reasonable application might want to catch.
         *
         * This class is the base class of all exceptions in this
         * framework. Please note that exceptions that are subclasses
         * of <TT>std::exception</TT> will not be catched by the
         * Exception class.
         *
         * Errors or unexpected conditions are reported by an
         * application using exceptions. Exceptions are thrown and
         * applications willing to handle the exception should
         * <TT>catch</TT> the thrown exception via <TT>catch</TT>
         * clause. Generally, exceptions propagate until a handler
         * is found. If no handler is found, it will be reported as
         * an unhandled exception by the system. To catch all
         * exceptions users should add the <I>catch all</I>
         * <TT>catch(...)</TT> clause in their exception handler.
         *
         * This class is inherited by two types:
         * <UL>
         *    <LI>SystemException</LI>
         *    <LI>ApplicationException</LI>
         * </UL>
         *
         * Most user-defined exceptions should derive from
         * ApplicationException. SystemException is used by the
         * framework.
         *
         * @sa SystemException, ApplicationException
         *
         * <HR>
         * <H3>Direct Known Subclasses:</H3>
         *     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
         *     SystemException, ApplicationException
         * <HR>
         */
        class Exception : public Object
        {
          public:
              /**
               * Constructs a new exception.
               */
              explicit Exception() throw()
                  : description_("Exception") {}

              /**
               * Constructs a new exception with the specified description.
               * @param[in] description The description of this exception
               */
              explicit Exception(const std::string& description) throw()
                  : description_(description) {}

              /**
               * Constructs a new exception with the specified description.
               * @param[in] description The description of this exception
               */
              explicit Exception(const char* description) throw()
                  : description_(std::string(description)) {}

              /**
               * Does nothing.
               */
              virtual ~Exception() throw() {}

              /**
               * Get the description of this exception.
               * @return A string that contains the description of this exception.
               */
              virtual const char* getDescription() const throw()
              {
                  return description_.c_str();
              }

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
                  return std::string("frog::sys::Exception") + ": " +
                      std::string(getDescription());
              }
          private:
              std::string description_;
        }; // Exception cls
    } // sys ns
} // frog ns

#endif // FROG_SYS_EXCEPTION_H
