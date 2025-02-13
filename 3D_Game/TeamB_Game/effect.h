//****************************
// 
// Author: HATORI
// �|���S���`�揈��[effect.h]
// 
//****************************
#ifndef EFFECT_H_
#define EFFECT_H_

// �C���N���[�h
#include "main.h"
#include "Object.h"
#include "shadow.h"

// �}�N����`
#define MAX_EFFECT (4096)
#define MAX_SMOKEANIM (8)
#define SMOKEANIMSPEED (20)
#define MAX_SMOKELENGTH (float)(2)

// �G�t�F�N�g�̎�ނ̗񋓌^
typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_SMOKE,
	EFFECT_SKILL,
	EFFECT_SKILLFLASH,
	EFFECT_MAGICCIRCLE,
	EFFECT_MAX
}EFFECTTYPE;

// �G�t�F�N�g�̍\����
typedef struct
{
	OBJECT Object;			// �I�u�W�F�N�g���
	D3DXVECTOR3 Scale;		// �X�P�[�����
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 dir;		// ����
	EFFECTTYPE ntype;		// �^�C�v
	bool bUse;				// �g�p��
	int IndxShadow;			// �e�̃C���f�b�N�X
	int nLife;				// ����
	D3DXCOLOR col;			// �F
	D3DXCOLOR colordiff;	// �A���t�@�n�̌�����
	int speed;				// ����
	float LengthValue;		// �傫���Ȃ鑬�x
	int AnimCount,Anim;		// �A�j���V�����̕������ƃJ�E���g
	int AnimSpeed,Indx;		// �A�j���[�V�����̑����ƃC���f�b�N�X
	float gravity;			// �d��
}EFFECT;

// �G�t�F�N�g�̃e�N�X�`��
static const char* EFFECTTEX[EFFECT_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\smoke000.png",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\magiccircle.png",
};

//*****************
// �v���g�^�C�v�錾
//*****************
void InitEffect(void);		// ����������
void UninitEffect(void);	// �I�����u
void UpdateEffect(void);	// �X�V����
void DrawEffect(void);		// �`�揈��
void SetEffect(D3DXVECTOR3 pos, 
	D3DXVECTOR3 dir,
	int nLife,
	float speed,
	D3DXVECTOR3 scale,
	D3DCOLOR col,
	EFFECTTYPE nType,
	int Indx,
	float gravity,
	D3DXVECTOR3 Rot);		// �G�t�F�N�g�̐ݒ菈��
void DeleteEffect(EFFECTTYPE nType, int Indx);	// �G�t�F�N�g���폜���鏈��
void SetSkillParticle(EFFECTTYPE nType, int Indx,D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos,int Limit);	//
#endif // !BILLBOARD_H_