import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'windows_ime_fix_method_channel.dart';

abstract class WindowsImeFixPlatform extends PlatformInterface {
  /// Constructs a WindowsImeFixPlatform.
  WindowsImeFixPlatform() : super(token: _token);

  static final Object _token = Object();

  static WindowsImeFixPlatform _instance = MethodChannelWindowsImeFix();

  /// The default instance of [WindowsImeFixPlatform] to use.
  ///
  /// Defaults to [MethodChannelWindowsImeFix].
  static WindowsImeFixPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [WindowsImeFixPlatform] when
  /// they register themselves.
  static set instance(WindowsImeFixPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<void> setCompositionWindow(int left, int top, int right, int bottom) {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
