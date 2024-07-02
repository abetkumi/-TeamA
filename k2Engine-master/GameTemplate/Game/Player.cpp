#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"
#include "Game.h"
#include "GameCamera.h"
#include "sound/SoundSource.h" 

namespace
{
	const Vector3 corre1 = { 0.0f,100.0f,0.0f };//??u?C???{?????????
	const Vector3 corre2 = { 0.0f,130.0f,10.0f };//??u?C???e???????u
	const float firstPosition = 60.0f;
}

Player::Player()
{

}

Player::~Player()
{
	DeleteGO(m_skyCube);
}


bool Player::Start()
{
	m_animationClips[enArrowClip_Idle].Load("Assets/animData/player_idle.tka");
	m_animationClips[enArrowClip_Idle].SetLoopFlag(true);
	m_animationClips[enArrowClip_Draw].Load("Assets/animData/player_reload.tka");
	m_animationClips[enArrowClip_Draw].SetLoopFlag(false);
	m_animationClips[enArrowClip_Aim].Load("Assets/animData/player_draw.tka");
	m_animationClips[enArrowClip_Aim].SetLoopFlag(false);
	m_animationClips[enArrowClip_Damage].Load("Assets/animData/player_damage.tka");
	m_animationClips[enArrowClip_Damage].SetLoopFlag(false);
	m_animationClips[enArrowClip_Dead].Load("Assets/animData/player_death.tka");
	m_animationClips[enArrowClip_Dead].SetLoopFlag(false);
	m_animationClips[enArrowClip_Clear].Load("Assets/animData/player_victory.tka");
	m_animationClips[enArrowClip_Clear].SetLoopFlag(false);

	g_soundEngine->ResistWaveFileBank(5, "Assets/BGM・SE/Arrow.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/BGM・SE/player_shot.wav");
	g_soundEngine->ResistWaveFileBank(17, "Assets/BGM・SE/player_damagevoice.wav");
	

	m_modelRender.Init("Assets/modelData/Player_S.tkm", m_animationClips,
		enArrowClip_Num);
	m_charaCon.Init(25.0f, 75.0f, m_position);
	
	//HPバーの表示
	m_spriteRender_HP.Init("Assets/sprite/HPBar.dds", 512.0f, 512.0f);
	m_spriteRender_HP.SetPivot({ 0.0f,0.5f });
	m_spriteRender_r.Init("Assets/sprite/HPRed.dds", 512.0f, 512.0f);
	m_spriteRender_r.SetPivot({ 0.0f,0.5f });
	m_spriteRender.Init("Assets/sprite/HPBarGreen.dds", 512.0f, 512.0f);
	m_spriteRender.SetPivot({ 0.0f,0.5f });
	m_spriteRender.SetPosition({ 600.0f,-420.0f,0.0f });
	m_spriteRender.Update();
	m_spriteRender_r.SetPosition({ 600.0f,-420.0f,0.0f });
	m_spriteRender_r.Update();
	m_spriteRender_HP.SetPosition({ 597.0f,-420.0f,0.0f });
	m_spriteRender_HP.Update();

	HP = 100;
	game = FindGO<Game>("game");
	gameCamera = FindGO<GameCamera>("gameCamera");

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetScale({ 8000.0f,8000.0f,8000.0f });
	m_skyCube->SetPosition(m_position);
	m_skyCube->SetType(enSkyCubeType_Day);
	m_skyCube->SetLuminance(0.5f);

	return true;

}

void Player::Update()
{
	Move();
	Rotation();
	Collision();
	HPGauge();
	ArrowAnimation();
	Score();
	m_modelRender.Update();
	m_skyCube->SetPosition(m_position);
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
//	//通常の移動モーション
//	Vector3 stickL;
//	stickL.x = g_pad[0]->GetLStickXF();
//	stickL.y = g_pad[0]->GetLStickYF();
//
//	Vector3 forward = g_camera3D->GetForward();
//	Vector3 right = g_camera3D->GetRight();
//
//	forward.y = 0.0f;
//	right.y = 0.0f;
//
//	right *= stickL.x * 120.0f;
//	forward *= stickL.y * 120.0f;
//
//	m_moveSpeed += right + forward;
//
//	//ダッシュとジャンプ
//if (g_pad[0]->IsPress(enButtonA))
//	{
//		m_moveSpeed.y = 300.0f;
//	}
//	if (g_pad[0]->IsPress(enButtonX))
//	{
//		m_moveSpeed = (right + forward) * 7.5;
//	}
//// 

	//ここから3ラインの移動式
	game->m_pointPosition = game->path00_pointList[m_point];
	game->m_nextPosition = game->path00_pointList[m_point + 1];
	game->m_pointPosition1 = game->path01_pointList[m_point];
	game->m_nextPosition1 = game->path01_pointList[m_point + 1];
	game->m_pointPosition2 = game->path02_pointList[m_point];
	game->m_nextPosition2 = game->path02_pointList[m_point + 1];

	//川の3ライン間を移動するための計算
	 if (game->m_spriteStatus == 7)
	{

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();

	switch (m_moveState) {
	case MoveState_Normal:
		// ���E�ɓ�������
		//�E�X�e�B�b�N�őD�̈ړ�
		if (stickL.x <= -0.8f&&m_lag == 0)
		{
			m_moveState = MoveState_Left;
		}
		else if (stickL.x >= 0.8f && m_lag == 0)
		{
			m_moveState = MoveState_Right;
		}

		break;
	case MoveState_Left:

		m_moveFlag--;
		m_lag++;
		m_moveState = MoveState_Normal;
		break;
	case MoveState_Right:

		m_moveFlag++;
		m_lag++;
		m_moveState = MoveState_Normal;
		break;
	}
	
	if (m_lag >= 1)
	{
		m_lag++;
		if (m_lag == 10)
		{

			m_lag = 0;
		}
	}


	//��̃��C���̏�������̐ݒ�
	if (m_moveFlag < 0)
	{
		m_moveFlag = 0;
	}
	if (m_moveFlag > 2)
	{
		m_moveFlag = 2;
	}

	if (m_moveFlag == 0)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPosition;
		Vector3 m_moveLineV1 = game->m_nextPosition - game->m_pointPosition;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;
		//���E�Ɉړ����鋗��
		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;
		diff = game->m_pointPosition - m_position;

	}

	if (m_moveFlag == 1)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPosition1;
		Vector3 m_moveLineV1 = game->m_nextPosition1 - game->m_pointPosition1;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;
		//���E�Ɉړ����鋗��
		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;

		diff = game->m_pointPosition1 - m_position;
	}

	if (m_moveFlag == 2)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPosition2;
		Vector3 m_moveLineV1 = game->m_nextPosition2 - game->m_pointPosition2;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;
		//���E�Ɉړ����鋗��
		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;

		diff = game->m_pointPosition2 - m_position;

	}

	//���̈ړ��|�C���g�֌�������
	float disToPlayer = diff.Length();
	if (disToPlayer <= 200.0f)
	{
		m_point++;
	}


	diff.Normalize();

	static bool hoge = false;
	
	if (hoge) {
		//�ړ��X�s�[�h
		m_moveSpeed = diff * 0.0f;
	}
	else {
		//�ړ��X�s�[�h
		m_moveSpeed = diff * 300.0f;
	}
	 }
	//�����܂�3���C���̈ړ���

	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}
	else
	{
		m_moveSpeed.y -= 10.0f;
	}
	
	

	//�����Q�[���I�[�o�[�R�}���h
	if (g_pad[0]->IsPress(enButtonY))
	{
		m_arrowState = 3;
		HP -= 10;
	}

	if (m_arrowState == 4 || m_arrowState == 6)
	{
		m_position = m_position;
	}
	else
	{
		m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 20.0f);//��܂��Ȉړ����x
	}
	
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	m_rotation.SetRotationYFromDirectionXZ(gameCamera->m_toCameraPos);
	m_modelRender.SetRotation(m_rotation);

	m_cNPos = gameCamera->m_toCameraPos;
	m_cNPos.Normalize();
	m_rotation.AddRotationX(-(m_cNPos.y + 0.04f));
}

void Player::Collision()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("e_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_charaCon))
		{
			se = NewGO<SoundSource>(17);
			se->Init(17);
			se->Play(false);

			m_arrowState = 3;
			HP -= 20;
		}
	}

	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("bat_enemy_col");
	for (auto collision : collisions2) {
		if (collision->IsHit(m_charaCon))
		{
			se = NewGO<SoundSource>(17);
			se->Init(17);
			se->Play(false);

			m_arrowState = 3;
			HP -= 1;
		}
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_fontRender.Draw(rc);
	m_spriteRender_HP.Draw(rc);
	m_spriteRender_r.Draw(rc);
	m_spriteRender.Draw(rc);
	m_skyCube->Render(rc);
}

void Player::HPGauge()
{
	if (HP > 0)
	{
		m_HPGauge.x = HP / 100;
		if (m_HPGauge.x != m_HPBar_r.x)
		{
			m_HPBar_r.x -= (m_HPBar_r.x - m_HPGauge.x) / 10.0f;
		}
		if (m_HPGauge.x >= m_HPBar_r.x)
		{
			m_HPBar_r.x = m_HPGauge.x;
		}
	}
	if (HP <= 0)
	{
		m_HPGauge.x = 0.0f;
		m_HPBar_r.x = 0.0f;
	}

	m_spriteRender_r.SetScale(m_HPBar_r);
	m_spriteRender_r.Update();

	m_spriteRender.SetScale(m_HPGauge);
	m_spriteRender.Update();
}

void Player::ArrowAnimation()
{
	switch (m_arrowState)
	{
	case 0:
		//待機モーション
		m_modelRender.PlayAnimation(enArrowClip_Idle);
		if (g_pad[0]->IsPress(enButtonRB1))
		{
			m_arrowState++;
		}
		
		break;
	case 1:
		//弓を構える
		if (g_pad[0]->IsPress(enButtonRB1))
		{
			se2 = NewGO<SoundSource>(5);
			se2->Init(5);
			se2->Play(false);

			m_modelRender.PlayAnimation(enArrowClip_Draw);
			m_arrowLag++;
			if (m_arrowLag >= 25)
			{
				m_arrowState++;
				m_arrowLag = 0;
			}
		}
		else if (m_arrowLag < 25 && !g_pad[0]->IsPress(enButtonRB1))
		{
			m_arrowLag = 0;
			m_arrowState = 0;
		}
		break;
	case 2:
		m_modelRender.PlayAnimation(enArrowClip_Aim);
		//弓発射
		if (!g_pad[0]->IsPress(enButtonRB1))
		{
			arrow = NewGO<Arrow>(0);

			se3 = NewGO<SoundSource>(9);
			se3->Init(9);
			se3->Play(false);

			Vector3 arrowPos = corre2;
			m_rotation.Apply(arrowPos);

			arrow->m_position = (m_position + arrowPos);
			arrow->m_1stPosition = arrow->m_position;
			arrow->m_rotation = m_rotation;

			if (SimilarAng >= 0.98) {
				arrow->eHoming = true;
				arrow->lock_ePos = lock_ePos;
			}

			arrow->SetEnArrow(Arrow::enArrow_Player);
			m_arrowState = 5;

			SimilarAng = 0.0f;
		}
		
		break;
	case 3:
		//ダメージを受けたステート
		m_modelRender.PlayAnimation(enArrowClip_Damage);
		m_damageLag++;
		if (m_damageLag >= 10)
		{
			m_damageLag = 0;
			m_arrowState = 0;
		}
		break;
	case 4:
		//ゲームオーバーステート
		m_modelRender.PlayAnimation(enArrowClip_Dead);
		m_arrowLag++;

		break;
	case 5:
		//初期ステートに戻る
		m_arrowState = 0;
		break;
	case 6:
		//ゲームクリアステート
		m_modelRender.PlayAnimation(enArrowClip_Clear);
		break;
	}
}

void Player::Score()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%dpoint", int(m_score));

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(500.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}
