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
		ptr->SetScale(10.0f*0.5f, 1.0f, 10.0f*0.5f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(2.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CYLINDER");
		ptrDraw->SetTextureResource(L"Manhole");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾

		AddTag(L"Manhole");//�}���z�[���p�̃^�O

	}

	void Manhole::OnUpdate()
	{
		m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto stage = GetStage();//�X�e�[�W�擾

		ManholeTransition();//�}���z�[���̑J��

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"���� : " << m_time
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}

	//�}���z�[���̑J��
	void Manhole::ManholeTransition()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto stage = GetStage();//�X�e�[�W�擾

		//�Z�����W�ɃA�C�e����ݒu������񂪂�������
		if (m_mapManager.lock()->SelMapNow(m_pos) == 2 && m_charen == 0)
		{
			m_charen = 1;//�A�C�e�����u����Ă�����
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������
		}

		//�N�[���^�C���߂�����d�r�̍R�͂��؂�ă}���z�[�����オ��Ȃ��悤�ɂ���
		if (m_charen == 1)//�d�r�����Ă�����
		{
			m_stanbyTime += delta;
			//3�b�o������_�ł���
			if (m_stanbyTime > 3.0f)
			{
				m_blinkingTime += delta;
				if (m_blinkingTime < 0.1f)
				{
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");
				}
				if (m_blinkingTime > 0.2f)
				{
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");
				}
				if (m_blinkingTime > 0.3f)
				{
					m_blinkingTime = 0;
				}
			}
			//�X�^���o�C��Ԃ��I����
			if (m_stanbyTime > 5.0f)
			{
				m_stanbyTime = 0;//�N�[���^�C�����Z�b�g
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//�������g�ɃA�C�e�����u����Ă��Ȃ���Ԃ��ƕ�����₷������
				m_mapManager.lock()->MapDataUpdate(m_pos, 3);//�グ��悤�ɂ���
			}

		}

		//�ʍs�֎~�ɂȂ鎞�̏���
		if (m_mapManager.lock()->SelMapNow(m_pos) == 3 && m_charen == 1)
		{
			m_charen = 2;//�ʍs�֎~�ɂȂ��Ă�����
			Vec3 clearPos = m_pos;
			clearPos.y += 5.0f;
			m_clearObject = GetStage()->AddGameObject<ClearObject>(clearPos, Vec3(0.0f, 0.0f, 0.0f));
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
			m_blinkingTime = 0;//�_�ł̃N�[���^�C�������Z�b�g����

			//��������������
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 10.0f, 10.0f));
		}

		//�ʍs�֎~�̎��̍ۂ̏���
		if (m_charen == 2)
		{
			//�N�[���^�C���߂�����ʂ��悤�ɂ���
			m_coolTime += delta;
			if (m_coolTime > 10.0f)//���Ԃ��߂�����
			{
				m_coolTime = 0;//�N�[���^�C�����Z�b�g
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������
				m_mapManager.lock()->MapDataUpdate(m_pos, 1);//�}�b�v�}�l�[�W���[�ɒʂ���Ԃ��ƕԂ�
				stage->RemoveGameObject<ClearObject>(m_clearObject);//�O�������������ȃI�u�W�F�N�g������
				stage->RemoveGameObject<WaterPillar>(m_waterPillar);//�O������������������
				m_charen = 0;
				m_blinkingTime = 0;
				m_stanbyTime = 0;
			}

		}

	}

	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto test = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);

		if (test->SelMapNow(m_pos) == 2)
		{//�������������I�u�W�F�N�g���G�Ȃ�
			if (enemy)
			{
				//GetStage()->RemoveGameObject<Enemy>(enemy);//�܂��G�������[�u���Ȃ�
				test->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");

				GetStage()->AddGameObject<MovieUpEnemy>(enemy);//�ł������鎞�̓G�̃��[�r�[
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//�Q�[���N���A�Ɉړ�����(���œG��1�l�����Ȃ�����)

			}
			if (player)//�v���C���[�Ȃ�
			{
				GetStage()->AddGameObject<MovieUpPlayer>();//Player���オ���Ă��܂����[�r���o��
			}
		}
	}

	void Manhole::OnCollisionExit(shared_ptr<GameObject>& other)
	{
		auto mapManager = m_mapManager.lock();
		auto player = dynamic_pointer_cast<Player>(other);

		if (mapManager->SelMapNow(m_pos)==2)
		{
			//Player�����ꂽ��܂��v���C�������邩�҂t���O�𗧂Ă�
			if (player)
			{
				m_playerStanbyFlag = true;
			}
		}

	}


}
//end basecross
