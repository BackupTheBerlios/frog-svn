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

#include <string>
#include <cstdio>
#include <iostream>

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


class Inet4AddressTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(Inet4AddressTest);

    // IPv4 tests 
    CPPUNIT_TEST(testConstructor1);
    CPPUNIT_TEST(testConstructor2);
    CPPUNIT_TEST(testCopyConstructor);

    CPPUNIT_TEST_EXCEPTION(testConstructorException1, frog::sys::IllegalArgumentException);
    CPPUNIT_TEST_EXCEPTION(testConstructorException2, frog::sys::IllegalArgumentException);
    CPPUNIT_TEST_EXCEPTION(testConstructorException3, frog::sys::IllegalArgumentException);
    CPPUNIT_TEST_EXCEPTION(testConstructorException4, frog::sys::IllegalArgumentException);
    CPPUNIT_TEST_EXCEPTION(testConstructorException5, frog::sys::IllegalArgumentException);
    CPPUNIT_TEST_EXCEPTION(testConstructorException6, frog::sys::IllegalArgumentException);

    CPPUNIT_TEST(testAnyLocal);
    CPPUNIT_TEST(testLoopback);
    CPPUNIT_TEST(testMulticast);
    CPPUNIT_TEST(testLinkLocal);
    CPPUNIT_TEST(testSiteLocal10);
    CPPUNIT_TEST(testSiteLocal172);
    CPPUNIT_TEST(testSiteLocal192);
    CPPUNIT_TEST(testMulticastGlobalMin);
    CPPUNIT_TEST(testMulticastGlobalMax);
    CPPUNIT_TEST(testMulticastLinkLocal);
    CPPUNIT_TEST(testMulticastSiteLocal);
    CPPUNIT_TEST(testMulticastOrgLocalMin);
    CPPUNIT_TEST(testMulticastOrgLocalMax);
    CPPUNIT_TEST_FAIL(testMulticastNodeLocal);

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

    CPPUNIT_TEST(testIfSame);
    CPPUNIT_TEST_FAIL(testIfNotSame);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp()
    {
        memset(&rawAddr_, 0, sizeof(struct in_addr));
    }

    void testConstructor1()
    {
        InetAddress addr("10.1.0.1");
        CPPUNIT_ASSERT(addr.addressFamily == AddressFamily::InterNetwork);
    }

    void testConstructor2()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.1", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.1")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.addressFamily == AddressFamily::InterNetwork);
    }

    void testConstructorException1()
    {
        InetAddress addr("10.1.0.1.x");
    }

    void testConstructorException2()
    {
        InetAddress addr("...");
    }

    void testConstructorException3()
    {
        InetAddress addr("z.x.c.v");
    }

    void testConstructorException4()
    {
        InetAddress addr("zxcv");
    }

    void testConstructorException5()
    {
        InetAddress addr("333.333.333.333");
    }

    void testConstructorException6()
    {
        InetAddress addr("255.255.255.256");
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

    void testLoopback()
    {
#ifdef HAVE_INET_ATON
        inet_aton("127.0.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("127.0.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isLoopbackAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
    }

    void testMulticast()
    {
#ifdef HAVE_INET_ATON
        inet_aton("224.0.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("224.0.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
    }

    void testLinkLocal()
    {
#ifdef HAVE_INET_ATON
        inet_aton("169.254.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("169.254.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isLinkLocalAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
    }

    void testSiteLocal10()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.254.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.254.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isSiteLocalAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testSiteLocal172()
    {
#ifdef HAVE_INET_ATON
        inet_aton("172.16.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("172.16.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isSiteLocalAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testSiteLocal192()
    {
#ifdef HAVE_INET_ATON
        inet_aton("192.168.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("192.168.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isSiteLocalAddress());
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isMulticastAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastGlobalMin()
    {
#ifdef HAVE_INET_ATON
        inet_aton("224.0.1.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("224.0.1.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastGlobal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastGlobalMax()
    {
#ifdef HAVE_INET_ATON
        inet_aton("238.255.255.255", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("238.255.255.255")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastGlobal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastNodeLocal()
    {
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastNodeLocal());
    }

    void testMulticastLinkLocal()
    {
#ifdef HAVE_INET_ATON
        inet_aton("224.0.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("224.0.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastLinkLocal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isMulticastGlobal()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastSiteLocal()
    {
#ifdef HAVE_INET_ATON
        inet_aton("239.255.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("239.255.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastSiteLocal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isMulticastGlobal()));
        CPPUNIT_ASSERT(!(addr.isMulticastLinkLocal()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastOrgLocalMin()
    {
#ifdef HAVE_INET_ATON
        inet_aton("239.192.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("239.192.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastOrgLocal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isMulticastGlobal()));
        CPPUNIT_ASSERT(!(addr.isMulticastLinkLocal()));
        CPPUNIT_ASSERT(!(addr.isMulticastSiteLocal()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testMulticastOrgLocalMax()
    {
#ifdef HAVE_INET_ATON
        inet_aton("239.195.0.0", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("239.195.0.0")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        CPPUNIT_ASSERT(addr.isMulticastOrgLocal());
        CPPUNIT_ASSERT(addr.isMulticastAddress());
        CPPUNIT_ASSERT(!(addr.isMulticastGlobal()));
        CPPUNIT_ASSERT(!(addr.isMulticastLinkLocal()));
        CPPUNIT_ASSERT(!(addr.isMulticastSiteLocal()));
        CPPUNIT_ASSERT(!(addr.isSiteLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isAnyLocalAddress()));
        CPPUNIT_ASSERT(!(addr.isLoopbackAddress()));
        CPPUNIT_ASSERT(!(addr.isLinkLocalAddress()));
    }

    void testEquality1()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        InetAddress addr2(rawAddr_);
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testEquality2()
    {
        InetAddress addr("10.1.0.158");
        InetAddress addr2("10.1.0.158");
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testEquality3()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.159", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.159")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        InetAddress addr2("10.1.0.159");
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testInequality1()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
#ifdef HAVE_INET_ATON
        inet_aton("202.8.42.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("202.8.42.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr2(rawAddr_);
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testInequality2()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
#ifdef HAVE_INET_ATON
        inet_aton("202.8.42.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("202.8.42.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr2(rawAddr_);
        CPPUNIT_ASSERT(addr != addr2);
    }

    void testInequality3()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        InetAddress addr2("202.8.42.157");
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testInequality4()
    {
#ifdef HAVE_INET_ATON
        inet_aton("10.1.0.157", &rawAddr_);
#else
        if((rawAddr_.s_addr = inet_addr("10.1.0.157")) == -1)
        {
            CPPUNIT_ASSERT(false);
        }

#endif
        InetAddress addr(rawAddr_);
        InetAddress addr2("202.8.42.157");
        CPPUNIT_ASSERT(addr != addr2);
    }

    void testAssignment1()
    {
        InetAddress addr("255.255.255.255");
        InetAddress addr2 = addr;
        CPPUNIT_ASSERT(addr == addr2);
    }

    void testAssignment2()
    {
        InetAddress addr("127.0.0.1");
        InetAddress addr2("1.1.1.1");

        addr2 = addr;

        CPPUNIT_ASSERT(addr == addr2);
    }

    void testAssignmentCascade()
    {
        InetAddress addr("127.0.0.1");
        InetAddress addr2("1.1.1.1");
        InetAddress addr3("2.2.2.2");

        addr3 = addr2 = addr;

        CPPUNIT_ASSERT(addr == addr2);
        CPPUNIT_ASSERT(addr2 == addr3);
        CPPUNIT_ASSERT(addr == addr3);
    }

    void testCopyConstructor()
    {
        InetAddress addr("127.0.0.1");
        someFn(addr, addr);
    }

    void testToString()
    {
        InetAddress addr("202.8.42.178");
        std::string s = "202.8.42.178";
        std::string s2 = "203.3.43.211";

        CPPUNIT_ASSERT(s == addr.toString());
        CPPUNIT_ASSERT(!(s2 == addr.toString()));
        CPPUNIT_ASSERT(!strcmp(s.c_str(), addr.toString().c_str()));
        CPPUNIT_ASSERT(!strcmp("202.8.42.178", addr.toString().c_str()));

        CPPUNIT_ASSERT(s == addr.getHostAddress());
        CPPUNIT_ASSERT(!(s2 == addr.getHostAddress()));
        CPPUNIT_ASSERT(!strcmp(s.c_str(), addr.getHostAddress().c_str()));
        CPPUNIT_ASSERT(!strcmp("202.8.42.178", addr.getHostAddress().c_str()));
    }

    void testGetAddress()
    {
        char dst[INET_ADDRSTRLEN];
        memset(&rawAddr_, 0, sizeof(struct in_addr));
        std::string dstAddr = "";

        InetAddress addr("127.0.0.1");
        addr.getPrimitive(rawAddr_);

        memset(dst, 0, sizeof(char) * INET_ADDRSTRLEN);
        if((inet_ntop(AF_INET, &rawAddr_,
                        dst, sizeof(char) * INET_ADDRSTRLEN) != NULL) && (dst != NULL))
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

    void testIfSame()
    {
        InetAddress addr("127.0.0.1");
        InetAddress* addr_p = &addr;

        CPPUNIT_ASSERT(addr.sameObject(addr_p));
        CPPUNIT_ASSERT(addr_p->sameObject(&addr));
    }

    void testIfNotSame()
    {
        InetAddress addr("127.0.0.1");
        InetAddress addr2("127.0.0.1");

        CPPUNIT_ASSERT(addr.sameObject(&addr2));
        CPPUNIT_ASSERT(addr2.sameObject(&addr));
    }
  private:
    struct in_addr rawAddr_;
    void someFn(const InetAddress& addr1, InetAddress addr2)
    {
        CPPUNIT_ASSERT(addr1 == addr2);
    }
};
