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
#include "status.h"
#include "key.h"
#include "loadmotion.h"
#include "skill.h"

#define PLAYER_RADIUS (3)			// プレイヤーの半径

#define PLAYER_MP (500)				// MP
#define PLAYER_HP (float)(1000)		// HP
#define PLAYER_SPEED (float) (2.0f)	// 速度
#define PLAYER_AP (100)				// 攻撃力

// プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_KNOCKUP,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 posOld;				// 位置
	D3DXVECTOR3 size;				// サイズ
	D3DXVECTOR3 move;				// 位置
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 rotDest;			// 向き
	D3DXVECTOR3 NextPosition;		// 初期位置
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	D3DXMATRIX mtxWand;				// 杖先のマトリックス
	OBJECTINFO PlayerMotion;		// パーツ情報とモーション情報
	int nIdxShadow;					// 影のインデックス
	int nIndxCircle;				// サークルのインデックス
	int nCntState;
	bool bUse;						// 使用状況
	bool bLanding;					// 地面に着地しているかどうか
	bool bfirst;					// 最初かどうか
	bool bHit;
	PlayerStatus Status;			// ステータス
	SKILLTYPE Skilltype;
	PLAYERSTATE state;
	
	int nNumModel;					// パーツの総数
	int nNumMotion;					// モーションの総数
	MOTIONTYPE motionType;			// モーションの種類
	bool bLoopMotion;				// ループするかどうか
	int nNumKey;					// キーの総数
	int nKey;						// 現在のキーNo
	int nCntMotion;					// モーションのカウンター

	bool btest;
	bool bAbolition;				// 全滅フラグ(trueで全滅)

	float fSightRange;
	float fSightAngle;
	float fDistance;
	bool bLockOn;
	bool bWantLockOn;
	int nLockOnEnemy;

}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMove(void);
void SkillChange(void);
Player* GetPlayer(void);
void HitPlayer(float Atack, D3DXVECTOR3 Pos);
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(LoadInfo PartsInfo);
void PlayerMotion(MOTIONINFO *pMotionInfo);
void MatrixWand(void);

#endif