/**
 *  @file       subcommand.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiArgs/sub_command.h>
#include <sub_command_entry.h>
#include <libKitsunemimiArgs/arg_parser.h>

namespace Kitsunemimi
{
namespace Args
{

/**
 * @brief SubCommand::SubCommand
 */
SubCommand::SubCommand()
{
    m_rootObject = new SubCommandEntry();
}

/**
 * @brief SubCommand::~SubCommand
 */
SubCommand::~SubCommand()
{
    m_rootObject->clearMap();
}

/**
 * @brief register new sub-command
 *
 * @param path sub-command path
 * @param parser argument-parser at the end of the new sub-command
 *
 * @return flase, if already registered
 */
bool
SubCommand::registerSubCommand(const std::vector<std::string> &path,
                               ArgParser* parser)
{
    std::vector<std::string> inputPath = path;
    return m_rootObject->add(inputPath, parser);
}

/**
 * @brief parse cli-arguments
 *
 * @param argc number of arguments
 * @param argv arguments
 *
 * @return false, if parsing failed
 */
bool
SubCommand::parse(const int argc,
                  char* argv[],
                  const std::string &version)
{
    // TODO: find better solution without warning
    return parse(argc, (const char**)argv, version);
}

/**
 * @brief parse cli-arguments
 *
 * @param argc number of arguments
 * @param argv arguments as const char
 *
 * @return false, if parsing failed
 */
bool
SubCommand::parse(const int argc,
                  const char* argv[],
                  const std::string &version)
{
    SubCommandEntry* next = m_rootObject;

    int i = 1;
    while(i < argc)
    {
        const std::string currentArgument(argv[i]);

        // in case, that there is already reached the first flag
        if(currentArgument.at(0) == '-') {
            return false;
        }

        SubCommandEntry* temp = next->get(currentArgument);

        // case of invalid path
        if(temp == nullptr) {
            return false;
        }

        if(temp->parser != nullptr) {
            return temp->parser->parse(argc - i, &argv[i], version);
        }

        i++;
        next = temp;
    }

    return false;
}

}
}
