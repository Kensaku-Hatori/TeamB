//================================
//
// プレイヤー表示処理[player.h]
// Author:kaiti
//
//================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

#define PLAYER_HITOSPEED (2)		//人型の速度
#define PLAYER_BALLSPEED (4)		//ボールの速度
#define PLAYER_SUPERBALLSPEED (7)	//スーパーボールの速度
#define PLAYER_HITOJUMP (10)		//人型のジャンプ量
#define PLAYER_BALLJUMP (5)			//ボールのジャンプ量
#define PLAYER_RADIUS (3)			//プレイヤーの半径
#define MAX_BALLTIME (200)			//ボールでいられる時間
#define PIN_CONDITION (10)			//スーパーボールになる条件
#define MOTIONFILE_PLAYER  ("data\\MOTION\\motionBallMan.txt")//プレイヤーのモーションファイル

//プレイヤーの状態
typedef enum
{
	PLAYERTYPE_HITO = 0,
	PLAYERTYPE_BALL,
	PLAYERTYPE_SUPERBALL,
	PLAYERTYPE_MAX
}PLAYERTYPE;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,

	MOTIONTYPE_BALLNEUTRAL,
	MOTIONTYPE_BALLMOVE,
	MOTIONTYPE_BALLACTION,
	MOTIONTYPE_BALLJUMP,
	MOTIONTYPE_BALLLANDING,

	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;

	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;
	KEY aKey[MAX_PARTS];
}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置
	D3DXVECTOR3 size;	//サイズ
	D3DXVECTOR3 move;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 rotDest;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	PLAYERTYPE type;
	int nIdxShadow;		//影
	int nJump;			//ジャンプ量
	int nBallTime;		//ボールでいられる時間
	int nCntKill;		//何体倒したか
	int nCntPin;		//スーパーボールになる条件用カウンタ―
	float fSpeed;		//速度
	bool bBall;			//ボールになれるかどうか
	bool bJump;			//ジャンプできるかどうか
	bool bUse;
	//モデル
	Model aModel[MAX_PARTS];
	int nNumModel;
	//モーション
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//モーション情報
	int nNumMotion;							//モーションの総数
	MOTIONTYPE motionType;					//モーションの種類
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キーの総数
	int nKey;								//現在のキーNo
	int nCntMotion;							//モーションのカウンター
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void SetPlayerMotion(void);
void LoadPlayer(void);

#endif