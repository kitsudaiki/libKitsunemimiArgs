/**
 *  @file       sub_command_entry.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include "sub_command_entry.h"

#include <libKitsunemimiArgs/arg_parser.h>

namespace Kitsunemimi
{
namespace Args
{

/**
 * @brief SubCommandEntry::SubCommandEntry
 */
SubCommandEntry::SubCommandEntry() {}

/**
 * @brief SubCommandEntry::~SubCommandEntry
 */
SubCommandEntry::~SubCommandEntry()
{
    clearMap();

    if(parser != nullptr) {
        delete parser;
    }
}

/**
 * @brief SubCommandEntry::add
 * @param path
 * @param newEntry
 * @return
 */
bool
SubCommandEntry::add(std::vector<std::string> &path,
                     ArgParser* parser)
{
    // terminate
    if(path.size() == 0)
    {
        // if already registered, return false, because overriding is not allowed
        if(this->parser != nullptr) {
            return false;
        }

        this->parser = parser;

        return true;
    }

    // cut next value from the path
    const std::string firstValue = path.at(0);
    path.erase(path.begin());

    SubCommandEntry* result = nullptr;

    // search for value and make recursive call, if found
    std::map<std::string, SubCommandEntry*>::const_iterator it;
    it = next.find(firstValue);
    if(it != next.end()) {
        result = it->second;
    } else {
        next.insert(std::make_pair(firstValue, new SubCommandEntry()));
    }

    return result->add(path, parser);
}

/**
 * @brief SubCommandEntry::get
 * @param key
 * @return
 */
SubCommandEntry*
SubCommandEntry::get(const std::string &key)
{
    // terminate
    if(this->next.size() == 0) {
        return this;
    }

    // search for value and make recursive call, if found
    std::map<std::string, SubCommandEntry*>::const_iterator it;
    it = next.find(key);
    if(it != next.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief SubCommandEntry::clearMap
 */
void
SubCommandEntry::clearMap()
{
    std::map<std::string, SubCommandEntry*>::iterator it;
    for(it = next.begin();
        it != next.end();
        it++)
    {
        delete it->second;
    }
}

}
}
