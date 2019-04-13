//
// Created by Serhii Rosovskyi on 4/13/19.
//

#ifndef CPP_LAB_4_WORD_COUNT_WORD_COUNT_H
#define CPP_LAB_4_WORD_COUNT_WORD_COUNT_H
#include "../headers/helpers.h"

std::map<std::string, int> run_one_thread_solution(std::vector<std::string> words);
std::map<std::string, int> run_multi_thread_solution(std::vector<std::string> words, int thread_num);

#endif //CPP_LAB_4_WORD_COUNT_WORD_COUNT_H
