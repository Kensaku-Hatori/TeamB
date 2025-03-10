//==============================
//
//  �~�j�}�b�v����[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorialUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialUI = NULL;

Mission g_Mission;

D3DXVECTOR3 g_TutorialUIpos;

LPD3DXFONT g_pMissionFont;
const char *g_MissionInfo[MISSION_MAX][255];
D3DXVECTOR2 g_MissionPos[MISSION_MAX];

int g_CntState;
//=============
// ����������
//=============
void InitMission(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	// �f�o�b�N�\���p�t�H���g�̐���

	D3DXCreateFont(pDevice, 23, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pMissionFont);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial100.jpg", &g_pTextureTutorialUI);	//�g
	g_MissionInfo[MISSION_ZENMETU][0] = { "�G��S�ł�����" };
	g_MissionInfo[MISSION_IDOU][0] = { "���̃G���A�Ɉړ�����" };
	g_MissionInfo[MISSION_BOSS][0] = { "�{�X��|��" };

	g_MissionPos[MISSION_ZENMETU] = D3DXVECTOR2(1060.0f,250.0f);
	g_MissionPos[MISSION_IDOU] = D3DXVECTOR2(1030.0f,250.0f);
	g_MissionPos[MISSION_BOSS] = D3DXVECTOR2(1080.0f,250.0f);

	g_Mission.mission = MISSION_ZENMETU;

	g_CntState = 60;
	
	////���_�o�b�t�@�̐����E���_���̐ݒ�
	//VERTEX_2D* pVtx;

	////�`���[�g���A��
	//{
	//	//���_�o�b�t�@�̐���
	//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//		D3DUSAGE_WRITEONLY,
	//		FVF_VERTEX_2D,
	//		D3DPOOL_MANAGED,
	//		&g_pVtxBuffTutorialUI,
	//		NULL);
	//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//	g_pVtxBuffTutorialUI->Lock(0, 0, (void**)&pVtx, 0);

	//	//���_���W�̐ݒ�
	//	pVtx[0].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y - MISSION_Y, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_Missionpos.x - MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_Missionpos.x + MISSION_X, g_Missionpos.y + MISSION_Y, 0.0f);
	//	//rhw�̐ݒ�
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;
	//	//���_�J���[�̐ݒ�
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	//���_�o�b�t�@���A�����b�N
	//	g_pVtxBuffTutorialUI->Unlock();
	//}
}
//==========
// �I������
//==========
void UninitMission(void)
{
	if (g_pMissionFont != NULL)
	{
		g_pMissionFont->Release();
		g_pMissionFont = NULL;
	}
	////�e�N�X�`���̔j��
	//for (int nCnt = 0; nCnt < MISSION_MAX; nCnt++)
	//{
	//	if (g_pTextureMission[nCnt] != NULL)
	//	{
	//		g_pTextureMission[nCnt]->Release();
	//		g_pTextureMission[nCnt] = NULL;
	//	}
	//}

	////���_�o�b�t�@�̔j��
	//if (g_pVtxBuffMission != NULL)
	//{
	//	g_pVtxBuffMission->Release();
	//	g_pVtxBuffMission = NULL;
	//}
}
//==========
// �X�V����
//==========
void UpdateMission(void)
{
	DrawMission(g_MissionInfo[g_Mission.mission][0],g_pMissionFont,
		g_MissionPos[g_Mission.mission],
		D3DXCOLOR(0.0f,1.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		2);
}
//===========
// �`�揈��
//===========
void DrawMission(const char *MissionInfo, LPD3DXFONT Font, D3DXVECTOR2 Pos, D3DXCOLOR Grow, D3DXCOLOR FontCol, int GrowRadius)
{
	// ���ʂ̔��a
	const int glowRadius = GrowRadius;

	// ���̃e�L�X�g�̐F
	D3DXCOLOR textColor = FontCol; // ��

	// ���ʂ̐F
	D3DXCOLOR glowColor = Grow; // ��

	// �e�L�X�g�̕`��̈�
	RECT rect;
	SetRect(&rect, (int)Pos.x, (int)Pos.y, SCREEN_WIDTH, SCREEN_HEIGHT); // �e�L�X�g�̈ʒu

	// ���ʌ��ʂ̕`��
	for (int y = -glowRadius; y <= glowRadius; y++)
	{
		for (int x = -glowRadius; x <= glowRadius; x++)
		{
			if (x * x + y * y <= glowRadius * glowRadius)
			{
				RECT offsetRect = rect;
				OffsetRect(&offsetRect, x, y);
				Font->DrawText(NULL, MissionInfo, -1, &offsetRect, DT_LEFT | DT_TOP, glowColor);
			}
		}
	}
	// ���C���e�L�X�g�̕`��
	Font->DrawText(NULL, MissionInfo, -1, &rect, DT_LEFT | DT_TOP, textColor);
}
//
//
//
Mission* GetMission()
{
	return &g_Mission;
}