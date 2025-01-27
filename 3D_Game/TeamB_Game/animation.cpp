//************************************
// 
// Author: HATORI
// ���[�V�������Ǘ�����[animation.cpp]
// 
//************************************


//*************
// �C���N���[�h
//*************
#include "animation.h"
#include "effect.h"
#include "impact.h"

//***************
// �O���[�o���ϐ�
//***************
bool g_bMotion;

//*********************
// ���[�V�����̍X�V����
//*********************
void UpdateMotion(OBJECTINFO* Motion)
{
	Motion->nCntMotion++;

	if (Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame)
	{// ���[�V�����J�E���^�[���ڕW�̃t���[���ȏゾ������
		Motion->nCntMotion = 0;
		Motion->nKey++;
		Motion->NextKey++;
		if (Motion->nKey == Motion->aMotionInfo[Motion->motionType].nNumKey - 1)
		{// ���̃L�[���L�[�̍ő吔��������
			if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
			{// ���[�v����^�C�v��������
				Motion->NextKey = 0;
			}
			else
			{// ���[�v���Ȃ��^�C�v��������
				g_bMotion = false;
				if (Motion->motionType != MOTIONTYPE_JUMP)
				{
					SetMotion(MOTIONTYPE_NEUTRAL,Motion);
				}
				else
				{
					Motion->NextKey = Motion->nKey;
				}
			}
		}
		else if (Motion->nKey > Motion->NextKey)
		{// ���̃L�[�����̃L�[�ȏゾ������
			if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
			{// ���[�v����^�C�v��������
				Motion->nKey = 0;
			}
		}
	}

	for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
	{// ���f������
		KEY KeyDef;
		KEY KeyDest;

		// ����
		KeyDef.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX;
		KeyDef.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY;
		KeyDef.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ;

		KeyDef.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX;
		KeyDef.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY;
		KeyDef.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ;

		// ��]�̒l
		KeyDest.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX + KeyDef.fPosX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY + KeyDef.fPosY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ + KeyDef.fPosZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);

		KeyDest.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX + KeyDef.fRotX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY + KeyDef.fRotY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ + KeyDef.fRotZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);

		// ����
		Motion->aModel[PartsCount].pos.x = Motion->aModel[PartsCount].OffSet.x + KeyDest.fPosX;
		Motion->aModel[PartsCount].pos.y = Motion->aModel[PartsCount].OffSet.y + KeyDest.fPosY;
		Motion->aModel[PartsCount].pos.z = Motion->aModel[PartsCount].OffSet.z + KeyDest.fPosZ;

		Motion->aModel[PartsCount].rot.x = KeyDest.fRotX;
		Motion->aModel[PartsCount].rot.y = KeyDest.fRotY;
		Motion->aModel[PartsCount].rot.z = KeyDest.fRotZ;
	}
}
//*********************
// ���[�V�����̐ݒ菈��
//*********************
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO* Motion)
{
	Motion->nKey = 0;
	Motion->NextKey = 1;
	Motion->nCntMotion = 0;
	g_bMotion = true;
	Motion->motionType = MotionType;
}