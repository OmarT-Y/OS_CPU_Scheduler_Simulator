#pragma once
#include "definitions_sch.h"
class RR_Sch : public Scheduler
{
public:
	int run_Schedular(int System_time, int prev_running_time);
};