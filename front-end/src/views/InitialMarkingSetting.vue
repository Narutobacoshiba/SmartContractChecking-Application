<template>
  <div id="initial-marking">
    <div id="initial-marking-header">
      Confguration
    </div>
    <div id="initial-marking-input">
      <div id="header-section">
        <div class="number-cell">
          Number of users
        </div>
        <div class="multi-cell">
          Balance
        </div>
        <div class="function-cell">
          Function parameters
        </div>
      </div>
      <div id="input-section">
        <div class="number-cell">
          <input type="text" placeholder="0" v-model="init_marking.NumberOfUser" id="number-user" class="input-text-form">
        </div>
        <div class="multi-cell">
          <div id="multi-radio-chooses">
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="fixed" v-model="init_marking.Balance.type">
              <span>Fixed</span>
            </div>
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="random" v-model="init_marking.Balance.type">
              <span>Random</span>
            </div>
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="map" v-model="init_marking.Balance.type">
              <span>Map</span>
            </div>
          </div>
          <div id="multi-input-forms">
            <input type="text" class="input-text-form" v-model="init_marking.Balance.fixed" id="fixed-input-form" placeholder="0" v-if="getSelectedRadio == 'fixed'">
            <div id="random-input-form" v-if="getSelectedRadio == 'random'">
              <div id="input-from-range">
                <span>From:</span>
                <input type="text" placeholder="0" v-model="init_marking.Balance.random.from" class="input-text-form">
              </div>
              <div id="input-to-range">
                <span>To:</span>
                <input type="text" placeholder="10" v-model="init_marking.Balance.random.to" class="input-text-form">
              </div>
            </div>
            <input type="text" v-model="init_marking.Balance.map" class="input-text-form" id="map-input-form" placeholder="0,1,2" v-if="getSelectedRadio == 'map'">
          </div>
        </div>
        <div class="function-cell">
            <div id="list-smart-contract">
              <ul class="nav nav-tabs">
                  <li
                  class="nav-item d-inline-block text-truncate"
                  v-for="item in list_smart_contract"
                  :key="item.id"
                >
                  <a
                    class="nav-link"
                    v-on:click="selectSC(item.id)"
                    v-bind:class="{ active: item.id == selected_sc}"
                    >{{ item.name }}</a
                  >
                </li>
              </ul>
          </div>
          <div id="sm-information-table">
              <div v-if="function_cell_selection == 'function'">
                <div id="table-list">
                  <div class="table-row" id="header-row">
                    <div class="table-cell header-cell first-cell">
                      #
                      <span class="material-icons"> swap_vert </span>
                    </div>
                    <div class="table-cell header-cell second-cell">
                      Functions
                      <span class="material-icons"> swap_vert </span>
                    </div>
                    <div class="table-cell header-cell third-cell">
                      Arguments
                    </div>
                  </div>

                  <div class="table-row" v-for="(func, index) in getSelectedScFunc" v-bind:key="func.id" :class="{ even_row: index % 2 == 0}">
                    <div class="table-cell first-cell">{{ index+1 }}</div>
                    <div class="table-cell second-cell">{{ func.name }}</div>
                    <div class="table-cell third-cell">
                      <div class="input-param-text" @click="setFunctionParam(func.id)">Input Params</div>
                    </div>
                  </div>
                </div>
            </div>
            <div v-if="function_cell_selection == 'params'">
                <function-table :list_argument="getFunctionArgument" @changeInitMarking="updateInitMarking"/>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div id="ssc-button">
        <button class="button-style" role="button" @click="goNextPage">Next</button>
        <button class="button-style" role="button" @click="goPrePage">Back</button>
    </div>
  </div>
</template>

<script>
import FunctionTable from "../components/initial-marking/FunctionTable.vue"
export default {
  components: {
    "function-table": FunctionTable,
  },
  data() {
    return {
      radio_seleted: "fixed",
      function_cell_selected: "function",
      list_smart_contract: [],
      smart_contract_infors: {},
      selected_sc: null,
      selected_function: null,
      init_marking: {}
    };
  },
  beforeMount(){
    this.list_smart_contract = this.$store.getters["data/GetSelectedSC"]
    let smi = this.$store.getters["data/GetSCSelectedInfor"]
    for(let i=0; i< smi.length; i++){
      this.smart_contract_infors[smi[i].id] = smi[i].functions 
    }
    this.initInitialMarkingHolder()
    
    if(this.list_smart_contract.length > 0){
      this.selected_sc = this.list_smart_contract[0].id
    }
  },
  watch: {
    init_marking: {
      handler(val){
        this.$store.commit("data/SetInitialMarking", val);
      },
      deep: true
    }
  },
  computed:{
    getSelectedRadio(){
      return this.init_marking.Balance.type
    },
    getSelectedScFunc(){
      if(this.selected_sc in this.smart_contract_infors){
        return this.smart_contract_infors[this.selected_sc]
      }else{
        return []
      }
    },
    function_cell_selection(){
      return this.function_cell_selected
    },
    getFunctionArgument(){
      return this.init_marking.Funtion_params[this.selected_sc].functions[this.selected_function]
    }
  },
  methods: {
    selectSC(id){
      if(this.selected_sc != id){
        this.selected_sc = id
        this.function_cell_selected = 'function'
      }
    },
    updateInitMarking(val){
      this.function_cell_selected = "function"
      this.selected_function = null
      this.init_marking.Funtion_params[this.selected_sc].functions[this.selected_function] = val
    },
    initInitialMarkingHolder(){
      this.init_marking = this.$store.getters["data/GetInitialMarking"]; 
      for(let i = 0; i < this.list_smart_contract.length; i++){
        let sm = this.list_smart_contract[i]

        if(!(sm.id in this.init_marking.Funtion_params)){
          this.init_marking.Funtion_params[sm.id] = {name: sm.name,functions: {}}
        }

        if(sm.id in this.smart_contract_infors){
          let sm_func_infor = this.smart_contract_infors[sm.id]
          for(let j = 0; j < sm_func_infor.length; j++){
            let sm_func =  sm_func_infor[j]
            if(!(sm_func.id in this.init_marking.Funtion_params[sm.id].functions)){
                this.init_marking.Funtion_params[sm.id].functions[sm_func.id] = {name: sm_func.name, sender_value:{from:null,to:null}, arguments: {}}
            }
            let sm_func_args = sm_func.argument
            for(let m = 0; m < sm_func_args.length; m++){
              let arg = sm_func_args[m]
              if(!(arg.id in this.init_marking.Funtion_params[sm.id].functions[sm_func.id].arguments)){
                this.init_marking.Funtion_params[sm.id].functions[sm_func.id].arguments[arg.id] = {name: arg.name, from: null, to: null}
              }
            }
          }
        }
      }
    },
    goNextPage() {
      this.$router.push({ name: "GenerateCPNModel" })
    },
    goPrePage(){
      let temp = this.$store.getters["data/GetSelectedVulnerability"]
      if(temp.type == "general"){
        this.$router.push({ name: "GeneralVulSetting" })
      }else if(temp.type == "specific"){
        if(temp.subtype == "temp"){
          this.$router.push({ name: "CSPPropertyTemp" })
        }else if(temp.subtype == "nontemp"){
          this.$router.push({ name: "CSPSettingNonTemp" })
        }
      }
      
    },
    setFunctionParam(func){
            this.function_cell_selected = "params"
            this.selected_function = func
    },
  },
};
</script>
<style scoped>
#initial-marking{
  height: 100%;
  width: 100%;
  min-width: 900px;
}

#initial-marking-header{
  height: 60px;
  padding-top: 10px;
  font-size: 30px;
  font-weight: bold;
  text-align: center;
}
#initial-marking-input{
  width: 60%;
  margin-left: 20%;

  display: flex;
  justify-content: space-between;
}

#header-section{
  flex-basis: 20%;
}

#input-section{
  flex-basis: 80%;
}

.number-cell{
  height: 40px;
  margin-top: 20px;
}

.multi-cell{
  height: 100px;
  margin-top: 20px;
}

.function-cell{
  margin-top: 20px;
}

#number-user{
  width: 100%;
}

#multi-radio-chooses{
  display: flex;
}

.radio-choose{
  flex-basis: 20%;
  height: 20px;
  margin-bottom: 20px;
}

.radio-choose span{
  font-size: 14px;
}

.radio-choose input{
  height: 11px;
}

#fixed-input-form{
  width: 60%;
}

#map-input-form{
  width: 60%;
}

#random-input-form{
  width: 60%;
  display: flex;
  justify-content: space-between;
}

.nav-item .active {
  color: white;
  background-color: #383838;
  border: grey;
}
.nav-link {
  font-size: 14px;
  color: #383838;
  border: grey solid;
  border-bottom: none;
}
.nav-item {
  width: 20%;
  margin-right: 3px;
  cursor: pointer;
}

#sm-information-table{
  border: black solid; 
  padding: 3% 2% 3% 2%;
}


/* function */

#table-list {
  width: 100%;
  margin: auto;
  font-size: 0.9em;
  height: 240px;
  overflow-y: auto;
  border-radius: 4px;
  border: 2px solid black;
  
  background: rgb(241, 240, 240);
}

.table-row{
  display: flex;
  height: 40px;
}
#header-row{
  background-color: rgb(196, 194, 194);
  font-weight: bold;
}

#table-list span {
  float: right;
  margin: 0 20% 0 0;
  padding: 0;
  font-size: 150%;
}
.even_row{
  background-color: rgb(226, 224, 224);
}
.table-cell{
  display: flex;
  align-items: center;
}
.first-cell{
  flex-basis: 12%;
  padding-left: 5px;
}
.second-cell{
  flex-basis: 58%;
}
.third-cell{
  flex-basis: 30%;
}
.input-param-text{
  color: rgb(42, 42, 214);
  cursor: pointer;
}
.input-param-text:hover{
  color: rgb(78, 78, 243);
}

/* Button */
#ssc-button{
    width: 60%;
    height: 80px;
    margin: auto;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.button-style {
  background-color: #FFFFFF;
  border: 0;
  border-radius: .5rem;
  box-sizing: border-box;
  color: #111827;
  font-family: "Inter var",ui-sans-serif,system-ui,-apple-system,system-ui,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
  font-size: .875rem;
  font-weight: 600;
  line-height: 1.25rem;
  padding: .75rem 1rem;
  text-align: center;
  text-decoration: none #D1D5DB solid;
  text-decoration-thickness: auto;
  box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.1), 0 2px 3px 0 rgba(0, 0, 0, 0.06);
  cursor: pointer;
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
}

.button-style:hover {
  background-color: rgb(249,250,251);
}

.button-style:focus {
  outline: 2px solid transparent;
  outline-offset: 2px;
}

.button-style:focus-visible {
  box-shadow: none;
}
</style>