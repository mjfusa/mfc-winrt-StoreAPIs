
// MFCWithWinRT.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCWithWinRT.h"
#include "MainFrm.h"

#include "MFCWithWinRTDoc.h"
#include "MFCWithWinRTView.h"
#include "winrt/RuntimeComponent1.h"

using namespace winrt;
using namespace Windows;
using namespace Foundation;
using namespace Collections;
using namespace Services::Store;
using namespace RuntimeComponent1;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWithWinRTApp

BEGIN_MESSAGE_MAP(CMFCWithWinRTApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMFCWithWinRTApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CMFCWithWinRTApp construction

CMFCWithWinRTApp::CMFCWithWinRTApp() noexcept
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCWithWinRT.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCWithWinRTApp object

CMFCWithWinRTApp theApp;


// CMFCWithWinRTApp initialization

BOOL CMFCWithWinRTApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCWithWinRTDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMFCWithWinRTView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CMFCWithWinRTApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

static StoreContext _storeContext ({nullptr});
static StoreProductQueryResult _durables({ nullptr });

IAsyncOperation<StoreProductQueryResult> GetProducts()
{
	auto productKinds{ winrt::single_threaded_vector<winrt::hstring>({ L"Durable", L"Consumable"}) };
	return _storeContext.GetAssociatedStoreProductsAsync(productKinds);
}

void PrintProducts(StoreProductQueryResult const& value) {
	int cnt = value.Products().Size();
	if (cnt < 1)
		return;
	AfxOutputDebugString(L"Products:\n");
	for (IKeyValuePair<hstring, StoreProduct> prod : value.Products())
	{
		CString productId = prod.Key().c_str();
		CString productTitle = prod.Value().Title().c_str();
		AfxOutputDebugString(L"Product: " + productId + L" " + productTitle + L"\n");
	}
}
// App command to run the dialog
void CMFCWithWinRTApp::OnAppAbout()
{
	winrt::init_apartment();
	
	MyMath math;
	auto res = math.add(2, 2);
	

	_storeContext = StoreContext::GetDefault();
	auto iwp = _storeContext.try_as<IInitializeWithWindow>();
	HWND hwnd = (HWND)GetMainWnd();
	auto hr = iwp->Initialize(hwnd);
	_com_error err(hr);
	AfxOutputDebugString(L"Init complete: " + (CString) err.ErrorMessage());

	if (_durables == nullptr)
	{
		auto productList{ GetProducts() };
		PrintProducts(productList.get());
	}
}
// CMFCWithWinRTApp message handlers



