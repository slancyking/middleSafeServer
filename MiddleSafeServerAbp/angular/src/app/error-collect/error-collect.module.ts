import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ErrorCollectRoutingModule } from './error-collect-routing.module';
import { ErrorCollectComponent } from './error-collect.component';
import { SharedModule } from '../shared/shared.module';

@NgModule({
  declarations: [
    ErrorCollectComponent
  ],
  imports: [
    CommonModule,
    SharedModule,
    ErrorCollectRoutingModule
  ]
})
export class ErrorCollectModule { }
