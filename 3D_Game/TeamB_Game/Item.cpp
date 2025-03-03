//============================================================
//
//�A�C�e��[Item.cpp]
//Author:Rio Ohno
//
//============================================================

#include"Item.h"
#include "player.h"
#include "itemui.h"
#include "score.h"

//�O���|�o���ϐ��錾
Item g_Item[MAX_ITEM];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemBill =  NULL ;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureItemBill[NUM_ITEMTYPE] = { NULL };			//�e�N�X�`���ւ̃|�C���^(����[��)
int g_nCntItem = 0;														//��ʏ�̃A�C�e����

//============================================================
// ���f���̏���������
//============================================================
void InitItem()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntItem = 0;														//��ʏ�̃A�C�e�����̏�����

	for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
	{
		//�e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureItemBill[nCnt]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemBill,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItemBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//�e�평����
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_Item[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
		g_Item[nCntItem].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���a
		g_Item[nCntItem].nIndexShadow = 0;								//�e�̃C���f�b�N�X
		g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;						//�A�C�e����������܂ł̎���
		g_Item[nCntItem].bUse = false;									//�g�p�����Ă��Ȃ����
		g_Item[nCntItem].bDesp = true;									//�Ƃ肠�������f�����Ă��Ƃɂ��Ƃ�

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Item[nCntItem].pos.x - ITEM_RADIUS;
		pVtx[0].pos.y = g_Item[nCntItem].pos.y + ITEM_RADIUS * 2.0f;
		pVtx[0].pos.z = g_Item[nCntItem].pos.z;

		pVtx[1].pos.x = g_Item[nCntItem].pos.x + ITEM_RADIUS;
		pVtx[1].pos.y = g_Item[nCntItem].pos.y + ITEM_RADIUS * 2.0f;
		pVtx[1].pos.z = g_Item[nCntItem].pos.z;

		pVtx[2].pos.x = g_Item[nCntItem].pos.x - ITEM_RADIUS;
		pVtx[2].pos.y = g_Item[nCntItem].pos.y;
		pVtx[2].pos.z = g_Item[nCntItem].pos.z;

		pVtx[3].pos.x = g_Item[nCntItem].pos.x + ITEM_RADIUS;
		pVtx[3].pos.y = g_Item[nCntItem].pos.y;
		pVtx[3].pos.z = g_Item[nCntItem].pos.z;

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItemBill->Unlock();
}

//============================================================
// ���f���̏I������
//============================================================
void UninitItem()
{
	//�o�b�t�@�̔j��
	if (g_pVtxBuffItemBill != NULL)
	{
		g_pVtxBuffItemBill->Release();
		g_pVtxBuffItemBill = NULL;
	}

	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
	{
		if (g_pTextureItemBill[nCnt] != NULL)
		{
			g_pTextureItemBill[nCnt]->Release();
			g_pTextureItemBill[nCnt] = NULL;
		}
	}
}

//============================================================
// ���f���̍X�V����
//============================================================
void UpdateItem()
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			//�t���[���f�N�������g
			g_Item[nCntItem].nCntTime--;

			//�A�C�e���̓_��
			if (g_Item[nCntItem].nCntTime <= 0)
			{
				g_Item[nCntItem].bUse = false;
				g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;				//������܂ł̃t���[��������
				g_nCntItem--;											//�h���b�v���̃A�C�e�����f�N�������g
			}
			else if (g_Item[nCntItem].nCntTime <= ITEM_TIME_DEL / 2.0f)
			{
				if ((g_Item[nCntItem].nCntTime % 2) == 0)
				{
					g_Item[nCntItem].bDesp = g_Item[nCntItem].bDesp ? false : true;
				}
			}
			else if (g_Item[nCntItem].nCntTime <= ITEM_TIME_DEL / 4.0f)
			{
				if ((g_Item[nCntItem].nCntTime % 8) == 0)
				{
					g_Item[nCntItem].bDesp = g_Item[nCntItem].bDesp ? false : true;
				}
			}

			//�����蔻��
			CollisionItem(nCntItem);
		}
	}
}

//============================================================
// �A�C�e��(�r���{�[�h)�̕`�揈��
//============================================================
void DrawItemBillboard()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true )
		{
			if (g_Item[nCntItem].bDesp == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Item[nCntItem].mtxWorld);

				D3DXMATRIX mtxView;//�r���[�}�g���b�N�X

				//�r���[�}�g���b�N�X�̎擾
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//�J�����̋t�s���ݒ�
				g_Item[nCntItem].mtxWorld._11 = mtxView._11;
				g_Item[nCntItem].mtxWorld._12 = mtxView._21;
				g_Item[nCntItem].mtxWorld._13 = mtxView._31;
				g_Item[nCntItem].mtxWorld._21 = mtxView._12;
				g_Item[nCntItem].mtxWorld._22 = mtxView._22;
				g_Item[nCntItem].mtxWorld._23 = mtxView._32;
				g_Item[nCntItem].mtxWorld._31 = mtxView._13;
				g_Item[nCntItem].mtxWorld._32 = mtxView._23;
				g_Item[nCntItem].mtxWorld._33 = mtxView._33;

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y, g_Item[nCntItem].pos.z);
				D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntItem].mtxWorld);

				//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffItemBill, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`�����W�̐ݒ�
				pDevice->SetTexture(0, g_pTextureItemBill[g_Item[nCntItem].type]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
			}
		}
	}

	//���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================
// �A�C�e���̐ݒ菈��
//============================================================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItemBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (type < NUM_ITEMTYPE && g_nCntItem < MAX_ITEM)//�ő�h���b�v���𒴂��ĂȂ��Ȃ�
		{
			if (g_Item[nCntItem].bUse == false)
			{
				g_Item[nCntItem].bUse = true;								//�g�p���Ă����Ԃɂ���
				g_Item[nCntItem].bDesp = true;								//�`�悷��
				g_Item[nCntItem].pos = pos;									//�ʒu�̐ݒ�
				g_Item[nCntItem].type = type;								//��ނ̐ݒ�
				g_nCntItem++;												//�A�C�e�����J�E���g
				g_Item[nCntItem].nCntTime = ITEM_TIME_DEL;					//������܂ł̃t���[��������

				break;
			}
		}
		else if (g_nCntItem >= MAX_ITEM)//�ő�h���b�v���𒴂��Ă�Ȃ�
		{
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItemBill->Unlock();

}

//============================================================
// �A�C�e���̎擾����
//============================================================
void CollisionItem(int nIndexItem)
{
	if (g_Item[nIndexItem].bUse == true)
	{
		//�v���C���[�̏��擾
		Player* pPlayer = GetPlayer();
		float Radius = 0;					//���a

		//�v���C���[�̔��a�擾
		D3DXVECTOR3 playerRadius = pPlayer->size / 2.0f;

		//����
		float Distance = (pPlayer->pos.x - g_Item[nIndexItem].pos.x) * (pPlayer->pos.x - g_Item[nIndexItem].pos.x) +
						 (pPlayer->pos.z - g_Item[nIndexItem].pos.z) * (pPlayer->pos.z - g_Item[nIndexItem].pos.z);

		//�Q�̔��a
		Radius = (playerRadius.z + ITEM_RADIUS) * (playerRadius.z + ITEM_RADIUS);

		if (Distance <= Radius)//�������Ă�Ȃ�
		{
			g_Item[nIndexItem].bUse = false;						//�g�p���Ă��Ȃ���Ԃɂ���
			g_Item[nIndexItem].nCntTime = 0;						//������܂ł̃t���[��������
			g_nCntItem--;											//�h���b�v���̃A�C�e�����f�N�������g
			ItemAbility(nIndexItem);
		}
	}
}

//=================
// �A�C�e���̌���
//=================
void ItemAbility(int nIndexItem)
{
	Player* pPlayer = GetPlayer();

	switch (g_Item[nIndexItem].type)
	{
	case ITEMTYPE_HP:
		AddItemUI(g_Item[nIndexItem].type);
		break;

	case ITEMTYPE_MP:
		AddItemUI(g_Item[nIndexItem].type);
		break;

	case ITEMTYPE_SPEED:
		pPlayer->Status.fPower += 30.0f;
		break;

	default:
		break;
	}

	AddScore(100);
}