<template>
  <div id="app">
    <NavBar v-if="showNavigationBar" />
    <router-view />
    <div v-for="i in per" :key="i.id">
      {{i.name}}
    </div>
  </div>
</template>

<script>
import NavBar from "./components/NavBar.vue";
import { GetDataSmartContact } from "../src/services/data";
// @ is an alias to /src
export default {
  components: { NavBar },
  data() {
    return {
      sngPage: { Index: true, ListSc: true },
      per: [],
    };
  },
  computed: {
    showNavigationBar() {
      if (this.$route.name in this.sngPage) {
        return true;
      }
      return false;
    },
  },
  mounted() {
    // axios.get(`/json`).then((response) => {
    //   this.per = response.data;
    // });
    this.per = GetDataSmartContact();
  },
};
</script>

<style>
* {
  -webkit-user-select: none;
  -khtml-user-select: none;
  -o-user-select: none;
  user-select: none;
}
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  height: 100%;
}
</style>
