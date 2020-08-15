/**
 *  @file       sub_command_entry_test.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include "sub_command_entry_test.h"

#include <sub_command_entry.h>
#include <libKitsunemimiArgs/arg_parser.h>

namespace Kitsunemimi
{
namespace Args
{

SubCommandEntry_Test::SubCommandEntry_Test()
    : Kitsunemimi::CompareTestHelper("SubCommandEntry_Test")
{
    add_test();
    get_test();

    clearMap_test();
}

/**
 * @brief add_test
 */
void
SubCommandEntry_Test::add_test()
{
    SubCommandEntry testEntry;
    std::vector<std::string> path;

    // prepare arg-parser for tests
    ArgParser* parser1 = new ArgParser();
    ArgParser* parser2 = new ArgParser();

    // positive tests
    path = {"poi", "asdf"};
    TEST_EQUAL(testEntry.add(path, parser1), true);

    path = {"poi", "xyz"};
    TEST_EQUAL(testEntry.add(path, parser2), true);

    // negative tests
    path = {"poi", "asdf"};
    TEST_EQUAL(testEntry.add(path, parser1), false);

    path = {"poi", "1234"};
    TEST_EQUAL(testEntry.add(path, nullptr), false);
}

/**
 * @brief get_test
 */
void
SubCommandEntry_Test::get_test()
{
    SubCommandEntry testEntry;
    SubCommandEntry* next = nullptr;

    // prepare arg-parser for tests
    ArgParser* parser = new ArgParser();

    // prepare entries
    std::vector<std::string> path = {"poi", "asdf"};
    testEntry.add(path, parser);

    // positive tests
    next = testEntry.get("poi");
    const bool isNullptr1 = next == nullptr;
    TEST_EQUAL(isNullptr1, false);

    next = next->get("asdf");
    const bool isNullptr2 = next == nullptr;
    TEST_EQUAL(isNullptr2, false);

    // negative tests
    next = testEntry.get("1234");
    const bool isNullptr3 = next == nullptr;
    TEST_EQUAL(isNullptr3, true);
}

/**
 * @brief clearMap_test
 */
void
SubCommandEntry_Test::clearMap_test()
{
    SubCommandEntry testEntry;

    // prepare arg-parser for tests
    ArgParser* parser = new ArgParser();

    // prepare entries
    std::vector<std::string> path = {"poi", "asdf"};
    testEntry.add(path, parser);

    // run test
    testEntry.clearMap();
    TEST_EQUAL(testEntry.next.size(), 0);
    const bool isNullptr = testEntry.parser == nullptr;
    TEST_EQUAL(isNullptr, true);
}

}
}
