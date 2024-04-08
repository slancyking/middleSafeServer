import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ErrorCollectComponent } from './error-collect.component';

const routes: Routes = [{ path: '', component: ErrorCollectComponent }];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ErrorCollectRoutingModule { }
