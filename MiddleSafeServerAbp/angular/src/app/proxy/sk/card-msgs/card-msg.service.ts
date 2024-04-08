import type { CardMsgInputDto, CardMsgOutputDto } from './dto/models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class CardMsgService {
  apiName = 'Default';
  

  deleteByIdsByMsgIds = (MsgIds: string[]) =>
    this.restService.request<any, void>({
      method: 'DELETE',
      url: '/api/app/card-msg/by-ids',
      params: { msgIds: MsgIds },
    },
    { apiName: this.apiName });
  

  getMsgListByInput = (input: CardMsgInputDto) =>
    this.restService.request<any, PagedResultDto<CardMsgOutputDto>>({
      method: 'GET',
      url: '/api/app/card-msg/msg-list',
      params: { msgFilter: input.msgFilter, skipCount: input.skipCount, maxResultCount: input.maxResultCount },
    },
    { apiName: this.apiName });
  

  setReadByIdsByMsgIds = (MsgIds: string[]) =>
    this.restService.request<any, void>({
      method: 'POST',
      url: '/api/app/card-msg/set-read-by-ids',
      body: MsgIds,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
