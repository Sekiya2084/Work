#include "main.h"
#include "manager.h"
#include <thread>


#include "imgui_impl_win32.h"
#include "imgui.h"


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ゲーム";
int g_ScreenWidth = 1280;
int g_ScreenHeight = 720;



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)g_ScreenWidth, (LONG)g_ScreenHeight };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);


	Manager::Init();



	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	//メッセージで動作に変更が効くためここでメニューを作成できるかもしれない
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Manager::Update();
				Manager::Draw();

			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	CoUninitialize();

	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void SetScreenSize(int width,int height) {
	g_ScreenWidth = width;
	g_ScreenHeight = height;
}


XMFLOAT2 MonitorInfo() {
	HMONITOR hMonitor;
	MONITORINFOEX  MonitorInfoEx;
	POINT pt = { 100, 100 };

	//ptで指定した部分のモニターのハンドルを取得する
	hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);

	//モニター情報を取得する
	MonitorInfoEx.cbSize = sizeof(MonitorInfoEx);
	GetMonitorInfo(hMonitor, &MonitorInfoEx);

	//ImGui::Begin("MonitorInfo");
	//{
	//	//  テキストの表示
	//	ImGui::Text("Monitor.buttom: %d", MonitorInfoEx.rcMonitor.bottom);
	//	ImGui::Text("Monitorleft: %d", MonitorInfoEx.rcMonitor.left);
	//	ImGui::Text("Monitorright: %d", MonitorInfoEx.rcMonitor.right);
	//	ImGui::Text("Monitortop: %d", MonitorInfoEx.rcWork.top);
	//	ImGui::Text("Monitortop: %d", (int)MonitorInfoEx.rcMonitor.bottom / 2);
	//	ImGui::Text("Monitortop: %d", (int)MonitorInfoEx.rcMonitor.right/2);

	//}
	//ImGui::End();

	return XMFLOAT2((int)MonitorInfoEx.rcMonitor.bottom / 2, (int)MonitorInfoEx.rcMonitor.right/2);
}