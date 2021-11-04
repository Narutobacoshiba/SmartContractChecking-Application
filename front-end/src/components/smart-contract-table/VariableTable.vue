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
        <div class="sc-table-content" id="sctc-content">
            <div id="sc-global-variable">
                <SelectTable :selectValue="getSelectVariable" rowName="Global variables" :rowContent="getListGlobalVar" @changeValue="updateSelectedVar"/>
            </div>
            <div id="sc-list-function">
                <ul class="nav nav-tabs">
                    <li
                    class="nav-item d-inline-block text-truncate"
                    v-for="item in getListFunction"
                    :key="item.name+item.id"
                    >
                    <a
                    class="nav-link nav-link-under"
                    v-on:click="selected_function = item.id"
                    v-bind:class="{ active: item.id == selected_function}"
                    >{{ item.name }}</a
                    >
                    </li>
                </ul>
                <div class="sc-table-content" id="sctc-localvar">
                    <div id="sc-list-localvar">
                        <SelectTable :selectValue="getSelectVariable" rowName="Local variables" :rowContent="getListLocalVar" @changeValue="updateSelectedVar"/>
                    </div>
                </div>
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
            selected_var: this.selectValue,
            selected_sc: null,
            selected_function: null,
        }
    },
    mounted(){
        this.list_smartcontract = this.$store.getters["data/GetSelectedSC"]
        this.smarcontract_infor = this.$store.getters["data/GetSCSelectedInfor"]
        this.initSelectedSc()
    },
    computed: {
        getSelectVariable(){
            return this.selected_var
        },
        getListSmartContract(){
            return this.list_smartcontract
        },
        getListGlobalVar(){
            for(let i=0; i < this.smarcontract_infor.length; i++){
                if(this.smarcontract_infor[i].id == this.selected_sc){
                    return this.smarcontract_infor[i].globalVariables
                }
            }
            return []  
        },
        getListFunction(){
            for(let i=0; i < this.smarcontract_infor.length; i++){
                if(this.smarcontract_infor[i].id == this.selected_sc){
                    return this.smarcontract_infor[i].functions
                }
            }
            return [] 
        },
        getListLocalVar(){
            let choosen_smartcontract = {}
            for(let i=0; i < this.smarcontract_infor.length; i++){
                if(this.smarcontract_infor[i].id == this.selected_sc){
                    choosen_smartcontract = this.smarcontract_infor[i]
                }
            }
            if("functions" in choosen_smartcontract){
                let sc_funtions = choosen_smartcontract.functions
                for(let i=0; i < sc_funtions.length; i++){
                    if(sc_funtions[i].id == this.selected_function){
                        return sc_funtions[i].localVariables
                    }
                }
            }
            return []
        },
    },
    methods: {
        updateSelectedVar(e){
            this.selected_var = e
            this.$emit("changeValue",e)
        },
        initSelectedSc(){
            this.selected_sc = this.list_smartcontract[0].id
            this.initSelectedFunction()
        },
        initSelectedFunction(){
            let choosen_smartcontract = {}
            for(let i=0; i < this.smarcontract_infor.length; i++){
                if(this.smarcontract_infor[i].id == this.selected_sc){
                    choosen_smartcontract = this.smarcontract_infor[i]
                }
            }
            if("functions" in choosen_smartcontract){
                this.selected_function = choosen_smartcontract.functions[0].id
            }
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

.sc-table-content{
    border: black solid; 
    padding: 2% 6% 2% 6%;
}

#sctc-content{
    height: calc(100% - 37px);
}
#sc-global-variable{
    height: 40%;
}

#sc-list-function{
    margin-top: 4%;
    height: calc(60% - 36px);
}

#sctc-localvar{
    height: 90%;
}

#sc-list-localvar{
    height: 96%;
}
</style>