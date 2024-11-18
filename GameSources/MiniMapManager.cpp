/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	void MiniMapManager::OnCreate()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		float Lenght = 225.0f;//�~�j�}�b�v�̒��a
		stage->AddGameObject<Sprite>(L"Gray", Vec2(Lenght, Lenght), Vec3(-640+(Lenght/2.0f), 400.0f - (Lenght / 2.0f), 0.0f));

		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f),5.0f);//�X�^�[�g�|�W�V����
		auto test = m_startPos;
		auto a = 0;
		m_mapSize = 200;//map�̒��a
		m_mapMagnification = Lenght / m_mapSize;//�}�b�v�̔{��

		CreateManhole();//�}���z�[���𐶐�//������������G���[�ł�H
		CreateEnemy();
	}

	void MiniMapManager::OnUpdate()
	{

	}

	//�~�j�}�b�v�p�̕ǂ𐶐�
	void MiniMapManager::CreateWall()
	{

	}

	//�~�j�}�b�v�p�̃A�C�e���𐶐�
	void MiniMapManager::CreateItem()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto item : obj)
		{
			if (dynamic_pointer_cast<Item>(item))//�A�C�e���^�ɃL���X�g����
			{
				auto castitem = dynamic_pointer_cast<Item>(item);
				auto itemTrans = item->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();
				
				stage->AddGameObject<MiniMapItem>(castitem ,L"White", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification),5,
					Vec3(m_startPos.x+(itemPos.x*m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification),0.0f),Vec3(0.0f,0.0f,0.0f));
			}
		}
	}

	//�~�j�}�b�v�p�̃}���z�[�����쐬
	void MiniMapManager::CreateManhole()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto manhole : obj)
		{
			if (dynamic_pointer_cast<Manhole>(manhole))//�A�C�e���^�ɃL���X�g����
			{
				auto castManhole = dynamic_pointer_cast<Manhole>(manhole);
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<Sprite>(L"Red", Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f), 10);
			}
		}

	}

	//�~�j�}�b�v�p�̓G���쐬
	void MiniMapManager::CreateEnemy()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto manhole : obj)
		{
			if (dynamic_pointer_cast<Enemy>(manhole))//�A�C�e���^�ɃL���X�g����
			{
				float Lenght = 225.0f;//�~�j�}�b�v�̒��a

				auto castEnemy = dynamic_pointer_cast<Actor>(manhole);
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<MiniMapActor>(castEnemy, L"MiniEnemy", Vec2((itemScale.x / m_mapMagnification) * 3, (itemScale.z / m_mapMagnification) * 3), m_startPos, m_mapSize, Lenght);
			}
		}

	}

	Vec3 MiniMapManager::GetStartPos()
	{
		return m_startPos;
	}

	

}
//end basecross
