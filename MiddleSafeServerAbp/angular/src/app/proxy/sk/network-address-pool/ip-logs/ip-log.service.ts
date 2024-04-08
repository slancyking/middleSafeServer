import type { IpLogInputDto, IpLogInputOutputDto } from './models';
import { RestService } from '@abp/ng.core';
import { Injectable } from '@angular/core';
import type { CardClientInputDto, CardClientOuputDto } from '../../common-dto/models';

@Injectable({
  providedIn: 'root',
})
export class IpLogService {
  apiName = 'Default';
  

  tryUseIpByInput = (input: CardClientInputDto<IpLogInputDto>) =>
    this.restService.request<any, CardClientOuputDto<IpLogInputOutputDto>>({
      method: 'POST',
      url: '/api/app/ip-log/try-use-ip',
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
