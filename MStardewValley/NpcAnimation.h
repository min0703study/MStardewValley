#pragma once
class NpcAnimation
{
	typedef struct tagAniInfo {
		float FrameUpdateSec;
		bool IsLoop;

		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;
	void init(eNpcs type);
	void release();

	void chageStage(int changeStage);

	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, float centerX, float bottomY);


	NpcAnimation() {};
	~NpcAnimation() {};
};

