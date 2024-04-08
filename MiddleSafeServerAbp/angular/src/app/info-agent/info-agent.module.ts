import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from '../shared/shared.module';

import { InfoAgentRoutingModule } from './info-agent-routing.module';
import { InfoAgentComponent } from './info-agent.component';


@NgModule({
  declarations: [
    InfoAgentComponent
  ],
  imports: [
    CommonModule,
    InfoAgentRoutingModule,
    SharedModule
  ]
})
export class InfoAgentModule { }
