//================================
//
// プレイヤー表示処理[Enemy.h]
// Author:kaiti
//
//================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "key.h"

#define ENEMY_SPEED (5)		//敵の速度
#define MAX_ENEMY (30)		//敵の最大数
#define ENEMY_RADIUS (3)	//敵の半径
#define ENEMYAND_RADIUS (3)	//敵同士の半径
#define MAX_ENEMYTIME (120)	//敵出現時間
#define ENEMY_LIFE (2)		//敵のライフ
#define MOTIONFILE_ENEMY  ("data\\MOTION\\motionPin.txt")//敵のモーションファイル

//モーションの種類
typedef enum
{
	ENEMYMOTIONTYPE_NEUTRAL = 0,
	ENEMYMOTIONTYPE_MOVE,
	ENEMYMOTIONTYPE_ACTION,
	ENEMYMOTIONTYPE_JUMP,
	ENEMYMOTIONTYPE_LANDING,
	ENEMYMOTIONTYPE_MAX
}ENEMYMOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;

	float fRotX;
	float fRotY;
	float fRotZ;
}ENEMYKEY;

//キー情報の構造体
typedef struct
{
	int nFrame;
	ENEMYKEY aKey[MAX_PARTS];
}ENEMYKEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;
	int nNumKey;
	ENEMYKEY_INFO aKeyInfo[MAX_KEY];
}ENEMYMOTION_INFO;

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
	int nIdxShadow;
	int nLife;
	int nDamage;
	float fDistance;
	bool bDamage;
	bool bJump;
	bool bCollision;
	bool bUse;
	//モデル
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//モーション
	ENEMYMOTION_INFO aMotionInfo[ENEMYMOTIONTYPE_MAX];  //モーション情報
	int nNumMotion;										//モーションの総数
	ENEMYMOTIONTYPE motionType;							//モーションの種類
	bool bLoopMotion;									//ループするかどうか
	int nNumKey;										//キーの総数
	int nKey;											//現在のキーNo
	int nCntMotion;										//モーションのカウンター
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy* GetEnemy(void);
void SetEnemyMotion(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos);
void CollisionEnemy(void);
void CollisionEnemyAndEnemy(int nCntEnemy);

#endif