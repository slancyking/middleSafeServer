import type { GetFormInputDto, GetFormOutputDto, GetFormsInputDto } from './dto/models';
import { RestService } from '@abp/ng.core';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class FormService {
  apiName = 'Default';
  

  getFormInfoListByInput = (input: GetFormsInputDto) =>
    this.restService.request<any, GetFormOutputDto[]>({
      method: 'GET',
      url: '/api/app/form/form-info-list',
      params: { name: input.name, maxResult: input.maxResult },
    },
    { apiName: this.apiName });
  

  getLastFormInfoByInput = (input: GetFormInputDto) =>
    this.restService.request<any, GetFormOutputDto>({
      method: 'GET',
      url: '/api/app/form/last-form-info',
      params: { name: input.name },
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
