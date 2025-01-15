//================================
//
// �G�t�F�N�g����[Effect.cpp]
// Author:kaiti
//
//================================
#include "effect.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
LPDIRECT3DTEXTURE9 g_apTextureEffect[1] = {};
Effect g_Effect[MAX_EFFECT];
//=========================
// �G�t�F�N�g�̏���������
//=========================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_Effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_Effect[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_apTextureEffect[0]); //1

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffEffect,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x - EFFECT_SIZE, g_Effect[nCnt].pos.y + EFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x + EFFECT_SIZE, g_Effect[nCnt].pos.y + EFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x - EFFECT_SIZE, g_Effect[nCnt].pos.y - EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x + EFFECT_SIZE, g_Effect[nCnt].pos.y - EFFECT_SIZE, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//=======================
// �G�t�F�N�g�̏I������
//=======================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureEffect[0] != NULL)
	{
		g_apTextureEffect[0]->Release();
		g_apTextureEffect[0] = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//=======================
// �G�t�F�N�g�̍X�V����
//=======================
void UpdateEffect(void)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			g_Effect[nCnt].pos += g_Effect[nCnt].move;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[1].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[2].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[3].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);

			g_Effect[nCnt].nLife -= 1;
			//�G�t�F�N�g�̎���
			if (g_Effect[nCnt].nLife <= 0)
			{
				g_Effect[nCnt].bUse = false;
			}
			g_Effect[nCnt].fRadius -= 0.5f;
			//
			if (g_Effect[nCnt].fRadius <= 0)
			{
				g_Effect[nCnt].fRadius = 0;
			}
			g_Effect[nCnt].col.a -= 0.05f;
			if (g_Effect[nCnt].col.a <= 0.0f)
			{
				g_Effect[nCnt].col.a = 0.0f;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//=======================
// �G�t�F�N�g�̕`�揈��
//=======================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Effect[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_Effect[nCnt].mtxWorld._11 = mtxView._11;
			g_Effect[nCnt].mtxWorld._12 = mtxView._21;
			g_Effect[nCnt].mtxWorld._13 = mtxView._31;
			g_Effect[nCnt].mtxWorld._21 = mtxView._12;
			g_Effect[nCnt].mtxWorld._22 = mtxView._22;
			g_Effect[nCnt].mtxWorld._23 = mtxView._32;
			g_Effect[nCnt].mtxWorld._31 = mtxView._13;
			g_Effect[nCnt].mtxWorld._32 = mtxView._23;
			g_Effect[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCnt].pos.x, g_Effect[nCnt].pos.y, g_Effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect[0]);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// �G�t�F�N�g�̐ݒ�
//===================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, float fRadius)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == false)
		{
			g_Effect[nCnt].pos = D3DXVECTOR3(pos.x,pos.y,pos.z);
			g_Effect[nCnt].move = move;
			g_Effect[nCnt].nLife = nLife;
			g_Effect[nCnt].fRadius = fRadius;
			g_Effect[nCnt].col = color;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCnt].fRadius, g_Effect[nCnt].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCnt].fRadius, g_Effect[nCnt].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCnt].fRadius, -g_Effect[nCnt].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCnt].fRadius, -g_Effect[nCnt].fRadius, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[1].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[2].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[3].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);

			g_Effect[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}