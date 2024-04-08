import { mapEnumToOptions } from '@abp/ng.core';

export enum CardStatus {
  UNUSE = 0,
  INUSE = 1,
  TEMPBLOCKED = 2,
  BLOCKED = 3,
  _COUNT = 4,
}

export const cardStatusOptions = mapEnumToOptions(CardStatus);
