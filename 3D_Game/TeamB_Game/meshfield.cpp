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
float maxVtx = 0.0f, polyNum = 0.0f, indexNum = 0.0f;					

//�t�@�C���i�[
static const char* MESHFIELD_TEXTURE[] =
{
	NULL
};

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
		g_Meshfield[nCnt].textype = 0;									//�e�N�X�`���^�C�v
		g_Meshfield[nCnt].nDiviX = 1;									//������x(0�ɂ�����nullptr)
		g_Meshfield[nCnt].nDiviY = 0;									//������y
		g_Meshfield[nCnt].nDiviZ = 1;									//������z(0�ɂ�����nullptr)
		g_Meshfield[nCnt].fWidth = 150;									//��
		g_Meshfield[nCnt].fHeight = 150;								//����
		g_Meshfield[nCnt].bUse = false;									//�g�p���Ă��Ȃ���Ԃɂ���

		//�e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			MESHFIELD_TEXTURE[g_Meshfield[nCnt].textype],
			&g_pTextureMeshfield[nCnt]);

		maxVtx += (g_Meshfield[nCnt].nDiviX + 1) * (g_Meshfield[nCnt].nDiviZ + 1);											//���_��
		polyNum += (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ - 1) * 2);		//�|���S����
		indexNum += (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ * 2) - 1);		//�C���f�b�N�X
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * maxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * indexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

		//���_���̐ݒ�
		for (int nCntZ = 0; nCntZ <= g_Meshfield[nCnt].nDiviZ; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= g_Meshfield[nCnt].nDiviX; nCntX++)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_Meshfield[nCnt].fWidth + (g_Meshfield[nCnt].fWidth * nCntX), 0.0f, g_Meshfield[nCnt].fHeight - (g_Meshfield[nCnt].fHeight * nCntZ));

				//�@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((1.0f / g_Meshfield[nCnt].nDiviX) * nCntX, (1.0f / g_Meshfield[nCnt].nDiviZ) * nCntZ);

				pVtx++;
			}
		}

		//���_�o�b�t�@���A�����b�N�@
		g_pVtxBuffMeshfield->Unlock();

		//�C���f�b�N�X�o�b�t�@�����b�N
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX;
		for (int nCntZ = 0; nCntZ < g_Meshfield[nCnt].nDiviZ; nCntZ++)
		{
			for (nCntX = 0; nCntX <= g_Meshfield[nCnt].nDiviX; nCntX++)
			{
				//�C���f�b�N�X�̐ݒ�
				pIdx[0] = (g_Meshfield[nCnt].nDiviX + 1) * (nCntZ + 1) + nCntX;
				pIdx[1] = nCntX + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1));

				pIdx += 2;
			}

			if (nCntZ < g_Meshfield[nCnt].nDiviZ - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1));
				pIdx[1] = (nCntX - 1) + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1)) + (g_Meshfield[nCnt].nDiviX + 2) * (nCntZ + 1);

				pIdx += 2;
			}
		}

		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffMeshField->Unlock();
	}
}

//===============================
// ���b�V�����̏I������
//===============================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
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
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, maxVtx, 0, polyNum);
		}
	}
}

//===============================
// ���b�V�����̐ݒ菈��
//===============================
void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX,int nDiviY, int nDiviZ, int fWidth, int fHeight)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		if (g_Meshfield[nCnt].bUse==false)
		{
			g_Meshfield[nCnt].pos = pos;						//�ʒu
			g_Meshfield[nCnt].rot = rot;						//����
			g_Meshfield[nCnt].textype = textype;				//�e�N�X�`���^�C�v
			g_Meshfield[nCnt].nDiviX = nDiviX;					//������x
			g_Meshfield[nCnt].nDiviY = nDiviY;					//������y
			g_Meshfield[nCnt].nDiviZ = nDiviZ;					//������z
			g_Meshfield[nCnt].fWidth = fWidth;					//��
			g_Meshfield[nCnt].fHeight = fHeight;				//����
			g_Meshfield[nCnt].bUse = true;						//�g�p���Ă����Ԃɂ���

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

			//���_�o�b�t�@���A�����b�N�@
			g_pVtxBuffMeshfield->Unlock();

			break;
		}
	}
}