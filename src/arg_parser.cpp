#include <libKitsunemimiArgs/arg_parser.h>

#include <libKitsunemimiCommon/common_methods/string_methods.h>
#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiPersistence/logger/logger.h>

namespace Kitsunemimi
{
namespace Args
{

ArgParser::ArgParser()
{

}

/**
 * @brief ArgParser::addArgument
 * @param identifier
 * @param helpText
 * @param type
 * @param withoutFlag
 * @return
 */
bool
ArgParser::addArgument(const std::string &identifier,
                       const std::string &helpText,
                       const ArgType type,
                       bool withoutFlag)
{
    // precheck
    if(identifier.size() == 0)
    {
        LOG_ERROR("No argument identifier was set");
        return false;
    }

    ArgIdentifier newArgument;

    // split identifier-string
    std::vector<std::string> identifierList;
    splitStringByDelimiter(identifierList, identifier, ',');

    // check splitting-result
    if(identifierList.size() > 2)
    {
        LOG_ERROR("Argument identifier is long: " + identifier);
        return false;
    }

    // prepare long identifier
    newArgument.longIdentifier = identifierList.at(0);
    if(newArgument.longIdentifier.size() == 0) {
        LOG_ERROR("Argument identifier is invalid: " + identifier);
    }

    // prepare short identifier
    if(identifierList.size() == 2)
    {
        newArgument.shortIdentifier = identifierList.at(1);
        if(newArgument.shortIdentifier.size() == 0) {
            LOG_ERROR("Argument identifier is invalid: " + identifier);
        }
    }

    // set other values
    newArgument.withoutFlag = withoutFlag;
    newArgument.type = type;
    newArgument.helpText = helpText;
    newArgument.results = new DataArray();

    return true;
}

/**
 * @brief ArgParser::parse
 * @param argc
 * @param argv
 * @return
 */
bool
ArgParser::parse(int argc, char* argv[])
{

}

/**
 * @brief ArgParser::getNumberOfValues
 * @param identifier
 * @return
 */
uint64_t
ArgParser::getNumberOfValues(const std::string &identifier)
{
    ArgParser::ArgIdentifier* arg = getArg(identifier);
    if(arg == nullptr) {
        return 0;
    }

    return arg->results->size();
}

/**
 * @brief ArgParser::getStringValues
 * @param identifier
 * @return
 */
const std::vector<std::string>
ArgParser::getStringValues(const std::string &identifier)
{
    std::vector<std::string> result;

    ArgParser::ArgIdentifier* arg = getArg(identifier);
    if(arg == nullptr) {
        return result;
    }
    if(arg->type != STRING_TYPE) {
        return result;
    }

    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->getString());
    }

    return result;
}

/**
 * @brief ArgParser::getIntValues
 * @param identifier
 * @return
 */
const std::vector<long>
ArgParser::getIntValues(const std::string &identifier)
{
    std::vector<long> result;

    ArgParser::ArgIdentifier* arg = getArg(identifier);
    if(arg == nullptr) {
        return result;
    }
    if(arg->type != INT_TYPE) {
        return result;
    }

    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->getLong());
    }

    return result;
}

/**
 * @brief ArgParser::getFloatValues
 * @param identifier
 * @return
 */
const std::vector<double>
ArgParser::getFloatValues(const std::string &identifier)
{
    std::vector<double> result;

    ArgParser::ArgIdentifier* arg = getArg(identifier);
    if(arg == nullptr) {
        return result;
    }
    if(arg->type != FLOAT_TYPE) {
        return result;
    }

    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->getDouble());
    }

    return result;
}

/**
 * @brief ArgParser::getBoolValues
 * @param identifier
 * @return
 */
const std::vector<bool>
ArgParser::getBoolValues(const std::string &identifier)
{
    std::vector<bool> result;

    ArgParser::ArgIdentifier* arg = getArg(identifier);
    if(arg == nullptr) {
        return result;
    }
    if(arg->type != BOOL_TYPE) {
        return result;
    }

    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->getBool());
    }

    return result;
}

/**
 * @brief ArgParser::getArg
 * @param identifier
 * @return
 */
ArgParser::ArgIdentifier*
ArgParser::getArg(const std::string &identifier)
{
    for(uint32_t i = 0; i < argumentList.size(); i++)
    {
        if(argumentList.at(i).longIdentifier == identifier) {
            return &argumentList.at(i);
        }
    }

    return nullptr;
}

}
}
