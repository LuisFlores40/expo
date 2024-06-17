/**
 * Automatically generated by expo-modules-test-core.
 *
 * This autogenerated file provides a mock for native Expo module,
 * and works out of the box with the expo jest preset.
 *  */

export type TakePictureOptions = any;

export type CameraRecordingOptionsLegacy = any;

export type CameraTypeLegacy = any;

export type FlashModeLegacy = any;

export type AutoFocus = any;

export type WhiteBalance = any;

export async function takePicture(options: TakePictureOptions, viewTag: number): Promise<any> {}

export async function record(
  options: CameraRecordingOptionsLegacy,
  viewTag: number
): Promise<any> {}

export async function stopRecording(viewTag: number): Promise<any> {}

export async function resumePreview(viewTag: number): Promise<any> {}

export async function pausePreview(viewTag: number): Promise<any> {}

export async function getAvailablePictureSizes(_: string | undefined, _: number): Promise<any> {}

export async function getAvailableVideoCodecsAsync(): Promise<string[]> {
  return [];
}

export async function getPermissionsAsync(): Promise<any> {}

export async function requestPermissionsAsync(): Promise<any> {}

export async function getCameraPermissionsAsync(): Promise<any> {}

export async function requestCameraPermissionsAsync(): Promise<any> {}

export async function getMicrophonePermissionsAsync(): Promise<any> {}

export async function requestMicrophonePermissionsAsync(): Promise<any> {}

export type ViewProps = {
  type: CameraTypeLegacy;
  flashMode: FlashModeLegacy;
  faceDetectorSettings: {
    [key: string]: any;
  };
  barCodeScannerSettings: {
    [key: string]: any;
  };
  autoFocus: AutoFocus;
  focusDepth: number;
  zoom: number;
  whiteBalance: WhiteBalance;
  pictureSize: string;
  faceDetectorEnabled: boolean | undefined;
  barCodeScannerEnabled: boolean | undefined;
  responsiveOrientationWhenOrientationLocked: boolean;
  cameraEvents: (event: any) => void;
};

export function View(props: ViewProps) {}
