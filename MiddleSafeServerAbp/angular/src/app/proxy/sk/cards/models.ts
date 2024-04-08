import type { EntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';
import type { CardStatus } from './card-status.enum';
import type { CardType } from './card-type.enum';
import type { CardChargingMode } from './card-charging-mode.enum';
import type { CardClientRequstBase } from '../common-dto/models';

export interface CardCommonOutputDto {
  result: number;
  info?: string;
}

export interface CardDto extends EntityDto<string> {
  password?: string;
  startTime?: string;
  days: number;
  loginOvertime?: string;
  loginToken?: string;
  mail?: string;
  phone?: string;
  branchId?: string;
  status: CardStatus;
  type: CardType;
  remark?: string;
  expiredTime?: string;
  creatorId?: string;
  isLogin: boolean;
  enableMail: boolean;
  enablePhoneMsg: boolean;
  title?: string;
  chargingMode: CardChargingMode;
}

export interface CardLoginInputDto {
  branchId: string;
  cardPassword: string;
}

export interface CardLoginOutpuDto {
  result: number;
  info?: string;
  token?: string;
  tokenEx?: string;
  expired: number;
  surplusSecond: number;
}

export interface CardLogoutDto extends CardClientRequstBase {
  token?: string;
}

export interface CardPauseDto extends CardClientRequstBase {
  token?: string;
}

export interface CardPingDto extends CardClientRequstBase {
  token?: string;
}

export interface CardSetTitleDto extends CardClientRequstBase {
  token?: string;
  title?: string;
}

export interface CreateCardDto {
  branchId: string;
  mail: string;
  phone: string;
  count: number;
  days: number;
  remark?: string;
  expiredTime?: string;
  enableMail: boolean;
  enablePhoneMsg: boolean;
  chargingMode: CardChargingMode;
}

export interface GetCardListDto extends PagedAndSortedResultRequestDto {
  filter?: string;
  creatorId?: string;
  branchId?: string;
  mail?: string;
  phone?: string;
}

export interface ImportCardInputDto {
  branchId: string;
  password: string;
  expiredTime: string;
  phone?: string;
  mail?: string;
  remark?: string;
}

export interface ImportCardOutputDto {
  failseList: string[];
}

export interface UpdateCardDto {
  password?: string;
  days: number;
  status: CardStatus;
  remark?: string;
  mail: string;
  phone: string;
  expiredTime?: string;
  enableMail: boolean;
  enablePhoneMsg: boolean;
  chargingMode: CardChargingMode;
}
