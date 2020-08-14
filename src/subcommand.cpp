/**
 *  @file       subcommand.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiArgs/subcommand.h>
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
 * @brief SubCommand::registerSubCommand
 * @param path
 * @param parser
 * @return
 */
bool
SubCommand::registerSubCommand(const std::vector<std::string> &path,
                               ArgParser* parser)
{
    std::vector<std::string> inputPath = path;
    return m_rootObject->add(inputPath, parser);
}

/**
 * @brief SubCommand::parse
 * @param argc
 * @param argv
 * @return
 */
bool
SubCommand::parse(const int argc,
                  char* argv[])
{
    // TODO: find better solution without warning
    return parse(argc, (const char**)argv);
}

/**
 * @brief SubCommand::parse
 * @param argc
 * @param argv
 * @return
 */
bool
SubCommand::parse(const int argc,
                  const char* argv[])
{
    SubCommandEntry* next = m_rootObject;

    int i = 1;
    while(i < argc)
    {
        const std::string currentArgument(argv[i]);
        SubCommandEntry* temp = next->get(currentArgument);

        if(temp->parser != nullptr) {
            return temp->parser->parse(argc - i, &argv[i]);
        }

        i++;
        next = temp;
    }

    return false;
}

}
}
