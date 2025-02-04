//*************************************************
// 
// モデルビューワ読み込み処理[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

#define MAX_PATHNUM (15)
#define MAX_FILEPATH (15)
#define MAX_PATHTYPE (2)

// パスの種類
typedef struct
{
	int nPolygoneType;
	int nModelType;
}NTYPE;

void LoadModelViewer(MODE Mode);					// スクリプト以前を読み込む処理
void SkipComment(FILE* pFile);						// シャープ以降を飛ばす関数
void LoadStart(FILE* pFile);						// スクリプト以降の読み込み処理
void SkipEqual(FILE* pFile);						//  = を読み飛ばす処理
int LoadInt(FILE* pFile);							// 整数を読み込む処理
float LoadFloat(FILE* pFile);						// 小数点を読み込む処理
char *LoadPath(FILE* pFile,char *cData2);			// 文字列を読み込む処理

void LoadCameraInfo(FILE* pFile);					// カメラ情報を読み込む処理
void LoadLightInfo(FILE* pFile);					// ライト情報を読み込む処理
void LoadSkyInfo(FILE* pFile);						// 空情報を読み込む処理
void LoadMountInfo(FILE* pFile);					// 山情報を読み込む処理
void LoadFieldInfo(FILE* pFile);					// 地面情報を読み込む処理
void LoadWallInfo(FILE* pFile);						// 壁情報を読み込む処理
void LoadModelInfo(FILE* pFile);					// モデル情報を読み込む処理
void LoadBillBoardInfo(FILE* pFile);				// ビルボード情報を読み込む処理
void LoadPlayerInfo(FILE* pFile);					// プレイヤー情報を読み込む処理
#endif // !LOADSTAGE_H_