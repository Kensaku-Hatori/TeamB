//================================
//
//�@�J��������[camera.h]
//�@Author:kaiti
//
//================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define CAMERA_DISTANCESPEED (float)(0.1f)
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;//���_
	D3DXVECTOR3 posR;//�����_

	D3DXVECTOR3 posVDest;//���_
	D3DXVECTOR3 posRDest;//�����_
	
	D3DXVECTOR3 vecU;//������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotDest;
	float fDistance;//���_���璍���_�̋���
	bool bResete;
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void UpdateCameratoMousePos(void);
void UpdateCameratoJoyPadPos(void);
void SetCamera(void);
Camera * GetCamera(void);
void SetMouseWheel(int zDelta);
void ResetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
#endif