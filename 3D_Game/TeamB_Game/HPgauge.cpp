//=========================================================
// 
// �G��HP�Q�[�W[HPgauge.cpp]
// Aothor:Rio Ohno
// 
//=========================================================

#include"HPgauge.h"

//�O���[�o���ϐ��錾
HPgauge g_HPgauge[MAX_HPGAUGE];

//==============
// ����������
//==============
void InitHPgauge()
{
	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//�\���̂̏�����
		g_HPgauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_HPgauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
		g_HPgauge[nCnt].pVtxHPgaugeBuff = NULL;							//���_���
		g_HPgauge[nCnt].nLife = 0;										//�̗�
		g_HPgauge[nCnt].bUse = false;									//�g�p���Ă��Ȃ���Ԃɂ���
	}
}