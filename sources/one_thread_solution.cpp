//
// Created by Serhii Rosovskyi on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"
#include "../headers/archive_functions.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Wrong number of arguments!" << std::endl;
        std::cout << "The format is following: <input file> .." << std::endl;
        exit(-2);
    }

    std::string filename = argv[1];
    config conf_file = read_file(filename);
    std::string ext = extension(conf_file.in_file);
    std::string file;
    if (ext == "zip") {
        extract(conf_file.in_file);
        file = read_archive_entries(conf_file.in_file);
    } else {
        file = conf_file.in_file;
    }
    std::cout << ext << std::endl;
    std::cout << file << " FILE:" << std::endl;
    std::vector<std::string> words;
    auto before = get_current_time_fenced();
    try {
        words = read_txt_file(file);
    } catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 3;
    }

    std::map<std::string, int> result = run_one_thread_solution(words);
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