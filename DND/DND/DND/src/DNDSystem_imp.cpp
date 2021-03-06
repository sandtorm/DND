#include "DNDSystem_imp.h"
#include "DNDError.h"
#include "DNDGame.h"
#include "DNDValue.h"

namespace DND
{

	void System_imp::_create_window()
	{
		dnd_assert(!_hWnd ,ERROR_00001);
		//窗口类
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = Game::_window_proc; //消息处理函数
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hInstance;//实例句柄
		wc.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景白色
		wc.lpszMenuName = 0;
		wc.lpszClassName = L"DNDWindowClass";//窗口类名

		dnd_assert(RegisterClass(&wc), ERROR_00002);
		//创建窗口

		_hWnd = CreateWindow(
			L"DNDWindowClass",
			L"DNDFirstWindow",
			WS_POPUP,
			-100,
			-100,
			100,
			100,
			0 /*parent hwnd*/, 0 /* menu */, _hInstance, 0 /*extra*/);

		dnd_assert(_hWnd, ERROR_00003);

		ShowWindow(_hWnd, SW_HIDE);
		//UpdateWindow(_hWnd);
		//SetFocus(_hWnd);

	}

	System_imp::System_imp()
	{
		_windowTitle = DEFAULT_WINDOW_TITLE;
		_windowStyle = DEFAULT_WINDOW_STYLE;
		_windowSize = DEFAULT_WINDOW_SIZE;
		SetWindowCenter();

		_hWnd = 0;
		_hInstance = GetModuleHandle(0);

	}

	void System_imp::SetWindowTitle(const String& title)
	{
		_windowTitle = title;
		SetWindowText(_hWnd, title.GetWcs());
	}

	void System_imp::SetWindowCenter()
	{
		Size s = GetDesktopSize();
		_windowPoint.x = (s.w - _windowSize.w) / 2;
		_windowPoint.y = (s.h - _windowSize.h) / 2;
	}

	void System_imp::SetWindowStyle(DWORD style)
	{
		_windowStyle = style;
	}

	void System_imp::SetWindowSize(Size size)
	{
		_windowSize = size;
	}

	void System_imp::ApplyWindow()
	{
		RECT rect = {0, 0, _windowSize.w, _windowSize.h};

		AdjustWindowRect(&rect, _windowStyle, false);

		SetWindowLong(_hWnd, GWL_STYLE, _windowStyle);

		MoveWindow(_hWnd,
			_windowPoint.x,
			_windowPoint.y,
			rect.right - rect.left,
			rect.bottom - rect.top,
			true);

		SetWindowText(_hWnd, _windowTitle.GetWcs());

		ShowWindow(_hWnd, SW_SHOW);
		/*UpdateWindow(_hWnd);
		SetFocus(_hWnd);*/
	}

	void System_imp::SetWindowPoint(Point point)
	{
		_windowPoint = point;
	}

	Size System_imp::GetDesktopSize()
	{
		return Size(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));;
	}

	



}

