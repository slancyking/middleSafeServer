import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { NameCollectComponent } from './name-collect.component';

const routes: Routes = [{ path: '', component: NameCollectComponent }];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class NameCollectRoutingModule { }
