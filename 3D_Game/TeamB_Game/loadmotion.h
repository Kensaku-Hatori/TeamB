#ifndef LOADMOTION_H_
#define LOADMOTION_H_

#include "main.h"
#include "loadstage.h"

#define CHARACTOR "END_CHARACTORSET"
#define MOTION "END_MOTIONSET"
#define PARTS "END_PARTSSET"
#define KEY "END_KEYSET"

void LoadMotionViewer(char *cMotionPath);				// スクリプト以前を読み込む処理
void LoadMotionStart(FILE* pFile);			// スクリプト以降の読み込み処理

char* LoadCharactorInfo(FILE* pFile);		// カメラ情報を読み込む処理
char* LoadPartsInfo(FILE* pFile);		// カメラ情報を読み込む処理
char* LoadMotionInfo(FILE* pFile);		// ライト情報を読み込む処理
char* LoadKeyInfo(FILE* pFile);		// ライト情報を読み込む処理
#endif // !LOADMOTION_H_