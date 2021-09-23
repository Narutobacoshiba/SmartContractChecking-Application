<template>
  <div id="main">
    <div id="header">Edit a Context</div>
    <div class="body">
      <div class="row" id="name-section">
        <div class="title col-2">Name</div>
        <div class="col-10">
          <input class="form-control" type="text" v-model="name" />
        </div>
      </div>
      <div class="row">
        <div class="title col-2">Description</div>
        <div class="col-10">
          <textarea
            class="form-control"
            type="text"
            v-model="description"
          ></textarea>
        </div>
      </div>
      <div class="editor-area">
        <span class="title">Formular</span>
        <EditorSc :code.sync="code" />
      </div>
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
import EditorSc from "../../components/EditorSc.vue";
import { GetContextById, UpdateContext } from "../../services/data";
export default {
  created() {
    this.initData();
  },
  data() {
    return {
      context_id: this.$route.params.context_id,
      code: "",
      name: "",
      description: "",
      context: { name: String, code: String, description: String },
    };
  },
  components: { EditorSc },
  methods: {
    async initData() {
      const data = await GetContextById(this.context_id);
      this.initModelContext(data);
      this.code = data.content;
      this.name = data.name;
      this.description = data.description;
    },
    SaveContext() {
      return UpdateContext(this.context_id, this.name, this.description);
    },
    async clickHandler(action) {
      if (action == "save") {
        if (!this.checkChangeConText()) {
          const res = await this.SaveContext();
          if (res.status && res.status === 200) {
            this.$router.push(this.$route.params.parent_path);
          }
        }else{
          alert('You do not edit!')
        }
      } else if (action == "cancel") {
        if (!this.$route.params.parent_path) this.$router.push("/");
        else this.$router.push(this.$route.params.parent_path);
      }
    },
    initModelContext(modelContext) {
      this.context.name = modelContext.name;
      this.context.code = modelContext.content;
      this.context.description = modelContext.description;
    },
    checkChangeConText(){
      return this.context.name.trim() === this.name.trim() 
      && this.context.code.trim() === this.code.trim() 
      && this.context.description.trim() === this.description.trim()
    }
  },
  computed: {},
};
</script>
<style scoped>
#main {
  background-color: rgb(241, 240, 240);
  align-items: center;
  height: 100%;
  margin: 0;
}
#header {
  text-align: center;
  font-size: 35px;
  font-weight: bold;
  padding-top: 20px;
  margin-bottom: 20px;
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
}
#group-btn button:hover {
  opacity: 0.9;
  background-color: #0d6efd;
  color: white;
}
#group-btn button:active {
  cursor: wait;
}
</style>