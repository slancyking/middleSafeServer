import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { NameCollectRoutingModule } from './name-collect-routing.module';
import { NameCollectComponent } from './name-collect.component';
import { SharedModule } from '../shared/shared.module';


@NgModule({
  declarations: [
    NameCollectComponent
  ],
  imports: [
    CommonModule,
    NameCollectRoutingModule,
    SharedModule
  ]
})
export class NameCollectModule { }
