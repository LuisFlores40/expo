/**
 * Automatically generated by expo-modules-test-core.
 *
 * This autogenerated file provides a mock for native Expo module,
 * and works out of the box with the expo jest preset.
 *  */

export type URL = any;

export type BarcodeType = any;

export type VisionScannerOptions = any;

export type TakePictureOptions = any;

export type CameraRecordingOptions = any;

export type CameraType = any;

export type FlashMode = any;

export type PictureSize = any;

export type CameraMode = any;

export type BarcodeSettings = any;

export type VideoQuality = any;

export async function scanFromURLAsync(url: URL, _: BarcodeType[]): Promise<any> {}

export async function launchScanner(options: VisionScannerOptions | undefined): Promise<any> {}

export async function dismissScanner(): Promise<any> {}

export async function getCameraPermissionsAsync(): Promise<any> {}

export async function requestCameraPermissionsAsync(): Promise<any> {}

export async function getMicrophonePermissionsAsync(): Promise<any> {}

export async function requestMicrophonePermissionsAsync(): Promise<any> {}

export async function getAvailableVideoCodecsAsync(): Promise<string[]> {
  return [];
}

export type ViewProps = {
  facing: CameraType | undefined;
  flashMode: FlashMode | undefined;
  enableTorch: boolean | undefined;
  pictureSize: PictureSize | undefined;
  zoom: number | undefined;
  mode: CameraMode | undefined;
  barcodeScannerEnabled: boolean | undefined;
  barcodeScannerSettings: BarcodeSettings | undefined;
  mute: boolean | undefined;
  animateShutter: boolean | undefined;
  videoQuality: VideoQuality | undefined;
  responsiveOrientationWhenOrientationLocked: boolean | undefined;
  cameraNextEvents: (event: any) => void;
};

export function View(props: ViewProps) {}
