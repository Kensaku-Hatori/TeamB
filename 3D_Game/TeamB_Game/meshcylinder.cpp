//==============================================
//
// ���b�V���~���\������[MeshCylinder.cpp]
// Author:kaiti
//
//==============================================
#include "meshcylinder.h"
//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;
//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;

D3DXVECTOR3 g_posMeshCylinder;//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;//����
D3DXMATRIX g_mtxWorldMeshCylinder;//���[���h�}�g���b�N�X

//=================================
// ���b�V���~���̏���������
//=================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posMeshCylinder = D3DXVECTOR3(0.0f, -500.0f, 0.0f);
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kabe.jpg", &g_pTextureMeshCylinder);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAXCYLINDER_VTX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffMeshCylinder,
		                        NULL);
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * CYLINDERINDEX_NO,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &g_pIdxBuffMeshCylinder,
							   NULL);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//�~��
	int radius = 3000;
	int index = 0;
	float fAngle = (D3DX_PI * 2.0f) / MESHCYLINDERVTX_X;

	for (int nCntV = 0; nCntV < MESHCYLINDERVTX_Z + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < MESHCYLINDERVTX_X + 1; nCntH++)
		{
			//�p�x
			float Angle = fAngle * nCntH;

			//���_���W�̐ݒ�
			pVtx[index].pos = D3DXVECTOR3(sinf(Angle) * radius, 1000.0f *(MESHCYLINDERVTX_Z - nCntV), cosf(Angle) * radius);
			
			D3DXVECTOR3 nor;//�ʒu
			nor = pVtx[index].pos - g_posMeshCylinder;
			//nor = g_posMeshCylinder - pVtx[index].pos;

			//�@���x�N�g��
			D3DXVec3Normalize(&pVtx[index].nor,&nor);

			//���_�J���[�̐ݒ�
			pVtx[index].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[index].tex = D3DXVECTOR2((1.0f / MESHCYLINDERVTX_X) * nCntH, (1.0f / MESHCYLINDERVTX_Z) * nCntV);

			index++;
		}
	}

	//���_�o�b�t�@���A�����b�N�@
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);
	
	int nCntX;
	for (int nCntZ = 0; nCntZ < MESHCYLINDERVTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX <= MESHCYLINDERVTX_X; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (MESHCYLINDERVTX_X + 1) * (nCntZ + 1) + nCntX;
			pIdx[1] = nCntX + (nCntZ * (MESHCYLINDERVTX_X + 1));

			pIdx += 2;
		}
		if (nCntZ < MESHCYLINDERVTX_Z - 1)
		{
			pIdx[0] = (nCntX - 1) + (nCntZ * (MESHCYLINDERVTX_X + 1));
			pIdx[1] = (nCntX - 1) + (nCntZ * (MESHCYLINDERVTX_X + 1)) + (MESHCYLINDERVTX_X + 2) * (nCntZ + 1);

			pIdx += 2;
		}
	}

	////�C���f�b�N�X�̐ݒ�(�~��)
	//pIdx[0] = 9;
	//pIdx[1] = 0;
	//
	//pIdx[2] = 10;
	//pIdx[3] = 1;
	//
	//pIdx[4] = 11;
	//pIdx[5] = 2;
	//
	//pIdx[6] = 12;
	//pIdx[7] = 3;
	//
	//pIdx[8] = 13;
	//pIdx[9] = 4;
	//
	//pIdx[10] = 14;
	//pIdx[11] = 5;
	//
	//pIdx[12] = 15;
	//pIdx[13] = 6;
	//
	//pIdx[14] = 16;
	//pIdx[15] = 7;
	//
	//pIdx[16] = 9;
	//pIdx[17] = 0;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();
}
//===============================
// ���b�V���~���̏I������
//===============================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}
//===============================
// ���b�V���~���̍X�V����
//===============================
void UpdateMeshCylinder(void)
{

}
//===============================
// ���b�V���~���̕`�揈��
//===============================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//���b�V���~����`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAXCYLINDER_VTX, 0, CYLINDERPOLYGON_NO);
}