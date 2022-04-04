#pragma once
#include "SingletonBase.h"

class ImageClass: public SingletonBase<ImageClass>
{
public:
	const char* Cursor = "커서";
	const char* MenuBack = "메뉴 뒷 배경";
	const char* MenuBackCloud = "메뉴 뒷 배경 구름";
	const char* MenuBackLogo = "메뉴 로고";
	const char* MenuBtn = "메뉴 버튼";
	const char* MenuBtnMaptool = "메뉴 맵툴 버튼";
	const char* MenuBtnStart = "메뉴 시작 버튼";
	const char* MenuBtnExit = "메뉴 나가기 버튼";

	const char* UISetupBox = "게임 설정 상자";

	const char* UIVScrollBtn = "수직 스크롤 바 버튼";
	const char* UIVScrollBar = "수직 스크롤 바";

	const char* UIHScrollBtn = "수평 스크롤 바 버튼";
	const char* UIHScrollBar = "수평 스크롤 바";

	const char* MapSpringSprite = "맵 봄 스프라이트";
	const char* MapMines1To30 = "맵 광산 1층부터 30층까지";
	
	const char* MapBtnEraser = "맵 지우개 버튼";
	const char* MapBtnSelect = "맵 선택 버튼";
	const char* MapBtnNone = "맵 기본 버튼";
	const char* MapBtnSave = "맵 저장 버튼";
	const char* MapBtnLoad = "맵 불러오기 버튼";


	const char* PlayerSpriteMan= "남성 동작 스프라이트";
	const char* PlayerSpriteHair= "머리 스프라이트";
	const char* PlayerSpriteCloth= "옷 스프라이트";

	const char* ToolSprite = "도구 스프라이트";
	const char* MineRockSprite = "광산 광물 스프라이트";
	const char* MonsterSprite = "몬스터 스프라이트";
	const char* WeaponSprite = "무기 스프라이트";

	const char* Toolbar = "게임 하단 툴바";
	const char* Clock = "게임 시계";
	const char* EnergeProgressBar = "게임 에너지 프로그래스 바";

	HRESULT init(void);
	virtual void release(void);
};

