#include "include/windows_ime_fix/windows_ime_fix_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "windows_ime_fix_plugin.h"

void WindowsImeFixPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  windows_ime_fix::WindowsImeFixPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
