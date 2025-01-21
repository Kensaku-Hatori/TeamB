//=====================================
//
// メッシュ床表示処理[meshfield.h]
// Author:kaiti
//
//=====================================
#ifndef _MESHFIELD_H
#define _MESHFIELD_H_

#include "main.h"

//マクロ定義
#define MESHVTX_X (15)//横
#define MESHVTX_Z (15)//縦

#define MAX_VTX ((MESHVTX_X + 1) * (MESHVTX_Z + 1))//頂点数

#define POLYGON_NO (MESHVTX_X * MESHVTX_Z * 2 + (MESHVTX_Z - 1) * 4)//ポリゴン数

#define INDEX_NO ((MESHVTX_X + 1) * 2 * MESHVTX_Z + (MESHVTX_Z - 1) * 2)//インデックス数

#define MESH_SIZE (150.0f)

#define MESH_NUM_MAX (1)//メッシュフィールドの数


//テクスチャタイプ
typedef enum
{
	MESH_TEX_NULL=0,
	MESH_TEX_MAX
}MESH_TEX;

//ファイル格納
static const char* MESHFIELD_TEXTURE[MESH_TEX_MAX] =
{
	NULL
};

//ポリゴン(横)の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	MESH_TEX textype;						//テクスチャのタイプ
	int nDiviX;								//分割数x
	int nDiviY;								//分割数y
	int nDiviZ;								//分割数z
	float fWidth;								//幅
	float fHeight;							//高さ
	bool bUse;								//使用しているかどうか
}MeshField;

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetMeshfield(D3DXVECTOR3 pos,D3DXVECTOR3 rot,MESH_TEX textype,int nDiviX,int nDiviY,int nDiviZ,float fWidth,float fHeight);//位置、向き、テクスチャ、分割数x、分割数y、分割数z、幅、高さ

#endif