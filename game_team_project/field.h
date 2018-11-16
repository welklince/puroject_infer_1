#pragma once

#include"direct3d.h"
#include"sprite.h"
#include"release.h"

// �\����
struct Parts
{
    Vector2 position;  // ���W
    RECT trim;         // �`��͈�
    int id;            // �p�[�c�ԍ�

    // �R���X�g���N�^
    Parts()
    {
        position = Vector2( 0.0F, 0.0F );
        trim = RECT();
        id = 0;
    }
};

// �N���X
class Field
{
private:
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��
    int width_, height_;                // �}�b�v�����c��
    Parts* parts_;                      // �p�[�c�\���̃|�C���^

public:
    Field();       // �R���X�g���N�^
    ~Field();      // �f�X�g���N�^
    bool init();   // ������
    void update( int pad ); // �X�V
    void draw();   // �`��
    void destroy();// �j�� 
};