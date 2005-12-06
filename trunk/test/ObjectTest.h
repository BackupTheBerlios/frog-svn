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

#include <cstdio>

#include <cppunit/extensions/HelperMacros.h>
#include <frog/Object.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using frog::Object;
using std::string;

class ObjectTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ObjectTest);

    CPPUNIT_TEST(testDisplay);

    CPPUNIT_TEST(testIfSameViaHashCode);
    CPPUNIT_TEST(testIfSameViaToString);
    CPPUNIT_TEST(testIfSameViaSameObject);
    CPPUNIT_TEST(testIfSameViaSameObjectTwoParam);

    CPPUNIT_TEST(testIfNotSameViaHashCode);
    CPPUNIT_TEST(testIfNotSameViaToString);
    CPPUNIT_TEST(testIfNotSameViaSameObject);
    CPPUNIT_TEST(testIfNotSameViaSameObjectTwoParam);

    CPPUNIT_TEST_SUITE_END();

  public:
    void testDisplay()
    {
        Object o;

        ::printf("(%s)\n", o.toString().c_str());

        CPPUNIT_ASSERT(o.sameObject(&o));
        CPPUNIT_ASSERT(Object::sameObject(&o, &o));
    }

    void testIfSameViaHashCode()
    {
        Object o;
        Object* op;

        op = &o;

        ::printf("(%x  %d) (%x  %d)\n", 
                o.hashCode(), o.hashCode(), op->hashCode(), op->hashCode());
        CPPUNIT_ASSERT(op->hashCode() == o.hashCode());
    }

    void testIfSameViaToString()
    {
        Object o;
        Object* op;

        op = &o;

        ::printf("(%s) (%s)\n", o.toString().c_str(), op->toString().c_str());
        CPPUNIT_ASSERT(op->toString() == o.toString());
    }

    void testIfSameViaSameObject()
    {
        Object o;
        Object* op;

        op = &o;

        ::printf("(%s) (%s)\n", o.toString().c_str(), op->toString().c_str());
        CPPUNIT_ASSERT(op->sameObject(&o));
    }

    void testIfSameViaSameObjectTwoParam()
    {
        Object o;
        Object* op;

        op = &o;

        ::printf("(%s) (%s)\n", o.toString().c_str(), op->toString().c_str());
        CPPUNIT_ASSERT(Object::sameObject(&o, op));
    }

    void testIfNotSameViaHashCode()
    {
        Object o;
        Object o2;

        ::printf("(%x  %d) (%x  %d)\n", 
                o.hashCode(), o.hashCode(), o2.hashCode(), o2.hashCode());
        CPPUNIT_ASSERT(o.hashCode() != o2.hashCode());
    }

    void testIfNotSameViaToString()
    {
        Object o;
        Object o2;

        ::printf("(%s) (%s)\n", o.toString().c_str(), o2.toString().c_str());
        CPPUNIT_ASSERT(o.toString() != o2.toString());
    }

    void testIfNotSameViaSameObject()
    {
        Object o;
        Object o2;

        ::printf("(%s) (%s)\n", o.toString().c_str(), o2.toString().c_str());
        CPPUNIT_ASSERT(!o.sameObject(&o2));
    }

    void testIfNotSameViaSameObjectTwoParam()
    {
        Object o;
        Object o2;

        ::printf("(%s) (%s)\n", o.toString().c_str(), o2.toString().c_str());
        CPPUNIT_ASSERT(!Object::sameObject(&o, &o2));
    }
};
