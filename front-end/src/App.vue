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
      sngPage: {"Index":true,"Login":true, "Register": true, "RoadMap": true, "ListSC":true, "ListContext":true, "ListLTL":true, "AddSC":true}
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
#app {
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  height: 100%;
  font-family: -apple-system,BlinkMacSystemFont,"Segoe UI",Helvetica,Arial,sans-serif,"Apple Color Emoji","Segoe UI Emoji";
  line-height: 1.5;
}
</style>
