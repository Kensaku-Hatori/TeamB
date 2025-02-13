//****************************
// 
// Author: HATORI
// ポリゴン描画処理[effect.h]
// 
//****************************
#ifndef EFFECT_H_
#define EFFECT_H_

// インクルード
#include "main.h"
#include "Object.h"
#include "shadow.h"

// マクロ定義
#define MAX_EFFECT (4096)
#define MAX_SMOKEANIM (8)
#define SMOKEANIMSPEED (20)
#define MAX_SMOKELENGTH (float)(2)

// エフェクトの種類の列挙型
typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_SMOKE,
	EFFECT_SKILL,
	EFFECT_SKILLFLASH,
	EFFECT_MAGICCIRCLE,
	EFFECT_MAX
}EFFECTTYPE;

// エフェクトの構造体
typedef struct
{
	OBJECT Object;			// オブジェクト情報
	D3DXVECTOR3 Scale;		// スケール情報
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 dir;		// 向き
	EFFECTTYPE ntype;		// タイプ
	bool bUse;				// 使用状況
	int IndxShadow;			// 影のインデックス
	int nLife;				// 寿命
	D3DXCOLOR col;			// 色
	D3DXCOLOR colordiff;	// アルファ地の減少量
	int speed;				// 速さ
	float LengthValue;		// 大きくなる速度
	int AnimCount,Anim;		// アニメションの分割数とカウント
	int AnimSpeed,Indx;		// アニメーションの速さとインデックス
	float gravity;			// 重力
}EFFECT;

// エフェクトのテクスチャ
static const char* EFFECTTEX[EFFECT_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\smoke000.png",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\magiccircle.png",
};

//*****************
// プロトタイプ宣言
//*****************
void InitEffect(void);		// 初期化処理
void UninitEffect(void);	// 終了処置
void UpdateEffect(void);	// 更新処理
void DrawEffect(void);		// 描画処理
void SetEffect(D3DXVECTOR3 pos, 
	D3DXVECTOR3 dir,
	int nLife,
	float speed,
	D3DXVECTOR3 scale,
	D3DCOLOR col,
	EFFECTTYPE nType,
	int Indx,
	float gravity,
	D3DXVECTOR3 Rot);		// エフェクトの設定処理
void DeleteEffect(EFFECTTYPE nType, int Indx);	// エフェクトを削除する処理
void SetSkillParticle(EFFECTTYPE nType, int Indx,D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos,int Limit);	//
#endif // !BILLBOARD_H_