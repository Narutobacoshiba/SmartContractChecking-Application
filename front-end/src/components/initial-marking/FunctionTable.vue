<template>
        <div>
            <div id="params-setting-header">
                <span id="return-arrow" class="material-icons" @click="existParamTable">
                keyboard_backspace
                </span>
              <span id="ps-function-name">Function: {{own_list_argument.name}}</span>
            </div>
            <div id="params-setting-input">
              <div id="sender-value-section">
                <span>Sender value</span>
                <input type="text" placeholder="0" v-model="own_list_argument.sender_value.from">
                <span>To</span>
                <input type="text" placeholder="10" v-model="own_list_argument.sender_value.to">
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
                  <div class="table-params-cell third-params-cell">
                    Range
                    <span class="material-icons"> swap_vert </span>
                  </div>
                </div>

                <div class="table-params-row" v-for="(param, key, index) in own_list_argument.arguments" v-bind:key="key" :class="{ even_row: index % 2 == 0}">
                  <div class="table-params-cell first-params-cell">{{ index+1 }}</div>
                  <div class="table-params-cell second-params-cell">{{ param.name }}</div>
                  <div class="table-params-cell third-params-cell">
                    <input type="text" v-model="param.from">
                    <span>To</span>
                    <input type="text" v-model="param.to">
                  </div>
                </div>
              </div>
            </div>
        </div>
</template>



<script>
export default ({
    props: ["list_argument"],
    data() {
        return{
            function_cell_selected: "function",
            own_list_argument: {}
        }
    },
    beforeMount(){
      this.own_list_argument = JSON.parse(JSON.stringify(this.list_argument)) 
    },
    methods:{
        existParamTable(){
            this.$emit("changeInitMarking",this.own_list_argument)
        },
    },
    computed:{
        function_cell_selection(){
            return this.function_cell_selected
        }
    },
})
</script>

<style scoped>
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
