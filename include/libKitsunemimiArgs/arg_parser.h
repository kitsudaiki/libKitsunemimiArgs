#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <iostream>
#include <vector>

namespace Kitsunemimi
{
class DataItem;
class DataArray;
namespace Args
{

enum ArgType
{
    STRING_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
    BOOL_TYPE
};

class ArgParser
{
public:
    ArgParser();

    bool addArgument(const std::string &identifier,
                     const std::string &helpText,
                     const ArgType type,
                     bool withoutFlag = false);

    bool parse(int argc, char* argv[]);

    uint64_t getNumberOfValues(const std::string &identifier);
    const std::vector<std::string> getStringValues(const std::string &identifier);
    const std::vector<long> getIntValues(const std::string &identifier);
    const std::vector<double> getFloatValues(const std::string &identifier);
    const std::vector<bool> getBoolValues(const std::string &identifier);

private:
    struct ArgIdentifier
    {
        bool withoutFlag = false;
        std::string longIdentifier = "";
        std::string shortIdentifier = "";
        ArgType type = STRING_TYPE;
        std::string helpText = "";

        DataArray* results = nullptr;
    };

    std::vector<ArgIdentifier> argumentList;

    ArgIdentifier* getArg(const std::string &identifier);
};

}
}

#endif // ARG_PARSER_H
