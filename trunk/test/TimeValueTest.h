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
#include <iostream>

using std::cout;
using std::endl;

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using frog::util::TimeValue;

class TimeValueTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TimeValueTest);

  CPPUNIT_TEST(testConstructor1);
  CPPUNIT_TEST(testConstructor2);
  CPPUNIT_TEST(testConstructor3);
  CPPUNIT_TEST(testSet1);
  CPPUNIT_TEST(testSet2);
  CPPUNIT_TEST(testSet3);
  CPPUNIT_TEST(testSet4);

  CPPUNIT_TEST_SUITE_END();

  public:
      void testConstructor1()
      {
          TimeValue tv(10, 10);
          CPPUNIT_ASSERT((tv.sec() == 10 && tv.usec() == 10));

          TimeValue tv1(100, 100);
          CPPUNIT_ASSERT((tv1.sec() == 100 && tv1.usec() == 100));

          TimeValue tv2(1000, 1000);
          CPPUNIT_ASSERT((tv2.sec() == 1000 && tv2.usec() == 1000));
      }

      void testConstructor2()
      {
          struct timeval tmval;

          tmval.tv_sec = 100;
          tmval.tv_usec = 100;

          TimeValue tv(tmval);
          TimeValue tv2(100, 100);

          CPPUNIT_ASSERT((tv2.sec() == tmval.tv_sec && tv2.usec() == tmval.tv_usec));
      }

      void testConstructor3()
      {
          struct timespec tmspec;

          tmspec.tv_sec = 100;
          tmspec.tv_nsec = 100;

          TimeValue tv(tmspec);
          TimeValue tv2(100, 100);

          CPPUNIT_ASSERT((tv2.sec() == tmspec.tv_sec && tv2.usec() == tmspec.tv_nsec));
      }

      void testSet1()
      {
          TimeValue tv;
          tv.set(1000);
          CPPUNIT_ASSERT((tv.sec() == 1000 && tv.usec() == 0));
      }

      void testSet2()
      {
          TimeValue tv;
          tv.set(1000, 1);
          CPPUNIT_ASSERT((tv.sec() == 1000 && tv.usec() == 1));
      }

      void testSet3()
      {
          struct timeval tmval;
          TimeValue tv;

          tmval.tv_sec = 100;
          tmval.tv_usec = 100;

          tv.set(tmval);
          CPPUNIT_ASSERT((tv.sec() == tmval.tv_sec && tv.usec() == tmval.tv_usec));
      }

      void testSet4()
      {
          struct timespec tmspec;
          TimeValue tv;

          tmspec.tv_sec = 100;
          tmspec.tv_nsec = 1000;

          tv.set(tmspec);
          CPPUNIT_ASSERT((tv.sec() == tmspec.tv_sec && tv.usec() == (tmspec.tv_nsec/1000)));
      }
};
