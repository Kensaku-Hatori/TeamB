//============================
//
// モデル表示処理[model.h]
// Author:kaiti
//
//============================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MAX_PARTS (15)//パーツの最大数

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
	DWORD dwNumMat;			//マテリアルの数
	int nIdxModelParent;	//親モデルのインデックス
	int nIndx, Parent;
	D3DXVECTOR3 pos;		//位置(オフセット)
	D3DXVECTOR3 OffSet;
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 size;		//サイズ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	LPDIRECT3DTEXTURE9 pTexture[128];
}MODELINFO;

#endif
