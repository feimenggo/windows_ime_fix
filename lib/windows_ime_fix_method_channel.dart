import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'windows_ime_fix_platform_interface.dart';

/// An implementation of [WindowsImeFixPlatform] that uses method channels.
class MethodChannelWindowsImeFix extends WindowsImeFixPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('windows_ime_fix');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<void> setCompositionWindow(int left, int top, int right, int bottom) async {
    final Map<String, int> arguments = {
      'left': left,
      'top': top,
      'right': right,
      'bottom': bottom,
    };
    await methodChannel.invokeMethod<bool>('setCompositionWindow', arguments);
  }
}
