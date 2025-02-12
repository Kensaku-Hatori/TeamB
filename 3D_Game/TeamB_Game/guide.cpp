//=======================================================
// 
// �U������[guide.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "guide.h"
#include "circle.h"
#include "player.h"

//�O���[�o���ϐ��錾
Guide g_Guide;					//�U���\����

//===============
// ����������
//===============
void InitGuide()
{
	g_Guide.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Guide.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Guide.bUse = false;
}

//===============
//�I������
//===============
void UninitGuide()
{

}

//===============
//�X�V����
//===============
void UpdateGuide()
{

}

//================
//�`�揈��
//================
void DrawGuide()
{

}

//================
//�ݒ菈��
//================
void SetGuide()
{
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();

	//�T�[�N���̐ݒ�
	SetCircle(pPlayer->pos, pPlayer->rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), 16, 0, 20.0f, 25.0f, true, false);
}