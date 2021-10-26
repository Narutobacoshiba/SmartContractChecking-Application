<template>
  <div class="container">
    <div id="header">Checking Result</div>
    <div class="main">
      <div class="content"> {{done_result}}</div>
    </div>

    <div class="button">
      <div class="container">
        <div class="row up">
          <div class="col-5">
            <button type="button" class="btn btn-outline-primary">
              Checking with the same LTL properties and different configurations
            </button>
          </div>
          <div class="col-6 right">
            <button type="button" class="btn btn-outline-primary">
              Checking with different LTL properties
            </button>
          </div>
        </div>

        <div class="row">
          <div class="col-5">
            <button type="button" class="btn btn-outline-primary">
              Start a new checking session
            </button>
          </div>
          <div class="col-6 right">
            <button type="button" class="btn btn-outline-primary">Back</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  computed: {
    done_result() {
      return this.$store.getters.Getrs;
    },
  }
};
</script>

<style>
#header {
  text-align: center;
  font-weight: bolder;
  font-size: 30px;
  margin-bottom: 70px;
}

.main {
  display: flex;
  justify-content: center;
}
.content {
  width: 800px;
  border: 1px solid black;
  width: 60%;
  height: 300px;
  font-weight: bolder;
  margin-bottom: 100px;
}

.right {
  text-align: right;
}

.up {
  margin-bottom: 20px;
}
</style>