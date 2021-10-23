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
          <input type="text" placeholder="0" id="number-user" class="input-text-form">
        </div>
        <div class="multi-cell">
          <div id="multi-radio-chooses">
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="fixed" v-model="radio_seleted">
              <span>Fixed</span>
            </div>
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="random" v-model="radio_seleted">
              <span>Random</span>
            </div>
            <div class="radio-choose">
              <input type="radio" name="radio" class="radio-buttons" value="map" v-model="radio_seleted">
              <span>Map</span>
            </div>
          </div>
          <div id="multi-input-forms">
            <input type="text" class="input-text-form" id="fixed-input-form" placeholder="0" v-if="getSelectedRadio == 'fixed'">
            <div id="random-input-form" v-if="getSelectedRadio == 'random'">
              <div id="input-from-range">
                <span>From:</span>
                <input type="text" placeholder="0" class="input-text-form">
              </div>
              <div id="input-to-range">
                <span>To:</span>
                <input type="text" placeholder="10" class="input-text-form">
              </div>
            </div>
            <input type="text" class="input-text-form" id="map-input-form" placeholder="0,1,2" v-if="getSelectedRadio == 'map'">
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
                      v-on:click="selected_sc = item.id, function_cell_selected = 'function'"
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

                  <div class="table-row" v-for="(lv, index) in list_ssm_function[selected_sc]" v-bind:key="lv.id" :class="{ even_row: index % 2 == 0}">
                    <div class="table-cell first-cell">{{ index }}</div>
                    <div class="table-cell second-cell">{{ lv.name }}</div>
                    <div class="table-cell third-cell">
                      <div class="input-param-text" @click="setFunctionParam(lv)">Input Params</div>
                    </div>
                  </div>
                </div>
              </div>
              <div v-if="function_cell_selection == 'params'">
                <div id="params-setting-header">
                  <span id="return-arrow" class="material-icons" @click="function_cell_selected = 'function',selected_function = {}">
                    keyboard_backspace
                    </span>
                  <span id="ps-function-name">Function: {{selected_function.name}}</span>
                </div>
                <div id="params-setting-input">
                  <div id="sender-value-section">
                    <span>Sender value</span>
                    <input type="text" placeholder="0">
                    <span>To</span>
                    <input type="text" placeholder="10">
                  </div>
                  <div id="table-params">
                    <div class="table-params-row" id="header-params-row">
                      <div class="table-params-cell first-params-cell">
                        #
                        <span class="material-icons"> swap_vert </span>
                      </div>
                      <div class="table-params-cell second-params-cell">
                        Parameters
                        <span class="material-icons"> swap_vert </span>
                      </div>
                      <div class="table-params-cell third-cell">
                        Range
                        <span class="material-icons"> swap_vert </span>
                      </div>
                    </div>

                    <div class="table-row" v-for="(param, index) in list_function_params[selected_function.id]" v-bind:key="param.id" :class="{ even_row: index % 2 == 0}">
                      <div class="table-params-cell first-params-cell">{{ index }}</div>
                      <div class="table-params-cell second-params-cell">{{ param.name }}</div>
                      <div class="table-params-cell third-params-cell">
                        <input type="text">
                        <span>To</span>
                        <input type="text">
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
      </div>
      <div id="routing-button">
        <!-- save and back button add here -->
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      radio_seleted: "fixed",
      list_smart_contract: [{name:"smart I",id:1},{name:"smart II",id:2},{name:"smart III",id:3},{name:"smart IV",id:4}],
      selected_sc: 1,
      function_cell_selected: "function",
      list_ssm_function: {1:[{name:"func I",id:1},{name:"func II",id:2},{name:"func III",id:3},{name:"func IV",id:4},{name:"func V",id:5}]},
      selected_function: {},
      list_function_params: {1:[{name:"param I",id:1},{name:"param II",id:2},{name:"param III",id:3},{name:"param IV",id:4}]},
    };
  },
  computed:{
    getSelectedRadio(){
      return this.radio_seleted
    },
    function_cell_selection(){
      return this.function_cell_selected
    }
  },
  methods: {
    setFunctionParam(func){
      this.function_cell_selected = "params"
      this.selected_function = func
    },
    routing(param) {
      if (param == "save") {
        this.$router.push({ name: "CheckSmartContract" });
      }
      if (param == "back") {
        this.$router.push({ name: "CSPSettingType" });
      }
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

#table-list {
  width: 100%;
  margin: auto;
  font-size: 0.9em;
  height: 300px;
  overflow-y: auto;
  border-radius: 4px;
  border: 2px solid black;
  
  background: rgb(241, 240, 240);
}

.table-row{
  display: flex;
  height: 49px;
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
  padding-top: 15px;
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


/* param */
#params-setting-header{
  display: flex;
  height: 30px;
  vertical-align: middle;
}

#params-setting-header span{
  margin-right: 20px;
  
}
#ps-function-name{
  font-weight: bold;
}
#return-arrow{
  cursor: pointer;
  color: rgb(38, 38, 192);
  font-size: 26px;
}

#return-arrow:hover{
  color: rgb(81, 81, 231);
}

#params-setting-input{
  height: 270px;
  border: 2px solid black;
  padding-left: 4%;
  padding-right: 4%;  
}

#sender-value-section{
  margin-top: 10px;
}

#sender-value-section span{
  font-size: 14px;
}
#sender-value-section input{
  width: 80px;
  height: 25px;
  margin-left: 10px;
  margin-right: 10px;
}

#table-params {
  width: 100%;
  margin-top: 10px;
  font-size: 0.9em;
  height: 200px;
  overflow-y: auto;
  border-radius: 4px;
  border: 2px solid black;
  
  background: rgb(241, 240, 240);
}

.table-params-row{
  display: flex;
  height: 40px;
}
#header-params-row{
  background-color: rgb(196, 194, 194);
  font-weight: bold;
}

#header-params-row span {
  float: right;
  margin: 0 20% 0 0;
  padding: 0;
  font-size: 150%;
}
.even_row{
  background-color: rgb(226, 224, 224);
}
.table-params-cell{
  padding-top: 10px;
}
.first-params-cell{
  flex-basis: 12%;
  padding-left: 5px;
}
.second-params-cell{
  flex-basis: 58%;
}
.third-params-cell{
  padding-left: 5%;
  flex-basis: 30%;
}

.third-params-cell input{
  height: 20px;
  width: 30px;
}
.third-params-cell span{
  margin-left: 5px;
  margin-right: 5px;
}
</style>