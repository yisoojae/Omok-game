// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

#define X_COUNT 19
#define Y_COUNT 19
#define START_X 50
#define START_Y 50
#define INTERVAL 26
char g_dol[X_COUNT][Y_COUNT];
char g_step;
char g_log[X_COUNT * Y_COUNT][2];
int g_turn;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, HBRUSH BackG_color);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    HBRUSH BackG_color = CreateSolidBrush(RGB(244, 176, 77));

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, BackG_color);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DeleteObject(BackG_color);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, HBRUSH BackG_color)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = BackG_color;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            for (int i = 0; i < X_COUNT; i++)
            {
                MoveToEx(hdc, START_X + INTERVAL * i, START_Y, NULL);
                LineTo(hdc, START_X + INTERVAL * i, START_Y + INTERVAL * (Y_COUNT - 1));
            }
            for (int i = 0; i < Y_COUNT; i++)
            {
                MoveToEx(hdc, START_X, START_Y + INTERVAL * i, NULL);
                LineTo(hdc, START_X + INTERVAL * (X_COUNT - 1), START_Y + INTERVAL * i);
            }
            for (int i = 0; i < X_COUNT; i++)
                for (int j = 0; j < Y_COUNT; j++)
                {
                    if (g_dol[i][j] == 1)
                    {
                        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
                        Ellipse(hdc, START_X - (INTERVAL / 2) + (INTERVAL * i), START_Y - (INTERVAL / 2) + (INTERVAL * j), START_X + (INTERVAL / 2) + (INTERVAL * i), START_Y + (INTERVAL / 2) + (INTERVAL * j));
                    }
                    else if (g_dol[i][j] == 2)
                    {
                        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
                        Ellipse(hdc, START_X - (INTERVAL / 2) + (INTERVAL * i), START_Y - (INTERVAL / 2) + (INTERVAL * j), START_X + (INTERVAL / 2) + (INTERVAL * i), START_Y + (INTERVAL / 2) + (INTERVAL * j));
                    }
                }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
    {
        int mouse_X = (LOWORD(lParam) - START_X + (INTERVAL / 2)) / INTERVAL, mouse_Y = (HIWORD(lParam) - START_Y + (INTERVAL / 2)) / INTERVAL;
        if (0 <= mouse_X && mouse_X < X_COUNT && 0 <= mouse_Y && mouse_Y < Y_COUNT)
        {
            if (g_dol[mouse_X][mouse_Y] == 0)
            {
                g_dol[mouse_X][mouse_Y] = g_step + 1;
                g_log[g_turn][0] = mouse_X;
                g_log[g_turn][1] = mouse_Y;
                g_turn += 1;
                g_step = !g_step;
                InvalidateRect(hWnd, NULL, false);
            }
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        if (g_turn != 0)
        {
            g_turn -= 1;
            g_dol[g_log[g_turn][0]][g_log[g_turn][1]] = 0;
            g_step = !g_step;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
