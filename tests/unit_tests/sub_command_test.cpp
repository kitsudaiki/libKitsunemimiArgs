#include "sub_command_test.h"

#include <libKitsunemimiArgs/sub_command.h>
#include <libKitsunemimiArgs/arg_parser.h>

namespace Kitsunemimi
{
namespace Args
{

SubCommand_Test::SubCommand_Test()
    : Kitsunemimi::CompareTestHelper("SubCommand_Test")
{
    registerSubCommand_test();
    parse_test();
}

/**
 * @brief parse_test
 */
void
SubCommand_Test::registerSubCommand_test()
{
    SubCommand subCommand;

    // prepare arg-parser for tests
    ArgParser* parser1 = new ArgParser();
    ArgParser* parser2 = new ArgParser();

    // positive tests
    TEST_EQUAL(subCommand.registerSubCommand({"poi", "asdf"}, parser1), true);
    TEST_EQUAL(subCommand.registerSubCommand({"poi", "xyz"}, parser2), true);

    // negative tests
    TEST_EQUAL(subCommand.registerSubCommand({"poi", "asdf"}, parser1), false);
    TEST_EQUAL(subCommand.registerSubCommand({"poi", "1234"}, nullptr), false);
}

/**
 * @brief parse_test
 */
void
SubCommand_Test::parse_test()
{
    SubCommand subCommand;

    // prepare arg-parser for tests
    ArgParser* parser1 = new ArgParser();
    initArgParser(parser1);
    ArgParser* parser2 = new ArgParser();
    initArgParser(parser2);

    // prepare entries
    subCommand.registerSubCommand({"poi", "asdf"}, parser1);
    subCommand.registerSubCommand({"poi", "xyz"}, parser2);

    // init args for testing
    int argc = 17;
    const char* argv[17];
    argv[0] = "-";
    argv[1] = "poi";
    argv[2] = "asdf";
    argv[3] = "--test";
    argv[4] = "test1";
    argv[5] = "--test";
    argv[6] = "test2";
    argv[7] = "--integer";
    argv[8] = "1337";
    argv[9] = "-f";
    argv[10] = "123.5";
    argv[11] = "-b";
    argv[12] = "true";
    argv[13] = "poi";
    argv[14] = "42";
    argv[15] = "42.25";
    argv[16] = "false";

    TEST_EQUAL(subCommand.parse(argc, argv), true);

    argv[2] = "xyz";
    TEST_EQUAL(subCommand.parse(argc, argv), true);

    argv[1] = "fail";
    TEST_EQUAL(subCommand.parse(argc, argv), false);
}

/**
 * @brief SubCommand_Test::prepareTest
 * @param parser
 */
void
SubCommand_Test::initArgParser(ArgParser* parser)
{
    std::string errorMessage = "";

    parser->registerString("test", " ");
    parser->registerInteger("integer,i", " ");
    parser->registerFloat("float,f", " ");
    parser->registerBoolean("bool,b", " ");
    parser->registerString("first_arg", "first argument", true, true);
    parser->registerInteger("secondArg", "second argument", true, true);
    parser->registerFloat("thirdArg", "third argument", true, true);
    parser->registerBoolean("lastArg", "last argument", true, true);
}

}
}
