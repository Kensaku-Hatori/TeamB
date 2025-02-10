//=======================================================
// 
// ���[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "arrow.h"

//�O���[�o���ϐ��錾
Arrow g_Arrow;

//===================
//���̏���������
//===================
void InitArrow()
{
	g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Arrow.fHeight = 0.0;
	g_Arrow.fWidth = 0.0f;
	g_Arrow.bUse = false;

}

//===================
//���̏I������
//===================
void UninitArrow()
{
	if (g_Arrow.VtxBuff != NULL)
	{
		g_Arrow.VtxBuff->Release();
		g_Arrow.VtxBuff = NULL;
	}
}

//===================
//���̍X�V����
//===================
void UpdateArrow()
{

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

	if (g_Arrow.bUse == true)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Arrow.mtxWorld);

		//�����𔽓]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow.rot.y, g_Arrow.rot.x, g_Arrow.rot.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Arrow.pos.x, g_Arrow.pos.y, g_Arrow.pos.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Arrow.mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_Arrow.VtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�|���S����`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//���̐ݒ菈��
//===================
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_Arrow.VtxBuff,
		NULL);

	//�e��ݒ�
	g_Arrow.pos = pos;
	g_Arrow.rot = rot;
	g_Arrow.fWidth = fWidth;
	g_Arrow.fHeight = fHeight;
	g_Arrow.bUse = true;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_Arrow.VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-g_Arrow.fWidth * 0.5f, 0.0f, g_Arrow.fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 0.0f, g_Arrow.fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-g_Arrow.fWidth * 0.5f, 0.0f, -g_Arrow.fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 0.0f, -g_Arrow.fHeight * 0.5f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N�@
	g_Arrow.VtxBuff->Unlock();
}