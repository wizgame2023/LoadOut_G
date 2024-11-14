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
		auto angle = m_parentObj.lock()->GetAngle();//�p�x���擾

		//���C�̔���ƂȂ郌�C�X�t�B�A�𐶐�����
		if (m_countTime >= 0.5f)
		{	
			m_countTime = 0;//���Z�b�g
			GetStage()->AddGameObject<RaySphere>(m_parentObj.lock()->GetComponent<Transform>()->GetPosition(), -angle, GetThis<Ray>(),m_range);//���C�X�t�B�A����
		}

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
		vector<weak_ptr<GameObject>> discoveryObj;//�V������̔z��𐶐�
		m_discoveryObj.swap(discoveryObj);//�V�����z��̒��g�ɂ���

	}



}
//end basecross
