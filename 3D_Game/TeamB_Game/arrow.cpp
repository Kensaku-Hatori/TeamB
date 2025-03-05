//=======================================================
// 
// ���[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

//�C���N���[�h
#include "arrow.h"

//�O���[�o���ϐ��錾
Arrow g_Arrow[MAX_ARROW];

//===================
//���̏���������
//===================
void InitArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		//�e�평����
		g_Arrow[nCnt].Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�ʒu
		g_Arrow[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�ւ̌���
		g_Arrow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_Arrow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_Arrow[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F
		g_Arrow[nCnt].VtxBuff = { NULL };//���_���
		g_Arrow[nCnt].tex = { NULL };//�e�N�X�`���|�C���^
		g_Arrow[nCnt].fHeight = 0.0;//�|���S���̍���
		g_Arrow[nCnt].fWidth = 0.0f;//�|���S���̕�
		g_Arrow[nCnt].fRadius = 0.0f;//pos����ǂꂾ��������
		g_Arrow[nCnt].Index = 0;
		g_Arrow[nCnt].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
}

//===================
//���̏I������
//===================
void UninitArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_Arrow[nCnt].tex != NULL)
		{
			g_Arrow[nCnt].tex->Release();
			g_Arrow[nCnt].tex = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_Arrow[nCnt].VtxBuff != NULL)
		{
			g_Arrow[nCnt].VtxBuff->Release();
			g_Arrow[nCnt].VtxBuff = NULL;
		}
	}
}

//===================
//���̍X�V����
//===================
void UpdateArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == true)
		{
			//�ړI�n�ւ̃x�N�g��
			D3DXVECTOR3 vec = g_Arrow[nCnt].Destpos - g_Arrow[nCnt].pos;
			float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);			//����
			float fAngle = 0.0f;												//�p�x
			float rotData = 0.0f;												//�p�x�̍�

			//�����̎擾
			fDistance = sqrtf(fDistance);

			//�p�x�̎擾
			fAngle = (float)atan2(vec.x, vec.z);

			//�ڕW�̈ړ������i�p�x�j�̕␳
			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2.0f;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2.0f;
			}

			//�ړI�ւ̌����ݒ�
			g_Arrow[nCnt].Destrot.y = fAngle;

			rotData = g_Arrow[nCnt].Destrot.y - g_Arrow[nCnt].rot.y;

			// �p�x�̋ߓ�
			if (rotData >= D3DX_PI)
			{
				g_Arrow[nCnt].rot.y += D3DX_PI * 2.0f;
			}
			else if (rotData <= -D3DX_PI)
			{
				g_Arrow[nCnt].rot.y -= D3DX_PI * 2.0f;
			}

			//�����̔��f
			g_Arrow[nCnt].rot.y += (g_Arrow[nCnt].Destrot.y - g_Arrow[nCnt].rot.y) * 0.1f;
		}
	}
}

//===================
//���̕`�揈��
//===================
void DrawArrow()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Arrow[nCnt].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow[nCnt].rot.y, g_Arrow[nCnt].rot.x, g_Arrow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Arrow[nCnt].mtxWorld, &g_Arrow[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Arrow[nCnt].pos.x, g_Arrow[nCnt].pos.y, g_Arrow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Arrow[nCnt].mtxWorld, &g_Arrow[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Arrow[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_Arrow[nCnt].VtxBuff, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Arrow[nCnt].tex);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//===================
//���̐ݒ菈��
//===================
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius, bool bGradation, bool bAnim)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	HRESULT hresult;

	int nCnt = 0;
	for (nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == false)
		{
			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Arrow[nCnt].VtxBuff,
				NULL);

			//�e�N�X�`���̓Ǎ�
			hresult = D3DXCreateTextureFromFile(pDevice,
				ARROW_TEX,
				&g_Arrow[nCnt].tex);

			if (FAILED(hresult))
			{
				return;
			}

			//�e��ݒ�
			g_Arrow[nCnt].Destpos = DestPos;
			g_Arrow[nCnt].pos = pos;
			g_Arrow[nCnt].col = col;
			g_Arrow[nCnt].fWidth = fWidth;
			g_Arrow[nCnt].fHeight = fHeight;
			g_Arrow[nCnt].fRadius = fRadius;
			g_Arrow[nCnt].bUse = true;

			//�����̐ݒ�------------------------------------------------------------
			D3DXVECTOR3 vec = g_Arrow[nCnt].Destpos - g_Arrow[nCnt].pos;
			float fAngle = 0.0f;										//�p�x�i�[�p

			//�p�x�̎擾
			fAngle = (float)atan2(vec.x, vec.z);

			//�ڕW�̈ړ������i�p�x�j�̕␳
			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2.0f;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2.0f;
			}

			//�����ݒ�
			g_Arrow[nCnt].rot.y = fAngle;

			//-------------------------------------------------------------------------

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_Arrow[nCnt].VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_Arrow[nCnt].fWidth * 0.5f, 1.0f, (g_Arrow[nCnt].fHeight + g_Arrow[nCnt].fRadius));
			pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCnt].fWidth * 0.5f, 1.0f, (g_Arrow[nCnt].fHeight + g_Arrow[nCnt].fRadius));
			pVtx[2].pos = D3DXVECTOR3(-g_Arrow[nCnt].fWidth * 0.5f, 1.0f, g_Arrow[nCnt].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCnt].fWidth * 0.5f, 1.0f, g_Arrow[nCnt].fRadius);

			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�F�̐ݒ�
			pVtx[0].col = g_Arrow[nCnt].col;
			pVtx[1].col = g_Arrow[nCnt].col;
			pVtx[2].col = g_Arrow[nCnt].col;
			pVtx[3].col = g_Arrow[nCnt].col;

			if (bGradation == true)
			{
				D3DXCOLOR colBottom = D3DCOLOR_RGBA(255, 255, 50, 204);
				pVtx[2].col = colBottom;
				pVtx[3].col = colBottom;
			}

			//�e�N�X�`���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N�@
			g_Arrow[nCnt].VtxBuff->Unlock();

			break;
		}
	}
}
//===================
//���̈ʒu�̍X�V����
//===================
void SetPositonArrow(int nIdex, D3DXVECTOR3 pos)
{
	g_Arrow[nIdex].pos = D3DXVECTOR3(pos.x, g_Arrow[nIdex].pos.y, pos.z);
}
