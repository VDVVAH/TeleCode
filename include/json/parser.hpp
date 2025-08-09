#ifndef __JSON_PARSER_HPP__
#define __JSON_PARSER_HPP__

#include <json/data_types.hpp>

namespace json {
    class Parser {
    public:
        static JsonTypes from_string_to_json_types(const char* begin, const char* end);
    };
}

#endif 