//==============================
//
//  魔法のUI処理[skillui.h]
//  Author:kaiti
//
//==============================
#ifndef _SKILLUI_H_
#define _SKILLUI_H_

#include "main.h"
#include "skill.h"

#define SKILLUI_SIZE (25)
#define SKILLUIFRAM_SIZE (35)

#define SKILLUI_SPACE (80)

//プロトタイプ宣言
void InitSkillUI(void);
void UninitSkillUI(void);
void UpdateSkillUI(void);
void DrawSkillUI(void);

#endif
