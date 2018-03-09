// stream-helper.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "sharedmemory.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define MAP_OBJECT_NAME "$pcars2$"


int main()
{

	HANDLE fileHandle = OpenFileMapping(PAGE_READONLY, FALSE, MAP_OBJECT_NAME );
	if (fileHandle == NULL)
	{
		printf("Could not open file mapping object (%d).\n", GetLastError());
		return 1;
	}

	const SharedMemory* sharedData = (SharedMemory*)MapViewOfFile(fileHandle, PAGE_READONLY, 0, 0, sizeof(SharedMemory));
	SharedMemory* localCopy = new SharedMemory;
	if (sharedData == NULL) 
	{
		printf("Could not map view of file (%d).\n", GetLastError());
		CloseHandle(fileHandle);
		return 1;
	}

	printf("Data Version: (%d).\n", sharedData->mVersion);
	printf("ESC TO EXIT \n\n");


	while (true)
	{
		if (_kbhit() && _getch() == 27)
		{
			break;
		}
	}
	UnmapViewOfFile(sharedData);
	CloseHandle(fileHandle);
	delete localCopy;
    return 0;
}

