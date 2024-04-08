import type { CardClientRequstBase } from '../../common-dto/models';
import type { EntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';

export interface CreateManyNameCollectDto extends CardClientRequstBase {
  nameCollects: CreateNameCollectDto[];
  token: string;
}

export interface CreateManyNameCollectOutputDto {
  result: number;
  info?: string;
}

export interface CreateNameCollectDto {
  name: string;
  infoAgentId: string;
  sex: number;
  headIconUrl: string;
  imageCollect: string;
  extendJson: string;
}

export interface GetNameCollectListDto extends PagedAndSortedResultRequestDto {
  filter?: string;
  infoAgentId?: string;
}

export interface GetRandomNameCollectInputDto extends CardClientRequstBase {
  infoAgentId: string;
  token: string;
}

export interface GetRandomNameCollectOutputDto {
  result: number;
  info?: string;
  data: NameCollectDto;
}

export interface NameCollectDto extends EntityDto<string> {
  infoAgent?: string;
  name?: string;
  sex: number;
  finishSaveHeadIcon: boolean;
  headIconUrl?: string;
  retrySaveHeadIconCount: number;
  imageCollect?: string;
}

export interface UpdateNameCollectDto {
  infoAgentId: string;
  name: string;
  sex: number;
  imageCollect: string;
  extendJson: string;
}
