//================================
//
// �|���S���\������[wall.cpp]
// Author:kaiti
//
//================================
#include "wall.h"
#include "player.h"
#include "polygon.h"
//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9 g_apTextureWall[1] = {};
Wall g_wall[MAX_WALL];

//=======================
// �|���S���̏���������
//=======================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kabe.jpg", &g_apTextureWall[0]); //1

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffWall,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_wall[nCnt].pos.x - POLYGON_X, g_wall[nCnt].pos.y + WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_wall[nCnt].pos.x + POLYGON_X, g_wall[nCnt].pos.y + WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_wall[nCnt].pos.x - POLYGON_X, g_wall[nCnt].pos.y - WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_wall[nCnt].pos.x + POLYGON_X, g_wall[nCnt].pos.y - WALL_HEIGHT, g_wall[nCnt].pos.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(4.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(4.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}
//======================
// �|���S���̏I������
//======================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureWall[0] != NULL)
	{
		g_apTextureWall[0]->Release();
		g_apTextureWall[0] = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}
//=====================
// �|���S���̍X�V����
//=====================
void UpdateWall(void)
{

}
//=====================
// �|���S���̕`�揈��
//=====================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_wall[nCnt].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCnt].rot.y, g_wall[nCnt].rot.x, g_wall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_wall[nCnt].mtxWorld, &g_wall[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_wall[nCnt].pos.x, g_wall[nCnt].pos.y, g_wall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_wall[nCnt].mtxWorld, &g_wall[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureWall[0]);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//=============
// �ǂ̐ݒ�
//=============
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float a)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == false)
		{
			g_wall[nCnt].pos = pos;
			g_wall[nCnt].rot = rot;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, a);

			g_wall[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}
//====================
// �ǂƂ̓����蔻��
//====================
void CollisionWall(void)
{
	D3DXVECTOR3 aPos[2];

	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;

	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == true)
		{
			aPos[0].x = g_wall[nCnt].pos.x - cosf(g_wall[nCnt].rot.y) * WALL_WIDTH;
			aPos[0].z = g_wall[nCnt].pos.z + sinf(g_wall[nCnt].rot.y) * WALL_WIDTH;

			aPos[1].x = g_wall[nCnt].pos.x + cosf(g_wall[nCnt].rot.y) * WALL_WIDTH;
			aPos[1].z = g_wall[nCnt].pos.z - sinf(g_wall[nCnt].rot.y) * WALL_WIDTH;

			//�x�N�g��A
			vecA = aPos[1] - aPos[0];
			//�x�N�g��B
			vecB = pPlayer->pos - aPos[0];

			float fvec = (vecA.z * vecB.x) - (vecA.x * vecB.z);

			if (fvec < 0)
			{
				pPlayer->pos = pPlayer->posOld;
			}
		}
	}
}
//============
// �ǂ̎擾
//============
Wall* GetWall(void)
{
	return &g_wall[0];
}