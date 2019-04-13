//
// Created by Serhii Rosovskyi on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"


void counting_process(std::vector<std::string> words, std::vector<std::map<std::string, int>> &res, std::mutex &m) {
    std::map<std::string, int> word_map;
    for(const std::string & word : words) {
        word_map[word]++;
    }

    m.lock();
    res.emplace_back(word_map);
    m.unlock();
}

std::map<std::string, int> merge_two_maps(std::map<std::string, int> first, std::map<std::string, int> second) {
    for (auto el : first) {
        if (!(second.find(el.first) == second.end())) {
            first[el.first] += second[el.first];
        }
    }

    for (auto el : second) {
        if (first.find(el.first) == first.end()) {
            first[el.first] = el.second;
        }
    }

    return first;
}

std::map<std::string, int> run_multi_thread_solution(std::vector<std::string> words, int thread_num) {

    std::mutex m;
    std::vector<std::map<std::string, int>> res;
    std::vector<std::thread> threads;

    int step = floor(words.size() / thread_num);
    int start = 0, finish = 0;
    for (int i = 0; i < thread_num - 1; ++i) {
        std::vector<std::string> part = slice(words, start, finish += step);
        print(part);
        threads.emplace_back(counting_process, part, std::ref(res), std::ref(m));
        start = finish + 1;
        finish++;
    }

    threads.emplace_back(counting_process, slice(words, finish, words.size() - 1), std::ref(res), std::ref(m));

    for (int i = 0; i < thread_num; i++) {
        threads[i].join();
    }

////    threads.clear();
////    std::vector<std::thread> threads;
////    bool sign = true
////    for (int i = 0; i < ceil(log2(thread_num)); i++) {
////
////    }
//
    for (int i = 0; i < res.size(); i++) {
        printMap(res[i]);
        std::cout << "\n" << std::endl;
    }

    std::map<std::string, int> result = res[0];
    for (int i = 1; i < res.size(); i++) {
        result = merge_two_maps(result, res[i]);
    }

     return result;
}


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