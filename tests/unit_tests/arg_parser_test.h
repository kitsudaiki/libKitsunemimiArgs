/**
 *  @file       arg_parser_test.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef ARG_PARSER_TEST_H
#define ARG_PARSER_TEST_H

#include <assert.h>
#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{
class ArgParser;

class ArgParser_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    ArgParser_Test();

    void registerArgument_test();
    void getArgument_test();
    void convertValue_test();

    void registerString_test();
    void registerInteger_test();
    void registerFloat_test();
    void registerBoolean_test();

    void parse_test();

    void getNumberOfValues_test();
    void getStringValues_test();
    void getIntValues_test();
    void getFloatValues_test();
    void getBoolValues_test();

    void getStringValue_test();
    void getIntValue_test();
    void getFloatValue_test();
    void getBoolValue_test();

private:
    void prepareTest(ArgParser* parser);
};

}

#endif // ARG_PARSER_TEST_H
