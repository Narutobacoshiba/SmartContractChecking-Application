<template>
  <div id="main">
    <div id="header">Create a new LTL Property Template</div>
    <div class="body">
      <div class="row" id="name-section">
        <div class="title col-3">Name</div>
        <div class="col-9">
          <input class="form-control" type="text" v-model="name" />
        </div>
      </div>

      <div class="row" style="margin-bottom: 8%">
        <div class="title col-3">Formula</div>
        <div class="col-9" id="formula">
          <LtlEditor :ltlcode="getLTLContent" @changeContent="getContent" />
        </div>
      </div>
      <div class="row" style="margin-bottom: 8%">
        <div class="title col-3">Formula Text</div>
        <div class="col-9">
          <textarea
            class="form-control"
            type="text"
            v-model="formular_text"
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
import LtlEditor from "../../components/LtlEditor.vue";
export default {
  data() {
    return {
      name: "",
      formular_text: "",
      formular: "",
      template_type: "Type0",
      description: "",
      fomular_code: "DemoFomularCode",
    };
  },
  components: { LtlEditor },
  methods: {
    getContent(e) {
      this.formular = e;
    },
    hashCode(s) {
      var h = 0,
        l = s.length,
        i = 0;
      if (l > 0) while (i < l) h = ((h << 5) - h + s.charCodeAt(i++)) | 0;
      return h;
    },
    async clickHandler(action) {
      if (action === "save") {
        const res = await LTLTemplate.createLTLTemplate(
          this.hashCode(this.name),
          this.name,
          this.formular,
          this.formular_text,
          this.template_type,
          this.description
          //this.fomular_code,
        );
        console.log(res);
        if (res.status && res.status === 201) {
          this.$router.push({ name: "ListLTL" });
        } else {
          alert("Fail");
        }
      } else if (action === "cancel") {
        if (!this.$route.params.parent_path) this.$router.push("/");
        else this.$router.push(this.$route.params.parent_path);
      }
    },
  },
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
  padding-bottom: 50px;
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
#formula {
  height: 240px;
}
</style>