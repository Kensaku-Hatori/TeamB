//********************************************************
// 
// �Ռ��g[impact.cpp]
// Author:Hatori
// 
//********************************************************

//*************
// �C���N���[�h
//*************
#include "impact.h"
#include "enemy.h"
#include "Player.h"

//*******************
// �O���[�o���ϐ��錾
//*******************
RINGIMPACT g_Impact[MAX_IMPACT];

// �W�Ƃ��̂��VERTICAL
// �Q�Ƃ��̂��HORIZON

//*******************
// �Ռ��g�̏���������
//*******************
void InitImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		g_Impact[ImpactCount].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].nLife = 0;
		g_Impact[ImpactCount].inringsize = 0;
		g_Impact[ImpactCount].outringsize = 0;
		g_Impact[ImpactCount].Horizon = 0;
		g_Impact[ImpactCount].Vertex = 0;
		g_Impact[ImpactCount].Vertical = 0;
		g_Impact[ImpactCount].Polygone = 0;
		g_Impact[ImpactCount].IndxVertex = 0;
		g_Impact[ImpactCount].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].AlphaDef = 0.0f;
		g_Impact[ImpactCount].Speed = 0.0f;
		g_Impact[ImpactCount].bUse = false;
	}
}

//*****************
// �Ռ��g�̏I������
//*****************
void UninitImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		UninitIndxBuffer(g_Impact[ImpactCount].pIdxBuffImpact);
		UninitBuffer(g_Impact[ImpactCount].pVtxBuffImpact);
		UninitTexture(g_Impact[ImpactCount].pTextureImpact);
	}
}
//*****************
// �Ռ��g�̍X�V����
//*****************
void UpdateImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].bUse == true)
		{
			int nCnt = 0;

			//�L���鏈��
			g_Impact[ImpactCount].nLife--;
			g_Impact[ImpactCount].col.a -= g_Impact[ImpactCount].AlphaDef;
			g_Impact[ImpactCount].inringsize = g_Impact[ImpactCount].inringsize + g_Impact[ImpactCount].Speed;
			g_Impact[ImpactCount].outringsize = g_Impact[ImpactCount].outringsize + g_Impact[ImpactCount].Speed;

			VERTEX_3D* pVtx = NULL;

			// ���_�o�b�t�@�����b�N
			g_Impact[ImpactCount].pVtxBuffImpact->Lock(0, 0, (void**)&pVtx, 0);

			//g_Impact[ImpactCount].col.a -= g_Impact[ImpactCount].AlphaDef;

			//����
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;

				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;

				//�e�N�X�`�����W�̐ݒ�
				pVtx[nCnt].tex = D3DXVECTOR2(0.5f * vertexcount, 0.5f);

				//���_�J���[�̐ݒ�
				pVtx[nCnt].col = D3DXCOLOR(g_Impact[ImpactCount].col);

				// ���_���W�̍X�V
				pVtx[nCnt].pos.x = 0.0f + sinf(ratioH) * g_Impact[ImpactCount].inringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = 0.0f + cosf(ratioH) * g_Impact[ImpactCount].inringsize;

				//�x�N�g���̌v�Z
				MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);

				//�@���̐��K��
				D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				nCnt++;
			}

			//�O��
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(0.5f * vertexcount, 0.5f);
				pVtx[nCnt].col = D3DXCOLOR(g_Impact[ImpactCount].col);

				// ���_���W�̍X�V
				pVtx[nCnt].pos.x = 0.0f + sinf(ratioH) * g_Impact[ImpactCount].outringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = 0.0f + cosf(ratioH) * g_Impact[ImpactCount].outringsize;

				//���@�Ȃ�
				if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
				{
					pVtx[nCnt].pos.y = -PROFOUND;
				}

				//�x�N�g��
				MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);

				//�@���̐��K��
				D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				nCnt++;
			}

			// ���_�o�b�t�@���A�����b�N
			g_Impact[ImpactCount].pVtxBuffImpact->Unlock();

			//���l��0�ɂȂ�����g���Ă��Ȃ���Ԃɂ���
			if (g_Impact[ImpactCount].col.a < 0.0f)
			{
				g_Impact[ImpactCount].bUse = false;
			}

			//�������s�����Ȃ�g���Ă��Ȃ���Ԃɂ���
			else if (g_Impact[ImpactCount].nLife <= 0.0f)
			{
				g_Impact[ImpactCount].bUse = false;
			}

			////�����蔻��
			//switch (g_Impact[ImpactCount].nType)
			//{
			//case IMPACTTYPE_NORMAL:
			//	//collisionImpact(ImpactCount);
			//	break;

			//case IMPACTTYPE_ENEMY:
			//	//collisionImpactPlayer(ImpactCount);
			//	break;

			//}
		}
	}
}
//*****************
// �Ռ��g�̕`�揈��
//*****************
void DrawImpact(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].bUse == true)
		{
			//���@�Ȃ�
			if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
			{
				// ���Z������ݒ肷��
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Impact[ImpactCount].Object.mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Impact[ImpactCount].Object.Rot.y, g_Impact[ImpactCount].Object.Rot.x, g_Impact[ImpactCount].Object.Rot.z);
			D3DXMatrixMultiply(&g_Impact[ImpactCount].Object.mtxWorld, &g_Impact[ImpactCount].Object.mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Impact[ImpactCount].Object.Pos.x, g_Impact[ImpactCount].Object.Pos.y, g_Impact[ImpactCount].Object.Pos.z);
			D3DXMatrixMultiply(&g_Impact[ImpactCount].Object.mtxWorld, &g_Impact[ImpactCount].Object.mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Impact[ImpactCount].Object.mtxWorld);

			// ���_�o�b�t�@���f�o�C�X����f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_Impact[ImpactCount].pVtxBuffImpact, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_Impact[ImpactCount].pIdxBuffImpact);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Impact[ImpactCount].pTextureImpact);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Impact[ImpactCount].Vertex, 0, g_Impact[ImpactCount].Polygone);

			//���@�Ȃ�
			if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************
// �Ռ��g�̐ݒ菈��
//*****************
void SetImpact(IMPACTTYPE nType, D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float inringsize,float outringsize, int Horizon, int Vertical,float Speed, float RotY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾����

	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].bUse == false)
		{
			g_Impact[ImpactCount].bUse = true;

			g_Impact[ImpactCount].nLife = nLife;
			g_Impact[ImpactCount].nType = nType;
			g_Impact[ImpactCount].Speed = Speed;
			g_Impact[ImpactCount].AlphaDef = col.a / nLife;
			g_Impact[ImpactCount].Object.Pos = pos;
			g_Impact[ImpactCount].Horizon = Horizon;
			g_Impact[ImpactCount].Vertical = Vertical;
			g_Impact[ImpactCount].Vertex = (Vertical + 1) * (Horizon);
			g_Impact[ImpactCount].Polygone = (Vertical) * 2;
			g_Impact[ImpactCount].IndxVertex = (Vertical + 1) * (Horizon);
			g_Impact[ImpactCount].inringsize = inringsize;
			g_Impact[ImpactCount].outringsize = outringsize;
			g_Impact[ImpactCount].col = col;
			g_Impact[ImpactCount].Object.Rot.y = RotY;

			// ���@�̂Ƃ��p�x��ς���
			if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
			{
				g_Impact[ImpactCount].Object.Rot.x = - D3DX_PI * 0.5f;
			}

			////�e�N�X�`���̓ǂݍ���
			//D3DXCreateTextureFromFile(pDevice,
			//	IMPACTTEX[0],
			//	&g_Impact[ImpactCount].pTextureImpact);

			// ���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Impact[ImpactCount].Vertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,		// ���_�t�H�[�}�b�g
				D3DPOOL_MANAGED,
				&g_Impact[ImpactCount].pVtxBuffImpact, NULL);

			VERTEX_3D* pVtx = NULL;

			// ���_�o�b�t�@�����b�N
			g_Impact[ImpactCount].pVtxBuffImpact->Lock(0, 0, (void**)&pVtx, 0);

			int nCnt = 0;

			//����
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[nCnt].col = D3DXCOLOR(col);

				// ���_���W�̍X�V
				pVtx[nCnt].pos.x = sinf(ratioH) * inringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = cosf(ratioH) * inringsize;
				//MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				//D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				nCnt++;
			}

			//�O��
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f,1.0f);
				pVtx[nCnt].col = D3DXCOLOR(col);

				// ���_���W�̍X�V
				pVtx[nCnt].pos.x = sinf(ratioH) * outringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = cosf(ratioH) * outringsize;

				//MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				//D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				nCnt++;
			}

			// ���_�o�b�t�@���A�����b�N
			g_Impact[ImpactCount].pVtxBuffImpact->Unlock();

			// �C���f�b�N�X�o�b�t�@�̐���
			pDevice->CreateIndexBuffer(sizeof(WORD) * g_Impact[ImpactCount].IndxVertex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Impact[ImpactCount].pIdxBuffImpact,
				NULL);

			WORD* pIdx = NULL;

			// ���_�o�b�t�@�����b�N
			g_Impact[ImpactCount].pIdxBuffImpact->Lock(0, 0, (void**)&pIdx, 0);

			int Indx = Vertical + 1;	// �X�^�[�g�n�_
			int Indx1 = 0;			// �[������X�^�[�g������
			int Indx2 = 0;			// �z��

			for (int IndxCount1 = 0; IndxCount1 <= Vertical; IndxCount1++)
			{
				pIdx[Indx2] = Indx;

				pIdx[Indx2 + 1] = Indx1;

				// �z�񂸂炷
				Indx2 += 2;
				Indx++;
				Indx1++;
			}

			// ���_�o�b�t�@���A�����b�N
			g_Impact[ImpactCount].pIdxBuffImpact->Unlock();

			break;
		}
	}
}

RINGIMPACT* GetImpact()
{
	return &g_Impact[0];
}