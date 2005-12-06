#include <cstdio>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextTestRunner.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_IPV6_SUPPORT

#include <Inet6AddressTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Inet6AddressTest);

#endif

int main(int argc, char* argv[])
{
#ifdef HAVE_IPV6_SUPPORT
    CppUnit::TextTestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();

    runner.addTest(registry.makeTest());
    runner.setOutputter(CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cerr));

    bool success = runner.run();
    return (success ? 0 : 1);
#else
    ::printf("\n.(Skipped test. No IPv6 support defined.)\n");
    return 0;
#endif
}

