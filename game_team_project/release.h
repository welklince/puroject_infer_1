#pragma once

// �֐��`���}�N��

// �C���^�[�t�F�C�X���
#define SAFE_RELEASE(x)   {if(x){x->Release();x = NULL;}}

// ���������
#define SAFE_DELETE(x)         {delete x;x=NULL;}      // ���
#define SAFE_DELETE_ARRAY(x)   {delete[] x;x = NULL; } // �z��