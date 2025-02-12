//=======================================================
// 
// �T�[�N��[circle.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "circle.h"

//�O���[�o���ϐ��錾
Circle g_Circle[MAX_CIRCLE];

//=========================
//�T�[�N���̏���������
//=========================
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

//=========================
//�T�[�N���̏I������
//=========================
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

//=========================
//�T�[�N���̍X�V����
//=========================
void UpdateCircle()
{

}

//=========================
//�T�[�N���̕`�揈��
//=========================
void DrawCircle()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O��؂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Circle[nCnt].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Circle[nCnt].rot.y, g_Circle[nCnt].rot.x, g_Circle[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Circle[nCnt].pos.x, 0.0f, g_Circle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Circle[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X����f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_Circle[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_Circle[nCnt].IndxBuff);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Circle[nCnt].nMaxVtx, 0, g_Circle[nCnt].nPolyNum);

		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�J�����O������
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
//�T�[�N���̐ݒ菈��
//=========================
int SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int DiviX, int DiviY, float fHeight, float fRadius, bool bGradation, bool bAnime)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;
	int nCnt = 0;

	for (nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == false)
		{
			//�e�ϐ��̐ݒ�
			g_Circle[nCnt].pos = pos;
			g_Circle[nCnt].rot = rot;
			g_Circle[nCnt].col = col;
			g_Circle[nCnt].nDiviX = DiviX;
			g_Circle[nCnt].nDiviY = DiviY + 1;
			g_Circle[nCnt].fHeight = fHeight;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bGradation = bGradation;																						//�O���f�[�V�����̗L��
			g_Circle[nCnt].bAnime = bAnime;																								//�����̗L��

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
					float fAngle = ((D3DX_PI * 2 / g_Circle[nCnt].nDiviX) * nCntX);

					//�����̊i�[
					float fHeight = (g_Circle[nCnt].fHeight / g_Circle[nCnt].nDiviY) * (g_Circle[nCnt].nDiviY - nCntY);

					//���_�̐ݒ�
					pVtx[indx].pos = D3DXVECTOR3(g_Circle[nCnt].fRadius * sinf(fAngle), fHeight, g_Circle[nCnt].fRadius * cosf(fAngle));

					//���S�ւ̃x�N�g��
					D3DXVECTOR3 vec = pVtx[indx].pos - g_Circle[nCnt].pos;

					//�x�N�g���̐��K��,�e���_�̖@���̐ݒ�
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//���_�J���[�̐ݒ�
					pVtx[indx].col = g_Circle[nCnt].col;

					//�O���f�[�V�����L�Ȃ�
					if (g_Circle[nCnt].bGradation == true)
					{
						pVtx[indx].col = D3DXCOLOR(g_Circle[nCnt].col.r, g_Circle[nCnt].col.g, g_Circle[nCnt].col.b, (g_Circle[nCnt].col.a / (g_Circle[nCnt].nDiviY + 1)) * (nCntY + 1));
					}

					//�e�N�X�`�����W�̐ݒ�
					pVtx[indx].tex = D3DXVECTOR2((1.0f / g_Circle[nCnt].nDiviX) * nCntX, (1.0f / g_Circle[nCnt].nDiviY) * nCntY);

					indx++;
				}
			}

			//���_�o�b�t�@���A�����b�N�@
			g_Circle[nCnt].pVtxBuff->Unlock();

			//�C���f�b�N�X�o�b�t�@�̐���
			pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].IndxBuff,
				NULL);

			//�C���f�b�N�X�o�b�t�@�����b�N
			g_Circle[nCnt].IndxBuff->Lock(0, 0, (void**)&pIdx, 0);

			int nCntX = 0;
			for (int nCntY = 0; nCntY < g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//�C���f�b�N�X�̐ݒ�
					pIdx[0] = (g_Circle[nCnt].nDiviX + 1) * (nCntY + 1) + nCntX;
					pIdx[1] = nCntX + (nCntY * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}

				//���ރ|���S����
				if (nCntY < g_Circle[nCnt].nDiviY - 1)
				{
					//�C���f�b�N�X�̐ݒ�
					pIdx[0] = (nCntX - 1) + (nCntY * (g_Circle[nCnt].nDiviX + 1));
					pIdx[1] = nCntX + ((nCntY + 1) * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}
			}

			//�C���f�b�N�X�o�b�t�@���A�����b�N
			g_Circle[nCnt].IndxBuff->Unlock();

			g_Circle[nCnt].bUse = true;

			break;
		}
	}
		return nCnt;
}

//=========================
//�T�[�N���̈ʒu�̍X�V����
//=========================
void  SetPositionCircle(int indx, D3DXVECTOR3  pos, D3DXVECTOR3 rot)
{
	g_Circle[indx].pos = pos;
	g_Circle[indx].rot = rot;
}