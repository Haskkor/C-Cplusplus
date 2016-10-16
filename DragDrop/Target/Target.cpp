#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <commctrl.h>
#include <ole2.h>   
#include <shlobj.h>
#include "DropTarget.h"

#pragma comment(lib, "comctl32.lib")

HINSTANCE g_hInst;
HWND hListView;

__declspec(naked) void __fastcall GetSystemImageList(HIMAGELIST *phLarge, HIMAGELIST *phSmall)
{
  __asm
  {
    push   edx
    push   ecx
    push   '\0lld'
    push   '.23l'
    push   'lehS'
    push   esp
    call   dword ptr[LoadLibrary]
    push   eax
    mov    dword ptr[esp + 4], 660
    mov    dword ptr[esp + 8], 1
    mov    dword ptr[esp + 12], eax
    call   dword ptr[GetProcAddress]
    call   eax
    call   dword ptr[FreeLibrary]
    call   dword ptr[Shell_GetImageLists]
    ret    0
  }
}

HWND InitListView(HWND hParent)
{
  HWND hListView = CreateWindow(WC_LISTVIEW, "",
    LVS_AUTOARRANGE | LVS_SHAREIMAGELISTS | WS_CHILD | WS_VISIBLE,
    0, 0, 0, 0,
    hParent, 0, g_hInst, NULL);

  HIMAGELIST imgSmall, imgNormal;
  GetSystemImageList(&imgNormal, &imgSmall);
  ListView_SetImageList(hListView, imgSmall, LVSIL_SMALL);
  ListView_SetImageList(hListView, imgNormal, LVSIL_NORMAL);

  return hListView;
}

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  
  static CDropTarget* pDropTarget;    

  switch (msg)
  { 
  case WM_CREATE:
    hListView = InitListView(hwnd);
    pDropTarget = new CDropTarget(hListView);
    // Permet a la ListView de devenir une cible
    RegisterDragDrop(hListView, pDropTarget);
    break;
  case WM_SIZE:
    SetWindowPos(hListView, 0, 0, 0, LOWORD(lParam), HIWORD(lParam), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    break;
  case WM_CLOSE:   
    RevokeDragDrop(hwnd);
    pDropTarget->Release();  
    break;
  case WM_DESTROY:                
    PostQuitMessage(0);
    break;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg;
  InitCommonControls();
  OleInitialize(NULL); 

  CDropTarget::SetFormat(RegisterClipboardFormat("Test"));

  WNDCLASS wc;
  memset(&wc, 0, sizeof wc);
  wc.lpfnWndProc = MainWndProc;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(0, (LPCTSTR)IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "TargetWndClass";
  RegisterClass(&wc);

  g_hInst = hInstance;

  HWND hWnd = CreateWindow("TargetWndClass", "DropTarget", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, NULL, NULL))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }  

  OleUninitialize();

  return (int)msg.wParam;
}