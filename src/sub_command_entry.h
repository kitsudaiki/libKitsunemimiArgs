/**
 *  @file       sub_command_entry.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef SUB_COMMAND_ENTRY_H
#define SUB_COMMAND_ENTRY_H

#include <map>
#include <vector>
#include <string>

namespace Kitsunemimi
{
namespace Args
{
class ArgParser;

class SubCommandEntry
{

public:
    SubCommandEntry();
    ~SubCommandEntry();

    bool add(std::vector<std::string> &path,
             ArgParser* parser);
    SubCommandEntry* get(const std::string &key);

    void clearMap();

    ArgParser* parser = nullptr;
    std::map<std::string, SubCommandEntry*> next;
};

}
}

#endif // SUB_COMMAND_ENTRY_H
