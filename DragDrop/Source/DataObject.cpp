#include "DataObject.h"

UINT CDataObject::m_uFormat = 0;

void CDataObject::SetFormat(UINT uFormat)
{
  m_uFormat = uFormat;
}

// Construction de l'objet contenant les données
CDataObject::CDataObject(HWND hWnd)
{

  m_selCount = ListView_GetSelectedCount(hWnd);
  m_itemList = (DWORD*)HeapAlloc(GetProcessHeap(), 0, m_selCount * 4 + 4);
  DWORD* p = m_itemList;
  *p++ = m_selCount;
  
  LVITEM lvi;
  lvi.mask = LVIF_IMAGE;
  lvi.iSubItem = 0;
  lvi.iItem = -1;
  for(DWORD i = 0; i < m_selCount; i++)
  {
    lvi.iItem = ListView_GetNextItem(hWnd, lvi.iItem, LVNI_ALL | LVNI_SELECTED);
    ListView_GetItem(hWnd, &lvi);
    *p++ = lvi.iImage;
  }
  m_refs = 1;    
}

CDataObject::~CDataObject()
{
  HeapFree(GetProcessHeap(), 0, m_itemList);
}

void CDataObject::RemoveItems(HWND hWnd)
{
  DWORD* p = m_itemList + 1;
  LVFINDINFO findInfo;
  findInfo.flags = LVFI_PARAM;
  for(int i = *m_itemList; i > 0; i--)
  {
    findInfo.lParam = m_itemList[i];
    ListView_DeleteItem(hWnd, ListView_FindItem(hWnd, -1, &findInfo));
  }
}

STDMETHODIMP CDataObject::QueryInterface(REFIID iid, void** ppv) 
{
  if(iid == IID_IUnknown || iid == IID_IDataObject)
  {
    *ppv = this;
    AddRef();
    return NOERROR;
  }
  *ppv = NULL;
  return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CDataObject::AddRef(void)
{
  return ++m_refs;
}

STDMETHODIMP_(ULONG) CDataObject::Release(void)
{
  if(--m_refs == 0)
  {
    delete this;
    return 0;
  }
  return m_refs;
}

// Méthode appelée par la cible pour récupérer les données de l'objet
// On remplit donc le STGMEDIUM a partir du FORMATETC
// Ici on fait toujours la même chose, mais dans le cas général le traitement est différent
// selon le tymed
STDMETHODIMP CDataObject::GetData(LPFORMATETC pformatetc, LPSTGMEDIUM pmedium) 
{
  pmedium->tymed = NULL;
  pmedium->pUnkForRelease = NULL;
  pmedium->hGlobal = NULL;

  // Vérification du format
  if (pformatetc->cfFormat == m_uFormat &&
    pformatetc->dwAspect == DVASPECT_CONTENT &&
    pformatetc->tymed == TYMED_HGLOBAL)
  {
    // Copie des données dans une zone de mémoire globale
    HGLOBAL hgbl = GlobalAlloc(GHND, 4 * m_selCount + 4);    
    LPVOID p = GlobalLock(hgbl);
    memcpy(p, m_itemList, 4 * m_selCount + 4);
    GlobalUnlock(hgbl);

    pmedium->tymed = TYMED_HGLOBAL;
    pmedium->hGlobal = hgbl; 

    return S_OK;
  }
  return DATA_E_FORMATETC;
}

STDMETHODIMP CDataObject::GetDataHere(LPFORMATETC pformatetc, LPSTGMEDIUM pmedium)  
{
  return E_NOTIMPL;    
}

// Cette fonction indique si le FORMATETC passé en paramètre est correct
// Si oui, ca veut dire que GetData devrait marcher avec ce FORMATETC
STDMETHODIMP CDataObject::QueryGetData(LPFORMATETC pformatetc) 
{
  if(pformatetc->lindex != -1) return DV_E_LINDEX;
  if(pformatetc->tymed != TYMED_HGLOBAL) return DV_E_TYMED;
  if(pformatetc->dwAspect != DVASPECT_CONTENT) return DV_E_DVASPECT;
  if(pformatetc->cfFormat != m_uFormat) return DV_E_FORMATETC;
  return S_OK;
}

STDMETHODIMP CDataObject::GetCanonicalFormatEtc(LPFORMATETC pformatetc, LPFORMATETC pformatetcOut)
{ 
  return E_NOTIMPL;
}

STDMETHODIMP CDataObject::SetData(LPFORMATETC pformatetc, STGMEDIUM *pmedium, BOOL fRelease)
{   
  return E_NOTIMPL;
}

STDMETHODIMP CDataObject::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppenumFormatEtc)
{ 
  return E_NOTIMPL;
}

STDMETHODIMP CDataObject::DAdvise(FORMATETC* pFormatetc, DWORD advf, 
                     LPADVISESINK pAdvSink, DWORD* pdwConnection)
{
  return E_NOTIMPL;
}


STDMETHODIMP CDataObject::DUnadvise(DWORD dwConnection)
{ 
  return E_NOTIMPL;
}

STDMETHODIMP CDataObject::EnumDAdvise(LPENUMSTATDATA* ppenumAdvise)
{
  return E_NOTIMPL;
}