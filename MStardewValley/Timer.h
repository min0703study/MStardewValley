#pragma once

class Timer
{
private:
	float _timeScale;		//경과시간 조절
	float _timeElapsed;		//마지막 시간과 현재시간의 경과값
	bool _isHardware;		//고성능 타이머 지원 여부

	__int64 _curTime;			// 현재 시간
	__int64 _lastTime;			// 이전 시간
	__int64 _periodFrequency;	// 시간 주기

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;

	float _FPSTimeElapsed;
	float _worldTime;
	float _gameTime;

	bool _isRunnigGameTime;
public:
	HRESULT init(void);
	// 현재 시간을 계산
	void tick(float lockFPS = 0.0f);

	// 현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	// 전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }

	inline float getGameTime(void) const { return _gameTime; }

	inline float isRunningGameTime(void) const { return _isRunnigGameTime; }

	void startGameTime() {
		_isRunnigGameTime = true;
	};
	void stopGameTime() {
		_isRunnigGameTime = false;
	};

	Timer() {}
	~Timer() {}
};