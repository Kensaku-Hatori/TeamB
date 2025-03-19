#ifndef _CAMERAANIM_H_
#define _CAMERAANIM_H_

#include "main.h"
#include "bossnameeffect.h"

#define MAX_CAMERAKEY (15)
#define MAX_MOVIEEFFECTTYPE (1)

typedef enum
{
	ANIMTYPE_ONE = 0,
	ANIMTYPE_TWO,
	ANIMTYPE_MAX
}ANIMTYPE;

typedef enum
{
	MOVIEEFFECT_NONE = 0,
	MOVIEEFFECT_NAME,
	MOVIEEFFECT_MAX,
}MovieEffectType;

typedef struct
{
	MovieEffectType EffectType;
	int StartFrame;
	int EndFrame;
	BOSSNAMEEFFECT SetNameEffect;
}MovieEffect;

typedef struct
{
	D3DXVECTOR3 PosV;
	D3DXVECTOR3 PosR;
	D3DXVECTOR3 Rot;
	int nFrame;
	int nLife;
}CameraKey;

typedef struct
{
	MovieEffect MovieEffect[MAX_MOVIEEFFECTTYPE];
	CameraKey KeyInfo[MAX_CAMERAKEY];
	int nNumKey;
	bool bLoop,bTracking;
}CameraAnimInfo;

typedef struct
{
	CameraAnimInfo Anim[ANIMTYPE_MAX];
	ANIMTYPE AnimType;
	int nKey, nNexKey, nFrameCount,AllFrame;
	bool bFinish;
}CameraAnim;

void UpdateCameraWork(CameraAnim *Anim,D3DXVECTOR3 *PosV,D3DXVECTOR3 *PosR,D3DXVECTOR3 *Rot);
void SetCameraWork(CameraAnim *Anim,ANIMTYPE nType);
#endif // !_CAMERAANIM_H_