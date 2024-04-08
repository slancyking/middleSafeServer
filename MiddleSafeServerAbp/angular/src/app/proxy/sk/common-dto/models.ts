
export interface CardClientRequstBase {
  postUnix: number;
}

export interface CardClientInputDto<T> {
  password: string;
  param: string;
}

export interface CardClientOuputDto<T> {
  result?: string;
}
