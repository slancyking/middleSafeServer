import type { EntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';

export interface BranchDto extends EntityDto<string> {
  projectId?: string;
  creationTime?: string;
  isOpen: boolean;
  name?: string;
  remark?: string;
}

export interface CreateBranchDto {
  name: string;
  projectId: string;
  isOpen: boolean;
  remark?: string;
}

export interface GetBranchListDto extends PagedAndSortedResultRequestDto {
  _projectId?: string;
  filter?: string;
}

export interface UpdateBranchDto {
  projectId: string;
  name: string;
  remark?: string;
}
