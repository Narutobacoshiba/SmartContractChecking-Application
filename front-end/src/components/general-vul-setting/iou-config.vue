<template>
    <div id="iot-container">
        <div id="outc-set-limmit">
            <div class="outc-limmit-sec">
                <div>MinThreshold</div>
                <input type="text" v-model="sdata.min_threshold">
            </div>
            <div class="outc-limmit-sec">
                <div>MaxThreshold</div>
                <input type="text" v-model="sdata.max_threshold">
            </div>
        </div>

        <div id="outc-select-var">
            <VariableTable :selectValue="sdata.selected_variable" @changeValue="changeValue"/>
        </div>
    </div>
</template>

<script>
import VariableTable from "../smart-contract-table/VariableTable.vue"

export default({
    components: {VariableTable},
    data() {
        return{
            vul_data: null,
            sdata: {}
        }
    },
    beforeMount(){
        this.vul_data = this.$store.getters["data/GetSelectedVulnerability"]
        this.sdata = this.vul_data.params.inputs
        if(!("min_threshold" in this.sdata)){
            this.sdata.min_threshold = "0"
        }
        if(!("max_threshold" in this.sdata)){
            this.sdata.max_threshold = "65535"
        }
        if(!("selected_variable" in this.sdata)){
            this.sdata.selected_variable = ""
        }
    },
    watch: {
        sdata: {
            handler(val){
                this.vul_data.params.inputs = val
                this.$store.commit("data/SetSelectedVulnerability", this.vul_data);
            },
            deep: true
        }
    },
    methods: {
        changeValue(e){
            this.sdata.selected_variable = e
        }
    }
})
</script>

<style scoped>
#iot-container{
    height: 100%;
    width: 100%;
}

#outc-set-limmit{
    display: flex;
    justify-content: space-between;
    padding-left: 10%;
    padding-right: 10%;
    height: 40px;
}

.outc-limmit-sec{
    display: flex;
    justify-content: space-between;
    align-items: center;
    height: 40px;
    font-weight: 500;
}

.outc-limmit-sec input{
    height: 26px;
    width: 100px;
    margin-left: 10px;
}

#outc-select-var{
    width: 100%;
    height: calc(100% - 50px);
    margin-top: 10px;
}
</style>
