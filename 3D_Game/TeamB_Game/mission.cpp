//==============================
//
//  ミニマップ処理[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorialUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI = NULL;

Mission g_Mission;

D3DXVECTOR3 g_TutorialUIpos;

LPD3DXFONT g_pMissionFont;
const char *g_MissionInfo[MISSION_MAX][255];
D3DXVECTOR2 g_MissionPos[MISSION_MAX];

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
		"Terminal", &g_pMissionFont);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial100.jpg", &g_pTextureTutorialUI);	//枠
	g_MissionInfo[MISSION_ZENMETU][0] = { "敵を全滅させろ" };
	g_MissionInfo[MISSION_IDOU][0] = { "次のエリアに移動しろ" };
	g_MissionInfo[MISSION_BOSS][0] = { "ボスを倒せ" };

	g_MissionPos[MISSION_ZENMETU] = D3DXVECTOR2(1060.0f,250.0f);
	g_MissionPos[MISSION_IDOU] = D3DXVECTOR2(1030.0f,250.0f);
	g_MissionPos[MISSION_BOSS] = D3DXVECTOR2(1080.0f,250.0f);

	g_Mission.mission = MISSION_ZENMETU;

	g_CntState = 60;
	
	////頂点バッファの生成・頂点情報の設定
	//VERTEX_2D* pVtx;

	////チュートリアル
	//{
	//	//頂点バッファの生成
	//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//		D3DUSAGE_WRITEONLY,
	//		FVF_VERTEX_2D,
	//		D3DPOOL_MANAGED,
	//		&g_pVtxBuffTutorialUI,
	//		NULL);
	//	//頂点バッファをロックし、頂点情報へのポインタを取得
	//	g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

	//	//頂点座標の設定
	//	pVtx[0].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
	//	//rhwの設定
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;
	//	//頂点カラーの設定
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	//頂点バッファをアンロック
	//	g_pVtxBuffTutorialUI->Unlock();
	//}
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
	////テクスチャの破棄
	//for (int nCnt = 0; nCnt < MISSION_MAX; nCnt++)
	//{
	//	if (g_pTextureMission[nCnt] != NULL)
	//	{
	//		g_pTextureMission[nCnt]->Release();
	//		g_pTextureMission[nCnt] = NULL;
	//	}
	//}

	////頂点バッファの破棄
	//if (g_pVtxBuffMission != NULL)
	//{
	//	g_pVtxBuffMission->Release();
	//	g_pVtxBuffMission = NULL;
	//}
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