//==============================
//
//  �I�v�V��������[option.h]
//  Author:kaiti
//
//==============================
#ifndef _OPTION_H_
#define _OPTION_H_

#include "main.h"

#define OPTION_X (100)
#define OPTION_Y (50)

#define OPTION_YAJIRUSI_SIZE (30)
#define OPTION_NO_SIZE (30)
//�|�[�Y���j���[
typedef enum
{
	OPTION_KANDO = 0,
	OPTION_MAX,
}OPTION;

typedef struct
{
	float cameraSP;
	OPTION type;
}Option;

//�v���g�^�C�v�錾
void InitOption(void);
void UninitOption(void);
void UpdateOption(void);
void DrawOption(void);
Option* GetOption(void);
void SelectOption(int zDelta);
void OptionKando(void);
void SetOptionKando(void);
#endif