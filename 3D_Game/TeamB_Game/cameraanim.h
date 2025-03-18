#ifndef _CAMERAANIM_H_
#define _CAMERAANIM_H_

#include "main.h"

#define MAX_CAMERAKEY (15)

typedef enum
{
	ANIMTYPE_ONE = 0,
	ANIMTYPE_TWO,
	ANIMTYPE_MAX
}ANIMTYPE;

typedef struct
{
	D3DXVECTOR3 PosV;
	D3DXVECTOR3 PosR;
	D3DXVECTOR3 Rot;
	int nFrame;
}CameraKey;

typedef struct
{
	CameraKey KeyInfo[MAX_CAMERAKEY];
	int nNumKey;
	bool bLoop,bTracking;
}CameraAnimInfo;

typedef struct
{
	CameraAnimInfo Anim[ANIMTYPE_MAX];
	ANIMTYPE AnimType;
	int nKey, nNexKey, nFrameCount;
}CameraAnim;

void UpdateCameraWork(CameraAnim *Anim,D3DXVECTOR3 *PosV,D3DXVECTOR3 *PosR,D3DXVECTOR3 *Rot);
void SetCameraWork(CameraAnim *Anim,ANIMTYPE nType);
#endif // !_CAMERAANIM_H_