//============================
//
// ���f���\������[model.h]
// Author:kaiti
//
//============================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MAX_PARTS (15)//�p�[�c�̍ő吔

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

#endif
