<template>
    <div>
        <road-map/>
        <div id="main-view">
            <router-view></router-view>
        </div>
    </div>
</template>

<script>
import RoadMap from "../components/RoadMap.vue"
export default {
  components: {"road-map":RoadMap},
  data() {
    return {
    };
  }
};
</script>

<style>
#main-view{
  position: absolute;
  margin-top: 90px;
  width: 100%;
  min-width: 900px;
}
</style>