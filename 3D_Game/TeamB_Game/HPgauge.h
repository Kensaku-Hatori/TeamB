//=========================================================
// 
// 敵のHPゲージ[HPgauge.h]
// Aothor:Rio Ohno
// 
//=========================================================

#ifndef HPGAUGE_H_
#define HPGAUGE_H_

#include "main.h"

//マクロ定義
#define MAX_HPGAUGE (32)		//ゲージの最大の数

//HPゲージ構造体
typedef struct
{
	D3DXVECTOR3 pos;								// 位置
	D3DXVECTOR3 rot;								// 向き
	LPDIRECT3DVERTEXBUFFER9 pVtxHPgaugeBuff;		// ワールドマトリックス
	float fNowHP;									// 現在のHP
	float fMaxHP;									// 最大のHP
	float fWidth;									// 幅
	float fHeight;									// 高さ
	bool bUse;										// 使用しているかどうか
}HPgauge;

//プロトタイプ宣言
void InitHPgauge();									// 初期化処理
void UninitHPgauge();								// 終了処理
void UpdateHPgauge();								// 更新処理
void DrawHPgauge();									// 描画処理
void SetHPgauge(D3DXVECTOR3 pos);					// 設定処理

#endif // !HPGAUGE_H_
