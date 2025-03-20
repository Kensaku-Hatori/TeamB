//==============================
//
//  ポーズ処理[Option.h]
//  Author:kaiti
//
//==============================
#include "option.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//グローバル変数
//設定
LPDIRECT3DTEXTURE9 g_pTextureOption[OPTION_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOption = NULL;
//背景
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionBack = NULL;
//矢印
LPDIRECT3DTEXTURE9 g_pTextureOptionArrow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionArrow = NULL;
//数字
LPDIRECT3DTEXTURE9 g_pTextureOptionNo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOptionNo = NULL;

Option g_Option;
bool g_bRight;
//============
// 初期化処理
//============
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();
	MODE mode = GetMode();


	//テクスチャの読み込み
	{
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\setting.png", &g_pTextureOption[OPTION_KANDO]);	 // 設定項目
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\setting01.png", &g_pTextureOption[OPTION_SOUND]);	 // 設定項目
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sirusi.png", &g_pTextureOptionArrow);			 // 矢印
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureOptionNo);			 // 数字
	}

	if (pPlayer->bfirst == true || mode == MODE_STAGEONE)
	{
		g_Option.cameraSP = 0.5f;
		g_Option.Sound = 0.5f;
	}

	g_Option.type = OPTION_KANDO;
	g_bRight = true;

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
		pVtx[0].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[1].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[2].col = D3DCOLOR_RGBA(1, 1, 1, 190);
		pVtx[3].col = D3DCOLOR_RGBA(1, 1, 1, 190);
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

	//設定
	{
		D3DXVECTOR3 Optionpos = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOption,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(Optionpos.x - OPTION_X, Optionpos.y - OPTION_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Optionpos.x + OPTION_X, Optionpos.y - OPTION_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Optionpos.x - OPTION_X, Optionpos.y + OPTION_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Optionpos.x + OPTION_X, Optionpos.y + OPTION_Y, 0.0f);
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

			Optionpos.y += OPTION_Y * 2;
			pVtx += 4;
		}
		//頂点バッファをアンロック
		g_pVtxBuffOption->Unlock();
	}

	//矢印
	{
		D3DXVECTOR3 Arrowpos = D3DXVECTOR3(SCREEN_WIDTH / 4 + 200.0f, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionArrow,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffOptionArrow->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(Arrowpos.x - OPTION_YAJIRUSI_SIZE, Arrowpos.y - OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Arrowpos.x + OPTION_YAJIRUSI_SIZE, Arrowpos.y - OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Arrowpos.x - OPTION_YAJIRUSI_SIZE, Arrowpos.y + OPTION_YAJIRUSI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Arrowpos.x + OPTION_YAJIRUSI_SIZE, Arrowpos.y + OPTION_YAJIRUSI_SIZE, 0.0f);

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

			Arrowpos.x += 300.0f;

			if (nCnt == 0 || nCnt == 2)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
			}
			else if (nCnt == 1 || nCnt == 3)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
				Arrowpos.y += OPTION_Y * 2;
				Arrowpos.x = SCREEN_WIDTH / 4 + 200.0f;
			}

			pVtx += 4;
		}
		//頂点バッファをアンロック
		g_pVtxBuffOptionArrow->Unlock();
	}

	//数字
	{
		D3DXVECTOR3 NoPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2 * OPTION_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffOptionNo,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(NoPos.x - OPTION_NO_SIZE, NoPos.y - OPTION_NO_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(NoPos.x + OPTION_NO_SIZE, NoPos.y - OPTION_NO_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(NoPos.x - OPTION_NO_SIZE, NoPos.y + OPTION_NO_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(NoPos.x + OPTION_NO_SIZE, NoPos.y + OPTION_NO_SIZE, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;

			NoPos.x += OPTION_NO_SIZE * 2;

			if (nCnt == 1)
			{
				NoPos.x = SCREEN_WIDTH / 2;
				NoPos.y += OPTION_Y * 2;
			}
		}
		SetOptionSound();
		//頂点バッファをアンロック
		g_pVtxBuffOptionNo->Unlock();
	}
}
//==========
//終了処理
//==========
void UninitOption(void)
{
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		// テクスチャの破棄
		UninitTexture(g_pTextureOption[nCnt]);
	}
	// テクスチャの破棄
	UninitTexture(g_pTextureOptionArrow);
	UninitTexture(g_pTextureOptionNo);

	// 頂点バッファの破棄
	UninitBuffer(g_pVtxBuffOption);
	UninitBuffer(g_pVtxBuffOptionBack);
	UninitBuffer(g_pVtxBuffOptionArrow);
	UninitBuffer(g_pVtxBuffOptionNo);

}
//==========
//更新処理
//==========
void UpdateOption(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player* pPlayer = GetPlayer();

	SelectOption(0);

	switch (g_Option.type)
	{
	case OPTION_KANDO:
		OptionKando();
		break;
	case OPTION_SOUND:
		OptionSound();
		break;

	default:
		break;
	}

	if (OnMouseDown(0) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetEnableOption(false);
	}

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
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//チュートリアル
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffOption, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureOption[nCnt]);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
	//矢印
	for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffOptionArrow, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureOptionArrow);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
	//数字
	for (int nCnt = 0; nCnt < 2 * OPTION_MAX; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffOptionNo, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureOptionNo);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

}
//
//
//
Option* GetOption(void)
{
	return &g_Option;
}
//===========
// 感度設定
//===========
void OptionKando(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
	{
		g_Option.cameraSP += 0.1f;
		if (g_Option.cameraSP >= 1.0f)
		{
			g_Option.cameraSP = 1.0f;
		}
		g_bRight = true;
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
	{
		g_Option.cameraSP -= 0.1f;
		if (g_Option.cameraSP <= 0.1f)
		{
			g_Option.cameraSP = 0.1f;
		}
		g_bRight = false;
	}

	SetOptionKando();
}
//===========
// 感度設定
//===========
void SetOptionKando(void)
{
	int aPosTexU[2];
	float nkando = g_Option.cameraSP * 10;

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		aPosTexU[nCnt] = ((int)nkando % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffOptionNo->Unlock();
}
void OptionSound(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
	{
		g_Option.Sound += 0.1f;
		if (g_Option.Sound >= 1.0f)
		{
			g_Option.Sound = 1.0f;
		}
		g_bRight = true;
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
	{
		g_Option.Sound -= 0.1f;
		if (g_Option.Sound <= 0.1f)
		{
			g_Option.Sound = 0.1f;
		}
		g_bRight = false;
	}

	SetOptionSound();

}
void SetOptionSound(void)
{
	int aPosTexU[2];
	float nkando = g_Option.Sound * 10;

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOptionNo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * 2;

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		aPosTexU[nCnt] = ((int)nkando % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffOptionNo->Unlock();

}
//=================
// 設定項目の選択
//=================
void SelectOption(int zDelta)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

	//メニューの選択(上下)
	//Contnueにいる場合
	if (KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_Option.type)
		{
		case OPTION_KANDO:
			g_Option.type = OPTION_SOUND;
			break;
		case OPTION_SOUND:
			g_Option.type = OPTION_KANDO;

			break;
		default:
			break;
		}
	}
	else if (KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_Option.type)
		{
		case OPTION_KANDO:
			g_Option.type = OPTION_SOUND;
			break;
		case OPTION_SOUND:
			g_Option.type = OPTION_KANDO;
			break;
		default:
			break;
		}
	}

	//頂点カラーの設定(明るく)
	for (int nCnt = 0; nCnt < OPTION_MAX; nCnt++)
	{
		if (g_Option.type == OPTION_KANDO)
		{	//Contnueにいる場合
			if (nCnt == OPTION_KANDO)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 127);
			}
		}
		else if (g_Option.type == OPTION_SOUND)
		{	//Contnueにいる場合
			if (nCnt == OPTION_SOUND)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 127);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 127);
			}
		}

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffOption->Unlock();
}