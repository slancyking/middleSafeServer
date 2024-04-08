import type { CardClientRequstBase } from '../../common-dto/models';
import type { QueryPropCollectInputCommon } from '../../../irepository/models';

export interface CreatePropCollectionInput extends CardClientRequstBase {
  token?: string;
  propName: string;
  propId: string;
  propNum: number;
  remark?: string;
}

export interface PropProjectOutputDto {
  projectName?: string;
}

export interface QueryDetailInput extends QueryPropCollectInputCommon {
  sorting?: string;
  maxResultCount: number;
  skipCount: number;
}

export interface QueryDetailOutput {
  creationTime?: string;
  ip?: string;
  projectName?: string;
  branchName?: string;
  cardPassword?: string;
  propName?: string;
  propId?: string;
  propNum: number;
  postUnix: number;
  remark?: string;
}

export interface QueryEveryDayInput extends QueryPropCollectInputCommon {
  sorting?: string;
  maxResultCount: number;
  skipCount: number;
}

export interface QueryEveryDayOutput {
  showTime?: string;
  projectName?: string;
  branchName?: string;
  propName?: string;
  propNum: number;
}

export interface QueryProjectTableInputDto extends QueryPropCollectInputCommon {
}
