//********************************************************************
// Include
//********************************************************************
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "pad.h"

//********************************************************************
// Enum
//********************************************************************
enum
{
    pDown,
    pUp,     // �����
    pRight,  // �E����
    pLeft,   // ������
};

//********************************************************************
// �萔
//********************************************************************
const int kPlayerSizeX = 64; // �v���C���[����
const int kPlayerSizeY = 96; // �v���C���[�c��
const int kAnimationSpeed = 8;  // �A�j���[�V�������x
const int kAnimationSpeed2 = 4;  // �A�j���[�V�������x (���s��)

//********************************************************************
// �R���X�g���N�^
//********************************************************************
Player::Player()
{
    // �����o�ϐ��̏�����
    position_ = Vector2( 576.0F, 288.0F );
    speed_ = 4;

    // �A�j���[�V�����֌W
    animation_no_ = 0;
    animation_counter_ = 0;
    animation_pattern_ = pUp,  // ������

    // �L�[�{�[�h�֌W
    pad_flag_ = false;

    // �e�N�X�`���֌W
    texture_ = NULL;
}

//********************************************************************
// �f�X�g���N�^
//********************************************************************
Player::~Player()
{
}

//********************************************************************
// ������
//********************************************************************
bool Player::init( const wchar_t* FileName )
{
    // �e�N�X�`���̓ǂݍ���
    texture_ = Texture::load( FileName );

    // NULL�`�F�b�N
    if( texture_ == NULL )
    {
        // �G���[
        return false;
    }

    return true;
}

//********************************************************************
// �X�V����
//********************************************************************
void Player::update( int* pad_ )
{
    // ���Ԃ̐錾

    // �R���g���[���̓��͂̎擾 
    const GamePad::State pad = Pad::getState();

    // ���͉\��
    if( pad_flag_ == false )
    {
        // �R���g���[�������͂��ꂽ��
        // ��
        if( pad.dpad.left )
        {
            pad_flag_ = true;
            pad_no_ = pLeft;
            *pad_ = pLeft;
        }
        // ��
        else if( pad.dpad.right )
        {
            pad_flag_ = true;
            pad_no_ = pRight;
            *pad_ = pRight;
        }
        // ��
        else if( pad.dpad.up )
        {
            pad_flag_ = true;
            pad_no_ = pUp;
            *pad_ = pUp;
        }
        else
        {
            animation_no_ = 0;
        }
    }
    // ���s��and���s�� 
    else
    {
        if( pad_no_ == pLeft )
        {
            animation_pattern_ = pLeft;
            position_.x += speed_;
        }
        else if( pad_no_ == pRight )
        {
            animation_pattern_ = pRight;
            position_.x -= speed_;
        }
        else if( pad_no_ == pUp )
        {
            animation_pattern_ = pUp;
            position_.y += speed_;
        }
    }

    // 1�}�X�i�񂾂�t���O�������� 
    if( static_cast<int>(position_.x) % 64 == 0 && static_cast<int>(position_.y) % 64 == 0 )
    {
        pad_flag_ = false;
    }

    // �A�j���[�V�����X�V
    animation();

}

//********************************************************************
//�`��
//********************************************************************
void Player::draw( )
{
    // �`��͈͂̐ݒ�
    RECT rect;
    rect.top = animation_pattern_ * kPlayerSizeY;
    rect.left = animation_no_ * kPlayerSizeX;
    rect.right = rect.left + kPlayerSizeX;
    rect.bottom = rect.top + kPlayerSizeY;

    // �`��
    Sprite::draw( texture_, position_, &rect );
}



//********************************************************************
// �A�j���[�V��������
//********************************************************************
void Player::animation()
{
    // ���s����

        // �J�E���g�A�b�v
    if( ++animation_counter_ >= kAnimationSpeed )
    {
        // �I�[�܂Ői�񂾂�߂�
        (animation_no_ == 3) ? animation_no_ = 0 : animation_no_++;

        // �J�E���^�[������
        animation_counter_ = 0;
    }
}

//********************************************************************
// �j��
//********************************************************************
void Player::destroy()
{
    // �e�N�X�`���̉��
    SAFE_RELEASE( texture_ );
}