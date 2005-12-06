#include <iostream>
using std::cout;
using std::endl;

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextTestRunner.h>

#include <NetworkInterfaceTest.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkInterfaceTest);

int main(int argc, char* argv[])
{
    CppUnit::TextTestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();

    cout << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "  If tests below fails, some configuration is required" << endl;
    cout << "  (specifically the interfaces and addresses). You need " << endl;
    cout << "  to change it to suit your system." << endl;
    cout << "--------------------------------------------------------" << endl;

    runner.addTest(registry.makeTest());
    runner.setOutputter(CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cerr));

    bool success = runner.run();
    return (success ? 0 : 1);
}

