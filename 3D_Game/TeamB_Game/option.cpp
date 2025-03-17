//==============================
//
//  ポーズ処理[Option.h]
//  Author:kaiti
//
//==============================
#include "Option.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//グローバル変数
//チュートリアル画像
LPDIRECT3DTEXTURE9 g_pTextureOption = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOption = NULL;
//背景
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionBack = NULL;


OPTION g_OptionType = OPTION_KANDO;
//============
// 初期化処理
//============
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	{
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Option001.jpg", &g_pTextureOption);		 //
		
	}

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//背景
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionBack,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffOptionBack->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 127);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffOptionBack->Unlock();
	}


	//チュートリアル
	{
		D3DXVECTOR3 Optionpos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOption,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(Optionpos.x - TUTO_X, Optionpos.y - TUTO_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Optionpos.x + TUTO_X, Optionpos.y - TUTO_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Optionpos.x - TUTO_X, Optionpos.y + TUTO_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Optionpos.x + TUTO_X, Optionpos.y + TUTO_Y, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffOption->Unlock();
	}

}
//==========
//終了処理
//==========
void UninitOption(void)
{
	// テクスチャの破棄
	UninitTexture(g_pTextureOption);

	// 頂点バッファの破棄
	UninitBuffer(g_pVtxBuffOption);
	UninitBuffer(g_pVtxBuffOptionBack);
}
//==========
//更新処理
//==========
void UpdateOption(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player* pPlayer = GetPlayer();

}
//===========
//描画処理
//===========
void DrawOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOptionBack, 0, sizeof(VERTEX_2D));
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//チュートリアル
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOption, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureOption);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}