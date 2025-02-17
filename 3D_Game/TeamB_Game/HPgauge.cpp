//=========================================================
// 
// �G��HP�Q�[�W[HPgauge.cpp]
// Aothor:Rio Ohno
// 
//=========================================================

//�C���N���[�h
#include"HPgauge.h"

//�O���[�o���ϐ��錾
HPgauge g_HPgauge[MAX_HPGAUGE];
LPDIRECT3DTEXTURE9 pTextureHPgauge[HPGAUGETYPE_MAX] = {};

//=================
// ����������
//=================
void InitHPgauge()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGETEX[(HPGAUGETYPE)0],
		&pTextureHPgauge[(HPGAUGETYPE)0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGETEX[(HPGAUGETYPE)1],
		&pTextureHPgauge[(HPGAUGETYPE)1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGETEX[(HPGAUGETYPE)2],
		&pTextureHPgauge[(HPGAUGETYPE)2]);


	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//�\���̂̏�����
		g_HPgauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu
		g_HPgauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//����
		g_HPgauge[nCnt].fNowHP = 0.0f;											//���݂�HP
		g_HPgauge[nCnt].fMaxHP = 0.0f;											//�ő��HP
		g_HPgauge[nCnt].bUse = false;											//�g�p���Ă��Ȃ���Ԃɂ���

		g_HPgauge[nCnt].poly[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�Q�[�W�̐F
		g_HPgauge[nCnt].poly[1].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);		//�ԃQ�[�W�̐F
		g_HPgauge[nCnt].poly[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�g�̐F

		g_HPgauge[nCnt].poly[0].type = HPGAUGETYPE_NORMAL;
		g_HPgauge[nCnt].poly[1].type = HPGAUGETYPE_RED;
		g_HPgauge[nCnt].poly[2].type = HPGAUGETYPE_NONE;
	}
}

//=================
//�I������
//=================
void UninitHPgauge()
{
	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (g_HPgauge[nCnt].pVtxBuff != NULL)
		{
			g_HPgauge[nCnt].pVtxBuff->Release();
			g_HPgauge[nCnt].pVtxBuff = NULL;
		}
	}

	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < HPGAUGETYPE_MAX; nCnt++)
	{
		if (pTextureHPgauge[nCnt] != NULL)
		{
			pTextureHPgauge[nCnt]->Release();
			pTextureHPgauge[nCnt] = NULL;
		}
	}
}

//=================
//�X�V����
//=================
void UpdateHPgauge()
{

}

//=================
//�`�揈��
//=================
void DrawHPgauge()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		if (g_HPgauge[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_HPgauge[nCnt].mtxWorld);

			D3DXMATRIX mtxView;

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_HPgauge[nCnt].mtxWorld._11 = mtxView._11;
			g_HPgauge[nCnt].mtxWorld._12 = mtxView._21;
			g_HPgauge[nCnt].mtxWorld._13 = mtxView._31;
			g_HPgauge[nCnt].mtxWorld._21 = mtxView._12;
			g_HPgauge[nCnt].mtxWorld._22 = mtxView._22;
			g_HPgauge[nCnt].mtxWorld._23 = mtxView._32;
			g_HPgauge[nCnt].mtxWorld._31 = mtxView._13;
			g_HPgauge[nCnt].mtxWorld._32 = mtxView._23;
			g_HPgauge[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_HPgauge[nCnt].pos.x, g_HPgauge[nCnt].pos.y, g_HPgauge[nCnt].pos.z);
			D3DXMatrixMultiply(&g_HPgauge[nCnt].mtxWorld, &g_HPgauge[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_HPgauge[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_HPgauge[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCntPoly = 0; nCntPoly < MAX_POLY; nCntPoly++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pTextureHPgauge[g_HPgauge[nCnt].poly[nCntPoly].type]);

				//�|���S����`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPoly, 2);
			}
		}
	}

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=================
//�ݒ菈��
//=================
int SetHPgauge(D3DXVECTOR3 pos,D3DXVECTOR2 scale,float MaxHP)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;
	int nCnt = 0;

	//���S
	float center = scale.x * 0.5f;

	for (nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		if (g_HPgauge[nCnt].bUse == false)
		{
			//�e��ݒ�
			g_HPgauge[nCnt].pos = pos;						// �ʒu
			g_HPgauge[nCnt].fMaxHP = MaxHP;					// �ő�HP
			g_HPgauge[nCnt].fWidth = scale.x - center;		// ��

			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_POLY,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_HPgauge[nCnt].pVtxBuff,
				NULL);


			//���_�o�b�t�@�����b�N
			g_HPgauge[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_���̐ݒ�
			for (int nCntPoly = 0; nCntPoly < MAX_POLY; nCntPoly++)
			{
				//��ނ̐ݒ�
				g_HPgauge[nCnt].poly[nCntPoly].type = (HPGAUGETYPE)nCntPoly;

				//���_���̐ݒ�
				pVtx[0].pos.x = -center;
				pVtx[0].pos.y = scale.y;
				pVtx[0].pos.x = 0.0f;

				pVtx[1].pos.x = (scale.x - center);
				pVtx[1].pos.y = scale.y;
				pVtx[1].pos.x = 0.0f;

				pVtx[2].pos.x = -center;
				pVtx[2].pos.y = 0.0f;
				pVtx[2].pos.x = 0.0f;

				pVtx[3].pos.x = (scale.x - center);
				pVtx[3].pos.y = 0.0f;
				pVtx[3].pos.x = 0.0f;

				//�@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//�J���[�̐ݒ�
				pVtx[0].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[1].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[2].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[3].col = g_HPgauge[nCnt].poly[nCntPoly].col;

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;
			}

			//���_�o�b�t�@���A�����b�N
			g_HPgauge[nCnt].pVtxBuff->Unlock();

			g_HPgauge[nCnt].bUse = true;
			break;
		}
	}
	return nCnt;
}

//=================
//�ʒu�̐ݒ菈��
//=================
void SetPositionHPgauge(int Indx,D3DXVECTOR3 pos)
{
	g_HPgauge[Indx].pos = pos;
}

//=================
//�Q�[�W�̌�������
//=================
void HPgaugeDeff(int Indx, float NowHP)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�䗦���v�Z����
	float ratio = NowHP / g_HPgauge[Indx].fMaxHP;

	//���_�o�b�t�@�����b�N
	g_HPgauge[Indx].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//pVtx[1].pos.x
	//pVtx[3].pos.x

	//���_�o�b�t�@���A�����b�N
	g_HPgauge[Indx].pVtxBuff->Unlock();

	//�|�C���^��i�߂�

}