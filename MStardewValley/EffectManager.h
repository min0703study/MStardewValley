#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class EffectManager: public SingletonBase<EffectManager>, public GameNode
{
public:
	typedef struct tagEffectAni {
		eEffectAniType AniType;

		int StartX;

		float AbsX;
		float AbsY;

		bool isOneTimeOver;

		float CurFrame;
		float MaxFrame;

		float ElapsedSec;
		float FrameUpdateSec;

		float IsPause;
	} EffectAni;

	typedef struct tagEffectSound {
		string EffectKey;
	} EffectSound;

	typedef struct tagEffectDamage {
		const int Damage;

		float Gravity;
		int AniDirection;

		bool IsEndAni;
		
		float CurX;
		float CurY;

		tagEffectDamage(const int damage, float curX, float curY) : Damage(damage), Gravity(4.0f), CurX(curX), CurY(curY), IsEndAni(false) {};
			
	} EffectDamage;

	HRESULT init();
	void playEffectOneTime(float x, float y, eEffectAniType type);
	int playEffectLoop(float absX, float absY, eEffectAniType type);
	void pauseEffectLoop(int key);
	void resumeEffectLoop(int key);
	void stopEffectLoop(int key);
	bool isPauseAni(int key);
	void playEffectDemage(float x, float y, int damage);
	void playEffectSound(eEffectSoundType type);

	void playRegularSound(eEffectSoundType type);

	void update();
	void render();
private:
	EffectAni mEffectAniList[eEffectAniType::EAT_END];
	vector<ImageGp*> mVEffectImg[eEffectAniType::EAT_END];

	EffectSound mEffectSoundList[eEffectSoundType::EST_END];

	vector<EffectAni*> mVOneTimeEffectAni;
	vector<EffectAni*>::iterator miVOneTimeEffectAni;

	map<int, EffectAni*> mLoopEffectAniList;
	map<int, EffectAni*>::iterator miVLoopEffectAni;

	vector<EffectSound> mVPlayingEffectSound;
	vector<EffectSound>::iterator miVPlayingEffectSound;

	vector<EffectDamage> mVPlayingDamage;
	vector<EffectDamage>::iterator miVPlayingDamage;

	ImageGp* mBaseSprite;
};

