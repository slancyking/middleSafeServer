import type { CardCommonOutputDto, CardDto, CardLoginInputDto, CardLoginOutpuDto, CardLogoutDto, CardPauseDto, CardPingDto, CardSetTitleDto, CreateCardDto, GetCardListDto, ImportCardInputDto, ImportCardOutputDto, UpdateCardDto } from './models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardClientInputDto, CardClientOuputDto } from '../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class CardService {
  apiName = 'Default';
  

  clearLoginStatusById = (id: string) =>
    this.restService.request<any, void>({
      method: 'POST',
      url: `/api/app/card/${id}/clear-login-status`,
    },
    { apiName: this.apiName });
  

  create = (input: CreateCardDto) =>
    this.restService.request<any, void>({
      method: 'POST',
      url: '/api/app/card',
      body: input,
    },
    { apiName: this.apiName });
  

  delete = (id: string) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: `/api/app/card/${id}`,
    },
    { apiName: this.apiName });
  

  get = (id: string) =>
    this.restService.request<any, CardDto>({
      method: 'GET',
      url: `/api/app/card/${id}`,
    },
    { apiName: this.apiName });
  

  getList = (input: GetCardListDto) =>
    this.restService.request<any, PagedResultDto<CardDto>>({
      method: 'GET',
      url: '/api/app/card',
      params: { filter: input.filter, creatorId: input.creatorId, branchId: input.branchId, mail: input.mail, phone: input.phone, sorting: input.sorting, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });
  

  importCard = (input: ImportCardInputDto[]) =>
    this.restService.request<any, ImportCardOutputDto>({
      method: 'POST',
      url: '/api/app/card/import-card',
      body: input,
    },
    { apiName: this.apiName });
  

  login = (input: CardLoginInputDto) =>
    this.restService.request<any, CardLoginOutpuDto>({
      method: 'POST',
      url: '/api/app/card/login',
      body: input,
    },
    { apiName: this.apiName });
  

  logout = (input: CardClientInputDto<CardLogoutDto>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/card/logout',
      body: input,
    },
    { apiName: this.apiName });
  

  pause = (input: CardClientInputDto<CardPauseDto>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/card/pause',
      body: input,
    },
    { apiName: this.apiName });
  

  ping = (input: CardClientInputDto<CardPingDto>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/card/ping',
      body: input,
    },
    { apiName: this.apiName });
  

  setTitleByInput = (input: CardClientInputDto<CardSetTitleDto>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/card/set-title',
      body: input,
    },
    { apiName: this.apiName });
  

  update = (id: string, input: UpdateCardDto) =>
    this.restService.request<any, void>({
      method: 'PUT',
      url: `/api/app/card/${id}`,
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
