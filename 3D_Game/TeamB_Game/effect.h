//****************************
// 
// Author: HATORI
// �|���S���`�揈��(������)[billboard.h]
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

typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_SMOKE,
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
	int AnimSpeed;
}EFFECT;

static const char* EFFECTTEX[EFFECT_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\smoke000.png",
};

//*****************
// �v���g�^�C�v�錾
//*****************
void InitEffect(void);		// ����������
void UninitEffect(void);	// �I�����u
void UpdateEffect(void);	// �X�V����
void DrawEffect(void);		// �`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int nLife,int speed,D3DXVECTOR3 scale,D3DCOLOR col,EFFECTTYPE nType);
#endif // !BILLBOARD_H_