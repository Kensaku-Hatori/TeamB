//============================
//
// モデル表示処理[model.h]
// Author:kaiti
//
//============================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MAX_TEX (32)
#define MAX_PARTS (15)//パーツの最大数
#define MAX_STAGEMODEL (25)

typedef enum
{
	MODELTYPE_ZERO = 0,
	MODELTYPE_ONE,
	MODELTYPE_TWO,
	MODELTYPE_THREE,
	MODELTYPE_FOUR,
	MODELTYPE_FIVE,
	MODELTYPE_SIX,
	MODELTYPE_SEVEN,
	MODELTYPE_EIGHT,
	MODELTYPE_NINE,
	MODELTYPE_TEN,
	MODELTYPE_ELEVEN,
	MODELTYPE_TWELVE,
	MODELTYPE_THIRTEEN,
	MODELTYPE_MAX
}MODELTYPE;

typedef struct
{
	D3DXVECTOR3 CenterPos;
	D3DXVECTOR3 RotVec[3];
	D3DXVECTOR3 FaceLength;
}OBB;

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

typedef struct
{
	LPD3DXMESH pMesh;		//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
	DWORD dwNumMat;			//マテリアルの数
	LPDIRECT3DTEXTURE9 pTexture[MAX_TEX];
}MODELORIGIN;

typedef struct
{
	MODELORIGIN ModelBuff;
	MODELTYPE nType;
	D3DXVECTOR3 pos;		//位置(オフセット)
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 Max;
	D3DXVECTOR3 Min;
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	OBB ObbModel;
	bool bUse;
}STAGEMODEL;

void InitStageModel();
void UninitStageModel();
void UpdateStageModel();
void DrawStageModel();
void SetStageModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType);
void SetStageModelInfo(char *ModelPath[],int nType);
void LenOBBToPoint(OBB& obb, D3DXVECTOR3& p);
void DotOBBToPoint(OBB& obb, D3DXVECTOR3& p);
#endif