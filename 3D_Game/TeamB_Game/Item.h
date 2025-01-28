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
#define MAX_MAT_ITEM (512)								//最大マテリアル数
#define MAX_ITEM (5)									//最大アイテム数
#define NUM_ITEMTYPE (3)								//アイテムの種類の数
#define ITEM_RADIUS (10.0f)								//アイテム(ビルボード)の半径
#define ITEM_TIME_DEL (240)								//アイテムが消えるまでのフレーム

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh;									//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;								//マテリアルへのポインタ
	DWORD dwNumMat;										//マテリアルの数
	D3DXVECTOR3 pos;									//位置(オフセット)
	D3DXVECTOR3 rot;									//向き
	D3DXVECTOR3 vtxMax;									//最大頂点
	D3DXVECTOR3 vtxMin;									//最小頂点
	D3DXVECTOR3 size;									//直径
	LPDIRECT3DTEXTURE9 apTextureItem[MAX_MAT_ITEM];		//テクスチャ
	D3DXMATRIX mtxWorld;								//ワールドマトリックス
	int Type;											//種類
	int nCntTime;										//消えるまでのフレーム
	int nIndexShadow;									//影のインデックス格納用
	bool bUse;											//使用しているかどうか
	bool bDesp;											//表示するかどうか
}Item;

//プロトタイプ宣言
void InitItem();										//初期化処理
void UninitItem();										//終了処理
void UpdateItem();										//更新処理
void DrawItemModel();									//描画処理(モデル)
void DrawItemBillboard();								//描画処理(ビルボード)
void SetItem(D3DXVECTOR3 pos,int nType);				//設定処理
void CollisionItem(int nIndexItem);						//取得処理

#endif // !_MODEL_H_