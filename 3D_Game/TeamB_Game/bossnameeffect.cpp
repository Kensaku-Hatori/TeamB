//*********************************************************
// 
// ボスのムービーの名前[bossnameeffect.cpp]
// Author:Hatori
// 
//*********************************************************

#include "bossnameeffect.h"
#include <cassert>

#define BACESIZEX (float)(10)
#define BACESIZEY (float)(10)

BOSSNAMEEFFECT g_BossName;

bool isReVerse(float V);
bool isFade(NAMEFADE FadeType);
bool isSetCondition();
bool isUseNameEffect();
bool CreatNameBuffer();
bool isGreaterLife(int Count);
bool isGreaterFade();

void UpdateTexUV(float U,float V);
void UpdateSizeAnim(float U, float V);
void UpdateAlphaAnim();

void InitBossNameEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossname1.png", &g_BossName.Tex);

	g_BossName.fAngle = atan2f(BACESIZEX,BACESIZEY);
	g_BossName.Length = sqrtf(BACESIZEX + BACESIZEY);
}
void UninitBossNameEffect()
{
	UninitBuffer(g_BossName.Buff);
	UninitTexture(g_BossName.Tex);
}
void UpdateBossNameEffect()
{
	static float U = 0.0f;
	static float V = 0.0f;
	if (isUseNameEffect() == true)
	{
		UpdateTexUV(U,V);

		UpdateSizeAnim(U,V);

		UpdateAlphaAnim();

		if (isReVerse(V) == true)
		{
			g_BossName.FadeCounter++;
			if (isGreaterFade() == true)
			{
				g_BossName.FadeCounter = 0;
				g_BossName.Fade = NAMEFADE_OUT;
			}
		}
		if (isFade(NAMEFADE_IN) == true)
		{
			g_BossName.Col.a += (1.1f - g_BossName.Col.a) * 0.05f;
			U += (1.0f - U) * 0.1f;
			V += (1.0f - V) * 0.1f;
		}
		else if (isFade(NAMEFADE_OUT) == true)
		{
			g_BossName.Col.a += (-0.1f - g_BossName.Col.a) * 0.05f;
			U += (-0.1f - U) * 0.1f;
			V += (-0.1f - V) * 0.1f;
		}

		g_BossName.nLife--;
		if (isGreaterLife(0) == false)
		{
			g_BossName.bUse = false;
			U = 0.0f;
			V = 0.0f;
		}
	}
}
void DrawBossNameEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (isUseNameEffect() == true)
	{
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_BossName.Buff, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_BossName.Tex);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
void SetBossNameEffect(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR2 Scale, D3DXCOLOR Col,int nLife)
{
	if (isSetCondition() == true)
	{
		g_BossName.bUse = true;
		g_BossName.Pos = Pos;
		g_BossName.Rot = Rot;
		g_BossName.Scale = Scale;
		g_BossName.Col = Col;
		g_BossName.nLife = nLife;
		g_BossName.Fade = NAMEFADE_IN;
		g_BossName.FadeCounter = 0;

		//頂点バッファの生成・頂点情報の設定
		VERTEX_2D* pVtx;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

		////一個目のポリゴン
		//pVtx[0].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.y - 25.0f;
		//pVtx[0].pos.y = Pos.y - cosf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.x - 150.0f;
		//pVtx[0].pos.z = 0.0f;//0.0f;

		//pVtx[1].pos.x = Pos.x - sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x + 150.0f;
		//pVtx[1].pos.y = Pos.y - cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y - 25.0f;
		//pVtx[1].pos.z = 0.0f;//0.0f;

		//pVtx[2].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x - 150.0f;
		//pVtx[2].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y + 25.0f;
		//pVtx[2].pos.z = 0.0f;//0.0f;

		//pVtx[3].pos.x = Pos.x + sinf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x + 150.0f;
		//pVtx[3].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y + 25.0f;
		//pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		////テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_BossName.Buff->Unlock();
	}
	else
	{
		assert(false);
	}
}

bool isSetCondition()
{
	return isUseNameEffect() == false && CreatNameBuffer() == true;
}
bool isUseNameEffect()
{
	return g_BossName.bUse;
}
bool CreatNameBuffer()
{
	HRESULT hresult;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	hresult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_BossName.Buff,
		NULL);
	if (FAILED(hresult)) return false;
	else return true;
}
bool isGreaterLife(int Count)
{
	return g_BossName.nLife > Count;
}

void UpdateTexUV(float U,float V)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, V);
	pVtx[3].tex = D3DXVECTOR2(U, V);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Unlock();
}
void UpdateSizeAnim(float U, float V)
{
	D3DXVECTOR3 Pos = g_BossName.Pos;
	D3DXVECTOR3 Rot = g_BossName.Rot;
	D3DXVECTOR2 Scale = g_BossName.Scale;
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//一個目のポリゴン
	pVtx[0].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.y - 25.0f;
	pVtx[0].pos.y = Pos.y - cosf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.x - 150.0f;
	pVtx[0].pos.z = 0.0f;//0.0f;

	pVtx[1].pos.x = Pos.x - sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x * U;//pos.x + 150.0f;
	pVtx[1].pos.y = Pos.y - cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y - 25.0f;
	pVtx[1].pos.z = 0.0f;//0.0f;

	pVtx[2].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x - 150.0f;
	pVtx[2].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y * V;//pos.y + 25.0f;
	pVtx[2].pos.z = 0.0f;//0.0f;

	pVtx[3].pos.x = Pos.x + sinf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.x * U;//pos.x + 150.0f;
	pVtx[3].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y * V;//pos.y + 25.0f;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Unlock();
}
void UpdateAlphaAnim()
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(g_BossName.Col);
	pVtx[1].col = D3DXCOLOR(g_BossName.Col);
	pVtx[2].col = D3DXCOLOR(g_BossName.Col);
	pVtx[3].col = D3DXCOLOR(g_BossName.Col);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_BossName.Buff->Unlock();
}
bool isFade(NAMEFADE FadeType)
{
	return g_BossName.Fade == FadeType;
}
bool isReVerse(float V)
{
	return V >= 0.8f;
}
bool isGreaterFade()
{
	return g_BossName.FadeCounter >= FADE_TIME;
}