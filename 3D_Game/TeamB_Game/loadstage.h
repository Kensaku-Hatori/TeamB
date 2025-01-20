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

void LoadModelViewer();				// スクリプト以前を読み込む処理
void SkipComment(FILE* pFile);		// シャープ以降を飛ばす関数
void LoadStart(FILE* pFile);		// スクリプト以降の読み込み処理
void SkipEqual(FILE* pFile);		//  = を読み飛ばす処理
int LoadInt(FILE* pFile);			// 整数を読み込む処理
float LoadFloat(FILE* pFile);		// 小数点を読み込む処理
char *LoadPath(FILE* pFile);		// 文字列を読み込む処理
char* LoadDecision(FILE* pFile);		// 文字列を判断する処理
#endif // !LOADSTAGE_H_