#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <string>
#include <iomanip>
#include <omp.h>
using namespace std;

/*
	Important Notes:
	Ensure installation of omp.h.
	In a linux system, try "sudo apt-get install libomp-dev"

	To compile do:
	"g++ -fopenmp omp_task_manager.cpp"

	Main difference:
	- omp allows function inputs
	- uses critical keyword and more familiar blocks of code for paralellism
	- defines the "this" keyword
*/

// Basically code everything the same.

// Struct to hold task result information
struct TaskInfo {
	int thread_id;
	string task_name;
	double execution_time_ms;
	string result;
};

// Shared data
vector<TaskInfo> task_results;
vector<int> completion_order;

double get_duration_ms(chrono::steady_clock::time_point start,
					  chrono::steady_clock::time_point end) {
	return chrono::duration<double, milli>(end - start).count();
}

// Task 1: Compute factorial
void task_factorial(int thread_id) {
	string status = "[Thread " + to_string(thread_id) + "] Starting factorial task...\n";
	cout << status << flush;
	auto start = chrono::steady_clock::now();
	int n = 5;
	unsigned long long result = 1;
	for (int i = 1; i <= n; ++i) result *= i;
	this_thread::sleep_for(chrono::milliseconds(15));
	auto end = chrono::steady_clock::now();
	string done_msg = "[Thread " + to_string(thread_id) + "] Done. Result = " + to_string(result) + "\n";
	cout << done_msg << flush;

	// Critical keyword
	#pragma omp critical
	{
		task_results.push_back({thread_id, "Factorial", get_duration_ms(start, end), to_string(result)});
		completion_order.push_back(thread_id);
	}
}

// Task 2: Simulate file scan
void task_file_scan(int thread_id) {
	cout << "[Thread " << thread_id << "] Starting file scan simulation...\n" << flush;
	auto start = chrono::steady_clock::now();
	int lines = 5;
	for (int i = 1; i <= lines; ++i) {
		cout << "[Thread " << thread_id << "] Line " << i << ": Simulated file content\n" << flush;
		this_thread::sleep_for(chrono::milliseconds(15));
	}
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done scanning.\n" << flush;

	#pragma omp critical
	{
		task_results.push_back({thread_id, "File Scan", get_duration_ms(start, end), "Scanned " + to_string(lines) + " lines"});
		completion_order.push_back(thread_id);
	}
}

// Task 3: Sort an array
void task_sort_array(int thread_id) {
	cout << "[Thread " << thread_id << "] Starting array sort task...\n" << flush;
	auto start = chrono::steady_clock::now();
	vector<int> arr = {5, 2, 8, 1, 3};
	sort(arr.begin(), arr.end());
	this_thread::sleep_for(chrono::milliseconds(12));
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done sorting array.\n" << flush;

	string result = "Sorted: ";
	for (int v : arr) result += to_string(v) + " ";
	#pragma omp critical
	{
		task_results.push_back({thread_id, "Array Sort", get_duration_ms(start, end), result});
		completion_order.push_back(thread_id);
	}
}

// Task 4: Simulate loading resources
void task_load_resources(int thread_id) {
	cout << "[Thread " << thread_id << "] Simulating resource loading...\n" << flush;
	auto start = chrono::steady_clock::now();
	this_thread::sleep_for(chrono::milliseconds(25));
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done loading resources.\n" << flush;

	#pragma omp critical
	{
		task_results.push_back({thread_id, "Resource Load", get_duration_ms(start, end), "Loaded"});
		completion_order.push_back(thread_id);
	}
}

// Same idea as before but this time with OPEN_MP
int main() {
	int num_threads = 4;
	int thread_ids[4] = {1, 2, 3, 4};

	auto global_start = chrono::steady_clock::now();

	// Start parallel threads
	#pragma omp parallel num_threads(num_threads)
	{
		int tid = omp_get_thread_num();
		if (tid == 0)	  task_factorial(thread_ids[tid]);
		else if (tid == 1) task_file_scan(thread_ids[tid]);
		else if (tid == 2) task_sort_array(thread_ids[tid]);
		else if (tid == 3) task_load_resources(thread_ids[tid]);
	}

	auto global_end = chrono::steady_clock::now();

	cout << "Main Thread: All threads completed.\n\n";
	cout << "Execution Summary:\n";
	for (int idx : completion_order) {
		for (const auto& task : task_results) {
			if (task.thread_id == idx) {
				cout << " - Thread " << task.thread_id
						  << ": Task = " << setw(12) << left << task.task_name
						  << "| Time = " << fixed << setprecision(2) << task.execution_time_ms << " ms"
						  << " | Result = " << task.result << "\n";
				break;
			}
		}
	}

	cout << "\nTotal elapsed time: "
			  << get_duration_ms(global_start, global_end) << " ms\n";

	return 0;
}
