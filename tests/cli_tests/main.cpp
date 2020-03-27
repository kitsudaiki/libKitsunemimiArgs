#include <libKitsunemimiArgs/arg_parser.h>
#include <libKitsunemimiPersistence/logger/logger.h>

int main(int argc, char *argv[])
{
    // error messages of the parser are printed via logger
    Kitsunemimi::Persistence::initLogger("/tmp", "testlog", true, true);

    Kitsunemimi::Args::ArgParser parser;

    // register flags
    parser.registerString("asdf",
                          "optional test-flag",
                          true);
    parser.registerInteger("test_integer,i",
                           "optional int values for testing");

    // register other values
    parser.registerString("first_arg",
                          "first required argument",
                          true,  // true to make it requried
                          true); // true to register this without a "--"-flag
    parser.registerInteger("second_arg",
                           "second requred argument",
                           true,
                           true);
    // register types:
    //     registerString
    //     registerInteger
    //     registerFloat
    //     registerBoolean

    bool ret = parser.parse(argc, argv);

    const std::vector<std::string> testValues = parser.getStringValues("asdf");

    const std::vector<long> numbers = parser.getIntValues("test_integer");

    const std::string testValue = parser.getStringValue("first_arg");

    const long number = parser.getIntValue("second_arg");
}
