#ifndef __GET_THREAD_ID_STR_H__
#define __GET_THREAD_ID_STR_H__

#include <sstream>
#include <string>
#include <thread>

/*----------------------------------------------------------------------------*/

inline std::string get_thread_id_str()
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string id_str = oss.str();

    if (id_str.length() > 2 && id_str.substr(0, 2) == "0x") {
        std::size_t id_hash = std::hash<std::thread::id>{}(
            std::this_thread::get_id()
        );
        return std::to_string(id_hash % 10000);
    }

    std::string numeric_part;
    for (char c : id_str) {
        if (std::isdigit(c)) {
            numeric_part += c;
        }
    }

    if (!numeric_part.empty()) {
        if (numeric_part.length() > 4) {
            return numeric_part.substr(numeric_part.length() - 4);
        }
        return numeric_part;
    }

    std::size_t id_hash = std::hash<std::thread::id>{}(
        std::this_thread::get_id()
    );
    return std::to_string(id_hash % 10000);
}

/*----------------------------------------------------------------------------*/

#endif // __GET_THREAD_ID_STR_H__
