#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <commctrl.h>
#include <ole2.h>

class CDropTarget : public IDropTarget
{
public:    
  static void SetFormat(UINT uFormat);

  CDropTarget(HWND hListView);

  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);

  STDMETHOD(DragEnter)(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect);
  STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect);
  STDMETHOD(DragLeave)();
  STDMETHOD(Drop)(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect); 

private:
  static UINT m_uFormat;
  HWND m_hListView;
  ULONG m_refs;
  BOOL m_bDropOK;

  DWORD GetEffect(DWORD grfKeyState);
  void FillFormatEtc(LPFORMATETC lpfect);
};