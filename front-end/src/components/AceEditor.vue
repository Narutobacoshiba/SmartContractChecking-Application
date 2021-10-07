<template>
  <div id="ace-editor">
    <!-- <h1>Hello demo {{codeSC}}</h1> -->
    <div class="tool-bar"></div>
    <editor
      v-model="contentSC"
      @init="editorInit"
      lang="solidity"
      theme="chrome"
      width="100%"
      height="90%"
    ></editor>
  </div>
</template>

<script>
export default {
  data() {
    return {
      contentSC:"//add your code here"
    };
  },
  watch:{
    codeSC:function(newVal, oldVal){
      console.log(`propchange oldVal:${oldVal}, newVal:${newVal}`)
      this.contentSC = this.codeSC
    },
    contentSC:function(newVal, oldVal){
      console.log(`propchange oldVal:${oldVal}, newVal:${newVal}`)
      this.$emit('changeSC',newVal)
    },
  },
  props:["codeSC"],
  components: {
    editor: require("vue2-ace-editor"),
  },
  methods: {
    editorInit: function () {
      require("brace/ext/language_tools"); //language extension prerequsite...
      require("brace/mode/solidity"); //language
    },
    change() {
      console.log("Alo");
    },
  },
};
</script>

<style scoped>
#ace-editor {
  /* width: 600px; */
  height: 400px;
}
.tool-bar {
  height: 30px;
  width: 100%;
  background-color: rgb(49, 98, 170);
  border-radius: 4px 4px 0 0;
}
</style>
<style>
.ace_content {
  background-color: aliceblue;
}
.ace-tm {
  background-color: #ffffff;
  color: black;
  border: 1px solid #d0d0d0;
  border-top-width: 1.5px;
  border-radius: 0 0 4px 4px;
}
</style>