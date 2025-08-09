#ifndef __ADDITIONALLY__STRING_HPP__
#define __ADDITIONALLY__STRING_HPP__

#include <map>

namespace additionally {
    class Splitter {
    private:
        bool sep_is_char;
        int length;

#ifdef __ADDITIONALLY_STRING_SPLITTER_DEFAULT_COUNT_OF_SEPARATORS__
        char* separators[__ADDITIONALLY_STRING_SPLITTER_DEFAULT_COUNT_OF_SEPARATORS__]
#else
        const char* separators[32];
#endif

    public:
        Splitter(const char* str, char sep);
        Splitter(const char* str_begin, const char* str_end, char sep);
        Splitter(const char* str, const char* sep, bool str_as_char_array);
        // Splitter(const char* str, const char* sep_begin, const char* sep_end, bool str_as_char_array);
        Splitter(const char* str_begin, const char* str_end, const char* sep, bool str_as_char_array);
        Splitter(const char* str_begin, const char* str_end, const char* sep_begin, const char* sep_end, bool str_as_char_array);
        Splitter(const char* str, const char** seps_begin, const char** seps_end);
        Splitter(const char* str_begin, const char* str_end, const char** seps_begin, const char** seps_end);
        ~Splitter();

        std::pair<const char*, const char*> at(int index) const;

        int getLength() const;
    };
}

#endif