<template>
  <div id="main">
    <div id="header">Create a new Context</div>
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
          <select name="" class="form-control" id="" v-model="type">
            <option value="DCR">DCR</option>
            <option value="CPN">CPN</option>
          </select>
        </div>
      </div>
      <div class="row" style="margin-bottom: 8%">
        <div class="title col-3">Description</div>
        <div class="col-9">
          <textarea
            class="form-control"
            type="text"
            v-model="description"
          ></textarea>
        </div>
      </div>
      <div class="row" id="name-section">
        <div class="title col-3">Content</div>
        <div class="col-9">
          <textarea name="" id="" cols="30" rows="10" class="form-control" type="text" v-model="content"></textarea>
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
import { ContextService } from "../../services/context.services";
export default {
  created() {
    this.initData();
  },
  data() {
    return {
      type: "",
      code: "",
      content: "C:/abc/xyz/Context.xml",
      name: "Context ABC",
      description: "",
      context: { name: String, code: String, description: String },
    };
  },
  // components: { EditorSc },
  methods: {
    hashCode(s) {
      var h = 0,
        l = s.length,
        i = 0;
      if (l > 0) while (i < l) h = ((h << 5) - h + s.charCodeAt(i++)) | 0;
      return h;
    },
    async initData() {
      // const data = await GetContextById(this.context_id)
      // this.initModelContext(data)
      // this.code = data.content
      // this.name = data.name
      // this.description = data.description
    },
    SaveContext() {
      // return UpdateContext(this.context_id, this.name, this.description)
    },
    async clickHandler(action) {
      if (action == "save") {
        const res = await ContextService.createContext(
          this.hashCode(this.name), 
          this.name, 
          this.type,
          this.content,
          this.description, 
        );
        console.log(res);
        this.$router.push(this.$router.push({ name: "ListContext" }));
      } else if (action == "cancel") {
        this.$router.push(this.$router.push({ name: "ListContext" }));
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