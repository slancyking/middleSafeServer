import { mapEnumToOptions } from '@abp/ng.core';

export enum CardChargingMode {
  timing = 0,
  timingCanPause = 1,
  timeingAutoPause = 2,
  realTime = 3,
}

export const cardChargingModeOptions = mapEnumToOptions(CardChargingMode);
