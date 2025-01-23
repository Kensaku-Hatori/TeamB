#ifndef OBJECT_H_
#define OBJECT_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 OldPos;
	D3DXVECTOR3 Rot;
	D3DXMATRIX mtxWorld;
}OBJECT;
#endif // !OBJECT_H_