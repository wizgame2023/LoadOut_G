/*!
@file Ray.cpp
@brief ���C
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
	{
		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(Vec3(0.0f,0.0f,0.0f));
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(Vec3(10.0f,10.0f,10.0f));

		//Transform�ɑ΂��Ă̓�������
		//Mat4x4 spanMat;
		//spanMat.affineTransformation(
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);

		//���b�V������
		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

	void Ray::OnUpdate()
	{
		auto ptr = GetComponent<Transform>();//Transform�擾
		auto pos = ptr->GetPosition();
		pos.x += 1;
		ptr->SetPosition(pos);
	}

	void Ray::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		
	}

}
//end basecross
