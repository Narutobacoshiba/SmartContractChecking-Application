<template>
    <div id="sdes-container">
        <div id="sdesc-select-var">
            <FunctionTable :selectValue="sdata.selected_function" @changeValue="changeValue"/>
        </div>
    </div>
</template>

<script>
import FunctionTable from "../smart-contract-table/FunctionTable.vue"

export default({
    components: {FunctionTable},
    data() {
        return{
            vul_data: null,
            sdata: {}
        }
    },
    beforeMount(){
        this.vul_data = this.$store.getters["data/GetSelectedVulnerability"]
        this.sdata = this.vul_data.params.inputs
        if(!("selected_function" in this.sdata)){
            this.sdata.selected_function = ""
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
            this.sdata.selected_function = e
        }
    }
})
</script>

<style scoped>
#sdes-container{
    height: 100%;
    width: 100%;
}

#sdesc-select-var{
    width: 100%;
    height: calc(100% - 50px);
    margin-top: 10px;
}
</style>
