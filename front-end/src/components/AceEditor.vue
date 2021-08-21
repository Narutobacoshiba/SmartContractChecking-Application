<template>
  <div id="ace-editor">
    <div class="tool-bar"></div>
    <editor
      v-model="content"
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
      content:
        "pragma solidity >=0.4.22 <0.6.0;\npragma solidity ^0.5.6 ;\ncontract Ballot {\n}",
    };
  },
  components: {
    editor: require("vue2-ace-editor"),
  },
  methods: {
    editorInit: function () {
      require("brace/ext/language_tools"); //language extension prerequsite...
      require("brace/mode/solidity"); //language
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