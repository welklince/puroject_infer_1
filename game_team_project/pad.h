#pragma once

#include<GamePad.h>

using namespace DirectX;

class Pad
{
private:
    static GamePad pad_;            // �Q�[���p�b�h�N���X
    static GamePad::State state_;   // ���͊i�[�\����
public:
    static void update();   // �X�V����

    // ���͍\���̂�Ԃ�
    static GamePad::State &getState() { return state_; }

    static void setVibration( const float Left, const float Right )
    {
        pad_.SetVibration( 0, Left, Right );
    }
};