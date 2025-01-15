//==============================
//
// モデル表示処理[Block.cpp]
// Author:kaiti
//
//==============================
#include "block.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

//グローバル変数
Block g_Block[MAX_BLOCK];
//=================
// モデルの初期化
//=================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		g_Block[nCntBlockBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlockBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlockBlock].type = BLOCKTYPE_NORMAL;
		g_Block[nCntBlockBlock].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\block00.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\wall00.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\block02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].pMesh);


		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
		{
			//頂点数取得
			nNumVtx = g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->GetNumVertices();
			//頂点フォーマットのサイズ取得
			sizeFVF = D3DXGetFVFVertexSize(g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->GetFVF());
			//頂点バッファのロック
			g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntBlockvtx = 0; nCntBlockvtx < nNumVtx; nCntBlockvtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してモデルの最小値、最大値を取得
				//最小値
				if (vtx.x < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x = vtx.x;
				}
				if (vtx.y < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y = vtx.y;
				}
				if (vtx.z < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z = vtx.z;
				}
				//最大値
				if (vtx.x > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x = vtx.x;
				}
				if (vtx.y > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y = vtx.y;
				}
				if (vtx.z > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z = vtx.z;
				}

				g_Block[nCntBlockBlock].aModel[nCntBlock].size = D3DXVECTOR3(g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x,
																		     g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y,
																		     g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z);

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			//頂点バッファのアンロック
			g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->UnlockVertexBuffer();

			
			D3DXMATERIAL* pMat;//マテリアルへのポインタ
			pMat = (D3DXMATERIAL*)g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat->GetBufferPointer();
			for (int nCntBlockMat = 0; nCntBlockMat < (int)g_Block[nCntBlockBlock].aModel[nCntBlock].dwNumMat; nCntBlockMat++)
			{
				if (pMat[nCntBlockMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMat[nCntBlockMat].pTextureFilename, &g_Block[nCntBlockBlock].aModel[nCntBlock].pTexture[nCntBlockMat]); //1
				}
			}
		}
	}
}
//===================
// モデルの終了処理
//===================
void UninitBlock(void)
{
	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
		{
			//メッシュの破棄
			if (g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh != NULL)
			{
				g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->Release();
				g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh = NULL;
			}
			//マテリアルの破棄
			if (g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat != NULL)
			{
				g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat->Release();
				g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat = NULL;
			}
		}
	}
}
//===================
// モデルの更新処理
//===================
void UpdateBlock(void)
{

}
//===============
// モデルの描画
//===============
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;
	//マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;
	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		if (g_Block[nCntBlockBlock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Block[nCntBlockBlock].mtxWorld);
			
			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlockBlock].rot.y, g_Block[nCntBlockBlock].rot.x, g_Block[nCntBlockBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlockBlock].mtxWorld, &g_Block[nCntBlockBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlockBlock].pos.x, g_Block[nCntBlockBlock].pos.y, g_Block[nCntBlockBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlockBlock].mtxWorld, &g_Block[nCntBlockBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlockBlock].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pBuffMat->GetBufferPointer();

			for (int nCntBlockMat = 0; nCntBlockMat < (int)g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].dwNumMat; nCntBlockMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntBlockMat].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pTexture[nCntBlockMat]);
				//モデルの描画
				g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pMesh->DrawSubset(nCntBlockMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}
//=================
// モデルの設定
//=================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE type)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].rot = rot;
			g_Block[nCntBlock].type = type;
			g_Block[nCntBlock].bUse = true;
			break;
		}
	}
}
//============================
// プレイヤーとの当たり判定
//============================
bool CollisionBlock(void)
{
	bool bLanding = false; //着地しているかどうか

	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pPlayer->posOld.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
			 && pPlayer->posOld.y + pPlayer->size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
			{
				if (pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					//手前
					if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
						&& pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pPlayer->pos.z = pPlayer->posOld.z;
					}
					//奥
					else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
							 && pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pPlayer->pos.z = pPlayer->posOld.z;
					}
				}

				if (pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				 && pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
				{
					//左
					if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
						&& pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pPlayer->pos.x = pPlayer->posOld.x;
					}
					//右
					else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
							&& pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pPlayer->pos.x = pPlayer->posOld.x;
					}
				}

				if (pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					if (pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				     && pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						//ブロックに上からめり込んだ時
						if (pPlayer->posOld.y - pPlayer->size.y / 2 >= g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2
						 && pPlayer->pos.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
						{
							pPlayer->pos.y = pPlayer->posOld.y;
							pPlayer->move.y = 0.0f;
							bLanding = true;
						}
						//ブロックに下からめり込んだ時
						if (pPlayer->posOld.y <= g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
					     && pPlayer->pos.y + pPlayer->size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2)
						{
							pPlayer->pos.y = pPlayer->posOld.y;
							pPlayer->move.y = 0.0f;
						}
					}
				}
			}
		}
	}
	return bLanding;
}
//===========================
// 敵とモデルの当たり判定
//===========================
void CollisionBlockEnemy(int nCntBlockEnemy)
{
	Enemy *pEnemy = GetEnemy();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pEnemy[nCntBlockEnemy].posOld.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
				&& pEnemy[nCntBlockEnemy].posOld.y + pEnemy[nCntBlockEnemy].size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
			{
				if (pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					//手前
					if (pEnemy[nCntBlockEnemy].posOld.z + pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
						&& pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pEnemy[nCntBlockEnemy].pos.z = pEnemy[nCntBlockEnemy].posOld.z;
					}
					//奥
					else if (pEnemy[nCntBlockEnemy].posOld.z - pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
							 && pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pEnemy[nCntBlockEnemy].pos.z = pEnemy[nCntBlockEnemy].posOld.z;
					}
				}

				if (pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				 && pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
				{
					//左
					if (pEnemy[nCntBlockEnemy].posOld.x + pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
						&& pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pEnemy[nCntBlockEnemy].pos.x = pEnemy[nCntBlockEnemy].posOld.x;
					}
					//右
					else if (pEnemy[nCntBlockEnemy].posOld.x - pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
							 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pEnemy[nCntBlockEnemy].pos.x = pEnemy[nCntBlockEnemy].posOld.x;
					}
				}


				if (pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					if (pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
					 && pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						//ブロックに上からめり込んだ時
						if (pEnemy[nCntBlockEnemy].posOld.y - pEnemy[nCntBlockEnemy].size.y / 2 >= g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2
						 && pEnemy[nCntBlockEnemy].pos.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
						{
							pEnemy[nCntBlockEnemy].pos.y = pEnemy[nCntBlockEnemy].posOld.y;
							pEnemy[nCntBlockEnemy].move.y = 0.0f;
						}
						//ブロックに下からめり込んだ時
						if (pEnemy[nCntBlockEnemy].posOld.y <= g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
						 && pEnemy[nCntBlockEnemy].pos.y + pEnemy[nCntBlockEnemy].size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2)
						{
							pEnemy[nCntBlockEnemy].pos.y = pEnemy[nCntBlockEnemy].posOld.y;
							pEnemy[nCntBlockEnemy].move.y = 0.0f;
						}
					}
				}
			}
		}
	}
}