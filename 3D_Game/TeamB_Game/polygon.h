//============================
//
// ポリゴン表示処理[polygon.h]
// Author:kaiti
//
//============================
#ifndef _POLYGON_H
#define _POLYGON_H_

#include "main.h"

#define POLYGON_X (800)
#define POLYGON_Y (800)

//プロトタイプ宣言
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void CollisionPolygon(void);

#endif
