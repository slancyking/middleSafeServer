import type { GetWebSettingOutputDto, UpdateWebSettingInputDto } from './models';
import { RestService } from '@abp/ng.core';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class WebSettingService {
  apiName = 'Default';
  

  getWebSettingDef = () =>
    this.restService.request<any, GetWebSettingOutputDto>({
      method: 'GET',
      url: '/api/app/web-setting/web-setting-def',
    },
    { apiName: this.apiName });
  

  updateWebSettingByIdAndInput = (id: string, input: UpdateWebSettingInputDto) =>
    this.restService.request<any, void>({
      method: 'PUT',
      url: `/api/app/web-setting/${id}/web-setting`,
      body: input,
    },
    { apiName: this.apiName });

  constructor(private restService: RestService) {}
}
