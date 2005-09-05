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
#include <frog/InetAddress.h>
#include <frog/IPEndpoint.h>
#include <frog/IllegalArgumentException.h>

#include <cstdio>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using frog::net::InetAddress;
using frog::net::IPEndpoint;
using frog::sys::IllegalArgumentException;

class IPEndpointTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(IPEndpointTest);

  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST(testPropertyChange);
  CPPUNIT_TEST(testAddressFamily);
  CPPUNIT_TEST(testAssignment);
  CPPUNIT_TEST(testEquality);
#ifdef HAVE_IPV6_SUPPORT
  CPPUNIT_TEST_FAIL(testEquality1);
#else
  CPPUNIT_TEST_EXCEPTION(testEquality1, frog::sys::IllegalArgumentException);
#endif
  CPPUNIT_TEST_FAIL(testEquality2);
  CPPUNIT_TEST_FAIL(testEquality3);
  CPPUNIT_TEST(testEquality4);
  CPPUNIT_TEST(testInequality);
  CPPUNIT_TEST(testInequality1);
  CPPUNIT_TEST(testInequality2);
  CPPUNIT_TEST_FAIL(testInequality3);
  CPPUNIT_TEST(testToString);
#ifdef HAVE_IPV6_SUPPORT
  CPPUNIT_TEST(testToString2);
#else
  CPPUNIT_TEST_EXCEPTION(testToString2, frog::sys::IllegalArgumentException);
#endif
  
  CPPUNIT_TEST_SUITE_END();

  public:
	  void testConstructor()
	  {
		  in_port_t port = 4444;
		  InetAddress addr("127.0.0.1");
		  IPEndpoint endpoint(addr, port);

		  CPPUNIT_ASSERT(endpoint.address == addr);
		  CPPUNIT_ASSERT(endpoint.address.toString() == addr.toString());
		  CPPUNIT_ASSERT(endpoint.port == port);
		  CPPUNIT_ASSERT(endpoint.addressFamily == addr.addressFamily);
	  }

	  void testPropertyChange()
	  {
		  in_port_t port = 4444;
		  InetAddress addr("127.0.0.1");
		  IPEndpoint endpoint(addr, port);

		  InetAddress addr2("10.1.0.207");
		  in_port_t port2 = 7777;
		  endpoint.address = addr2;
		  endpoint.port = port2;

		  CPPUNIT_ASSERT(!(addr2 == addr));
		  CPPUNIT_ASSERT(!(port2 == port));
		  CPPUNIT_ASSERT(endpoint.address.toString() == addr2.toString());
		  CPPUNIT_ASSERT(endpoint.port == port2);
	  }

	  void testAddressFamily()
	  {
		  InetAddress addr("255.255.255.255");
		  IPEndpoint endpoint(addr, 65535);

		  CPPUNIT_ASSERT(endpoint.address.addressFamily == AddressFamily::InterNetwork);
		  CPPUNIT_ASSERT(endpoint.addressFamily == AddressFamily::InterNetwork);
	  }

	  void testAssignment()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("2.2.2.2");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  endpoint2 = endpoint;

		  CPPUNIT_ASSERT(endpoint == endpoint2);
	  }

	  void testEquality()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("2.2.2.2");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  CPPUNIT_ASSERT(!(endpoint == endpoint2));

	  }

	  void testEquality1()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("::1");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  CPPUNIT_ASSERT(endpoint == endpoint2);
	  }

	  void testEquality2()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("1.1.1.1");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  CPPUNIT_ASSERT(endpoint == endpoint2);
	  }

	  void testEquality3()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("2.2.2.2");
		  IPEndpoint endpoint2(addr2, 1000);
		  
		  CPPUNIT_ASSERT(endpoint == endpoint2);
	  }
	  
	  void testEquality4()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("1.1.1.1");
		  IPEndpoint endpoint2(addr2, 1000);
		  
		  CPPUNIT_ASSERT(endpoint == endpoint2);

	  }

	  void testInequality()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("2.2.2.2");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  CPPUNIT_ASSERT(endpoint != endpoint2);

	  }

	  void testInequality1()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("1.1.1.1");
		  IPEndpoint endpoint2(addr2, 1111);
		  
		  CPPUNIT_ASSERT(endpoint != endpoint2);

	  }

	  void testInequality2()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  InetAddress addr2("2.2.2.2");
		  IPEndpoint endpoint2(addr2, 1000);
		  
		  CPPUNIT_ASSERT(endpoint != endpoint2);

	  }

	  void testInequality3()
	  {
		  InetAddress addr("7.7.7.7");
		  IPEndpoint endpoint(addr, 5555);
		  
		  InetAddress addr2("7.7.7.7");
		  IPEndpoint endpoint2(addr2, 5555);
		  
		  CPPUNIT_ASSERT(endpoint != endpoint2);
	  }

	  void testToString()
	  {
		  InetAddress addr("1.1.1.1");
		  IPEndpoint endpoint(addr, 1000);
		  
		  CPPUNIT_ASSERT(endpoint.toString() == "1.1.1.1:1000");
	  }

	  void testToString2()
	  {
		  InetAddress addr2("::1");
		  IPEndpoint endpoint2(addr2, 1111);

		  CPPUNIT_ASSERT(endpoint2.toString() == "[::1]:1111");
	  }
};
