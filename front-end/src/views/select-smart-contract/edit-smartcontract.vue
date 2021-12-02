<template>
  <div id="main">
    <div id="head"><a href="#">Home</a>>Edit</div>
    <div id="header">Edit the Smart Contract code</div>
    <div class="body">
      <div class="row" id="name-section">
        <div class="title col-3">Name</div>
        <div class="col-9">
          <input class="form-control" type="text" v-model="name" />
        </div>
      </div>
      <div class="row" id="name-section">
        <div class="col-3">Smart Contract Type</div>
        <div class="col-9">
          <select name="" class="form-control" id="">
            <option value="1">Common</option>
            <option value="2">Private</option>
            <option value="3">Pending</option>
          </select>
        </div>
      </div>
      <div class="row">
        <div class="title col-3">Content</div>
        <div class="col-9" style="margin-bottom: 5%">
          <textarea class="form-control" type="text" v-model="code"></textarea>
        </div>
      </div>
      <div class="row">
        <div class="title col-3">Description</div>
        <div class="col-9">
          <textarea
            class="form-control"
            type="text"
            v-model="description"
          ></textarea>
        </div>
      </div>
      <!-- <div class="editor-area">
        <span class="title">Formular</span> -->
      <!-- <EditorSc :code.sync="code" /> -->
      <!-- </div> -->
      <div id="group-btn">
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
</template>

<script>
import { SmartContractService } from "../../services/smartcontract.services";
export default {
  created() {
    this.initData();
  },
  data() {
    return {
      sid: "",
      code: "",
      name: "Smart contract 1",
      description: "",
      type: "",
    };
  },
  // components: { EditorSc },
  methods: {
    initData() {
      this.name = this.$route.params.name;
      this.code = this.$route.params.code;
      this.description = this.$route.params.description;
      this.type = this.$route.params.type;
      this.sid = this.$route.params.sc_id;
      // console.log(this.sid)
    },
    async clickHandler(action) {
      if (action === "save") {

        const res = await SmartContractService.editSmartContract(
          this.sid,
          this.name,
          this.code,
          this.type,
          this.description
        );
        console.log(res)
        if (res.status === 202) {
          this.$router.push(this.$router.push({ name: "ListSC" }));
        }else{
          alert("Something Wrong!!!")
        }
      } else if (action === "cancel") {
        this.$router.push(this.$router.push({ name: "ListSC" }));
      }
    },
    initModelContext(modelContext) {
      this.context.name = modelContext.name;
      this.context.code = modelContext.content;
      this.context.description = modelContext.description;
    },
    checkChangeConText() {
      return (
        this.context.name.trim() === this.name.trim() &&
        this.context.code.trim() === this.code.trim() &&
        this.context.description.trim() === this.description.trim()
      );
    },
  },
  computed: {},
};
</script>
<style scoped>
#main {
  /* background-color: rgb(241, 240, 240); */
  align-items: center;
  height: 100%;
  margin: 0;
}
#header {
  text-align: center;
  font-size: 35px;
  font-weight: bold;
  padding-top: 20px;
  margin-bottom: 40px;
}
.body {
  display: flex;
  flex-direction: column;
  width: 700px;
  margin: auto;
}
.title {
  font-size: 18px;
}
#name-section {
  margin-bottom: 30px;
}
/* editor area */
.editor-area {
  width: 100%;
  overflow: hidden;
  position: relative;
  /* left: 40px; */
}
/* button style */
#group-btn {
  width: 100%;
  align-items: center;
  display: flex;
  justify-content: space-evenly;
  margin-top: 30px;
}
#group-btn button {
  width: 170px;
  height: 30px;
  color: #0d6efd;
  border: 1px solid;
  border-radius: 4px;
  background: white;
}
#group-btn button:hover {
  opacity: 0.9;
  background-color: #0d6efd;
  color: white;
}
#group-btn button:active {
  cursor: wait;
}
textarea {
  height: 180px;
}
#head {
  position: relative;
  left: 6%;
}
</style>