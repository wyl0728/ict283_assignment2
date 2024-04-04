#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <map>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "WeatherData.h"
#include "Date.h"
#include "Time.h"
#include "Calculations.h"
#include "Bst.h"
#include "Spcc.h"

// Function prototypes
void LoadWeatherData(const std::vector<std::string>& filenames, Bst<WeatherData>& Tree, std::map<Date, AggregatedWeatherData>& aggregatedData);
void DisplayAverageWindSpeed(const Bst<WeatherData>& tree, int year, int month);
void DisplayAverageTemperature(const Bst<WeatherData>& tree, int year);
void DisplayTotalSolarRadiationByMonth(const Bst<WeatherData>& tree, int year);
void DisplayMonthlyStatisticsForYear(const Bst<WeatherData>& tree);
void ProcessWeatherData(const WeatherData& data, std::map<Date, AggregatedWeatherData>& aggregatedData);
void DisplayAggregatedData(const std::map<Date, AggregatedWeatherData>& aggregatedData, int year, int month);
void CalculateAndDisplaySPCC(const Bst<WeatherData>& tree, int month);
void ClearWeatherData(Bst<WeatherData>& Tree);
bool ReadDataSourceFile(const std::string& sourceFileName, std::vector<std::string>& filenames);

int main() {
    // Initialize data structures and variables
    Bst<WeatherData> Tree;
    std::vector<std::string> filenames;
    std::map<Date, AggregatedWeatherData> aggregatedData;

    // Read filenames from data_source.txt
    if (!ReadDataSourceFile("data/data_source.txt", filenames)) {
        return 1; // Exit with error
    }

    std::cout << "Debug: Found " << filenames.size() << " filenames." << std::endl;

    // Load weather data from CSV files
    if (!filenames.empty()) {
        std::cout << "Debug: Loading weather data..." << std::endl;
        LoadWeatherData(filenames, Tree, aggregatedData);
    } else {
        std::cerr << "No filenames found in data_source." << std::endl;
        return 1; // Exit with error
    }

    // Menu
    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Average wind speed and sample standard deviation for a specific month of year\n";
        std::cout << "2. Average ambient air temperature and sample standard deviation for each month of year\n";
        //std::cout << "3. Total solar radiation in kWh/m2, for each month of year\n";
        std::cout << "3. Sample Pearson Correlation Coefficient for a specific month\n";
        std::cout << "4. Average wind speed (km/h), Average ambient air temperature and total solar radiation for each month\n";
        std::cout << "5. Reload data_source.txt\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
    case 1:
        int year, month;
        std::cout << "Enter year (YYYY): ";
        std::cin >> year;
        std::cout << "Enter month (MM): ";
        std::cin >> month;
        DisplayAverageWindSpeed(Tree, year, month);
        break;
    case 2:
        //Display average temperature
        std::cout << "Enter year (YYYY): ";
        std::cin >> year;
        DisplayAverageTemperature(Tree, year);
        break;
    case 3:
        // Display average solar radiation
        //std::cout << "Enter year (YYYY): ";
        //std::cin >> year;
        //DisplayTotalSolarRadiationByMonth(Tree, year);
        std::cout << "Enter month (1-12): ";
        std::cin >> month;
        CalculateAndDisplaySPCC(Tree, month);
        break;
    case 4:
        //Display monthly statistics
        DisplayMonthlyStatisticsForYear(Tree);
        break;
    case 5:
        ClearWeatherData(Tree);
        ReadDataSourceFile("data/data_source.txt", filenames);
        LoadWeatherData(filenames, Tree, aggregatedData);
        break;
    case 6:
        std::cout << "Exiting\n";
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

//Parse Date and Time in CSV
void ParseDateTime(const std::string& dateTimeStr, Date& date, Time& time) {
    int day, month, year, hour, minute;
    char dateDelim1, dateDelim2;

    //std::cout << "Debug: Parsing datetime string: " << dateTimeStr << std::endl;

    std::istringstream dateTimeStream(dateTimeStr);
    std::string datePart, timePart;

    if (!std::getline(dateTimeStream, datePart, ' ')) {
        throw std::runtime_error("Datetime format error");
    }

    if (!std::getline(dateTimeStream, timePart)) {
        throw std::runtime_error("Date,time format error");
    }

    // Parse the date part
    std::istringstream dateStream(datePart);
    if (!(dateStream >> day >> dateDelim1 >> month >> dateDelim2 >> year) || dateDelim1 != '/' || dateDelim2 != '/') {
        throw std::runtime_error("Date format error");
    }

    // Parse the time part
    std::istringstream timeStream(timePart);
    std::replace(timePart.begin(), timePart.end(), ':', ' ');
    timeStream.str(timePart);
    if (!(timeStream >> hour >> minute)) {
        throw std::runtime_error("Time format error");
    }

    date = Date(day, month, year);
    time = Time(hour, minute, 0);
}

//Check CSV headers
std::map<std::string, int> getHeaderIndices(const std::string& headerLine) {
    std::map<std::string, int> headerIndices;
    std::istringstream stream(headerLine);
    std::string column;
    int index = 0;

    //std::cout << "Debug: Header line: " << headerLine << std::endl;

    while (std::getline(stream, column, ',')) {
        headerIndices[column] = index;
        ++index;
    }
    return headerIndices;
}

//Clean the input string for numeric values
std::string CleanNumericString(const std::string& str) {
    std::string cleanedString;
    for (char c : str) {
        if ((c >= '0' && c <= '9') || c == '.' || c == '-' || c == '+') {
            cleanedString += c;
        }
    }
    return cleanedString;
}

// Check if the values are numbers.
bool IsNumber(const std::string& s) {
    auto it = s.begin();  // Use auto to automatically use the correct iterator type
    bool decimalPoint = false;
    std::string::size_type minSize = 0;  // Use string::size_type for size-related variables

    if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
        it++;
        minSize++;
    }
    while (it != s.end()) {
        if (*it == '.') {
            if (!decimalPoint) {
                decimalPoint = true;
            } else {
                return false;
            }
        } else if (!isdigit(static_cast<unsigned char>(*it)) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint)) {
            return false;
        }
        ++it;
    }
    return s.size() > minSize;
}

//Clear Weather Data from Bst
void ClearWeatherData(Bst<WeatherData>& Tree) {
    Tree.Clear();
}

//Load data_source.txt
bool ReadDataSourceFile(const std::string& sourceFileName, std::vector<std::string>& filenames) {
    std::ifstream sourceFile(sourceFileName);
    filenames.clear();

    if (sourceFile.is_open()) {
        std::string filename;
        while (std::getline(sourceFile, filename)) {
            if (!filename.empty()) {
                filenames.push_back("data/" + filename);
            }
        }
        sourceFile.close();
        return true;
    } else {
        std::cerr << "Could not open data_source file at " << sourceFileName << std::endl;
        return false;
    }
}

// Load data from CSV file and insert into BST
void LoadWeatherData(const std::vector<std::string>& filenames, Bst<WeatherData>& Tree, std::map<Date, AggregatedWeatherData>& aggregatedData) {
    for (const auto& filename : filenames) {
        std::cout << "Debug: Processing file " << filename << std::endl;
        std::ifstream file(filename);

        if (!file) {
            std::cerr << "Could not open input file: " << filename << std::endl;
            continue;  // Move to the next file
        }

        std::string headerLine;
        if (!std::getline(file, headerLine)) {
            std::cerr << "Could not read header line from file." << std::endl;
            continue;
        }

        auto headerIndices = getHeaderIndices(headerLine);
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty() || line.find_first_not_of(",") == std::string::npos) {
                continue;  // Skip empty lines
            }

            std::istringstream iss(line);
            std::string cell;
            std::vector<std::string> cells;

            while (std::getline(iss, cell, ',')) {
                cells.push_back(cell);
            }

            WeatherData data;
            try {
                ParseDateTime(cells[headerIndices["WAST"]], data.date, data.time);
                data.windSpeed = (!cells[headerIndices["S"]].empty() && IsNumber(cells[headerIndices["S"]])) ? std::stof(cells[headerIndices["S"]]) : -1.0f;
                data.solarRadiation = (!cells[headerIndices["SR"]].empty() && IsNumber(cells[headerIndices["SR"]])) ? std::stof(cells[headerIndices["SR"]]) : -1.0f;
                data.temperature = (!cells[headerIndices["T"]].empty() && IsNumber(cells[headerIndices["T"]])) ? std::stof(cells[headerIndices["T"]]) : -1.0f;

                Tree.Insert(data);  // Insert data into the tree

                // Aggregate data by month and year
                Date monthKey(data.date.GetYear(), data.date.GetMonth(), 1);
                AggregatedWeatherData& aggData = aggregatedData[monthKey];
                aggData.totalWindSpeed += data.windSpeed >= 0 ? data.windSpeed : 0;
                aggData.windSpeedCount += data.windSpeed >= 0 ? 1 : 0;
                aggData.totalSolarRadiation += data.solarRadiation >= 0 ? data.solarRadiation : 0;
                aggData.solarRadiationCount += data.solarRadiation >= 0 ? 1 : 0;
                aggData.totalTemperature += data.temperature >= 0 ? data.temperature : 0;
                aggData.temperatureCount += data.temperature >= 0 ? 1 : 0;

            } catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << " Line skipped." << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument error: " << e.what() << " Line skipped." << std::endl;
            }
        }

        file.close();
    }
}

// Function to process WeatherData and update aggregated data
void ProcessWeatherData(const WeatherData& data, std::map<Date, AggregatedWeatherData>& aggregatedData) {
    Date monthKey(data.date.GetYear(), data.date.GetMonth(), 1);
    auto& aggregated = aggregatedData[monthKey];

    if (data.windSpeed >= 0) {
        aggregated.totalWindSpeed += data.windSpeed;
        aggregated.windSpeedCount++;
    }
    if (data.solarRadiation >= 100) {
        aggregated.totalSolarRadiation += data.solarRadiation;
        aggregated.solarRadiationCount++;
    }
    if (data.temperature >= 0) {
        aggregated.totalTemperature += data.temperature;
        aggregated.temperatureCount++;
    }
}

// Function to display aggregated data for a specific month
void DisplayAggregatedData(const std::map<Date, AggregatedWeatherData>& aggregatedData, int year, int month) {
    Date targetDate(year, month, 1);
    auto it = aggregatedData.find(targetDate);
    if (it != aggregatedData.end()) {
        const Date& date = it->first;  // Use the date from the map's key
        const AggregatedWeatherData& data = it->second;

        std::cout << "Aggregated data for " << date.GetMonthName() << " " << date.GetYear() << ":\n";
        std::cout << "Average Wind Speed: " << (data.windSpeedCount > 0 ? data.totalWindSpeed / data.windSpeedCount : 0) << " km/h\n";
        std::cout << "Total Solar Radiation: " << (data.solarRadiationCount > 0 ? data.totalSolarRadiation / 1000.0 : 0) << " MWh\n";
        std::cout << "Average Temperature: " << (data.temperatureCount > 0 ? data.totalTemperature / data.temperatureCount : 0) << " °C\n";
    } else {
        std::cout << "No data available for " << targetDate.GetMonthName() << " " << year << std::endl;
    }
}

//Display average wind speed
void DisplayAverageWindSpeed(const Bst<WeatherData>& Tree, int year, int month) {
    AggregatedWeatherData aggregatedData;
    std::vector<float> windSpeedsKmh;
    std::string monthName;

    Tree.InOrderTraversal([&](const WeatherData& data) {
        if (data.date.GetYear() == year && data.date.GetMonth() == month) {
            if (monthName.empty()) {
                monthName = data.date.GetMonthName(); // Get the month name from the first relevant data node
            }
            float windSpeedKmh = data.windSpeed * 3.6; // Convert m/s to km/h
            aggregatedData.totalWindSpeed += windSpeedKmh;
            aggregatedData.windSpeedCount++;
            windSpeedsKmh.push_back(windSpeedKmh);
        }
    });

    if (aggregatedData.windSpeedCount > 0) {
        float averageWindSpeedKmh = aggregatedData.totalWindSpeed / aggregatedData.windSpeedCount;
        float stdDeviationKmh = CalculateStandardDeviation(windSpeedsKmh, averageWindSpeedKmh);

        std::cout << monthName << " " << year << ":" << std::endl;
        std::cout << "Average Wind Speed: " << std::fixed << std::setprecision(2) << averageWindSpeedKmh << " km/h" << std::endl;
        std::cout << "Sample Standard Deviation: " << std::fixed << std::setprecision(2) << stdDeviationKmh << " km/h" << std::endl;
    } else {
        std::cout << "No wind speed data available for " << monthName << " " << year << std::endl;
    }

}

//Display average Temperature
void DisplayAverageTemperature(const Bst<WeatherData>& Tree, int year) {
    std::cout << "Year: " << year << std::endl;

    for (int month = 1; month <= 12; ++month) {
        std::vector<float> temperatures;
        AggregatedWeatherData aggregatedData;

        Tree.InOrderTraversal([&](const WeatherData& data) {
            if (data.date.GetYear() == year && data.date.GetMonth() == month) {
                if (data.temperature >= 0) {
                    aggregatedData.totalTemperature += data.temperature;
                    ++aggregatedData.temperatureCount;
                    temperatures.push_back(data.temperature);
                }
            }
        });

        if (!temperatures.empty()) {
            float averageTemperature = CalculateAverage(temperatures);
            float stdDeviationTemperature = CalculateStandardDeviation(temperatures, averageTemperature);
            std::cout << Date(1, month, year).GetMonthName() << ": "
                      << std::fixed << std::setprecision(2)
                      << "Average Temperature: " << averageTemperature << " C, "
                      << "Standard Deviation: " << stdDeviationTemperature << " C" << std::endl;
        } else {
            std::cout << Date(1, month, year).GetMonthName() << ": No temperature data" << std::endl;
        }
    }
}

//Display total solar radiation
void DisplayTotalSolarRadiationByMonth(const Bst<WeatherData>& Tree, int year) {
    std::cout << "Year: " << year << std::endl;

    for (int month = 1; month <= 12; ++month) {
        AggregatedWeatherData aggregatedData;

        Tree.InOrderTraversal([&](const WeatherData& data) {
            if (data.date.GetYear() == year && data.date.GetMonth() == month && data.solarRadiation >= 100) {
                aggregatedData.totalSolarRadiation += data.solarRadiation * (10.0f / 60.0f) / 1000.0f;
                ++aggregatedData.solarRadiationCount;
            }
        });

        if (aggregatedData.solarRadiationCount > 0) {
            float totalSolarRadiationKWh = aggregatedData.totalSolarRadiation;
            std::cout << Date(1, month, year).GetMonthName() << ": "
                      << std::fixed << std::setprecision(2)
                      << totalSolarRadiationKWh << " kWh/m^2" << std::endl;
        } else {
            std::cout << Date(1, month, year).GetMonthName() << ": No Solar Radiation Data" << std::endl;
        }
    }
}

//Display monthly stats of the year
void DisplayMonthlyStatisticsForYear(const Bst<WeatherData>& Tree) {
    int inputYear;
    std::cout << "Enter year (YYYY): ";
    std::cin >> inputYear;

    std::ofstream outputFile("output.txt");
    bool hasData = false;

    for (int month = 1; month <= 12; ++month) {
        AggregatedWeatherData aggregatedData;

        Tree.InOrderTraversal([&](const WeatherData& data) {
            if (data.date.GetYear() == inputYear && data.date.GetMonth() == month) {
                if (data.windSpeed >= 0) {
                    aggregatedData.totalWindSpeed += data.windSpeed;
                    aggregatedData.windSpeedCount++;
                }
                if (data.solarRadiation >= 100) {
                    aggregatedData.totalSolarRadiation += data.solarRadiation;
                    aggregatedData.solarRadiationCount++;
                }
                if (data.temperature >= 0) {
                    aggregatedData.totalTemperature += data.temperature;
                    aggregatedData.temperatureCount++;
                }
            }
        });

        Date monthDate(inputYear, month, 1);
        std::string monthName = monthDate.GetMonthName();
        std::ostringstream outputLine;
        outputLine << inputYear << ", " << monthName << ": ";

        if (aggregatedData.windSpeedCount > 0 || aggregatedData.temperatureCount > 0 || aggregatedData.solarRadiationCount > 0) {
            hasData = true;

            float averageWindSpeed = (aggregatedData.windSpeedCount > 0) ? (aggregatedData.totalWindSpeed / aggregatedData.windSpeedCount) * 3.6f : 0;
            float averageTemperature = (aggregatedData.temperatureCount > 0) ? (aggregatedData.totalTemperature / aggregatedData.temperatureCount) : 0;
            float totalSolarRadiationKWh = (aggregatedData.solarRadiationCount > 0) ? (aggregatedData.totalSolarRadiation * (10.0f / 60.0f) / 1000.0f) : 0;

            outputLine << std::fixed << std::setprecision(2);
            outputLine << "Wind Speed: " << averageWindSpeed << " km/h, ";
            outputLine << "Temperature: " << averageTemperature << " C, ";
            outputLine << "Solar Radiation: " << totalSolarRadiationKWh << " kWh/m^2";
        } else {
            outputLine << "No data available";
        }

        std::cout << outputLine.str() << std::endl;
        outputFile << outputLine.str() << std::endl;
    }

    if (!hasData) {
        std::cout << "No data available for year " << inputYear << "." << std::endl;
        outputFile << "No data available for year " << inputYear << "." << std::endl;
    }

    outputFile.close();
}

// Implementation of CalculateAndDisplaySPCC
void CalculateAndDisplaySPCC(const Bst<WeatherData>& tree, int month) {
    std::vector<double> windSpeeds, temperatures, solarRadiations;

    tree.InOrderTraversal([&](const WeatherData& data) {
        if (data.date.GetMonth() == month) {
            windSpeeds.push_back(data.windSpeed);
            temperatures.push_back(data.temperature);
            solarRadiations.push_back(data.solarRadiation);
        }
    });

    double s_t = sPCC(windSpeeds, temperatures);
    double s_r = sPCC(windSpeeds, solarRadiations);
    double t_r = sPCC(temperatures, solarRadiations);

    // Create a Date object with the specified month to get the month's name
    // Year is not significant for the month's name
    Date tempDate(1, month, 2000);  // Use a placeholder year
    std::string monthName = tempDate.GetMonthName();

    std::cout << "Sample Pearson Correlation Coefficient for " << monthName << std::endl;
    std::cout << "S_T: " << s_t << std::endl;
    std::cout << "S_R: " << s_r << std::endl;
    std::cout << "T_R: " << t_r << std::endl;
}
