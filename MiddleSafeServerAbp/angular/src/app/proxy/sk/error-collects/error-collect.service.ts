import type { CreateErrorCollectInputDto, ErrorCollectDto, GetErrorCollectListDto } from './models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardCommonOutputDto } from '../cards/models';
import type { CardClientInputDto, CardClientOuputDto } from '../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class ErrorCollectService {
  apiName = 'Default';
  

  clientErrorCollect = (input: CardClientInputDto<CreateErrorCollectInputDto>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/error-collect/client-error-collect',
      body: input,
    },
    { apiName: this.apiName });
  

  delete = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/error-collect/${id}`,
    },
    { apiName: this.apiName });
  

  deleteSameErrorMessageById = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/error-collect/${id}/same-error-message`,
    },
    { apiName: this.apiName });
  

  get = (id: string) =>
    this.restService.request<any, ErrorCollectDto>({
      method: 'GET',
      url: `/api/app/error-collect/${id}`,
    },
    { apiName: this.apiName });
  

  getList = (input: GetErrorCollectListDto) =>
    this.restService.request<any, PagedResultDto<ErrorCollectDto>>({
      method: 'GET',
      url: '/api/app/error-collect',
      params: { branchId: input.branchId, errorTitle: input.errorTitle, errorMessage: input.errorMessage, sorting: input.sorting, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
