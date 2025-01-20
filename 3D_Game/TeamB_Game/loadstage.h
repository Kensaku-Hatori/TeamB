//*************************************************
// 
// モデルビューワ読み込み処理[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

#define CAMERA "END_CAMERASET"
#define LIGHT "END_LIGHTSET"
#define SKY "END_SKYSET"
#define MOUNTAIN "END_MOUNTAINSET"
#define FIELD "END_FIELDSET"
#define WALL "END_WALLSET"
#define MODEL "END_MODELSET"
#define BILLBOARD "END_BILLBOARDSET"
#define MAX_PATHNUM 10
#define MAX_FILEPATH 32
#define MAX_PATHTYPE 2

typedef struct
{
	int nPolygoneType;
	int nModelType;
}NTYPE;

void LoadModelViewer();					// スクリプト以前を読み込む処理
void SkipComment(FILE* pFile);			// シャープ以降を飛ばす関数
void LoadStart(FILE* pFile);			// スクリプト以降の読み込み処理
void SkipEqual(FILE* pFile);			//  = を読み飛ばす処理
int LoadInt(FILE* pFile);				// 整数を読み込む処理
float LoadFloat(FILE* pFile);			// 小数点を読み込む処理
char *LoadPath(FILE* pFile);			// 文字列を読み込む処理

char* LoadCameraInfo(FILE* pFile);		// カメラ情報を読み込む処理
char* LoadLightInfo(FILE* pFile);		// ライト情報を読み込む処理
char* LoadSkyInfo(FILE* pFile);			// 空情報を読み込む処理
char* LoadMountInfo(FILE* pFile);		// 山情報を読み込む処理
char* LoadFieldInfo(FILE* pFile);		// 地面情報を読み込む処理
char* LoadWallInfo(FILE* pFile);		// 壁情報を読み込む処理
char* LoadModelInfo(FILE* pFile);		// モデル情報を読み込む処理
char* LoadBillBoardInfo(FILE* pFile);	// ビルボード情報を読み込む処理
#endif // !LOADSTAGE_H_