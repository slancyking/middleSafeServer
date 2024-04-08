import { PagedResultDto, RestService } from "@abp/ng.core";
import { Injectable } from "@angular/core";
import { BranchService,BranchDto,GetBranchListDto } from "@proxy/sk/branchs/index";
import { CardDto } from "@proxy/sk/cards/index";
import { Observable } from "rxjs";

export interface ClientBranchDto extends BranchDto {
    projectName?: string;
}


export interface ClientCardDto extends CardDto {
    check?: boolean;
}

