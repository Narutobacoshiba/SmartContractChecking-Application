<template>
    <div id="process-body">
        <div id="roadmap">
            <RoadMap />
        </div>
        <div id="main-area">
            <ScSelection v-if="chosenViews == 'sc-selection'"/>
            <ChooseVul v-if="chosenViews == 'choose-vul'"/>
            <SelectContext v-if="chosenViews == 'select-context'"/>
            <GenerateSC v-if="chosenViewNum >= 4"/>
        </div>
    </div>
</template>

<script>
import RoadMap from "../components/RoadMap.vue";

import ScSelection from "./processing/sc-selection.vue"
import ChooseVul from "./processing/choose-vulnerability.vue"
import SelectContext from "./processing/select-context.vue"
import GenerateSC from "./processing/generate-sc.vue"
export default ({
    components: {RoadMap,ScSelection,ChooseVul, SelectContext, GenerateSC},
    computed: {
        chosenViews(){
            var id = this.pages.filter(item => {
            return item.view == this.$store.getters["data/GetProcessView"];
            })[0].id
            
            this.$store.commit("data/SetCurrentPage",id)
            if(id > this.$store.getters["data/GetRoadPage"]){
                this.$store.commit("data/SetRoadPage",id)
            }
            return this.$store.getters["data/GetProcessView"]
        }, 
        chosenViewNum(){
            var id = this.pages.filter(item => {
            return item.view == this.$store.getters["data/GetProcessView"];
            })[0].id
            this.$store.commit("data/SetCurrentPage",id)
            if(id > this.$store.getters["data/GetRoadPage"]){
                this.$store.commit("data/SetRoadPage",id)
            }
            return id
        }
    }, 
    data(){
        return{
            pages: [
                    { id: 1, name: "Select Smart Contracts", view: "sc-selection"},
                    { id: 2, name: "Select Context", view: "select-context"},
                    { id: 3, name: "Choose Vulnerabilities", view: "choose-vul"},
                    { id: 4, name: "Generate SC to CPN",view: "generate-sc2cpn"},
                    { id: 5, name: "Check the SCs",view: "check-sc" },
                    { id: 6, name: "Finish",view: "finish"},
                ],
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
