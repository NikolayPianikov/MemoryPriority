// MemoryPriority.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>

auto main(const int argc, char* argv[]) -> int
{
	if (argc != 2)
	{
		std::cout << "Please run as MemoryPriority.exe PID\n";		
		return 1;
	}

	const auto pid = std::stoi(argv[1]);

	MEMORY_PRIORITY_INFORMATION mem_priority;
	ZeroMemory(&mem_priority, sizeof(mem_priority));
	mem_priority.MemoryPriority = MEMORY_PRIORITY_NORMAL;

	const auto h_process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if(GetLastError() != 0)
	{
		std::cout << "Fail\n";
		return 1;
	}

	const auto result = SetProcessInformation(h_process, ProcessMemoryPriority, &mem_priority, sizeof(MEMORY_PRIORITY_INFORMATION));
	CloseHandle(h_process);
	if (!result)
	{
		std::cout << "Fail\n";
		return 1;
	}
	
	std::cout << "Success\n";
	return 0;	
}
