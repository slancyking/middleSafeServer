import type { EntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';

export interface CreateInfoAgentDto {
  name: string;
  isOpen: boolean;
  description?: string;
}

export interface GetInfoAgentListDto extends PagedAndSortedResultRequestDto {
  filter?: string;
}

export interface InfoAgentDto extends EntityDto<string> {
  creationTime?: string;
  isOpen: boolean;
  name?: string;
  description?: string;
}

export interface UpdateInfoAgentDto {
  name: string;
  description?: string;
}
