#include <curl/curl.h>
#include <iostream>

int main(void) {
    CURL* curl = curl_easy_init();
    CURLcode res_code;

    if (!curl) {
        std::cout << "Возникла ошибка!" << std::endl;

        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.telegram.org/bot6316255395:AAG1MUjxfb7Int3uBNvSg8P_ciJ-cbN6DKQ/sendmessage?chat_id=5234933306&text=Саша,_а_ты_уроки_сделал?");

    res_code = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    std::cout << res_code;

    return 0;
}