//==============================================
//
// ���b�V�����\������[meshfield.cpp]
// Author:kaiti
//
//==============================================

#include "meshfield.h"
#include <string.h>

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;						//���_���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield[MAX_TEX_FIELD] = {};				//�e�N�X�`���ւ̃|�C���^

MeshField g_Meshfield[MESH_NUM_MAX];									//�|���S��(��)�̍\����
static char fieldtexName[MAX_TEX_FIELD][32] = { NULL };					//�e�N�X�`���t�@�C�����ۑ��p
int flmaxVtx = 0, flpolyNum = 0;						//���_���A�|���S�����A�C���f�b�N�X���ۑ��p

//=================================
// ���b�V�����̏���������
//=================================
void InitMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���A�|���S�����A�C���f�b�N�X��������
	flmaxVtx = 0;
	flpolyNum = 0;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//�\���̂̏�����
		g_Meshfield[nCnt].pos = D3DXVECTOR3(-900.0f, 0.0f, 900.0f);		//�ʒu
		g_Meshfield[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
		g_Meshfield[nCnt].IdxBuffMeshField = { NULL };					//�C���f�b�N�X�o�b�t�@
		g_Meshfield[nCnt].textype = 0;									//�e�N�X�`���^�C�v
		g_Meshfield[nCnt].nDiviX = 0;									//������x(0�ɂ�����nullptr)
		g_Meshfield[nCnt].nDiviY = 0;									//������y
		g_Meshfield[nCnt].nDiviZ = 0;									//������z(0�ɂ�����nullptr)
		g_Meshfield[nCnt].nWidth = 0;									//��
		g_Meshfield[nCnt].nHeight = 0;									//����
		g_Meshfield[nCnt].nIndex = 0;									//�C���f�b�N�X
		g_Meshfield[nCnt].bUse = false;									//�g�p���Ă��Ȃ���Ԃɂ���
	}
}

//===============================
// ���b�V�����̏I������
//===============================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEX_FIELD; nCnt++)
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

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_Meshfield[nCnt].IdxBuffMeshField != NULL)
		{
			g_Meshfield[nCnt].IdxBuffMeshField->Release();
			g_Meshfield[nCnt].IdxBuffMeshField = NULL;
		}
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
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
			pDevice->SetIndices(g_Meshfield[nCnt].IdxBuffMeshField);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshfield[g_Meshfield[nCnt].textype]);

			//���b�V������`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, flmaxVtx, 0, flpolyNum);
		}
	}
}

//===============================
// ���b�V�����̐ݒ菈��
//===============================
void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX,int nDiviY, int nDiviZ, int nWidth, int nHeight)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;

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
			g_Meshfield[nCnt].nWidth = nWidth;					//��
			g_Meshfield[nCnt].nHeight = nHeight;				//����
			g_Meshfield[nCnt].bUse = true;						//�g�p���Ă����Ԃɂ���

			flmaxVtx += (g_Meshfield[nCnt].nDiviX + 1) * (g_Meshfield[nCnt].nDiviZ + 1);											//���_��
			flpolyNum += (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ - 1) * 2);			//�|���S����
			int flindexNum = (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ * 2) - 1);		//�C���f�b�N�X

				//�C���f�b�N�X�o�b�t�@�̐���
			pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Meshfield[nCnt].IdxBuffMeshField,
				NULL);


			break;
		}
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * flmaxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		if (g_Meshfield[nCnt].bUse == true)
		{
			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

			//���_���̐ݒ�
			for (int nCntZ = 0; nCntZ <= g_Meshfield[nCnt].nDiviZ; nCntZ++)
			{
				for (int nCntX = 0; nCntX <= g_Meshfield[nCnt].nDiviX; nCntX++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(-g_Meshfield[nCnt].nWidth + (g_Meshfield[nCnt].nWidth * nCntX), 0.0f, g_Meshfield[nCnt].nHeight - (g_Meshfield[nCnt].nHeight * nCntZ));

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
			g_Meshfield[nCnt].IdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
			g_Meshfield[nCnt].IdxBuffMeshField->Unlock();
		}
	}
}

//===============================
// ���b�V�����̃e�N�X�`���ݒ菈��
//===============================
void SetfieldTexture(char* pFileName, int TexIndx)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	strcpy(fieldtexName[TexIndx], pFileName);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		&fieldtexName[TexIndx][0],
		&g_pTextureMeshfield[TexIndx]);
}
