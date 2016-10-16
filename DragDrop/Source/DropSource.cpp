#include "DropSource.h"

CDropSource::CDropSource()
{
  m_refs = 1;  
}   

STDMETHODIMP
CDropSource::QueryInterface(REFIID iid, void** ppv) 
{
  if(iid == IID_IUnknown || iid == IID_IDropSource)
  {
    *ppv = this;
    ++m_refs;
    return NOERROR;
  }
  *ppv = NULL;
  return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CDropSource::AddRef(void)
{
  return ++m_refs;
}


STDMETHODIMP_(ULONG) CDropSource::Release(void)
{
  if(--m_refs == 0)
  {
    delete this;
    return 0;
  }
  return m_refs;
}  

STDMETHODIMP CDropSource::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
{  
  if(fEscapePressed) return DRAGDROP_S_CANCEL;
  if(!(grfKeyState & MK_LBUTTON)) return DRAGDROP_S_DROP;
  return S_OK;                  
}

STDMETHODIMP CDropSource::GiveFeedback(DWORD dwEffect)
{
  return DRAGDROP_S_USEDEFAULTCURSORS;
}