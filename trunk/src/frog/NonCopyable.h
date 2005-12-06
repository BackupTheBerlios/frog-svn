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

#ifndef FROG_NONCOPYABLE_H
#define FROG_NONCOPYABLE_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

namespace frog
{
    /**
     * Classes derived from class NonCopyable cannot be copied.
     */
    class NonCopyable
    {
      protected:
          NonCopyable() {}
          ~NonCopyable() {}
      private:
          NonCopyable(const NonCopyable&);
          const NonCopyable& operator=(const NonCopyable&);
    }
} // frog ns


#endif // FROG_NONCOPYABLE_H
