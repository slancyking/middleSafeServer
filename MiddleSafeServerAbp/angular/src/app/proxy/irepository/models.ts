
export interface QueryPropCollectInputCommon {
  branchId?: string;
  queryStartTime?: string;
  queryEndTime?: string;
  projectIdContain: string[];
  projectIdFilter: string[];
  branchIdContain: string[];
  branchIdFilter: string[];
  propContain: string[];
  propFilter: string[];
  cardIdContains: string[];
  cardIdFilter: string[];
}
