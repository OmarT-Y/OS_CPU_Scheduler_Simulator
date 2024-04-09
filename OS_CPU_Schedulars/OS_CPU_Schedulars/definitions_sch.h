#pragma once
#include <string>
#include <vector>
using namespace std;

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
extern vector<Process> Job_Q;
class Scheduler
{
public:
    Process* Running_task;
    vector<Process*> Ready_Q;
    vector<Process*> Blocked_Q;
    vector<int> turnaround;
    vector<int> wait_time;
    int number_of_current_processes = 0;
    int total_number_of_processes = 0;
    int expected_last_return;
    /*
    *   check if the total numbe rof processes is less than the size of the job queue
    *   if so update the ready/blocked queues(3la 7sb arival time)
    *   return true if any processes were added
    *   called when: at the beggining of the scheduler_run functions
    */
    bool Check_new_processes(int sys_time);
    /*
    *   check the system time and the arival times of the process in the blocked queue
    *   if a process should arrive now or aleady arived move to the ready queue
    *   return true if any process was moved from the blocked q to the ready q
    *   called when: at the beggining of the scheduler_run functions
    */
    bool check_blocked(int sys_time);
    /*
    *   calculate the turnaround time for the process and push it into the vector
    *   called when: before a task is terminated at the end of the run scheduler function
    */
    int get_turnaround(Process* p, int System_time);
    /*
    *   calculate the waiting time for the process and push it into the vector
    *   called when: before a task is terminated at the end of the run scheduler function
    */
    int get_waiting_time(Process* p, int System_time);
    double get_avg_turnaround();
    double get_avg_waiting_time();
    virtual int run_Schedular(int System_time, int prev_running_time);
    /*
    *   1)check for new processes(call the function)
    *   2)check for blocked updates(call the function)
    *   3)comapre the prev running time to the expected_return_time to know if the task 
                                                                           was interrupted
    *       3.1)update the remaining burst
    *       3.2) if the task is done running (remaining burst = 0)
                                        (call get_turnaround and get_waiting_time)
            3.3)delete the process(remove from ready queue)

    *   //the order of the first 3 steps may change for better performance (bra7tk b2a)
    *   4)check the ready queue
    *   //SCHEDULE A PROCESS
    *   5)select a process to run and set the global pointer
    *   6)check how much will the process run for?(msln feh process waiting ht interrupt
                                                  el process el running so check blocked)
    *   //aw msln non preemptive f ht run el burst kolo? 3la 7sb b2a bra7tk
    *   7)return the next expected time for the context switching(and set the variable)
                                                (3aizny a call el function deh tany b3d ad eh?)
    */
    Scheduler(Process* Running_task, const vector<Process*>& Ready_Q, const vector<Process*>& Blocked_Q, const vector<int>& turnaround, const vector<int>& wait_time, int number_of_current_processes, int total_number_of_processes, int expected_last_return)
        : Running_task(Running_task), Ready_Q(Ready_Q), Blocked_Q(Blocked_Q), turnaround(turnaround), wait_time(wait_time), number_of_current_processes(number_of_current_processes), total_number_of_processes(total_number_of_processes), expected_last_return(expected_last_return) {};

    Scheduler() = default;
};