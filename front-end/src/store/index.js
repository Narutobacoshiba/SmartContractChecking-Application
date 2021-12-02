import Vue from 'vue'
import Vuex from 'vuex'
import modules from './modules'
import createPersistedState from "vuex-persistedstate"; 
/* import * as Cookies from 'js-cookie' */
Vue.use(Vuex)

export default new Vuex.Store({
  modules,
  plugins: [createPersistedState(/* {
      getState: (key) => Cookies.get(key),
      setState: (key, state) => Cookies.set(key, state, { expires: 30, secure: true })
    } */)]
})
