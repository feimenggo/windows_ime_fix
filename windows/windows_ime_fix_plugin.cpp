#include "windows_ime_fix_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

#pragma comment(lib, "Imm32.lib")

namespace windows_ime_fix {

// static
void WindowsImeFixPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "windows_ime_fix",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<WindowsImeFixPlugin>(registrar);

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

WindowsImeFixPlugin::WindowsImeFixPlugin(
    flutter::PluginRegistrarWindows *registrar)
    :registrar(registrar) {
    //window_proc_id = registrar->RegisterTopLevelWindowProcDelegate(
    //  [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //    return HandleWindowProc(hWnd, message, wParam, lParam);
    //  });
}

WindowsImeFixPlugin::~WindowsImeFixPlugin() {
    registrar->UnregisterTopLevelWindowProcDelegate(window_proc_id);
}

void WindowsImeFixPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else if (method_call.method_name().compare("setCompositionWindow") == 0) {
    const flutter::EncodableMap& args = std::get<flutter::EncodableMap>(*method_call.arguments());
    int left = std::get<int>(args.at(flutter::EncodableValue("left")));
    int top = std::get<int>(args.at(flutter::EncodableValue("top")));
    int right = std::get<int>(args.at(flutter::EncodableValue("right")));
    int bottom = std::get<int>(args.at(flutter::EncodableValue("bottom")));
    SetCompositionWindow(left, top, right, bottom);
    result->Success(flutter::EncodableValue(true));
  } else {
    result->NotImplemented();
  }
}

HWND WindowsImeFixPlugin::GetWindow() {
    return ::GetAncestor(registrar->GetView()->GetNativeWindow(), GA_ROOT);
}

void WindowsImeFixPlugin::SetCompositionWindow(int left, int top, int right, int bottom)
{
    HWND hwnd = GetWindow();
    HIMC hIMC = ImmGetContext(hwnd);
    if (hIMC) {
        COMPOSITIONFORM compForm;
        compForm.dwStyle = CFS_POINT;
        compForm.ptCurrentPos.x = left;
        compForm.ptCurrentPos.y = bottom;
        SetCaretPos(left, bottom);
        ImmSetCompositionWindow(hIMC, &compForm);
        CANDIDATEFORM candidateForm = {0, CFS_EXCLUDE, {left, bottom}, {left, top, right, bottom}};
        ImmSetCandidateWindow(hIMC, &candidateForm);
        ImmReleaseContext(hwnd, hIMC);
//        std::cout << "修复候选框: left=" << left << "，top=" << top << "，right=" << right << "，bottom=" << bottom << std::endl;
    }
}

//std::optional<LRESULT> WindowsImeFixPlugin::HandleWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//    return 0;
//}

}  // namespace windows_ime_fix
