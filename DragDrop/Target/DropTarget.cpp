#include "DropTarget.h"

UINT CDropTarget::m_uFormat;

void CDropTarget::SetFormat(UINT uFormat)
{
  m_uFormat = uFormat;
}

CDropTarget::CDropTarget(HWND hListView): m_hListView(hListView)
{
  m_refs = 1;
  m_bDropOK = FALSE;
}   

STDMETHODIMP CDropTarget::QueryInterface(REFIID iid, void** ppv) 
{
  if(iid == IID_IUnknown || iid == IID_IDropTarget)
  {
    *ppv = this;
    AddRef();
    return NOERROR;
  }
  *ppv = NULL;
  return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
{
  return ++m_refs;
}


STDMETHODIMP_(ULONG) CDropTarget::Release(void)
{
  if(--m_refs == 0)
  {
    delete this;
    return 0;
  }
  return m_refs;
}  

STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
{  
  FORMATETC fmtetc;
  FillFormatEtc(&fmtetc);

  // A cause de la valeur de fmtetc.cfFormat, seuls les objets provenant de notre application seront accept�s
  m_bDropOK = pDataObj->QueryGetData(&fmtetc) == S_OK;
  *pdwEffect = GetEffect(grfKeyState);
  return S_OK;
}

// Fonction appel�e d�s que la souris bouge au dessus de la fen�tre
// On a juste a choisir le bon effet (qui d�pend de l'�tat des touches du clavier)
STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
{
  *pdwEffect = GetEffect(grfKeyState);
  return S_OK;
}

// Passage en dehors de la fen�tre: rien a faire
STDMETHODIMP CDropTarget::DragLeave()
{
  return S_OK;
}

// Fin du d�placement
STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)  
{   
  FORMATETC fmtetc;   
  STGMEDIUM medium;   

  *pdwEffect = GetEffect(grfKeyState);
  FillFormatEtc(&fmtetc);

  // On r�cup�re les donn�es de l'objet
  pDataObj->GetData(&fmtetc, &medium);

  // R�cup�re la zone m�moire contenant les num�ro des items, puis les ajoute dans la ListView
  HGLOBAL hgbl = medium.hGlobal;
  DWORD* items = (DWORD*)GlobalLock(hgbl);
  int itemCount = *items++;

  LVITEM lvi;
  char buffer[20];

  lvi.mask = LVIF_TEXT | LVIF_IMAGE;
  lvi.iItem = 0;
  lvi.iSubItem = 0;
  lvi.pszText = buffer;
  while(--itemCount >= 0)
  {
    _itoa(*items, buffer, 10);
    lvi.iImage = *items++;
    ListView_InsertItem(m_hListView, &lvi);
  }

  GlobalUnlock(hgbl);
  ReleaseStgMedium(&medium);
  return S_OK;      
}

// R�cup�re l'effet en fonction des touches du clavier et de m_bDropOK
DWORD CDropTarget::GetEffect(DWORD grfKeyState)
{  
  if(!m_bDropOK) return DROPEFFECT_NONE;
  if(grfKeyState & MK_CONTROL) return DROPEFFECT_COPY;
  return DROPEFFECT_MOVE;
}

void CDropTarget::FillFormatEtc(LPFORMATETC lpfect)
{
  lpfect->cfFormat = m_uFormat;
  lpfect->ptd = NULL;
  lpfect->dwAspect = DVASPECT_CONTENT;  
  lpfect->lindex = -1;
  lpfect->tymed = TYMED_HGLOBAL;       
}