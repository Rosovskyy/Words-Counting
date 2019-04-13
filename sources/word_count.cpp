//
// Created by Serhii Rosovskyi on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"

std::map<std::string, int> run_one_thread_solution(std::vector<std::string> words) {
    std::map<std::string, int> word_map;

    auto before = get_current_time_fenced();

    for(const std::string & word : words) {
        word_map[word]++;
    }

    auto time_to_calculate = get_current_time_fenced() - before;
    std::cout << "Counting the number of numbers: " << to_us(time_to_calculate) << std::endl;

    return word_map;

}