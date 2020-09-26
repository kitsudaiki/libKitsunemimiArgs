/**
 *  @file       arg_parser.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>

namespace Kitsunemimi
{
class DataItem;
class DataArray;
namespace Args
{
class ArgParser_Test;
class SubCommand;

class ArgParser
{
public:
    ArgParser(const std::string &version = "");
    ~ArgParser();

    // register
    bool registerPlain(const std::string &identifier,
                       const std::string &helpText);
    bool registerString(const std::string &identifier,
                        const std::string &helpText,
                        bool required = false,
                        bool withoutFlag = false);
    bool registerInteger(const std::string &identifier,
                         const std::string &helpText,
                         bool required = false,
                         bool withoutFlag = false);
    bool registerFloat(const std::string &identifier,
                       const std::string &helpText,
                       bool required = false,
                       bool withoutFlag = false);
    bool registerBoolean(const std::string &identifier,
                         const std::string &helpText,
                         bool required = false,
                         bool withoutFlag = false);

    // parse
    bool parse(const int argc, char *argv[]);
    bool parse(const int argc, const char* argv[]);

    // getter
    uint64_t getNumberOfValues(const std::string &identifier);
    bool wasSet(const std::string &identifier);
    const std::vector<std::string> getStringValues(const std::string &identifier);
    const std::vector<long> getIntValues(const std::string &identifier);
    const std::vector<double> getFloatValues(const std::string &identifier);
    const std::vector<bool> getBoolValues(const std::string &identifier);

    const std::string getStringValue(const std::string &identifier);
    long getIntValue(const std::string &identifier);
    double getFloatValue(const std::string &identifier);
    bool getBoolValue(const std::string &identifier);

private:
    friend ArgParser_Test;
    friend SubCommand;

    enum ArgType
    {
        NO_TYPE,
        STRING_TYPE,
        INT_TYPE,
        FLOAT_TYPE,
        BOOL_TYPE
    };

    struct ArgDefinition
    {
        bool withoutFlag = false;
        bool required = false;
        bool hasValue = false;
        bool wasSet = false;
        std::string longIdentifier = "";
        std::string shortIdentifier = "";
        ArgType type = STRING_TYPE;
        std::string helpText = "";

        DataArray* results = nullptr;
    };

    uint32_t m_positionCounter = 0;
    std::string m_version = "";
    std::vector<ArgDefinition> m_argumentList;

    const std::string convertType(ArgType type);
    void print(const std::string &commandName);
    bool precheckFlags(const int argc, const char* argv[]);

    ArgDefinition* getArgument(const std::string &identifier);
    bool registerArgument(const std::string &identifier,
                          const std::string &helpText,
                          const ArgType type,
                          bool required,
                          bool withoutFlag,
                          bool hasValue);

    DataItem* convertValue(const std::string &value,
                           const ArgType requiredType);
};

}
}

#endif // ARG_PARSER_H
