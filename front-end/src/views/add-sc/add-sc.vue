<template>
  <div id="addsc">
    <div class="header">
      <div class="title"><h1>Create a new Smart Contract code</h1></div>
    </div>
    <div class="body">
      <div class="name-area area">
        <h2 class="label">Name</h2>
        <input
          class="input-name input-type"
          type="text"
          placeholder="Smart Contract Name"
          v-model="nameSc"
        />
      </div>
      <div class="type-area area">
        <div class="label">Smart Contract Type</div>
        <div class="wrapper">
          <input type="radio" name="select" id="option-1" checked />
          <input type="radio" name="select" id="option-2" />
          <label for="option-1" class="option option-1">
            <div class="dot"></div>
            <span>Student</span>
          </label>
          <label for="option-2" class="option option-2">
            <div class="dot"></div>
            <span>Teacher</span>
          </label>
        </div>
      </div>

      <div class="editor-area area">
        <EditorSc v-model="code" />
      </div>
      <div class="button-area area">
        <div class="button-add-cancell">
          <button id="button-add" type="button" @click="clickHandler('save')">
            Save
          </button>
          <button
            id="button-cancel"
            type="button"
            @click="clickHandler('cancel')"
          >
            Cancel
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { AddNewSmartContracts } from "../../services/data";
import EditorSc from "../../components/EditorSc.vue";

export default {
  name: "AddSc",
  data() {
    return {
      nameSc: "",
      options: this.$route.params.options,
      code: "",
    };
  },
  components: { EditorSc },
  methods: {
    clickHandler(action) {
      if (action == "save") {
        AddNewSmartContracts(
          this.hashValue(this.nameSc),
          this.nameSc,
          this.options,
          this.code
        );
      }
    },
  },
  computed: {
    selectOption: {
      get: function () {
        return this.options;
      },
      set: function (value) {
        this.options = value;
      },
    },
    isSuperior() {
      return this.$store.state.user.currentUser.role == "admin";
    },
  },
};
</script>
<style scoped>
#type-select {
  width: 300px;
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
.option div {
  display: flex;
  align-items: center;
}
.option {
  width: 250px;
  display: flex;
  /* background-color: red; */
  justify-content: space-between;
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
#addsc {
  background-color: #fff;
  height: 100vh;
  display: flex;
  flex-direction: column;
  align-items: center;
}
/* header style */
.title {
  padding-top: 8%;
  margin-bottom: 5%;
}
.title h1 {
  font-size: 40px;
  font-family: sans-serif;
  font-weight: 600;
  color: #62a9e6;
}
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
  overflow: hidden;
  border-top-width: 0;
  border-left-width: 0;
  border-right-width: 0;
}
.input-name:focus {
  border-bottom-width: 0;
  transition: 0.5s;
  width: 330px;
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
  width: 160px;
  height: 30px;
  background-color: #2196f3;
  text-align: center;
  color: white;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
  border-width: 0px;
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
input[type="radio"] {
  transform: scale(1.6);
}
label {
  margin-right: 10px;
}
label:hover {
  cursor: pointer;
}

@import url("https://fonts.googleapis.com/css?family=Lato:400,500,600,700&display=swap");
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: "Lato", sans-serif;
}
html,
body {
  display: grid;
  height: 100%;
  place-items: center;
  background: #0069d9;
  font-family: "Lato", sans-serif;
}
.wrapper {
  left: 49%;
  position: absolute;
  top: -5px;
  display: inline-flex;
  background: #fff;
  height: 40px;
  width: 300px;
  align-items: center;
  justify-content: space-evenly;
  border-radius: 5px;
  padding: 10px 15px;
}
.wrapper .option {
  background: #fff;
  height: 100%;
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: space-evenly;
  margin: 0 10px;
  border-radius: 5px;
  cursor: pointer;
  padding: 0 10px;
  border: 2px solid lightgrey;
  transition: all 0.3s ease;
}
.wrapper .option .dot {
  height: 10px;
  width: 10px;
  background: #d9d9d9;
  border-radius: 50%;
  position: relative;
}
.wrapper .option .dot::before {
  position: absolute;
  content: "";
  top: 2px;
  left: 1.9px;
  width: 6px;
  height: 6px;
  background: #0069d9;
  border-radius: 50%;
  opacity: 0;
  transform: scale(1.5);
  transition: all 0.3s ease;
}
input[type="radio"] {
  display: none;
}
#option-1:checked:checked ~ .option-1,
#option-2:checked:checked ~ .option-2 {
  border-color: #0069d9;
  background: #0069d9;
}
#option-1:checked:checked ~ .option-1 .dot,
#option-2:checked:checked ~ .option-2 .dot {
  background: #fff;
}
#option-1:checked:checked ~ .option-1 .dot::before,
#option-2:checked:checked ~ .option-2 .dot::before {
  opacity: 1;
  transform: scale(1);
}
.wrapper .option span {
  font-size: 13px;
  color: #808080;
}
#option-1:checked:checked ~ .option-1 span,
#option-2:checked:checked ~ .option-2 span {
  color: #fff;
}
</style>