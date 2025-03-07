//==============================
//
//  ミニマップ処理[minimap.cpp]
//  Author:kaiti
//
//==============================
#include "minimap.h"
#include "player.h"
#include "camera.h"
//グローバル変数
//枠
LPDIRECT3DTEXTURE9 g_pTextureMiniMap = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMiniMap = NULL;
//プレイヤーアイコン
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;

//敵アイコン
LPDIRECT3DTEXTURE9 pTextureMapEnemy = NULL;

D3DXVECTOR3 g_MiniMappos;
D3DXVECTOR3 g_MapPlayerpos;

MiniMapEnemy g_MiniMapEnemy[MAX_ENEMY];
//=============
// 初期化処理
//=============
void InitMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\radar-6370407_1280.png", &g_pTextureMiniMap);	//枠
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ownmachine.jpg", &g_pTextureMapPlayer);		//HP 


	g_MiniMappos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	g_MapPlayerpos = D3DXVECTOR3(1800.0f, 100.0f, 0.0f);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//枠
	{		
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMiniMap,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMiniMap->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y + MINIMAP_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y + MINIMAP_Y, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffMiniMap->Unlock();
	}

	//プレイヤーアイコン
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMapPlayer,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffMapPlayer->Unlock();
	}

}
//==========
// 終了処理
//==========
void UninitMiniMap(void)
{
	//テクスチャの破棄
	if (g_pTextureMiniMap != NULL && g_pTextureMapPlayer != NULL)
	{
		g_pTextureMiniMap->Release();
		g_pTextureMiniMap = NULL;
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMiniMap != NULL && g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMiniMap->Release();
		g_pVtxBuffMiniMap = NULL;
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy != NULL)
		{
			g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy->Release();
			g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy = NULL;
		}
	}
	if (pTextureMapEnemy != NULL)
	{
		pTextureMapEnemy->Release();
		pTextureMapEnemy = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateMiniMap(void)
{
	MODE mode = GetMode();

	if (mode == MODE_STAGEONE || mode == MODE_STAGETWO || mode == MODE_STAGETHREE || mode == MODE_STAGEFOUR)
	{
		SetMapPlayer(mode);
	}
}
void UpdateMiniMapEnemy(int Indx,D3DXVECTOR3 PosEnemy)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	g_MiniMapEnemy[Indx].MiniMappos = PosEnemy;
	float fAngle,fDistance;
	D3DXVECTOR3 MathPos;
	MathPos.x = g_MiniMapEnemy[Indx].MiniMappos.x - pPlayer->pos.x;
	MathPos.z = g_MiniMapEnemy[Indx].MiniMappos.z - pPlayer->pos.z;
	fAngle = atan2f(MathPos.x, MathPos.z);

	fDistance = fabsf(sqrtf(MathPos.x * MathPos.x + MathPos.z * MathPos.z));
	if (fDistance >= 100.0f)
	{
		fDistance = 100.0f;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_MiniMapEnemy[Indx].pVtxBuffMapEnemy->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR2 Pos = { g_MapPlayerpos.x ,g_MapPlayerpos.y };
	Pos.x -= sinf(fAngle) * fDistance;
	Pos.y += cosf(fAngle) * fDistance;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x, Pos.y + MAPSIZE_PLAYER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y + MAPSIZE_PLAYER, 0.0f);

	//頂点バッファをアンロック
	g_MiniMapEnemy[Indx].pVtxBuffMapEnemy->Unlock();
}
//===========
// 描画処理
//===========
void DrawMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//枠
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMiniMap, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMiniMap);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//アイテム欄
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMapPlayer);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if(g_MiniMapEnemy->bUse == true)
		{//アイテム欄
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy, 0, sizeof(VERTEX_2D));
			//テクスチャの設定
			pDevice->SetTexture(0, pTextureMapEnemy);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}
//==========================
// プレイヤーアイコン設定
//==========================
void SetMapPlayer(int nStageNo)
{
	//ステージごとの場所変更（仮）
	if (nStageNo == MODE_STAGEONE)
	{
		g_MapPlayerpos = D3DXVECTOR3(1110.0f, 100.0f, 0.0f);
	}
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffMapPlayer->Unlock();
}
int SetMapEnemy(D3DXVECTOR3 Pos)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();
	int MaxpEnemyCount = 0;
	for (MaxpEnemyCount = 0; MaxpEnemyCount < MAX_ENEMY; MaxpEnemyCount++)
	{
		if (g_MiniMapEnemy[MaxpEnemyCount].bUse == false)
		{
			g_MiniMapEnemy[MaxpEnemyCount].bUse = true;
			g_MiniMapEnemy[MaxpEnemyCount].MiniMappos = Pos;
			float fAngle;
			fAngle = atan2f(pPlayer->pos.x - Pos.x, pPlayer->pos.z - Pos.z);

			//頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy,
				NULL);
			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy->Lock(0, 0, (void**)&pVtx, 0);

			D3DXVECTOR2 Pos = { g_MapPlayerpos.x ,g_MapPlayerpos.y};
			Pos.x += sinf(fAngle) * 100.0f;
			Pos.y += cosf(fAngle) * 100.0f;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Pos.x, Pos.y + MAPSIZE_PLAYER, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y + MAPSIZE_PLAYER, 0.0f);
			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//頂点バッファをアンロック
			g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy->Unlock();

			break;
		}
	}
	return MaxpEnemyCount;
}
void DeleteEnemyMiniMap(int Indx)
{
	g_MiniMapEnemy[Indx].bUse = false;
}