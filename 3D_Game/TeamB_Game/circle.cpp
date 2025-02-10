//=======================================================
// 
// �T�[�N��[circle.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "circle.h"

//�O���[�o���ϐ��錾
Circle g_Circle[MAX_CIRCLE];

//=====================
//�T�[�N���̏���������
//=====================
void InitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		g_Circle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Circle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Circle[nCnt].pVtxBuff = { NULL };
		g_Circle[nCnt].IndxBuff = { NULL };
		g_Circle[nCnt].fRadius = 0.0f;
		g_Circle[nCnt].bAnime = false;
		g_Circle[nCnt].bUse = false;
	}
}

//=====================
//�T�[�N���̏I������
//=====================
void UninitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		//�o�b�t�@�̔j��
		if (g_Circle[nCnt].pVtxBuff != NULL)
		{
			g_Circle[nCnt].pVtxBuff->Release();
			g_Circle[nCnt].pVtxBuff = NULL;
		}

		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_Circle[nCnt].IndxBuff != NULL)
		{
			g_Circle[nCnt].IndxBuff->Release();
			g_Circle[nCnt].IndxBuff = NULL;
		}
	}
}

//=====================
//�T�[�N���̍X�V����
//=====================
void UpdateCircle()
{

}

//=====================
//�T�[�N���̕`�揈��
//=====================
void DrawCircle()
{

}

//=====================
//�T�[�N���̐ݒ菈��
//=====================
void SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fRadius, bool bAnime, bool bUse)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == false)
		{
			//�e�ϐ��̐ݒ�
			g_Circle[nCnt].pos = pos;
			g_Circle[nCnt].rot = rot;
			g_Circle[nCnt].nDiviX = DiviX;
			g_Circle[nCnt].nDiviY = DiviY;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bAnime = bAnime;

			g_Circle[nCnt].nMaxVtx = (g_Circle[nCnt].nDiviX + 1) * (g_Circle[nCnt].nDiviY + 1);											//���_��
			g_Circle[nCnt].nPolyNum = (2 * g_Circle[nCnt].nDiviX * g_Circle[nCnt].nDiviY + (g_Circle[nCnt].nDiviY - 1) * 4);			//�|���S����
			int flindexNum = (2 * (g_Circle[nCnt].nDiviY * (2 + g_Circle[nCnt].nDiviX) - 1));											//�C���f�b�N�X

			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Circle[nCnt].nMaxVtx,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].pVtxBuff,
				NULL);

			//�C���f�b�N�X�J�E���^�[
			int indx = 0;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_Circle[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			for (int nCntY = 0; nCntY <= g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (int nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//�p�x�i�[
					float fAngle = (D3DX_PI * 2 / g_Circle[nCnt].nDiviX) * nCntX;

					//���_�̐ݒ�
					pVtx[indx].pos = D3DXVECTOR3(g_Circle[nCnt].fRadius * sinf(fAngle), 0.0f, g_Circle[nCnt].fRadius * cosf(fAngle));

					//���S�ւ̃x�N�g��
					D3DXVECTOR3 vec = pVtx[indx].pos - g_Circle[nCnt].pos;

					//�x�N�g���̐��K��,�e���_�̖@���̐ݒ�
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//���_�J���[�̐ݒ�
					pVtx[indx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//�e�N�X�`�����W�̐ݒ�
					pVtx[indx].tex = D3DXVECTOR2((1.0f / g_Circle[nCnt].nDiviX) * nCntX, (1.0f / g_Circle[nCnt].nDiviY) * nCntY);

					indx++;
				}
			}

			//���_�o�b�t�@���A�����b�N�@
			g_Circle[nCnt].pVtxBuff->Unlock();

			g_Circle[nCnt].bUse = true;
			break;
		}
	}
}