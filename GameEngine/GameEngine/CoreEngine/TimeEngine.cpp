#include "CoreEngine/AppMain.h"

TimeEngine::TimeEngine()
{
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&PerformanceFrequency))
	{
		PerformanceHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&LastTime);
		TimeScale = 1.0f / PerformanceFrequency;
	}
	else
	{
		PerformanceHardware = false;
		LastTime = timeGetTime();
		TimeScale = 0.001f;
	}

	SampleCount = 0;
	FrameRate = 0;
	FramesPerSecond = 0;
	FPSTimeElapsed = 0.0f;
}

TimeEngine::~TimeEngine()
{
	if(CanReadCPU)
	{
		PdhCloseQuery(QueryHandle);
	}

	GlobalRefs::Debug->Log("Time Shutdown...");
}

bool TimeEngine::Initialize()
{
	// CPU Usage Count
	PDH_STATUS status;

	// Initialize the flag indicating whether this object can read the system cpu usage or not.
	CanReadCPU = true;

	// Create a query object to poll cpu usage.
	status = PdhOpenQuery(NULL, 0, &QueryHandle);

	if(status != ERROR_SUCCESS)
	{
		CanReadCPU = false;
	}

	// Set the query object to poll all cpus in the system.
	status = PdhAddCounter(QueryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &CounterHandle);

	if(status != ERROR_SUCCESS)
	{
		CanReadCPU = false;
	}

	LastSampleTime = GetTickCount();

	CPUUsage = 0;

	GlobalRefs::Debug->Log("Time Initialized...");

	return true;
}

void TimeEngine::Update(float lockFPS)
{
	float tempTimeElapsed;

	if(PerformanceHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&CurrentTime);
	}
	else
	{
		CurrentTime = timeGetTime();
	}

	tempTimeElapsed = (CurrentTime - LastTime) * TimeScale;

	if(lockFPS > 0.0f)
	{
		while(tempTimeElapsed < (1.0f / lockFPS))
		{
			if(PerformanceHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&CurrentTime);
			}
			else
			{
				CurrentTime = timeGetTime();
			}

			tempTimeElapsed = (CurrentTime - LastTime) * TimeScale;
		}
	}

	LastTime = CurrentTime;

	if(fabs(tempTimeElapsed - TimeElapsed) < 1.0f)
	{
		memmove(&FrameTime[1], FrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		FrameTime[0] = tempTimeElapsed;

		if(SampleCount < MAX_SAMPLE_COUNT)
		{
			SampleCount++;
		}
	}

	FramesPerSecond++;
	FPSTimeElapsed += tempTimeElapsed;

	if(FPSTimeElapsed > 1.0f)
	{
		FrameRate = FramesPerSecond;
		FramesPerSecond = 0;
		FPSTimeElapsed = 0.0f;
	}

	TimeElapsed = 0.0f;

	for(ULONG i = 0; i < SampleCount; i++)
	{
		TimeElapsed += FrameTime[i];
	}

	if(SampleCount > 0)
	{
		TimeElapsed /= SampleCount;
	}

	// CPU Usage Count
	PDH_FMT_COUNTERVALUE value;

	if(CanReadCPU)
	{
		if((LastSampleTime + 1000) < GetTickCount())
		{
			LastSampleTime = GetTickCount();

			PdhCollectQueryData(QueryHandle);

			PdhGetFormattedCounterValue(CounterHandle, PDH_FMT_LONG, NULL, &value);

			CPUUsage = value.longValue;
		}
	}

	return;
}

float TimeEngine::GetDeltaTime()
{
	return TimeElapsed;
}

unsigned long TimeEngine::GetFPSCount()
{
	return FrameRate;
}

int TimeEngine::GetCPUPercentage()
{
	int usage;

	if(CanReadCPU)
	{
		usage = (int)CPUUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}

char* TimeEngine::GetFPSText()
{
	char tempString[16];

	if(FrameRate > 9999)
	{
		FrameRate = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(FrameRate, tempString, 10);

	// Setup the fps string
	strcpy_s(FPSString, "FPS : ");
	strcat_s(FPSString, tempString);

	return FPSString;
}

char* TimeEngine::GetCPUPercentageText()
{
	char tempString[16];

	_itoa_s(this->GetCPUPercentage(), tempString, 10);

	strcpy_s(CPUString, "CPU Usage : ");
	strcat_s(CPUString, tempString);
	strcat_s(CPUString, "%");

	return CPUString;
}

/*
Color TimeEngine::GetFPSTextColor()
{
	Color textColor;

	if(FPS >= 60)
	{
		textColor = Color(0, 1, 0, 1);
	}

	if(FPS < 60)
	{
		textColor = Color(1, 1, 0, 1);
	}

	if(FPS < 30)
	{
		textColor = Color(1, 0, 0, 1);
	}

	return textColor;
}

*/