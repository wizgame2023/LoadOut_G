/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Enemy :public GameObject
	{
	private:
		enum STATETYPE
		{
			m_platol,
			m_tracking,
			m_attack,
		};

		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
	public:
		Enemy(const shared_ptr<Stage>& StaegePtrconst,
			Vec3& pos,const Vec3& rot,const Vec3& scale);
		//~Enemy();

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;


	private:
		class StateBase
		{
		public:
			virtual void OnStart(Enemy owner)
			{
			}

			virtual void OnUpdate(Enemy owner)
			{
			}

			virtual void OnExit(Enemy owner)
			{ 
			}
		private:
			void GetState(STATETYPE state);
			void SetState(STATETYPE state);
		};

		class Patrol :StateBase
		{
		public:
			void OnStart(Enemy owner) override
			{
			}
			void OnUpdate(Enemy owner) override
			{
			}
			void OnExit(Enemy owner) override
			{
			}
		};
		
		Patrol m_Patrol;
	};

}
//end basecross
