#include "../headers/helpers.h"

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

    std::vector<std::string> words;
    try {
        words = read_txt_file(filename);
    } catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 3;
    }

    print(words);

    return 0;
}