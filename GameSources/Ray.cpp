/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr, shared_ptr<Actor> parentObj,float range) :
		GameObject(stagePtr),
		m_parentObj(parentObj),
		m_range(range)
	{

	}

	Ray::~Ray()
	{
	}

	void Ray::OnCreate()
	{

	}

	void Ray::OnUpdate()
	{
		//���ƂȂ�I�u�W�F�N�g���������ꍇ�A������������
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<Ray>(GetThis<Ray>());
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		m_countTime += delta;

		//���C�̔���ƂȂ郌�C�X�t�B�A�𐶐�����
		if (m_countTime >= 0.2f)
		{	
			m_countTime = 0;//���Z�b�g
			auto raySphere = GetStage()->AddGameObject<RaySphere>(m_parentObj.lock()->GetComponent<Transform>()->GetPosition(), -m_angle, GetThis<Ray>(),m_range);//���C�X�t�B�A����
			//m_raySphere.push_back(raySphere);
			//auto a = 0;//�f�o�b�N�p
		}



		////�f�o�b�N�p
		//// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̎擾
		
		auto m_controler = inputDevice.GetControlerVec()[0];

		////�����������C�X�t�B�A���폜����
		//if (m_controler.wPressedButtons & XINPUT_GAMEPAD_X)
		//{

		//	auto stage = GetStage();//�X�e�[�W�擾
		//	//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		//	auto obj = stage->GetGameObjectVec();
		//	//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		//	for (auto raySphere : obj)
		//	{
		//		if (dynamic_pointer_cast<RaySphere>(raySphere))//���C�X�t�B�A�^�ɃL���X�g����
		//		{
		//			auto castRaySphere = dynamic_pointer_cast<RaySphere>(raySphere);
		//			auto itemTrans = raySphere->GetComponent<Transform>();
		//			auto itemPos = itemTrans->GetPosition();
		//			auto itemScale = itemTrans->GetScale();

		//			GetStage()->RemoveGameObject<RaySphere>(raySphere);//�폜�t���O�𗧂Ă�
		//			castRaySphere->SetRemove(true);//������t���O��n��
		//		}
		//	}


		//}

		
		

		//�f�o�b�N�p
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		////auto gameStage = scene->GetGameStage();

		//wss /* << L"�f�o�b�O�p������ "*/
		//	<< L"\n�X�� " << XMConvertToDegrees(-angle)
		//	<< endl;

		//scene->SetDebugString(wss.str());

	}

	//���C�X�t�B�A���擾�����I�u�W�F�N�g���󂯎��Z�b�^�[
	void Ray::SetDisObj(vector<weak_ptr<GameObject>> discoveryObj)
	{
		m_discoveryObj.clear();//�O�̔z��S�폜
		m_discoveryObj.swap(discoveryObj);//�V�����z��̒��g�ɂ���
		auto a = 0;//�f�o�b�N�p
	}

	vector<weak_ptr<GameObject>> Ray::GetDisObj()
	{
		//���������I�u�W�F�N�g�̏��̔z���n��
		return m_discoveryObj;

		//���̔z���n�����̂ł���Ȃ��Ȃ����z����폜
		m_discoveryObj.clear();//�O�̔z��S�폜

	}

	//���������I�u�W�F�N�g�̃|�C���^�[�z����폜����
	void Ray::ResetDisObj()
	{
		//�g��Ȃ��z����폜
		m_discoveryObj.clear();//�O�̔z��S�폜

	}

	//�o�Ă��郌�C�X�t�B�A��S�č폜
	void Ray::ResetRaySphere()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto raySphere : obj)
		{
			if (dynamic_pointer_cast<RaySphere>(raySphere))//���C�X�t�B�A�^�ɃL���X�g����
			{
				auto castRaySphere = dynamic_pointer_cast<RaySphere>(raySphere);
				auto itemTrans = raySphere->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				GetStage()->RemoveGameObject<RaySphere>(raySphere);//�폜�t���O�𗧂Ă�
				castRaySphere->SetRemove(true);//������t���O��n��
			}
		}

	}

	

	//�p�x�̃Z�b�^�[
	void Ray::SetAngle(float angle)
	{
		m_angle = angle;
	}

	//�p�x�̃Q�b�^�[
	float Ray::GetAngle()
	{
		return m_angle;
	}



}
//end basecross
