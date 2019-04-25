import subprocess
import sys


def parse_result(result):
    return [int(s) for s in result.replace('\n', ' ').split(' ') if s.isdigit()]


def check_results(data):
    with open('../results/result1.txt', 'r') as f:
        res = f.readlines()
    f.close()
    return data == res


def run_one_time(one_thread, input_file):
    subprocess.Popen([one_thread, input_file], stdout=subprocess.PIPE).communicate()[0].decode('utf-8')
    with open('../results/result1.txt', 'r') as f:
        data = f.readlines()
    f.close()
    return data


def run_multi_thread_solution(times, multi_thread, num_of_threads, input_file, one_thread):
    results_are_same_1 = True
    result = 0
    min_multi_thread = [0, 0, sys.maxsize]
    data = run_one_time(one_thread, input_file)

    for i in range(0, times):
        res_multi = parse_result(subprocess.Popen([multi_thread, num_of_threads, input_file],
                                                  stdout=subprocess.PIPE).communicate()[0].decode('utf-8'))

        if not result:
            result = res_multi[0]
        else:
            results_are_same_1 = check_results(data)

        if res_multi[2] < min_multi_thread[2]:
            min_multi_thread = res_multi

    for i in min_multi_thread:
        print("[" + str(i) + "]")
    if results_are_same_1:
        print("Results are the same for all the multiple solutions runs")
    else:
        print("Results are NOT the same for all the multiple solutions runs")

    return result


def run_one_thread_solution(times, one_thread, input_file):
    min_one_thread = [0, 0, sys.maxsize]
    results_are_same_2 = True
    result = 0
    data = run_one_time(one_thread, input_file)

    for i in range(0, times):
        res_one = parse_result(
            subprocess.Popen([one_thread, input_file], stdout=subprocess.PIPE).communicate()[0].decode('utf-8'))

        print(res_one)

        if not check_results(data):
            results_are_same_2 = False

        if res_one[2] < min_one_thread[2]:
            min_one_thread = res_one

    for i in min_one_thread:
        print("[" + str(i) + "]")
    if results_are_same_2:
        print("Results are the same for all the one solutions runs")
    else:
        print("Results are NOT the same for all the one solutions runs")

    return result


def main():
    if len(sys.argv) != 5:
        print('Usage: <program_name> <number_of_threads_for_multiple_threads_program>'
              ' <times_to_run_the_program> <multiple/both> <input_file>')
        exit(-1)

    one_thread = './one_thread_solution'
    multi_thread = './multi_thread_solution'

    num_of_threads = sys.argv[1]
    times = int(sys.argv[2])
    threads_to_run = sys.argv[3]
    input_file = sys.argv[4]

    run_multi_thread_solution(times, multi_thread, num_of_threads, input_file, one_thread)
    exit(-1)

    if threads_to_run == 'multiple':
        run_multi_thread_solution(times, multi_thread, num_of_threads, input_file, one_thread)
    elif threads_to_run == 'both':
        first = run_one_thread_solution(times, one_thread, input_file)
        second = run_multi_thread_solution(times, multi_thread, num_of_threads, input_file, one_thread)

        if first != second:
            print("\nResults are NOT the same for one thread and multiple threads solutions!")
        else:
            print("\nResults are the same for one thread and multiple threads solutions!")


if __name__ == '__main__':
    main()
