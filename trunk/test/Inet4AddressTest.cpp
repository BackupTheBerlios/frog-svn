#include <iostream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextTestRunner.h>

#include <Inet4AddressTest.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

CPPUNIT_TEST_SUITE_REGISTRATION(Inet4AddressTest);

int main(int argc, char* argv[])
{
	CppUnit::TextTestRunner runner;
	CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();

	runner.addTest(registry.makeTest());
	runner.setOutputter(CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cerr));
	
	bool success = runner.run();
	return (success ? 0 : 1);
}

