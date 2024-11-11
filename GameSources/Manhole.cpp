/*!
@file Manhole.cpp
@brief �}���z�[��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Manhole::Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos)
	{

	}
	Manhole::~Manhole()
	{
	}

	void Manhole::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(10.0f, 1.0f, 10.0f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Manhole");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾

	}

	void Manhole::OnUpdate()
	{
		m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾

		//m_mapManager.lock()->MapDataUpdate(m_pos, 1);//������Z�����W�̓}���z�[���̃f�[�^�Ƃ������Ƃ�`����
		//�Z�����W�ɃA�C�e����ݒu������񂪂�������
		auto test = m_charen;
		auto a = 0;
		if (m_mapManager.lock()->SelMapNow(m_pos)==2&&m_charen==0)
		{
			m_charen = 1;
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Red");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������
		}
	}

	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto test = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);


		if (test->SelMapNow(m_pos) == 2)
		{//�������������I�u�W�F�N�g���G�Ȃ��
			if (enemy)
			{
				GetStage()->RemoveGameObject<Enemy>(enemy);
				test->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Prohibited");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������

				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//�Q�[���N���A�Ɉړ�����(���œG��1�l�����Ȃ�����)

			}
		}
	}

}
//end basecross
