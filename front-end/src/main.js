import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";
/* import sha256 from 'crypto-js/sha256'; */
import VueCookies from 'vue-cookies'

Vue.config.productionTip = false;


VueCookies.config("90d")
Vue.use(VueCookies)

new Vue({
  store,
  router,
  render: (h) => h(App),
}).$mount("#app");
