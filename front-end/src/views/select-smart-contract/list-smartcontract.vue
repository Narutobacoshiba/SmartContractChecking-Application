<template>
  <div id="body">
    <div id="showConfirmation" v-if="showConfirmation">
      <div id="removeSC-holder">
        <confirm
          @cancel="closeConfirm"
          @confirm="cfDeleteSC()"
          :dialog="deleteDialog"
        />
      </div>
    </div>
    <div id="first-section"></div>
    <div id="second-section">
      <div class="middle-section">
        <div>
          <label for="date-picker">Date</label>
          <date-picker
            id="date-picker"
            v-model="time"
            valueType="format"
          ></date-picker>
        </div>

        <div id="select-section">
          <h5>Type</h5>
          <select v-model="chosen_table" class="select-custom">
            <option value="common">Common</option>
            <option value="private">Private</option>
            <option value="pending">Pending</option>
          </select>
        </div>
      </div>
    </div>
    <div id="third-section">
      <div id="table-section">
        <div id="table-name">
          <div id="add-button" @click="addSmartContract" v-if="showAddButton">
            Add
          </div>
          <p>Smart Contract List</p>
        </div>
        <div id="table-body">
          <div id="table-header" class="table-row">
            <div class="index-cell table-cell">#</div>
            <div class="name-cell table-cell">Name</div>
            <div class="name-cell table-cell">Type</div>
            <div class="date-modified-cell table-cell">Date modified</div>
            <div class="action-cell table-cell">Description</div>
          </div>
          <div id="table-content">
            <div
              class="table-row"
              v-for="(i, idx) in list_smart_contracts.common"
              :key="i.id"
            >
              <div class="index-cell table-cell">{{ idx + 1 }}</div>
              <div class="name-cell table-cell">{{ i.name }}</div>
              <div class="name-cell table-cell">{{ i.type }}</div>

              <div class="date-modified-cell table-cell">
                {{ convertDate(i.date_modified) }}
              </div>
              <div class="action-cell table-cell">
                <div>
                  <i>{{ i.description }}</i>
                  <i
                    class="material-icons"
                    @click="
                      editSC(i.id, i.name, i.content, i.description, i.type)
                    "
                    >edit</i
                  >
                  <i class="material-icons" @click="deleteSC(i.id)">delete</i>
                  <i
                    class="material-icons"
                    @click="acceptPendingSC(sc.id, sc.name, sc.content)"
                    >check_circle_outline</i
                  >
                  <i
                    class="material-icons"
                    @click="deleteSC(sc.id, sc.name, chosen_table)"
                    >next_plan</i
                  >
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div id="amsb-footer"></div>
      <button type="button" class="btn btn-primary" @click="routing('Add')">
        Add
      </button>
    </div>
  </div>
</template>

<script>
import { SmartContractService } from "../../services/smartcontract.services";
import DatePicker from "vue2-datepicker";
import "vue2-datepicker/index.css";
export default {
  components: { DatePicker },
  data() {
    return {
      chosen_table: "common",
      list_smart_contracts: {
        common: [],
        private: [],
        pending: [],
      },
      num_of_record: 7,
      num_of_page: 0,
      pageNum: 1,
      showConfirmation: false,
      deleteDialog: {},
      scDelete: null,
      time: null,
    };
  },
  mounted() {
    this.fetchData();
    //
  },
  computed: {
    GetTableName() {
      if (this.chosen_table == "common") {
        return "Common Smart Contracts";
      }
      if (this.chosen_table == "private") {
        return "Private Smart Contracts";
      }
      if (this.chosen_table == "pending") {
        return "Pending Smart Contracts";
      }
      return "Invalid Table";
    },
    showAddButton() {
      return (
        this.chosen_table != "pending" &&
        (this.chosen_table != "common" ||
          this.$store.state.user.currentUser.role == "admin")
      );
    },
    isSuperior() {
      return this.$store.state.user.currentUser.role == "admin";
    },
    getShowList() {
      let ret = [];
      for (
        let i = 0;
        i < this.list_smart_contracts[this.chosen_table].length;
        i++
      ) {
        if (
          (this.pageNum - 1) * this.num_of_record <= i &&
          this.pageNum * this.num_of_record > i
        ) {
          ret.push(this.list_smart_contracts[this.chosen_table][i]);
        }
      }
      return ret;
    },
    countPageNum() {
      return "" + this.pageNum + "/" + this.numOfPage;
    },
    numOfItems() {
      return this.list_smart_contracts[this.chosen_table].length;
    },
    numOfRecod() {
      if (
        this.list_smart_contracts[this.chosen_table].length <
        this.num_of_record * this.pageNum
      ) {
        return (
          this.list_smart_contracts[this.chosen_table].length -
          this.num_of_record * (this.pageNum - 1)
        );
      }
      return this.num_of_record;
    },
    numOfPage() {
      return Math.ceil(this.numOfItems / this.num_of_record);
    },
  },
  methods: {
    routing(param) {
      if (param == "Add") {
        this.$router.push({ name: "AddSC" });
      }
    },
    async fetchData() {
      const res = await SmartContractService.getAllSmartContract();
      this.list_smart_contracts.common = res.data.filter(
        (i) => i.type == this.chosen_table
      );
      console.log(this.list_smart_contracts.common);
    },
    inc(value) {
      return value + 1;
    },
    convertDate(value) {
      var date = new Date(value);
      var datestring = "" + date.getDate();
      var monthstring = "" + (date.getMonth() + 1);
      var hourstring = "" + date.getHours();
      var minutestring = "" + date.getMinutes();
      hourstring = hourstring.length == 1 ? "0" + hourstring : hourstring;
      minutestring =
        minutestring.length == 1 ? "0" + minutestring : minutestring;
      datestring = datestring.length == 1 ? "0" + datestring : datestring;
      monthstring = monthstring.length == 1 ? "0" + monthstring : monthstring;
      return (
        datestring +
        "/" +
        monthstring +
        "/" +
        date.getFullYear() +
        " " +
        hourstring +
        ":" +
        minutestring
      );
    },
    ChooseTable(value) {
      this.chosen_table = value;
      this.fetchData();
    },
    addSmartContract() {
      this.$router.push({
        name: "AddSc",
        params: { options: this.chosen_table, parent_path: "/list-sc" },
      });
    },
    async deleteSC(sc_id) {
      const res = await SmartContractService.deleteSmartContract(sc_id);
      if (res.status == 200) {
        this.fetchData();
      }
    },
    cfDeleteSC() {
      let sc_id = this.scDelete.sc_id;
      let option = this.scDelete.option;
      //   DeleteSmartContracts(sc_id, option);
      if (option == "common") {
        let list_smart_contracts_afterdelete = this.list_smart_contracts.common.filter(
          (i) => {
            return i.id != sc_id;
          }
        );
        this.list_smart_contracts.common = list_smart_contracts_afterdelete;
      } else if (option == "private") {
        let list_smart_contracts_afterdelete = this.list_smart_contracts.private.filter(
          (i) => {
            return i.id != sc_id;
          }
        );
        this.list_smart_contracts.private = list_smart_contracts_afterdelete;
      } else if (option == "pending") {
        let list_smart_contracts_afterdelete = this.list_smart_contracts.pending.filter(
          (i) => {
            return i.id != sc_id;
          }
        );
        this.list_smart_contracts.pending = list_smart_contracts_afterdelete;
      }

      // this.fetchData();
      this.closeConfirm();
    },
    closeConfirm() {
      this.showConfirmation = false;
    },
    editSC(sc_id, sc_name, sc_code, sc_des, sc_type) {
      this.$router.push({
        name: "EditSc",
        params: {
          sc_id: sc_id,
          name: sc_name,
          code: sc_code,
          description: sc_des,
          type: sc_type,
          parent_path: "/list-sc",
        },
      });
    },
    acceptPendingSC() {},
    goPage(value) {
      this.pageNum = value;
    },
  },
  watch: {
    chosen_table: function () {
      this.pageNum = 1;
    },
  },
};
</script>

<style scoped>
.btn {
  margin-bottom: 50px;
}
#body {
  width: 100%;
  min-width: 750px;
}
#first-section {
  height: 100px;
  width: 100%;
  background-color: #fafafa;
  border-bottom: 1px solid #d8d7d7;
  border-top: 1px solid #d8d7d7;
}
#second-section {
  height: 600px;
  width: 100%;
  background-color: #ffffff;
  margin-top: -50px;
}
#third-section {
  height: 600px;
  width: 86%;
  margin: 0 auto;
  margin-top: -500px;
  background-color: transparent;
}
#select-section {
  width: 300px;
  height: 70px;
}
.select-box {
  width: 200px;
  height: 40px;
  display: inline-block;
  margin-top: 15px;
  margin-bottom: 15px;
  margin-right: 10px;
  border: 0.5px solid #d8d7d7;
  border-radius: 4px;
  font-size: 15px;
  text-align: center;
  vertical-align: middle;
  cursor: pointer;
}
.select-box p {
  margin-top: 8px;
  color: #1967d2;
}
.select-box:hover {
  background-color: #e9eef7;
}
#table-section {
  width: 100%;
  height: 560px;
  background-color: white;
  border: 1px solid #d8d7d7;
  border-radius: 8px;
  box-shadow: 0 1px 4px 0 rgba(0, 0, 0, 0.37);
}
#table-name {
  width: 100%;
  height: 80px;
  border-bottom: 1px solid #d8d7d7;
  text-align: center;
  color: #6b6e73;
  padding: 12px;
}
#table-name p {
  font-size: 32px;
}
#table-name #add-button {
  position: absolute;
  margin-top: 15px;
  margin-left: 2%;
  height: 30px;
  width: 60px;
  border: 1px solid #5c5b5b;
  box-shadow: 2px 2px 0px 0px rgb(78, 77, 77);
  padding: 2px;
  cursor: pointer;
}
#table-name #add-button:hover {
  background-color: #d8d7d7;
  color: #272626;
}
#table-body {
  width: 100%;
  height: 520px;
  overflow-y: auto;
}
#table-header {
  background-color: #c9dff0;
  color: #4d4c4c;
  font-size: 16px;
  font-weight: bold;
}
/* --- table row --- */
.table-row {
  width: 100%;
  height: 60px;
  display: flex;
  align-items: center;
  color: #585858;
  border-bottom: 0.5px solid #d8d7d7;
}
.index-cell {
  height: 24px;
  flex-basis: 10%;
  text-align: center;
}
.name-cell {
  height: 24px;
  flex-basis: 15%;
}
.date-modified-cell {
  height: 24px;
  flex-basis: 20%;
}
.action-cell {
  height: 40px;
  flex-basis: 40%;
  text-align: center;
}
.action-cell i {
  padding: 8px;
  color: #858383;
  cursor: pointer;
}
.table-cell {
  overflow: hidden;
  text-overflow: ellipsis;
}
.table-row:hover {
  background-color: #fafafa;
}
.action-cell i:hover {
  color: #5e5d5d;
}
/* --- box --- */
.chosen_box {
  background-color: #e4ecfa;
}
/* ---- amsb-footer ---- */
#amsb-footer {
  width: 100%;
  height: 50px;
  border-bottom-right-radius: 4px;
  border-bottom-left-radius: 4px;
  display: flex;
}
#itb-entries {
  font-size: 14px;
  margin-top: 10px;
  margin-left: 2%;
}
#itb-cnpage {
  margin-left: auto;
  order: 2;
  margin-top: 10px;
  margin-right: 2%;
  display: flex;
}
#itb-cnpage i {
  margin-top: 1px;
  font-size: 22px;
  color: #636262;
  cursor: pointer;
}
#itb-cnpage i:hover {
  color: #424141;
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
.middle-section {
  width: 100%;
  display: inline-flex;
  justify-content: space-around;
  align-items: center;
}
</style>

/* Dropdown */
<style scoped>
@import url(https://fonts.googleapis.com/css?family=Open+Sans:400italic,600italic,400,600);

body {
  background: #1c5570;
  color: #ffffff;
  font: 400 0.9em/1.9 "Open Sans", Calibri, Helvetica, Arial, sans-serif;
}

.select-custom{
  height: 35px;
  width: 300px;
  border-radius: 10px;
  border:2px solid black;
}
</style>