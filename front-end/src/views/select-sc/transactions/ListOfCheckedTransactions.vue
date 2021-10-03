<template>
  <div class="container">
    <div class="smart">
      <h1>List of Checked Transctions</h1>
      <div class="grey">
        <span>Checked information</span>
      </div>
      <div class="blue">
        <div class="atable">
          <table class="table table-striped table-hover table-sm">
            <thead class="table-dark">
              <tr>
                <th style="width: 10%" scope="col">#</th>
                <th style="width: 40%" scope="col">Batch Name</th>
                <th style="width: 25%" scope="col">Checked Date</th>
                <th style="width: 25%" scope="col">Description</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <th scope="row">1</th>
                <td>Mark</td>
                <td>Otto</td>
                <td>@mdo</td>
              </tr>
              <tr>
                <th scope="row">2</th>
                <td>Jacob</td>
                <td>Thornton</td>
                <td>@fat</td>
              </tr>
              <tr>
                <th scope="row">3</th>
                <td>Larry the Bird</td>
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
        <div class="col-sm-8">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('addsc')"
          >
            Add Smart Contracts
          </button>
        </div>
        <div class="col-sm-2">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('back')"
          >
            Back
          </button>
        </div>
        <div class="col-sm-2">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('next')"
          >
            Next
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  methods: {
    routing(param) {
      if (param == "next") {
        this.$router.push({ name: "CheckRentrancy" });
      }
      if (param == "addsc") {
        this.$router.push({ name: "SelectSmartContract" });
      }
      if ((param == "back")) {
        this.$router.push({ name: "Index" });
      }
    },
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
</style>