/**
 *  @file       main.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiArgs/arg_parser.h>
#include <libKitsunemimiCommon/logger.h>

int main(int argc, char *argv[])
{
    // error messages of the parser are printed via logger
    Kitsunemimi::initConsoleLogger(true);

    Kitsunemimi::Args::ArgParser parser("0.1.0");

    // register flags without value
    parser.registerPlain("debug,d",
                         "debug-flag to enable addtional debug output");
    // "registerPlain" allows it to register flags without any value, which says only true or flase
    //                 if they were set or not set

    // register flags
    parser.registerString("source",
                          "source-path",
                          true);
    parser.registerInteger("input,i",
                           "additional parameter");

    // register other values
    parser.registerString("mode",
                          "modus for converting",
                          true,  // true to make it requried
                          true); // true to register this without a "--"-flag
    parser.registerString("destination",
                          "destination path for output",
                          true,
                          true);
    // register types:
    //     registerString
    //     registerInteger
    //     registerFloat
    //     registerBoolean

    bool ret = parser.parse(argc, argv);
    if(ret == false) {
        return 1;
    }
    // ret say, if the converting was successful or not. Error-message are written in the logger

    // check if flags without values were set. In this case check if the debug-flag was set

    // get values with or without flag as list of value for the case, that a flag was
    // used multiple times within one cli-call:
    const std::vector<std::string> testValues = parser.getStringValues("source");
    const std::vector<long> numbers = parser.getIntValues("input");
    // get types:
    //     getStringValues
    //     getIntValues
    //     getFloatValues
    //     getBoolValues

    // get values without flag:
    const std::string mode = parser.getStringValue("mode");
    const std::string destination = parser.getStringValue("destination");
    // get types:
    //     getStringValue
    //     getIntValue
    //     getFloatValue
    //     getBoolValue

    //...

    return 0;
}
