//==============================================
//
// メッシュ円柱表示処理[MeshCylinder.h]
// Author:kaiti
//
//==============================================
#ifndef _MESHCYLINDER_H
#define _MESHCYLINDER_H_

#include "main.h"

//マクロ定義
#define MESHCYLINDERVTX_X (8)//横
#define MESHCYLINDERVTX_Z (2)//縦

#define MAXCYLINDER_VTX ((MESHCYLINDERVTX_X + 1) * (MESHCYLINDERVTX_Z + 1))//頂点数

#define CYLINDERPOLYGON_NO (MESHCYLINDERVTX_X * MESHCYLINDERVTX_Z * 2 + (MESHCYLINDERVTX_Z - 1) * 4)//ポリゴン数

#define CYLINDERINDEX_NO ((MESHCYLINDERVTX_X + 1) * 2 * MESHCYLINDERVTX_Z + (MESHCYLINDERVTX_Z - 1) * 2)//インデックス数

#define MESHCYLINDER_SIZE (150.0f)

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
#endif