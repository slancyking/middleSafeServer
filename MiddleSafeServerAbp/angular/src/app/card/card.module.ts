import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { CardRoutingModule } from './card-routing.module';
import { CardComponent } from './card.component';
import { SharedModule } from '../shared/shared.module';

import { NgbDatepickerModule, NgbCollapse } from '@ng-bootstrap/ng-bootstrap';

@NgModule({
  declarations: [
    CardComponent
  ],
  imports: [ 
    CommonModule,
    CardRoutingModule,
    SharedModule,
    NgbDatepickerModule
  ]
})
export class CardModule { }
