# Words-Couting

## Підрахунку кількість слів у текстовому файлі

## Introduction
This program counts the number of each words in input files usin multithreading.

## Installation and compilation
  ```bash
  $ git clone https://github.com/Rosovskyy/Words-Counting
  $ cd Words-Counting
  $ mkdir build
  $ cd build
  $ cmake -G"Unix Makefiles" ..
  $ make
  ```

## Running
    <i>(Inside the <b>bin</b> directory)</i>
    ### CPP FILE
  <b>One thread file:</b><br>
    ```bash
    $ ./integrate_one_thread <input_file>
    ```<br>
  <b>Multi thread file:</b><br>
    ```bash
    $ ./integrate_multi_thread <number_of_threads> <input file>
    ```<br>
  ### Python script
    Multiple threads
    ```bash
    $ python3 script.py <number_of_threads_for_multiple_threads_program> <times_to_run_the_program> <multiple_threads/both> <input_file>
    ```<br>
    
    One thread
    ```bash
    $ python3 script.py <times_to_run_the_program> <input_file>
    ```
    


## License and copyright
© Serhii Rosovskyi, student of the Ukrainian Catholic University
