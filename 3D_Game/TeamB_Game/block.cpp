//==============================
//
// ���f���\������[Block.cpp]
// Author:kaiti
//
//==============================
#include "block.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

//�O���[�o���ϐ�
Block g_Block[MAX_BLOCK];
//=================
// ���f���̏�����
//=================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		g_Block[nCntBlockBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlockBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlockBlock].type = BLOCKTYPE_NORMAL;
		g_Block[nCntBlockBlock].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\block00.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_NORMAL].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\wall00.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_WALL].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\block02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].pBuffMat,
			NULL,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].dwNumMat,
			&g_Block[nCntBlockBlock].aModel[BLOCKTYPE_PILLAR].pMesh);


		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
		{
			//���_���擾
			nNumVtx = g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y�擾
			sizeFVF = D3DXGetFVFVertexSize(g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->GetFVF());
			//���_�o�b�t�@�̃��b�N
			g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntBlockvtx = 0; nCntBlockvtx < nNumVtx; nCntBlockvtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ă��f���̍ŏ��l�A�ő�l���擾
				//�ŏ��l
				if (vtx.x < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x = vtx.x;
				}
				if (vtx.y < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y = vtx.y;
				}
				if (vtx.z < g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z)
				{
					g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z = vtx.z;
				}
				//�ő�l
				if (vtx.x > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x = vtx.x;
				}
				if (vtx.y > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y = vtx.y;
				}
				if (vtx.z > g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z)
				{
					g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z = vtx.z;
				}

				g_Block[nCntBlockBlock].aModel[nCntBlock].size = D3DXVECTOR3(g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].x - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].x,
																		     g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].y - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].y,
																		     g_Block[nCntBlockBlock].vtxMaxBlock[nCntBlock].z - g_Block[nCntBlockBlock].vtxMinBlock[nCntBlock].z);

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			//���_�o�b�t�@�̃A�����b�N
			g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->UnlockVertexBuffer();

			
			D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
			pMat = (D3DXMATERIAL*)g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat->GetBufferPointer();
			for (int nCntBlockMat = 0; nCntBlockMat < (int)g_Block[nCntBlockBlock].aModel[nCntBlock].dwNumMat; nCntBlockMat++)
			{
				if (pMat[nCntBlockMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMat[nCntBlockMat].pTextureFilename, &g_Block[nCntBlockBlock].aModel[nCntBlock].pTexture[nCntBlockMat]); //1
				}
			}
		}
	}
}
//===================
// ���f���̏I������
//===================
void UninitBlock(void)
{
	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
		{
			//���b�V���̔j��
			if (g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh != NULL)
			{
				g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh->Release();
				g_Block[nCntBlockBlock].aModel[nCntBlock].pMesh = NULL;
			}
			//�}�e���A���̔j��
			if (g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat != NULL)
			{
				g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat->Release();
				g_Block[nCntBlockBlock].aModel[nCntBlock].pBuffMat = NULL;
			}
		}
	}
}
//===================
// ���f���̍X�V����
//===================
void UpdateBlock(void)
{

}
//===============
// ���f���̕`��
//===============
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;
	for (int nCntBlockBlock = 0; nCntBlockBlock < MAX_BLOCK; nCntBlockBlock++)
	{
		if (g_Block[nCntBlockBlock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Block[nCntBlockBlock].mtxWorld);
			
			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlockBlock].rot.y, g_Block[nCntBlockBlock].rot.x, g_Block[nCntBlockBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlockBlock].mtxWorld, &g_Block[nCntBlockBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlockBlock].pos.x, g_Block[nCntBlockBlock].pos.y, g_Block[nCntBlockBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlockBlock].mtxWorld, &g_Block[nCntBlockBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlockBlock].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pBuffMat->GetBufferPointer();

			for (int nCntBlockMat = 0; nCntBlockMat < (int)g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].dwNumMat; nCntBlockMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntBlockMat].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pTexture[nCntBlockMat]);
				//���f���̕`��
				g_Block[nCntBlockBlock].aModel[g_Block[nCntBlockBlock].type].pMesh->DrawSubset(nCntBlockMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}
//=================
// ���f���̐ݒ�
//=================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE type)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].rot = rot;
			g_Block[nCntBlock].type = type;
			g_Block[nCntBlock].bUse = true;
			break;
		}
	}
}
//============================
// �v���C���[�Ƃ̓����蔻��
//============================
bool CollisionBlock(void)
{
	bool bLanding = false; //���n���Ă��邩�ǂ���

	Player* pPlayer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pPlayer->posOld.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
			 && pPlayer->posOld.y + pPlayer->size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
			{
				if (pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					//��O
					if (pPlayer->posOld.z + pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
						&& pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pPlayer->pos.z = pPlayer->posOld.z;
					}
					//��
					else if (pPlayer->posOld.z - pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
							 && pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pPlayer->pos.z = pPlayer->posOld.z;
					}
				}

				if (pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				 && pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
				{
					//��
					if (pPlayer->posOld.x + pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
						&& pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pPlayer->pos.x = pPlayer->posOld.x;
					}
					//�E
					else if (pPlayer->posOld.x - pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
							&& pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pPlayer->pos.x = pPlayer->posOld.x;
					}
				}

				if (pPlayer->pos.x + pPlayer->size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pPlayer->pos.x - pPlayer->size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					if (pPlayer->pos.z - pPlayer->size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				     && pPlayer->pos.z + pPlayer->size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						//�u���b�N�ɏォ��߂荞�񂾎�
						if (pPlayer->posOld.y - pPlayer->size.y / 2 >= g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2
						 && pPlayer->pos.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
						{
							pPlayer->pos.y = pPlayer->posOld.y;
							pPlayer->move.y = 0.0f;
							bLanding = true;
						}
						//�u���b�N�ɉ�����߂荞�񂾎�
						if (pPlayer->posOld.y <= g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
					     && pPlayer->pos.y + pPlayer->size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2)
						{
							pPlayer->pos.y = pPlayer->posOld.y;
							pPlayer->move.y = 0.0f;
						}
					}
				}
			}
		}
	}
	return bLanding;
}
//===========================
// �G�ƃ��f���̓����蔻��
//===========================
void CollisionBlockEnemy(int nCntBlockEnemy)
{
	Enemy *pEnemy = GetEnemy();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pEnemy[nCntBlockEnemy].posOld.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
				&& pEnemy[nCntBlockEnemy].posOld.y + pEnemy[nCntBlockEnemy].size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
			{
				if (pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					//��O
					if (pEnemy[nCntBlockEnemy].posOld.z + pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
						&& pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pEnemy[nCntBlockEnemy].pos.z = pEnemy[nCntBlockEnemy].posOld.z;
					}
					//��
					else if (pEnemy[nCntBlockEnemy].posOld.z - pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
							 && pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						pEnemy[nCntBlockEnemy].pos.z = pEnemy[nCntBlockEnemy].posOld.z;
					}
				}

				if (pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
				 && pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
				{
					//��
					if (pEnemy[nCntBlockEnemy].posOld.x + pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
						&& pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pEnemy[nCntBlockEnemy].pos.x = pEnemy[nCntBlockEnemy].posOld.x;
					}
					//�E
					else if (pEnemy[nCntBlockEnemy].posOld.x - pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
							 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
					{
						pEnemy[nCntBlockEnemy].pos.x = pEnemy[nCntBlockEnemy].posOld.x;
					}
				}


				if (pEnemy[nCntBlockEnemy].pos.x + pEnemy[nCntBlockEnemy].size.x / 2 > g_Block[nCntBlock].pos.x - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2
				 && pEnemy[nCntBlockEnemy].pos.x - pEnemy[nCntBlockEnemy].size.x / 2 < g_Block[nCntBlock].pos.x + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.x / 2)
				{
					if (pEnemy[nCntBlockEnemy].pos.z - pEnemy[nCntBlockEnemy].size.z / 2 < g_Block[nCntBlock].pos.z + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2
					 && pEnemy[nCntBlockEnemy].pos.z + pEnemy[nCntBlockEnemy].size.z / 2 > g_Block[nCntBlock].pos.z - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.z / 2)
					{
						//�u���b�N�ɏォ��߂荞�񂾎�
						if (pEnemy[nCntBlockEnemy].posOld.y - pEnemy[nCntBlockEnemy].size.y / 2 >= g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2
						 && pEnemy[nCntBlockEnemy].pos.y < g_Block[nCntBlock].pos.y + g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y)
						{
							pEnemy[nCntBlockEnemy].pos.y = pEnemy[nCntBlockEnemy].posOld.y;
							pEnemy[nCntBlockEnemy].move.y = 0.0f;
						}
						//�u���b�N�ɉ�����߂荞�񂾎�
						if (pEnemy[nCntBlockEnemy].posOld.y <= g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y
						 && pEnemy[nCntBlockEnemy].pos.y + pEnemy[nCntBlockEnemy].size.y / 2 > g_Block[nCntBlock].pos.y - g_Block[nCntBlock].aModel[g_Block[nCntBlock].type].size.y / 2)
						{
							pEnemy[nCntBlockEnemy].pos.y = pEnemy[nCntBlockEnemy].posOld.y;
							pEnemy[nCntBlockEnemy].move.y = 0.0f;
						}
					}
				}
			}
		}
	}
}