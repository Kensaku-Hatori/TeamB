#include "model.h"
#include "player.h"

MODELORIGIN g_ModelOrigin[MODELTYPE_MAX];
STAGEMODEL g_StageModel[MAX_STAGEMODEL];

void InitStageModel()
{
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		g_StageModel[ModelCount].bUse = false;
		g_StageModel[ModelCount].nType = MODELTYPE_ZERO;
		g_StageModel[ModelCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_StageModel[ModelCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
void UninitStageModel()
{
	for (int ModelCount = 0; ModelCount < MODELTYPE_MAX; ModelCount++)
	{
		if (g_ModelOrigin[ModelCount].pBuffMat != NULL)
		{
			g_ModelOrigin[ModelCount].pBuffMat->Release();
			g_ModelOrigin[ModelCount].pBuffMat = NULL;
		}
		if (g_ModelOrigin[ModelCount].pMesh != NULL)
		{
			g_ModelOrigin[ModelCount].pMesh->Release();
			g_ModelOrigin[ModelCount].pMesh = NULL;
		}
		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{
			if (g_ModelOrigin[ModelCount].pTexture[TexCount] != NULL)
			{
				g_ModelOrigin[ModelCount].pTexture[TexCount]->Release();
				g_ModelOrigin[ModelCount].pTexture[TexCount] = NULL;
			}
		}
	}
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].ModelBuff.pBuffMat != NULL)
		{
			g_StageModel[ModelCount].ModelBuff.pBuffMat = NULL;
		}
		if (g_StageModel[ModelCount].ModelBuff.pMesh != NULL)
		{
			g_StageModel[ModelCount].ModelBuff.pMesh = NULL;
		}
		for (int texcount = 0; texcount < MAX_TEX; texcount++)
		{
			if (g_StageModel[ModelCount].ModelBuff.pTexture[texcount] != NULL)
			{
				g_StageModel[ModelCount].ModelBuff.pTexture[texcount] = NULL;
			}
		}
	}
}
void UpdateStageModel()
{
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == true)
		{
			Player* pPlayer = GetPlayer();
			float fDistance = 0.0f;
			CollOBBs(g_StageModel[ModelCount].ObbModel, pPlayer->pos);
		}
	}
}
void DrawStageModel()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_StageModel[ModelCount].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_StageModel[ModelCount].rot.y, g_StageModel[ModelCount].rot.x, g_StageModel[ModelCount].rot.z);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].mtxWorld, &g_StageModel[ModelCount].mtxWorld, &mtxRot);

			g_StageModel[ModelCount].ObbModel.RotVec[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
			g_StageModel[ModelCount].ObbModel.RotVec[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
			g_StageModel[ModelCount].ObbModel.RotVec[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_StageModel[ModelCount].pos.x, g_StageModel[ModelCount].pos.y, g_StageModel[ModelCount].pos.z);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].mtxWorld, &g_StageModel[ModelCount].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_StageModel[ModelCount].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_StageModel[ModelCount].ModelBuff.pBuffMat->GetBufferPointer();

			for (int ModelMatCount = 0; ModelMatCount < (int)g_StageModel[ModelCount].ModelBuff.dwNumMat; ModelMatCount++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[ModelMatCount].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_StageModel[ModelCount].ModelBuff.pTexture[ModelMatCount]);
				//���f���̕`��
				g_StageModel[ModelCount].ModelBuff.pMesh->DrawSubset(ModelMatCount);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetStageModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++)
	{
		if (g_StageModel[ModelCount].bUse == false)
		{
			g_StageModel[ModelCount].bUse = true;
			g_StageModel[ModelCount].nType = nType;
			g_StageModel[ModelCount].ModelBuff = g_ModelOrigin[nType];
			g_StageModel[ModelCount].pos = pos;
			g_StageModel[ModelCount].rot = rot;

			int nNumVtx;   //���_��
			DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
			BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

			//���_���擾
			nNumVtx = g_StageModel[ModelCount].ModelBuff.pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y�擾
			sizeFVF = D3DXGetFVFVertexSize(g_StageModel[ModelCount].ModelBuff.pMesh->GetFVF());
			//���_�o�b�t�@�̃��b�N
			g_StageModel[ModelCount].ModelBuff.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ăv���C���[�̍ŏ��l�A�ő�l���擾
				//�ŏ��l
				if (vtx.x < g_StageModel[ModelCount].Min.x)
				{
					g_StageModel[ModelCount].Min.x = vtx.x;
				}
				if (vtx.y < g_StageModel[ModelCount].Min.y)
				{
					g_StageModel[ModelCount].Min.y = vtx.y;
				}
				if (vtx.z < g_StageModel[ModelCount].Min.z)
				{
					g_StageModel[ModelCount].Min.z = vtx.z;
				}
				//�ő�l
				if (vtx.x > g_StageModel[ModelCount].Max.x)
				{
					g_StageModel[ModelCount].Max.x = vtx.x;
				}
				if (vtx.y > g_StageModel[ModelCount].Max.y)
				{
					g_StageModel[ModelCount].Max.y = vtx.y;
				}
				if (vtx.z > g_StageModel[ModelCount].Max.z)
				{
					g_StageModel[ModelCount].Max.z = vtx.z;
				}
				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			//���_�o�b�t�@�̃A�����b�N
			g_StageModel[ModelCount].ModelBuff.pMesh->UnlockVertexBuffer();

			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;
			D3DXMatrixIdentity(&g_StageModel[ModelCount].ObbModel.CenterMtx);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_StageModel[ModelCount].rot.y, g_StageModel[ModelCount].rot.x, g_StageModel[ModelCount].rot.z);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].ObbModel.CenterMtx, &g_StageModel[ModelCount].ObbModel.CenterMtx, &mtxRotModel);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, 0.0f, g_StageModel[ModelCount].Max.y * 0.5f, 0.0f);
			D3DXMatrixMultiply(&g_StageModel[ModelCount].ObbModel.CenterMtx, &g_StageModel[ModelCount].ObbModel.CenterMtx, &mtxTransModel);

			mtxParent = g_StageModel[ModelCount].mtxWorld;

			D3DXMatrixMultiply(&g_StageModel[ModelCount].ObbModel.CenterMtx,
				&g_StageModel[ModelCount].ObbModel.CenterMtx,
				&mtxParent);

			pDevice->SetTransform(D3DTS_WORLD,
				&g_StageModel[ModelCount].ObbModel.CenterMtx);

			// ���S�_
			g_StageModel[ModelCount].ObbModel.CenterPos.x = g_StageModel[ModelCount].ObbModel.CenterMtx._41;
			g_StageModel[ModelCount].ObbModel.CenterPos.y = g_StageModel[ModelCount].ObbModel.CenterMtx._42;
			g_StageModel[ModelCount].ObbModel.CenterPos.z = g_StageModel[ModelCount].ObbModel.CenterMtx._43;

			// �e���W���̌X����\���x�N�g�����v�Z
			g_StageModel[ModelCount].ObbModel.RotVec[0] = D3DXVECTOR3(mtxRotModel._11, mtxRotModel._12, mtxRotModel._13);
			g_StageModel[ModelCount].ObbModel.RotVec[1] = D3DXVECTOR3(mtxRotModel._21, mtxRotModel._22, mtxRotModel._23);
			g_StageModel[ModelCount].ObbModel.RotVec[2] = D3DXVECTOR3(mtxRotModel._31, mtxRotModel._32, mtxRotModel._33);

			// ���S�_����ʂւ̋����̔���
			g_StageModel[ModelCount].ObbModel.fLength[0] = fabsf(g_StageModel[ModelCount].Max.x - g_StageModel[ModelCount].Min.x) * 0.5f;
			g_StageModel[ModelCount].ObbModel.fLength[1] = fabsf(g_StageModel[ModelCount].Max.y - g_StageModel[ModelCount].Min.y) * 0.5f;
			g_StageModel[ModelCount].ObbModel.fLength[2] = fabsf(g_StageModel[ModelCount].Max.z - g_StageModel[ModelCount].Min.z) * 0.5f;
			break;
		}
	}
}
void SetStageModelInfo(char *ModelPath[], int PathType)
{
	HRESULT Hresult;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const char* pFile = ModelPath[0];

	//X�t�@�C���̓ǂݍ���
	Hresult = D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelOrigin[PathType].pBuffMat,
		NULL,
		&g_ModelOrigin[PathType].dwNumMat,
		&g_ModelOrigin[PathType].pMesh);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_ModelOrigin[PathType].pBuffMat->GetBufferPointer();
	for (int nCntBlockMat = 0; nCntBlockMat < (int)g_ModelOrigin[PathType].dwNumMat; nCntBlockMat++)
	{
		if (pMat[nCntBlockMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, 
				pMat[nCntBlockMat].pTextureFilename, 
				&g_ModelOrigin[PathType].pTexture[nCntBlockMat]); //1
		}
		else
		{
			g_ModelOrigin[PathType].pTexture[nCntBlockMat] = NULL;
		}
	}

	if(FAILED(Hresult))
	{
		return;
	}
}
void LenOBBToPoint(OBB& obb, D3DXVECTOR3& p)
{
	D3DXVECTOR3 Vec(0, 0, 0);   // �ŏI�I�ɒ��������߂�x�N�g��

   // �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
	for (int DimensionCount = 0; DimensionCount < 3; DimensionCount++)
	{
		FLOAT L = obb.fLength[DimensionCount];
		if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
		D3DXVECTOR3 test = p - obb.CenterPos;
		FLOAT s = D3DXVec3Dot(&test, &obb.RotVec[DimensionCount]) / L;

		// s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
		s = (float)fabs(s);
		if (s > 1)
			Vec += (1 - s) * L * obb.RotVec[DimensionCount];   // �͂ݏo���������̃x�N�g���Z�o
	}
	FLOAT fDistance = D3DXVec3Length(&Vec);   // �������o��
	if (fDistance < 10)
	{
		Player* pPlayer = GetPlayer();
		pPlayer->pos = pPlayer->posOld;
	}
}
void CollOBBs(OBB& obb, D3DXVECTOR3& p)
{
	Player* pPlayer = GetPlayer();
	// �e�����x�N�g���̊m��
	   // �iN***:�W���������x�N�g���j
	D3DXVECTOR3 NAe1 = obb.RotVec[0], Ae1 = NAe1 * obb.fLength[0];
	D3DXVECTOR3 NAe2 = obb.RotVec[1], Ae2 = NAe2 * obb.fLength[1];
	D3DXVECTOR3 NAe3 = obb.RotVec[2], Ae3 = NAe3 * obb.fLength[2];
	D3DXVECTOR3 NBe1 = D3DXVECTOR3(1.0f, 0.0f, 0.0f), Be1 = NBe1 * 10.0f;
	D3DXVECTOR3 NBe2 = D3DXVECTOR3(0.0f, 1.0f, 0.0f), Be2 = NBe2 * 50.0f;
	D3DXVECTOR3 NBe3 = D3DXVECTOR3(0.0f, 0.0f, 1.0f), Be3 = NBe3 * 10.0f;

	D3DXVECTOR3 Interval = obb.CenterPos - p;
	bool bCollision = true;

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = (float)fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
		bCollision = false;

	// ������ : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
		bCollision = false;

	// ������ : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
		bCollision = false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
		bCollision = false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
		bCollision = false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	// ������ : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		bCollision = false;

	if (bCollision == true)
	{
		pPlayer->pos = pPlayer->posOld;
	}
}
// �������ɓ��e���ꂽ���������瓊�e���������Z�o
FLOAT LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	FLOAT r1 = (float)fabs(D3DXVec3Dot(Sep, e1));
	FLOAT r2 = (float)fabs(D3DXVec3Dot(Sep, e2));
	FLOAT r3 = e3 ? (float)fabs(D3DXVec3Dot(Sep, e3)) : 0;
	return r1 + r2 + r3;
}
void DotOBBToPoint(OBB& obb, D3DXVECTOR3& p)
{

}