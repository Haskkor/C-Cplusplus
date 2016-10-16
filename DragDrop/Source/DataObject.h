#pragma once
#include <windows.h>
#include <commctrl.h>
#include <ole2.h>

class CDataObject : public IDataObject
{
public:
  static void SetFormat(UINT uFormat);
  CDataObject(HWND hListView);
  ~CDataObject();

  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);

  STDMETHOD(GetData)(LPFORMATETC pformatetcIn,  LPSTGMEDIUM pmedium );
  STDMETHOD(GetDataHere)(LPFORMATETC pformatetc, LPSTGMEDIUM pmedium );
  STDMETHOD(QueryGetData)(LPFORMATETC pformatetc );
  STDMETHOD(GetCanonicalFormatEtc)(LPFORMATETC pformatetc, LPFORMATETC pformatetcOut);
  STDMETHOD(SetData)(LPFORMATETC pformatetc, STGMEDIUM* pmedium,
    BOOL fRelease);
  STDMETHOD(EnumFormatEtc)(DWORD dwDirection, LPENUMFORMATETC* ppenumFormatEtc);
  STDMETHOD(DAdvise)(FORMATETC* pFormatetc, DWORD advf, 
    LPADVISESINK pAdvSink, DWORD* pdwConnection);
  STDMETHOD(DUnadvise)(DWORD dwConnection);
  STDMETHOD(EnumDAdvise)(LPENUMSTATDATA* ppenumAdvise);

  void RemoveItems(HWND hWnd);

private:
  static UINT m_uFormat;
  ULONG m_refs;   
  DWORD m_selCount, *m_itemList;
};
