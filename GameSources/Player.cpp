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
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(-90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);


		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"Player_Mesh_Kari");
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//ptrDraw->SetTextureResource(L"");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//ptrColl->SetSleepActive(false);//�Ԃ���Ȃ�����X���[�v��ԂɂȂ�
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		ptrColl->SetDrawActive(true);//�R���W������������悤�ɂ���


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
		//�R���g���[���[�̎擾
		m_controler = inputDevice.GetControlerVec()[0];
		auto pos = GetComponent<Transform>()->GetPosition();//�|�W�V�����擾


		PlayerMove();//�v���C���[�̓���

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		Vec2 selPos = mapManager->ConvertSelMap(pos);//������Z�����W���擾
		int selNow = mapManager->SelMapNow(pos);//���݂���Z�����W�ɉ������邩���擾

		ManholeSet(pos);//�}���z�[���̏�ɂ�Ȃ��d�|���鏈��

		//�f�o�b�N�p��hp�����炷
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_Y)//Y�{�^����hp�����炷
		{
			m_hp -= 1;
		}
		if (m_hp <= 0)//�̗͂�0�ɂȂ�����
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//�Q�[���I�[�o�V�[���Ɉړ�����
		}

		auto rot = GetComponent<Transform>()->GetRotation();//��]�x���擾

		//�f�o�b�N�p
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"�f�o�b�O�p������ "
			<< L"\n�X�� " << m_deg
			<< L"\nPos.x " << pos.x << "\nPos.z " << pos.z
			<<L"\nrot.x "<<rot.x << L"\nrot.y " << rot.y << "\nrot.z" << rot.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<< L"\nCount " << m_count
			<< L"\nSelNow " << selNow
			<< L"\ntest " <<  XMConvertToDegrees(XM_PI * 0.5f)
			<<L"\nFPS:"<< 1.0f/Delta
			<< endl;
		//XMConvertToRadians(-90.0f)e

		scene->SetDebugString(wss.str());

	}

	void Player::PlayerMove()//�v���C���[�̌����⓮�����Ǘ�����֐�
	{
		auto pos = GetComponent<Transform>()->GetPosition();//�|�W�V�����擾
		auto Delta = App::GetApp()->GetElapsedTime();

		//���X�e�b�N�̌����Ƀv���C���[���i��
		if (m_controler.bConnected)
		{

			pos.x += (m_controler.fThumbLX * 10 * Delta) * 2;
			pos.z += (m_controler.fThumbLY * 10 * Delta) * 2;

			m_Trans->SetPosition(pos);//�|�W�V�����X�V
		}

		float deg = 0;
		//���X�e�b�N�̌����Ƀv���C���[������
		if (m_controler.bConnected)
		{
			//�X�e�B�b�N�̌X�������W�A���ɂ���
			float rad = -atan2(m_controler.fThumbLY, m_controler.fThumbLX);
			//���W�A���̌X�����f�B�O���[�p�ɂ���
			m_deg = rad * 180 / 3.14f;
			m_Rot.y = rad;
			//�Q�[���p�b�g�̌X����������Ή�]�x�͍X�V���Ȃ�
			if (m_controler.fThumbLY != 0.0f && m_controler.fThumbLX != 0.0f)
			{
				m_Trans->SetRotation(m_Rot);
			}

		}

	}

	//�}���z�[���̏�ɂ�Ȃ��d�|���鏈��
	void Player::ManholeSet(Vec3 pos)
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾

		if (m_count >= 1)//�J�E���g���P�ȏ�Ȃ�
		{
			auto device = App::GetApp()->GetInputDevice().GetControlerVec();
			if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)//B�{�^�����������Ƃ�
			{
				if (mapManager->SelMapNow(pos) == 1)//�����A���݂���Z�����W���}���z�[���̏�Ȃ��
				{
					m_count--;
					mapManager->MapDataUpdate(pos, 2);//㩂�ݒu����

				}
			}


		}
	}

	void Player::SetUp()
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		auto pos = GetComponent<Transform>()->GetPosition();

		//���̃Z�����W���}���z�[���̏�Ȃ�㩂�u������
		if (mapManager->SelMapNow(pos) == 1)
		{
			mapManager->MapDataUpdate(pos, 2);//���݂̃Z�����W��㩂�u������������
		}
	}

	//m_count�ɐ��l���v���X�����
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

