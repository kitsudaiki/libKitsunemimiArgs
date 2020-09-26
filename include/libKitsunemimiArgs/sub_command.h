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
    SubCommand(const std::string &version = "");
    ~SubCommand();

    bool registerSubCommand(const std::vector<std::string> &path,
                            ArgParser* parser);

    // parse
    bool parse(const int argc, char *argv[]);
    bool parse(const int argc, const char* argv[]);

private:
    friend SubCommand_Test;

    SubCommandEntry* m_rootObject = nullptr;
    std::string m_version = "";
};

}
}

#endif // SUBCOMMAND_H
