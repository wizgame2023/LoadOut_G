/*!
@file RaySphere.cpp
@brief ���C
*/
//���݂̏������Əd����ԂɂȂ�\�����ƂĂ������̂ŏC���K�{���Ǝv���܂�
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RaySphere::RaySphere(shared_ptr<Stage>& stagePtr,Vec3 pos,float angle,weak_ptr<Ray> parentObj,float range) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rad(angle),
		m_parentObj(parentObj),
		m_range(range),
		m_originPos(pos),
		m_discoveryObj(NULL)
	{

	}

	RaySphere::~RaySphere()
	{
	}

	void RaySphere::OnCreate()
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

		AddTag(L"RaySphere");//���C�X�t�B�A�p�̃^�O

	}

	void RaySphere::OnUpdate()
	{
		//���ƂȂ�I�u�W�F�N�g���������ꍇ�A������������
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());
			return;

		}


		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C���擾
		auto ptr = GetComponent<Transform>();//Transform�擾
		auto pos = ptr->GetPosition();
		float speed = 100;
		pos.x += cos(m_rad) * speed * delta;
		pos.z += sin(m_rad) * speed * delta;
		ptr->SetPosition(pos);

		m_moveVec = Vec3((m_originPos.x - pos.x), (m_originPos.y - pos.y), (m_originPos.z - pos.z));
		float move = RemoveMinus(m_moveVec.x) + RemoveMinus(m_moveVec.y) + RemoveMinus(m_moveVec.z);
		
		//���_�����苗�����ꂽ�ꍇ������������
		if (move >= m_range)
		{
			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());//�������g��������
			m_parentObj.lock()->SetDisObj(m_discoveryObj);//�擾�����I�u�W�F�N�g��n��

		}


		
	}

	void RaySphere::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//�Ԃ������I�u�W�F�N�g�����܂łԂ��������Ƃ̂Ȃ��I�u�W�F�N�g�Ȃ�z��ɓ����
		//for (auto a : m_discoveryObj)
		//{
		//	if (a.lock() != other)//�I�u�W�F�N�g���O�o���Ă��镨�łȂ��Ƃ�
		//	{
				//m_discoveryObj.push_back(other);//�L������
			//}
			//m_parentObj.lock()->SetDisObj(m_discoveryObj);//�擾�����I�u�W�F�N�g��n��
		//}
		
		auto wall = dynamic_pointer_cast<Wall>(other);
		auto player = dynamic_pointer_cast<Player>(other);
		if (wall||player)
		{
			m_discoveryObj.push_back(other);//�L������
			m_parentObj.lock()->SetDisObj(m_discoveryObj);//�擾�����I�u�W�F�N�g��n��

			GetStage()->RemoveGameObject<RaySphere>(GetThis<RaySphere>());//�������g������
		}
	}

	//�擾�����I�u�W�F�N�g��n��
	vector<weak_ptr<GameObject>> RaySphere::GetDisObj()
	{
		return m_discoveryObj;
	}

	float RaySphere::RemoveMinus(float num)
	{
		//num��0��菬����������0�����傫������
		if (num <= 0)
		{
			num = -num;
		}

		return num;
	}

}
//end basecross
