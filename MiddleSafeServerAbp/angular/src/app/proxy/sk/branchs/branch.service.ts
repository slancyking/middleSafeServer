import type { BranchDto, CreateBranchDto, GetBranchListDto, UpdateBranchDto } from './models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class BranchService {
  apiName = 'Default';
  

  create = (input: CreateBranchDto) =>
    this.restService.request<any, BranchDto>({
      method: 'POST',
      url: '/api/app/branch',
      body: input,
    },
    { apiName: this.apiName });
  

  delete = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/branch/${id}`,
    },
    { apiName: this.apiName });
  

  get = (id: string) =>
    this.restService.request<any, BranchDto>({
      method: 'GET',
      url: `/api/app/branch/${id}`,
    },
    { apiName: this.apiName });
  

  getList = (input: GetBranchListDto) =>
    this.restService.request<any, PagedResultDto<BranchDto>>({
      method: 'GET',
      url: '/api/app/branch',
      params: { _projectId: input._projectId, filter: input.filter, sorting: input.sorting, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });
  

  update = (id: string, input: UpdateBranchDto) =>
    this.restService.request<any, void>({
      method: 'PUT',
      url: `/api/app/branch/${id}`,
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
