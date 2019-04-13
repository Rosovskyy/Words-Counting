//
// Created by Serhii Rosovskyi on 4/13/19.
//
#include "../headers/helpers.h"

bool isNotAlpha(char c) {
    if (isdigit(c)) {
        return 1;
    }
    return isalnum(c) == 0;
}

void print(std::vector<std::string> const &string) {
    for (std::string str: string) {
        std::cout << str << ' ';
    }
    std::cout << '\n';
}

void printMap(std::map<std::string, int> map) {
    for (auto el : map) {
        std::cout << el.first << " " << el.second << std::endl;
    }
}

std::vector<std::string> read_txt_file(std::string const &path) {
    std::vector<std::string> res;
    std::string str;

    std::ifstream file(path);
    auto before = get_current_time_fenced();
    if (file.is_open()) {
        while (file >> str) {
            boost::algorithm::to_lower(str);
            str.erase(std::remove_if(str.begin(), str.end(), isNotAlpha), str.end());
            res.push_back(str);
        }
        file.close();
    } else {
        throw std::invalid_argument("File not found");
    }
    if (res.empty()) {
        throw std::invalid_argument("File is empty");
    }
    auto reading_time = get_current_time_fenced() - before;
    std::cout << "Reading time: " << to_us(reading_time) << std::endl;
    return res;
}

void write_to_file(std::map<std::string, int> words, int number) {
    std::ofstream file;
    file.open("../results/result" + std::to_string(number) + ".txt");
    for (auto el : words) {
        file << el.first << " " << el.second << std::endl;
    }
}