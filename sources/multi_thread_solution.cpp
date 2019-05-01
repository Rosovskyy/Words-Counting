//
// Created by Serhiy Rosovskyy on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"
#include "../headers/archive_functions.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "Wrong number of arguments!" << std::endl;
        std::cout << "The format is following: <number of threads> <input file> .." << std::endl;
        exit(-2);
    }

    int thread_num = 0;
    try {
        thread_num = std::atoi(argv[1]);
    } catch (std::bad_cast& bc) {
        std::cerr << "The type of first argument is incorrect" << std::endl;
        exit(-2);
    }

    try {
        if (thread_num < 1) {
            throw "Incorrect number of threads";
        }
    } catch (char *str) {
        std::cout << str << std::endl;
        exit(-2);
    }

    std::string filename = argv[2];
    config conf_file = read_file(filename);
    std::string ext = extension(conf_file.in_file);
    std::string file;
    if (ext == "zip") {
        extract(conf_file.in_file);
        file = read_archive_entries(conf_file.in_file);
    } else {
        file = conf_file.in_file;
    }
    std::cout << file << " FILE:" << std::endl;
    std::vector<std::string> words;
    auto before = get_current_time_fenced();
    try {
        words = read_txt_file(file);
    } catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 3;
    }
    std::map<std::string, int> result = run_multi_thread_solution(words, thread_num);

    std::vector<std::pair<std::string, int>> data(result.begin(), result.end());
    std::sort(data.begin(), data.end(), words_compare);
    std::vector<std::pair<std::string, int>> res = data;
    write_to_file(conf_file.out_by_name, res);
    std::vector<std::pair<std::string, int>> data_number(result.begin(), result.end());
    std::sort(data_number.begin(), data_number.end(), number_compare);
    std::vector<std::pair<std::string, int>> by_number = data_number;

    auto total_time = get_current_time_fenced() - before;
    std::cout << "Total time: " << to_us(total_time) << std::endl;
    std::cout << "\n" << std::endl;


    return 0;
}