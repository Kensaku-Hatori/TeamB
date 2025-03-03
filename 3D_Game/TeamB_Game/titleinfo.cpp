//==============================
//
//  選択処理[titleinfo.h]
//  Author:kaiti
//
//==============================
#include "titleinfo.h"
#include "game.h"
#include "input.h"
#include "ranking.h"
#include "fade.h"
//#include "tutorial.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"

#define MAX_TEXTURE (3)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturetitleinfo[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleinfo = NULL;
D3DXVECTOR3 g_Selectpos;
//ロゴ
LPDIRECT3DTEXTURE9 g_pTexturetitleinfoLogo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitleinfoLogo = NULL;
D3DXVECTOR3 g_Logopos;

TITLEINFO g_titleinfoMenu=TITLE_START;
//============
//初期化処理
//============
void InitTitleInfo(void)
{
	g_titleinfoMenu = TITLE_START;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_Selectpos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gamestart.png", &g_pTexturetitleinfo[0]); //START
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titleranking.png", &g_pTexturetitleinfo[1]); //ランキング
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\exit.png", &g_pTexturetitleinfo[2]); //ランキング

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBufftitleinfo,
		                        NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftitleinfo->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{//メニュー
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Selectpos.x - TITLESELECT_WIDTH / 2, g_Selectpos.y - TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Selectpos.x + TITLESELECT_WIDTH / 2, g_Selectpos.y - TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Selectpos.x - TITLESELECT_WIDTH / 2, g_Selectpos.y + TITLESELECT_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Selectpos.x + TITLESELECT_WIDTH / 2, g_Selectpos.y + TITLESELECT_HEIGHT / 2, 0.0f);
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

		g_Selectpos.y += 120.0f;
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBufftitleinfo->Unlock();


	//ロゴ
	g_Logopos = D3DXVECTOR3(640.0f, 0.0f, 0.0f);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title.png", &g_pTexturetitleinfoLogo); //START
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufftitleinfoLogo,
		NULL);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftitleinfoLogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
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
	g_pVtxBufftitleinfoLogo->Unlock();
}
//==========
//終了処理
//==========
void UninitTitleInfo(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTexturetitleinfo[nCnt] != NULL)
		{
			g_pTexturetitleinfo[nCnt]->Release();
			g_pTexturetitleinfo[nCnt] = NULL;
		}
	}
	//テクスチャの破棄
	if (g_pTexturetitleinfoLogo != NULL)
	{
		g_pTexturetitleinfoLogo->Release();
		g_pTexturetitleinfoLogo = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBufftitleinfo != NULL && g_pVtxBufftitleinfoLogo != NULL)
	{
		g_pVtxBufftitleinfo->Release();
		g_pVtxBufftitleinfo = NULL;
		g_pVtxBufftitleinfoLogo->Release();
		g_pVtxBufftitleinfoLogo = NULL;
	}
}
//==========
//更新処理
//==========
void UpdateTitleInfo(int zDelta)
{
	FADE g_fade;
	g_fade = GetFade();

	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftitleinfo->Lock(0, 0, (void**)&pVtx, 0);

	//メニューの選択(上下)
	//STARTにいる場合
	if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu==TITLE_START)
	{
		g_titleinfoMenu = TITLE_FIN;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_START)
	{
		g_titleinfoMenu = TITLE_RANK;
	}
	//RANKにいる場合
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu == TITLE_RANK)
	{
		g_titleinfoMenu = TITLE_START;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_RANK)
	{
		g_titleinfoMenu = TITLE_FIN;
	}
	//FINにいる場合
	else if ((KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true || zDelta > 0) && g_titleinfoMenu == TITLE_FIN)
	{
		g_titleinfoMenu = TITLE_RANK;
	}
	else if ((KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true || zDelta < 0) && g_titleinfoMenu == TITLE_FIN)
	{
		g_titleinfoMenu = TITLE_START;
	}

	//頂点カラーの設定(明るく)
	if (g_titleinfoMenu == TITLE_START)
	{	//STARTにいる場合
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (g_titleinfoMenu == TITLE_RANK)
	{	//RULEにいる場合
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	else if (g_titleinfoMenu == TITLE_FIN)
	{	//RULEにいる場合
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}

	//頂点バッファをアンロック
	g_pVtxBufftitleinfo->Unlock();


	if ((KeyboardTrigger(DIK_RETURN) == true|| GetJoypadTrigger(JOYKEY_A) == true || OnMouseDown(0) == true) && g_fade == FADE_NONE)
	{//ENTERが押された
		if (g_Logopos.y < LOGO_END_Y)
		{//ロゴが下りてきている時
			g_Logopos.y += LOGO_END_Y;
		}
		else
		{//ロゴがおり切ったとき
			StopSound();

			//メニューに合わせてモードの切り替え
			if (g_titleinfoMenu == TITLE_START)
			{	//STARTにいる場合
				SetFade(MODE_STAGEONE);
				pPlayer->bfirst = true;

				PlaySound(SOUND_LABEL_GAME);
			}
			else if (g_titleinfoMenu == TITLE_RANK)
			{	//RANKにいる場合
				SetFade(MODE_RANK);
				SetRankMode(RANKMODE_SELECT);

				PlaySound(SOUND_LABEL_RANKING);
			}
			else if (g_titleinfoMenu == TITLE_FIN)
			{	//FINにいる場合
				SetFade(MODE_END);
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftitleinfoLogo->Lock(0, 0, (void**)&pVtx, 0);

	//ロゴを下げる
	if (g_Logopos.y < LOGO_END_Y)
	{
		g_Logopos.y++;
	}
	//ロゴのY制限
	if (g_Logopos.y >= LOGO_END_Y)
	{
		g_Logopos.y = LOGO_END_Y;
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y - TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Logopos.x - TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Logopos.x + TITLELOGO_WIDTH / 2, g_Logopos.y + TITLELOGO_HEIGHT / 2, 0.0f);


	//頂点バッファをアンロック
	g_pVtxBufftitleinfoLogo->Unlock();
}
//===========
//描画処理
//===========
void DrawTitleInfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufftitleinfo, 0, sizeof(VERTEX_2D));

	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturetitleinfo[nCnt]);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufftitleinfoLogo, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturetitleinfoLogo);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}