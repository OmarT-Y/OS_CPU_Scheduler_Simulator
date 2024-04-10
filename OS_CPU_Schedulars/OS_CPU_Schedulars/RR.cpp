#include "RR.h"
#include <algorithm>
static bool sort_ready_queue(const Process* a, const Process* b) {
	//put the one with lower PID first
	//if all jobs has same arrival time
	if (a->PID <= b->PID)
	{
		return true;
	}
	else
		return false;
}
static bool sort_blocked_queue(const Process* a, const Process* b) {
	if (a->ariv_time <= b->ariv_time)
	{
		return true;
	}
	else
		return false;
}
int RR_Sch::run_Schedular(int System_time, int prev_running_time)
{
	int quantum_t = 2; 
    Check_new_processes(System_time);

	check_blocked(System_time);

    if(!Ready_Q.empty()){
		sort(Ready_Q.begin(), Ready_Q.end(), sort_ready_queue);
	}

	if (!Blocked_Q.empty())
	{
	  	sort(Blocked_Q.begin(), Blocked_Q.end(), sort_blocked_queue);
	}

	if (System_time == 0) //Initial System State
	{
		Running_task = nullptr;

		if (!Ready_Q.empty()) 
		{
			Running_task = Ready_Q[0];
			Running_task->start_time = System_time;
			expected_last_return = Running_task->remaining_burst;
			return min(Running_task->remaining_burst,quantum_t);
		}
	}
	else if (prev_running_time == expected_last_return) //If the running process is done
	{
		// Calculating specs of terminated process
		Running_task->remaining_burst = 0;
		turnaround.push_back(get_turnaround(Running_task, System_time));
		wait_time.push_back(get_waiting_time(Running_task, System_time));

		// Erasing terminated process
		int index = -1;
		for (size_t i = 0; i < Ready_Q.size(); ++i)
		{
			if (Ready_Q[i] == Running_task)
			{
				index = static_cast<int>(i);
				break;
			}
		}

		if (index != -1)
		{
			Ready_Q.erase(Ready_Q.begin() + index);
		}

		//Alocating New Process to CPU
		//sort Ready Queue
		if (!Ready_Q.empty()){
			sort(Ready_Q.begin(), Ready_Q.end(), sort_ready_queue);
		}


		if (!Ready_Q.empty())
		{
			Running_task = Ready_Q[0];
			if (Running_task->start_time == -1) //if this task ran for the first time
			{
				Running_task->start_time = System_time;
			}
			expected_last_return = Running_task->remaining_burst;
			return min(Running_task->remaining_burst,quantum_t);
		}
		else
		{
			Running_task = nullptr;
		}

	}
	else //a new process got added or blocked process exited or idle 
	{
		if (Running_task != nullptr) //if there is a running task
		{
				Running_task->remaining_burst = (expected_last_return - prev_running_time);
				Process *prevRunning = Ready_Q[0];
				Ready_Q.push_back(prevRunning);
				Ready_Q.erase(Ready_Q.begin());
			    if (!Ready_Q.empty())
				{
				     Running_task = Ready_Q[0];
				     if (Running_task->start_time == -1) //if this task ran for the first time
				     {
				     	Running_task->start_time = System_time;
				     }
				     expected_last_return = Running_task->remaining_burst;
				     return min(Running_task->remaining_burst,quantum_t);
				}
				else
				{
					 Running_task = nullptr; 
				}

		}
		else	//no running task so check ready queue
		{
			if (!Ready_Q.empty())
			{
				Running_task = Ready_Q[0];
				if (Running_task->start_time == -1) //if this task ran for the first time
				{
					Running_task->start_time = System_time;
				}
				expected_last_return = Running_task->remaining_burst;
				return min(Running_task->remaining_burst,quantum_t);
			}
		}
	}
	if (!Blocked_Q.empty())	//If there is a task in blocked queue
	{
		return (Blocked_Q[0]->ariv_time) - System_time;
	}
	return INT32_MAX;	//else wait for infinity
}