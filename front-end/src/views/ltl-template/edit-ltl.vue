<template>
  <div id="main">
    <div id="header">Update the LTL Property Template</div>
    <div class="body">
      <div class="row" id="name-section">
        <div class="title col-3">Name</div>
        <div class="col-9">
          <input class="form-control" type="text" v-model="name" />
        </div>
      </div>
      <div class="row" style="margin-bottom: 8%">
        <div class="title col-3">Formula Text</div>
        <div class="col-9">
          <textarea
            class="form-control"
            type="text"
            v-model="fomular"
          ></textarea>
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
import { LTLTemplate } from "../../services/ltlproperty.services";
export default {
  data() {
    return {
      id: this.$route.params.l_id,
      name: this.$route.params.l_name,
      fomular: this.$route.params.l_fomular,
      description: this.$route.params.l_description,
      fomular_text: this.$route.params.l_fomular_text,
    };
  },
  // components: { EditorSc },
  methods: {
    async clickHandler(action) {
      if (action === "save") {
        const res = await LTLTemplate.updateLTLTemplate(
          this.id,
          this.name,
          this.fomular,
          "Type",
          this.description,
          this.fomular_text
        );
        console.log(res);
        if (res.status === 200) {
          this.$router.push({ name: "ListLTL" });
        } else {
          alert("Faill");
        }
      } else if (action === "cancel") {
        if (!this.$route.params.parent_path) this.$router.push("/");
        else this.$router.push(this.$route.params.parent_path);
      }
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