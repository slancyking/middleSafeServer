import type { AuditedEntityDto, PagedAndSortedResultRequestDto } from '@abp/ng.core';

export interface CreateProjectDto {
  name: string;
  ipMaxUserCount: number;
  remark?: string;
}

export interface GetProjectListDto extends PagedAndSortedResultRequestDto {
  filter?: string;
}

export interface ProjectDto extends AuditedEntityDto<string> {
  name?: string;
  ipMaxUserCount: number;
  remark?: string;
}

export interface UpdateProjectDto {
  name: string;
  ipMaxUserCount: number;
  remark?: string;
}
