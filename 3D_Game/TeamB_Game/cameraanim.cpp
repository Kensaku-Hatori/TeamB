#include "cameraanim.h"

void UpdateCameraWork(CameraAnim* Anim, D3DXVECTOR3* PosV, D3DXVECTOR3* PosR, D3DXVECTOR3* Rot)
{
	Anim->nFrameCount++;
	if(Anim->Anim[Anim->AnimType].nNumKey != NULL) Anim->nNexKey = (Anim->nKey + 1) % Anim->Anim[Anim->AnimType].nNumKey;
	if (Anim->nFrameCount >= Anim->Anim[Anim->AnimType].KeyInfo[Anim->nKey].nFrame)
	{
		Anim->nFrameCount = 0;
		if (Anim->Anim[Anim->AnimType].nNumKey != NULL) Anim->nKey = (Anim->nKey + 1) % Anim->Anim[Anim->AnimType].nNumKey;
	}
	CameraKey nKey = Anim->Anim[Anim->AnimType].KeyInfo[Anim->nKey];
	CameraKey nNexKey = Anim->Anim[Anim->AnimType].KeyInfo[Anim->nNexKey];

	CameraKey KeyDef;
	CameraKey KeyDest;

	// ·•ª
	KeyDef.PosR.x = nNexKey.PosR.x - nKey.PosR.x;
	KeyDef.PosR.y = nNexKey.PosR.y - nKey.PosR.y;
	KeyDef.PosR.z = nNexKey.PosR.z - nKey.PosR.z;

	KeyDef.PosV.x = nNexKey.PosV.x - nKey.PosV.x;
	KeyDef.PosV.y = nNexKey.PosV.y - nKey.PosV.y;
	KeyDef.PosV.z = nNexKey.PosV.z - nKey.PosV.z;

	KeyDef.Rot.x = nNexKey.Rot.x - nKey.Rot.x;
	KeyDef.Rot.y = nNexKey.Rot.y - nKey.Rot.y;
	KeyDef.Rot.z = nNexKey.Rot.z - nKey.Rot.z;

	// Šp“x‚Ì‹ß“¹
	if (KeyDef.Rot.x >= D3DX_PI)
	{
		KeyDef.Rot.x -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.x <= -D3DX_PI)
	{
		KeyDef.Rot.x += D3DX_PI * 2.0f;
	}

	// Šp“x‚Ì‹ß“¹
	if (KeyDef.Rot.y >= D3DX_PI)
	{
		KeyDef.Rot.y -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.y <= -D3DX_PI)
	{
		KeyDef.Rot.y += D3DX_PI * 2.0f;
	}

	// Šp“x‚Ì‹ß“¹
	if (KeyDef.Rot.z >= D3DX_PI)
	{
		KeyDef.Rot.z -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.z <= -D3DX_PI)
	{
		KeyDef.Rot.z += D3DX_PI * 2.0f;
	}

	// Šó–]‚Ì’l
	KeyDest.PosV.x = nKey.PosV.x + KeyDef.PosV.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosV.y = nKey.PosV.y + KeyDef.PosV.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosV.z = nKey.PosV.z + KeyDef.PosV.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// Šó–]‚Ì’l
	KeyDest.PosR.x = nKey.PosR.x + KeyDef.PosR.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosR.y = nKey.PosR.y + KeyDef.PosR.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosR.z = nKey.PosR.z + KeyDef.PosR.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// Šó–]‚Ì’l
	KeyDest.Rot.x = nKey.Rot.x + KeyDef.Rot.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.Rot.y = nKey.Rot.y + KeyDef.Rot.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.Rot.z = nKey.Rot.z + KeyDef.Rot.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// ‘«‚·
	PosV->x = KeyDest.PosV.x;
	PosV->y = KeyDest.PosV.y;
	PosV->z = KeyDest.PosV.z;

	// ‘«‚·
	PosR->x = KeyDest.PosR.x;
	PosR->y = KeyDest.PosR.y;
	PosR->z = KeyDest.PosR.z;

	// ‘«‚·
	Rot->x = KeyDest.Rot.x;
	Rot->y = KeyDest.Rot.y;
	Rot->z = KeyDest.Rot.z;
}
void SetCameraWork(CameraAnim *Anim, ANIMTYPE nType)
{
	Anim->AnimType = nType;
	Anim->nKey = 0;
	Anim->nNexKey = 0;
	Anim->nFrameCount = 0;
}