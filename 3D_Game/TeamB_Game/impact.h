#ifndef IMPACT_H_
#define IMPACT_H_

#include "main.h"
#include "Object.h"

#define MAX_IMPACT (32)

typedef enum
{
	IMPACTTYPE_NORMAL = 0,
	IMPACTTYPE_ENEMY,
	IMPACTTYPE_MAX
}IMPACTTYPE;

typedef struct
{
	OBJECT Object;
	D3DXCOLOR col;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffImpact;
	LPDIRECT3DINDEXBUFFER9 pIdxBuffImpact;
	LPDIRECT3DTEXTURE9 pTextureImpact;
	IMPACTTYPE nType;
	int nLife;
	float inringsize,outringsize;
	int Horizon, Vertical, Vertex, Polygone,IndxVertex;
	float AlphaDef;
	float Speed;
	bool bUse;
}RINGIMPACT;

static const char* IMPACTTEX[IMPACTTYPE_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\effect000.jpg",
};

void InitImpact(void);
void UninitImpact(void);
void UpdateImpact(void);
void DrawImpact(void);
void SetImpact(IMPACTTYPE nType,D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float inringsize,float outringsize,int Horizon,int Vertical,float Speed);
void collisionImpact(int Indx);
void collisionImpactPlayer(int Indx);
#endif // !IMPACT_H_