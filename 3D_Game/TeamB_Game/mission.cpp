//==============================
//
//  �~�j�}�b�v����[Mission.cpp]
//  Author:kaiti
//
//==============================
#include "mission.h"
#include "player.h"
Mission g_Mission;

LPD3DXFONT g_pMissionFont;
const char *g_MissionInfo[MISSION_MAX][255];
D3DXVECTOR2 g_MissionPos[MISSION_MAX];
LPD3DXFONT g_pTutorialFont;
D3DXVECTOR2 g_TutorialPos;

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
		"Arial", &g_pMissionFont);

	D3DXCreateFont(pDevice, 20, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Arial", &g_pTutorialFont);

	g_MissionInfo[MISSION_ZENMETU][0] = { "�G��S�ł�����" };
	g_MissionInfo[MISSION_IDOU][0] = { "���̃G���A�Ɉړ�����" };
	g_MissionInfo[MISSION_BOSS][0] = { "�{�X��|��" };

	g_MissionPos[MISSION_ZENMETU] = D3DXVECTOR2(1060.0f,250.0f);
	g_MissionPos[MISSION_IDOU] = D3DXVECTOR2(1030.0f,250.0f);
	g_MissionPos[MISSION_BOSS] = D3DXVECTOR2(1080.0f,250.0f);

	g_Mission.mission = MISSION_ZENMETU;

	g_TutorialPos = D3DXVECTOR2(1040.0f,530.0f);

	g_CntState = 60;	
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
	if (g_pTutorialFont != NULL)
	{
		g_pTutorialFont->Release();
		g_pTutorialFont = NULL;
	}
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

	MODE pMode = GetMode();
	if (pMode == MODE_STAGEONE)
	{
		DrawMission("�`���[�g���A��:TAB/BACK", g_pTutorialFont,
			g_TutorialPos,
			D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			2);
	}
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