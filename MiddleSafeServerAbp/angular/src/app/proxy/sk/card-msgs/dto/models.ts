
export interface CardMsgInputDto {
  msgFilter?: string;
  skipCount: number;
  maxResultCount: number;
}

export interface CardMsgOutputDto {
  id?: string;
  creationTime?: string;
  personalCardId?: string;
  cardPassword?: string;
  cardRemark?: string;
  isRead: boolean;
  info?: string;
}
