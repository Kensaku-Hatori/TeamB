//============================================================
//
//アイテム[Item.cpp]
//Author:Rio Ohno
//
//============================================================

#include"Item.h"
#include "player.h"
#include "itemui.h"
#include "score.h"

//グロ－バル変数宣言
Item g_Item[MAX_ITEM];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemBill =  NULL ;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureItemBill[NUM_ITEMTYPE] = { NULL };			//テクスチャへのポインタ(ちゅーる)
int g_nCntItem = 0;														//画面上のアイテム数

//============================================================
// モデルの初期化処理
//============================================================
void InitItem()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntItem = 0;														//画面上のアイテム数の初期化

	for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
	{
		//テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureItemBill[nCnt]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemBill,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffItemBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//各種初期化
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_Item[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
		g_Item[nCntItem].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//直径
		g_Item[nCntItem].nIndexShadow = 0;								//影のインデックス
		g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;						//アイテムが消えるまでの時間
		g_Item[nCntItem].bUse = false;									//使用しいていない状態
		g_Item[nCntItem].bDesp = true;									//とりあえずモデルってことにしとく

		//頂点座標の設定
		pVtx[0].pos.x = g_Item[nCntItem].pos.x - ITEM_RADIUS;
		pVtx[0].pos.y = g_Item[nCntItem].pos.y + ITEM_RADIUS * 2.0f;
		pVtx[0].pos.z = g_Item[nCntItem].pos.z;

		pVtx[1].pos.x = g_Item[nCntItem].pos.x + ITEM_RADIUS;
		pVtx[1].pos.y = g_Item[nCntItem].pos.y + ITEM_RADIUS * 2.0f;
		pVtx[1].pos.z = g_Item[nCntItem].pos.z;

		pVtx[2].pos.x = g_Item[nCntItem].pos.x - ITEM_RADIUS;
		pVtx[2].pos.y = g_Item[nCntItem].pos.y;
		pVtx[2].pos.z = g_Item[nCntItem].pos.z;

		pVtx[3].pos.x = g_Item[nCntItem].pos.x + ITEM_RADIUS;
		pVtx[3].pos.y = g_Item[nCntItem].pos.y;
		pVtx[3].pos.z = g_Item[nCntItem].pos.z;

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffItemBill->Unlock();
}

//============================================================
// モデルの終了処理
//============================================================
void UninitItem()
{
	//バッファの破棄
	if (g_pVtxBuffItemBill != NULL)
	{
		g_pVtxBuffItemBill->Release();
		g_pVtxBuffItemBill = NULL;
	}

	//テクスチャの破棄
	for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
	{
		if (g_pTextureItemBill[nCnt] != NULL)
		{
			g_pTextureItemBill[nCnt]->Release();
			g_pTextureItemBill[nCnt] = NULL;
		}
	}
}

//============================================================
// モデルの更新処理
//============================================================
void UpdateItem()
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			//フレームデクリメント
			g_Item[nCntItem].nCntTime--;

			//アイテムの点滅
			if (g_Item[nCntItem].nCntTime <= 0)
			{
				g_Item[nCntItem].bUse = false;
				g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;				//消えるまでのフレーム初期化
				g_nCntItem--;											//ドロップ中のアイテム数デクリメント
			}
			else if (g_Item[nCntItem].nCntTime <= ITEM_TIME_DEL / 2.0f)
			{
				if ((g_Item[nCntItem].nCntTime % 2) == 0)
				{
					g_Item[nCntItem].bDesp = g_Item[nCntItem].bDesp ? false : true;
				}
			}
			else if (g_Item[nCntItem].nCntTime <= ITEM_TIME_DEL / 4.0f)
			{
				if ((g_Item[nCntItem].nCntTime % 8) == 0)
				{
					g_Item[nCntItem].bDesp = g_Item[nCntItem].bDesp ? false : true;
				}
			}

			//当たり判定
			CollisionItem(nCntItem);
		}
	}
}

//============================================================
// アイテム(ビルボード)の描画処理
//============================================================
void DrawItemBillboard()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true )
		{
			if (g_Item[nCntItem].bDesp == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Item[nCntItem].mtxWorld);

				D3DXMATRIX mtxView;//ビューマトリックス

				//ビューマトリックスの取得
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//カメラの逆行列を設定
				g_Item[nCntItem].mtxWorld._11 = mtxView._11;
				g_Item[nCntItem].mtxWorld._12 = mtxView._21;
				g_Item[nCntItem].mtxWorld._13 = mtxView._31;
				g_Item[nCntItem].mtxWorld._21 = mtxView._12;
				g_Item[nCntItem].mtxWorld._22 = mtxView._22;
				g_Item[nCntItem].mtxWorld._23 = mtxView._32;
				g_Item[nCntItem].mtxWorld._31 = mtxView._13;
				g_Item[nCntItem].mtxWorld._32 = mtxView._23;
				g_Item[nCntItem].mtxWorld._33 = mtxView._33;

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y, g_Item[nCntItem].pos.z);
				D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntItem].mtxWorld);

				//頂点バッファをデバイスのデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffItemBill, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャ座標の設定
				pDevice->SetTexture(0, g_pTextureItemBill[g_Item[nCntItem].type]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
			}
		}
	}

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================
// アイテムの設定処理
//============================================================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをロック
	g_pVtxBuffItemBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (type < NUM_ITEMTYPE && g_nCntItem < MAX_ITEM)//最大ドロップ数を超えてないなら
		{
			if (g_Item[nCntItem].bUse == false)
			{
				g_Item[nCntItem].bUse = true;								//使用している状態にする
				g_Item[nCntItem].bDesp = true;								//描画する
				g_Item[nCntItem].pos = pos;									//位置の設定
				g_Item[nCntItem].type = type;								//種類の設定
				g_nCntItem++;												//アイテム数カウント
				g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;					//消えるまでのフレーム初期化

				break;
			}
		}
		else if (g_nCntItem >= MAX_ITEM)//最大ドロップ数を超えてるなら
		{
			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffItemBill->Unlock();

}

//============================================================
// アイテムの取得処理
//============================================================
void CollisionItem(int nIndexItem)
{
	if (g_Item[nIndexItem].bUse == true)
	{
		//プレイヤーの情報取得
		Player* pPlayer = GetPlayer();
		float Radius = 0;					//半径

		//プレイヤーの半径取得
		D3DXVECTOR3 playerRadius = pPlayer->size / 2.0f;

		//距離
		float Distance = (pPlayer->pos.x - g_Item[nIndexItem].pos.x) * (pPlayer->pos.x - g_Item[nIndexItem].pos.x) +
						 (pPlayer->pos.z - g_Item[nIndexItem].pos.z) * (pPlayer->pos.z - g_Item[nIndexItem].pos.z);

		//２つの半径
		Radius = (playerRadius.z + ITEM_RADIUS) * (playerRadius.z + ITEM_RADIUS);

		if (Distance <= Radius)//当たってるなら
		{
			g_Item[nIndexItem].bUse = false;						//使用していない状態にする
			g_Item[nIndexItem].nCntTime = 0;						//消えるまでのフレーム初期化
			g_nCntItem--;											//ドロップ中のアイテム数デクリメント
			ItemAbility(nIndexItem);
		}
	}
}

//=================
// アイテムの効果
//=================
void ItemAbility(int nIndexItem)
{
	Player* pPlayer = GetPlayer();

	switch (g_Item[nIndexItem].type)
	{
	case ITEMTYPE_HP:
		AddItemUI(g_Item[nIndexItem].type);
		break;

	case ITEMTYPE_MP:
		AddItemUI(g_Item[nIndexItem].type);
		break;

	case ITEMTYPE_SPEED:
		pPlayer->Status.fPower += 30.0f;
		break;

	default:
		break;
	}

	AddScore(100);
}