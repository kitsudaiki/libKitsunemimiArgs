/**
 *  @file       sub_command_entry_test.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef SUB_COMMAND_ENTRY_TEST_H
#define SUB_COMMAND_ENTRY_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{
namespace Args
{

class SubCommandEntry_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    SubCommandEntry_Test();

    void add_test();
    void get_test();

    void clearMap_test();

};

}
}

#endif // SUB_COMMAND_ENTRY_TEST_H
