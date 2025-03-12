//============================================================
//
//メッシュスフィア[meshSphere.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

#include "main.h"

#define MAX_MESHSPHERE (1)																				// 球の最大数
																										   
//球の構造体																							 　 
typedef struct																							   
{																										   
	D3DXVECTOR3 pos;																					// 位置
	D3DXVECTOR3 rot;																					// 向き
	D3DXCOLOR col;																						// 色
	D3DXMATRIX mtxWorld;																				// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;																	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIndxBuff;																	// インデクスバッファへのポインタ
	int Indx;																							// インテックス
	int DiviX;																							// 分割数
	int DiviY;																							// 分割数
	int nMaxVtx;																						   
	int nPolyNum;																						   
	float  fRadius;																						// 半径
	bool bHalf;																							// 半球かどうか
	bool bHead;																							// 表かどうか
	bool bUse;																							// 使用しているかどうか
}MeshSphere;																							   
																										   
//プロトタイプ宣言																						   
void InitSphere(void);																					// 初期化処理
void UninitSphere(void);																				// 終了処理
void UpdateSphere(void);																				// 更新処理
void DrawSphere(void);																					// 描画処理
int SetSphere(D3DXVECTOR3 pos, int DiviX, int DiviY, float fRadius, bool bHead, bool bHalf);			// 設定処理
void SetSpherePos(void);																				// 位置の設定処理
void SetSphereTexture(void);																			// テクスチャの設定処理
void DeleteSphere(void);																				// 消す処理
#endif // !_MESHSPHERE_H_
