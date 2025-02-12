//==================================
//
//　ウインドウ表示処理[light.cpp]
//　Author:kaiti
//
//==================================
#include "light.h"
//グローバル変数
D3DLIGHT9 g_light[MAX_LIGHT]; //ライト情報
bool bUse[MAX_LIGHT];
//==================
// ライトの初期化
//==================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトをクリアする
		ZeroMemory(&g_light, sizeof(g_light));


		//ライトの拡散光を設定
		g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//ライトの色

		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.9f, -0.1f, 0.4f);

		//正規化する（大きさ１のベクトルにする）
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		g_light[nCnt].Direction = vecDir[nCnt];

		//ライトを設定
		pDevice->SetLight(nCnt, &g_light[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);

		bUse[nCnt] = false;
	}	
}
//====================
// ライトの終了処理
//====================
void UninitLight(void)
{

}
//====================
// ライトの更新処理
//====================
void UpdateLight(void)
{

}
//
//
//
void SetLight(D3DXVECTOR3 Dir, D3DXCOLOR Diffuse)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		if (bUse[nCnt] == false)
		{
			D3DXVECTOR3 vecDir;

			//ライトの種類を設定
			g_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//平行光源

			//ライトの拡散光を設定
			g_light[nCnt].Diffuse = Diffuse;//ライトの色

			//ライトの方向を設定
			vecDir = Dir;

			//正規化する（大きさ１のベクトルにする）
			D3DXVec3Normalize(&vecDir, &vecDir);
			g_light[nCnt].Direction = vecDir;

			//ライトを設定
			pDevice->SetLight(nCnt, &g_light[nCnt]);

			//ライトを有効にする
			pDevice->LightEnable(nCnt, TRUE);

			bUse[nCnt] = true;
			break;
		}
	}
}
//*****************
// ライトの取得処理
//*****************
D3DLIGHT9* GetLight()
{
	return &g_light[0];
}