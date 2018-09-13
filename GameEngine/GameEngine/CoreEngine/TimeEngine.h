#ifndef TIMEENGINE_H
#define TIMEENGINE_H

const ULONG MAX_SAMPLE_COUNT = 50;

class TimeEngine
{
	private:
			// Timer
			bool PerformanceHardware;
			float TimeScale;
			float TimeElapsed;
			__int64 CurrentTime;
			__int64 LastTime;
			__int64 PerformanceFrequency;

			float FrameTime[MAX_SAMPLE_COUNT];
			ULONG SampleCount;

			unsigned long FrameRate;
			unsigned long FramesPerSecond;
			float FPSTimeElapsed;
			char FPSString[16];

			// Cpu Usage
			bool CanReadCPU;
			HQUERY QueryHandle;
			HCOUNTER CounterHandle;
			unsigned long LastSampleTime;
			long CPUUsage;
			char CPUString[16];
	public:
			TimeEngine();
			~TimeEngine();

			bool Initialize();
			void Update(float lockFPS = 0.0f);

			float GetDeltaTime();
			unsigned long GetFPSCount();
			int GetCPUPercentage();
			char* GetFPSText();
			char* GetCPUPercentageText();
//			Color GetFPSTextColor();
};

#endif 