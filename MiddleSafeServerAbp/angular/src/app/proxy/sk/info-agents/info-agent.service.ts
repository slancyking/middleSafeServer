import type { CreateInfoAgentDto, GetInfoAgentListDto, InfoAgentDto, UpdateInfoAgentDto } from './models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class InfoAgentService {
  apiName = 'Default';
  

  create = (input: CreateInfoAgentDto) =>
    this.restService.request<any, InfoAgentDto>({
      method: 'POST',
      url: '/api/app/info-agent',
      body: input,
    },
    { apiName: this.apiName });
  

  delete = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/info-agent/${id}`,
    },
    { apiName: this.apiName });
  

  get = (id: string) =>
    this.restService.request<any, InfoAgentDto>({
      method: 'GET',
      url: `/api/app/info-agent/${id}`,
    },
    { apiName: this.apiName });
  

  getList = (input: GetInfoAgentListDto) =>
    this.restService.request<any, PagedResultDto<InfoAgentDto>>({
      method: 'GET',
      url: '/api/app/info-agent',
      params: { filter: input.filter, sorting: input.sorting, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });
  

  update = (id: string, input: UpdateInfoAgentDto) =>
    this.restService.request<any, void>({
      method: 'PUT',
      url: `/api/app/info-agent/${id}`,
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
