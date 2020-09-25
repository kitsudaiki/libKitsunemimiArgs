/**
 *  @file       subcommand.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef SUBCOMMAND_H
#define SUBCOMMAND_H

#include <map>
#include <vector>
#include <string>

namespace Kitsunemimi
{
namespace Args
{
class SubCommand_Test;

class SubCommandEntry;
class ArgParser;

class SubCommand
{
public:
    SubCommand();
    ~SubCommand();

    bool registerSubCommand(const std::vector<std::string> &path,
                            ArgParser* parser);

    // parse
    bool parse(const int argc, char *argv[], const std::string &version);
    bool parse(const int argc, const char* argv[], const std::string &version);

private:
    friend SubCommand_Test;

    SubCommandEntry* m_rootObject = nullptr;
};

}
}

#endif // SUBCOMMAND_H
