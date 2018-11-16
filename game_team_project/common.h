#pragma once

#include<CommonStates.h>

// ���O���
using namespace DirectX;

// �N���X
class Common
{
private:
    static CommonStates* state_; // CommonState�N���X�|�C���^
public:
    static bool init();                                // ������
    static void destroy() { delete state_; }           // �j��
    static CommonStates* getState() { return state_; } // CommonStates�|�C���^��Ԃ�
};