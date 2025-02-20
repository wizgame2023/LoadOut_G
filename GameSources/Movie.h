/*!
@file Character.h
@brief ムービー関係の親クラス
*/

#pragma once
#include "stdafx.h"
#include "MyCamera.h"
#include "StageCollisionManager.h"
#include "StageManager.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:
		vector<weak_ptr<Actor>> m_actorVec;//動くオブジェクトを入れる配列
		vector<weak_ptr<Spanner>> m_batteryVec;//バッテリーを入れる配列
		vector<weak_ptr<Manhole>> m_manholeVec;//マンホールを入れる配列
		vector<weak_ptr<Sprite>> m_spriteVec;//スプライトをを入れる配列
	protected:
		shared_ptr<MyCamera> m_stageCamera;//ステージ用のカメラ
		shared_ptr<Camera> m_movieCamera;//ムービー用のかめら
		shared_ptr<StageCollisionManager> m_collsionManager;//コリジョンマネージャー
		shared_ptr<StageManager> m_stageManager;//ステージマネージャー
		int m_count;
	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		//ムービー用のカメラに変更させる
		virtual void CameraChange();

		//カメラを目的地に向けて移動させる
		virtual Vec3 CameraMove(float speed,Vec3 pos,Vec3 tagetPos);
	};

}
//end basecross
