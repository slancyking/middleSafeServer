import type { MiddleNomalQueryInputDto, MiddleNomalQueryOutputDto, MiddleReportInputDto, MiddleReportOutputDto } from './models';
import { RestService } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardClientInputDto, CardClientOuputDto } from '../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class MiddleReportService {
  apiName = 'Default';
  

  normalQuery = (input: CardClientInputDto<MiddleNomalQueryInputDto>) =>
    this.restService.request<any, CardClientOuputDto<MiddleNomalQueryOutputDto>>({
      method: 'POST',
      url: '/api/app/middle-report/normal-query',
      body: input,
    },
    { apiName: this.apiName });
  

  normalReport = (input: CardClientInputDto<MiddleReportInputDto>) =>
    this.restService.request<any, CardClientOuputDto<MiddleReportOutputDto>>({
      method: 'POST',
      url: '/api/app/middle-report/normal-report',
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
