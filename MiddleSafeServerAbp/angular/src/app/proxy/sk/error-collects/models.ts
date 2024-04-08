import type { CardClientRequstBase } from '../common-dto/models';
import type { EntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';

export interface CreateErrorCollectInputDto extends CardClientRequstBase {
  token: string;
  errorTitle: string;
  errorMessage: string;
  backStackTraceBack: string;
}

export interface ErrorCollectDto extends EntityDto<string> {
  creationTime?: string;
  branchId?: string;
  branchName?: string;
  cardId?: string;
  ip?: string;
  errorTitle?: string;
  errorMessage?: string;
  backStackTraceBack?: string;
}

export interface GetErrorCollectListDto extends PagedAndSortedResultRequestDto {
  branchId?: string;
  errorTitle?: string;
  errorMessage?: string;
}
