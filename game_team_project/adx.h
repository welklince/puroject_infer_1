#pragma once

// Include
#include<cri_adx2le.h>
#include"release.h"

// Class
class Adx
{
private:
    static CriAtomExVoicePoolHn voice_pool_;  // �{�C�X�v�[��
    static CriAtomExAcbHn acb_;               // ACB�n���h��
    static CriAtomExPlayerHn player_;         // �v���C���[�n���h��

public:
    static bool init( const CriChar8* acfFilePatch );  // ������
    static bool load( const CriChar8* acbFilePath, CriChar8* awbFile );  // �T�E���h�̓ǂݍ���
    static void destroy(); // �j��
    static void play( CriAtomExCueId id = 0 ); // �Đ�

    // ��~
    static void stop() { criAtomExPlayer_Stop( player_ ); }
    static void stop( CriAtomExCueId id ) { criAtomExPlayer_Stop( player_ ); }
    // �X�V
    static void update() { criAtomEx_ExecuteMain(); }

    // �G���[�����֐�
    static void userErrorCallBack( const CriChar8* ErrorId, CriUint32 P1, CriUint32 P2, CriUint32* pArray );
};
