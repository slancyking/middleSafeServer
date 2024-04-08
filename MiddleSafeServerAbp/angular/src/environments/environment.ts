import { Environment } from '@abp/ng.core';

const baseUrl = 'http://mss.d4d.top:4200';

export const environment = {
  localization: {
    defaultResourceName: 'middleSafeServer',
  },
  production: false,
  application: {
    baseUrl,
    name: 'middleSafeServer',
    logoUrl: '',
  },
  oAuthConfig: {
    issuer: 'http://mss.d4d.top:44367',
    redirectUri: baseUrl,
    clientId: 'middleSafeServer_App',
    responseType: 'code',
    scope: 'offline_access middleSafeServer',
    requireHttps: false
  },
  apis: {
    default: {
      url: 'http://mss.d4d.top:44367',
      rootNamespace: 'middleSafeServer',
    },
  },
} as Environment;
