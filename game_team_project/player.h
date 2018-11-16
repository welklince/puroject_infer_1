#pragma once

//********************************************************************
// Include
//********************************************************************
#include <d3d11.h>
#include <SimpleMath.h>
#include <Windows.h>
#include "release.h"

//********************************************************************
//  Namespace
//********************************************************************
using namespace DirectX;
using namespace SimpleMath;

//********************************************************************
// Class
//********************************************************************
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��
    Vector2 position_;                  // ���W
    Vector2 offset_;                    // �␳�l

    // �A�j���[�V�����֌W
    int  animation_no_;      // �A�j���[�V�����ԍ�
    int  animation_pattern_; // �A�j���[�V�����p�^�[��
    int  animation_counter_; // �A�j���[�V�����J�E���^
    void animation();        // �A�j���[�V��������
    int  speed_;             // �ړ����x

    // �L�[�{�[�h�֌W
    bool pad_flag_;       // �p�b�h�̃t���O
    int  pad_no_;         // �p�b�h�̓��͔ԍ�

public:
    Player();  //�R���g���X�^
    ~Player(); //�f�X�g���N�^

    //������
    bool init( const wchar_t* FileName ); // ������
    void update( int* pad_ );                        // �X�V
    void draw( );                          // �`��
    void destroy();                       // �j��
};