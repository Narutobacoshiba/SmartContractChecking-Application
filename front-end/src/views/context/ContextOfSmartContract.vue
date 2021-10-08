<template>
  <div class="container" id="section">
    <div id="header">Context of the Smart Contract</div>

    <div class="row" id="select">
      <div class="col-2">
        <p>Context of the SCs</p>
      </div>
      <div class="col-10">
        <select
          class="form-select input-sm"
          aria-label="Default select example"
          v-model="contextSC"
        >
          <option v-for="c in contexts" :key="c" :value="c.cid">
            {{ c.context }}
          </option>
        </select>
      </div>
    </div>
    <div class="row" id="select">
      <div class="col-2">
        <p>Type</p>
      </div>
      <div class="col-10">
        <input type="text" value="DCR" class="form-select input-sm" />
      </div>
    </div>

    <div class="row" id="description">
      <div class="col-2">
        <p>Description</p>
      </div>
      <div class="col-10">
        <span>There are several options:</span>
        <ul>
          <li v-for="c in contexts" :key="c">{{ c.des }}</li>
        </ul>
      </div>
    </div>
    <div id="btns">
      <button
        id="btn1"
        type="button"
        class="btn btn-outline-primary btn-sm"
        @click="routing('add')"
      >
        Add
      </button>
      <button
        id="btn1"
        type="button"
        class="btn btn-outline-primary btn-sm"
        @click="OpenUploadContext"
      >
        Up a Context File
      </button>
      <button
        id="btn2"
        type="button"
        class="btn btn-outline-primary btn-sm"
        @click="routing('back')"
      >
        Back
      </button>
    </div>
    <div id="showComponents" v-if="getShowComponents">
      <div id="components-holder">
        <UploadContext
          @closeComponents="cComponents"
          v-if="getSelectComponents == 'uploadctx'"
        />
      </div>
    </div>
  </div>
</template>

<script>
import UploadContext from "./UpLoadContext.vue";
import CheckService from "../../services/check.service.js";
export default {
  components: { UploadContext },
  data() {
    return {
      contexts: [],
      selectedContext: [],
      contextSC: [],
      showComponents: false,
      selectComponents: "",
    };
  },
  computed: {
    getShowComponents() {
      return this.showComponents;
    },
    getSelectComponents() {
      return this.selectComponents;
    },
  },
  methods: {
    async checkContext() {
      const context = {
        cid: 1,
        name: "Medicine",
        content: "",
        description: "",
        ctid: 1,
      };
      // console.log(context);
      const res = await CheckService.callToolsCheckContext(
        context.cid,
        context.name,
        context.content,
        context.description,
        context.ctid
      );
      console.log(res);
    },
    cComponents() {
      this.showComponents = false;
    },
    OpenUploadContext() {
      this.selectComponents = "uploadctx";
      this.showComponents = true;
    },
    loadContext() {
      this.showComponents = true;
    },
    routing(param) {
      if (param == "add") {
        this.checkContext();
        this.$router.push({ name: "UnFolding" });
      }
      if (param == "upfile") {
        this.$router.push({ name: "UpLoadContext" });
      }
      if (param == "back") {
        this.$router.push({ name: "SelectSmartContract" });
      }
    },
  },
};
</script>

<style scoped>
#section {
  width: 70%;
  margin: auto;
}
#header {
  text-align: center;
  font-size: 35px;
  font-weight: bold;
  margin-top: 2%;
  padding-bottom: 2%;
}
#select {
  text-align: center;
}
#select p {
  text-align: left;
  font-size: 18px;
}
#load-btn {
  float: left;
}
#description {
  margin-top: 2%;
}
#description p {
  text-align: left;
  font-size: 18px;
}
#btns {
  text-align: center;
  margin-top: 50px;
  margin-bottom: 50px;
  padding-bottom: 5%;
  
}
#btns button {
  margin-left: 40px;
  margin-right: 40px;
  cursor: pointer;
  width: 15%;
  height: 2%;
  border: 1px solid #2196f3;
  text-align: center;
  color: #2196f3;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
}
#btns button:hover {
  background-color: #1079cf;
  color: white;
}

/* ---- showComponents ---- */
#showComponents {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 100;
  display: flex;
  align-items: center;
  justify-content: center;
}
@media screen and (max-width: 800px) {
  #section {
    width: 100%;
  }
}
</style>