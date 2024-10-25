/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& StagePtr,Vec3 pos,Vec3 rot) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Rot(rot)
	{
	}
	Player::~Player()
	{
	}

	void Player::OnCreate()
	{
		m_Trans = GetComponent<Transform>();
		m_Trans->SetPosition(m_Pos);
		m_Trans->SetRotation(m_Rot);
		m_Trans->SetScale(5.0f, 5.0f, 5.0f);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);


		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�

		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Player");//�^�O�ǉ�
	}

	void Player::OnUpdate()
	{
		//�f���^�^�C��
		auto Delta = App::GetApp()->GetElapsedTime();

		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto contorollerVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//���X�e�b�N�̌����Ƀv���C���[���i��
		if (contorollerVec[0].bConnected)
		{
			m_Pos.x += contorollerVec[0].fThumbLX*10*Delta;
			m_Pos.z += contorollerVec[0].fThumbLY*10*Delta;

			m_Trans->SetPosition(m_Pos);//�|�W�V�����X�V
		}
		float deg;
		//���X�e�b�N�̌����Ƀv���C���[������
		if (contorollerVec[0].bConnected)
		{
			//�X�e�B�b�N�̌X�������W�A���ɂ���
			float rad = -atan2(contorollerVec[0].fThumbLY, contorollerVec[0].fThumbLX);
			//���W�A���̌X�����f�B�O���[�p�ɂ���
			deg = rad * 180 / 3.14f;
			m_Rot.y = rad;

			m_Trans->SetRotation(m_Rot);

		}

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		Vec2 selPos = mapManager->MyMapNow(m_Pos);

		//�f�o�b�N�p
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"�f�o�b�O�p������ "
			<<L"\n�X�� "<<deg
			<< L"\nPos.x " << m_Pos.x << "\nPos.z " << m_Pos.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<<L"\nCount "<<m_count
			<< endl;

		scene->SetDebugString(wss.str());

	}

	//m_count�ɐ��l���v���X�����
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

