#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
_channel(nullptr),
_sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
	// 사운드 시스템 생성
	 System_Create(&_system);

	// 시스템 초기화
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// 채널 수 만큼 메모리 버퍼 및 사운드를 생성
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// 메모리 한번 밀자
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

	return S_OK;
}

void SoundManager::release(void)
{
	// destroy
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != nullptr)
			{
				if (_sound != nullptr) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update(void)
{
	// 사운드 시스템 업데이트
	// ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는등 다양한 작업을 자동으로 한다.
	_system->update();

	for (_ViCurPlaySound = _VCurPlaySound.begin(); _ViCurPlaySound != _VCurPlaySound.end();) {
		bool isPlay;
		_channel[(_ViCurPlaySound->second)]->isPlaying(&isPlay);
		if (!isPlay) {
			_VCurPlaySound.erase(_ViCurPlaySound++);
		} else {
			++_ViCurPlaySound;
		}
	}
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	FMOD_RESULT fmodResult;

	if (loop)
	{
		if (background)
		{
			fmodResult = _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			fmodResult = _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		fmodResult = _system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	if (fmodResult != FMOD_RESULT::FMOD_OK) {
		LOG::e(LOG_DEFAULT_TAG, "사운드 리소스 생성 실패 : " + keyName + "\nㄴPATH: " + soundName);
	}
	else {
		LOG::d(LOG_DEFAULT_TAG, "사운드 리소스 생성 성공 : " + keyName);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

// 사운드 플레이 (volume 영역은 Max -> 1.0)
void SoundManager::play(int soundKind, float volume)
{
	// 사운드 플레이
	//_system->playSound(FMOD_CHANNEL_FREE, _sound[soundKind], false, &_channel[soundKind]);
	_system->playSound(_sound[soundKind], false, 0, &_channel[soundKind]);

	// 볼륨 설정
	_channel[soundKind]->setVolume(volume);
}

void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{

#if SOUND_MODE
			int result = _system->playSound(*(iter->second), false, 0, &_channel[count]);
			_channel[count]->setVolume(volume);

			_VCurPlaySound.insert(make_pair(keyName, count));
			break;
#endif // SOUND_MODE


		}
	}
}

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
#if SOUND_MODE
			_channel[count]->stop();
#endif // SOUND_MODE
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	auto key = _VCurPlaySound.find(keyName);
	return key != _VCurPlaySound.end();
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}