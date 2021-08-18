import Index from "../views/Index.vue";
import ListSc from "../views/List-sc.vue"
import EditSc from "../views/Edit-Sc.vue"
import AddSc from "../views/Add-Sc.vue"
import Processing from "../views/Processing.vue"
import CreateCsp from "../views/Create-Csp.vue"
import RoadMap from "../views/RoadMap.vue"
import { DOMAIN_TITLE } from '../.env'

export const routes = [
  {
    path: "/",
    name: "Index",
    component: Index,
    meta: { requiresAuth: true, title: `${DOMAIN_TITLE} | home` },
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
]