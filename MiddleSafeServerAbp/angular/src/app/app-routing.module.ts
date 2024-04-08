import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    loadChildren: () => import('./home/home.module').then(m => m.HomeModule),
  },
  {
    path: 'account',
    loadChildren: () => import('@abp/ng.account').then(m => m.AccountModule.forLazy()),
  },
  {
    path: 'identity',
    loadChildren: () => import('@abp/ng.identity').then(m => m.IdentityModule.forLazy()),
  },
  {
    path: 'tenant-management',
    loadChildren: () =>
      import('@abp/ng.tenant-management').then(m => m.TenantManagementModule.forLazy()),
  },
  {
    path: 'setting-management',
    loadChildren: () =>
      import('@abp/ng.setting-management').then(m => m.SettingManagementModule.forLazy()),
  },
  { path: 'projects', loadChildren: () => import('./project/project.module').then(m => m.ProjectModule) },
  { path: 'branchs', loadChildren: () => import('./branch/branch.module').then(m => m.BranchModule) },
  { path: 'cards', loadChildren: () => import('./card/card.module').then(m => m.CardModule) },
  { path: 'infoAgents', loadChildren: () => import('./info-agent/info-agent.module').then(m => m.InfoAgentModule) },
  { path: 'error-collects', loadChildren: () => import('./error-collect/error-collect.module').then(m => m.ErrorCollectModule) },
  { path: 'name-collects', loadChildren: () => import('./name-collect/name-collect.module').then(m => m.NameCollectModule) },
];

@NgModule({
  imports: [RouterModule.forRoot(routes, { relativeLinkResolution: 'legacy' })],
  exports: [RouterModule],
})
export class AppRoutingModule {}
