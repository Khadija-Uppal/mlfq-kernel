                                                                                             __​MLFQ Kernel Scheduler Simulator v2.0__
_​Subject: Operating Systems_
_Environment: Kali Linux / GCC_
_Author: Khadija-Tul-Kubra(23011556-056_)
​                                                                                                         __Project Overview__
​This project is a high-fidelity C-based simulation of a Multilevel Feedback Queue (MLFQ) scheduling algorithm within a custom kernel environment. It features a simulated boot sequence, dynamic process allocation, and real-time visualization of process aging and preemption.
__Key Features__
​->_Simulated Bootloader:_In thi Project GRUB has been used as bootloader that visualizes kernel module initialization and hardware mapping.
​->__Three-Level Queue System:__
​._Queue 0:_ High priority with a 4ms time quantum.
​._Queue 1:_ Medium priority with an 8ms time quantum.
​._Queue 2:_ Low priority (FCFS) for CPU-bound tasks.
​->_Dynamic Preemption:_ Higher priority processes automatically preempt lower ones.
->​_Feedback Mechanism:_ Processes are demoted to lower queues if they exceed their time slice.
​->_Performance Analytics:_ Calculates Turnaround Time (TAT) and Waiting Time (WT) for every process.
​ __Execution__
​->To run this project on Kali Linux, follow these commands:
        gcc src/main.c -o bin/kernel_sim _(This command Compiles the Kernel source)_
        ./bin/kernel_sim _(This command runs the simulator)
