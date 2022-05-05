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

	const char* MapOutdoorSpring = "맵 봄 스프라이트";
	const char* MapMines1To30 = "맵 광산 1층부터 30층까지 스프라이트";
	const char* MapTownInterior = "마을 인테리어 스프라이트";
	
	const char* MapBtnEraser = "맵툴 지우개 버튼";
	const char* MapBtnSelect = "맵툴 선택 버튼";
	const char* MapBtnNone = "맵툴 기본 버튼";
	const char* MapBtnSave = "맵툴 저장 버튼";
	const char* MapBtnBack = "맵툴 뒤로가기 버튼";
	const char* MapBtnLoad = "맵툴 불러오기 버튼";
	const char* MapBtnCollision = "맵툴 충돌 버튼";
	const char* MapBtnMovable = "맵툴 움직일 수 있는 버튼";
	const char* MapBtnObjectGroup = "맵툴  오브젝트 묶기 버튼";
	const char* MapBtnSelectMine = "맵툴 - 광산 팔레트 선택 버튼";
	const char* MapBtnSelectFarm = "맵툴 - 농장 팔레트 선택 버튼";
	const char* MapBtnSelectInterior = "맵툴 - 인테리어 팔레트 선택 버튼";

	const char* PlayerSpriteMan= "남성 동작 스프라이트";
	const char* PlayerSpriteHair= "머리 스프라이트";
	const char* PlayerSpriteCloth= "옷 스프라이트";

	const char* ToolSprite = "도구 스프라이트";
	const char* MineRockSprite = "광산 광물 스프라이트";
	const char* MinesItemSprite = "광산 아이템 스프라이트";
	const char* MonsterSprite = "몬스터 스프라이트";
	const char* WeaponSprite = "무기 스프라이트";

	const char* Toolbar = "게임 하단 툴바";
	const char* Clock = "게임 시계";
	const char* EnergePGBarF = "에너지 게이지 바 Front";
	const char* EnergePGBarB = "에너지 게이지 바 Back";
	const char* InventoryBox = "인벤토리 상자";
	const char* InventoryRadioBtn = "인벤토리 라디오 버튼";
	const char* CraftRadioBtn = "공예 라디오 버튼";
	const char* MoneyBoard = "돈 계기판";
	const char* CropsSeedSprite = "작물 씨앗 스프라이트";
	const char* CropsStageSprite = "작물 진화 스프라이트";
	const char* HoedSprite = "괭이질 한 땅 스프라이트";
	const char* ForageSprite = "forage 스프라이트";
	const char* WeedSprite = "잡초 스프라이트";

	const char* ShopMenuItem = "상점 메뉴 리스트 아이템";

	const char* NpcSpritePierreP = "피에르 초상화 스프라이트";
	const char* NpcSpritePierreA = "피에르 액션 스프라이트";


	const char* NpcSpriteMarlonP = "말론 초상화 스프라이트";
	const char* NpcSpriteMarlonA = "말론 액션 스프라이트";

	const char* ItemInfoName = "아이템 이름";
	const char* ItemInfoContent = "아이템 콘텐츠";
	const char* ItemInfoEnd = "아이템 끝";

	const char* EventBox = "아이템 잠깐 표시";

	const char* EffectSprite = "효과 애니메이션 스프라이트";
	const char* CraftablesSprite = "공예가능 스프라이트";
	const char* WeaponIcon = "무기 아이콘";

	const char* TileSize = "타일 사이즈";
	const char* FuranceOverEvent = "용광로 작업 종료 이벤트 말풍선";
	const char* QuestionBox = "질문 상자";

	HRESULT init(void);
	virtual void release(void);
};

