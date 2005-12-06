// C++ test file ---------------------------------------------------------//
//   Copyright (C) 2005 by Janvier D. Anonical <janvier@gmail.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU Library General Public License as
//   published by the Free Software Foundation; either version 2 of the
//   License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU Library General Public
//   License along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//   This file is part of the Frog Framework.
//------------------------------------------------------------------------//

#include <cppunit/extensions/HelperMacros.h>
#include <frog/TimeValue.h>

#include <cstdio>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

class TimeValueTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TimeValueTest);

    CPPUNIT_TEST(testConstructor1);

    CPPUNIT_TEST_SUITE_END();
    public:
        void testConstructor1()
        {
            TimeValue tv(10, 10);
            CPPUNIT_ASSERT(tv.sec() == 10 && tv.usec == 10);
            TimeValue tv1(100, 100);
            CPPUNIT_ASSERT(tv1.sec() == 100 && tv1.usec == 100);
            TimeValue tv2(1000, 1000);
            CPPUNIT_ASSERT(tv2.sec() == 1000 && tv2.usec == 1000);
        }
};
