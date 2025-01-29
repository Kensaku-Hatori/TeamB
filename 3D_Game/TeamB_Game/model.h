//============================
//
// ���f���\������[model.h]
// Author:kaiti
//
//============================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MAX_TEX (32)
#define MAX_PARTS (15)//�p�[�c�̍ő吔
#define MAX_STAGEMODEL (128)

typedef enum
{
	MODELTYPE_ZERO = 0,
	MODELTYPE_ONE,
	MODELTYPE_TWO,
	MODELTYPE_THREE,
	MODELTYPE_FOUR,
	MODELTYPE_FIVE,
	MODELTYPE_SIX,
	MODELTYPE_SEVEN,
	MODELTYPE_EIGHT,
	MODELTYPE_NINE,
	MODELTYPE_TEN,
	MODELTYPE_ELEVEN,
	MODELTYPE_TWELVE,
	MODELTYPE_THIRTEEN,
	MODELTYPE_MAX
}MODELTYPE;

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;			//�}�e���A���̐�
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	int nIndx, Parent;
	D3DXVECTOR3 pos;		//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 OffSet;
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 size;		//�T�C�Y
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture[128];
}MODELINFO;

typedef struct
{
	LPD3DXMESH pMesh;		//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;			//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTexture[MAX_TEX];
}MODELORIGIN;

typedef struct
{
	MODELORIGIN ModelBuff;
	MODELTYPE nType;
	D3DXVECTOR3 pos;		//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;
}STAGEMODEL;

void InitStageModel();
void UninitStageModel();
void UpdateStageModel();
void DrawStageModel();
void SetStageModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType);
void SetStageModelInfo(char *ModelPath[],int nType);
#endif