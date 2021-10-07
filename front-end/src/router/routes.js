import Index from "../views/Index.vue";
import Login from "../views/Login.vue"
import Register from "../views/Register.vue"
import SelectSc from "../views/SelectSc.vue"
import SelectContext from "../views/SelectContext.vue"
import InitialMarkingSetting from "../views/InitialMarkingSetting.vue"
import ChooseProperty from "../views/ChooseProperty"

import ListOfCheckedTransactions from "../views/select-sc/transactions/ListOfCheckedTransactions.vue"
import CheckReenTrancyDetail from "../views/select-sc/transactions/CheckReenTrancyDetail.vue"

import SelectSmartContract from "../views/select-sc/smartcontract/SelectSmartContract.vue"
import UpLoadSc from "../views/select-sc/smartcontract/UpLoadSc.vue"

import ContextOfSmartContract from "../views/context/ContextOfSmartContract.vue"
import LoadContext from "../views/context/LoadContext.vue"
import UnFolding from "../views/context/UnFolding.vue"
import UpLoadContext from "../views/context/UpLoadContext.vue"

import LTLCheckingOption from "../views/choose-property/LTLCheckingOption.vue"
import ContractSpecificProperty from "../views/choose-property/CheckContractSpecificProperty/ContractSpecificProperty.vue"
import CSPTemplateSetting from "../views/choose-property/CheckContractSpecificProperty/CSPTemplate/CSPTemplateSetting.vue"
import CheckingSmartContract from "../views/CheckingSmartContract.vue"
import ContractSpecificPropertyNonTemplate from "../views/choose-property/CheckContractSpecificProperty/ContractSpecificPropertyNonTemplate.vue"

import GenaralVulSetting from "../views/choose-property/CheckGeneralVul/GenaralVulSetting.vue"

import ListContext from "../views/context/context-crud/list-context.vue"
import AddContext from "../views/context/context-crud/add-context.vue"
import EditContext from "../views/context/context-crud/edit-context.vue"

import ListSc from "../views/select-sc/smartcontract-crud/list-sc.vue"
import EditSc from "../views/select-sc/smartcontract-crud/edit-sc.vue"
import AddSc from "../views/select-sc/smartcontract-crud/add-sc.vue"

import AddVul from "../views/vuls-crud/add-vul.vue"
import EditVul from "../views/vuls-crud/edit-vul.vue"
import ListVul from "../views/vuls-crud/list-vulnerabilities.vue"

import LTLEditor from "../components/LTL"

import { DOMAIN_TITLE } from '../.env'

export const routes = [
  {
    path: "/",
    name: "Index",
    component: Index,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | home` },
  },
  {
    path: "/LTL",
    name: "LTL",
    component: LTLEditor,
    meta: { requiresAuth: false, title: `${DOMAIN_TITLE} | home` },
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | login` },
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | register` },
  },
  {
    path: "/select-sc/",
    name: "SelectSc",
    component: SelectSc,
    children: [
      {
        path: 'listofcheckedtransactions',
        name: 'ListOfCheckedTransactions',
        component: ListOfCheckedTransactions,
        meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | listofcheckedtransactions` },
      },
      {
        path: 'checkreentrancydetail',
        name: 'CheckRentrancy',
        component: CheckReenTrancyDetail
      },
      {
        path: 'select-smart-contract',
        name: 'SelectSmartContract',
        component: SelectSmartContract
      },
      {
        path: 'uploadsc',
        name: 'UpLoadSc',
        component: UpLoadSc
      },
    ],
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | checkreentrancydetail` },
  },
  {
    path: "/context/",
    name: "SelectContext",
    component: SelectContext,
    children: [
      {
        path: 'context-of-smartcontract',
        name: 'ContextOfSmartContract',
        component: ContextOfSmartContract
      },
      {
        path: 'load-context',
        name: 'LoadContext',
        component: LoadContext
      },
      {
        path: 'unfolding',
        name: 'UnFolding',
        component: UnFolding
      },
      {
        path: 'uploadcontext',
        name: 'UpLoadContext',
        component: UpLoadContext
      }
    ],
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | select context` },
  },
  {
    path: "/choose-property/",
    name: "ChooseProperty",
    component: ChooseProperty,
    children: [
      {
        path: "ltlcheck-option",
        name: "LTLCheckOption",
        component: LTLCheckingOption,
      },
      {
        path: "csp-template-setting",
        name: "CSPTemplateSetting",
        component: CSPTemplateSetting
      },
       {
        path: "csp-setting-types",
        name: "CSPSettingType",
        component: ContractSpecificProperty
      },
      {
        path: "csp-non-template-setting",
        name: "CSPNonTemplateSetting",
        component: ContractSpecificPropertyNonTemplate
      },
      {
        path: "genaral-vul-setting",
        name: "GenaralVulSetting",
        component: GenaralVulSetting
      },
      
    ],
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | choose property` },
  },
  {
    path: "/initialmarking",
    name: "Initial",
    component: InitialMarkingSetting,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Initial` },
  },
  {
    path: "/check-sc",
    name: "CheckSmartContract",
    component: CheckingSmartContract,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Initial` },
  },
  {
    path: "/list-context",
    name: "ListContext",
    component: ListContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | List Of Contexts` },
    props: true
  },
  {
    path: "/list-sc",
    name: "ListSc",
    component: ListSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | list smart contracts` },
  },
  {
    path: "/edit-sc",
    name: "EditSc",
    component: EditSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | edit smart contracts` },
    props: true
  },
  {
    path: "/add-sc",
    name: "AddSc",
    component: AddSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | create smart contracts` },
    props: true
  },
  {
    path: "/add-context",
    name: "AddContext",
    component: AddContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Add a Context` },
    props: true
  },
  {
    path: "/edit-context",
    name: "EditContext",
    component: EditContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Edit Context` },
    props: true
  },
  {
    path: "/list-vul",
    name: "ListVul",
    component: ListVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | List Of Vulnerabilities` },
    props: true
  },
  {
    path: "/add-vul",
    name: "AddVul",
    component: AddVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Add an LTL Vulnerability` },
    props: true
  },
  {
    path: "/edit-vul",
    name: "EditVul",
    component: EditVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Edit an LTL Vulnerability` },
    props: true
  },
]

/*
{
    path: "/list-sc",
    name: "ListSc",
    component: ListSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | list smart contracts` },
  },
  {
    path: "/edit-sc",
    name: "EditSc",
    component: EditSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | edit smart contracts` },
    props: true
  },
  {
    path: "/add-sc",
    name: "AddSc",
    component: AddSc,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | create smart contracts` },
    props: true
  },
  {
    path: "/process",
    name: "Processing",
    component: Processing,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | processing` },
  },
  {
    path: "/create-csp",
    name: "CreateCsp",
    component: CreateCsp,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | create contract-specific property` },
    props: true
  },
  {
    path: "/roadmap",
    name: "RoadMap",
    component: RoadMap,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | RoadMap` },
    props: true
  },
  {
    path: "/add-context",
    name: "AddContext",
    component: AddContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Add a Context` },
    props: true
  },
  {
    path: "/edit-context",
    name: "EditContext",
    component: EditContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Edit Context` },
    props: true
  },
  {
    path: "/list-context",
    name: "ListContext",
    component: ListContext,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | List Of Contexts` },
    props: true
  },
  {
    path: "/list-vul",
    name: "ListVul",
    component: ListVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | List Of Vulnerabilities` },
    props: true
  },
  {
    path: "/add-vul",
    name: "AddVul",
    component: AddVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Add an LTL Vulnerability` },
    props: true
  },
  {
    path: "/edit-vul",
    name: "EditVul",
    component: EditVul,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | Edit an LTL Vulnerability` },
    props: true
  },
*/