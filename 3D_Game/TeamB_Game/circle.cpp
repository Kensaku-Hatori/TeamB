//=======================================================
// 
// �T�[�N��[circle.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "circle.h"

//�O���[�o���ϐ��錾
Circle g_Circle[MAX_CIRCLE];

//=========================
//�T�[�N���̏���������
//=========================
void InitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		//�e�평����
		g_Circle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
		g_Circle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
		g_Circle[nCnt].AddCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F�̕ω���
		g_Circle[nCnt].pVtxBuff = { NULL };								// ���_�o�b�t�@
		g_Circle[nCnt].IndxBuff = { NULL };								// �C���f�b�N�X�o�b�t�@
		g_Circle[nCnt].nDiviX = 0;										// X�̕�����
		g_Circle[nCnt].nDiviY = 0;										// Y�̕�����
		g_Circle[nCnt].nMaxVtx = 0;										// ���_��
		g_Circle[nCnt].nPolyNum = 0;									// �|���S����
		g_Circle[nCnt].nCntFrame = 0;									// �t���[���J�E���^�[
		g_Circle[nCnt].fHeight = 0.0f;									// ����
		g_Circle[nCnt].fRadius = 0.0f;									// ���a
		g_Circle[nCnt].bGradation = false;								// �O���f�[�V�������邩�ǂ���
		g_Circle[nCnt].bAnime = false;									// ���������邩�ǂ���
		g_Circle[nCnt].bUse = false;									// �g�p���Ă��邩�ǂ���
	}
}

//=========================
//�T�[�N���̏I������
//=========================
void UninitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		//�o�b�t�@�̔j��
		if (g_Circle[nCnt].pVtxBuff != NULL)
		{
			g_Circle[nCnt].pVtxBuff->Release();
			g_Circle[nCnt].pVtxBuff = NULL;
		}

		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_Circle[nCnt].IndxBuff != NULL)
		{
			g_Circle[nCnt].IndxBuff->Release();
			g_Circle[nCnt].IndxBuff = NULL;
		}

		//�e�N�X�`���̔j��
		if (g_Circle[nCnt].tex != NULL)
		{
			g_Circle[nCnt].tex->Release();
			g_Circle[nCnt].tex = NULL;
		}

	}
}

//=========================
//�T�[�N���̍X�V����
//=========================
void UpdateCircle()
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		int  i = 0;
		if (g_Circle[nCnt].bUse == true)
		{
			if (g_Circle[nCnt].bAnime == true && g_Circle[nCnt].frame >= 0)
			{
				int indx = 0;										//���_�C���f�b�N�X

				//�t���[���J�E���g
				g_Circle[nCnt].nCntFrame++;

				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_Circle[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntY = 0; nCntY <= g_Circle[nCnt].nDiviY; nCntY++)
				{
					for (int nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
					{
						//���_�J���[�̐ݒ�
						pVtx[indx].col = D3DXCOLOR((FLOAT)g_Circle[nCnt].col.r + (g_Circle[nCnt].AddCol.r * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.g + (g_Circle[nCnt].AddCol.g * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.b + (g_Circle[nCnt].AddCol.b * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.a + (g_Circle[nCnt].AddCol.a * (g_Circle[nCnt].nCntFrame)));

						//�C���f�b�N�X��i�߂�
						indx++;
					}
				}

				//�t���[����������
				if (g_Circle[nCnt].nCntFrame >= g_Circle[nCnt].frame)
				{
					//g_Circle[nCnt].nCntFrame = 0;
					g_Circle[nCnt].bUse = false;
				}

				//���_�o�b�t�@���A�����b�N�@
				g_Circle[nCnt].pVtxBuff->Unlock();
			}

		}
	}
}

//=========================
//�T�[�N���̕`�揈��
//=========================
void DrawCircle()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//���C�g��؂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O��؂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ALPHA�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == true)
		{
			if (g_Circle[nCnt].type == 1)
			{
				// ���Z������ݒ肷��
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Circle[nCnt].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Circle[nCnt].rot.y, g_Circle[nCnt].rot.x, g_Circle[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Circle[nCnt].pos.x, g_Circle[nCnt].pos.y, g_Circle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Circle[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X����f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_Circle[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_Circle[nCnt].IndxBuff);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Circle[nCnt].tex);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Circle[nCnt].nMaxVtx, 0, g_Circle[nCnt].nPolyNum);

		}
	}

	//���Z������؂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�J�����O������
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
//�T�[�N���̐ݒ菈��
//=========================
int SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int DiviX, int DiviY, float fHeight, float fRadius, bool bGradation, bool bAnime, int type)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�C���f�b�N�X�ւ̃|�C���^
	WORD* pIdx = NULL;
	int nCnt = 0;

	for (nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == false)
		{
			//�e�ϐ��̐ݒ�
			g_Circle[nCnt].pos = pos;
			g_Circle[nCnt].rot = rot;
			g_Circle[nCnt].col = col;
			g_Circle[nCnt].nDiviX = DiviX;
			g_Circle[nCnt].nDiviY = DiviY + 1;
			g_Circle[nCnt].nCntFrame = 0;
			g_Circle[nCnt].fHeight = fHeight;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bGradation = bGradation;	//�O���f�[�V�����̗L��
			g_Circle[nCnt].bAnime = bAnime;			//�����̗L��
			if (type == 1)
			{
				//�e�N�X�`���̓Ǎ�
				D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\haikei2.jpg", &g_Circle[nCnt].tex); //1
			}

			//�A�j���[�V������true�Ȃ�
			if (g_Circle[nCnt].bAnime == true)
			{
				D3DXCOLOR Col = (col);	//�v�Z���ʕۑ��p

				//D3DCOLOR_RGBA�΍�
				if (col.r > 1.0f)
				{
					Col.r = (FLOAT)col.r / 255.0f;
				}
				if (col.g > 1.0f)
				{		
					Col.g = (FLOAT)col.g / 255.0f;
				}
				if (col.b > 1.0f)
				{
					Col.b = (FLOAT)col.b / 255.0f;
				}
				if (col.a > 1.0f)
				{
					Col.a = (FLOAT)col.a / 255.0f;
				}

				//�F�̕ω��ʂ�ݒ�
				g_Circle[nCnt].AddCol.r = (1.0f - Col.r);
				g_Circle[nCnt].AddCol.g = (1.0f - Col.g);
				g_Circle[nCnt].AddCol.b = (1.0f - Col.b);
				g_Circle[nCnt].AddCol.a = (1.0f - Col.a);
			}

			g_Circle[nCnt].nMaxVtx = (g_Circle[nCnt].nDiviX + 1) * (g_Circle[nCnt].nDiviY + 1);											//���_��
			g_Circle[nCnt].nPolyNum = (2 * g_Circle[nCnt].nDiviX * g_Circle[nCnt].nDiviY + (g_Circle[nCnt].nDiviY - 1) * 4);			//�|���S����
			int flindexNum = (2 * (g_Circle[nCnt].nDiviY * (2 + g_Circle[nCnt].nDiviX) - 1));											//�C���f�b�N�X

			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Circle[nCnt].nMaxVtx,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].pVtxBuff,
				NULL);

			//�C���f�b�N�X�J�E���^�[
			int indx = 0;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_Circle[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			for (int nCntY = 0; nCntY <= g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (int nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//�p�x�i�[
					float fAngle = ((D3DX_PI * 2 / g_Circle[nCnt].nDiviX) * nCntX);

					//�����̊i�[
					float fHeight = (g_Circle[nCnt].fHeight / g_Circle[nCnt].nDiviY) * (g_Circle[nCnt].nDiviY - nCntY);

					//���_�̐ݒ�
					pVtx[indx].pos = D3DXVECTOR3(g_Circle[nCnt].fRadius * sinf(fAngle), fHeight, g_Circle[nCnt].fRadius * cosf(fAngle));

					//���S�ւ̃x�N�g��
					D3DXVECTOR3 vec = g_Circle[nCnt].pos - pVtx[indx].pos;

					//�x�N�g���̐��K��,�e���_�̖@���̐ݒ�
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//���_�J���[�̐ݒ�
					pVtx[indx].col = g_Circle[nCnt].col;

					//�O���f�[�V�����L�Ȃ�
					if (g_Circle[nCnt].bGradation == true)
					{
						pVtx[indx].col = D3DXCOLOR(g_Circle[nCnt].col.r, 
							g_Circle[nCnt].col.g, 
							g_Circle[nCnt].col.b, 
							(g_Circle[nCnt].col.a / (g_Circle[nCnt].nDiviY)) * (nCntY));
					}

					//�e�N�X�`�����W�̐ݒ�
					pVtx[indx].tex = D3DXVECTOR2(1.0f * nCntX,1.0f * nCntY);
					indx++;
				}
			}

			//���_�o�b�t�@���A�����b�N�@
			g_Circle[nCnt].pVtxBuff->Unlock();

			//�C���f�b�N�X�o�b�t�@�̐���
			pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].IndxBuff,
				NULL);

			//�C���f�b�N�X�o�b�t�@�����b�N
			g_Circle[nCnt].IndxBuff->Lock(0, 0, (void**)&pIdx, 0);

			int nCntX = 0;
			for (int nCntY = 0; nCntY < g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//�C���f�b�N�X�̐ݒ�
					pIdx[0] = (g_Circle[nCnt].nDiviX + 1) * (nCntY + 1) + nCntX;
					pIdx[1] = nCntX + (nCntY * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}

				//���ރ|���S����
				if (nCntY < g_Circle[nCnt].nDiviY - 1)
				{
					//�C���f�b�N�X�̐ݒ�
					pIdx[0] = (nCntX - 1) + (nCntY * (g_Circle[nCnt].nDiviX + 1));
					pIdx[1] = nCntX + ((nCntY + 1) * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}
			}

			//�C���f�b�N�X�o�b�t�@���A�����b�N
			g_Circle[nCnt].IndxBuff->Unlock();

			g_Circle[nCnt].bUse = true;

			break;
		}
	}
		return nCnt;
}

//=========================
//�T�[�N���̈ʒu�̍X�V����
//=========================
void  SetPositionCircle(int indx, D3DXVECTOR3  pos, D3DXVECTOR3 rot)
{
	g_Circle[indx].pos = pos;
	g_Circle[indx].rot = rot;
}

//=========================
//�T�[�N���A�j���[�V�����̎�ސݒ菈��
//=========================
void SetAnime(int indx, ANIMETYPE type, int frame)
{
	if (g_Circle[indx].bUse == true && g_Circle[indx].bAnime == true)
	{
		g_Circle[indx].type = type;
		g_Circle[indx].frame = frame;
		g_Circle[indx].Anime.bHalf = false;
		g_Circle[indx].nCntFrame = 0;
	
		float a = 1.0f / g_Circle[indx].frame;

		//�F�̕ω��ʂ̐ݒ�
		g_Circle[indx].AddCol.r = g_Circle[indx].AddCol.r * a;
		g_Circle[indx].AddCol.g = g_Circle[indx].AddCol.g * a;
		g_Circle[indx].AddCol.b = g_Circle[indx].AddCol.b * a;
		g_Circle[indx].AddCol.a = g_Circle[indx].AddCol.a * a;

	//	switch (g_Circle[indx].type)
	//	{
	//	case ANIMETYPE_0:

	//		g_Circle[indx].frame = g_Circle[indx].frame * (4 / 3);

	//		break;

	//	default:

	//		break;
	//	}
	}
}

//=========================
//�T�[�N���̃A���t�@�l�������炷����
//=========================
void DefAlpha(int indx,int frame)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

}

//=========================
//�T�[�N������������
//=========================
void DeleteCircle(int indx)
{
	g_Circle[indx].bUse = false;
}