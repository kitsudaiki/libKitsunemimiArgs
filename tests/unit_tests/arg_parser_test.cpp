#include "arg_parser_test.h"

#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiArgs/arg_parser.h>

namespace Kitsunemimi
{
namespace Args
{

ArgParser_Test::ArgParser_Test()
    : Kitsunemimi::CompareTestHelper("ArgParser_Test")
{
    registerArgument_test();
    getArgument_test();
    convertValue_test();

    registerString_test();
    registerInteger_test();
    registerFloat_test();
    registerBoolean_test();

    parse_test();

    getNumberOfValues_test();
    getStringValues_test();
    getIntValues_test();
    getFloatValues_test();
    getBoolValues_test();
}

/**
 * @brief registerArgument_test
 */
void
ArgParser_Test::registerArgument_test()
{
    ArgParser parser;

    TEST_EQUAL(parser.registerArgument("",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , false);
    TEST_EQUAL(parser.registerArgument("xyz,",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , true);
    TEST_EQUAL(parser.registerArgument(",a",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , false);
    TEST_EQUAL(parser.registerArgument("asdf,asdf",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , false);

    TEST_EQUAL(parser.registerArgument("asdf,a",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , true);
    TEST_EQUAL(parser.registerArgument("asdf,a",
                                       "this is an example",
                                       ArgParser::ArgType::INT_TYPE,
                                       true,
                                       false)
               , false);
}

/**
 * @brief getArgument_test
 */
void
ArgParser_Test::getArgument_test()
{
    ArgParser parser;
    bool isNullptr = false;

    parser.registerArgument("asdf,a",
                            "this is an example",
                            ArgParser::ArgType::INT_TYPE,
                            true,
                            false);

    isNullptr = parser.getArgument("xyz") == nullptr;
    TEST_EQUAL(isNullptr, true);

    isNullptr = parser.getArgument("--asdf") == nullptr;
    TEST_EQUAL(isNullptr, false);

    isNullptr = parser.getArgument("-a") == nullptr;
    TEST_EQUAL(isNullptr, false);

    ArgParser::ArgIdentifier* ret = parser.getArgument("-a");
    TEST_EQUAL(ret->type, ArgParser::ArgType::INT_TYPE);
    TEST_EQUAL(ret->helpText, std::string("this is an example"));
    TEST_EQUAL(ret->required, true);
    TEST_EQUAL(ret->withoutFlag, false);
    TEST_EQUAL(ret->longIdentifier, "--asdf");
    TEST_EQUAL(ret->shortIdentifier, "-a");
}

/**
 * @brief convertValue_test
 */
void
ArgParser_Test::convertValue_test()
{
    ArgParser parser;
    DataItem* result = nullptr;
    bool isNullptr = false;

    // string-type
    // check if result is nullptr
    isNullptr = parser.convertValue("asdf", ArgParser::ArgType::STRING_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("1", ArgParser::ArgType::STRING_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);

    // check result value
    result = parser.convertValue("asdf", ArgParser::ArgType::STRING_TYPE);
    TEST_EQUAL(result->toValue()->getValueType(), DataValue::STRING_TYPE);
    TEST_EQUAL(result->getString(), "asdf");

    // int-type
    // check if result is nullptr
    isNullptr = parser.convertValue("1", ArgParser::ArgType::INT_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("asdf", ArgParser::ArgType::INT_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, true);

    // check result value
    result = parser.convertValue("42", ArgParser::ArgType::INT_TYPE);
    TEST_EQUAL(result->toValue()->getValueType(), DataValue::INT_TYPE);
    TEST_EQUAL(result->getInt(), 42);

    // float-type
    // check if result is nullptr
    isNullptr = parser.convertValue("1.0", ArgParser::ArgType::FLOAT_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("1", ArgParser::ArgType::FLOAT_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("asdf", ArgParser::ArgType::FLOAT_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, true);

    // check result value
    result = parser.convertValue("42.25", ArgParser::ArgType::FLOAT_TYPE);
    TEST_EQUAL(result->toValue()->getValueType(), DataValue::FLOAT_TYPE);
    TEST_EQUAL(result->getDouble(), 42.25);

    // bool-type
    // check if result is nullptr
    isNullptr = parser.convertValue("1", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("true", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("True", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("0", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("false", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);
    isNullptr = parser.convertValue("False", ArgParser::ArgType::BOOL_TYPE) == nullptr;
    TEST_EQUAL(isNullptr, false);

    // check result value
    result = parser.convertValue("true", ArgParser::ArgType::BOOL_TYPE);
    TEST_EQUAL(result->toValue()->getValueType(), DataValue::BOOL_TYPE);
    TEST_EQUAL(result->getBool(), true);
}

/**
 * @brief registerString_test
 */
void
ArgParser_Test::registerString_test()
{
    ArgParser parser;

    TEST_EQUAL(parser.registerString("", "this is an example", true, false), false);
    TEST_EQUAL(parser.registerString("asdf", "this is an example", true, false), true);
}

/**
 * @brief registerInteger_test
 */
void
ArgParser_Test::registerInteger_test()
{
    ArgParser parser;

    TEST_EQUAL(parser.registerInteger("", "this is an example", true, false), false);
    TEST_EQUAL(parser.registerInteger("asdf", "this is an example", true, false), true);
}

/**
 * @brief registerFloat_test
 */
void
ArgParser_Test::registerFloat_test()
{
    ArgParser parser;

    TEST_EQUAL(parser.registerFloat("", "this is an example", true, false), false);
    TEST_EQUAL(parser.registerFloat("asdf", "this is an example", true, false), true);
}

/**
 * @brief registerBoolean_test
 */
void
ArgParser_Test::registerBoolean_test()
{
    ArgParser parser;

    TEST_EQUAL(parser.registerBoolean("", "this is an example", true, false), false);
    TEST_EQUAL(parser.registerBoolean("asdf", "this is an example", true, false), true);
}

/**
 * @brief parse_test
 */
void
ArgParser_Test::parse_test()
{

}

/**
 * @brief getNumberOfValues_test
 */
void
ArgParser_Test::getNumberOfValues_test()
{

}

/**
 * @brief getStringValues_test
 */
void
ArgParser_Test::getStringValues_test()
{

}

/**
 * @brief getIntValues_test
 */
void
ArgParser_Test::getIntValues_test()
{

}

/**
 * @brief getFloatValues_test
 */
void
ArgParser_Test::getFloatValues_test()
{

}

/**
 * @brief getBoolValues_test
 */
void
ArgParser_Test::getBoolValues_test()
{

}

}
}
