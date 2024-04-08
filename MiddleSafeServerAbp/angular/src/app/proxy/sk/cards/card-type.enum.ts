import { mapEnumToOptions } from '@abp/ng.core';

export enum CardType {
  Inner = 0,
  Outer = 1,
}

export const cardTypeOptions = mapEnumToOptions(CardType);
