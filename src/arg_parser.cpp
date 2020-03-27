/**
 *  @file       arg_parser.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiArgs/arg_parser.h>

#include <libKitsunemimiCommon/common_methods/string_methods.h>
#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiPersistence/logger/logger.h>

namespace Kitsunemimi
{
namespace Args
{

/**
 * @brief constructor
 */
ArgParser::ArgParser() {}

/**
 * @brief destructor
 */
ArgParser::~ArgParser()
{
    for(uint32_t i = 0; i < m_argumentList.size(); i++)
    {
        delete m_argumentList[i].results;
    }
}

/**
 * @brief register string-value
 *
 * @param identifier Identifier for the new argument. Its a single word like "flag" for defining
 *                   only a long identifier like "--flag" or a comma-separated pair like "flag,f"
 *                   to define a long identifier like "--flag" together with a short identifier
 *                   like "-f"
 * @param helpText help-text for the argument for user-output
 * @param required true, to make the argument required, fals to make it optional
 * @param withoutFlag true, the handle the identifier as flag for the value
 *
 * @return false, if identifier is already registered or broken, else true
 */
bool
ArgParser::registerString(const std::string &identifier,
                          const std::string &helpText,
                          bool required,
                          bool withoutFlag)
{
    return registerArgument(identifier,
                            helpText,
                            ArgType::STRING_TYPE,
                            required,
                            withoutFlag);
}

/**
 * @brief register int/long value
 *
 * @param identifier Identifier for the new argument. Its a single word like "flag" for defining
 *                   only a long identifier like "--flag" or a comma-separated pair like "flag,f"
 *                   to define a long identifier like "--flag" together with a short identifier
 *                   like "-f"
 * @param helpText help-text for the argument for user-output
 * @param required true, to make the argument required, fals to make it optional
 * @param withoutFlag true, the handle the identifier as flag for the value
 *
 * @return false, if identifier is already registered or broken, else true
 */
bool
ArgParser::registerInteger(const std::string &identifier,
                           const std::string &helpText,
                           bool required,
                           bool withoutFlag)
{
    return registerArgument(identifier,
                            helpText,
                            ArgType::INT_TYPE,
                            required,
                            withoutFlag);
}


/**
 * @brief register float/double value
 *
 * @param identifier Identifier for the new argument. Its a single word like "flag" for defining
 *                   only a long identifier like "--flag" or a comma-separated pair like "flag,f"
 *                   to define a long identifier like "--flag" together with a short identifier
 *                   like "-f"
 * @param helpText help-text for the argument for user-output
 * @param required true, to make the argument required, fals to make it optional
 * @param withoutFlag true, the handle the identifier as flag for the value
 *
 * @return false, if identifier is already registered or broken, else true
 */
bool
ArgParser::registerFloat(const std::string &identifier,
                         const std::string &helpText,
                         bool required,
                         bool withoutFlag)
{
    return registerArgument(identifier,
                            helpText,
                            ArgType::FLOAT_TYPE,
                            required,
                            withoutFlag);
}

/**
 * @brief register bool value
 *
 * @param identifier Identifier for the new argument. Its a single word like "flag" for defining
 *                   only a long identifier like "--flag" or a comma-separated pair like "flag,f"
 *                   to define a long identifier like "--flag" together with a short identifier
 *                   like "-f"
 * @param helpText help-text for the argument for user-output
 * @param required true, to make the argument required, fals to make it optional
 * @param withoutFlag true, the handle the identifier as flag for the value
 *
 * @return false, if identifier is already registered or broken, else true
 */
bool
ArgParser::registerBoolean(const std::string &identifier,
                           const std::string &helpText,
                           bool required,
                           bool withoutFlag)
{
    return registerArgument(identifier,
                            helpText,
                            ArgType::BOOL_TYPE,
                            required,
                            withoutFlag);
}

/**
 * @brief register ne argument
 *
 * @param identifier Identifier for the new argument. Its a single word like "flag" for defining
 *                   only a long identifier like "--flag" or a comma-separated pair like "flag,f"
 *                   to define a long identifier like "--flag" together with a short identifier
 *                   like "-f"
 * @param helpText help-text for the argument for user-output
 * @param type type identifier
 * @param required true, to make the argument required, fals to make it optional
 * @param withoutFlag true, the handle the identifier as flag for the value
 *
 * @return false, if identifier is already registered or broken, else true
 */
bool
ArgParser::registerArgument(const std::string &identifier,
                            const std::string &helpText,
                            const ArgType type,
                            bool required,
                            bool withoutFlag)
{
    // precheck
    if(identifier.size() == 0
            || identifier.at(0) == ',')
    {
        LOG_ERROR("No argument identifier was set");
        return false;
    }

    ArgDefinition newArgument;

    // split identifier-string
    std::vector<std::string> identifierList;
    splitStringByDelimiter(identifierList, identifier, ',');

    // check splitting-result
    if(identifierList.size() > 2)
    {
        LOG_ERROR("argument identifier is long: " + identifier);
        return false;
    }

    // prepare long identifier
    if(identifierList.at(0).size() == 0)
    {
        LOG_ERROR("argument identifier is invalid: " + identifier);
        return false;
    }
    if(withoutFlag == false) {
        newArgument.longIdentifier = "--";
    }

    newArgument.longIdentifier += identifierList.at(0);

    // check if already used
    ArgParser::ArgDefinition* findLong = getArgument(newArgument.longIdentifier);
    if(findLong != nullptr)
    {
        LOG_ERROR("argument already in use: " + newArgument.longIdentifier);
        return false;
    }

    // prepare short identifier
    if(identifierList.size() == 2)
    {
        // check length
        if(identifierList.at(1).size() != 1)
        {
            LOG_ERROR("Argument identifier is invalid: " + identifier);
            return false;
        }

        newArgument.shortIdentifier = "-" + identifierList.at(1);

        // check if already used
        ArgParser::ArgDefinition* findShort = getArgument(newArgument.shortIdentifier);
        if(findShort != nullptr)
        {
            LOG_ERROR("argument already in use: " + newArgument.shortIdentifier);
            return false;
        }
    }

    // set other values
    newArgument.withoutFlag = withoutFlag;
    newArgument.required = required;
    newArgument.type = type;
    newArgument.helpText = helpText;
    newArgument.results = new DataArray();

    m_argumentList.push_back(newArgument);

    return true;
}

/**
 * @brief convert argument-values
 *
 * @param value string-value
 * @param requiredType required type for the argument
 *
 * @return nullptr, if converting failed, else data-item with the converted value
 */
DataItem*
ArgParser::convertValue(const std::string &value,
                        const ArgParser::ArgType requiredType)
{
    // string value
    if(requiredType == ArgType::STRING_TYPE) {
        return new DataValue(value);
    }

    // long/int value
    if(requiredType == ArgType::INT_TYPE)
    {
        char* err = nullptr;
        const char* charValue = value.c_str();

        // convert to long-value
        const long longValue = std::strtol(charValue, &err, 10);
        if(std::string(err).size() != 0) {
            return nullptr;
        }

        return new DataValue(longValue);
    }

    // double/floag value
    if(requiredType == ArgType::FLOAT_TYPE)
    {
        char* err = nullptr;
        const char* charValue = value.c_str();

        // convert to double-value
        const double doubleValue = std::strtod(charValue, &err);
        if(std::string(err).size() != 0) {
            return nullptr;
        }

        return new DataValue(doubleValue);
    }

    // bool value
    if(requiredType == ArgType::BOOL_TYPE)
    {
        // convert true
        if(value == "true"
                || value == "True"
                || value == "1")
        {
            return new DataValue(true);
        }

        // convert false
        if(value == "false"
                || value == "False"
                || value == "0")
        {
            return new DataValue(false);
        }

        // if nothing match, it is no boolean
        return nullptr;
    }

    return nullptr;
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
ArgParser::parse(const int argc,
                 const char* argv[])
{
    m_positionCounter = 0;

    int i = 1;
    while(i < argc)
    {
        const std::string currentArgument(argv[i]);

        if(currentArgument.at(0) == '-')
        {
            // get and check identifier
            ArgParser::ArgDefinition* argIdent = getArgument(currentArgument);
            if(argIdent == nullptr)
            {
                LOG_ERROR("unknown argument: " + currentArgument);
                return false;
            }

            // check if there is a value for the identifier
            if(i+i == argc)
            {
                LOG_ERROR("flag has no value: " + currentArgument);
                return false;
            }

            // get value
            const std::string currentValue(argv[i+1]);

            // convert value
            DataItem* convertedValue = convertValue(currentValue, argIdent->type);
            if(convertedValue == nullptr)
            {
                LOG_ERROR("argument has the false type: " + currentArgument);
                return false;
            }

            // add converted value to results
            argIdent->results->append(convertedValue);

            i += 2;
        }
        else
        {
            uint32_t counter = 0;
            for(uint64_t j = 0; j < m_argumentList.size(); j++)
            {
                if(m_argumentList[j].withoutFlag == true)
                {
                    ArgParser::ArgDefinition* argIdent = &m_argumentList[j];
                    if(m_positionCounter == counter)
                    {
                        // convert value
                        DataItem* convertedValue = convertValue(currentArgument, argIdent->type);
                        if(convertedValue == nullptr)
                        {
                            LOG_ERROR("argument has the false type: " + currentArgument);
                            return false;
                        }

                        // add converted value to results
                        argIdent->results->append(convertedValue);

                        // update counter
                        m_positionCounter++;
                        j = m_argumentList.size();
                    }

                    counter++;
                }
            }

            i += 1;
        }
    }

    // check if all requirements are satisfied
    for(uint32_t i = 0; i < m_argumentList.size(); i++)
    {
        if(m_argumentList[i].results->size() == 0
                && m_argumentList[i].required)
        {
            LOG_ERROR("argument is required but was not set: "
                      + m_argumentList[i].longIdentifier);
            return false;
        }
    }

    return true;
}

/**
 * @brief ArgParser::getNumberOfValues
 * @param identifier
 * @return
 */
uint64_t
ArgParser::getNumberOfValues(const std::string &identifier)
{
    ArgParser::ArgDefinition* arg = getArgument(identifier);
    if(arg == nullptr) {
        return 0;
    }

    return arg->results->size();
}

/**
 * @brief get parsed string values of an identifier
 *
 * @param identifier regested identifier without "--" or "-"
 *
 * @return list of parsed string values
 */
const std::vector<std::string>
ArgParser::getStringValues(const std::string &identifier)
{
    std::vector<std::string> result;

    // get registered argument
    ArgParser::ArgDefinition* arg = getArgument(identifier);
    if(arg == nullptr) {
        return result;
    }

    // check argument-type
    if(arg->type != STRING_TYPE) {
        return result;
    }

    // build list with all results
    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->get(i)->getString());
    }

    return result;
}

/**
 * @brief get parsed long values of an identifier
 *
 * @param identifier regested identifier without "--" or "-"
 *
 * @return list of parsed long values
 */
const std::vector<long>
ArgParser::getIntValues(const std::string &identifier)
{
    std::vector<long> result;

    // get registered argument
    ArgParser::ArgDefinition* arg = getArgument(identifier);
    if(arg == nullptr) {
        return result;
    }

    // check argument-type
    if(arg->type != INT_TYPE) {
        return result;
    }

    // build list with all results
    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->get(i)->getLong());
    }

    return result;
}

/**
 * @brief get parsed double values of an identifier
 *
 * @param identifier regested identifier without "--" or "-"
 *
 * @return list of parsed double values
 */
const std::vector<double>
ArgParser::getFloatValues(const std::string &identifier)
{
    std::vector<double> result;

    // get registered argument
    ArgParser::ArgDefinition* arg = getArgument(identifier);
    if(arg == nullptr) {
        return result;
    }

    // check argument-type
    if(arg->type != FLOAT_TYPE) {
        return result;
    }

    // build list with all results
    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->get(i)->getDouble());
    }

    return result;
}

/**
 * @brief get parsed bool values of an identifier
 *
 * @param identifier regested identifier without "--" or "-"
 *
 * @return list of parsed bool values
 */
const std::vector<bool>
ArgParser::getBoolValues(const std::string &identifier)
{
    std::vector<bool> result;

    // get registered argument
    ArgParser::ArgDefinition* arg = getArgument(identifier);
    if(arg == nullptr) {
        return result;
    }

    // check argument-type
    if(arg->type != BOOL_TYPE) {
        return result;
    }

    // build list with all results
    for(uint32_t i = 0; i < arg->results->size(); i++)
    {
        result.push_back(arg->results->get(i)->getBool());
    }

    return result;
}

/**
 * @brief get a registered argument
 *
 * @param identifier identifier of the argument without "--" or "-"
 *
 * @return nullptr, if identifier is unknown, else pointer to the registered argument
 */
ArgParser::ArgDefinition*
ArgParser::getArgument(const std::string &identifier)
{
    for(uint32_t i = 0; i < m_argumentList.size(); i++)
    {
        if(m_argumentList.at(i).longIdentifier == identifier
                || m_argumentList.at(i).shortIdentifier == identifier
                || m_argumentList.at(i).longIdentifier == "--" + identifier
                || m_argumentList.at(i).shortIdentifier == "-" + identifier)
        {
            return &m_argumentList.at(i);
        }
    }

    return nullptr;
}

}
}
