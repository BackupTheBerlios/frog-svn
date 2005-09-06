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

#include <sys/types.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>


#include <cppunit/extensions/HelperMacros.h>
#include <frog/InetAddress.h>
#include <frog/NotImplementedException.h>
#include <frog/IllegalArgumentException.h>
#include <frog/ArgumentOutOfBoundsException.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using frog::net::InetAddress;
using namespace std;

class Inet6AddressTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(Inet6AddressTest);
 
  // IPv6 tests 
  CPPUNIT_TEST(testConstructor1);
  CPPUNIT_TEST(testConstructor2);
  CPPUNIT_TEST(testConstructor3);
  CPPUNIT_TEST(testCopyConstructor);
  
  CPPUNIT_TEST_EXCEPTION(testConstructorException1, frog::sys::IllegalArgumentException);
  CPPUNIT_TEST_EXCEPTION(testConstructorException2, frog::sys::IllegalArgumentException);
  CPPUNIT_TEST_EXCEPTION(testConstructorException3, frog::sys::IllegalArgumentException);
  CPPUNIT_TEST_EXCEPTION(testConstructorException4, frog::sys::IllegalArgumentException);
  CPPUNIT_TEST_EXCEPTION(testConstructorException5, frog::sys::IllegalArgumentException);
  CPPUNIT_TEST_EXCEPTION(testConstructorException6, frog::sys::IllegalArgumentException);
  
  CPPUNIT_TEST(testAnyLocal);
  CPPUNIT_TEST(testAnyLocal2);
  CPPUNIT_TEST(testLoopback);
  CPPUNIT_TEST(testLoopback2);
  CPPUNIT_TEST(testMulticast);
  
  CPPUNIT_TEST(testEquality1);
  CPPUNIT_TEST(testEquality2);
  CPPUNIT_TEST(testEquality3);
  CPPUNIT_TEST_FAIL(testInequality1);
  CPPUNIT_TEST(testInequality2);
  CPPUNIT_TEST_FAIL(testInequality3);
  CPPUNIT_TEST(testInequality4);

  CPPUNIT_TEST(testAssignment1);
  CPPUNIT_TEST(testAssignment2);
  CPPUNIT_TEST(testAssignmentCascade);

  CPPUNIT_TEST(testToString);
  CPPUNIT_TEST(testGetAddress);
  
  CPPUNIT_TEST(testGetLocalHost);

  CPPUNIT_TEST(testIPv4MappedEquality);
  CPPUNIT_TEST(testIPv4CompatEquality);

  CPPUNIT_TEST_FAIL(testCompareIPv4Compat);
  CPPUNIT_TEST_FAIL(testCompareIPv4Compat2);
  CPPUNIT_TEST(testCompareIPv4Compat3);
  CPPUNIT_TEST(testCompareIPv4Compat4);

  CPPUNIT_TEST(testIPv4Compat);

  CPPUNIT_TEST_SUITE_END();

  public:
	void setUp()
	{
		memset(&rawAddr_, 0, sizeof(struct in_addr));
	}

	void testConstructor1()
	{
		InetAddress addr("1080:0:0:0:8:800:200C:417A");
		CPPUNIT_ASSERT(addr.addressFamily == AddressFamily::InterNetworkV6);
	}
	
	void testConstructor2()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200C:417A", &rawAddr_);
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.addressFamily == AddressFamily::InterNetworkV6);
	}
	
	void testConstructor3()
	{
		inet_pton(AF_INET6, "1080::8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.addressFamily == AddressFamily::InterNetworkV6);
	}
		
	void testConstructorException1()
	{
		InetAddress addr("1080:0:0:0:8:800:200c:417a:ggg");
	}
	
	void testConstructorException2()
	{
		InetAddress addr(":::::::::::");
	}
	
	void testConstructorException3()
	{
		InetAddress addr("ghyi:f:56:0rtt:8h:8zz:zzzc:417a");
	}
	
	void testConstructorException4()
	{
		InetAddress addr("asdfgrert");
	}
	
	void testConstructorException5()
	{
		InetAddress addr("g:g:g:g:g:g:g:g");
	}
	
	void testConstructorException6()
	{
		InetAddress addr("1080:0:0:0:8:800:200c:417z");
	}
	
	void testAnyLocal()
	{
		memset(&rawAddr_, 0, sizeof(struct in_addr));
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.isAnyLocalAddress());
		CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
		CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
		CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
		CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
	}
	
	void testAnyLocal2()
	{
		InetAddress addr("::");
		CPPUNIT_ASSERT(addr.isAnyLocalAddress());
		CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
		CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
	}

	void testLoopback()
	{
		inet_pton(AF_INET6, "::1", &rawAddr_);
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.isLoopbackAddress());
		CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
		CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
	}
	
	void testLoopback2()
	{
		inet_pton(AF_INET6, "0:0:0:0:0:0:0:1", &rawAddr_);
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.isLoopbackAddress());
		CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
		CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
	}

	void testMulticast()
	{
		inet_pton(AF_INET6, "ff01:0:0:0:0:0:0:43", &rawAddr_);
		InetAddress addr(rawAddr_);
		CPPUNIT_ASSERT(addr.isMulticastAddress());
		CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
		CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
	}

	void testEquality1()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		InetAddress addr2(rawAddr_);
		CPPUNIT_ASSERT(addr == addr2);
	}
	
	void testEquality2()
	{
		InetAddress addr("1080:0:0:0:8:800:200c:417a");
		InetAddress addr2("1080:0:0:0:8:800:200c:417a");
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testEquality3()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		InetAddress addr2("1080:0:0:0:8:800:200c:417a");
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testInequality1()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		inet_pton(AF_INET6, "10a0:0:0:0:8:800:100a:417a", &rawAddr_);
		InetAddress addr2(rawAddr_);
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testInequality2()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		inet_pton(AF_INET6, "10a0:0:0:0:8:800:100a:417a", &rawAddr_);
		InetAddress addr2(rawAddr_);
		CPPUNIT_ASSERT(addr != addr2);
	}

	void testInequality3()
	{
		inet_pton(AF_INET6, "1080:0:0:0:8:800:200c:417a", &rawAddr_);
		InetAddress addr(rawAddr_);
		InetAddress addr2("10a0:0:0:0:8:800:100a:417a");
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testInequality4()
	{
		inet_pton(AF_INET6, "::1", &rawAddr_);
		InetAddress addr(rawAddr_);
		InetAddress addr2("10a0:0:0:0:8:800:100a:417a");
		CPPUNIT_ASSERT(addr != addr2);
	}

	void testAssignment1()
	{
		InetAddress addr("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff");
		InetAddress addr2 = addr;
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testAssignment2()
	{
		InetAddress addr("0:0:0:0:0:0:0:1");
		InetAddress addr2("1:1:1:1:1:1:1:1");

		addr2 = addr;
		
		CPPUNIT_ASSERT(addr == addr2);
	}

	void testAssignmentCascade()
	{
		InetAddress addr("0:0:0:0:0:0:0:1");
		InetAddress addr2("1:1:1:1:1:1:1:1");
		InetAddress addr3("2:2:2:2:2:2:2:2");

		addr3 = addr2 = addr;
		
		CPPUNIT_ASSERT(addr == addr2);
		CPPUNIT_ASSERT(addr2 == addr3);
		CPPUNIT_ASSERT(addr == addr3);
	}

	void testCopyConstructor()
	{
		InetAddress addr("0:0:0:0:0:0:0:1");
		someFn(addr, addr);
	}

	void testToString()
	{
		InetAddress addr("ff01::43");
		std::string s = "ff01::43";
		std::string s2 = "1:1:1:1:1:1:1:1";

		CPPUNIT_ASSERT(s == addr.toString());
		CPPUNIT_ASSERT(!(s2 == addr.toString()));
		CPPUNIT_ASSERT(!strcmp(s.c_str(), addr.toString().c_str()));
		CPPUNIT_ASSERT(!strcmp("ff01::43", addr.toString().c_str()));

		CPPUNIT_ASSERT(s == addr.getHostAddress());
		CPPUNIT_ASSERT(!(s2 == addr.getHostAddress()));
		CPPUNIT_ASSERT(!strcmp(s.c_str(), addr.getHostAddress().c_str()));
		CPPUNIT_ASSERT(!strcmp("ff01::43", addr.getHostAddress().c_str()));
	}

	void testGetAddress()
	{
		char dst[INET6_ADDRSTRLEN];
		memset(&rawAddr_, 0, sizeof(struct in6_addr));
		std::string dstAddr = "";
		
		InetAddress addr("::1");
		addr.getPrimitive(rawAddr_);

		memset(dst, 0, sizeof(char) * INET6_ADDRSTRLEN);
		if((inet_ntop(AF_INET6, &rawAddr_,
						dst, sizeof(char) * INET6_ADDRSTRLEN) != NULL) && (dst != NULL))
		{
			dstAddr = std::string(dst);
		}

		CPPUNIT_ASSERT(addr.toString() == dstAddr);
		CPPUNIT_ASSERT(addr.getHostAddress() == dstAddr);
	}

	void testGetLocalHost()
	{
		InetAddress localHost;
		localHost = InetAddress::getLocalHost();

		cout << endl << "toString: " << localHost.toString() << endl;

		CPPUNIT_ASSERT(!localHost.isLoopbackAddress());
	}

	void testIPv4MappedEquality()
	{
		InetAddress addr("::ffff:10.1.0.1");
		InetAddress addr2("::ffff:0a01:0001");

		CPPUNIT_ASSERT(addr == addr2);
	}

	void testIPv4CompatEquality()
	{
		InetAddress addr("::10.9.8.7");
		InetAddress addr2("::0a09:0807");

		CPPUNIT_ASSERT(addr == addr2);
	}

	void testCompareIPv4Compat()
	{
		InetAddress addr("10.9.8.7");
		InetAddress addr2("::10.9.8.7");
		CPPUNIT_ASSERT(addr == addr2);
	}
	
	void testCompareIPv4Compat2()
	{
		InetAddress addr("10.9.8.7");
		InetAddress addr2("::0a09:0807");
		CPPUNIT_ASSERT(addr == addr2);
	}
	
	void testCompareIPv4Compat3()
	{
		InetAddress addr("10.9.8.7");
		InetAddress addr2("::10.9.8.7");
		CPPUNIT_ASSERT(addr != addr2);
	}
	
	void testCompareIPv4Compat4()
	{
		InetAddress addr("10.9.8.7");
		InetAddress addr2("::0a09:0807");
		CPPUNIT_ASSERT(addr != addr2);
	}

	void testIPv4Compat()
	{
		InetAddress addr("10.9.8.7");
		InetAddress addr2("::0a09:0807");
		InetAddress addr3("::10.9.8.7");

		CPPUNIT_ASSERT(addr.ipv4Compatible);
		CPPUNIT_ASSERT(addr2.ipv4Compatible);
		CPPUNIT_ASSERT(addr3.ipv4Compatible);
	}
  private:
	struct in6_addr rawAddr_;
	void someFn(const InetAddress& addr1, InetAddress addr2)
	{
		CPPUNIT_ASSERT(addr1 == addr2);
	}
};
