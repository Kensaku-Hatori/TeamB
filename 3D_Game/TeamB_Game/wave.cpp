//============================================================
//
//�E�F�[�u����[wave.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wave.h"
#include"enemy.h"
#include "boss.h"
#include<stdio.h>

//�}�N����`
#define WAVE_0 "data\\TEXT\\wave\\wave00.txt"						// �E�F�[�u0
#define WAVE_1 "data\\TEXT\\wave\\wave01.txt"						// �E�F�[�u1
#define WAVE_2 "data\\TEXT\\wave\\wave02.txt"						// �E�F�[�u2
#define WAVE_3 "data\\TEXT\\wave\\wave03.txt"						// �E�F�[�u3


//�O���[�o���ϐ��錾
//LoadInfo g_Info[MAX_ENEMY];
MODE g_gamemode;
int g_nCntEnemy;
int g_nWave;												// �E�F�[�u�̃J�E���g
bool g_bFinish;												// �E�F�[�u�̏I������

//============================================================
// �E�F�[�u�̏���������
//============================================================
void InitWave(MODE mode)
{
	g_gamemode = mode;
	g_nCntEnemy = 0;
	g_nWave = 0;
	g_bFinish = false;
}

//============================================================
// �E�F�[�u�̓Ǎ�����
//============================================================
void LoadWave()
{
	FILE* pFile;											// �O���t�@�C���ւ̃|�C���^

	int type = 0;
	int Return = 0;
	D3DXVECTOR3 pos = {}, rot = {};

	//�G�̐����擾
	int *pNumEnemy = GetNumEnemy();
	g_nCntEnemy = (int)pNumEnemy;

	//�e�E�F�[�u�̃t�@�C�����J��
	switch (g_gamemode)
	{
	case MODE_STAGEONE://Wave1

		pFile = fopen(WAVE_0, "r");

		break;

	case MODE_STAGETWO://Wave2

		pFile = fopen(WAVE_1, "r");

		break;

	case MODE_STAGETHREE:

		pFile = fopen(WAVE_2, "r");

		break;

	case MODE_STAGEFOUR:

		pFile = fopen(WAVE_3, "r");

		break;

	default://��O

		pFile = NULL;

		g_bFinish = true;//�E�F�[�u�I��

		break;
	}

	if (pFile != NULL)
	{
		while (1)
		{
			char aString[MAX_WORD];

			//�t�@�C����ǂ݂���
			Return = fscanf(pFile, "%s", &aString[0]);
			if (strcmp(aString, "ENEMYSET") == 0)//ENEMYSET��Ǎ��񂾂Ȃ�
			{
				while (1)
				{
					Return = fscanf(pFile, "%s", &aString[0]);//TYPE��ǂݍ��񂾂�

					if (strcmp(aString, "TYPE") == 0)
					{
						//��ނ̎擾
						Return = fscanf(pFile, "%d", &type);
					}
					else if (strcmp(aString, "POS") == 0)//POS��Ǎ��񂾂Ȃ�
					{
						//�ʒu�̎擾
						Return = fscanf(pFile, "%f", &pos.x);
						Return = fscanf(pFile, "%f", &pos.y);
						Return = fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "ROT") == 0)//LIFE��Ǎ��񂾂Ȃ�
					{
						//�����̎擾
						Return = fscanf(pFile, "%f", &rot.x);
						Return = fscanf(pFile, "%f", &rot.y);
						Return = fscanf(pFile, "%f", &rot.z);
					}
					else if (strcmp(aString, "END_ENEMYSET") == 0)//END_ENEMYSET��Ǎ��񂾂Ȃ�
					{
						if (type == 3)
						{
							SetBoss(pos, rot);
						}
						else
						{
							//�G�̐ݒ�
							SetEnemy(pos, type, rot);
						}

						break;
					}
				}
			}
			if (Return == EOF)
			{
				break;
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//============================================================
// �E�F�[�u���̎擾
//============================================================
int GetWave()
{
	return g_nWave;
}

//============================================================
// �E�F�[�u�I���̎擾
//============================================================
bool GetFinish()
{
	return g_bFinish;
}