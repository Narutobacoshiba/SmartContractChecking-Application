import Index from "../views/Index.vue";
import Login from "../views/Login.vue"
import Register from "../views/Register.vue"

import CheckedSCList from "../views/CheckedSCList.vue"

import CheckVunerabilities from "../views/Check-Vulnerabilities.vue"
import SmartContractSelection from "../views/select-smart-contract/smart-contract-selection.vue"

import ContextSelection from "../views/select-context/context-selection.vue"
import UploadContext from "../views/select-context/upload-context.vue"

import LtlCheckingOptions from "../views/choose-property/ltl-checking-options.vue"
import CSPSettingChooseType from "../views/choose-property/csp-setting-choosetype.vue"
import CSPSettingNonTemp from "../views/choose-property/csp-setting-nontemp.vue"
import CSPPropertyTemp from "../views/choose-property/csp-property-temp.vue"
import GeneralVulSetting from "../views/choose-property/general-vul-setting.vue"

import InitialMarkingSetting from "../views/InitialMarkingSetting.vue"

import GenerateCPNModel from "../views/Generate-CPN-Model.vue"

import CheckCPNModel from "../views/Check-CPN-Model.vue"

import CheckingResult from "../views/Checking-Result.vue"

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
        path: '',
        name: 'CheckedSCList',
        component: CheckedSCList
      },
      {
        path: 'start',
        name: 'CheckedSCList',
        component: CheckedSCList
      },
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
        path: 'choose-type',
        name: 'CSPSettingChooseType',
        component: CSPSettingChooseType
      },
      {
        path: 'csp-setting-nontemp',
        name: 'CSPSettingNonTemp',
        component: CSPSettingNonTemp
      },
      {
        path: 'csp-property-template',
        name: 'CSPPropertyTemp',
        component: CSPPropertyTemp
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
      },
      {
        path: 'generate-cpn-model',
        name: 'GenerateCPNModel',
        component: GenerateCPNModel
      },
      {
        path: 'checking-cpn-model',
        name: 'CheckCPNModel',
        component: CheckCPNModel
      },
      {
        path: 'checking-result',
        name: 'CheckingResult',
        component: CheckingResult
      }
    ],
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | check-vulnerabilities` },
  },
]