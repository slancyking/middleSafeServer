import type { CardClientRequstBase } from '../../common-dto/models';

export interface IpLogInputDto extends CardClientRequstBase {
  ipAddress?: string;
  logMark?: string;
  nation?: string;
  province?: string;
  city?: string;
  district?: string;
  token: string;
}

export interface IpLogInputOutputDto {
  result: number;
  info?: string;
}
