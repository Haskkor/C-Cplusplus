#pragma once
#include <windows.h>
#include <commctrl.h>
#include <ole2.h>

class CDropSource : public IDropSource
{
public:    
  CDropSource();

  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);

  STDMETHOD(QueryContinueDrag)(BOOL fEscapePressed, DWORD grfKeyState);
  STDMETHOD(GiveFeedback)(DWORD dwEffect);

private:
  ULONG m_refs;     
};