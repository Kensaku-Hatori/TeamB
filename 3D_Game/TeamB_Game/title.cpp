//==============================
//
//  選択処理[Title.h]
//  Author:kaiti
//
//==============================
#include "title.h"
#include "title.h"
#include "game.h"
#include "input.h"
#include "ranking.h"
#include "fade.h"
//#include "tutorial.h"
#include "sound.h"
#define MAX_TEXTURE (3)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
TITLE g_TitleMenu=TITLE_START;
//============
//初期化処理
//============
void InitTitle(void)
{
	g_TitleMenu = TITLE_START;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title01.jpg", &g_pTextureTitle[0]); //背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stage.png", &g_pTextureTitle[1]); //START
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank.png", &g_pTextureTitle[2]); //ランキング

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffTitle,
		                        NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	int nData=0;
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{//ポーズメニュー
		if (nCnt == 0)
		{//背景
            //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
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
		}
		else if (nCnt > 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(400.0f, 300.0f + (nData * 150), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 300.0f + (nData * 150), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 400.0f + (nData * 150), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 400.0f + (nData * 150), 0.0f);
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
			nData++;
		}

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
}
//==========
//終了処理
//==========
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//==========
//更新処理
//==========
void UpdateTitle(void)
{
	FADE g_fade;
	g_fade = GetFade();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//メニューの選択(上下)
	//STARTにいる場合
	if ((KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true) && g_TitleMenu==TITLE_START)
	{
		g_TitleMenu = TITLE_RANK;
	}
	else if ((KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true) && g_TitleMenu == TITLE_START)
	{
		g_TitleMenu = TITLE_RANK;
	}
	//RANKにいる場合
	else if ((KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true) && g_TitleMenu == TITLE_RANK)
	{
		g_TitleMenu = TITLE_START;
	}
	else if ((KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true) && g_TitleMenu == TITLE_RANK)
	{
		g_TitleMenu = TITLE_START;
	}

	//頂点カラーの設定(明るく)
	if (g_TitleMenu == TITLE_START)
	{	//STARTにいる場合
		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (g_TitleMenu == TITLE_RANK)
	{	//RULEにいる場合
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	if ((KeyboardTrigger(DIK_RETURN) == true|| GetJoypadTrigger(JOYKEY_A) == true) && g_fade == FADE_NONE)
	{
		//メニューに合わせてモードの切り替え
		if (g_TitleMenu == TITLE_START)
		{	//STARTにいる場合
			SetFade(MODE_GAME);
		}
		else if (g_TitleMenu == TITLE_RANK)
		{	//RANKにいる場合
			SetFade(MODE_RANK);
			SetRankMode(RANKMODE_TITLE);
		}
	}
}
//===========
//描画処理
//===========
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}