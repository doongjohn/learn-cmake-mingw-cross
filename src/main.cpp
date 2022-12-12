#include <iostream>
#include <windows.h>

#include <spdlog/spdlog.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
  spdlog::info(fmt::format("I'd rather be {1} than {0}.", "right", "happy"));

  HWND hWnd;
  MSG msg;
  WNDCLASS wndClass;
  g_hInst = hInstance;

  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hInstance = hInstance;
  wndClass.lpfnWndProc = WndProc;
  wndClass.lpszClassName = lpszClass;
  wndClass.lpszMenuName = NULL;
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  RegisterClass(&wndClass);

  hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  switch (iMessage) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
