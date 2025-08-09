#include <json/parser.hpp>
#include <cstring>

namespace json {
    JsonTypes Parser::from_string_to_json_types(const char* begin, const char* end) {
        if ((*begin == '"' and *(end - 1) == '"') or (*begin == '\'' and *(end - 1) == '\''))
            return JsonTypes(std::string(begin + 1, end - 1));
        else if (not strncmp(begin, "true", 4))
            return JsonTypes(true);
        else if (not strncmp(begin, "false", 5))
            return JsonTypes(false);
        else if (not strncmp(begin, "null", 4))
            return JsonTypes();
        else 
            return JsonTypes(std::stod(std::string(begin, end)));
    }
}