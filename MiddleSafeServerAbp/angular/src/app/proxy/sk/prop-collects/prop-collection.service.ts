import type { CreatePropCollectionInput, PropProjectOutputDto, QueryDetailInput, QueryDetailOutput, QueryEveryDayInput, QueryEveryDayOutput, QueryProjectTableInputDto } from './dto/models';
import { RestService } from '@abp/ng.core';
import type { PagedResultDto } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardCommonOutputDto } from '../cards/models';
import type { CardClientInputDto, CardClientOuputDto } from '../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class PropCollectionService {
  apiName = 'Default';
  

  createSyncByInput = (input: CardClientInputDto<CreatePropCollectionInput>) =>
    this.restService.request<any, CardClientOuputDto<CardCommonOutputDto>>({
      method: 'POST',
      url: '/api/app/prop-collection/sync',
      body: input,
    },
    { apiName: this.apiName });
  

  getProjectTableinfoByInput = (input: QueryProjectTableInputDto) =>
    this.restService.request<any, PropProjectOutputDto[]>({
      method: 'GET',
      url: '/api/app/prop-collection/project-tableinfo',
      params: { branchId: input.branchId, queryStartTime: input.queryStartTime, queryEndTime: input.queryEndTime, projectIdContain: input.projectIdContain, projectIdFilter: input.projectIdFilter, branchIdContain: input.branchIdContain, branchIdFilter: input.branchIdFilter, propContain: input.propContain, propFilter: input.propFilter, cardIdContains: input.cardIdContains, cardIdFilter: input.cardIdFilter },
    },
    { apiName: this.apiName });
  

  queryByEveryDayByInput = (input: QueryEveryDayInput) =>
    this.restService.request<any, PagedResultDto<QueryEveryDayOutput>>({
      method: 'POST',
      url: '/api/app/prop-collection/query-by-every-day',
      body: input,
    },
    { apiName: this.apiName });
  

  queryPropListByInput = (input: QueryDetailInput) =>
    this.restService.request<any, PagedResultDto<QueryDetailOutput>>({
      method: 'POST',
      url: '/api/app/prop-collection/query-prop-list',
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
