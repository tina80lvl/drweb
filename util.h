//
// Created by  Valentina Smirnova on 9/22/21.
//

#ifndef GRAPH_UTIL_H
#define GRAPH_UTIL_H

#include <cstring>
#include <vector>

#endif //GRAPH_UTIL_H

std::string trim(std::string s) {
    // удаляем пробелы и табы с начала строки:
    size_t l = s.length();
    int i = 0, j;
    while ((s[i] == ' ') || (s[i] == '\t')) {
        i++;
    }
    if (i > 0) {
        for (j = 0; j < l; j++) {
            s[j] = s[j + i];
        }
        s[j] = '\0';
    }

    // удаляем пробелы и табы с конца строки:
    i = l - 1;
    while ((s[i] == ' ') || (s[i] == '\t')) {
        --i;
    }
    if (i < (l - 1)) {
        s[i + 1] = '\0';
    }
    return s;
}


std::string trim_code(const std::string &s) {
    std::string tmp;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '{') {
            while (s[i + 1] != '}') {
                tmp += s[++i];
            }
        }
    }
    return tmp;
}


std::vector<std::string> parse_string_list(const std::string &s, const char del = ',') {
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string tmp;

    if (s.find(del) == s.length()) {
        v.push_back(s);
        return v;
    }
    while (getline(ss, tmp, del)) {
        v.push_back(tmp);
    }

    return v;
}

std::string vec_to_string(const std::vector<std::string> &v) {
    std::string s;
    for (const auto &p: v) {
        s += p + " ";
    }
    s.pop_back();
    return s;
}


