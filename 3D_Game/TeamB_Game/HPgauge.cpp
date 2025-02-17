//=========================================================
// 
// 敵のHPゲージ[HPgauge.cpp]
// Aothor:Rio Ohno
// 
//=========================================================

#include"HPgauge.h"

//グローバル変数宣言
HPgauge g_HPgauge[MAX_HPGAUGE];

//==============
// 初期化処理
//==============
void InitHPgauge()
{
	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//構造体の初期化
		g_HPgauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_HPgauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
		g_HPgauge[nCnt].pVtxHPgaugeBuff = NULL;							//頂点情報
		g_HPgauge[nCnt].fNowHP = 0.0f;									//現在のHP
		g_HPgauge[nCnt].fMaxHP = 0.0f;
		g_HPgauge[nCnt].fWidth = 0.0f;									//幅
		g_HPgauge[nCnt].fHeight = 0.0f;									//高さ
		g_HPgauge[nCnt].bUse = false;									//使用していない状態にする
	}
}