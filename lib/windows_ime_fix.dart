import 'windows_ime_fix_platform_interface.dart';

class WindowsImeFix {
  Future<String?> getPlatformVersion() {
    return WindowsImeFixPlatform.instance.getPlatformVersion();
  }

  static Future<void> setCompositionWindow(int left, int top, int right, int bottom) {
    return WindowsImeFixPlatform.instance.setCompositionWindow(left, top, right, bottom);
  }
}
