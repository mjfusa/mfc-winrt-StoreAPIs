## MFC - WinRT - Store APIs

# Description
This sample demonstrates how to call the WinRT Store APIs from an MFC application

To modify an existing MFC app to call WinRT Store APIs:

1) Add the Microsoft.Windows.CppWinRT to your MFC app. This will help you access the Windows Runtime APIs.
NuGet Gallery | Microsoft.Windows.CppWinRT 2.0.200615.7
microsoft/cppwinrt: C++ language projection for the Windows Runtime

2) After installing the nuget package, make sure the MFC project properties are set to C++ version is ISO C++17, which is required by C++/WinRT:
  

3) You will need to use the Windows.Services.Store API set as the namespace Windows.ApplicationModel.Store is not supported when running packaged as an MSIX app. Source: https://docs.microsoft.com/en-us/windows/uwp/monetize/in-app-purchases-and-trials

3) If you haven’t done so already, you should reserve the application name in Partner Center: https://partner.microsoft.com/en-us/dashboard

4) Use the Visual Studio Application Packaging Project to package the app as MSIX and provide the requires app identity and Store association. Package a desktop app from source code using Visual Studio - MSIX | Microsoft Docs. You should run and debug your application in the context of the Package Project to ensure it works as expected in this environment. Be sure to change the debug settings to Native only as it defaults to Managed and your breakpoints will not hit.

5) Regarding initialization:
   
a. Be sure to call winrt::init_apartment(); in app start up.

b. Call IInitializeWithWindow.Initialize() from the StoreContext to associate the main window with the Microsoft Store UI. Here’s a code sample: 

```C++
winrt::init_apartment();  
  
_storeContext = StoreContext::GetDefault();  
auto iwp = _storeContext.try_as<IInitializeWithWindow>();  
HWND hwnd = (HWND)GetMainWnd();  
auto hr = iwp->Initialize(hwnd);  
_com_error err(hr);  
AfxOutputDebugString(L"Init complete: " + (CString) err.ErrorMessage());  
```

7) Then you can call the WinRT async calls which should be UI thread friendly without have to resort to creating worker threads to accomplish this task.

# To Run

Click About icon – all work done in that handler.
Note: You’ll want to associate it with your own app in Partner Center. In the sample, I've associated with an app I have in the Store.

