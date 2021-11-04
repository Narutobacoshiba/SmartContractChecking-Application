import Index from "../views/Index.vue";
import Login from "../views/Login.vue"
import Register from "../views/Register.vue"

import CheckVunerabilities from "../views/Check-Vulnerabilities.vue"
import SmartContractSelection from "../views/select-smart-contract/smart-contract-selection.vue"

import ContextSelection from "../views/select-context/context-selection.vue"
import UploadContext from "../views/select-context/upload-context.vue"

import LtlCheckingOptions from "../views/choose-property/ltl-checking-options.vue"
import CSPSettingNonTemp from "../views/choose-property/csp-setting-nontemp.vue"
import GeneralVulSetting from "../views/choose-property/general-vul-setting.vue"

import InitialMarkingSetting from "../views/InitialMarkingSetting.vue"

import { DOMAIN_TITLE } from '../.env'

export const routes = [
  {
    path: "/",
    name: "Index",
    component: Index,
    meta: { requiresAuth: false, title: `${DOMAIN_TITLE} | home` },
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: { requiresAuth: false, title: `${DOMAIN_TITLE} | login` },
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: { requiresAuth: false, title: `${DOMAIN_TITLE} | register` },
  },
  {
    path: "/check-vulnerabilities/",
    name: "CheckVulnerabilities",
    component: CheckVunerabilities,
    children: [
      {
        path: 'select-smart-contract',
        name: 'SmartContractSelection',
        component: SmartContractSelection
      },
      {
        path: 'select-context',
        name: 'ContextSelection',
        component: ContextSelection
      },
      {
        path: 'upload-context',
        name: 'UploadContext',
        component: UploadContext
      },
      {
        path: 'ltl-formula',
        name: 'LtlCheckingOptions',
        component: LtlCheckingOptions
      },
      {
        path: 'csp-setting-nontemp',
        name: 'CSPSettingNonTemp',
        component: CSPSettingNonTemp
      },
      {
        path: 'general-vulnerabilities-setting',
        name: 'GeneralVulSetting',
        component: GeneralVulSetting
      },
      {
        path: 'initial-marking',
        name: 'InitialMarkingSetting',
        component: InitialMarkingSetting
      }
    ],
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | check-vulnerabilities` },
  },
]