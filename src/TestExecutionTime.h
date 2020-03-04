#pragma once

#include<iostream>
#include<ctime>

class TestExecutionTime
{
public:
	static void start();
	static void end(const char* msg);
	static clock_t start_time;
	static clock_t end_time;
  static bool start_init;
public:
	TestExecutionTime();
	~TestExecutionTime();
};

