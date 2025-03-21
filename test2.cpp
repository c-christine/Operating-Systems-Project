#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <format>
#include <cctype>
#include <algorithm>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

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

void printProcesses(const std::vector<Process>& processes) { //Prints out header and list of processes
    std::cout << "PID\tArrival_Time\tBurst_Time\tPriority\tWaiting_Time\tTurnaround_Time\n";
    for (std::vector<Process>::const_iterator it = processes.begin(); it != processes.end(); ++it) {
        std::cout << it->pid << "\t" 
                  << it->arrival_time << "\t\t\t\t" 
                  << it->burst_time << "\t\t\t" 
                  << it->priority << "\t\t\t"
                  << it->waiting_time << "\t\t\t\t"
                  << it->turnaround_time << "\n";
    }    
} 

void fcfs(std::vector<Process> &processes){
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    for(size_t i = 0; i < processes.size(); i++){
        if(current_time < processes[i].arrival_time){
            current_time = processes[i].arrival_time;
        }

        processes[i].waiting_time = current_time - processes[i].arrival_time;

        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        current_time += processes[i].burst_time;
        
    }
}

int main() {
    const std::string filename = "processes.txt";
    std::vector<Process> processes = readProcesses(filename); // stores parced file into process

    if (!processes.empty()) { // check if any processes exist 
        printProcesses(processes);
        fcfs(processes);
        printProcesses(processes);
    } else {
        std::cerr << "No processes loaded or an error occurred." << std::endl;
    }
    
    return 0;
}