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
    int waiting_time;
    int turnaround_time;
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

void sjfScheduling(std::vector<Process> &processes) {
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int current_cpu_time = 0;
    int completed = 0;
    std::vector<bool> done(processes.size(), false);
    while (completed < processes.size()) {
        int index = -1;
        
        
        for (size_t i = 0; i < processes.size(); i++) { // Finds the shortest job available
            if (!done[i] && processes[i].arrival_time <= current_cpu_time) { // Finds an unfinished process that has arrived
                if (index == -1 || processes[i].burst_time < processes[index].burst_time) { // Assigns first available process i
                    index = i;
                }
            }
        }

        if (index == -1) { // Ensures loop continues even if no process arrives
            current_cpu_time++;
            continue;
        }
        

        processes[index].waiting_time = current_cpu_time - processes[index].arrival_time; 
        processes[index].turnaround_time = processes[index].waiting_time + processes[index].burst_time; 

        current_cpu_time += processes[index].burst_time;
        done[index] = true;
        completed++;
    }
}

void fcfs(std::vector<Process> &processes){
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int current_cpu_time = 0;

    for(size_t i = 0; i < processes.size(); i++){
        if(current_cpu_time < processes[i].arrival_time){
            current_cpu_time = processes[i].arrival_time;
        }

        processes[i].waiting_time = current_cpu_time - processes[i].arrival_time;

        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        current_cpu_time += processes[i].burst_time;
        
    }
}

void printProcesses(const std::vector<Process>& processes, int para) { //Prints out header and list of processes
    
    if (para == 0) {
        std::cout << "PID\tArrival_Time\tBurst_Time\tPriority\n";
        for (std::vector<Process>::const_iterator it = processes.begin(); it != processes.end(); ++it) {
            std::cout << it->pid << "\t" 
                    << it->arrival_time << "\t\t" 
                    << it->burst_time << "\t\t" 
                    << it->priority << "\n";
        }
    } else {
        std::cout << "PID\tArrival_Time\tBurst_Time\tPriority\tWaiting_Time\tTurnaround_Time\n";
        for (std::vector<Process>::const_iterator it = processes.begin(); it != processes.end(); ++it) {
            std::cout << it->pid << "\t" 
                    << it->arrival_time << "\t\t" 
                    << it->burst_time << "\t\t" 
                    << it->priority << "\t\t"
                    << it->waiting_time << "\t\t"
                    << it->turnaround_time << "\n";
        }    
    } 
} 



int main() {
    const std::string filename = "processes.txt";
    std::vector<Process> processes = readProcesses(filename); // stores parced file into process

    if (!processes.empty()) { // check if any processes exist 
        std::cout << "Original\n";
        printProcesses(processes, 0);
        std::cout << "\n";
        
        std::vector<Process> fcfsList = processes; // creates a copy for fcfs
        std::cout << "First Come First Serve\n";
        fcfs(fcfsList);
        printProcesses(fcfsList, 1);
        std::cout << "\n";

        std::vector<Process> sjfList = processes; // creates a copy for sjf
        std::cout << "Shortest Job First\n";
        sjfScheduling(sjfList);
        printProcesses(sjfList, 1);
        std::cout << "\n";

    } else {
        std::cerr << "No processes loaded or an error occurred." << "\n";
    }
    
    return 0;
}