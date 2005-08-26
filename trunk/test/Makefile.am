TESTS = Object Inet4Address Inet6Address IPEndpoint
check_PROGRAMS = $(TESTS)

Object_SOURCES = ObjectTest.cpp
Inet4Address_SOURCES = Inet4AddressTest.cpp
Inet6Address_SOURCES = Inet6AddressTest.cpp
IPEndpoint_SOURCES = IPEndpointTest.cpp

AM_CPPFLAGS = $(CPPUNIT_CFLAGS) -I../src
AM_LDFLAGS = $(CPPUNIT_LIBS) -lfrog -L../src
