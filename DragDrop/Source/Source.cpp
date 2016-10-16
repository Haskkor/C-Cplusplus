#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <ole2.h>          
#include <shlobj.h>
#include "DropSource.h"
#include "DataObject.h"

#pragma comment(lib, "comctl32.lib")

HINSTANCE g_hInst;
WNDPROC defLVProc;

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

LRESULT CALLBACK LVProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  static CDropSource* pDropSource; 
  if(msg == WM_LBUTTONDOWN)
  {
    SetFocus(hwnd);
    CallWindowProc(defLVProc, hwnd, msg, wParam, lParam);
    DWORD dwEffect;

    pDropSource = new CDropSource;
    CDataObject* pDataObject = new CDataObject(hwnd);     

    DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);
    if(dwEffect == DROPEFFECT_MOVE)
    {
      // Déplacement des items: on les enlève de la ListView
      pDataObject->RemoveItems(hwnd);
    }
    pDataObject->Release();
    return 0;
  }
  return CallWindowProc(defLVProc, hwnd, msg, wParam, lParam);
}

HWND InitListView(HWND hParent)
{
  HWND hListView = CreateWindow(WC_LISTVIEW, "",
    LVS_AUTOARRANGE | LVS_SHAREIMAGELISTS | WS_CHILD | WS_VISIBLE,
    0, 0, 0, 0,
    hParent, 0, g_hInst, NULL);

  defLVProc = (WNDPROC)SetWindowLongPtr(hListView, GWL_WNDPROC, (LONG_PTR)LVProc);

  HIMAGELIST imgSmall, imgNormal;
  GetSystemImageList(&imgNormal, &imgSmall);
  ListView_SetImageList(hListView, imgSmall, LVSIL_SMALL);
  ListView_SetImageList(hListView, imgNormal, LVSIL_NORMAL);

  LVITEM lvi;

  lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
  lvi.iSubItem = 0;
  char szText[20];
  lvi.pszText = szText;
  int count = ImageList_GetImageCount(imgNormal);
  for(int i = 0; i < count; i++)
  {
    lvi.iItem = i;
    _itoa(i, szText, 10);
    lvi.iImage = lvi.lParam = i;
    ListView_InsertItem(hListView, &lvi);
  }

  return hListView;
}

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  
  static HWND hListView;

  switch (msg)
  {
  case WM_SETFOCUS:
    SetFocus(hListView);
    break;
  case WM_CREATE:
    hListView = InitListView(hwnd);                
    break;
  case WM_SIZE:
    SetWindowPos(hListView, 0, 0, 0, LOWORD(lParam), HIWORD(lParam), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
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

  CDataObject::SetFormat(RegisterClipboardFormat("Test"));

  WNDCLASS wc;
  memset(&wc, 0, sizeof wc);
  wc.lpfnWndProc = MainWndProc;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(0, (LPCTSTR)IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "SourceWndClass";
  RegisterClass(&wc);

  g_hInst = hInstance;

  HWND hWnd = CreateWindow("SourceWndClass", "DropSource", WS_OVERLAPPEDWINDOW,
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