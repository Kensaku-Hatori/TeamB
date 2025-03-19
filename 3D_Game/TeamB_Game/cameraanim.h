//*********************************************************
// 
// �J�����A�j���[�V����[cameraanim.h]
// Author:Hatori
// 
//*********************************************************

#ifndef _CAMERAANIM_H_
#define _CAMERAANIM_H_

#include "main.h"
#include "bossnameeffect.h"

#define MAX_CAMERAKEY (15)
#define MAX_MOVIEEFFECTTYPE (1)

// �J�����A�j���[�V�����̗񋓌^
typedef enum
{
	ANIMTYPE_ONE = 0,
	ANIMTYPE_TWO,
	ANIMTYPE_THREE,
	ANIMTYPE_FOUR,
	ANIMTYPE_FIVE,
	ANIMTYPE_SIX,
	ANIMTYPE_MAX
}ANIMTYPE;

// �J�����A�j���[�V�����G�t�F�N�g�̗񋓌^
typedef enum
{
	MOVIEEFFECT_NONE = 0,
	MOVIEEFFECT_NAME,
	MOVIEEFFECT_MAX,
}MovieEffectType;

// �J�����A�j���[�V�����G�t�F�N�g�̍\����
typedef struct
{
	MovieEffectType EffectType;
	int StartFrame;
	int EndFrame;
	BOSSNAMEEFFECT SetNameEffect;
}MovieEffect;

// �J�����A�j���[�V�����̃L�[�̍\����
typedef struct
{
	D3DXVECTOR3 PosV;
	D3DXVECTOR3 PosR;
	D3DXVECTOR3 Rot;
	int nFrame;
	int nLife;
}CameraKey;

// �J�����A�j���[�V�����̍\����
typedef struct
{
	MovieEffect MovieEffect[MAX_MOVIEEFFECTTYPE];
	CameraKey KeyInfo[MAX_CAMERAKEY];
	int nNumKey;
	bool bLoop,bTracking;
}CameraAnimInfo;

// �J�����A�j���[�V�������܂Ƃ߂��񋓌^
typedef struct
{
	CameraAnimInfo Anim[ANIMTYPE_MAX];
	ANIMTYPE AnimType;
	int nKey, nNexKey, nFrameCount,AllFrame;
	bool bFinish;
}CameraAnim;

//*****************
// �v���g�^�C�v�錾
//*****************
void UpdateCameraWork(CameraAnim *Anim,D3DXVECTOR3 *PosV,D3DXVECTOR3 *PosR,D3DXVECTOR3 *Rot);
void SetCameraWork(CameraAnim *Anim,ANIMTYPE nType);
#endif // !_CAMERAANIM_H_