//================================
//
// 弾処理[skill.cpp]
// Author:kaiti
//
//================================
#include "skill.h"
#include "shadow.h"
#include "explosion.h"
#include "player.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"
#include "enemy.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkill = NULL;
LPDIRECT3DTEXTURE9 g_apTextureSkill[1] = {};
Skill g_Skill[MAX_SKILL];
//=========================
// 弾の初期化処理
//=========================
void InitSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		g_Skill[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].nLife = SKILL_LIFE;
		g_Skill[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureSkill[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SKILL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffSkill,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSkill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffSkill->Unlock();
}
//=======================
// 弾の終了処理
//=======================
void UninitSkill(void)
{
	//テクスチャの破棄
	if (g_apTextureSkill[0] != NULL)
	{
		g_apTextureSkill[0]->Release();
		g_apTextureSkill[0] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSkill != NULL)
	{
		g_pVtxBuffSkill->Release();
		g_pVtxBuffSkill = NULL;
	}
}
//=======================
// 弾の更新処理
//=======================
void UpdateSkill(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Shadow* pShadow;
	pShadow = GetShadow();
	
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			SkillCollision(nCnt);

			SetEffect(g_Skill[nCnt].pos,
					  D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					  10.0f,
					  0.0f, 
					  D3DXVECTOR3(3.0f, 3.0f, 3.0f), 
					  D3DXCOLOR(0.80f, 1.00f, 0.00f,1.0f),
					  EFFECT_NONE);

			g_Skill[nCnt].pos += g_Skill[nCnt].move;

			g_Skill[nCnt].move.x += sinf(g_Skill[nCnt].rot.y - D3DX_PI) * 0.5f;
			g_Skill[nCnt].move.z += cosf(g_Skill[nCnt].rot.y - D3DX_PI) * 0.5f;

			g_Skill[nCnt].nLife -= 1;

			if (g_Skill[nCnt].nLife <= 0)
			{
				g_Skill[nCnt].bUse = false;
				pShadow[g_Skill[nCnt].nIdxShadow].bUse = false;
			}
		}
	}
}
//=======================
// 弾の描画処理
//=======================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Skill[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_Skill[nCnt].mtxWorld._11 = mtxView._11;
			g_Skill[nCnt].mtxWorld._12 = mtxView._21;
			g_Skill[nCnt].mtxWorld._13 = mtxView._31;
			g_Skill[nCnt].mtxWorld._21 = mtxView._12;
			g_Skill[nCnt].mtxWorld._22 = mtxView._22;
			g_Skill[nCnt].mtxWorld._23 = mtxView._32;
			g_Skill[nCnt].mtxWorld._31 = mtxView._13;
			g_Skill[nCnt].mtxWorld._32 = mtxView._23;
			g_Skill[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Skill[nCnt].pos.x, g_Skill[nCnt].pos.y, g_Skill[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Skill[nCnt].mtxWorld, &g_Skill[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Skill[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSkill, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureSkill[0]);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// 弾の設定
//===================
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == false)
		{
			g_Skill[nCnt].pos = D3DXVECTOR3(pos.x, pos.y + 30, pos.z);
			g_Skill[nCnt].move = move;
			g_Skill[nCnt].rot = rot;
			g_Skill[nCnt].nLife = SKILL_LIFE;
			g_Skill[nCnt].bUse = true;
			break;
		}
	}
}
//
// 敵と魔法の当たり判定
//
void SkillCollision(int nIdx)
{
	ENEMY* pEnemy = GetEnemy();
	Player* pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			g_Skill[nIdx].fDistance = sqrtf(((g_Skill[nIdx].pos.x - pEnemy->Object.Pos.x) * (g_Skill[nIdx].pos.x - pEnemy->Object.Pos.x))
										  + ((g_Skill[nIdx].pos.y - pEnemy->Object.Pos.y) * (g_Skill[nIdx].pos.y - pEnemy->Object.Pos.y))
										  + ((g_Skill[nIdx].pos.z - pEnemy->Object.Pos.z) * (g_Skill[nIdx].pos.z - pEnemy->Object.Pos.z)));

			float RADIUS = (pEnemy->Radius + SKILL_SIZE) * (pEnemy->Radius + SKILL_SIZE);

			if (g_Skill[nIdx].fDistance <= RADIUS)
			{
				HitEnemy(pPlayer->Status.fPower,nCntEnemy);
			}
		}
	}
}