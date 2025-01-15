//================================
//
// ��������[Explosion.cpp]
// Author:kaiti
//
//================================
#include "explosion.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
LPDIRECT3DTEXTURE9 g_apTextureExplosion[1] = {};
Explosion g_Explosion[MAX_EXPLOSION];
//=========================
// �����̏���������
//=========================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		g_Explosion[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].nCounterAnim = 0;
		g_Explosion[nCnt].nPattemAnim = 0;
		g_Explosion[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_apTextureExplosion[0]); //1

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffExplosion,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x - 25.0f, g_Explosion[nCnt].pos.y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x - 25.0f, g_Explosion[nCnt].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x + 25.0f, g_Explosion[nCnt].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x + 25.0f, g_Explosion[nCnt].pos.y + 25.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//=======================
// �����̏I������
//=======================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureExplosion[0] != NULL)
	{
		g_apTextureExplosion[0]->Release();
		g_apTextureExplosion[0] = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=======================
// �����̍X�V����
//=======================
void UpdateExplosion(void)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			g_Explosion[nCnt].nCounterAnim++;

			if ((g_Explosion[nCnt].nCounterAnim % 5) == 0)
			{//��莞�Ԍo��
				//�p�^�[��No���X�V
				g_Explosion[nCnt].nPattemAnim = (g_Explosion[nCnt].nPattemAnim + 1) % 8;

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f + 0.125f, 1.0f);
			}
			if (g_Explosion[nCnt].nCounterAnim >= 32)
			{
				g_Explosion[nCnt].bUse = false;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//=======================
// �����̕`�揈��
//=======================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Explosion[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_Explosion[nCnt].mtxWorld._11 = mtxView._11;
			g_Explosion[nCnt].mtxWorld._12 = mtxView._21;
			g_Explosion[nCnt].mtxWorld._13 = mtxView._31;
			g_Explosion[nCnt].mtxWorld._21 = mtxView._12;
			g_Explosion[nCnt].mtxWorld._22 = mtxView._22;
			g_Explosion[nCnt].mtxWorld._23 = mtxView._32;
			g_Explosion[nCnt].mtxWorld._31 = mtxView._13;
			g_Explosion[nCnt].mtxWorld._32 = mtxView._23;
			g_Explosion[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCnt].pos.x, g_Explosion[nCnt].pos.y, g_Explosion[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCnt].mtxWorld, &g_Explosion[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureExplosion[0]);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// �����̐ݒ�
//===================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{
			g_Explosion[nCnt].pos = D3DXVECTOR3(pos.x, pos.y + 30, pos.z);
			//g_Explosion[nCnt].rot = rot;
			g_Explosion[nCnt].nCounterAnim = 0;
			g_Explosion[nCnt].nPattemAnim = 0;

			g_Explosion[nCnt].bUse = true;
			break;
		}
	}
}