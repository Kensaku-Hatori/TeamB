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

#define PLAYER_JUMP (5)			//ジャンプ量
#define PLAYER_RADIUS (3)		//プレイヤーの半径
#define MOTIONFILE_PLAYER  ("data\\MOTION\\motion00.txt")//プレイヤーのモーションファイル

#define PLAYER_MP (500)		//MP
#define PLAYER_HP (1000)	//HP
#define PLAYER_SPEED (4)	//速度

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

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
	int nIdxShadow;		//影
	int nJump;			//ジャンプ量
	bool bJump;			//ジャンプできるかどうか
	bool bUse;
	PlayerStatus Status;//ステータス
	//モデル
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//モーション
	MOTIONINFO aMotionInfo[MOTIONTYPE_MAX];//モーション情報
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
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(MODELINFO ModelInfo,int Indx);
void PlayerMotion(MOTIONINFO *pMotionInfo);
#endif