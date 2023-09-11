package abi48_0_0.expo.modules.haptics

import android.content.Context
import android.os.Build
import android.os.VibrationEffect
import android.os.Vibrator
import abi48_0_0.expo.modules.haptics.arguments.HapticsImpactType
import abi48_0_0.expo.modules.haptics.arguments.HapticsNotificationType
import abi48_0_0.expo.modules.haptics.arguments.HapticsSelectionType
import abi48_0_0.expo.modules.haptics.arguments.HapticsVibrationType
import abi48_0_0.expo.modules.kotlin.exception.Exceptions
import abi48_0_0.expo.modules.kotlin.modules.Module
import abi48_0_0.expo.modules.kotlin.modules.ModuleDefinition

class HapticsModule : Module() {
  private val context: Context
    get() = appContext.reactContext ?: throw Exceptions.ReactContextLost()
  private val vibrator
    get() = context.getSystemService(Context.VIBRATOR_SERVICE) as Vibrator

  override fun definition() = ModuleDefinition {
    Name("ExpoHaptics")

    AsyncFunction("notificationAsync") { type: String ->
      vibrate(HapticsNotificationType.fromString(type))
    }

    AsyncFunction("selectionAsync") {
      vibrate(HapticsSelectionType)
    }

    AsyncFunction("impactAsync") { style: String ->
      vibrate(HapticsImpactType.fromString(style))
    }
  }

  private fun vibrate(type: HapticsVibrationType) {
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
      vibrator.vibrate(VibrationEffect.createWaveform(type.timings, type.amplitudes, -1))
    } else {
      vibrator.vibrate(type.oldSDKPattern, -1)
    }
  }
}
