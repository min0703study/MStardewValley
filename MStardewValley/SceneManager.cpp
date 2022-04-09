#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;

	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}

			miSceneList = _mSceneList.erase(miSceneList);
			SAFE_DELETE(miSceneList->second);
		}
	}

	_mSceneList.clear();
}

void SceneManager::update(void)
{
	if (_currentScene) _currentScene->update();

}

void SceneManager::render(void)
{
	if (_currentScene) _currentScene->render();

}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	if (!scene) return nullptr;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

GameNode * SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;
	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

HRESULT SceneManager::initScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	//if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return S_OK;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	//if (find->second == _currentScene) return S_OK;

	//_currentScene->release();
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return S_OK;
}

DWORD CALLBACK loadingThread(LPVOID prc)
{
	SceneManager::_readyScene->init();
	
	SceneManager::_currentScene = SceneManager::_readyScene;

	SceneManager::_loadingScene->release();
	SceneManager::_currentScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return 0;
}
