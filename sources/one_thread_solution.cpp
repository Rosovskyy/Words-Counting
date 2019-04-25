//
// Created by Serhii Rosovskyi on 4/13/19.
//

#include "../headers/helpers.h"
#include "../headers/word_count.h"

int main(int argc, char *argv[]) {

    int err = 0;
     zip *z = zip_open("../zipInput.zip", 0, &err);

    exit(-1);

    if (argc < 2) {
        std::cout << "Wrong number of arguments!" << std::endl;
        std::cout << "The format is following: <input file> .." << std::endl;
        exit(-2);
    }

    for (int i = 1; i < argc; i++) {
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

        std::map<std::string, int> result = run_one_thread_solution(words);
        write_to_file(result, i);
        auto total_time = get_current_time_fenced() - before;
        std::cout << "Total time: " << to_us(total_time) << std::endl;
        std::cout << "\n" << std::endl;
    }



    return 0;
}