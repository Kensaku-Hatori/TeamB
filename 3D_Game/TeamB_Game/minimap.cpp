//==============================
//
//  �~�j�}�b�v����[minimap.cpp]
//  Author:kaiti
//
//==============================
#include "minimap.h"
#include "player.h"
#include "camera.h"
//�O���[�o���ϐ�
//�g
LPDIRECT3DTEXTURE9 g_pTextureMiniMap = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMiniMap = NULL;
//�v���C���[�A�C�R��
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;
//�v���C���[�̎��E
LPDIRECT3DTEXTURE9 g_pTextureMapSight = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapSight = NULL;

//�G�A�C�R��
LPDIRECT3DTEXTURE9 pTextureMapEnemy = NULL;

D3DXVECTOR3 g_MiniMappos;
D3DXVECTOR3 g_MapPlayerpos;

MiniMapEnemy g_MiniMapEnemy[MAX_ENEMY];
//=============
// ����������
//=============
void InitMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\radar-6370407_1280.png", &g_pTextureMiniMap);	//�g
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ownmachine.jpg", &g_pTextureMapPlayer);		//HP 

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemyicon.png", &pTextureMapEnemy);		//HP 

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PlayerSight.png", &g_pTextureMapSight);		//HP 


	g_MiniMappos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	g_MapPlayerpos = D3DXVECTOR3(1800.0f, 100.0f, 0.0f);

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	//�g
	{		
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMiniMap,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMiniMap->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MiniMappos.x, g_MiniMappos.y + MINIMAP_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MiniMappos.x + MINIMAP_X, g_MiniMappos.y + MINIMAP_Y, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMiniMap->Unlock();
	}

	//�v���C���[�A�C�R��
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMapPlayer,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMapPlayer->Unlock();
	}
	//�v���C���[�̎��E
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMapSight,
			NULL);
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMapSight->Lock(0, 0, (void**)&pVtx, 0);

		float fAngle, fLength;

		fAngle = atan2f(MAPSIZE_SIGHT, MAPSIZE_SIGHT);
		fLength = sqrtf(MAPSIZE_SIGHT + MAPSIZE_SIGHT);

		//��ڂ̃|���S��
		pVtx[0].pos.x = g_MapPlayerpos.x + sinf((D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
		pVtx[0].pos.y = g_MapPlayerpos.y + cosf((D3DX_PI - fAngle)) * fLength;//pos.x - 150.0f;
		pVtx[0].pos.z = 0.0f;//0.0f;
		pVtx[1].pos.x = g_MapPlayerpos.x + sinf((D3DX_PI - fAngle)) * fLength;//pos.x + 150.0f;
		pVtx[1].pos.y = g_MapPlayerpos.y + cosf((D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
		pVtx[1].pos.z = 0.0f;//0.0f;
		pVtx[2].pos.x = g_MapPlayerpos.x + sinf((0.0f - fAngle)) * fLength;//pos.x - 150.0f;
		pVtx[2].pos.y = g_MapPlayerpos.y + cosf((0.0f - fAngle)) * fLength;//pos.y + 25.0f;
		pVtx[2].pos.z = 0.0f;//0.0f;
		pVtx[3].pos.x = g_MapPlayerpos.x + sinf((0.0f + fAngle)) * fLength;//pos.x + 150.0f;
		pVtx[3].pos.y = g_MapPlayerpos.y + cosf((0.0f + fAngle)) * fLength;//pos.y + 25.0f;
		pVtx[3].pos.z = 0.0f;
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMapSight->Unlock();
	}
	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		g_MiniMapEnemy[EnemyCount].bUse = false;
	}
}
//==========
// �I������
//==========
void UninitMiniMap(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMiniMap != NULL)
	{
		g_pVtxBuffMiniMap->Release();
		g_pVtxBuffMiniMap = NULL;
	}
	if (g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
	if (g_pVtxBuffMapSight != NULL)
	{
		g_pVtxBuffMapSight->Release();
		g_pVtxBuffMapSight = NULL;
	}
	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy != NULL)
		{
			g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy->Release();
			g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy = NULL;
		}
	}
	if (pTextureMapEnemy != NULL)
	{
		pTextureMapEnemy->Release();
		pTextureMapEnemy = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pTextureMiniMap != NULL)
	{
		g_pTextureMiniMap->Release();
		g_pTextureMiniMap = NULL;
	}
	if (g_pTextureMapPlayer != NULL)
	{
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;
	}
	if (g_pTextureMapSight != NULL)
	{
		g_pTextureMapSight->Release();
		g_pTextureMapSight = NULL;
	}
}
//==========
// �X�V����
//==========
void UpdateMiniMap(void)
{
	MODE mode = GetMode();

	if (mode == MODE_STAGEONE || mode == MODE_STAGETWO || mode == MODE_STAGETHREE || mode == MODE_STAGEFOUR)
	{
		//SetMapPlayer(mode);
		UpdateMiniMapSight();
	}
}
void UpdateMiniMapSight(void)
{
	Camera* pCamera = GetCamera();
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMapSight->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle, fLength, LocalCameraAngle;
	D3DXVECTOR2 LocalPos;
	LocalPos = D3DXVECTOR2(g_MapPlayerpos.x + MAPSIZE_PLAYER * 0.5f, g_MapPlayerpos.y + MAPSIZE_PLAYER * 0.5f);

	fAngle = atan2f(MAPSIZE_SIGHT, MAPSIZE_SIGHT);
	fLength = sqrtf(MAPSIZE_SIGHT + MAPSIZE_SIGHT);
	LocalCameraAngle = -pCamera->rot.y + D3DX_PI;

	//��ڂ̃|���S��
	pVtx[0].pos.x = LocalPos.x + sinf((LocalCameraAngle - (D3DX_PI * 0.5f) - fAngle)) * fLength;//pos.y - 25.0f;
	pVtx[0].pos.y = LocalPos.y + cosf((LocalCameraAngle - (D3DX_PI * 0.5f) - fAngle)) * fLength;//pos.x - 150.0f;
	pVtx[0].pos.z = 0.0f;//0.0f;
	pVtx[1].pos.x = LocalPos.x + sinf((LocalCameraAngle + (D3DX_PI * 0.5f) + fAngle)) * fLength;//pos.x + 150.0f;
	pVtx[1].pos.y = LocalPos.y + cosf((LocalCameraAngle + (D3DX_PI * 0.5f) + fAngle)) * fLength;//pos.y - 25.0f;
	pVtx[1].pos.z = 0.0f;//0.0f;
	pVtx[2].pos.x = LocalPos.x + sinf((LocalCameraAngle - (D3DX_PI * 0.5f))) * fLength * 0.75f;//pos.x - 150.0f;
	pVtx[2].pos.y = LocalPos.y + cosf((LocalCameraAngle - (D3DX_PI * 0.5f))) * fLength * 0.75f;//pos.y + 25.0f;
	pVtx[2].pos.z = 0.0f;//0.0f;
	pVtx[3].pos.x = LocalPos.x + sinf((LocalCameraAngle + (D3DX_PI * 0.5f))) * fLength * 0.75f;//pos.x + 150.0f;
	pVtx[3].pos.y = LocalPos.y + cosf((LocalCameraAngle + (D3DX_PI * 0.5f))) * fLength * 0.75f;//pos.y + 25.0f;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(155, 255, 155, 155);
	pVtx[1].col = D3DCOLOR_RGBA(155, 255, 155, 155);
	pVtx[2].col = D3DCOLOR_RGBA(155, 255, 155, 155);
	pVtx[3].col = D3DCOLOR_RGBA(155, 255, 155, 155);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMapSight->Unlock();
}
void UpdateMiniMapEnemy(int Indx,D3DXVECTOR3 PosEnemy)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	Player* pPlayer = GetPlayer();

	g_MiniMapEnemy[Indx].MiniMappos = PosEnemy;
	float fAngle,fDistance;
	D3DXVECTOR3 MathPos;
	MathPos.x = g_MiniMapEnemy[Indx].MiniMappos.x - pPlayer->pos.x;
	MathPos.z = g_MiniMapEnemy[Indx].MiniMappos.z - pPlayer->pos.z;
	fAngle = atan2f(MathPos.x, MathPos.z);

	fDistance = fabsf(sqrtf(MathPos.x * MathPos.x + MathPos.z * MathPos.z));
	if (fDistance >= 100.0f)
	{
		fDistance = 100.0f;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_MiniMapEnemy[Indx].pVtxBuffMapEnemy->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR2 Pos = { g_MapPlayerpos.x ,g_MapPlayerpos.y };
	Pos.x -= sinf(fAngle) * fDistance;
	Pos.y += cosf(fAngle) * fDistance;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x, Pos.y + MAPSIZE_PLAYER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y + MAPSIZE_PLAYER, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_MiniMapEnemy[Indx].pVtxBuffMapEnemy->Unlock();
}
//===========
// �`�揈��
//===========
void DrawMiniMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�g
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMiniMap, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMiniMap);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//�A�C�e����
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMapPlayer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//���E
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMapSight, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMapSight);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if(g_MiniMapEnemy[EnemyCount].bUse == true)
		{//�A�C�e����
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_MiniMapEnemy[EnemyCount].pVtxBuffMapEnemy, 0, sizeof(VERTEX_2D));
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTextureMapEnemy);
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}
//==========================
// �v���C���[�A�C�R���ݒ�
//==========================
void SetMapPlayer(int nStageNo)
{
	//�X�e�[�W���Ƃ̏ꏊ�ύX�i���j
	if (nStageNo == MODE_STAGEONE)
	{
		g_MapPlayerpos = D3DXVECTOR3(1110.0f, 100.0f, 0.0f);
	}
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPlayerpos.x, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPlayerpos.x + MAPSIZE_PLAYER, g_MapPlayerpos.y + MAPSIZE_PLAYER, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMapPlayer->Unlock();
}
int SetMapEnemy(D3DXVECTOR3 Pos)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();
	int MaxpEnemyCount = 0;
	for (MaxpEnemyCount = 0; MaxpEnemyCount < MAX_ENEMY; MaxpEnemyCount++)
	{
		if (g_MiniMapEnemy[MaxpEnemyCount].bUse == false)
		{
			g_MiniMapEnemy[MaxpEnemyCount].bUse = true;
			g_MiniMapEnemy[MaxpEnemyCount].MiniMappos = Pos;
			float fAngle;
			fAngle = atan2f(pPlayer->pos.x - Pos.x, pPlayer->pos.z - Pos.z);

			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy,
				NULL);
			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy->Lock(0, 0, (void**)&pVtx, 0);

			D3DXVECTOR2 Pos = { g_MapPlayerpos.x ,g_MapPlayerpos.y};
			Pos.x += sinf(fAngle) * 100.0f;
			Pos.y += cosf(fAngle) * 100.0f;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Pos.x, Pos.y + MAPSIZE_PLAYER, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Pos.x + MAPSIZE_PLAYER, Pos.y + MAPSIZE_PLAYER, 0.0f);
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			g_MiniMapEnemy[MaxpEnemyCount].pVtxBuffMapEnemy->Unlock();

			break;
		}
	}
	return MaxpEnemyCount;
}
void DeleteEnemyMiniMap(int Indx)
{
	g_MiniMapEnemy[Indx].bUse = false;
}