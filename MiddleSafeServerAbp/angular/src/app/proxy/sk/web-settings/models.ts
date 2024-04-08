import type { EntityDto } from '@abp/ng.core';

export interface GetWebSettingOutputDto extends EntityDto<string> {
  isMailReportDrop: boolean;
  isMailReportServiceResource: boolean;
  mailListForServiceResource: string[];
  isSmsReportDrop: boolean;
  isSmsReportServiceResource: boolean;
  phoneNumForServiceResource: string[];
}

export interface UpdateWebSettingInputDto {
  isMailReportDrop: boolean;
  isMailReportServiceResource: boolean;
  mailListForServiceResource?: string;
  isSmsReportDrop: boolean;
  isSmsReportServiceResource: boolean;
  phoneNumForServiceResource?: string;
}
