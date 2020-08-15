/**
 *  @file       sub_command_test.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef SUB_COMMAND_TEST_H
#define SUB_COMMAND_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{
namespace Args
{
class ArgParser;

class SubCommand_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    SubCommand_Test();

    void registerSubCommand_test();

    void parse_test();

private:
    void initArgParser(ArgParser* parser);
};

}
}

#endif // SUB_COMMAND_TEST_H
