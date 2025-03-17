//==============================
//
//  アイテム欄処理[SkillUI.cpp]
//  Author:kaiti
//
//==============================
#include "skillui.h"
#include "player.h"
#include "buttonUI.h"

//グローバル変数
//枠
LPDIRECT3DTEXTURE9 g_pTextureSkillUIframe = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillUIframe = NULL;

//魔法の種類
LPDIRECT3DTEXTURE9 g_pTextureSkillUI[SKILLTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillUI = NULL;

D3DXVECTOR3 g_SkillUIframepos;
D3DXVECTOR3 g_SkillUIpos;

//=============
// 初期化処理
//=============
void InitSkillUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill00.png", &g_pTextureSkillUI[0]);		// 通常魔法 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill01.png", &g_pTextureSkillUI[1]);		// 追尾魔法
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\skill02.png", &g_pTextureSkillUI[2]);		// 爆発魔法

	g_SkillUIframepos = D3DXVECTOR3(80.0f, 150.0f, 0.0f);
	g_SkillUIpos = g_SkillUIframepos;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//枠
	{		
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SKILLTYPE_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSkillUIframe,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffSkillUIframe->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_SkillUIframepos.x - SKILLUIFRAM_SIZE, g_SkillUIframepos.y - SKILLUIFRAM_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SkillUIframepos.x + SKILLUIFRAM_SIZE, g_SkillUIframepos.y - SKILLUIFRAM_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SkillUIframepos.x - SKILLUIFRAM_SIZE, g_SkillUIframepos.y + SKILLUIFRAM_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SkillUIframepos.x + SKILLUIFRAM_SIZE, g_SkillUIframepos.y + SKILLUIFRAM_SIZE, 0.0f);
			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			pVtx += 4;
			g_SkillUIframepos.x += SKILLUI_SPACE;
		}
		//頂点バッファをアンロック
		g_pVtxBuffSkillUIframe->Unlock();
	}

	//アイテム
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SKILLTYPE_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSkillUI,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffSkillUI->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//アイテム欄
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_SkillUIpos.x - SKILLUI_SIZE, g_SkillUIpos.y - SKILLUI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SkillUIpos.x + SKILLUI_SIZE, g_SkillUIpos.y - SKILLUI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SkillUIpos.x - SKILLUI_SIZE, g_SkillUIpos.y + SKILLUI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SkillUIpos.x + SKILLUI_SIZE, g_SkillUIpos.y + SKILLUI_SIZE, 0.0f);
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

			pVtx += 4;
			g_SkillUIpos.x += SKILLUI_SPACE;
		}
		//頂点バッファをアンロック
		g_pVtxBuffSkillUI->Unlock();
	}
	
	//SetButtonUi(BUTTONUI_WHEEL, g_SkillUIpos, D3DXVECTOR3(20.0f, 20.0f, 0.0f));
}
//==========
// 終了処理
//==========
void UninitSkillUI(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
	{
		if (g_pTextureSkillUI[nCnt] != NULL)
		{
			g_pTextureSkillUI[nCnt]->Release();
			g_pTextureSkillUI[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSkillUIframe != NULL)
	{
		g_pVtxBuffSkillUIframe->Release();
		g_pVtxBuffSkillUIframe = NULL;
	}
	if (g_pVtxBuffSkillUI != NULL)
	{
		g_pVtxBuffSkillUI->Release();
		g_pVtxBuffSkillUI = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateSkillUI(void)
{
	//プレイヤーの情報取得
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSkillUIframe->Lock(0, 0, (void**)&pVtx, 0);

	switch (pPlayer->Skilltype)
	{
	case SKILLTYPE_NONE:
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[4].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[5].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[6].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[7].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[8].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[9].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[10].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[11].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		break;
	case SKILLTYPE_HORMING:
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[8].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[9].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[10].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[11].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		break;
	case SKILLTYPE_EXPLOSION:
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[4].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[5].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[6].col = D3DCOLOR_RGBA(1, 1, 1, 255);
		pVtx[7].col = D3DCOLOR_RGBA(1, 1, 1, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		break;
	default:
		break;
	}


	//頂点バッファをアンロック
	g_pVtxBuffSkillUIframe->Unlock();
}
//===========
// 描画処理
//===========
void DrawSkillUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//枠
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffSkillUIframe, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSkillUIframe);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//アイテム欄
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffSkillUI, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < SKILLTYPE_MAX; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSkillUI[nCnt]);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}