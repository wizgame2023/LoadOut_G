/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ray::Ray(shared_ptr<Stage>& stagePtr, shared_ptr<Enemy> parentObj) :
		GameObject(stagePtr),
		m_parentObj(parentObj)
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
		//�����A���C�X�t�B�A�����O�󂯎�����I�u�W�F�N�g���擾���Ă��Ȃ������炻�̃I�u�W�F�N�g�͔z�񂩂����
		if (m_countTime >= 0.5f)
		{
			//GetStage()->AddGameObject<RaySphere>()
			//GetStage()->AddGameObject<RaySphere>(GetComponent<Transform>()->GetPosition(), atan2(m_controler.fThumbLY, m_controler.fThumbLX),GetThis<Ray>());

		}
	}

	//���C�X�t�B�A���擾�����I�u�W�F�N�g���󂯎��Z�b�^�[
	void Ray::SetDisObj(vector<weak_ptr<GameObject>> discoveryObj)
	{
		m_discoveryObj.clear();//�O�̔z��S�폜
		m_discoveryObj.swap(discoveryObj);//�V�����z��̒��g�ɂ���
		
		//for (auto test : m_discoveryObj)
		//{
		//	
		//}
		//m_discoveryObj[0].lock();
		////m_discoveryObj = discoveryObj;//�󂯎��
	}

}
//end basecross
