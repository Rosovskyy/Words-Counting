//
// Created by Serhii Rosovskyi on 4/13/19.
//

#ifndef CPP_LAB_4_WORD_COUNT_HEALPERS_H
#define CPP_LAB_4_WORD_COUNT_HEALPERS_H

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <map>
#include <math.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <mutex>


struct config {
    std::string in_file;
    std::string out_by_name;
    std::string out_by_number;
    int indexing_threads;
    int merging_threads;
};

inline std::chrono::steady_clock::time_point get_current_time_fenced() {
    assert(std::chrono::steady_clock::is_steady &&
           "Timer should be steady (monotonic).");
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::steady_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

void print(std::vector<std::string> const &string);
void printMap(std::map<std::string, int> map);
std::vector<std::string> read_txt_file(std::string const &path);
bool isNotAlpha(char c);
std::vector<std::string> slice(std::vector<std::string> const &data, int m, int n);

std::string extension(std::string file);
void write_to_file(const std::string &filename, std::vector<std::pair<std::string, int>> &words);
bool words_compare(std::pair<std::string, int> &first, std::pair<std::string, int> &second);
bool number_compare(std::pair<std::string, int> &first, std::pair<std::string, int> &second);
config read_file(std::string filename);

#endif //CPP_LAB_4_WORD_COUNT_HELPERS_H
