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
#include "player.h"

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
//=====================
// ���[�V�����u�����h
//=====================
//void MotionBlend(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	pPlayer->nCntMotion++;
//	pPlayer->nCntMotionBlend++;
//
//	if (pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].StartKey == pPlayer->nKey)
//	{// ���̃L�[���J�n����L�[��������
//		if (pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].StartFlame <= pPlayer->nCntMotion
//			&& pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].EndFlame >= pPlayer->nCntMotion)
//		{// �J�n�t���[���ȏ�ŏI���t���[���ȓ��Ȃ�
//			//collisionEnemy(pPlayer->WeponRadius);
//		}
//	}
//	if (pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aStartKey == pPlayer->nKey)
//	{// ���̃L�[�����ޖڂ̊J�n����L�[��������
//		if (pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aStartFlame <= pPlayer->nCntMotion
//			&& pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aEndFlame >= pPlayer->nCntMotion)
//		{// ���ޖڂ̊J�n�t���[���ȏ�œ��ޖڂ̏I���t���[���ȓ��Ȃ�
//			if (pPlayer->motionType == MOTIONTYPE_ACTION)
//			{
//
//			}
//		}
//	}
//
//	if (pPlayer->nCntMotion >= pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame)
//	{// ���[�V�����J�E���^�[���ڕW�̃t���[���ȏゾ������
//		pPlayer->nCntMotion = 0;
//		if (pPlayer->bFinish == false)
//		{
//			pPlayer->nKey++;
//			pPlayer->PlayerMotion.NextKey++;
//		}
//		if (pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].bLoop == true)
//		{
//			if (pPlayer->nKey >= pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].nNumKey - 1)
//			{// ���̃L�[���L�[�̍ő吔��������
//				if (pPlayer->nKey > pPlayer->PlayerMotion.NextKey)
//				{// ���̃L�[�����̃L�[�ȏゾ������
//					pPlayer->nKey = 0;
//				}
//				else
//				{
//					pPlayer->PlayerMotion.NextKey = 0;
//				}
//			}
//		}
//		else
//		{
//			if (pPlayer->nKey >= pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].nNumKey - 1)
//			{// ���̃L�[���L�[�̍ő吔��������
//				g_bMotion = false;
//				pPlayer->bFinish = true;
//				pPlayer->PlayerMotion.NextKey = pPlayer->nKey;
//				if (pPlayer->motionType != MOTIONTYPE_JUMP)
//				{
//					if (pPlayer->motionType == MOTIONTYPE_ACTION)
//					{
//						pPlayer->bBlendMotion = true;
//						pPlayer->motionTypeBlend = MOTIONTYPE_NEUTRAL;
//					}
//					//SetMotion(MOTIONTYPE_NUTORAL);w
//				}
//				else
//				{
//					pPlayer->PlayerMotion.NextKey = pPlayer->nKey;
//				}
//			}
//			else if (pPlayer->nKey > pPlayer->PlayerMotion.NextKey)
//			{// ���̃L�[�����̃L�[�ȏゾ������
//				pPlayer->nKey = 0;
//			}
//		}
//	}
//	if (pPlayer->nCntMotionBlend >= pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame)
//	{// ���[�V�����J�E���^�[���ڕW�̃t���[���ȏゾ������
//		pPlayer->nCntMotionBlend = 0;
//		pPlayer->nKeyBlend++;
//		pPlayer->nNextKeyBlend++;
//		if (pPlayer->nKeyBlend == pPlayer->nNumKeyBlend - 1)
//		{// ���̃L�[���L�[�̍ő吔��������
//			if (pPlayer->bLoopBlend == true)
//			{// ���[�v����^�C�v��������
//				pPlayer->nNextKeyBlend = 0;
//			}
//			else
//			{// ���[�v���Ȃ��^�C�v��������
//				g_bMotion = false;
//				pPlayer->bBlendMotion = false;
//				pPlayer->nNextKeyBlend = pPlayer->nKeyBlend;
//			}
//		}
//		else if (pPlayer->nKeyBlend > pPlayer->nNextKeyBlend)
//		{// ���̃L�[�����̃L�[�ȏゾ������
//			if (pPlayer->bLoopBlend == true)
//			{// ���[�v����^�C�v��������
//				pPlayer->nKeyBlend = 0;
//			}
//		}
//	}
//
//	KEYINFO nKey = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey];
//	KEYINFO nNexKey = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey];
//
//	float fRateMotion = (float)pPlayer->nCntMotion / (float)nKey.nFrame;
//
//	if (pPlayer->bBlendMotion == false)
//	{
//		for (int PartsCount = 0; PartsCount < pPlayer->nNumModel; PartsCount++)
//		{// ���f������
//			KEY KeyDef;
//			KEY KeyDest;
//
//			// ����
//			KeyDef.fPosX = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fPosX - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosX;
//			KeyDef.fPosY = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fPosY - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosY;
//			KeyDef.fPosZ = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fPosZ - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosZ;
//
//			KeyDef.fRotX = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fRotX - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotX;
//			KeyDef.fRotY = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fRotY - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotY;
//			KeyDef.fRotZ = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->PlayerMotion.NextKey].aKey[PartsCount].fRotZ - pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotZ;
//
//			// ��]�̒l
//			KeyDest.fPosX = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosX + KeyDef.fPosX * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//			KeyDest.fPosY = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosY + KeyDef.fPosY * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//			KeyDest.fPosZ = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosZ + KeyDef.fPosZ * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//
//			KeyDest.fRotX = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotX + KeyDef.fRotX * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//			KeyDest.fRotY = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotY + KeyDef.fRotY * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//			KeyDest.fRotZ = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotZ + KeyDef.fRotZ * ((float)pPlayer->nCntMotion / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
//
//			// ����
//			pPlayer->PlayerMotion.aModel[PartsCount].Partspos.x = pPlayer->PlayerMotion.aModel[PartsCount].OffSet.x + KeyDest.fPosX;
//			pPlayer->PlayerMotion.aModel[PartsCount].Partspos.y = pPlayer->PlayerMotion.aModel[PartsCount].OffSet.y + KeyDest.fPosY;
//			pPlayer->PlayerMotion.aModel[PartsCount].Partspos.z = pPlayer->PlayerMotion.aModel[PartsCount].OffSet.z + KeyDest.fPosZ;
//
//			pPlayer->PlayerMotion.aModel[PartsCount].Partsrot.x = pPlayer->PlayerMotion.aModel[PartsCount].OffSetRot.x + KeyDest.fRotX;
//			pPlayer->PlayerMotion.aModel[PartsCount].Partsrot.y = pPlayer->PlayerMotion.aModel[PartsCount].OffSetRot.y + KeyDest.fRotY;
//			pPlayer->PlayerMotion.aModel[PartsCount].Partsrot.z = pPlayer->PlayerMotion.aModel[PartsCount].OffSetRot.z + KeyDest.fRotZ;
//		}
//	}
//	else
//	{
//		KEYINFO nKeyBlend = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionTypeBlend].aKeyInfo[pPlayer->nKeyBlend];
//		KEYINFO nNextKeyBlend = pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionTypeBlend].aKeyInfo[pPlayer->nNextKeyBlend];
//
//		float fRateMotionBlend = (float)pPlayer->nCntMotionBlend / (float)pPlayer->PlayerMotion.aMotionInfo[pPlayer->motionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame;
//		float fRateBlend = (float)pPlayer->nCntBlend / (float)pPlayer->nFrameBlend;
//
//		for (int PartsCount = 0; PartsCount < pPlayer->nNumModel; PartsCount++)
//		{
//			D3DXVECTOR3 fDiffMotion;
//			fDiffMotion.x = nNexKey.aKey[PartsCount].fRotX - nKey.aKey[PartsCount].fRotX;
//			fDiffMotion.y = nNexKey.aKey[PartsCount].fRotY - nKey.aKey[PartsCount].fRotY;
//			fDiffMotion.z = nNexKey.aKey[PartsCount].fRotZ - nKey.aKey[PartsCount].fRotZ;
//			D3DXVECTOR3 fRotCurrent;
//			fRotCurrent.x = nKey.aKey[PartsCount].fRotX + (fDiffMotion.x * fRateMotion);
//			fRotCurrent.y = nKey.aKey[PartsCount].fRotY + (fDiffMotion.y * fRateMotion);
//			fRotCurrent.z = nKey.aKey[PartsCount].fRotZ + (fDiffMotion.z * fRateMotion);
//
//			D3DXVECTOR3 fDiffMotionBlend;
//			fDiffMotionBlend.x = nNextKeyBlend.aKey[PartsCount].fRotX - nKeyBlend.aKey[PartsCount].fRotX;
//			fDiffMotionBlend.y = nNextKeyBlend.aKey[PartsCount].fRotY - nKeyBlend.aKey[PartsCount].fRotY;
//			fDiffMotionBlend.z = nNextKeyBlend.aKey[PartsCount].fRotZ - nKeyBlend.aKey[PartsCount].fRotZ;
//			D3DXVECTOR3 fRotBlend;
//			fRotBlend.x = nKeyBlend.aKey[PartsCount].fRotX + (fDiffMotionBlend.x * fRateMotionBlend);
//			fRotBlend.y = nKeyBlend.aKey[PartsCount].fRotY + (fDiffMotionBlend.y * fRateMotionBlend);
//			fRotBlend.z = nKeyBlend.aKey[PartsCount].fRotZ + (fDiffMotionBlend.z * fRateMotionBlend);
//
//			D3DXVECTOR3 fDiffBlendRot = fRotBlend - fRotCurrent;
//			D3DXVECTOR3 fRot;
//
//			D3DXVECTOR3 fDiffMotionPos;
//			fDiffMotionPos.x = nNexKey.aKey[PartsCount].fPosX - nKey.aKey[PartsCount].fPosX;
//			fDiffMotionPos.y = nNexKey.aKey[PartsCount].fPosY - nKey.aKey[PartsCount].fPosY;
//			fDiffMotionPos.z = nNexKey.aKey[PartsCount].fPosZ - nKey.aKey[PartsCount].fPosZ;
//			D3DXVECTOR3 fRotCurrentPos;
//			fRotCurrentPos.x = nKey.aKey[PartsCount].fPosX + (fDiffMotion.x * fRateMotion);
//			fRotCurrentPos.y = nKey.aKey[PartsCount].fPosY + (fDiffMotion.y * fRateMotion);
//			fRotCurrentPos.z = nKey.aKey[PartsCount].fPosZ + (fDiffMotion.z * fRateMotion);
//
//			D3DXVECTOR3 fDiffMotionBlendPos;
//			fDiffMotionBlendPos.x = nNextKeyBlend.aKey[PartsCount].fPosX - nKeyBlend.aKey[PartsCount].fPosX;
//			fDiffMotionBlendPos.y = nNextKeyBlend.aKey[PartsCount].fPosY - nKeyBlend.aKey[PartsCount].fPosY;
//			fDiffMotionBlendPos.z = nNextKeyBlend.aKey[PartsCount].fPosZ - nKeyBlend.aKey[PartsCount].fPosZ;
//			D3DXVECTOR3 fRotBlendPos;
//			fRotBlendPos.x = nKeyBlend.aKey[PartsCount].fPosX + (fDiffMotionBlendPos.x * fRateMotionBlend);
//			fRotBlendPos.y = nKeyBlend.aKey[PartsCount].fPosY + (fDiffMotionBlendPos.y * fRateMotionBlend);
//			fRotBlendPos.z = nKeyBlend.aKey[PartsCount].fPosZ + (fDiffMotionBlendPos.z * fRateMotionBlend);
//
//			D3DXVECTOR3 fDiffBlendPos = fRotBlendPos - fRotCurrentPos;
//			D3DXVECTOR3 fPos;
//
//			fPos.x = fRotCurrentPos.x + (fDiffBlendPos.x * fRateBlend);
//			fPos.y = fRotCurrentPos.y + (fDiffBlendPos.y * fRateBlend);
//			fPos.z = fRotCurrentPos.z + (fDiffBlendPos.z * fRateBlend);
//
//			fRot.x = fRotCurrent.x + (fDiffBlendRot.x * fRateBlend);
//			fRot.y = fRotCurrent.y + (fDiffBlendRot.y * fRateBlend);
//			fRot.z = fRotCurrent.z + (fDiffBlendRot.z * fRateBlend);
//
//			pPlayer->PlayerMotion.aModel[PartsCount].Partspos = pPlayer->PlayerMotion.aModel[PartsCount].OffSet + fPos;
//			pPlayer->PlayerMotion.aModel[PartsCount].Partsrot = pPlayer->PlayerMotion.aModel[PartsCount].OffSetRot + fRot;
//			int i = 0;
//		}
//		pPlayer->nCntBlend++;
//		if (pPlayer->nCntBlend >= pPlayer->nFrameBlend)
//		{
//			pPlayer->nCntBlend = 0;
//			SetMotion(pPlayer->motionTypeBlend, &pPlayer->PlayerMotion);
//			pPlayer->bFinish = false;
//			pPlayer->bBlendMotion = false;
//		}
//	}
//}