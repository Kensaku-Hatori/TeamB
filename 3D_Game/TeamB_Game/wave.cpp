//============================================================
//
//�E�F�[�u����[wave.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wave.h"
#include"enemy.h"
#include<stdio.h>

//�}�N����`
#define MAXX_CHAR (256)										//�ő啶����

//.txt
static const char* WAVE_TXT[MAX_WAVE] =
{
	"data\\TEXT\\wave\\wave00.txt",
	"data\\TEXT\\wave\\wave01.txt",
	"data\\TEXT\\wave\\wave02.txt",
	"data\\TEXT\\wave\\wave03.txt",
};

//�O���[�o���ϐ��錾
int g_nWave;												//�E�F�[�u�̃J�E���g
bool g_bFinish;												//�E�F�[�u�̏I������

//============================================================
// �E�F�[�u�̏���������
//============================================================
void InitWave()
{
	g_nWave = 0;
	g_bFinish = false;
}

//============================================================
// �E�F�[�u�̓Ǎ�����
//============================================================
void LoadWave()
{
	int type = 0/*, nLife = 0*/;
	D3DXVECTOR3 pos = {}, rot = {};

	//�O���t�@�C���ւ̃|�C���^
	FILE* pFile;

	//wave���S�ďI�����Ă���Ȃ�
	if (g_nWave >= MAX_WAVE)
	{
		pFile = NULL;

		g_bFinish = true;									//�E�F�[�u�I��

	}
	else
	{	//�e�E�F�[�u�̃t�@�C�����J��

		pFile = fopen(WAVE_TXT[g_nWave], "r");
	}

	if (pFile != NULL)
	{
		while (1)
		{
			char aString[MAXX_CHAR];

			//�t�@�C����ǂ݂���
			fscanf(pFile, "%s", &aString[0]);
			if (strcmp(aString, "ENEMYSET") == 0)//ENEMYSET��Ǎ��񂾂Ȃ�
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);//TYPE��ǂݍ��񂾂�

					if (strcmp(aString, "TYPE") == 0)
					{
						//��ނ̎擾
						fscanf(pFile, "%d", &type);
					}
					else if (strcmp(aString, "POS") == 0)//POS��Ǎ��񂾂Ȃ�
					{
						//�ʒu�̎擾
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "ROT") == 0)//LIFE��Ǎ��񂾂Ȃ�
					{
						//�����̎擾
						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);
					}
					else if (strcmp(aString, "END_ENEMYSET") == 0)//END_ENEMYSET��Ǎ��񂾂Ȃ�
					{
						//�G�̐ݒ�
						SetEnemy(pos,type, rot);

						break;
					}
				}
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		//�t�@�C�������
		fclose(pFile);

		//�E�F�[�u�̃J�E���g�A�b�v
		g_nWave++;
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