#include"common.h"
#include"direct3d.h"


// ���̂̐錾
CommonStates*Common::state_;

// ������
bool Common::init()
{
    // SpriteBatch�N���X�̃��������m��
    state_ = new CommonStates( Direct3D::getDevice() );

    // �������m�ۃ`�F�b�N
    if( !state_ )
    {
        // �G���[
        return false;
    }

    return true;
}