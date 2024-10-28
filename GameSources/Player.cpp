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

		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾

		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto& gamePad = inputDevice.GetControlerVec()[0];


		//���X�e�b�N�̌����Ƀv���C���[���i��
		if (gamePad.bConnected)
		{
			m_Pos.x += gamePad.fThumbLX*10*Delta;
			m_Pos.z += gamePad.fThumbLY*10*Delta;

			m_Trans->SetPosition(m_Pos);//�|�W�V�����X�V
		}
		float deg = 0;
		//���X�e�b�N�̌����Ƀv���C���[������
		if (gamePad.bConnected)
		{
			//�X�e�B�b�N�̌X�������W�A���ɂ���
			float rad = -atan2(gamePad.fThumbLY, gamePad.fThumbLX);
			//���W�A���̌X�����f�B�O���[�p�ɂ���
			deg = rad * 180 / 3.14f;
			m_Rot.y = rad;

			m_Trans->SetRotation(m_Rot);

		}

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		Vec2 selPos = mapManager->ConvertSelMap(m_Pos);//������Z�����W���擾
		int selNow = mapManager->SelMapNow(m_Pos);//���݂���Z�����W�ɉ������邩���擾

		//�ł��܂���
		if (m_count >= 1)//�J�E���g���P�ȏ�Ȃ�
		{
			auto device = App::GetApp()->GetInputDevice().GetControlerVec();
			if (gamePad.wPressedButtons & XINPUT_GAMEPAD_B)//B�{�^�����������Ƃ�
			{
				m_count--;
				if (mapManager->SelMapNow(m_Pos) == 1)//�����A���݂���Z�����W���}���z�[���̏�Ȃ��
				{
					mapManager->MapDataUpdate(m_Pos, 2);//㩂�ݒu����

				}
			}

			
		}

		//�f�o�b�N�p
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"�f�o�b�O�p������ "
			<<L"\n�X�� "<<deg
			<< L"\nPos.x " << m_Pos.x << "\nPos.z " << m_Pos.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<< L"\nCount " << m_count
			<< L"\nSelNow " << selNow
			<< endl;

		scene->SetDebugString(wss.str());

	}

	void Player::SetUp()
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾

		//���̃Z�����W���}���z�[���̏�Ȃ�㩂�u������
		if (mapManager->SelMapNow(m_Pos) == 1)
		{
			mapManager->MapDataUpdate(m_Pos, 2);//���݂̃Z�����W��㩂�u������������
		}
	}

	//m_count�ɐ��l���v���X�����
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

