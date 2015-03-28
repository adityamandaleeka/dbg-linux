#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

char *to_ascii(char16_t *src)
{
    char *result = (char *)src;
    char *dst = result;
    while (*src)
    {
        *dst++ = (char)*src++;
    }
    *dst = 0;
    return result;
}


MIDL_DEFINE_GUID(IID, IID_ICorDebugManagedCallback,0x3d6f5f60,0x7538,0x11d3,0x8d,0x5b,0x00,0x10,0x4b,0x35,0xe7,0xef);


MIDL_DEFINE_GUID(IID, IID_ICorDebugManagedCallback3,0x264EA0FC,0x2591,0x49AA,0x86,0x8E,0x83,0x5E,0x65,0x15,0x32,0x3F);


MIDL_DEFINE_GUID(IID, IID_ICorDebugManagedCallback2,0x250E5EEA,0xDB5C,0x4C76,0xB6,0xF3,0x8C,0x46,0xF1,0x2E,0x32,0x03);

#define DebugBreak() asm("int 3");
#define PrintWhereIAm() printf("Callback called: %s\n", __func__);

class ManagedCallback : public ICorDebugManagedCallback, ICorDebugManagedCallback2
{
    ICorDebugProcess *m_pProcess;


public:
    ManagedCallback()
        :m_pProcess(nullptr)
    {
    }

    // IUnknown
    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        REFIID riid,
        void **ppvObj) 
    {
        if (!ppvObj)
            return E_INVALIDARG;

        *ppvObj = NULL;
        if (/* riid == IID_IUnknown || */ riid == IID_ICorDebugManagedCallback
             || riid == IID_ICorDebugManagedCallback2)
        {
            // Increment the reference count and return the pointer.
            *ppvObj = (LPVOID)this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
        
    virtual ULONG STDMETHODCALLTYPE AddRef( void) { return 1; }
        
    virtual ULONG STDMETHODCALLTYPE Release( void) { return 1; }

    // ICorDebugManagedCallback
    virtual HRESULT STDMETHODCALLTYPE Breakpoint( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugBreakpoint *pBreakpoint)
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE StepComplete( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugStepper *pStepper,
        /* [in] */ CorDebugStepReason reason)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE Break( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *thread)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE Exception( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ BOOL unhandled)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE EvalComplete( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugEval *pEval)
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE EvalException( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugEval *pEval)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateProcess( 
        /* [in] */ ICorDebugProcess *pProcess)    
    {
        PrintWhereIAm();
        m_pProcess = pProcess;
        m_pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE ExitProcess( 
        /* [in] */ ICorDebugProcess *pProcess)    
    {
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateThread( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *thread)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE ExitThread( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *thread)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE LoadModule( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugModule *pModule)    
    {
        PrintWhereIAm(); 
        WCHAR name[100];
        ULONG32 len;
        pModule->GetName(100, &len, name);
        printf("\tModule name: %s\n", to_ascii(name));        
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE UnloadModule( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugModule *pModule)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE LoadClass( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugClass *c)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE UnloadClass( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugClass *c)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE DebuggerError( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ HRESULT errorHR,
        /* [in] */ DWORD errorCode)    
    {
        PrintWhereIAm(); 
        pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE LogMessage( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ LONG lLevel,
        /* [in] */ WCHAR *pLogSwitchName,
        /* [in] */ WCHAR *pMessage)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE LogSwitch( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ LONG lLevel,
        /* [in] */ ULONG ulReason,
        /* [in] */ WCHAR *pLogSwitchName,
        /* [in] */ WCHAR *pParentName)
        {
            PrintWhereIAm();
            printf("\tSwitch name: %s\n", to_ascii(pLogSwitchName));
            pAppDomain->Continue(FALSE);  
            return S_OK; 
        }
    
    virtual HRESULT STDMETHODCALLTYPE CreateAppDomain( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ ICorDebugAppDomain *pAppDomain)
        {
            PrintWhereIAm(); 
            pAppDomain->Attach();
            pAppDomain->Continue(FALSE); 
            return S_OK; 
        }
    
    virtual HRESULT STDMETHODCALLTYPE ExitAppDomain( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ ICorDebugAppDomain *pAppDomain)
        {
            PrintWhereIAm(); 
            pAppDomain->Continue(FALSE); 
            return S_OK; 
        }
    
    virtual HRESULT STDMETHODCALLTYPE LoadAssembly( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugAssembly *pAssembly)    
    {
        PrintWhereIAm(); 
        WCHAR name[100];
        ULONG32 len;
        pAssembly->GetName(100, &len, name);
        printf("\tAssembly name: %s\n", to_ascii(name));
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE UnloadAssembly( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugAssembly *pAssembly)
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE ControlCTrap( 
        /* [in] */ ICorDebugProcess *pProcess)
    {
        PrintWhereIAm(); 
        pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE NameChange( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread)
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE UpdateModuleSymbols( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugModule *pModule,
        /* [in] */ IStream *pSymbolStream)
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE EditAndContinueRemap( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugFunction *pFunction,
        /* [in] */ BOOL fAccurate)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE BreakpointSetError( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugBreakpoint *pBreakpoint,
        /* [in] */ DWORD dwError)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    

    // ICorDebugManagedCallback2
    virtual HRESULT STDMETHODCALLTYPE FunctionRemapOpportunity( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugFunction *pOldFunction,
        /* [in] */ ICorDebugFunction *pNewFunction,
        /* [in] */ ULONG32 oldILOffset)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateConnection( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ CONNID dwConnectionId,
        /* [in] */ WCHAR *pConnName)
    {
        PrintWhereIAm(); 
        pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE ChangeConnection( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ CONNID dwConnectionId)
    {
        PrintWhereIAm(); 
        pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE DestroyConnection( 
        /* [in] */ ICorDebugProcess *pProcess,
        /* [in] */ CONNID dwConnectionId)
    {
        PrintWhereIAm(); 
        pProcess->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE Exception( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugFrame *pFrame,
        /* [in] */ ULONG32 nOffset,
        /* [in] */ CorDebugExceptionCallbackType dwEventType,
        /* [in] */ DWORD dwFlags)    
    {
        PrintWhereIAm();
        printf("\tFlags = %x\n dwEventType=%x", dwFlags, (DWORD)dwEventType);
        pAppDomain->Continue(FALSE);  
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE ExceptionUnwind( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ CorDebugExceptionUnwindCallbackType dwEventType,
        /* [in] */ DWORD dwFlags)    
    {
        PrintWhereIAm(); 
        pAppDomain->Continue(FALSE); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE FunctionRemapComplete( 
        /* [in] */ ICorDebugAppDomain *pAppDomain,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugFunction *pFunction)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    
    virtual HRESULT STDMETHODCALLTYPE MDANotification( 
        /* [in] */ ICorDebugController *pController,
        /* [in] */ ICorDebugThread *pThread,
        /* [in] */ ICorDebugMDA *pMDA)    
    { 
        PrintWhereIAm(); 
        return S_OK; 
    }
    

};
