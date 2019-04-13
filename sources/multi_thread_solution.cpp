//
// Created by Serhiy Rosovskyy on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"

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



    for (int i = 2; i < argc; i++) {
        std::string filename = argv[i];
        std::cout << filename << " FILE:" << std::endl;
        std::vector<std::string> words;
        auto before = get_current_time_fenced();
        try {
            words = read_txt_file(filename);
        } catch (std::exception &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return 3;
        }
        std::map<std::string, int> result = run_multi_thread_solution(words, thread_num);

        write_to_file(result, i-1);

        auto total_time = get_current_time_fenced() - before;
        std::cout << "Total time: " << to_us(total_time) << std::endl;
        std::cout << "\n" << std::endl;
    }


    return 0;
}