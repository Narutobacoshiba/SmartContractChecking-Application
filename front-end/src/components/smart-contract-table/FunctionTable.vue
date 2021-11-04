<template>
    <div id="list-smart-contract">
        <ul class="nav nav-tabs">
            <li
            class="nav-item d-inline-block text-truncate"
            v-for="item in getListSmartContract"
            :key="item.name+item.id"
            >
            <a
            class="nav-link nav-link-top"
            v-on:click="selected_sc = item.id"
            v-bind:class="{ active: item.id == selected_sc}"
            >{{ item.name }}</a
            >
            </li>
        </ul>
        <div id="sc-table-content">
            <div id="sc-funtion">
                <SelectTable :selectValue="selectValue" rowName="Functions" :rowContent="getListFunction" @changeValue="updateSelectedFunction"/>
            </div>
        </div>
    </div>
</template>

<script>
import SelectTable from "./ElementSelectTable.vue"

export default ({
    props: ["selectValue"],
    components: {SelectTable},
    data(){
        return{
            list_smartcontract: [],
            smarcontract_infor: [],

            selected_sc: null,
        }
    },
    mounted(){
        this.list_smartcontract = this.$store.getters["data/GetSelectedSC"]
        this.smarcontract_infor = this.$store.getters["data/GetSCSelectedInfor"]
        this.initSelectedSc()
    },
    computed: {
        getListSmartContract(){
            return this.list_smartcontract
        },
        getListFunction(){
            for(let i=0; i < this.smarcontract_infor.length; i++){
                if(this.smarcontract_infor[i].id == this.selected_sc){
                    return this.smarcontract_infor[i].functions
                }
            }
            return [] 
        },
    },
    methods: {
        updateSelectedFunction(e){
            this.$emit("changeValue",e)
        },
        initSelectedSc(){
            this.selected_sc = this.list_smartcontract[0].id
        }
    }
})
</script>

<style scoped>
#list-smart-contract{
    width: 100%;
    height: 100%;
}
.nav-item .active {
    color: white;
    background-color: #383838;
    border: grey;
}
.nav-link {
    color: #383838;
    border: grey solid;
    border-bottom: none;
}
.nav-link-top{
    font-size: 14px;
}
.nav-link-under{
    font-size: 12px;
}
.nav-item {
    width: 20%;
    margin-right: 3px;
    cursor: pointer;
}

#sc-table-content{
    border: black solid; 
    padding: 2% 6% 2% 6%;
    height: calc(100% - 38px);
}

#sc-funtion{
    height: 96%;
}

</style>