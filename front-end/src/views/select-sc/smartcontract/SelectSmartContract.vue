<template>
  <div id="ssc-body">
    <div id="ssc-header">Select Smart Contracts</div>
    <div id="ssc-selected">
      <div class="smart">
        <div class="grey">
          <span>Common Smart Contracts</span>
        </div>
        <div class="blue">
          <div class="atable">
            <table class="table table-striped table-hover table-sm">
              <thead class="table-dark">
                <tr>
                  <th style="width: 20%" scope="col">#</th>
                  <th style="width: 60%" scope="col">Smart Contract Name</th>
                  <th style="width: 20%" scope="col">Select</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <th scope="row">1</th>
                  <td>EtherGame</td>
                  <td>
                    <input
                      type="checkbox"
                      id="one"
                      value="One"
                      v-model="picked"
                    />
                  </td>
                </tr>
                <tr>
                  <th scope="row">2</th>
                  <td>EtherLotto</td>
                  <td>
                    <input
                      type="checkbox"
                      id="two"
                      value="Two"
                      v-model="picked"
                    />
                  </td>
                </tr>
                <tr>
                  <th scope="row">3</th>
                  <td>blindAuction</td>
                  <td>
                    <input
                      type="checkbox"
                      id="the"
                      value="Three"
                      v-model="picked"
                    />
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>

        <div class="grey">
          <span>Private Smart Contracts</span>
        </div>
        <div class="blue">
          <div class="atable">
            <table class="table table-striped table-hover table-sm">
              <thead class="table-dark">
                <tr>
                  <th style="width: 20%" scope="col">#</th>
                  <th style="width: 60%" scope="col">Smart Contract Name</th>
                  <th style="width: 20%" scope="col">Select</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <th scope="row">1</th>
                  <td>PSC1</td>
                  <td>
                    <input
                      type="checkbox"
                      id="one"
                      value="One"
                      v-model="picked"
                    />
                  </td>
                </tr>
                <tr>
                  <th scope="row">2</th>
                  <td>PSC2</td>
                  <td>
                    <input
                      type="checkbox"
                      id="two"
                      value="Two"
                      v-model="picked"
                    />
                  </td>
                </tr>
                <tr>
                  <th scope="row">3</th>
                  <td>PSC3</td>
                  <td>
                    <input
                      type="checkbox"
                      id="the"
                      value="Thee"
                      v-model="picked"
                    />
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>
      </div>

      <div id="ssc-action">
        <div id="first-action">
          <div id="ssc-add" @click="routing('add')">Add</div>
        </div>
        <div id="second-action">
          <div id="ssc-upload" @click="routing('uploadfile')">Upload File</div>
        </div>
        <div id="third-action">
          <div id="ssc-back" @click="routing('back')">Back</div>
        </div>
      </div>
    </div>
  </div>
  <!-- </div> -->
</template>

<script>
export default {
  data() {
    return {};
  },
  methods: {
    routing(param) {
      if (param == "add") {
        this.$router.push({ name: "ContextOfSmartContract" });
      }
      if (param == "back") {
        this.$router.push({ name: "ListOfCheckedTransactions" });
      }
      if (param == "uploadfile") {
        this.$router.push({ name: "UpLoadSc" });
      }
    },
  },
};
</script>

<style scoped>
.blue {
  width: 100%;
  height: 200px;
  color: black;
}
.grey {
  width: 200px;
  height: 30px;
  color: black;
}
.grey {
  margin-left: 20px;
  margin-bottom: 25px;
  background: white;
  z-index: 3;
  position: relative;
}
.blue {
  border: 1px solid black;
  margin-top: -40px;
  background: none;
  z-index: 2;
  position: relative;
}
h1 {
  text-align: center;
}

.atable {
  margin-left: 25px;
  margin-top: 20px;
  margin-right: 25px;
}

#ssc-body {
  width: 100%;
  height: 530px;
}
#ssc-header {
  margin-top: 20px;
  text-align: center;
  font-size: 35px;
  font-weight: bold;
  margin-bottom: 20px;
}
#ssc-selected {
  width: 60%;
  margin: 0 auto;
}

#sscs-body {
  height: 350px;
  width: 100%;
  border: 1px solid #d9edf7;
  border-radius: 6px;
}
#sscs-header {
  width: 100%;
  height: 40px;
  background-color: #d9edf7;
  padding: 9px;
}
#sscs-header #sscsh-name {
  display: inline-block;
  margin-left: 4%;
  font-size: 13;
  font-weight: bold;
  color: #3a7694;
}
#sscs-header #rma-button {
  width: 100px;
  height: 24px;
  float: right;
  border: 1px solid #4b97bd;
  border-radius: 2px;
  color: #4b97bd;
  padding: 0px 8px;
  cursor: pointer;
}
#sscs-header #rma-button:hover {
  background-color: #3c7c9c;
  color: white;
}
#sscs-table {
  width: 100%;
  height: 310px;
  overflow-y: auto;
}

#link-text {
  color: #5ca5d3;
  font-weight: bold;
  cursor: pointer;
}
#link-text:hover {
  color: #77c0ec;
}
.noneHandler {
  font-size: 13px;
  margin-top: 10px;
  margin-left: 10px;
  color: rgb(43, 41, 41);
}

/* --- table --- */
.table-row {
  width: 100%;
  height: 40px;

  display: flex;
  color: #585858;
  border-bottom: 0.5px solid #d8d7d7;
}
.index-cell {
  flex-basis: 10%;
  justify-content: center;
}
.name-cell {
  flex-basis: 70%;
  padding-left: 6%;
  justify-content: left;
  overflow: hidden;
  text-overflow: ellipsis;
}
.action-cell {
  flex-basis: 20%;
  justify-content: center;
}
.action-cell i {
  padding: 8px;
  color: #858383;
  cursor: pointer;
}
.table-cell {
  overflow: hidden;
  display: flex;
  align-items: center;
}
.table-row:hover {
  background-color: #fafafa;
}
.action-cell i:hover {
  color: #5e5d5d;
}

/* --- action --- */
#ssc-action {
  width: 100%;
  display: flex;
  justify-content: space-between;
  margin: 0 auto;
  margin-top: 30px;
}
#first-action {
  flex-basis: 20%;
}
#second-action {
  flex-basis: 60%;
}
#third-action {
  flex-basis: 15%;
}
#fourth-action {
  flex-basis: 5%;
}
#ssc-add {
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
#ssc-add:hover {
  background-color: #1079cf;
}
#ssc-upload {
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
#ssc-upload:hover {
  background-color: #1079cf;
}
#ssc-back {
  width: 60px;
  height: 30px;
  border: 1px solid rgb(221, 227, 240);
  border-radius: 4px;
  text-align: center;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  cursor: pointer;
}
#ssc-back:hover {
  border-color: #1079cf;
  color: #1079cf;
}
#ssc-next {
  width: 60px;
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
#ssc-next:hover {
  background-color: #1079cf;
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