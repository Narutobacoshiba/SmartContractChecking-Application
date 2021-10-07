<template>
  <div class="container">
    <div class="smart">
      <h1>Check Reentrancy Detailed Information</h1>
      <div class="grey">
        <span>Details information</span>
      </div>
      <div class="blue">
        <div class="atable">
          <table class="table table-striped table-hover table-sm">
            <thead class="header">
              <tr>
                <th style="width: 10%" scope="col">#</th>
                <th style="width: 30%" scope="col">Smart Contract Name</th>
                <th style="width: 15%" scope="col">Context</th>
                <th style="width: 15%" scope="col">LTL</th>
                <th style="width: 10%" scope="col">Status</th>
                <th style="width: 20%" scope="col">Result</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <th scope="row">1</th>
                <td>Mark</td>
                <td>Otto</td>
                <td>@mdo</td>
                <td>Mark</td>
                <td>Otto</td>
              </tr>
              <tr>
                <th scope="row">2</th>
                <td>Jacob</td>
                <td>Thornton</td>
                <td>@fat</td>
                <td>Thornton</td>
                <td>@fat</td>
              </tr>
              <tr>
                <th scope="row">3</th>
                <td>Larry the Bird</td>
                <td>Larry the Bird</td>
                <td>@twitter</td>
                <td>Larry the Bird</td>
                <td>@twitter</td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
    <div class="Button">
      <div class="row">
        <div class="col-sm-10">
          <!-- <button type="button" class="btn btn-primary" @click="routing('addsc')">
            Add Smart Contracts
          </button> -->
        </div>
        <div class="col-sm-2">
          <button type="button" class="btn btn-primary" @click="routing('back')">Back</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  methods: {
    routing(param) {
      if (param == "back") {
        this.$router.push({ name: "ListOfCheckedTransactions" });
      }
      if (param == "addsc") {
        this.$router.push({ name: "SelectSmartContract" });
      }
    }, //Back to List Of Checked Transactions
  },
};
</script>

<style scoped>
.blue {
  width: 100%;
  height: 450px;
  color: black;
}
.grey {
  width: 150px;
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
  border-radius: 10px;
}
h1 {
  text-align: center;
}

.atable {
  margin-left: 25px;
  margin-top: 20px;
  margin-right: 25px;
}

.Button {
  margin-top: 80px;
}

.header {
  background-color: rgb(144, 208, 243);
}
</style>