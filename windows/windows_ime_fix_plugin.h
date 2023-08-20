#ifndef FLUTTER_PLUGIN_WINDOWS_IME_FIX_PLUGIN_H_
#define FLUTTER_PLUGIN_WINDOWS_IME_FIX_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace windows_ime_fix {

class WindowsImeFixPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  WindowsImeFixPlugin(flutter::PluginRegistrarWindows *registrar);

  virtual ~WindowsImeFixPlugin();

  // Disallow copy and assign.
  WindowsImeFixPlugin(const WindowsImeFixPlugin&) = delete;
  WindowsImeFixPlugin& operator=(const WindowsImeFixPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  // The ID of the WindowProc delegate registration.
  int window_proc_id = -1;

  flutter::PluginRegistrarWindows *registrar = nullptr;

  HWND GetWindow();

  void SetCompositionWindow(int left, int top, int right, int bottom);

  // Called for top-level WindowProc delegation.
  // std::optional<LRESULT> HandleWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}  // namespace windows_ime_fix

#endif  // FLUTTER_PLUGIN_WINDOWS_IME_FIX_PLUGIN_H_
