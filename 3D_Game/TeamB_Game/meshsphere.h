//=========================================================
// 
// ���b�V���X�t�B�A[meshsphere.h]
// Aothor:Rio Ohno
// 
//=========================================================

#ifndef MESHSPHERE_H_
#define MESHSPHERE_H_

//�C���N���[�h
#include "main.h"

void InitMeshSphere(void);
void UninitMeshSphere(void);
void UpdatetMeshSphere(void);
void DrawMeshSphere(void);
void SetMeshSphere(D3DXVECTOR3 pos, float radius, int nDiviX);

#endif // !MESHSPHERE_H_