import type { CardClientRequstBase } from '../common-dto/models';

export interface MiddleNomalQueryInputDto extends CardClientRequstBase {
  flag: string;
  token: string;
}

export interface MiddleNomalQueryOutputDto {
  flag?: string;
  randomPort: number;
  randomKey?: string;
  keyIndex: number;
  info?: string;
}

export interface MiddleReportInputDto extends CardClientRequstBase {
  flag: string;
  keyIndex: number;
  randomPort: number;
  randomKey: string;
  token: string;
}

export interface MiddleReportOutputDto {
  result: number;
  info?: string;
}
