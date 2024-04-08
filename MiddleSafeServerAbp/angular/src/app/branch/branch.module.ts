import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from '../shared/shared.module';

import { BranchRoutingModule } from './branch-routing.module';
import { BranchComponent } from './branch.component';


@NgModule({
  declarations: [
    BranchComponent
  ],
  imports: [
    CommonModule,
    BranchRoutingModule,
    SharedModule
  ]
})
export class BranchModule { }
