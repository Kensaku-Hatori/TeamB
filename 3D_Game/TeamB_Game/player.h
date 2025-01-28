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

#define PLAYER_JUMP (5)			//ジャンプ量
#define PLAYER_RADIUS (3)		//プレイヤーの半径

#define PLAYER_MP (500)		//MP
#define PLAYER_HP (1000)	//HP
#define PLAYER_SPEED (4)	//速度
#define PLAYER_AP (10)	//速度

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
	OBJECTINFO PlayerMotion;
	int nIdxShadow;		//影
	int nJump;			//ジャンプ量
	bool bJump;			//ジャンプできるかどうか
	bool bUse;
	PlayerStatus Status;//ステータス
	int nNumModel;
	int nNumMotion;							//モーションの総数
	MOTIONTYPE motionType;					//モーションの種類
	bool bLoopMotion;						//ループするかどうか
	int nNumKey;							//キーの総数
	int nKey;								//現在のキーNo
	int nCntMotion;							//モーションのカウンター

	bool bFinishMotion;				//現在のモーションが終了しているかどうか
	bool bBlendMotion;				//ブレンドモーションがあるかどうか
	MOTIONTYPE motionTypeBlend;		//ブレンドモーションの種類
	int nNumKeyBlend;				//ブレンドモーションのキーの総数
	int nKeyBlend;					//ブレンドモーションののキーNo
	int nCntMotionBlend;			//ブレンドモーションのカウンター
	int nFrameBlend;
	int nCntBlend;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(LoadInfo PartsInfo);
void PlayerMotion(MOTIONINFO *pMotionInfo);
#endif