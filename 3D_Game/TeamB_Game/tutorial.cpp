//==============================
//
//  ポーズ処理[Tutorial.h]
//  Author:kaiti
//
//==============================
#include "Tutorial.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "mouse.h"
#include "buttonUI.h"

//グローバル変数
//チュートリアル画像
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
//矢印
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;
//分母
LPDIRECT3DTEXTURE9 g_pTextureDenom = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDenom = NULL;
//スラッシュ
LPDIRECT3DTEXTURE9 g_pTextureSlash = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlash = NULL;
//分子
LPDIRECT3DTEXTURE9 g_pTextureNumer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNumer = NULL;
//背景
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBack = NULL;


TUTORIAL g_TutorialType = TUTORIAL_MOVE;
int g_CntTutorialState = 0;
D3DXVECTOR3 g_ButtonSize;
float ButtonY;
//============
// 初期化処理
//============
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	{
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial001.jpg", &g_pTextureTutorial[TUTORIAL_MOVE]);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial007.jpg", &g_pTextureTutorial[TUTORIAL_CAMERA]);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial004.jpg", &g_pTextureTutorial[TUTORIAL_ROLL]);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial006.jpg", &g_pTextureTutorial[TUTORIAL_SKILL]); //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial003.jpg", &g_pTextureTutorial[TUTORIAL_ITEM]);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial005.jpg", &g_pTextureTutorial[TUTORIAL_LOCKON]);		 //
		
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sirusi.png", &g_pTextureArrow);		 //

		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number200.png", &g_pTextureDenom);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\slash.png", &g_pTextureSlash);		 //
		D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number200.png", &g_pTextureNumer);		 //
	}

	g_TutorialType = TUTORIAL_MOVE;
	g_ButtonSize = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
	ButtonY = 75.0f;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//背景
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTutorialBack,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTutorialBack->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pVtxBuffTutorialBack->Unlock();
	}


	//チュートリアル
	{
		D3DXVECTOR3 Tutorialpos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTutorial,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(Tutorialpos.x - TUTO_X, Tutorialpos.y - TUTO_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Tutorialpos.x + TUTO_X, Tutorialpos.y - TUTO_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Tutorialpos.x - TUTO_X, Tutorialpos.y + TUTO_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Tutorialpos.x + TUTO_X, Tutorialpos.y + TUTO_Y, 0.0f);

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
		g_pVtxBuffTutorial->Unlock();
	}

	float nSpace = 5.0f;
	//矢印
	{
		D3DXVECTOR3 Arrowpos = D3DXVECTOR3(120.0f, SCREEN_HEIGHT / 2, 0.0f);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffArrow,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y - YAJIRUSI_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Arrowpos.x - YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Arrowpos.x + YAJIRUSI_SIZE, Arrowpos.y + YAJIRUSI_SIZE, 0.0f);

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
			if (nCnt == 0)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

				SetButtonUi(BUTTONUI_AKEY, D3DXVECTOR3(Arrowpos.x - (g_ButtonSize.x + nSpace), Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
				SetButtonUi(BUTTONUI_L1, D3DXVECTOR3(Arrowpos.x + (g_ButtonSize.x + nSpace), Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
			}
			else if (nCnt == 1)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				SetButtonUi(BUTTONUI_DKEY, D3DXVECTOR3(Arrowpos.x - (g_ButtonSize.x + nSpace), Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
				SetButtonUi(BUTTONUI_R1, D3DXVECTOR3(Arrowpos.x + (g_ButtonSize.x + nSpace), Arrowpos.y - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
			}

			Arrowpos.x += 1030.0f;
			pVtx += 4;
		}
		//頂点バッファをアンロック
		g_pVtxBuffArrow->Unlock();
	}

	SetTutorialNo();
}
//==========
//終了処理
//==========
void UninitTutorial(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		UninitTexture(g_pTextureTutorial[nCnt]);
	}

	UninitTexture(g_pTextureArrow);
	UninitTexture(g_pTextureDenom);
	UninitTexture(g_pTextureSlash);
	UninitTexture(g_pTextureNumer);

	// 頂点バッファの破棄
	UninitBuffer(g_pVtxBuffTutorial);
	UninitBuffer(g_pVtxBuffArrow);
	UninitBuffer(g_pVtxBuffDenom);
	UninitBuffer(g_pVtxBuffSlash);
	UninitBuffer(g_pVtxBuffNumer);
	UninitBuffer(g_pVtxBuffTutorialBack);
}
//==========
//更新処理
//==========
void UpdateTutorial(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player* pPlayer = GetPlayer();

	ChangeTutorial();
	ChangeTutorialArrow();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffNumer->Lock(0, 0, (void**)&pVtx, 0);

	int aPosTexU; //桁数分	
	int nData = 10;
	int nData2 = 1;

	aPosTexU = g_TutorialType % nData / nData2;
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.2f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffNumer->Unlock();
}
//===========
//描画処理
//===========
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBack, 0, sizeof(VERTEX_2D));
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//チュートリアル
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial[g_TutorialType]);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//矢印
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureArrow);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}


	//分母
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffDenom, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureDenom);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//スラッシュ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSlash, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSlash);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//分子
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffNumer, 0, sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureNumer);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=========================
// チュートリアル画像変更
//=========================
void ChangeTutorial(void)
{
	if (KeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_R1) == true)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_TutorialType)
		{
		case TUTORIAL_MOVE:
			g_TutorialType = TUTORIAL_CAMERA;
			break;
		case TUTORIAL_CAMERA:
			g_TutorialType = TUTORIAL_ROLL;
			break;
		case TUTORIAL_ROLL:
			g_TutorialType = TUTORIAL_SKILL;
			break;
		case TUTORIAL_SKILL:
			g_TutorialType = TUTORIAL_ITEM;
			break;
		case TUTORIAL_ITEM:
			g_TutorialType = TUTORIAL_LOCKON;
			break;
		case TUTORIAL_LOCKON:
			SetEnableTutorial(false);
			break;

		default:
			break;
		}
	}
	else if (KeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_L1) == true)
	{
		PlaySound(SOUND_LABEL_SELECT);
		switch (g_TutorialType)
		{
		case TUTORIAL_MOVE:
			break;
		case TUTORIAL_CAMERA:
			g_TutorialType = TUTORIAL_MOVE;
			break;
		case TUTORIAL_ROLL:
			g_TutorialType = TUTORIAL_CAMERA;
			break;
		case TUTORIAL_SKILL:
			g_TutorialType = TUTORIAL_ROLL;
			break;
		case TUTORIAL_ITEM:
			g_TutorialType = TUTORIAL_SKILL;
			break;
		case TUTORIAL_LOCKON:
			g_TutorialType = TUTORIAL_ITEM;
			break;

		default:
			break;
		}
	}
}

//============
// 矢印の変更
//============
void ChangeTutorialArrow(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	static float Alpha = 0.0f;
	Alpha++;
	Alpha = (int)Alpha % 50;

	for (int ArrowCount = 0; ArrowCount < 2; ArrowCount++)
	{
		//テクスチャ座標の設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, Alpha / 50);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, Alpha / 50);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, Alpha / 50);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, Alpha / 50);
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffArrow->Unlock();
}

//
// 
//
void SetTutorial(TUTORIAL type)
{
	g_TutorialType = type;
	float nSpace = 5.0f;
	SetButtonUi(BUTTONUI_AKEY, D3DXVECTOR3(120.0f - (g_ButtonSize.x + nSpace), SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
	SetButtonUi(BUTTONUI_L1, D3DXVECTOR3(120.0f + (g_ButtonSize.x + nSpace), SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);

	SetButtonUi(BUTTONUI_DKEY, D3DXVECTOR3(1150.0f - (g_ButtonSize.x + nSpace), SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
	SetButtonUi(BUTTONUI_R1, D3DXVECTOR3(1150.0f + (g_ButtonSize.x + nSpace), SCREEN_HEIGHT / 2 - ButtonY, 0.0f), g_ButtonSize, BUTTONUI_TYPE_TUTORIAL);
}

//
// 
//
void SetTutorialNo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	VERTEX_2D* pVtx;

	int aPosTexU; //桁数分	
	int nData = 10;
	int nData2 = 1;

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + TUTO_NO_SIZE, 50.0f, 0.0f);

	//分母
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffDenom,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffDenom->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
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

		aPosTexU = TUTORIAL_MAX % nData / nData2;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffDenom->Unlock();
	}
	pos.x = SCREEN_WIDTH / 2;

	//スラッシュ
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSlash,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffSlash->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
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
		g_pVtxBuffSlash->Unlock();
	}
	pos.x -= TUTO_NO_SIZE;

	//分子
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffNumer,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffNumer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y - TUTO_NO_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + TUTO_NO_SIZE, pos.y + TUTO_NO_SIZE, 0.0f);
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

		aPosTexU = g_TutorialType % nData / nData2;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU * 0.1f) + 0.2f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffNumer->Unlock();
	}
}