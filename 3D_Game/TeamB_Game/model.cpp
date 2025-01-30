#include "model.h"
#include "player.h"

MODELORIGIN g_ModelOrigin[MODELTYPE_MAX];
STAGEMODEL g_StageModel[MAX_STAGEMODEL];

void InitStageModel()
{
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		g_StageModel[ModelCount].bUse = false;
		g_StageModel[ModelCount].nType = MODELTYPE_ZERO;
		g_StageModel[ModelCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_StageModel[ModelCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
void UninitStageModel()
{
	for (int ModelCount = 0; ModelCount < MODELTYPE_MAX; ModelCount++)
	{
		if (g_ModelOrigin[ModelCount].pBuffMat != NULL)
		{
			g_ModelOrigin[ModelCount].pBuffMat->Release();
			g_ModelOrigin[ModelCount].pBuffMat = NULL;
		}
		if (g_ModelOrigin[ModelCount].pMesh != NULL)
		{
			g_ModelOrigin[ModelCount].pMesh->Release();
			g_ModelOrigin[ModelCount].pMesh = NULL;
		}
		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{
			if (g_ModelOrigin[ModelCount].pTexture[TexCount] != NULL)
			{
				g_ModelOrigin[ModelCount].pTexture[TexCount]->Release();
				g_ModelOrigin[ModelCount].pTexture[TexCount] = NULL;
			}
		}
	}
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].ModelBuff.pBuffMat != NULL)
		{
			g_StageModel[ModelCount].ModelBuff.pBuffMat = NULL;
		}
		if (g_StageModel[ModelCount].ModelBuff.pMesh != NULL)
		{
			g_StageModel[ModelCount].ModelBuff.pMesh = NULL;
		}
		for (int texcount = 0; texcount < MAX_TEX; texcount++)
		{
			if (g_StageModel[ModelCount].ModelBuff.pTexture[texcount] != NULL)
			{
				g_StageModel[ModelCount].ModelBuff.pTexture[texcount] = NULL;
			}
		}
	}
}
void UpdateStageModel()
{
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == true)
		{
			Player* pPlayer = GetPlayer();
			float fDistance = 0.0f;
			LenOBBToPoint(g_StageModel[ModelCount].ObbModel, pPlayer->pos);
		}
	}
}
void DrawStageModel()
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

	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_StageModel[ModelCount].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_StageModel[ModelCount].rot.y, g_StageModel[ModelCount].rot.x, g_StageModel[ModelCount].rot.z);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].mtxWorld, &g_StageModel[ModelCount].mtxWorld, &mtxRot);

			g_StageModel[ModelCount].ObbModel.RotVec[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
			g_StageModel[ModelCount].ObbModel.RotVec[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
			g_StageModel[ModelCount].ObbModel.RotVec[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_StageModel[ModelCount].pos.x, g_StageModel[ModelCount].pos.y, g_StageModel[ModelCount].pos.z);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].mtxWorld, &g_StageModel[ModelCount].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_StageModel[ModelCount].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_StageModel[ModelCount].ModelBuff.pBuffMat->GetBufferPointer();

			for (int ModelMatCount = 0; ModelMatCount < (int)g_StageModel[ModelCount].ModelBuff.dwNumMat; ModelMatCount++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[ModelMatCount].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, g_StageModel[ModelCount].ModelBuff.pTexture[ModelMatCount]);
				//モデルの描画
				g_StageModel[ModelCount].ModelBuff.pMesh->DrawSubset(ModelMatCount);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetStageModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType)
{
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == false)
		{
			g_StageModel[ModelCount].bUse = true;
			g_StageModel[ModelCount].nType = nType;
			g_StageModel[ModelCount].ModelBuff = g_ModelOrigin[nType];
			g_StageModel[ModelCount].pos = pos;
			g_StageModel[ModelCount].rot = rot;

			int nNumVtx;   //頂点数
			DWORD sizeFVF; //頂点フォーマットのサイズ
			BYTE* pVtxBuff;//頂点バッファへのポインタ

			//頂点数取得
			nNumVtx = g_StageModel[ModelCount].ModelBuff.pMesh->GetNumVertices();
			//頂点フォーマットのサイズ取得
			sizeFVF = D3DXGetFVFVertexSize(g_StageModel[ModelCount].ModelBuff.pMesh->GetFVF());
			//頂点バッファのロック
			g_StageModel[ModelCount].ModelBuff.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してプレイヤーの最小値、最大値を取得
				//最小値
				if (vtx.x < g_StageModel[ModelCount].Min.x)
				{
					g_StageModel[ModelCount].Min.x = vtx.x;
				}
				if (vtx.y < g_StageModel[ModelCount].Min.y)
				{
					g_StageModel[ModelCount].Min.y = vtx.y;
				}
				if (vtx.z < g_StageModel[ModelCount].Min.z)
				{
					g_StageModel[ModelCount].Min.z = vtx.z;
				}
				//最大値
				if (vtx.x > g_StageModel[ModelCount].Max.x)
				{
					g_StageModel[ModelCount].Max.x = vtx.x;
				}
				if (vtx.y > g_StageModel[ModelCount].Max.y)
				{
					g_StageModel[ModelCount].Max.y = vtx.y;
				}
				if (vtx.z > g_StageModel[ModelCount].Max.z)
				{
					g_StageModel[ModelCount].Max.z = vtx.z;
				}
				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			//頂点バッファのアンロック
			g_StageModel[ModelCount].ModelBuff.pMesh->UnlockVertexBuffer();

			// 中心点
			g_StageModel[ModelCount].ObbModel.CenterPos.x = g_StageModel[ModelCount].pos.x;
			g_StageModel[ModelCount].ObbModel.CenterPos.y = g_StageModel[ModelCount].Min.y + g_StageModel[ModelCount].Max.y * 0.5f + g_StageModel[ModelCount].pos.y;
			g_StageModel[ModelCount].ObbModel.CenterPos.z = g_StageModel[ModelCount].pos.z;

			//計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_StageModel[ModelCount].rot.y, g_StageModel[ModelCount].rot.x, g_StageModel[ModelCount].rot.z);

			// 各座標軸の傾きを表すベクトルを計算
			g_StageModel[ModelCount].ObbModel.RotVec[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
			g_StageModel[ModelCount].ObbModel.RotVec[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
			g_StageModel[ModelCount].ObbModel.RotVec[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

			g_StageModel[ModelCount].ObbModel.RotVec[0].x = rot.x;
			g_StageModel[ModelCount].ObbModel.RotVec[0].y = rot.x;
			g_StageModel[ModelCount].ObbModel.RotVec[0].z = rot.x;

			g_StageModel[ModelCount].ObbModel.RotVec[1].x = rot.y;
			g_StageModel[ModelCount].ObbModel.RotVec[1].y = rot.y;
			g_StageModel[ModelCount].ObbModel.RotVec[1].z = rot.y;

			g_StageModel[ModelCount].ObbModel.RotVec[2].x = rot.z;
			g_StageModel[ModelCount].ObbModel.RotVec[2].y = rot.z;
			g_StageModel[ModelCount].ObbModel.RotVec[2].z = rot.z;

			// 中心点から面への距離の半分
			g_StageModel[ModelCount].ObbModel.FaceLength.x = fabsf(g_StageModel[ModelCount].Max.x - g_StageModel[ModelCount].Min.x) * 0.5f;
			g_StageModel[ModelCount].ObbModel.FaceLength.y = fabsf(g_StageModel[ModelCount].Max.y - g_StageModel[ModelCount].Min.y) * 0.5f;
			g_StageModel[ModelCount].ObbModel.FaceLength.z = fabsf(g_StageModel[ModelCount].Max.z - g_StageModel[ModelCount].Min.z) * 0.5f;
			break;
		}
	}
}
void SetStageModelInfo(char *ModelPath[], int PathType)
{
	HRESULT Hresult;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const char* pFile = ModelPath[0];

	//Xファイルの読み込み
	Hresult = D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelOrigin[PathType].pBuffMat,
		NULL,
		&g_ModelOrigin[PathType].dwNumMat,
		&g_ModelOrigin[PathType].pMesh);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ
	pMat = (D3DXMATERIAL*)g_ModelOrigin[PathType].pBuffMat->GetBufferPointer();
	for (int nCntBlockMat = 0; nCntBlockMat < (int)g_ModelOrigin[PathType].dwNumMat; nCntBlockMat++)
	{
		if (pMat[nCntBlockMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, 
				pMat[nCntBlockMat].pTextureFilename, 
				&g_ModelOrigin[PathType].pTexture[nCntBlockMat]); //1
		}
		else
		{
			g_ModelOrigin[PathType].pTexture[nCntBlockMat] = NULL;
		}
	}

	if(FAILED(Hresult))
	{
		return;
	}
}
void LenOBBToPoint(OBB& obb, D3DXVECTOR3& p)
{
	D3DXVECTOR3 Vec(0, 0, 0);   // 最終的に長さを求めるベクトル

		FLOAT LX = obb.FaceLength.x;
		FLOAT LY = obb.FaceLength.y;
		FLOAT LZ = obb.FaceLength.z;

		D3DXVECTOR3 fDistance = obb.CenterPos - p;

		// はみ出した部分のベクトルを計算
		FLOAT sX = D3DXVec3Dot(&fDistance, &obb.RotVec[0]) / LX;
		FLOAT sY = D3DXVec3Dot(&fDistance, &obb.RotVec[1]) / LY;
		FLOAT sZ = D3DXVec3Dot(&fDistance, &obb.RotVec[2]) / LZ;

		// sの値を絶対値にする
		sX = (float)fabsf(sX);
		// sの値を絶対値にする
		sY = (float)fabsf(sY);
		// sの値を絶対値にする
		sZ = (float)fabsf(sZ);

		if (sX > 1)
		{
			Vec.x += (1 - sX) * LX;   // はみ出した部分のベクトル算出
		}
		if (sY > 1)
		{
			Vec.y += (1 - sY) * LY;   // はみ出した部分のベクトル算出
		}
		if (sZ > 1)
		{
			Vec.z += (1 - sZ) * LZ;   // はみ出した部分のベクトル算出
		}

	float fLength = D3DXVec3Length(&Vec);   // 長さを出力

	if (fLength < 10.0f)
	{
		Player* pPlayer = GetPlayer();
		D3DXVECTOR3 pVec = pPlayer->posOld - pPlayer->pos;
		D3DXVECTOR3 nor = D3DXVECTOR3(0.0f,0.0f,0.0f);

		// Xベクトルが一番大きかったら
		if (Vec.x > Vec.y && Vec.x > Vec.z)
		{
			nor.x = 1.0f;
		}
		// Xベクトルが一番小さかったら
		else if(Vec.x < Vec.y && Vec.x < Vec.z)
		{
			nor.x = -1.0f;
		}
		// Yベクトルが一難大きかったら
		if (Vec.y > Vec.x && Vec.y > Vec.z)
		{
			nor.y = 1.0f;
		}
		// Yベクトルが一番小さかったら
		else if (Vec.y < Vec.x && Vec.y < Vec.z)
		{
			nor.y = -1.0f;
		}
		// Zベクトルが一番大きかったら
		if (Vec.z > Vec.x && Vec.z > Vec.y)
		{
			nor.z = 1.0f;
		}
		// Zベクトルが一番小さかったら
		else if (Vec.z < Vec.x && Vec.z < Vec.y)
		{
			nor.z = -1.0f;
		}

		D3DXVECTOR3 test = nor * D3DXVec3Dot(&pVec, &nor);
		pPlayer->pos += test;
		DotOBBToPoint(obb, pPlayer->pos);
	}
}
void DotOBBToPoint(OBB& obb, D3DXVECTOR3& p)
{

}