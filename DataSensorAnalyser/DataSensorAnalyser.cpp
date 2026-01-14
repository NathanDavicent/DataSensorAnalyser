// DataSensorAnalyser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

const std::string SENTINEL = "QUIT";

// --- Helper function to check for sentinel input (case-insensitive) ---
bool isSentinel(const std::string& input) {
	std::string lower;
	lower.resize(input.size());
	transform(input.begin(), input.end(), lower.begin(), ::tolower);
	return lower == "q" || lower == "quit";
}

// --- Function to show the menu ---
void displayMenu() {
	std::cout << "\n--- Temperature Data Manager ---\n";
	std::cout << "1. Enter temperature values manually\n";
	std::cout << "2. Display all data\n";
	std::cout << "3. Analyze data\n";
	std::cout << "4. Display data sorted (Low to High)\n";
	std::cout << "5. Display data sorted (High to Low)\n";
	std::cout << "6. Exit\n";
	std::cout << "Enter your choice: ";
}

// --- Function to safely get an int from user ---
bool getIntInput(int& value) {
	std::string input;
	std::cin >> input;

	try {
		size_t idx;
		value = stoi(input, &idx);
		if (idx != input.length()) throw std::invalid_argument("Extra characters after number");
		return true;
	}
	catch (...) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
}

// --- Function to input temperature data ---
void inputTemperatures(std::vector<double>& temperatures) {
	std::cout << "\nEnter temperature values (type " << SENTINEL << " to stop):\n";
	std::string input;
	while (true) {
		std::cout << "Temperature: ";
		std::cin >> input;
		if (isSentinel(input)) break;

		try {
			size_t idx;
			double value = stod(input, &idx);
			if (idx != input.length()) {
				throw std::invalid_argument("Extra characters after number");
			}
			temperatures.push_back(value);
		}
		catch (const std::invalid_argument&) {
			std::cout << "Invalid input. Please enter a numeric value or " << SENTINEL << " to stop.\n";
		}
		catch (const std::out_of_range&) {
			std::cout << "Value out of range. Please enter a valid temperature.\n";
		}
	}
	std::cout << "Data entry complete. " << temperatures.size() << " values recorded.\n";
}

// --- Function to calculate and display statistics ---
void analyzeTemperatures(const std::vector<double>& temperatures) {
	if (temperatures.empty()) {
		std::cout << "No data to analyze.\n";
		return;
	}

	double sum = 0.0;
	double minTemp = std::numeric_limits<double>::max();
	double maxTemp = std::numeric_limits<double>::lowest();

	for (double temp : temperatures) {
		sum += temp;
		if (temp < minTemp) minTemp = temp;
		if (temp > maxTemp) maxTemp = temp;
	}

	double avg = sum / temperatures.size();

	std::cout << "\n--- Temperature Analysis ---\n";
	std::cout << "Number of records: " << temperatures.size() << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Average temperature: " << avg << " °C\n";
	std::cout << "Minimum temperature: " << minTemp << " °C\n";
	std::cout << "Maximum temperature: " << maxTemp << " °C\n";
}

// --- Function to display entered data ---
void displayData(const std::vector<double>& temperatures) {
	if (temperatures.empty()) {
		std::cout << "No temperature data available.\n";
		return;
	}

	std::cout << "\n--- Stored Temperature Data ---\n";
	std::cout << std::fixed << std::setprecision(2);
	for (size_t i = 0; i < temperatures.size(); ++i) {
		std::cout << temperatures[i] << " °C";
		if ((i + 1) % 5 == 0 || i == temperatures.size() - 1)
			std::cout << std::endl;
		else
			std::cout << "  ";
	}
	std::cout << "Total: " << temperatures.size() << " values\n";
}

// --- Function to display entered data with sorting options ---
void displayDataSorted(const std::vector<double>& temperatures, bool descending) {
	if (temperatures.empty()) {
		std::cout << "No temperature data available.\n";
		return;
	}

	std::vector<double> sortedTemps = temperatures;
	if (descending) {
		sort(sortedTemps.begin(), sortedTemps.end(), std::greater<double>());
		std::cout << "\n--- Temperature Data (High to Low) ---\n";
	}
	else {
		sort(sortedTemps.begin(), sortedTemps.end());
		std::cout << "\n--- Temperature Data (Low to High) ---\n";
	}

	std::cout << std::fixed << std::setprecision(2);
	for (size_t i = 0; i < sortedTemps.size(); ++i) {
		std::cout << sortedTemps[i] << " °C";
		if ((i + 1) % 5 == 0 || i == sortedTemps.size() - 1)
			std::cout << std::endl;
		else
			std::cout << "  ";
	}
	std::cout << "Total: " << sortedTemps.size() << " values\n";
}

// --- Main program ---
int main() {

	std::vector<double> temperatures;
	int choice;

	do {
		displayMenu();
		while (!getIntInput(choice) || choice < 1 || choice > 6) {
			std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
			std::cout << "Enter your choice: ";
		}

		switch (choice)
		{
		case 1:
			inputTemperatures(temperatures);
			break;
		case 2:
			displayData(temperatures);
			break;
		case 3:
			analyzeTemperatures(temperatures);
			break;
		case 4:
			displayDataSorted(temperatures, false);
			break;
		case 5:
			displayDataSorted(temperatures, true);
			break;
		case 6:
			std::cout << "Exiting program.\n";
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 6);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
