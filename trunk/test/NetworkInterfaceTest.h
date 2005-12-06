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

#include <iostream>
#include <cstdio>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>
#include <frog/NetworkInterface.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using frog::net::NetworkInterface;
using frog::net::InetAddress;
using std::string;
using std::vector;
using std::cout;
using std::endl;

class NetworkInterfaceTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(NetworkInterfaceTest);


    CPPUNIT_TEST(testEquality1);
    CPPUNIT_TEST(testEquality2);
    CPPUNIT_TEST(testInequality1);
    CPPUNIT_TEST(testInequality2);
    CPPUNIT_TEST(displayOneAndOther);
    CPPUNIT_TEST(displayAll);

    CPPUNIT_TEST_SUITE_END();
  public:
    void testEquality1()
    {
        InetAddress addr("127.0.0.1");
        NetworkInterface ni = NetworkInterface::getByInetAddress(addr);

        InetAddress addr2("127.0.0.1");
        NetworkInterface ni2 = NetworkInterface::getByInetAddress(addr2);

        CPPUNIT_ASSERT(ni == ni2);
    }

    void testEquality2()
    {
        NetworkInterface ni = NetworkInterface::getByName("eth0");
        NetworkInterface ni2 = NetworkInterface::getByName("eth0");
        CPPUNIT_ASSERT(ni == ni2);
    }

    void testInequality1()
    {
        InetAddress addr("127.0.0.1");
        NetworkInterface ni = NetworkInterface::getByInetAddress(addr);

        InetAddress addr2("127.0.0.2");
        NetworkInterface ni2 = NetworkInterface::getByInetAddress(addr2);

        CPPUNIT_ASSERT(ni != ni2);
    }

    void testInequality2()
    {
        NetworkInterface ni = NetworkInterface::getByName("eth0");
        NetworkInterface ni2 = NetworkInterface::getByName("lo");
        CPPUNIT_ASSERT(ni != ni2);
    }

    void displayOneAndOther()
    {
        NetworkInterface::InterfaceAddrList int_addr;
        NetworkInterface::InterfaceAddrListIterator int_addr_iter;

        NetworkInterface ni = NetworkInterface::getByName("lo");
        int_addr = ni.getInterfaceAddresses();
        cout << endl;
        cout << ni.name;
        for(int_addr_iter = int_addr.begin(); int_addr_iter != int_addr.end(); ++int_addr_iter)
        {
            cout << "	inet addr: " << int_addr_iter->unicast.getHostAddress();
            cout << "  Mask: " << int_addr_iter->netmask.getHostAddress();
            cout << "  Bcast: " << int_addr_iter->broadcast.getHostAddress() << endl;
        }
        cout << "	String: " << ni.toString() << endl;

        NetworkInterface ni2 = NetworkInterface::getByName("eth0");
        int_addr = ni2.getInterfaceAddresses();
        cout << endl;
        cout << ni2.name;
        for(int_addr_iter = int_addr.begin(); int_addr_iter != int_addr.end(); ++int_addr_iter)
        {
            cout << "	inet addr: " << int_addr_iter->unicast.getHostAddress();
            cout << "  Mask: " << int_addr_iter->netmask.getHostAddress();
            cout << "  Bcast: " << int_addr_iter->broadcast.getHostAddress() << endl;
        }
        cout << "	String: " << ni2.toString() << endl;
        cout << endl;

        CPPUNIT_ASSERT(ni != ni2);
    }

    void displayAll()
    {
        vector<NetworkInterface> nis = NetworkInterface::getNetworkInterfaces();
        vector<NetworkInterface>::iterator if_iter;

        NetworkInterface::InterfaceAddrList int_addr;
        NetworkInterface::InterfaceAddrListIterator int_addr_iter;

        int count = 0;
        cout << endl;
        for(if_iter = nis.begin(); if_iter != nis.end(); ++if_iter)
        {
            ++count;
            int_addr = if_iter->getInterfaceAddresses();
            cout << if_iter->name;
            for(int_addr_iter = int_addr.begin(); int_addr_iter != int_addr.end(); ++int_addr_iter)
            {
                cout << "	inet addr: " << int_addr_iter->unicast.getHostAddress();
                cout << "  Mask: " << int_addr_iter->netmask.getHostAddress();
                cout << "  Bcast: " << int_addr_iter->broadcast.getHostAddress() << endl;
            }

            cout << "	String: " << if_iter->toString() << endl;
            cout << endl;
        }

        CPPUNIT_ASSERT(nis.size() > 0);
    }


};
