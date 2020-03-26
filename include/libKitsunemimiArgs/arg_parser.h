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

class ArgParser
{
public:
    ArgParser();
    ~ArgParser();

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

    bool parse(const int argc,
               const char* argv[],
               std::string &errorMessage);

    uint64_t getNumberOfValues(const std::string &identifier);
    const std::vector<std::string> getStringValues(const std::string &identifier);
    const std::vector<long> getIntValues(const std::string &identifier);
    const std::vector<double> getFloatValues(const std::string &identifier);
    const std::vector<bool> getBoolValues(const std::string &identifier);

private:
    friend ArgParser_Test;

    enum ArgType
    {
        STRING_TYPE,
        INT_TYPE,
        FLOAT_TYPE,
        BOOL_TYPE
    };

    struct ArgIdentifier
    {
        bool withoutFlag = false;
        bool required = false;
        std::string longIdentifier = "";
        std::string shortIdentifier = "";
        ArgType type = STRING_TYPE;
        std::string helpText = "";

        DataArray* results = nullptr;
    };

    uint32_t m_positionCounter = 0;
    std::vector<ArgIdentifier> m_argumentList;

    ArgIdentifier* getArgument(const std::string &identifier);

    bool registerArgument(const std::string &identifier,
                          const std::string &helpText,
                          const ArgType type,
                          bool required,
                          bool withoutFlag);

    DataItem* convertValue(const std::string &value,
                           const ArgType requiredType);
};

}
}

#endif // ARG_PARSER_H
