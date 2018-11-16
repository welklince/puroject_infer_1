#include<Windows.h>
#include<d3d11.h>
#include<cstdio>
#include<ctime>
#include<Keyboard.h>

#include"common.h"
#include"game.h"
#include"pad.h"
#include"direct3d.h"
#include"sprite.h"

//// �񋓑�
//enum
//{
//    kTitleinit,   // �^�C�g����ʏ�����
//    kTitleUpdate, // �^�C�g����ʍX�V(�`��)
//    kGameInit,    // �Q�[����ʏ�����
//    kGameUpdate   // �Q�[����ʍX�V(�`��)
//};

//�v���g�^�C�v�錾
LRESULT CALLBACK WinProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow )
{
    srand( time( NULL ) );

    //�E�B���h�E�N���X�̍쐬
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );    //�\���̃T�C�Y
    wnd.style = CS_HREDRAW | CS_VREDRAW; //�X�^�C��
    wnd.hInstance = hInstance;               //�A�v���P�[�V�����C���X�g�[��
    wnd.lpszClassName = "ClassName";             //�N���X��
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW ); //�J�[�\���`��
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                 //�E�B���h�E�v���V�[�W���ւ̊֐��|�C���^

    //�o�^
    if( !RegisterClassEx( &wnd ) )
    {
        //�G���[
        return 0;
    }

    //�E�B���h�E�T�C�Y������
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    //�E�B���h�E�̍쐬
    const HWND hwnd = CreateWindowEx(
        ex_style,               //�g���E�B���h�E�X�^�C��
        "ClassName",            //�N���X��
        "Title",                //�E�B���h�E�X�^�C��
        style,                  //�E�B���h�E�X�^�C��
        CW_USEDEFAULT,          //�\�����WX
        CW_USEDEFAULT,          //�\�����WY
        rect.right - rect.left, //�E�B���h�E����
        rect.bottom - rect.top, //�E�B���h�E�c��
        NULL,                   //�e�E�B���h�E�ւ̃n���h��
        NULL,                   //���j���[�n���h��
        hInstance,              //�A�v���P�[�V�����C���X�^���X
        NULL                    //�E�B���h�E�쐬�f�[�^
    );

    //NULL�`�F�b�N
    if( hwnd == NULL )
    {
        //�G���[
        return 0;
    }

    //Direct3D������
    if( !Direct3D::init( hwnd ) )
    {
        // �G���[ 
        return 0;
    }

    //COM���C�u�����̏�����
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        //�G���[
        return 0;
    }

    // sprite�N���X������
    if( !Sprite::init() )
    {
        // �G���[
        return 0;
    }

    // Common�N���X�̍쐬
    if( !Common::init() )
    {
        // �G���[
        return 0;
    }

    // �V�[���N���X�ϐ�
    Game game;

    game.init();

    //�E�B���h�E�̕\��
    ShowWindow( hwnd, SW_SHOWNORMAL );

    //���C�����[�v
    MSG msg = { NULL };

    // ���Ԍv��
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    //// ���݂̍�Ɣԍ�
    //int work_no = kTitleinit;

    while( msg.message != WM_QUIT )
    {
        //���b�Z�[�W����
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // �t���[�����[�g����
            t1 = timeGetTime();   // ���݂̎���
            dt = (t1 - t2) + t3;  //�O��̍X�V����̍������v�Z

            // ��16�~���b�o�߂��Ă����珈�����s��
            if( dt > 16 )
            {
                t2 = t1;       // ���̎��Ԃ�O��̎��Ԃɂ���
                t3 = dt % 16;  // �덷�����z��

                //// �X�V����
                // �R���g���[���N���X�̍X�V 
                Pad::update();

                game.update();


                //// �`�揈��
                // ��ʃN���A
                Direct3D::clear();

                //�X�v���C�g�`��J�n
                Sprite::begin();

                game.draw();

                //�X�v���C�g�̕`��I��
                Sprite::end();

                //��ʍX�V
                Direct3D::present();
            }
        }
    }

    //COM���C�u�����̉��
    CoUninitialize();

    // �C���^�[�t�F�C�X�̉��
    game.destroy();
    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();

    return 0;
}

LRESULT CALLBACK WinProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hwnd, &ps );
        EndPaint( hwnd, &ps );
        break;
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        switch( wParam )
        {
        case VK_ESCAPE:
            //ESC�������ꂽ�烋�[�v���I������
            PostMessage( hwnd, WM_CLOSE, 0, 0 );
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hwnd, Msg, wParam, lParam );
}
