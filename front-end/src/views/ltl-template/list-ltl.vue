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
      <h2>LTL Property Template List</h2>
      <div class="middle-section">
        <div id="date">
          <h5>Date</h5>
          <label for="date-picker"></label>
          <date-picker
            id="date-picker"
            v-model="time"
            valueType="format"
          ></date-picker>
        </div>
        <div id="select-section">
          <div class="custom-select">
            <h5>Type</h5>
            <label for="select-choice1" class="label select-1"> </label>
            <select id="select-choice1" class="select">
              <option value="Choice 1">CSP</option>
              <option value="Choice 2">Vulnerability</option>
            </select>
          </div>
        </div>
      </div>
    </div>
    <div id="third-section">
      <div id="table-section">
        <!-- <div id="table-name">
          <div id="add-button" @click="addSmartContract" v-if="showAddButton">
            Add
          </div>
        </div> -->
        <div id="table-body">
          <div id="table-header" class="table-row">
            <div class="index-cell table-cell">#</div>
            <div class="name-cell table-cell">Name</div>
            <div class="name-cell table-cell">Type</div>
            <div class="date-modified-cell table-cell">Date modified</div>
            <div class="action-cell table-cell">Description</div>
          </div>
          <div id="table-content">
            <div class="table-row" v-for="(i, idx) in list_ltl" :key="i.id">
              <div class="index-cell table-cell">{{ idx + 1 }}</div>
              <div class="name-cell table-cell">{{ i.name }}</div>
              <div class="name-cell table-cell">{{ i.template_type }}</div>

              <div class="date-modified-cell table-cell">
                {{ convertDate(i.date_modified) }}
              </div>
              <div class="action-cell table-cell">
                <div class="item">
                  <i>{{ i.description }}</i>
                  <i
                    class="material-icons"
                    @click="editLTL(i.id, i.name, i.formula, i.description)"
                    >edit</i
                  >
                  <i class="material-icons" @click="deleteSC(i.id)">delete</i>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div id="amsb-footer"></div>
      <button type="button" class="btn btn-primary" @click="addLTL()">
        Add
      </button>
    </div>
  </div>
</template>

<script>
import DatePicker from "vue2-datepicker";
import "vue2-datepicker/index.css";
import { LTLTemplate } from "../../services/ltlproperty.services";
export default {
  name: "HelloWorld",
  components: { DatePicker },
  data() {
    return {
      chosen_table: "common",
      list_ltl: {},
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
  },
  methods: {
    async deleteSC(_id) {
      const res = await LTLTemplate.deleteLTLTemplate(_id);
      if (res.status === 200) {
        this.fetchData();
      }else{
        alert("FAill")
      }
    },
    editLTL(_id, _name, _formular, _description) {
      this.$router.push({
        name: "EditLTL",
        params: {
          l_id: _id,
          l_name: _name,
          l_fomular: _formular,
          l_description: _description,
        },
      });
    },
    addLTL() {
      this.$router.push({ name: "AddLTLCom" });
    },
    async fetchData() {
      const res = await LTLTemplate.getLTLTemplate();
      this.list_ltl = res.data;
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
      hourstring = hourstring.length === 1 ? "0" + hourstring : hourstring;
      minutestring =
        minutestring.length === 1 ? "0" + minutestring : minutestring;
      datestring = datestring.length === 1 ? "0" + datestring : datestring;
      monthstring = monthstring.length === 1 ? "0" + monthstring : monthstring;
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
  margin-bottom: 10%;
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
.custom-select {
  position: relative;
  width: 100%;
  max-width: 25em;
  cursor: pointer;
}
.select,
.label {
  display: block;
}
.select {
  width: 100%;
  position: absolute;
  top: 0;
  padding: 1em;
  height: 4em;
  opacity: 0;
  background: none transparent;
  border: 0 none;
}
.label {
  /* position: relative; */
  padding: 1em;
  border-radius: 0.5em;
  cursor: pointer;
}
.item {
  display: flex;
  flex-direction: row;
  width: 76%;
}
.label::after {
  content: "▼";
  position: absolute;
  right: 0;
  bottom: 13px;
  padding: 1em;
  /* border-left: 1px solid; */
  height: 1.5px;
}
.open .label::after {
  content: "▲";
}
.select-1 {
  border: 1px solid;
  background: #fcfcfc;
  border-bottom: 0.25em solid darken(#0bf09c, 10);
}
h2 {
  text-align: center;
  margin-bottom: 2%;
}
#head {
  position: relative;
  left: 8%;
}
#date {
  position: relative;
  right: 8%;
}
#select-section {
  position: relative;
  left: 8%;
}
.material-icons {
  position: relative;
  left: 25%;
}
button {
  width: 15%;
}
</style>