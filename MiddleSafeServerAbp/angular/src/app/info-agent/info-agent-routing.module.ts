import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { InfoAgentComponent } from './info-agent.component';

const routes: Routes = [{ path: '', component: InfoAgentComponent }];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class InfoAgentRoutingModule { }
