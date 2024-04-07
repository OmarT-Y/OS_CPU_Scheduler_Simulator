#pragma once
#include <string>
#include <vector>
extern Process* Running_task;
extern vector<Process*> Ready_Q;
extern vector<Process*> Blocked_Q;
extern vector<Process> Job_Q;
extern vector<int> turnaround;
extern vector<int> wait_time;
class P_color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
public:

    P_color(unsigned char red, unsigned char green, unsigned char blue)
        : red(red), green(green), blue(blue)
    {
    }
};
class Process
{
private:
    static int number_of_tasks_created;
public:
    string name;
    int PID;
    int ariv_time;
    int burst_time;
    int remaining_burst;
    int priority;
    int start_time;
    P_color color;

    Process(const string& name, int ariv_time, int burst_time, int priority, const P_color& color)
        : name(name), ariv_time(ariv_time), burst_time(burst_time), priority(priority), color(color)
    {
        this->PID = number_of_tasks_created++;
        this->start_time = -1;
        this->remaining_burst = burst_time;
    }

};
class Scheduler
{
public:
    int number_of_processes = 0;
    virtual int run_Schedular(int System_time) = 0;
    /*
    *   the function should:
    *       1)check of there are new processes in the job queue(if the size of the job queue is greater than the variable number_of_processes)
    *         1.2)if there are new process add them to the ready queue of the ready queue depending on the arival time
    *         1.3)if added to the ready queue re-order the ready queue
    *       2)check if the currently running process should be deleted or put back into the ready queue (with order)
    *       3)if the process is deleted calculate the wait time and the turnaround and add them to their lists 
    *       4)set the running process pointer the next process in the ready queue and return the expected running time
    *       5)check the new running task and set the start time if its running for the first time
    */
};