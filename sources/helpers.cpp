//
// Created by Serhii Rosovskyi on 4/13/19.
//
#include "../headers/helpers.h"
#include <boost/locale.hpp>

bool isNotAlpha(char c) {
    if (isdigit(c)) {
        return 1;
    }
    return isalnum(c) == 0;
}

std::string extension(std::string file) {
    return file.substr(file.find_last_of('.') + 1, file.length());
}

void print(std::vector<std::string> const &string) {
    for (std::string str: string) {
        std::cout << str << ' ';
    }
    std::cout << '\n';
}

std::vector<std::string> slice(std::vector<std::string> const &data, int m, int n) {
    auto first = data.cbegin() + m;
    auto last = data.cbegin() + n + 1;

    std::vector<std::string> vec(first, last);
    return vec;
}

void printMap(std::map<std::string, int> map) {
    for (auto el : map) {
        std::cout << el.first << " - " << el.second << " ";
    }
    std::cout << "\n" << std::endl;
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

bool number_compare(std::pair<std::string, int> &first, std::pair<std::string, int> &second) {
    return first.second > second.second;
}


bool words_compare(std::pair<std::string, int> &first, std::pair<std::string, int> &second) {
    return first.first < second.first;
}

void write_to_file(const std::string &filename, std::vector<std::pair<std::string, int>> &words) {
    std::ofstream my_file;
    my_file.open(filename);
    for (const auto &i: words)
        my_file << i.first << ":  " << i.second << std::endl;
}

config read_file(std::string filename) {
    config conf{};
    std::string s, indexing, merging;
    std::ifstream file(filename);
    std::vector<std::string> data;

    for (int i = 0; i < 3; ++i) {
        file >> s;
        data.push_back(s.substr(s.find('"') + 1, s.find_last_not_of('"') - s.find('"')));
    }
    file >> s;
    indexing = s.substr(s.find('=') + 1, s.find('\\'));
    file >> s;
    merging = s.substr(s.find('=') + 1, s.find('\\'));

    conf.in_file = data[0];
    conf.out_by_name = data[1];
    conf.out_by_number = data[2];
    conf.merging_threads = stoi(merging);
    conf.indexing_threads = stoi(indexing);
    return conf;
}