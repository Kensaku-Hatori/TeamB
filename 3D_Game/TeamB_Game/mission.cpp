//==============================
//
//  ミニマップ処理[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
//グローバル変数
//ミッション
LPDIRECT3DTEXTURE9 g_pTextureMission[MISSION_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMission = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTutorialUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI = NULL;

Mission g_Mission;

D3DXVECTOR3 g_Missionpos;
D3DXVECTOR3 g_TutorialUIpos;

int g_CntState;
//=============
// 初期化処理
//=============
void InitMission(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission00.jpg", &g_pTextureMission[0]);	//枠
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission01.jpg", &g_pTextureMission[1]);	//枠
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mission02.jpg", &g_pTextureMission[2]);	//枠

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial100.jpg", &g_pTextureTutorialUI);	//枠

	g_Mission.mission = MISSION_ZENMETU;

	g_Missionpos = D3DXVECTOR3(1130.0f, 270.0f, 0.0f);

	g_CntState = 60;
	
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//枠
	{		
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMission,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMission->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffMission->Unlock();
	}
	g_Missionpos.y += 80.0f;

	//チュートリアル
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTutorialUI,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffTutorialUI->Unlock();
	}
}
//==========
// 終了処理
//==========
void UninitMission(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MISSION_MAX; nCnt++)
	{
		if (g_pTextureMission[nCnt] != NULL)
		{
			g_pTextureMission[nCnt]->Release();
			g_pTextureMission[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMission != NULL)
	{
		g_pVtxBuffMission->Release();
		g_pVtxBuffMission = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateMission(void)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMission->Lock(0, 0, (void**)&pVtx, 0);


	//頂点バッファをアンロック
	g_pVtxBuffMission->Unlock();
}
//===========
// 描画処理
//===========
void DrawMission(void)
{
	MODE Mode = GetMode();

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//枠
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMission, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMission[g_Mission.mission]);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	//チュートリアル
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTutorialUI, 0, sizeof(VERTEX_2D));
		if (Mode == MODE_STAGEONE)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTutorialUI);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

}
//
//
//
Mission* GetMission()
{
	return &g_Mission;
}