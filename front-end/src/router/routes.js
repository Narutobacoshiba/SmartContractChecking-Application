import Index from "../views/Index.vue";
import ListSc from "../views/List-sc.vue"
import EditSc from "../views/Edit-Sc.vue"
import AddSc from "../views/Add-Sc.vue"
import Processing from "../views/Processing.vue"
import CreateCsp from "../views/Create-Csp.vue"
import RoadMap from "../views/RoadMap.vue"
import Login from "../views/Login.vue"
import Register from "../views/Register.vue"
import AddContext from "../views/context-crud/add-context.vue"
import EditContext from "../views/context-crud/edit-context.vue"
import ListContext from "../views/context-crud/list-context.vue"
import AddVul from "../views/vuls-crud/add-vul.vue"
import EditVul from "../views/vuls-crud/edit-vul.vue"
import ListVul from "../views/vuls-crud/list-vulnerabilities.vue"
import { DOMAIN_TITLE } from '../.env'

export const routes = [
  {
    path: "/",
    name: "Index",
    component: Index,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | home` },
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
]