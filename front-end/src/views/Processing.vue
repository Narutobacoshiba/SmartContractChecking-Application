<template>
    <div id="process-body">
        <div id="roadmap">
            <RoadMap />
        </div>
        <div id="main-area">
            <ScSelection v-if="chosenViews == 'sc-selection'"/>
            <ChooseVul v-if="chosenViews == 'choose-vul'"/>
        </div>
    </div>
</template>

<script>
import RoadMap from "../components/RoadMap.vue";

import ScSelection from "./processing/sc-selection.vue"
import ChooseVul from "./processing/choose-vulnerability.vue"

export default ({
    components: {RoadMap,ScSelection,ChooseVul},
    computed: {
        chosenViews(){
            return this.$store.getters["data/GetProcessView"]
        }
    }
})
</script>

<style scoped>
#process-body{
    width: 100%;
    height: 100%;
    min-width: 1000px;
}
#main-area{
    height: calc(100% - 90px);
}
</style>
