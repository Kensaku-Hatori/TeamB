#ifndef LOADMOTION_H_
#define LOADMOTION_H_

#include "main.h"
#include "loadstage.h"
#include "key.h"
#include "model.h"

#define MOTIONFILE_PLAYER  ("data\\MOTION\\motion00.txt")//プレイヤーのモーションファイル
#define MOTIONFILE_ENEMYONE  ("data\\MOTION\\Enemymotion00.txt")//プレイヤーのモーションファイル

#define CHARACTOR "END_CHARACTERSET"
#define MOTION "END_MOTIONSET"
#define PARTS "END_PARTSSET"
#define KEYPARTS "END_KEY"
#define KEY "END_KEYSET"

typedef enum
{
	LOADTYPE_PLAYER = 0,
	LOADTYPE_ENEMYONE,
	LOADTYPE_ENEMYTWO,
	LOADTYPE_ENEMYTHREE,
	LOADTYPE_ENEMYFOUR,
	LOADTYPE_MAX
}LoadType;

typedef struct
{
	MODELINFO PartsInfo[MAX_PARTS];
	MOTIONINFO MotionInfo[MOTIONTYPE_MAX];
	char cPartsPath[MAX_PARTS][62];
	int nNumParts;
	int PathCount,PartsCount,MotionCount,KeyCount,KeyPartsCount;
}LoadInfo;

void InitMotion();
void LoadMotionViewer(char *cMotionPath);	// スクリプト以前を読み込む処理
void LoadMotionStart(FILE* pFile);			// スクリプト以降の読み込み処理

char* LoadCharactorInfo(FILE* pFile,int *nCharactor, int* nParts, MODELINFO*Model);				// キャラクター情報を読み込む処理
char* LoadPartsInfo(FILE* pFile,int *nParts);									// パーツ情報を読み込む処理
char* LoadMotionInfo(FILE* pFile,int *nMotion, int* nKey, int* nKeyParts,MOTIONINFO *Motion);	// モーション情報を読み込む処理
char* LoadKeyInfo(FILE* pFile, int* nKey, int* nKeyParts, MOTIONINFO* Motion);					// キー情報を読み込む処理
char* LoadKeyPartsInfo(FILE* pFile,int *nKey,int *nKeyParts, MOTIONINFO* Motion);				// パーツごとのキー情報を読み込む処理
#endif // !LOADMOTION_H_