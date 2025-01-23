//==============================
//
//  �Q�[�W����[gauge.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include"main.h"

typedef enum
{
	GAUGETYPE_HP = 0,
	GAUGETYPE_MP,
	GAUGETYPE_MAX,
}GAUGETYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	GAUGETYPE type;
	bool bUse;
}Gauge;

//�v���g�^�C�v�錾
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void SetGauge(GAUGETYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size);
void GaugeCalculation(int nValue, GAUGETYPE type);

#endif
