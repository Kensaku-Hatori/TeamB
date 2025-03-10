//==============================
//
//  ミニマップ処理[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
Mission g_Mission;

LPD3DXFONT g_pMissionFont;
const char *g_MissionInfo[MISSION_MAX][255];
D3DXVECTOR2 g_MissionPos[MISSION_MAX];
LPD3DXFONT g_pTutorialFont;
D3DXVECTOR2 g_TutorialPos;

int g_CntState;
//=============
// 初期化処理
//=============
void InitMission(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	// デバック表示用フォントの生成

	D3DXCreateFont(pDevice, 23, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Arial", &g_pMissionFont);

	D3DXCreateFont(pDevice, 20, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Arial", &g_pTutorialFont);

	g_MissionInfo[MISSION_ZENMETU][0] = { "敵を全滅させろ" };
	g_MissionInfo[MISSION_IDOU][0] = { "次のエリアに移動しろ" };
	g_MissionInfo[MISSION_BOSS][0] = { "ボスを倒せ" };

	g_MissionPos[MISSION_ZENMETU] = D3DXVECTOR2(1060.0f,250.0f);
	g_MissionPos[MISSION_IDOU] = D3DXVECTOR2(1030.0f,250.0f);
	g_MissionPos[MISSION_BOSS] = D3DXVECTOR2(1080.0f,250.0f);

	g_Mission.mission = MISSION_ZENMETU;

	g_TutorialPos = D3DXVECTOR2(1040.0f,530.0f);

	g_CntState = 60;	
}
//==========
// 終了処理
//==========
void UninitMission(void)
{
	if (g_pMissionFont != NULL)
	{
		g_pMissionFont->Release();
		g_pMissionFont = NULL;
	}
	if (g_pTutorialFont != NULL)
	{
		g_pTutorialFont->Release();
		g_pTutorialFont = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateMission(void)
{
	DrawMission(g_MissionInfo[g_Mission.mission][0],g_pMissionFont,
		g_MissionPos[g_Mission.mission],
		D3DXCOLOR(0.0f,1.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		2);

	MODE pMode = GetMode();
	if (pMode == MODE_STAGEONE)
	{
		DrawMission("チュートリアル:TAB/BACK", g_pTutorialFont,
			g_TutorialPos,
			D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			2);
	}
}
//===========
// 描画処理
//===========
void DrawMission(const char *MissionInfo, LPD3DXFONT Font, D3DXVECTOR2 Pos, D3DXCOLOR Grow, D3DXCOLOR FontCol, int GrowRadius)
{
	// 光彩の半径
	const int glowRadius = GrowRadius;

	// 元のテキストの色
	D3DXCOLOR textColor = FontCol; // 白

	// 光彩の色
	D3DXCOLOR glowColor = Grow; // 青

	// テキストの描画領域
	RECT rect;
	SetRect(&rect, (int)Pos.x, (int)Pos.y, SCREEN_WIDTH, SCREEN_HEIGHT); // テキストの位置

	// 光彩効果の描画
	for (int y = -glowRadius; y <= glowRadius; y++)
	{
		for (int x = -glowRadius; x <= glowRadius; x++)
		{
			if (x * x + y * y <= glowRadius * glowRadius)
			{
				RECT offsetRect = rect;
				OffsetRect(&offsetRect, x, y);
				Font->DrawText(NULL, MissionInfo, -1, &offsetRect, DT_LEFT | DT_TOP, glowColor);
			}
		}
	}
	// メインテキストの描画
	Font->DrawText(NULL, MissionInfo, -1, &rect, DT_LEFT | DT_TOP, textColor);
}
//
//
//
Mission* GetMission()
{
	return &g_Mission;
}