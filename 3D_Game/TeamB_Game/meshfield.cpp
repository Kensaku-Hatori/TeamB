//==============================================
//
// ���b�V�����\������[meshfield.cpp]
// Author:kaiti
//
//==============================================

#include "meshfield.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;						//���_���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield[MESH_NUM_MAX] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;						//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

MeshField g_Meshfield[MESH_NUM_MAX];									//�|���S��(��)�̍\����

//=================================
// ���b�V�����̏���������
//=================================
void InitMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//�\���̂̏�����
		g_Meshfield[nCnt].pos = D3DXVECTOR3(-900.0f, 0.0f, 900.0f);		//�ʒu
		g_Meshfield[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
		g_Meshfield[nCnt].textype = MESH_TEX_NULL;						//�e�N�X�`���^�C�v
		g_Meshfield[nCnt].DiviX = 0;									//������x
		g_Meshfield[nCnt].DiviZ = 0;									//������z
		g_Meshfield[nCnt].fWidth = 0.0f;								//��
		g_Meshfield[nCnt].fHeight = 0.0f;								//����
		g_Meshfield[nCnt].bUse = false;									//�g�p���Ă��Ȃ���Ԃɂ���

		//�e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			MESHFIELD_TEXTURE[g_Meshfield[nCnt].textype],
			&g_pTextureMeshfield[nCnt]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_NO,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

		VERTEX_3D* pVtx = NULL;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= MESHVTX_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESHVTX_X; nCntX++)
		{
			//���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(-MESH_SIZE + (MESH_SIZE * nCntX), 0.0f, MESH_SIZE - (MESH_SIZE * nCntZ));
			pVtx[0].pos = D3DXVECTOR3(-MESH_SIZE + (MESH_SIZE * nCntX), 0.0f, MESH_SIZE - (MESH_SIZE * nCntZ));

				//�@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((1.0f / MESHVTX_X) * nCntX, (1.0f / MESHVTX_Z) * nCntZ);

				pVtx++;
			}
		}

		////�~��
		//int radius = 150;
		//int index = 0;
		//float fAngle = (D3DX_PI * 2) / MESHVTX_X;
		//
		//for (int nCntV = 0; nCntV < MESHVTX_Z + 1; nCntV++)
		//{
		//	for (int nCntH = 0; nCntH < MESHVTX_X + 1; nCntH++)
		//	{
		//		//�p�x
		//		float Angle = fAngle * nCntH;
		//
		//		//���_���W�̐ݒ�
		//		pVtx[index].pos = D3DXVECTOR3(sinf(Angle) * radius, 50.0f * (nCntV + 1), cosf(Angle) * radius);
		//		
		//		D3DXVECTOR3 nor;//�ʒu
		//		nor = pVtx[index].pos - g_posMeshfield;
		//		//�@���x�N�g��
		//		D3DXVec3Normalize(&pVtx[index].nor,&nor);
		//		
		//		//���_�J���[�̐ݒ�
		//		pVtx[index].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		//		//�e�N�X�`�����W�̐ݒ�
		//		pVtx[index].tex = D3DXVECTOR2((1.0f / MESHVTX_X) * nCntH, (1.0f / MESHVTX_Z) * nCntV);
		//
		//		index++;
		//	}
		//}

		//���_�o�b�t�@���A�����b�N�@
		g_pVtxBuffMeshfield->Unlock();

		WORD* pIdx;

		//�C���f�b�N�X�o�b�t�@�����b�N
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX;
		for (int nCntZ = 0; nCntZ < MESHVTX_Z; nCntZ++)
		{
			for (nCntX = 0; nCntX <= MESHVTX_X; nCntX++)
			{
				//�C���f�b�N�X�̐ݒ�
				pIdx[0] = (MESHVTX_X + 1) * (nCntZ + 1) + nCntX;
				pIdx[1] = nCntX + (nCntZ * (MESHVTX_X + 1));

				pIdx += 2;
			}
			if (nCntZ < MESHVTX_Z - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntZ * (MESHVTX_X + 1));
				pIdx[1] = (nCntX - 1) + (nCntZ * (MESHVTX_X + 1)) + (MESHVTX_X + 2) * (nCntZ + 1);

				pIdx += 2;
			}
		}

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

		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffMeshField->Unlock();
	
}

//===============================
// ���b�V�����̏I������
//===============================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MESH_TEX_MAX; nCnt++)
	{
		if (g_pTextureMeshfield[nCnt] != NULL)
		{
			g_pTextureMeshfield[nCnt]->Release();
			g_pTextureMeshfield[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//===============================
// ���b�V�����̍X�V����
//===============================
void UpdateMeshfield(void)
{

}

//===============================
// ���b�V�����̕`�揈��
//===============================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		if (g_Meshfield[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Meshfield[nCnt].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meshfield[nCnt].rot.y, g_Meshfield[nCnt].rot.x, g_Meshfield[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Meshfield[nCnt].mtxWorld, &g_Meshfield[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Meshfield[nCnt].pos.x, g_Meshfield[nCnt].pos.y, g_Meshfield[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Meshfield[nCnt].mtxWorld, &g_Meshfield[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Meshfield[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshfield[g_Meshfield[nCnt].textype]);

			//���b�V������`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VTX, 0, POLYGON_NO);
		}
	}
}