<template>
  <div id="main">
    <div id="header">
      <h1>Generating CPN Model</h1>
    </div>
    <div class="text-2">
      <span>Smart Contracts</span>
    </div>
    <div id="locate-1">
      <div id="component">
        <div class="table table-striped table-hover">
          <table class="table" border="1">
            <tr>
              <th>#</th>
              <th>Contract Name</th>
            </tr>
            <tr v-for="data in datatable" :key="data.id">
              <td>{{ data.id }}</td>
              <td>{{ data.var }}</td>
            </tr>
          </table>
        </div>
      </div>
    </div>
    <div id="locate-2">
      <div class="label">Context</div>
      <div class="input-area">
        <input
          type="text"
          class="form-control"
          aria-describedby="basic-addon3"
          value="Gaming"
        />
      </div>
    </div>
    <div id="locate-3">
      <div class="label">LTL Property</div>
      <div class="input-area">
        <input
          type="text"
          class="form-control"
          aria-describedby="basic-addon3"
          value="Integer Overflow"
        />
      </div>
    </div>
    <div id="locate-4">
      <div class="label">Configuration</div>
      <div class="link-to">
        <a href="" @click="navgiate('config')">Link to setting Configuration</a>
      </div>
    </div>
    <div class="contain-process">
      <div id="processing-section">
        <div id="download">
          <a
            v-if="showDownload"
            class="btn btn-primary btn-sm"
            href=""
            download="Solidity"
            >Download</a
          >
        </div>
        <div id="initial" v-if="step == 'initial'"></div>
        <div id="generating" v-show="step == 'generating'">
          <div>The smart contract is generating...</div>
          <div class="progress" id="progress">
            <div
              id="progress-bar-gen"
              class="progress-bar progress-bar-striped bg-warning"
              role="progressbar"
              style="width: 0%"
            ></div>
          </div>
        </div>
        <div id="generated" v-if="step == 'generated'">
          The generating process completed successfully
        </div>
        <div id="checking" v-show="step == 'checking'">
          <div>The smart contract is checking...</div>
          <div class="progress" id="progress">
            <div
              id="progress-bar-check"
              class="progress-bar progress-bar-striped bg-warning"
              role="progressbar"
              style="width: 0%"
            ></div>
          </div>
        </div>
        <div id="checked" v-if="step == 'checked'">
          The checking process completed successfully
        </div>
        <div id="results" v-if="this.results.length > 0 && step == 'finish'">
          <div><h3>Results:</h3></div>
          <div v-for="r in this.results" :key="r">{{ r }}</div>
        </div>
      </div>
    </div>
    <div id="processing-btn">
      <button
        v-if="step == 'initial' || step == 'generating'"
        class="btn btn-primary-outline"
        @click="generate"
      >
        Generate
      </button>
      <button
        v-if="step == 'check'"
        class="btn btn-primary-outline"
        @click="check"
      >
        Check
      </button>
      <button v-if="step == 'finish'" class="btn btn-primary-outline">
        Next
      </button>
      <button class="btn btn-primary-outline">Back</button>
    </div>
  </div>
</template>

<script>
import CheckService from "../services/check.service";

export default {
  data() {
    return {
      datatable: [
        { id: "1", var: "GV1" },
        { id: "2", var: "GV2" },
        { id: "3", var: "GV3" },
        { id: "4", var: "GV4" },
      ],
      step: "initial",
      list_selected_sc: [],
      list_selected_vuls: [],
      context: [],
      user: { user_name: "Dinh Thanh Ha" },
      error: true,
      view: "",
      results: [],
      showConfirmation: false,
      dialog: {},
      confirmation: "",
      currentSC: null,
    };
  },
  methods: {
    navgiate(param) {
      if (param == "config") {
        this.$router.push({ path: "" });
      }
    },
    async callUnfoldingTool() {
      const tName = "unfolding";
      const tcontext_PATH_xml = "<DCRModel>\n    <id>220802</id>\n    <title>Healthcare Workflow</title>\n    <events>\n        <id>play</id>\n    </events>\n    <events>\n        <id>claimReward</id>\n    </events>\n    \n    <rules>\n        <type>condition</type>\n        <source>play</source>\n        <target>claimReward</target>\n    </rules>\n    <rules>\n        <type>include</type>\n        <source>claimReward</source>\n        <target>play</target>\n    </rules>\n</DCRModel>";
      const tltl_PATH_json = "{\n    \"type\": \"general\",\n    \"params\": {\n        \"name\": \"under_over_flow\",\n        \"inputs\": [\"currentBalance\"]\n    }\n}";
      const res = await CheckService.callUnfoldingTools(
        tName,
        tcontext_PATH_xml,
        tltl_PATH_json
      );
      console.log("here");
      console.log(res);
    },

    async callToolHelena() {
      console.log("bat dau goi tool helena");
      const tName = "helena";
      this.$store.commit("Setrs","wait a sec...");
      const res = await CheckService.callHelenaTools(tName);
      if (res.status == 200 && res !== null && res != undefined) {
        const mess = res.data.message;
        this.results.push(mess);
        this.$store.commit("Setrs", mess);
      } else {
        console.log("bat dau mutation");
        this.$store.commit("Setrs","11");
        this.results.push("Can't run HELENA tools");
        
      }
    },
    async callToolLTL() {
      const tName = "ltl";
      const res = await CheckService.callToolLTL(tName);
      if (res.status == 200 && res !== null && res != undefined) {
        const mess = res.data.message;
        this.results.push(mess);
      } else {
        this.results.push("Can't run LTL tools");
      }
    },
    async checkContext() {
      const toolName = "dcr2cpn";
      const xml = "";
      // console.log(context);
      const res = await CheckService.callDCNTools(toolName, xml);
      console.log(res);
    },
    move(id) {
      //let _this = this;
      var elem = document.getElementById(id);
      var width = elem.offsetWidth;
      if (width >= 0) width = 0;
      var inter = setInterval(() => {
        if (width >= 100) {
          clearInterval(inter);
        } else {
          width++;
          elem.style.width = width + "%";
        }
      }, 10);
    },
    async delay(ms) {
      return await new Promise((resolve) => setTimeout(resolve, ms));
    },
    async generate() {
      this.step = "generating";
      this.move("progress-bar-gen");
      await this.delay(2000);
      this.step = "check";
      this.$store.commit("data/SetProcessView", "check-sc");
      //dcr2cpn
      // await this.checkContext();
      //unfoding
      await this.callUnfoldingTool();
      // await this.callToolLTL();
    },
    async check() {
      this.step = "checking";
      this.move("progress-bar-check");
      await this.delay(2000);
      if (this.error)
        confirm(
          "We have discover some counter-examples with the smart contract code. Do you want to look at them?"
        );
      this.step = "checked";
      await this.delay(2000);
      this.step = "finish";
      this.$store.commit("data/SetProcessView", "finish");
      this.callToolHelena();
      this.$router.push({name:"checkingresult31"})
    },
    routing(processview) {
      this.$store.commit("data/SetProcessView", processview);
    },
    addSmartContract() {
      this.$store.commit("data/SetProcessView", "sc-selection");
    },
    inc(value) {
      return value + 1;
    },
    removeSC(sc) {
      this.dialog = {
        title: "Remove Smart Contract",
        message: "Are you sure to remove '" + sc.name + "' ?",
        confirmbtn: "Remove",
      };
      this.confirmation = "removeSC";
      this.currentSC = sc.id;
      this.showConfirmation = true;
    },
    cfRemoveSC(id) {
      for (var i = 0; i < this.list_selected_sc.length; i++) {
        if (this.list_selected_sc[i].id === id) {
          this.list_selected_sc.splice(i, 1);
        }
      }
      this.$cookies.set("_ssc", JSON.stringify(this.list_selected_sc));
      this.closeConfirm();
    },
    editSC(sc_id, sc_name) {
      this.$router.push({
        name: "EditSc",
        params: { sc_id: sc_id, name: sc_name, parent_path: "/process" },
      });
    },
    removeAllSc() {
      if (this.list_selected_sc.length > 0) {
        this.confirmation = "removeAll";
        this.dialog = {
          title: "Remove All",
          message: "Are you sure to remove all selected smart contracts?",
          confirmbtn: "Remove All",
        };
        this.showConfirmation = true;
      }
    },
    cfRemoveAll() {
      this.list_selected_sc = [];
      this.$store.commit("data/SetSelectedSC", this.list_selected_sc);
      this.$cookies.set("_ssc", JSON.stringify(this.list_selected_sc));
      this.closeConfirm();
    },
    closeConfirm() {
      this.showConfirmation = false;
    },
  },
  mounted() {
    this.list_selected_sc = this.$store.getters["data/GetSelectedSC"];
    this.context = this.$store.getters["data/GetSelectedContext"];
    this.list_selected_vuls = this.$store.getters[
      "data/GetSelectedVulnerbility"
    ];
    this.view = this.$store.getters["data/GetProcessView"];
  },
  computed: {
    done_result() {
      return this.$store.getters.Getrs;
    },
    selectedSc() {
      return this.list_selected_sc;
    },
    isSelectSomeThing() {
      return this.list_selected_sc.length > 0;
    },
    getStep() {
      return this.step;
    },
    showDownload() {
      return this.step != "initial" && this.step != "generating";
    },
  },
};
</script>

<style scoped>
#header {
  text-align: center;
  margin-top: 2%;
  margin-bottom: 2%;
  font-weight: bold;
}
.contain-process {
  padding-bottom: 5%;
}
#locate-1 {
  border: 1px solid;
  width: 70%;
  margin: 0 auto;
  padding-bottom: 3%;
}

#processing-btn button {
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
.btn {
  margin: 0 3%;
}
#locate-1 {
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  border: 1px solid #d9edf7;
  border-radius: 10px;
}

#processing-btn button:hover {
  background-color: #1079cf;
  color: white;
}
.text-1 {
  position: relative;
  left: 15%;
  top: 15px;
  z-index: 1;
  height: 30px;
  width: 8%;
  background: white;
  text-align: center;
}
.text-2 {
  position: relative;
  left: 20%;
  top: 15px;
  z-index: 1;
  height: 30px;
  width: 6.6%;
  background: white;
  text-align: center;
  width: 140px;
}
.text {
  position: relative;
  left: 15%;
  top: 15px;
  z-index: 1;
  height: 30px;
  width: 3.6%;
  background: white;
  text-align: center;
}
#component {
  margin: 0 auto;
  width: 94%;
  padding-top: 2%;
  padding-bottom: 2%;
}
.table {
  width: 94%;
  margin: 0 auto;
}
.table tr:first-child {
  background-color: #d9edf7;
  color: #4ea8d6;
}
#processing-btn {
  margin: 40px;
  text-align: center;
}
#download {
  text-align: right;
  padding: 20px;
  height: 60px;
}

#processing-section {
  height: 300px;
  margin: auto;
  border: 1px black solid;
  border-radius: 3px;
  text-align: center;
  background-color: #f5f5f5;
  width: 80%;
}
#generating,
#checking {
  margin: auto;
  margin-top: 60px;
  padding: 0;
  width: 70%;
}
#results {
  margin-left: 40px;
  text-align: left;
  margin-top: 0;
  overflow: scroll;
  height: 79%;
}
#generated,
#checked {
  margin-top: 100px;
}
/*---- showConfirmation */
#showConfirmation {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.2);
  z-index: 1;
  align-items: center;
  justify-content: center;
}
#removeSC-holder {
  margin-top: 200px;
}
#removeAll-holder {
  margin-top: 50px;
}
</style>
<style scoped>
/* -----Context Style------ */

#locate-2,
#locate-3,
#locate-4 {
  width: 70%;
  margin: 0 auto;
  padding: 3% 2%;
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  border: 1px solid #d9edf7;
  border-radius: 10px;
  display: flex;
  justify-content: space-between;
  margin: 1% auto;
}

.label {
  font-size: 25px;
}
.input-area {
  width: 80%;
}
.link-to {
  width: 80%;
  display: flex;
  align-items: center;
}
</style>