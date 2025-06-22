#include <iostream> // input output
#include <pthread.h>
#include <vector> // for storage
#include <chrono> // for time calculation
#include <unistd.h> // for sleep/usleep
#include <algorithm>
#include <string> //for string
#include <iomanip> // for setw
using namespace std;

/*
	Very important notes:

	The hardest part is figuring out syntax that works for a concept.
	There was a lot of back and forth from an LLM.
	Though, I believe the work done is incomplete because of a one cpp file limitation.
*/

// Struct to hold task result information
struct s_TaskInfo {
	int thread_id;
	string task_name;
	double execution_time_ms;
	string result;
};

// Shared data
vector<s_TaskInfo> task_results;
vector<int> completion_order;
pthread_mutex_t result_mutex = PTHREAD_MUTEX_INITIALIZER;

// Helper: time in ms
double get_duration_ms(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end) {
	return (chrono::duration<double, milli>(end - start).count());
}

void* task_factorial(void* arg) {
	int f_thread_id = 1; // Hardcoded thread id for consistency
	int n = 10; // Hardcoded factorial input

	string status = "[Thread " + to_string(f_thread_id) + "] Starting factorial task with number " + to_string(n) + "...\n";
	cout << status << flush;

	auto start = chrono::steady_clock::now();
	unsigned long long result = 1;
	for (int i = 1; i <= n; ++i) result *= i;
	usleep(15000); // simulate work (15ms)
	auto end = chrono::steady_clock::now();

	string done_msg = "[Thread " + to_string(f_thread_id) + "] Done. Result = " + to_string(result) + "\n";
	cout << done_msg << flush;

	// Mutex to stop every other thread from putting to global variable
	pthread_mutex_lock(&result_mutex);
	task_results.push_back({f_thread_id, "Factorial", get_duration_ms(start, end), to_string(result)});
	completion_order.push_back(f_thread_id);
	pthread_mutex_unlock(&result_mutex);

	return nullptr;
}


// Thread 2: Simulate file scan
void* task_file_scan(void* arg) {
	int thread_id = *(int*)arg;
	cout << "[Thread " << thread_id << "] Starting file scan simulation...\n" << flush;

	// Start thread clock
	auto start = chrono::steady_clock::now();
	int lines = 5;
	for (int i = 1; i <= lines; ++i) {
		cout << "[Thread " << thread_id << "] Line " << i << ": Simulated file content\n" << flush;
		usleep(15000); // 15ms per line
	}
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done scanning.\n" << flush;

	// Global Mutex Locking for putting into results
	pthread_mutex_lock(&result_mutex);
	task_results.push_back({thread_id, "File Scan", get_duration_ms(start, end), "Scanned " + to_string(lines) + " lines"});
	completion_order.push_back(thread_id);
	pthread_mutex_unlock(&result_mutex);

	return nullptr;
}

// Thread 3: Sort an array
void* task_sort_array(void* arg) {
	int thread_id = *(int*)arg;
	cout << "[Thread " << thread_id << "] Starting array sort task...\n" << flush;
	auto start = chrono::steady_clock::now();
	vector<int> arr = {5, 2, 8, 1, 3};
	sort(arr.begin(), arr.end());
	usleep(12000); // simulate sort time
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done sorting array.\n" << flush;

	string result = "Sorted: ";
	for (int v : arr) result += to_string(v) + " ";

	// Global Mutex Locking for putting into results
	pthread_mutex_lock(&result_mutex);
	task_results.push_back({thread_id, "Array Sort", get_duration_ms(start, end), result});
	completion_order.push_back(thread_id);
	pthread_mutex_unlock(&result_mutex);

	return nullptr;
}

// Thread 4: Simulate loading resources
void* task_load_resources(void* arg) {
	int thread_id = *(int*)arg;

	// Print out thread starting...
	cout << "[Thread " << thread_id << "] Simulating resource loading...\n" << flush;

	auto start = chrono::steady_clock::now();
	usleep(25000); // simulate loading (25ms)
	auto end = chrono::steady_clock::now();
	cout << "[Thread " << thread_id << "] Done loading resources.\n" << flush;

	// Global Mutex Locking for putting into results
	pthread_mutex_lock(&result_mutex);
	task_results.push_back({thread_id, "Loader", get_duration_ms(start, end), "Loaded"});
	completion_order.push_back(thread_id);
	pthread_mutex_unlock(&result_mutex);

	return nullptr;
}

int main() {
	pthread_t threads[4];
	int thread_ids[4] = {1, 2, 3, 4};

	// Start global clock
	auto global_start = chrono::steady_clock::now();

	/*
		Create threads:
		- assign each thread address to pthread_t array.
		- assign null by default for thread attributes (a whole rabbit hole to learn)
		- assign function to do
		- assign thread input (in this case only the id no. but can be changable)
	*/
	pthread_create(&threads[0], nullptr, task_factorial, &thread_ids[0]);
	pthread_create(&threads[1], nullptr, task_file_scan, &thread_ids[1]);
	pthread_create(&threads[2], nullptr, task_sort_array, &thread_ids[2]);
	pthread_create(&threads[3], nullptr, task_load_resources, &thread_ids[3]);

	// Join them for execution. (join by address and set return to null)
	for (int i = 0; i < 4; ++i) {
		pthread_join(threads[i], nullptr);
	}

	// After threads execute count time.
	auto global_end = chrono::steady_clock::now();

	// Print finishing statement
	cout << "Main Thread: All threads completed.\n\n";

	// Print out summary.
	cout << "Execution Summary:\n";

	// Print details in completion order (cease threads)
	pthread_mutex_lock(&result_mutex);
	for (int idx : completion_order) {
		for (const auto& task : task_results) {
			if (task.thread_id == idx) {
				cout << " - Thread " << task.thread_id
						  << ": Task = " << setw(12) << left << task.task_name
						  // Set time to only have two floating points
						  << "| Time = " << fixed << setprecision(2) << task.execution_time_ms << " ms"
						  << " | Result = " << task.result << "\n";
				break;
			}
		}
	}
	pthread_mutex_unlock(&result_mutex);

	cout << "\nTotal elapsed time: " << get_duration_ms(global_start, global_end) << " ms\n";

	// Cease global mutex
	pthread_mutex_destroy(&result_mutex);

	return 0;
}
