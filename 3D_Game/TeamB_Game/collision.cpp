//*************************************
//
// 当たり判定をまとめたcpp[collision.h]
// Author Kensaku Hatori
//
//*************************************
#include "collision.h"

//*********************
// 点と矩形の当たり判定
//*********************
bool collisionboxtopoint(D3DXVECTOR3 Pos, BoxCollision BoxInfo)
{
	for (int FaceCount = 0; FaceCount < 4; FaceCount++)
	{
		if (BoxInfo.Nor[FaceCount].x > 1.0f ||
			BoxInfo.Nor[FaceCount].y > 1.0f ||
			BoxInfo.Nor[FaceCount].z > 1.0f)
		{
			D3DXVec3Normalize(&BoxInfo.Nor[FaceCount], &BoxInfo.Nor[FaceCount]);
		}
		D3DXVECTOR3 pVec = BoxInfo.FacePos[FaceCount] - Pos;
		float fDot = D3DXVec3Dot(&pVec, &BoxInfo.Nor[FaceCount]);
		if (fDot < 0)
		{
			return true;
		}
	}
	return false;
}
//*******************
// 球と球の当たり判定
//*******************
bool collisioncircle(D3DXVECTOR3 Pos, float fRadius, D3DXVECTOR3 Pos1, float fRadius1)
{
	D3DXVECTOR3 Math = Pos - Pos1;
	float fDistance = D3DXVec3Length(&Math);
	float fMathRadius = fRadius + fRadius1;
	fMathRadius = fMathRadius * fMathRadius;
	if (fDistance < fMathRadius)
	{
		return true;
	}
	return false;
}
//*********************
// OBBとOBBの当たり判定
//*********************
bool collisionobb(OBB obb, OBB obb1, D3DXVECTOR3 Pos, D3DXVECTOR3 Pos1)
{
	// 各方向ベクトルの確保
   // （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = obb.RotVec[0], Ae1 = NAe1 * obb.fLength[0];	// X軸
	D3DXVECTOR3 NAe2 = obb.RotVec[1], Ae2 = NAe2 * obb.fLength[1];	// Y軸
	D3DXVECTOR3 NAe3 = obb.RotVec[2], Ae3 = NAe3 * obb.fLength[2];	// Z軸
	D3DXVECTOR3 NBe1 = obb1.RotVec[0], Be1 = NBe1 * obb1.fLength[0];
	D3DXVECTOR3 NBe2 = obb1.RotVec[1], Be2 = NBe2 * obb1.fLength[1];
	D3DXVECTOR3 NBe3 = obb1.RotVec[2], Be3 = NBe3 * obb1.fLength[2];

	D3DXVECTOR3 r;
	D3DXVECTOR3 MathX;
	D3DXVECTOR3 MathY;
	D3DXVECTOR3 MathZ;
	D3DXVECTOR3 MathPos;
	MathPos = Pos - Pos1;
	MathX = obb.RotVec[0] * obb.fLength[0];
	MathY = obb.RotVec[1] * obb.fLength[1];
	MathZ = obb.RotVec[2] * obb.fLength[2];
	r.x = (float)fabs(D3DXVec3Dot(&MathX, &NBe1));
	r.y = (float)fabs(D3DXVec3Dot(&MathY, &NBe2));
	r.z = (float)fabs(D3DXVec3Dot(&MathZ, &NBe3));

	FLOAT sX = D3DXVec3Dot(&MathPos, &NBe1);
	FLOAT sY = D3DXVec3Dot(&MathPos, &NBe2);
	FLOAT sZ = D3DXVec3Dot(&MathPos, &NBe3);

	D3DXVECTOR3 Interval = MathPos;
	bool bCollision = true;

	// 分離軸 : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = (float)fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
	{
		return false;
	}
	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
	{
		return false;
	}
	return true;
}
//*************
// 押し出し関数
//*************
void PushPosition(D3DXVECTOR3* Pos, D3DXVECTOR3 VecMove, D3DXVECTOR3 Nor)
{
	if (Pos == NULL)
	{
		return;
	}
	D3DXVECTOR3 PushMove = Nor * D3DXVec3Dot(&VecMove, &Nor);
	*Pos += PushMove;
}