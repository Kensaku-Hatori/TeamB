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

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif