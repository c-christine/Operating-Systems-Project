# Operating Systems Project
## Project 1 - Process Scheduling Simulation
### ✅Step 1: Read Process Data from a File
  1. Create a text file (e.g., processes.txt) with a list of processes.
  2. Each process should have:
     * Process ID (PID)
     * Arrival Time (When the process arrives in the system)
     * Burst Time (How long the process needs the CPU)
     * Priority (If using Priority Scheduling)

      Example of processes.txt:
      PID Arrival_Time Burst_Time Priority
      1 0 5 2
      2 2 3 1
      3 4 2 3
  
  3. Your program should read this file and store the data in memory.
### ✅Step 2: Implement Two Scheduling Algorithms
  * First-Come, First-Served (FCFS) → The first process that arrives runs first.
  * Shortest Job First (SJF) → The process with the smallest burst time runs first.

  Each algorithm:
    * Sorts the processes based on the algorithm's rule.
    * Simulates execution (decide which process runs at each step).
    * Calculates Waiting Time (WT) and Turnaround Time (TAT).
### ✅Step 3: Display a Gantt Chart (Execution Order)
  1. Program shows the order in which processes run.
  2. Displays a simple text-based Gantt chart in the console.
        Example Output:
        | P1 | P2 | P3 | P1 | P4 |
        0    2    5    7    12    15
  3. At the end, print:
    * Waiting Time (WT) for each process
    * Turnaround Time (TAT) for each process
    * Average WT and TAT
