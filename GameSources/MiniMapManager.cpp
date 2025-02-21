/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr, float mapSize) :
		GameObject(stagePtr),
		m_mapSize(mapSize)
	{

	}
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_mapSize(200)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	//��������
	void MiniMapManager::OnCreate()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		float Lenght = 225.0f;//�~�j�}�b�v�̒��a
		auto background = stage->AddGameObject<Sprite>(L"Gray", Vec2(Lenght, Lenght), Vec3(-640+(Lenght/2.0f), 400.0f - (Lenght / 2.0f), 0.0f));
		background->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		m_startPos = Vec3(-640 + (Lenght / 2.0f), 400.0f - (Lenght / 2.0f),5.0f);//�X�^�[�g�|�W�V����
		m_mapMagnification = Lenght / m_mapSize;//�}�b�v�̔{��

		CreateManhole();//�}���z�[���𐶐�
		CreateEnemy();//�GUI����
		CreatePlayer();//PlayerUI�쐬
		CreateWall();//��UI����
	}

	//�X�V����
	void MiniMapManager::OnUpdate()
	{
		UpdateBattery();
		UpdateEnemy();
	}

 
	//�~�j�}�b�v�p�̃A�C�e���𐶐�
	void MiniMapManager::CreateBattery()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto objVec = stage->GetGameObjectVec();
		int count = 0;
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Spanner>(item);
			if (castitem)//�A�C�e���^�ɃL���X�g����
			{
				auto itemTrans = item->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();
				
				auto miniMapItem = stage->AddGameObject<MiniMapItem>(castitem, L"White", Vec2(itemScale.x * m_mapMagnification, itemScale.z * m_mapMagnification)/*size*/,
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),
					Col4(1.0f, 1.0f, 0.0f, 1.0f)/*���F�ɂ���*/, 5/*���C���[*/);
				miniMapItem->AddTag(L"MiniMapItem");//�^�O��ǉ�
				count++;
			}
		}
		m_beforeItemNum = count;
	}
	//�~�j�}�b�v�p�̃A�C�e���𐶐�(Updeta��)
	void MiniMapManager::UpdateBattery()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto objVec = stage->GetGameObjectVec();
		int itemNumNow = 0;
		//�X�e�[�W�ɂ���A�C�e���̐����J�E���g����
		for (auto item : objVec)
		{
			auto castitem = dynamic_pointer_cast<Spanner>(item);
			if (castitem)//�A�C�e���^�ɃL���X�g����
			{
				itemNumNow++;
			}
		}

		//������A�C�e���̐����O��������������~�j�}�b�v�̃A�C�e���̕\�����X�V����
		if (itemNumNow > m_beforeItemNum)
		{
			//�~�j�}�b�v�ɂ���A�C�e�������Z�b�g����
			for (auto sprite : objVec)
			{
				auto castsprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castsprite)//�A�C�e���^�ɃL���X�g����
				{
					//�^�O��MiniMapItem
					if (castsprite->FindTag(L"MiniMapItem"))
					{
						castsprite->MyDestroy();//�������g����������
					}
				}
			}

			//�Đ�������
			CreateBattery();
		}

		m_beforeItemNum = itemNumNow;//�X�V����
	}

	//�~�j�}�b�v�̓G�\��(Update��)
	void MiniMapManager::UpdateEnemy()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto objVec = stage->GetGameObjectVec();
		int enemyNumNow = 0;
		//�X�e�[�W�ɂ���A�C�e���̐����J�E���g����
		for (auto enemy : objVec)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(enemy);
			if (castEnemy)//�A�C�e���^�ɃL���X�g����
			{
				enemyNumNow++;
			}
		}

		//������A�C�e���̐����O��������������~�j�}�b�v�̃A�C�e���̕\�����X�V����
		if (enemyNumNow > m_beforeEnemyNum)
		{
			//�~�j�}�b�v�ɂ���A�C�e�������Z�b�g����
			for (auto sprite : objVec)
			{
				auto castsprite = dynamic_pointer_cast<MiniMapActor>(sprite);
				if (castsprite)//�L���X�g����
				{
					//�^�O��MiniMapItem
					if (castsprite->FindTag(L"MiniMapEnemy"))
					{
						castsprite->MyDestroy();//�������g����������
					}
				}
			}
			//�Đ�������
			CreateEnemy();
		}

		m_beforeEnemyNum = enemyNumNow;//�X�V����
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
			auto castManhole = dynamic_pointer_cast<Manhole>(manhole);
			if (castManhole)//�A�C�e���^�ɃL���X�g����
			{
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<ManholeSprite>(castManhole, L"Bule",Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f), 10);
			}
		}

	}

	//�~�j�}�b�v�p�̃n�b�`���쐬
	void MiniMapManager::CreateHatch()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto objVec = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto obj : objVec)
		{
			auto castHatch = dynamic_pointer_cast<Hatch>(obj);
			if (castHatch)//�A�C�e���^�ɃL���X�g����
			{
				auto hatchTrans = castHatch->GetComponent<Transform>();
				auto hatchPos = hatchTrans->GetPosition();
				auto hatchScale = hatchTrans->GetScale();

				stage->AddGameObject<MiniMapHatch>(L"White", Vec2((hatchScale.x * m_mapMagnification), (hatchScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (hatchPos.x * m_mapMagnification), m_startPos.y + (hatchPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(0.35f, 1.0f, 0.1f, 1.0f), 10);//��
			}
		}
	}

	//�~�j�}�b�v�̗p�̕ǂ��쐬
	void MiniMapManager::CreateWall()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();

		////�e�X�g�p�ǂ�\��
		for (auto manhole : obj)
		{
			auto castManhole = dynamic_pointer_cast<Wall>(manhole);
			if (castManhole)//�A�C�e���^�ɃL���X�g����
			{
				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemRot = itemTrans->GetRotation();
				if (itemRot.y > 0)
				{
					itemRot.y = XMConvertToRadians(90.0f);
				}
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<Sprite>(L"White", Vec2((itemScale.x * m_mapMagnification), (itemScale.z * m_mapMagnification)),
					Vec3(m_startPos.x + (itemPos.x * m_mapMagnification), m_startPos.y + (itemPos.z * m_mapMagnification), 0.0f), Vec3(0.0f, 0.0f, itemRot.y), Col4(1.0f, 1.0f, 1.0f, 1.0f), 10);
			}
		}

	}

	//�~�j�}�b�v�p�̓G���쐬
	void MiniMapManager::CreateEnemy()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto objVec = stage->GetGameObjectVec();
		int count = 0;//���������~�j�}�b�v��Enemy�̐��𐔂���

		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto obj : objVec)
		{
			auto castEnemy = dynamic_pointer_cast<Enemy>(obj);
			if (castEnemy)//Enemy�^�ɃL���X�g����
			{
				float Lenght = 225.0f;//�~�j�}�b�v�̒��a

				auto enemyTrans = castEnemy->GetComponent<Transform>();
				auto enemyPos = enemyTrans->GetPosition();
				auto enemyScale = enemyTrans->GetScale();

				auto sprite = stage->AddGameObject<MiniMapActor>(castEnemy, L"MiniEnemy", Vec2((enemyScale.x * m_mapMagnification) * 2.0f, (enemyScale.z * m_mapMagnification) * 2.0f), m_startPos, m_mapSize, Lenght);
				sprite->AddTag(L"MiniMapEnemy");//�^�O�ǉ�
				count++;

			}
		}

		m_beforeEnemyNum = count;//���������~�j�}�b�v��Enemy�̐���n��
	}

	void MiniMapManager::CreatePlayer()
	{
		auto stage = GetStage();//�X�e�[�W�擾
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = stage->GetGameObjectVec();
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto manhole : obj)
		{
			auto castPlayer = dynamic_pointer_cast<Player>(manhole);
			if (castPlayer)//Enemy�^�ɃL���X�g����
			{
				float Lenght = 225.0f;//�~�j�}�b�v�̒��a

				auto itemTrans = manhole->GetComponent<Transform>();
				auto itemPos = itemTrans->GetPosition();
				auto itemScale = itemTrans->GetScale();

				stage->AddGameObject<MiniMapActor>(castPlayer, L"MiniPlayer", Vec2((10 * m_mapMagnification), (10 * m_mapMagnification)), m_startPos, m_mapSize, Lenght);
			}
		}

	}

	Vec3 MiniMapManager::GetStartPos()
	{
		return m_startPos;
	}

	

}
//end basecross
