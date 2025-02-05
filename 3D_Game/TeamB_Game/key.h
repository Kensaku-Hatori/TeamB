#ifndef KEY_H_
#define KEY_H_

#define MAX_KEY (10)
#define MAX_MOTION (5)

#include "main.h"
#include "model.h"

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_DOWN,
	MOTIONTYPE_DOWNNUTORAL,
	MOTIONTYPE_NANDE,
	MOTIONTYPE_MAX
}MOTIONTYPE;

typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

typedef struct
{
	int nFrame;
	KEY aKey[MAX_PARTS];
}KEYINFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEYINFO aKeyInfo[MAX_KEY];
}MOTIONINFO;

//プレイヤーの構造体
typedef struct
{
	//モデル
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//モーション
	MOTIONINFO aMotionInfo[MOTIONTYPE_MAX];	//モーション情報
	int nNumMotion;							//モーションの総数
	MOTIONTYPE motionType;					//モーションの種類
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キーの総数
	int nKey;								//現在のキーNo
	int NextKey;
	int nCntMotion;							//モーションのカウンター

	bool bFinish;							// 現在のモーションが終了しているかどうか
	bool bBlendMotion;						// ブレンドモーションがあるかどうか
	MOTIONTYPE motionTypeBlend;				// ブレンドモーションの種類
	int nNumKeyBlend;						// ブレンドモーションのキーの総数
	int nKeyBlend;							// ブレンドモーションののキーNo
	int nCntMotionBlend;					// ブレンドモーションのカウンター
	int nFrameBlend;						// ブレンドフレーム
	int nCntBlend;							// ブレンドフレームカウント
	int nNextKeyBlend;
	bool bLoopBlend;						//ループするかどうか

}OBJECTINFO;

#endif // !KEY_H_