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

  // A cause de la valeur de fmtetc.cfFormat, seuls les objets provenant de notre application seront acceptés
  m_bDropOK = pDataObj->QueryGetData(&fmtetc) == S_OK;
  *pdwEffect = GetEffect(grfKeyState);
  return S_OK;
}

// Fonction appelée dès que la souris bouge au dessus de la fenêtre
// On a juste a choisir le bon effet (qui dépend de l'état des touches du clavier)
STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
{
  *pdwEffect = GetEffect(grfKeyState);
  return S_OK;
}

// Passage en dehors de la fenêtre: rien a faire
STDMETHODIMP CDropTarget::DragLeave()
{
  return S_OK;
}

// Fin du déplacement
STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)  
{   
  FORMATETC fmtetc;   
  STGMEDIUM medium;   

  *pdwEffect = GetEffect(grfKeyState);
  FillFormatEtc(&fmtetc);

  // On récupère les données de l'objet
  pDataObj->GetData(&fmtetc, &medium);

  // Récupère la zone mémoire contenant les numéro des items, puis les ajoute dans la ListView
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

// Récupère l'effet en fonction des touches du clavier et de m_bDropOK
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