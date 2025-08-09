#include <additionally/_string.hpp>
#include <cstring>

namespace additionally {
    Splitter::Splitter(const char* str, char sep) {
        this->separators[0] = str;

        this->sep_is_char = true;

        int k = 1;

        const char* ptr;
        for (ptr = str; *ptr != '\0'; ptr++)
            if (*ptr == sep) {
                this->separators[k] = ptr;
                k++;
            }

        this->separators[k] = ptr;
        this->length = k - 1;
    }

    Splitter::Splitter(const char* str_begin, const char* str_end, char sep) {
        this->separators[0] = str_begin;

        this->sep_is_char = true;

        int k = 1;

        for (const char* ptr = str_begin; ptr < str_end; ptr++)
            if (*ptr == sep) {
                this->separators[k] = ptr;
                k++;
            }

        this->separators[k] = str_end;
        this->length = k - 1;
    }

    Splitter::Splitter(const char* str, const char* sep, bool str_as_char_array) {
        this->separators[0] = str;

        int sep_len = strlen(sep);
        int k = 1;

        const char* ptr;

        if (str_as_char_array) {
            this->sep_is_char = true;

            for (ptr = str; *ptr != '\0' and k - 1 < sep_len; ptr++)
                if (*ptr == sep[k - 1]) {
                    this->separators[k] = ptr;
                    k++;
                }

            for (; *ptr != '\0'; ptr++);

            this->separators[k] = ptr;
            this->length = k - 1;

        } else {
            this->sep_is_char = false;

            for (ptr = str; *ptr != '\0'; ptr++)
                if (not strncmp(ptr, sep, sep_len)) {
                    this->separators[k] = ptr;
                    k++;

                    ptr += sep_len;
                    this->separators[k] = ptr;
                    k++;
                }

            this->separators[k] = ptr;
            this->length = k / 2;
        }
    }
/*
    Splitter::Splitter(const char* str, const char* sep_begin, const char* sep_end, bool str_as_char_array) {
        this->separators[0] = str;

        int sep_len = sep_end - sep_begin;
        int k = 0;

        char* ptr;

        if (str_as_char_array) {
            this->sep_is_char = true;

            for (const char* ptr = str; *ptr != '\0' and k < sep_len; ptr++)
                if (*ptr == sep_begin[k]) {
                    this->separators[k] = ptr;
                    k++;
                }
            
            for (; *ptr != '\0'; ptr++);

            this->separators[k] = ptr;
            this->length = k - 1;

        } else {
            this->sep_is_char = false;

            for (const char* ptr = str; *ptr != '\0'; ptr++)
                if (not strncmp(ptr, sep_begin, sep_len)) {
                    this->separators[k] = ptr;
                    k++;

                    ptr += sep_len;
                    this->separators[k] = ptr;
                    k++;
                }

            this->separators[k] = ptr;
            this->length = k / 2;
        }
    }
*/
    Splitter::Splitter(const char* str_begin, const char* str_end, const char* sep, bool str_as_char_array) {
        this->separators[0] = str_begin;

        int sep_len = strlen(sep);
        int k = 1;

        if (str_as_char_array) {
            this->sep_is_char = true;

            for (const char* ptr = str_begin; ptr < str_end and k - 1 < sep_len; ptr++)
                if (*ptr == sep[k - 1]) {
                    this->separators[k] = ptr;
                    k++;
                }

            this->length = k - 1;

        } else {
            this->sep_is_char = false;

            for (const char* ptr = str_begin; ptr < str_end; ptr++)
                if (not strncmp(ptr, sep, sep_len)) {
                    this->separators[k] = ptr;
                    k++;

                    ptr += sep_len;
                    this->separators[k] = ptr;
                    k++;
                }

            this->length = k / 2;
        }

        this->separators[k] = str_end;
    }

    Splitter::Splitter(const char* str_begin, const char* str_end, const char* sep_begin, const char* sep_end, bool str_as_char_array) {
        this->separators[0] = str_begin;

        int sep_len = sep_end - sep_begin;
        int k = 1;

        if (str_as_char_array) {
            this->sep_is_char = true;

            for (const char* ptr = str_begin; ptr < str_end and k - 1 < sep_len; ptr++)
                if (*ptr == sep_begin[k - 1]) {
                    this->separators[k] = ptr;
                    k++;
                }

            this->length = k - 1;

        } else {
            this->sep_is_char = false;

            for (const char* ptr = str_begin; ptr < str_end; ptr++)
                if (not strncmp(ptr, sep_begin, sep_len)) {
                    this->separators[k] = ptr;
                    k++;

                    ptr += sep_len;
                    this->separators[k] = ptr;
                    k++;
                }

            this->length = k / 2;
        }

        this->separators[k] = str_end;
    }

    Splitter::Splitter(const char* str, const char** seps_begin, const char** seps_end) {
        this->separators[0] = str;

        int seps_len = (seps_begin - seps_end) / sizeof(char*);
        int sep_len = strlen(*seps_begin);
        int k = 1;
        int l = 0;

        this->sep_is_char = false;

        const char* ptr;
        for (ptr = str; *ptr != '\0' and k - 1 < seps_len; ptr++)
            if (not strncmp(ptr, seps_begin[l], sep_len)) {
                this->separators[k] = ptr;
                k++;

                ptr += sep_len;
                this->separators[k] = ptr;

                l++;
                sep_len = strlen(seps_begin[l]);
            }

        for (; *ptr != '\0'; ptr++);

        this->separators[k] = ptr;
        this->length = k / 2;
    }

    Splitter::Splitter(const char* str_begin, const char* str_end, const char** seps_begin, const char** seps_end) {
        this->separators[0] = str_begin;

        int seps_len = (seps_begin - seps_end) / sizeof(char*);
        int sep_len = strlen(*seps_begin);
        int k = 1;
        int l = 0;

        this->sep_is_char = false;

        for (const char* ptr = str_begin; ptr < str_end and k < seps_len; ptr++)
            if (not strncmp(ptr, seps_begin[l], sep_len)) {
                this->separators[k] = ptr;
                k++;

                ptr += sep_len;
                this->separators[k] = ptr;

                l++;
                sep_len = strlen(seps_begin[l]);
            }

        this->separators[k] = str_end;
        this->length = k / 2;
    }

    Splitter::~Splitter() {}

    std::pair<const char*, const char*> Splitter::at(int index) const {
        if (this->sep_is_char)
            return std::pair<const char*, const char*>(this->separators[index], this->separators[index + 1]);
        else
            return std::pair<const char*, const char*>(this->separators[index * 2], this->separators[index * 2 + 1]);
    }

    int Splitter::getLength() const {
        return this->length;
    }
}