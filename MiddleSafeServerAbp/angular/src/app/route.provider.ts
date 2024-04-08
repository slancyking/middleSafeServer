import { RoutesService, eLayoutType } from '@abp/ng.core';
import { APP_INITIALIZER } from '@angular/core';

export const APP_ROUTE_PROVIDER = [
  { provide: APP_INITIALIZER, useFactory: configureRoutes, deps: [RoutesService], multi: true },
];

function configureRoutes(routesService: RoutesService) {
  return () => {
    routesService.add([
      {
        path: '/',
        name: '::Menu:Home',
        iconClass: 'fas fa-home',
        order: 1,
        layout: eLayoutType.application,
      },
      {
        path: '',
        name: '::Menu:ProjectManagers',
        iconClass: 'fas fa-book',
        order: 2,
        layout: eLayoutType.application,
      },
      {
        path: '/projects',
        name: '::Menu:Projects',
        parentName: '::Menu:ProjectManagers',
        layout: eLayoutType.application,
      },
      {
        path: '/branchs',
        name: '::Menu:Branchs',
        parentName: '::Menu:ProjectManagers',
        layout: eLayoutType.application,
      },
      {
        path: '/',
        name: '::Menu:InfoCollect',
        iconClass: 'fas  fa-eye',
        order: 3,
        layout: eLayoutType.application,
      },
      {
        path: '/infoAgents',
        name: '::Menu:InfoAgents',
        parentName: '::Menu:InfoCollect',
        layout: eLayoutType.application,
      },
      {
        path: '/name-collects',
        name: '::Menu:nameCollect',
        parentName: '::Menu:InfoCollect',
        layout: eLayoutType.application,
      },
      {
        path: '/error-collects',
        name: '::Menu:ErrorCollects',
        iconClass: 'fas fa-ambulance',
        order: 4,
        layout: eLayoutType.application,
      },

    ]);
  };
}
