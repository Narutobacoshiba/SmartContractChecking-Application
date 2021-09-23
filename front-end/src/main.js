import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";
import sha256 from 'crypto-js/sha256';
import VueCookies from 'vue-cookies'

Vue.config.productionTip = false;

Vue.mixin({
  methods: {
    hashValue: function (value) {
      return sha256(value)
    }
  },
})

VueCookies.config("90d")
Vue.use(VueCookies)

new Vue({
  store,
  router,
  render: (h) => h(App),
  beforeMount(){
    window.addEventListener("beforeunload", () => {
      var current_user_id = store.state.user.currentUser.id
      var current_date = Date.now()
      if(current_user_id && store.state.data.used){
        var state = store.state.data
        this.$cookies.set("_dt"+current_user_id,JSON.stringify({"date_modified":current_date,"version":state.version,"views":state.views,"data":state.data}))
      }
    })
  }
}).$mount("#app");
