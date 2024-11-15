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
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		m_countTime += delta;

		//���C�̔���ƂȂ郌�C�X�t�B�A�𐶐�����
		if (m_countTime >= 0.1f)
		{	
			m_countTime = 0;//���Z�b�g
			auto raySphere = GetStage()->AddGameObject<RaySphere>(m_parentObj.lock()->GetComponent<Transform>()->GetPosition(), -m_angle, GetThis<Ray>(),m_range);//���C�X�t�B�A����
			//m_raySphere.push_back(raySphere);
			//auto a = 0;//�f�o�b�N�p
		}

		////�f�o�b�N�p
		//// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		//auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		////�R���g���[���[�̎擾
		//auto m_controler = inputDevice.GetControlerVec()[0];

		////�����������C�X�t�B�A���폜���� �쐬�r��
		//if (m_controler.wPressedButtons & XINPUT_GAMEPAD_X)
		//{
		//	//for (auto a : m_raySphere)
		//	//{
		//	//	GetStage()->RemoveGameObject<RaySphere>(a.lock());
		//	//	auto test = m_raySphere;
		//	//}
		//	//�X�e�[�W��̃I�u�W�F�N�g�����ׂČ��ē���̃^�O�̃I�u�W�F�N�g���擾����
		//	//GetStage()->GetUsedTagObjectVec(L"RaySphere", shared_ptr<RaySphere>)
		//	//weak_ptr<RaySphere> obj[] = 

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
