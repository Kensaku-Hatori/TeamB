//============================================================
//
//アイテム[Item.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ定義
#define MAX_ITEM (5)									//最大アイテム数
#define NUM_ITEMTYPE (3)								//アイテムの種類の数
#define ITEM_RADIUS (10.0f)								//アイテム(ビルボード)の半径
#define ITEM_TIME_DEL (240)								//アイテムが消えるまでのフレーム

//テクスチャ
static const char* ITEM_TEXTURE[NUM_ITEMTYPE] =
{

};

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//向き
	D3DXVECTOR3 size;									//直径
	D3DXMATRIX mtxWorld;								//ワールドマトリックス
	int type;											//種類
	int nCntTime;										//消えるまでのフレームカウンタ
	int nIndexShadow;									//影のインデックス格納用
	bool bUse;											//使用しているかどうか
	bool bDesp;											//描画するかどうか
}Item;

//プロトタイプ宣言
void InitItem();										//初期化処理
void UninitItem();										//終了処理
void UpdateItem();										//更新処理
void DrawItemBillboard();								//描画処理(ビルボード)
void SetItem(D3DXVECTOR3 pos, int type);				//設定処理
void CollisionItem(int nIndexItem);						//取得処理

#endif // !_MODEL_H_