import type { CreateManyNameCollectDto, CreateManyNameCollectOutputDto, CreateNameCollectDto, GetNameCollectListDto, GetRandomNameCollectInputDto, GetRandomNameCollectOutputDto, NameCollectDto, UpdateNameCollectDto } from './models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardClientInputDto, CardClientOuputDto } from '../../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class NameCollectService {
  apiName = 'Default';
  

  create = (input: CreateNameCollectDto) =>
    this.restService.request<any, NameCollectDto>({
      method: 'POST',
      url: '/api/app/name-collect',
      body: input,
    },
    { apiName: this.apiName });
  

  createMany = (input: CardClientInputDto<CreateManyNameCollectDto>) =>
    this.restService.request<any, CardClientOuputDto<CreateManyNameCollectOutputDto>>({
      method: 'POST',
      url: '/api/app/name-collect/many',
      body: input,
    },
    { apiName: this.apiName });
  

  delete = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/name-collect/${id}`,
    },
    { apiName: this.apiName });
  

  get = (id: string) =>
    this.restService.request<any, NameCollectDto>({
      method: 'GET',
      url: `/api/app/name-collect/${id}`,
    },
    { apiName: this.apiName });
  

  getList = (input: GetNameCollectListDto) =>
    this.restService.request<any, PagedResultDto<NameCollectDto>>({
      method: 'GET',
      url: '/api/app/name-collect',
      params: { filter: input.filter, infoAgentId: input.infoAgentId, sorting: input.sorting, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });
  

  getRandomNameCollectByInput = (input: CardClientInputDto<GetRandomNameCollectInputDto>) =>
    this.restService.request<any, CardClientOuputDto<GetRandomNameCollectOutputDto>>({
      method: 'GET',
      url: '/api/app/name-collect/random-name-collect',
      params: { password: input.password, param: input.param },
    },
    { apiName: this.apiName });
  

  update = (id: string, input: UpdateNameCollectDto) =>
    this.restService.request<any, void>({
      method: 'PUT',
      url: `/api/app/name-collect/${id}`,
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
