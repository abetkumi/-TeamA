#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"
#include "Game.h"
#include "GameCamera.h"

Player::Player()
{
	

}

Player::~Player()
{

}


bool Player::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_charaCon.Init(25.0f, 75.0f, m_position);

	HP = 100;
	game = FindGO<Game>("game");
	gameCamera = FindGO<GameCamera>("gameCamera");
}
void Player::Update()
{
	Move();
	Rotation();

	m_modelRender.Update();

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		arrow = NewGO<Arrow>(0, "p_arrow");
		arrow->m_position = (m_position);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

	}
}

void Player::Move()
{
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;

	////�ʏ�̈ړ����[�V����
	//Vector3 stickL;
	//stickL.x = g_pad[0]->GetLStickXF();
	//stickL.y = g_pad[0]->GetLStickYF();

	//Vector3 forward = g_camera3D->GetForward();
	//Vector3 right = g_camera3D->GetRight();

	//forward.y = 0.0f;
	//right.y = 0.0f;

	//right *= stickL.x * 120.0f;
	//forward *= stickL.y * 120.0f;

	//m_moveSpeed += right + forward;

	//�_�b�V���ƃW�����v
//if (g_pad[0]->IsPress(enButtonA))
//	{
//		m_moveSpeed.y = 300.0f;
//	}
//	if (g_pad[0]->IsPress(enButtonX))
//	{
//		m_moveSpeed = (right + forward) * 7.5;
//	}

	//��������3���C���̈ړ���
	game->m_pointPosition = game->path00_pointList[m_point];
	game->m_nextPosition = game->path00_pointList[m_point + 1];
	game->m_pointPosition1 = game->path01_pointList[m_point];
	game->m_nextPosition1 = game->path01_pointList[m_point + 1];
	game->m_pointPosition2 = game->path02_pointList[m_point];
	game->m_nextPosition2 = game->path02_pointList[m_point + 1];
	////���3���C���Ԃ��ړ����邽�߂̌v�Z
	/*Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();*/

	////�E�X�e�B�b�N�őD�̈ړ�
	//if (stickL.x <= -0.5f&&!m_isHit)
	//{
	//	m_isHit = true;
	//	m_moveState++;
	//}
	//if (stickL.x >= 0.5f)
	//{
	//	m_isHit = true;
	//	m_moveState--;
	//}
	//m_isHit = false;

	//LB,RB�őD�̈ړ��i���j
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_moveState--;
	}
	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		m_moveState++;
	}

	//��̃��C���̏�������̐ݒ�
	if (m_moveState < 0)
	{
		m_moveState = 0;
	}
	if (m_moveState > 2)
	{
		m_moveState = 2;
	}

	if (m_moveState == 0)
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

		m_moveSpeed.x += m_moveLine.x;
		diff = game->m_pointPosition - m_position;

	}
	if (m_moveState == 1)
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

		m_moveSpeed.x += m_moveLine.x;

		diff = game->m_pointPosition1 - m_position;
	}
	if (m_moveState == 2)
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

		m_moveSpeed.x += m_moveLine.x;

		diff = game->m_pointPosition2 - m_position;
	}

	//���̈ړ��|�C���g�֌�������
	float disToPlayer = diff.Length();
	if (disToPlayer <= 60.0f)
	{
		m_point++;
	}
	diff.Normalize();

	//�ړ��X�s�[�h
	m_moveSpeed = diff * 100.0f;
	//�����܂�3���C���̈ړ���

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
		HP -= 100;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 20.0f);//��܂��Ȉړ����x
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	m_rotation.SetRotationYFromDirectionXZ(gameCamera->target);
	m_modelRender.SetRotation(m_rotation);
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}