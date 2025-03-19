#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
};

bool compareArrivalTime(const Process &a, const Process &b) { // sort process by arrival time
    return a.arrival_time < b.arrival_time;
}

std::vector<Process> readProcesses(const std::string &filename) {
    std::ifstream file(filename); //Opens the file with given name
    std::vector<Process> processes; //Creates empty list

    if (!file) { // Print Error is file can not open
        std::cerr << "Error opening file '" << filename << "'." << std::endl;
        return processes;
    }

    std::string line; 

    
    
    while (std::getline(file, line)) {
        // Find the first character
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue; // Skip blank lines
    
        // Skips Header
        if (std::isalpha(line[start])) {
            continue;
        }
    

        std::istringstream iss(line.substr(start)); // Removes leading spaces
        Process proc;
        if (iss >> proc.pid >> proc.arrival_time >> proc.burst_time >> proc.priority) {
            processes.push_back(proc);
        } else {
            std::cerr << "Error reading a line: " << line << std::endl;
        }
    }
    
    return processes;
}

void sjfScheduling(std::vector<Process> &sjf) {
    std::sort(sjf.begin(), sjf.end(), compareArrivalTime);

    int process_number = sjf.size();
    std::vector<bool> done(process_number, false);
    int completed = 0;
    int current_time = 0;
    while (completed < process_number) {
        int index = -1;
        int min_burst = 100;

        for (int i = 0; i < process_number; i++) {
            if (!done[i] && sjf[i].arrival_time <= current_time) {
                if (sjf[i].burst_time < min_burst) {
                    min_burst = sjf[i].burst_time;
                    index = i;
                }
            }
        }
    }
}


void printProcesses(const std::vector<Process>& processes) { //Prints out header and list of processes
    std::cout << "PID\tArrival_Time\tBurst_Time\tPriority\n";
    for (std::vector<Process>::const_iterator it = processes.begin(); it != processes.end(); ++it) {
        std::cout << it->pid << "\t" 
                  << it->arrival_time << "\t\t" 
                  << it->burst_time << "\t\t" 
                  << it->priority << "\n";
    }    
}

int main() {
    const std::string filename = "processes.txt";
    std::vector<Process> processes = readProcesses(filename); // stores parced file into process

    if (!processes.empty()) { // check if any processes exist 
        printProcesses(processes);

        std::vector<Process> sjfList = processes; // creates a copy for sjf
        sjfScheduling(sjfList);

    } else {
        std::cerr << "No processes loaded or an error occurred." << std::endl;
    }
    
    return 0;
}