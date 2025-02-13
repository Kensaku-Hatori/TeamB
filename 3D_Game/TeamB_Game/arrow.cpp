//=======================================================
// 
// ���[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

//�C���N���[�h
#include "arrow.h"

//�O���[�o���ϐ��錾
Arrow g_Arrow;

//===================
//���̏���������
//===================
void InitArrow()
{
	//�e�평����
	g_Arrow.Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�ʒu
	g_Arrow.Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�ւ̌���
	g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
	g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	g_Arrow.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F
	g_Arrow.VtxBuff = { NULL };//���_���
	g_Arrow.tex = { NULL };//�e�N�X�`���|�C���^
	g_Arrow.fHeight = 0.0;//�|���S���̍���
	g_Arrow.fWidth = 0.0f;//�|���S���̕�
	g_Arrow.fRadius = 0.0f;//pos����ǂꂾ��������
	g_Arrow.bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
}

//===================
//���̏I������
//===================
void UninitArrow()
{
	//�e�N�X�`���̔j��
	if (g_Arrow.tex != NULL)
	{
		g_Arrow.tex->Release();
		g_Arrow.tex = NULL;
	}

	//���_�o�b�t�@�̔j��
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
		//�ړI�n�ւ̃x�N�g��
		D3DXVECTOR3 vec = g_Arrow.Destpos - g_Arrow.pos;
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
		g_Arrow.Destrot.y = fAngle;

		rotData = g_Arrow.Destrot.y - g_Arrow.rot.y;

		// �p�x�̋ߓ�
		if (rotData >= D3DX_PI)
		{
			g_Arrow.rot.y += D3DX_PI * 2.0f;
		}
		else if (rotData <= -D3DX_PI)
		{
			g_Arrow.rot.y -= D3DX_PI * 2.0f;
		}

		//�����̔��f
		g_Arrow.rot.y += (g_Arrow.Destrot.y - g_Arrow.rot.y) * 0.1f;
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
		pDevice->SetTexture(0, g_Arrow.tex);

		//�|���S����`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//���̐ݒ菈��
//===================
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	HRESULT hresult;

	if (g_Arrow.bUse == false)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_Arrow.VtxBuff,
			NULL);

		//�e�N�X�`���̓Ǎ�
		hresult = D3DXCreateTextureFromFile(pDevice,
			ARROW_TEX,
			&g_Arrow.tex);

		if (FAILED(hresult))
		{
			return;
		}

		//�e��ݒ�
		g_Arrow.Destpos = DestPos;
		g_Arrow.pos = pos;
		g_Arrow.col = col;
		g_Arrow.fWidth = fWidth;
		g_Arrow.fHeight = fHeight;
		g_Arrow.fRadius = fRadius;
		g_Arrow.bUse = true;

		//�����̐ݒ�------------------------------------------------------------
		D3DXVECTOR3 vec = g_Arrow.Destpos - g_Arrow.pos;
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
		g_Arrow.rot.y = fAngle;

		//-------------------------------------------------------------------------

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_Arrow.VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(- g_Arrow.fWidth * 0.5f, 1.0f, (g_Arrow.fHeight + g_Arrow.fRadius));
		pVtx[1].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 1.0f, (g_Arrow.fHeight + g_Arrow.fRadius));
		pVtx[2].pos = D3DXVECTOR3(- g_Arrow.fWidth * 0.5f, 1.0f,  g_Arrow.fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 1.0f,  g_Arrow.fRadius);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�F�̐ݒ�
		pVtx[0].col = g_Arrow.col;
		pVtx[1].col = g_Arrow.col;
		pVtx[2].col = g_Arrow.col;
		pVtx[3].col = g_Arrow.col;

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N�@
		g_Arrow.VtxBuff->Unlock();
	}
}

//===================
//���̈ʒu�̍X�V����
//===================
void SetPositonArrow(D3DXVECTOR3 pos)
{
	g_Arrow.pos = D3DXVECTOR3(pos.x, g_Arrow.pos.y, pos.z);
}
