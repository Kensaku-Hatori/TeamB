//****************************
// 
// Author: HATORI
// ポリゴン描画処理(未完成)[billboard.h]
// 
//****************************
#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "Object.h"
#include "shadow.h"


#define MAX_EFFECT (4096)
#define MAX_SMOKEANIM (8)
#define SMOKEANIMSPEED (20)
#define MAX_SMOKELENGTH (float)(2)
#define SKILL_COL (D3DXCOLOR(0.25f,0.45f,1.0f,1.0f)

typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_SMOKE,
	EFFECT_SKILL,
	EFFECT_SKILLFLASH,
	EFFECT_MAX
}EFFECTTYPE;

typedef struct
{
	OBJECT Object;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 move;
	D3DXVECTOR3 dir;
	EFFECTTYPE ntype;
	bool bUse;
	int IndxShadow;
	int nLife;
	D3DXCOLOR col;
	D3DXCOLOR colordiff;
	int speed;
	float LengthValue;
	int AnimCount,Anim;
	int AnimSpeed,Indx;
	float gravity;
}EFFECT;

static const char* EFFECTTEX[EFFECT_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\smoke000.png",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\effect000.jpg",
};

//*****************
// プロトタイプ宣言
//*****************
void InitEffect(void);		// 初期化処理
void UninitEffect(void);	// 終了処置
void UpdateEffect(void);	// 更新処理
void DrawEffect(void);		// 描画処理
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int nLife,float speed,D3DXVECTOR3 scale,D3DCOLOR col,EFFECTTYPE nType,int Indx,float gravity,D3DXVECTOR3 Rot);
void DeleteEffect(EFFECTTYPE nType, int Indx);
void SetSkillParticle(EFFECTTYPE nType, int Indx,D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos,int Limit);
#endif // !BILLBOARD_H_