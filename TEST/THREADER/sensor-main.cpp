#include <iostream>
#include <vector>
#include <thread>

using namespace std;

// TODO: Write a function to read 5 sensors for Group 1
void readGroup1(vector<float>& temps, vector<float>& moistures) {
    // TODO: Loop 5 times to read each sensor
    for (int i = 0; i < 5; ++i) {
        // TODO: For each sensor:
        //    - Simulate reading temperature (assign some value)
        temps[i] = 20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0f));
        //    - Simulate reading moisture (assign some value)
        moistures[i] = 30.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0f));
        //    - Print sensor number and values
        cout << "Group 1 - Sensor " << i + 1 << ": "
             << "Temperature = " << temps[i] << "°C, "
             << "Moisture = " << moistures[i] << "%" << endl;
    }
}

// TODO: Write a function to read 8 sensors for Group 2
void readGroup2(vector<float>& temps, vector<float>& moistures) {
    for (int i = 0; i < 8; ++i) {
        temps[i] = 20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0f));
        moistures[i] = 30.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.0f));
        cout << "Group 2 - Sensor " << i + 1 << ": "
             << "Temperature = " << temps[i] << "°C, "
             << "Moisture = " << moistures[i] << "%" << endl;
    }
}

int main() {
    // TODO: Create vectors to hold 5 temps and moistures for Group 1
	vector<float> group1Temps(5);
	vector<float> group1Moistures(5);
    // TODO: Create vectors to hold 8 temps and moistures for Group 2
	vector<float> group2Temps(8);
	vector<float> group2Moistures(8);

    // TODO: Create thread to run readGroup1 function
	thread group1Thread(readGroup1, ref(group1Temps), ref(group1Moistures));
	// TODO: Create thread to run readGroup2 function
	thread group2Thread(readGroup2, ref(group2Temps), ref(group2Moistures));

    // TODO: Wait for both threads to finish (join)
	group1Thread.join();
	group2Thread.join();

    // TODO: Print summary of all sensor readings for both groups
	cout << "Group 1 Sensor Readings:" << endl;
	for (size_t i = 0; i < group1Temps.size(); ++i) {
	    cout << "Sensor " << i + 1 << ": "
	         << "Temperature = " << group1Temps[i] << "°C, "
	         << "Moisture = " << group1Moistures[i] << "%" << endl;
	}

	cout << "Group 2 Sensor Readings:" << endl;
	for (size_t i = 0; i < group2Temps.size(); ++i) {
	    cout << "Sensor " << i + 1 << ": "
	         << "Temperature = " << group2Temps[i] << "°C, "
	         << "Moisture = " << group2Moistures[i] << "%" << endl;
	}

    return 0;
}
