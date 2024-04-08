
export interface GetFormInputDto {
  name?: string;
}

export interface GetFormOutputDto {
  creationTime?: string;
  name?: string;
  value?: string;
  userId?: string;
}

export interface GetFormsInputDto {
  name?: string;
  maxResult: number;
}
