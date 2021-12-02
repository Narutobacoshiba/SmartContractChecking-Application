import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";
import sha256 from 'crypto-js/sha256';

Vue.config.productionTip = false;

Vue.mixin({
  methods: {
    hashValue: function (value) {
      return sha256(value).toString()
    }
  },
})

new Vue({
  store,
  router,
  render: (h) => h(App),
}).$mount("#app");
