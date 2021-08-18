<template>
  <div id="editsc">
    <div class="header">
      <div class="title"><h1>Edit the Smart Contract code</h1></div>
    </div>
    <div class="body">
      <div class="name-area area">
        <h2 class="label">Name</h2>
        <input class="input-name input-type" type="text" v-model="nameSc" />
      </div>
      <div class="editor-area area">
        <EditorSc v-model="code"/>
      </div>
      <div class="button-area area">
        <div class="button-add-cancell">
          <button id="button-add" type="button" @click="clickHandler('save')">Save</button>
          <button id="button-cancel" type="button" @click="clickHandler('back')">Back</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import {GetSmartContractCode, UpdateSmartContractCode} from "../../services/data"
import EditorSc from "../../components/EditorSc.vue";
export default {
  components: { EditorSc },
  name: "EditSc",
  data() {
    return {
      nameSc: this.$route.params.name,
      code: GetSmartContractCode(this.$route.params.sc_id)
    };
  },
  methods:{
    clickHandler(param){
      if(param == "save"){
        UpdateSmartContractCode(this.$route.params.sc_id, this.code)
        this.$router.push(this.$route.params.parent_path);
      }
      if(param == "back"){
        this.$router.push(this.$route.params.parent_path);
      }
    },
  }
};
</script>


<style scoped>
#editsc {
  background-color: rgb(241, 240, 240);
 
 
  display: flex;
  flex-direction: column;
  align-items: center;
  height: 100vh;
}
#type-select {
  width: 300px;
}
.title{
  padding-top: 8%;
  margin-bottom: 5%;
}
.title h1{
  font-size: 50px;
}
.input-type {
  position: absolute;
  top: 0;
  left: 50%;
}
.area {
  margin-bottom: 30px;
  position: relative;
}
/* router style */
a.router-link-active {
  color: white;
  text-decoration: none;
}
.body {
  display: flex;
  flex-direction: column;
  align-items: center;
}
/* header style */
/* name area */
.name-area,
.type-area {
  width: 500px;
}
.label {
  font-style: normal;
  font-size: 20px;
  font-weight: 100;
  position: relative;
  left: 0;
}
.input-name {
  width: 250px;
  border: 1px solid;
  border-radius: 2px;
  overflow: hidden;
}
/* editor area */
.editor-area {
  width: 600px;
  overflow: hidden;
  position: relative;
  left: 40px;
}
/* button style */
.button-add-cancell button {
  width: 170px;
  height: 30px;
  color: #0d6efd;
  border: 1px solid;
  border-radius: 4px;
}
.button-add-cancell button:hover {
  opacity: 0.9;
  background-color: #0d6efd;
  color: white;
  cursor: pointer;
}
.button-add-cancell button:active {
  cursor: wait;
}
#button-add {
  margin-right: 20px;
}
.button-add-cancell {
  position: relative;
  left: 40px;
}
</style>