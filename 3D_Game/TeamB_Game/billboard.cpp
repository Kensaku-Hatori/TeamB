//==================================
//
// �r���{�[�h����[Biillboard.cpp]
// Author:kaiti
//
//==================================

#include "billboard.h"
#include "shadow.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBiillboard = NULL;
LPDIRECT3DTEXTURE9 g_apTextureBiillboard[MAX_BILLBOARD] = {};
Biillboard g_Biillboard[MAX_BILLBOARD];

//=========================
// �r���{�[�h�̏���������
//=========================
void InitBiillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾����
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Biillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Biillboard[nCnt].bUse = false;
	}

	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\move.jpg", &g_apTextureBiillboard[0]); // �ړ�


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBiillboard,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBiillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Biillboard[nCnt].pos.x - 65.0f, g_Biillboard[nCnt].pos.y + 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Biillboard[nCnt].pos.x + 65.0f, g_Biillboard[nCnt].pos.y + 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Biillboard[nCnt].pos.x - 65.0f, g_Biillboard[nCnt].pos.y - 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Biillboard[nCnt].pos.x + 65.0f, g_Biillboard[nCnt].pos.y - 40.0f, 0.0f);

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
	g_pVtxBuffBiillboard->Unlock();
}

//=======================
// �r���{�[�h�̏I������
//=======================
void UninitBiillboard(void)
{
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureBiillboard[nCnt] != NULL)
		{
			g_apTextureBiillboard[nCnt]->Release();
			g_apTextureBiillboard[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBiillboard != NULL)
	{
		g_pVtxBuffBiillboard->Release();
		g_pVtxBuffBiillboard = NULL;
	}
}

//=======================
// �r���{�[�h�̍X�V����
//=======================
void UpdateBiillboard(void)
{
}

//=======================
// �r���{�[�h�̕`�揈��
//=======================
void DrawBiillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Biillboard[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Biillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_Biillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Biillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Biillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Biillboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Biillboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Biillboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Biillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Biillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Biillboard[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Biillboard[nCnt].pos.x, g_Biillboard[nCnt].pos.y, g_Biillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Biillboard[nCnt].mtxWorld, &g_Biillboard[nCnt].mtxWorld, &mtxTrans);


			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Biillboard[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBiillboard, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBiillboard[nCnt]);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===================
// �r���{�[�h�̐ݒ�
//===================
void SetBiillboard(D3DXVECTOR3 pos)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Biillboard[nCnt].bUse == false)
		{
			g_Biillboard[nCnt].pos = pos;

			g_Biillboard[nCnt].bUse = true;
			break;
		}
	}
}