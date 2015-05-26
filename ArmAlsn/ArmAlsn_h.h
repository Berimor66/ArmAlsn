

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue May 26 18:51:23 2015
 */
/* Compiler settings for ArmAlsn.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __ArmAlsn_h_h__
#define __ArmAlsn_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IArmAlsn_FWD_DEFINED__
#define __IArmAlsn_FWD_DEFINED__
typedef interface IArmAlsn IArmAlsn;
#endif 	/* __IArmAlsn_FWD_DEFINED__ */


#ifndef __CArmAlsnDoc_FWD_DEFINED__
#define __CArmAlsnDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CArmAlsnDoc CArmAlsnDoc;
#else
typedef struct CArmAlsnDoc CArmAlsnDoc;
#endif /* __cplusplus */

#endif 	/* __CArmAlsnDoc_FWD_DEFINED__ */


#ifndef __IDBVListView_FWD_DEFINED__
#define __IDBVListView_FWD_DEFINED__
typedef interface IDBVListView IDBVListView;
#endif 	/* __IDBVListView_FWD_DEFINED__ */


#ifndef __DBVListView_FWD_DEFINED__
#define __DBVListView_FWD_DEFINED__

#ifdef __cplusplus
typedef class DBVListView DBVListView;
#else
typedef struct DBVListView DBVListView;
#endif /* __cplusplus */

#endif 	/* __DBVListView_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ArmAlsn_LIBRARY_DEFINED__
#define __ArmAlsn_LIBRARY_DEFINED__

/* library ArmAlsn */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ArmAlsn;

#ifndef __IArmAlsn_DISPINTERFACE_DEFINED__
#define __IArmAlsn_DISPINTERFACE_DEFINED__

/* dispinterface IArmAlsn */
/* [uuid] */ 


EXTERN_C const IID DIID_IArmAlsn;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BCBF38A5-7B4C-48E1-A0C8-0F05733A6AF3")
    IArmAlsn : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IArmAlsnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IArmAlsn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IArmAlsn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IArmAlsn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IArmAlsn * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IArmAlsn * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IArmAlsn * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IArmAlsn * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IArmAlsnVtbl;

    interface IArmAlsn
    {
        CONST_VTBL struct IArmAlsnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArmAlsn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IArmAlsn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IArmAlsn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IArmAlsn_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IArmAlsn_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IArmAlsn_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IArmAlsn_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IArmAlsn_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CArmAlsnDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("D77DB3AB-0C61-4008-9B42-C36AEB57B303")
CArmAlsnDoc;
#endif

#ifndef __IDBVListView_DISPINTERFACE_DEFINED__
#define __IDBVListView_DISPINTERFACE_DEFINED__

/* dispinterface IDBVListView */
/* [uuid] */ 


EXTERN_C const IID DIID_IDBVListView;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2853546B-F22C-4199-8CB4-AAFB4F1803AA")
    IDBVListView : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDBVListViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDBVListView * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDBVListView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDBVListView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDBVListView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDBVListView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDBVListView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDBVListView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDBVListViewVtbl;

    interface IDBVListView
    {
        CONST_VTBL struct IDBVListViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBVListView_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDBVListView_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDBVListView_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDBVListView_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDBVListView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDBVListView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDBVListView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDBVListView_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DBVListView;

#ifdef __cplusplus

class DECLSPEC_UUID("6613BD2E-4BE3-469F-A0C6-85EF19271D96")
DBVListView;
#endif
#endif /* __ArmAlsn_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


