/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//�R���X�g���N�^�̐錾�E�f�X�g���N�^
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_speed(10)
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);
		trans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());
		m_CurrentSt->OnStart();
	}

	void Enemy::OnUpdate()
	{
		auto trans = GetComponent<Transform>();

		m_CurrentSt->OnUpdate();//���݂̃X�e�[�g�X�V����

		//���̃X�e�[�g�p�ϐ��ɉ�������̃X�e�[�g��������ꂽ��
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// ���݂̃X�e�[�g���Ō�ɍs������
			
			m_CurrentSt.reset();// ���݂̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt = m_NextSt;// ���݂̃X�e�[�g�Ɏ��̃X�e�[�g����
			
			m_NextSt.reset();// ���̃X�e�[�g�p�̕ϐ�����ɂ���
		
			m_CurrentSt->OnExit();// �؂�ւ�����V�����X�e�[�g�̍ŏ��ɍs������
		}

		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
			wss << L"transform : "
			<< L"\n"
			<< L"postion : ("
			<< L"\nx."
			<< trans->GetPosition().x
			<< L","
			<< "\ny."
			<< trans->GetPosition().y
			<< L","
			<< "\nz."
			<< trans->GetPosition().z
			<< L")"
			<< L"\nRot:"
			<< L"\nx." << trans->GetRotation().x
			<< L"\ny." << trans->GetRotation().y
			<< L"\nz." << trans->GetRotation().z
			<< endl;
		scene->SetDebugString(wss.str());

	}
	void Enemy::OnDestroy()
	{
		// �I�u�W�F�N�g���̂��j������鎞�Ɍ��݂Ǝ��̃X�e�[�g�p�̕ϐ�����ɂ���
		m_CurrentSt.reset();
		m_NextSt.reset();

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}
}
//end basecross
