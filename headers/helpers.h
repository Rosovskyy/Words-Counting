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
#include <string>
#include <boost/algorithm/string.hpp>

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
void write_to_file(std::map<std::string, int> words, int number);
bool isNotAlpha(char c);

#endif //CPP_LAB_4_WORD_COUNT_HEALPERS_H
