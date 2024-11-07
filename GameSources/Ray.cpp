/*!
@file Ray.cpp
@brief ���C
*/
//���݂̏������Əd����ԂɂȂ�\�����ƂĂ������̂ŏC���K�{���Ǝv���܂�
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr,Vec3 pos,float angle,weak_ptr<GameObject> parentObj) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rad(angle),
		m_parentObj(parentObj),
		m_discoveryObj(NULL)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
	{
		//Transform�쐬
		auto ptr = GetComponent<Transform>();//Transform�擾
		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(Vec3(3.0f,3.0f,3.0f));

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
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetFixed(true);
		//ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

	void Ray::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C���擾
		auto ptr = GetComponent<Transform>();//Transform�擾
		auto pos = ptr->GetPosition();
		float speed = 100;
		pos.x += cos(m_rad) * speed * delta;
		pos.z += sin(m_rad) * speed * delta;
		ptr->SetPosition(pos);
	}

	void Ray::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//�Ԃ������I�u�W�F�N�g�����܂łԂ��������Ƃ̂Ȃ��I�u�W�F�N�g�Ȃ�z��ɓ����
		for (auto a : m_discoveryObj)
		{
			if (a.lock() != other)//�I�u�W�F�N�g���O�o���Ă��镨�łȂ��Ƃ�
			{
				m_discoveryObj.push_back(other);//�L������
			}
			GetDisObj();//�擾�����I�u�W�F�N�g��n������
		}
		
		auto enemy = dynamic_pointer_cast<Wall>(other);
		if (enemy)
		{
			GetStage()->RemoveGameObject<Ray>(GetThis<Ray>());//�������g������
		}
	}

	//�擾�����I�u�W�F�N�g��n��
	vector<weak_ptr<GameObject>> Ray::GetDisObj()
	{
		return m_discoveryObj;
	}

}
//end basecross
