//==============================================
//
// ���b�V���Ǖ\������[meshWall.cpp]
// Author:kaiti
//
//==============================================
#include "meshwall.h"
//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;
//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;

MeshWall g_MeshWall[MAX_MESHWALL];
//=================================
// ���b�V���ǂ̏���������
//=================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		g_MeshWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCnt].bUse = false;
	}
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kabe.jpg", &g_pTextureMeshWall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * WALLMAX_VTX * MAX_MESHWALL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffMeshWall,
		                        NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * WALLINDEX_NO * MAX_MESHWALL,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &g_pIdxBuffMeshWall,
							   NULL);

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		VERTEX_3D* pVtx = NULL;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntZ = 0; nCntZ <= WALLMESHVTX_Y; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= WALLMESHVTX_X; nCntX++)
			{
				//���_���W�̐ݒ�
				//pVtx[0].pos = D3DXVECTOR3(-WALLMESH_SIZE + (WALLMESH_SIZE * nCntX), 0.0f, WALLMESH_SIZE - (WALLMESH_SIZE * nCntZ));
				pVtx[0].pos = D3DXVECTOR3(-WALLMESH_SIZE + (WALLMESH_SIZE * nCntX), WALLMESH_SIZE - (WALLMESH_SIZE * nCntZ), g_MeshWall[nCnt].pos.z);

				//�@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((2.0f / WALLMESHVTX_X) * nCntX, (2.0f / WALLMESHVTX_Y) * nCntZ);

				pVtx++;
			}
		}
		//���_�o�b�t�@���A�����b�N�@
		g_pVtxBuffMeshWall->Unlock();

		//�C���f�b�N�X�o�b�t�@�����b�N
		WORD* pIdx = NULL;
		g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX, nCntZ;
		for (nCntZ = 0; nCntZ < WALLMESHVTX_Y; nCntZ++)
		{
			for (nCntX = 0; nCntX <= WALLMESHVTX_X; nCntX++)
			{
				//�C���f�b�N�X�̐ݒ�
				pIdx[0] = (WALLMESHVTX_X + 1) * (nCntZ + 1) + nCntX;
				pIdx[1] = nCntX + (nCntZ * (WALLMESHVTX_X + 1));

				pIdx += 2;
			}
			if (nCntZ <= WALLMESHVTX_Y - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntZ * (WALLMESHVTX_X + 1));
				pIdx[1] = (nCntX - 1) + (nCntZ * (WALLMESHVTX_X + 1)) + (WALLMESHVTX_X + 2) * (nCntZ + 1);

				pIdx += 2;
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffMeshWall->Unlock();
		////�C���f�b�N�X�̐ݒ�(��)
		//pIdx[0] = 3;
		//pIdx[1] = 0;
		//
		//pIdx[2] = 4;
		//pIdx[3] = 1;
		//
		//pIdx[4] = 5;
		//pIdx[5] = 2;
		//
		//pIdx[6] = 2;
		//pIdx[7] = 6;
		//
		//pIdx[8] = 6;
		//pIdx[9] = 3;
		//
		//pIdx[10] = 7;
		//pIdx[11] = 4;
		//
		//pIdx[12] = 8;
		//pIdx[13] = 5;
		//
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
	}
}
//===============================
// ���b�V���ǂ̏I������
//===============================
void UninitMeshWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}
//===============================
// ���b�V���ǂ̍X�V����
//===============================
void UpdateMeshWall(void)
{

}
//===============================
// ���b�V���ǂ̕`�揈��
//===============================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_MeshWall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWall[nCnt].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCnt].rot.y, g_MeshWall[nCnt].rot.x, g_MeshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCnt].mtxWorld, &g_MeshWall[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCnt].pos.x, g_MeshWall[nCnt].pos.y, g_MeshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCnt].mtxWorld, &g_MeshWall[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//���b�V���ǂ�`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, WALLMAX_VTX, 0, WALLPOLYGON_NO);
		}
	}
}
//===================
// ���b�V���ǂ̐ݒ�
//===================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_MeshWall[nCnt].bUse == false)
		{
			g_MeshWall[nCnt].pos = pos;
			g_MeshWall[nCnt].rot = rot;
			g_MeshWall[nCnt].bUse = true;
			break;
		}
	}
}