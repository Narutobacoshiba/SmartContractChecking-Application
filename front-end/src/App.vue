<template>
  <div id="app">
    <NavBar v-if="showNavigationBar"/>
    <router-view />
  </div>
</template>

<script>
import NavBar from "./components/NavBar.vue"
// @ is an alias to /src
export default {
  components: {NavBar},
  data(){
    return{
      sngPage: {"Index":true,"ListSc":true, "RoadMap": true}
    }
  },
  computed: {
    showNavigationBar(){
      if(this.$route.name in this.sngPage){
        return true
      }
      return false
    }
  }
};
</script>

<style>
*{
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
