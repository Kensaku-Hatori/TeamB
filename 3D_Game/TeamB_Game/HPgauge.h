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
#define MAX_HPGAUGE (32)															// ゲージの最大の数
#define MAX_POLY (3)																// １個のゲージに使うポリゴン数

//タイプ
typedef enum
{
	HPGAUGETYPE_NORMAL=0,															// 通常
	HPGAUGETYPE_RED,																// 赤
	HPGAUGETYPE_NONE,																// 枠
	HPGAUGETYPE_MAX										
}HPGAUGETYPE;

//テクスチャ
static const char* HPGAUGETEX[HPGAUGETYPE_MAX] =
{
	"data\\TEXTURE\\GUAGE.png",														// 通常ゲージのパス
	"data\\TEXTURE\\GUAGE.png",														// 赤ゲージのパス
	"data\\TEXTURE\\GUAGEEDGE.png",													// 枠ゲージ
};

//ポリゴンの構造体
typedef struct
{
	D3DXCOLOR col;																	// 色
	HPGAUGETYPE type;																// 種類
	D3DXMATRIX mtxWorld;															// ワールドマトリックス
	float fWidth;																	// 幅保存
	float fMaxGauge;																// 最大幅保存
}POLY;

//HPゲージ構造体
typedef struct
{
	POLY poly[MAX_POLY];															//ポリゴンの情報
	D3DXVECTOR3 pos;																// 位置
	D3DXVECTOR3 rot;																// 向き
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;												// 頂点情報
	float fNowHP;																	// 現在のHP
	float fMaxHP;																	// 最大のHP
	bool bUse;																		// 使用しているかどうか
}HPgauge;

//プロトタイプ宣言
void InitHPgauge();																	// 初期化処理
void UninitHPgauge();																// 終了処理
void UpdateHPgauge();																// 更新処理
void DrawHPgauge();																	// 描画処理
int SetHPgauge(D3DXVECTOR3 pos, D3DXVECTOR2 scale, float MaxHP);					// 設定処理
void SetPositionHPgauge(int Indx,D3DXVECTOR3 pos);									// 位置の設定処理
void HPgaugeDeff(int Indx,float NowHP);												// ゲージの減少処理
void RedgaugeDeff(int Indx, float NowHP);											// 赤ゲージの減少処理
void DeleteGuage(int Indx);															// HPゲージを消す

#endif // !HPGAUGE_H_
