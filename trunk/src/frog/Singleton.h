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

#ifndef FROG_SYS_SINGLETON_H
#define FROG_SYS_SINGLETON_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include <frog/RuntimeException.h>
#include <frog/NullPointerException.h>

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
		 * A template class for creating single-instance global classes.
		 * A singleton is an object that has only one instance in a system
		 * at any time. This template class is meant to be derived from.
		 *
		 * To convert any class into a singleton, the following steps should
		 * be followed:
		 *
		 * 		-# Publicly derive you class @c MyClass from @c Singleton<MyClass>.
		 * 		-# Declare <TT>template<> MyClass* Singleton<MyClass>::singleton_ = 0</TT>
		 * 		in the class that derives from @c Singleton.
		 * 		-# Make sure that you're constructing an instance of @c MyClass
		 * 		somewhere in the system before using it. How you instantiate it
		 * 		does not matter. You can let the compiler worry about it by making
		 * 		it a global or local static, or you can worry about it yourself via
		 * 		@c new and @c delete through an owner class. Regardless of how and
		 * 		when you construct the instance, it will get tracked and may be used
		 * 		as a singleton through common interfaces by the rest of the system.
		 * 		-# Call @c MyClass::getSingleton() to use the object from anywhere
		 * 		in the system. You can also <TT>\#define gMyClass</TT> to be
		 * 		@c MyClass::getSingleton() and treat it exactly like a global object
		 * 		for notational convenience.
		 *
		 * 		An example is given below:
		 *
		 * <TT>
		 * @code
		 * 		class MyClass : public Singleton<MyClass>
		 * 		{
		 * 		  public:
		 * 		  		MyClass* getSomething(const char* name);
		 * 		};
		 *
		 * 		#define gMyClass MyClass::getSingleton()
		 * 		template<> MyClass* Singleton<MyClass>::singleton = 0;
		 *
		 * 		void SomeFunction()
		 * 		{
		 * 				SomeClass* one = MyClass::getSingleton().getSomeClass("XX");
		 * 				SomeClass* two = gMyClass.getSomeClass("YY");
		 * 		}
		 * @endcode
		 * </TT>
		 * @note This Singleton is based from the work of Scott Bilas <scottb@drizzle.com>.
		 */
		template <typename T>
			class Singleton
			{
			  public:
				  /**
				   * The template constructor.
				   * @exception frog::sys::RuntimeException Thrown whenever there are
				   * attempts to construct the object while there is still a valid
				   * instance of it.
				   */
				  Singleton()
				  {
					  if(this->singleton_)
						  throw RuntimeException(std::string(__PRETTY_FUNCTION__) + 
								  ": There is already an existing instance of this object.");
					  singleton_ = static_cast<T*>( this );
				  }

				  /*
				   *
				   */
				  ~Singleton()
				  {
					  if(this->singleton_)
						  this->singleton_ = 0;
				  }

				  /**
				   * Obtain a reference to the singleton instance.
				   * @return A reference to the object.
				   * @exception frog::sys::NullPointerException Thrown when attempting
				   * to get a reference when there is none.
				   */
				  static T& getSingleton()
				  {
					  if(!singleton_)
						  throw NullPointerException(std::string(__PRETTY_FUNCTION__) + 
								  ": Attempting to reference a non-existent object.");
					  return *singleton_;
				  }

				  /**
				   * Obtain a pointer to the singleton instance.
				   * @return A reference to the object.
				   * @exception frog::sys::NullPointerException Returned when attempting
				   * to get a reference when there is none.
				   */
				  static T* getSingletonPtr()
				  {
					  if(!singleton_)
						  throw NullPointerException(std::string(__PRETTY_FUNCTION__) + 
								  ": Attempting to reference a non-existent object.");
					  return singleton_;
				  }

			  protected:
				  static T* singleton_; /**< The object wrapped by this Singleton class. */
			}; // Singleton tmpl
	} //ns sys
} // ns frog

#endif // FROG_SYS_SINGLETON_H
