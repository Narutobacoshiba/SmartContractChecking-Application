<template>
  <div class="container">
    <div id="header">Checking Result</div>
    <div class="main">
      <div class="content"></div>
    </div>

    <div class="button">
      <div class="container">
        <div class="row up">
          <div class="col-5">
            <button type="button" class="btn btn-outline-primary">
              Start a new checking session
            </button>
          </div>
          <div class="col-5 right">
            <button type="button" class="btn btn-outline-primary">Back</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {};
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