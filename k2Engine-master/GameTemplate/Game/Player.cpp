#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"
#include "Game.h"
#include "GameCamera.h"
#include "sound/SoundSource.h" 

namespace
{
	const Vector3 corre1 = { 0.0f,100.0f,0.0f };//??u?C???{?????????
	const Vector3 corre2 = { 30.0f,130.0f,10.0f };//??u?C???e???????u
}

Player::Player()
{

}

Player::~Player()
{
	DeleteGO(arrow);
	DeleteGO(ArrowSE);
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

	m_modelRender.Init("Assets/modelData/Player_S.tkm", m_animationClips,
		enArrowClip_Num);
	m_charaCon.Init(25.0f, 75.0f, m_position);
	m_spriteRender_r.Init("Assets/sprite/HPRed.dds", 512.0f, 512.0f);
	m_spriteRender_r.SetPivot({ 0.0f,0.5f });
	m_spriteRender.Init("Assets/sprite/HPBarGreen.dds", 512.0f, 512.0f);
	m_spriteRender.SetPivot({ 0.0f,0.5f });
	m_spriteRender.SetPosition({ 600.0f,-420.0f,0.0f });
	m_spriteRender.Update();
	m_spriteRender_r.SetPosition({ 600.0f,-420.0f,0.0f });
	m_spriteRender_r.Update();

	HP = 100;
	game = FindGO<Game>("game");
	gameCamera = FindGO<GameCamera>("gameCamera");

	m_skyCube = NewGO<SkyCube>(0, "skycube");
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
	m_modelRender.Update();
	m_skyCube->SetPosition(m_position);
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	//通常の移動モーション
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
// 

	//ここから3ラインの移動式
	game->m_pointPosition = game->path00_pointList[m_point];
	game->m_nextPosition = game->path00_pointList[m_point + 1];
	game->m_pointPosition1 = game->path01_pointList[m_point];
	game->m_nextPosition1 = game->path01_pointList[m_point + 1];
	game->m_pointPosition2 = game->path02_pointList[m_point];
	game->m_nextPosition2 = game->path02_pointList[m_point + 1];

	//川の3ライン間を移動するための計算
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
		//����̑D�̃��[�u�|�C���g����i������ƃG���[���o��j
		//if (m_point == 13)
		//{
		//	m_point = 0;
		//}
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
	////�����܂�3���C���̈ړ���

	//if (m_charaCon.IsOnGround())
	//{
	//	m_moveSpeed.y = 0.0f;
	//}
	//else
	//{
	//	m_moveSpeed.y -= 10.0f;
	//}
	
	

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
			m_arrowState = 3;
			HP -= 20;
		}
	}

	/*collisions == g_collisionObjectManager->FindCollisionObjects("g_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_charaCon))
		{
			HP -= 20;
		}
	}

	collisions == g_collisionObjectManager->FindCollisionObjects("s_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_charaCon))
		{
			HP -= 8;
		}
	}*/
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
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
			ArrowSE = NewGO<SoundSource>(5);
			ArrowSE->Init(5);
			ArrowSE->Play(false);

			m_modelRender.PlayAnimation(enArrowClip_Draw);
			m_arrowLag++;
			if (m_arrowLag >=25)
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
			arrow->m_position = (m_position + corre2);
			arrow->m_1stPosition = arrow->m_position;
			arrow->m_rotation = m_rotation;

			arrow->SetEnArrow(Arrow::enArrow_Player);
			m_arrowState = 5;
		}
		
		break;
	case 3:
		m_modelRender.PlayAnimation(enArrowClip_Damage);
		m_damageLag++;
		if (m_damageLag >= 10)
		{
			m_damageLag = 0;
			m_arrowState = 0;
		}
		break;
	case 4:
		m_modelRender.PlayAnimation(enArrowClip_Dead);
		m_arrowLag++;

		break;
	case 5:
		m_arrowState = 0;
		break;
	case 6:
		//ゲームクリアステート
		m_modelRender.PlayAnimation(enArrowClip_Clear);
		break;
	}
}