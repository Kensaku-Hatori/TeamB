//*************************************************
// 
// モデルビューワ読み込み処理[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

void LoadModelViewer();				// スクリプト以前を読み込む処理
void SkipComment(FILE* pFile);		// シャープ以降を飛ばす関数
void LoadStart(FILE* pFile);		// スクリプト以降の読み込み処理
void SkipEqual(FILE* pFile);		//  = を読み飛ばす処理
void LoadTextureNum(FILE* pFile);	// テクスチャの種類を読み込む処理
void LoadTexturePath(FILE* pFile);	// テクスチャのパスを読み込む処理
void LoadModelNum(FILE* pFile);		// モデルの種類を読み込む処理
void LoadModelPath(FILE* pFile);	// モデルのパスを読み込む処理
int LoadInt(FILE* pFile);
char *LoadPath(FILE* pFile);
#endif // !LOADSTAGE_H_