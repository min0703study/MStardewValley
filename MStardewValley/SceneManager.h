#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager: public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;
private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneIter _miSceneList;
	mapSceneList _mLoadingSceneList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ImageBase* mSceneChange;

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT initScene(string sceneName);

	//씬 교체
	HRESULT changeScene(string sceneName);
	HRESULT changeGameScene(string sceneName);

	bool bStartChangeScene;
	float mChangeSceneTime;
	int mChangeSceneFadeInAlpha;

	//로딩 스레드 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager();
	~SceneManager();
};

