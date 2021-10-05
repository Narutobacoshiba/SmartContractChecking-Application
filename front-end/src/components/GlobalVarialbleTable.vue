<template>
  <div class="container">
    <div class="row">
      <div class="col-2 full-size">Global Variables</div>
      <div class="col-8 full-size">
        <div class="table-list">
          <div class="row" id="header">
            <div class="col-2">
              # <span class="material-icons icon"> swap_vert </span>
            </div>
            <div class="col-8">
              Global Variables
              <span class="material-icons icon">swap_vert</span>
            </div>
            <div class="col-2 select">Select All <input type="checkbox" /></div>
          </div>
          <div class="row">
            <div class="col-2">1</div>
            <div class="col-8">Function1</div>
            <div class="col-2 select">
              <input type="checkbox" />
            </div>
          </div>
        </div>
      </div>
      <div class="col-2"></div>
    </div>
  </div>
</template>

<script>
export default {};
</script>

<style scoped>
.title {
  text-align: center;
  font-size: 1.5em;
  font-weight: bold;
}
.row {
  margin: 2% 0%;
  text-align: left;
  width: 100%;
}
.table-list .row {
  height: 30px;
  background-color: #ffffff;
  border-top: 1px solid #dee2e6;
  vertical-align: middle;
  align-items: center;
  margin: 0;
}
.table-list .row:hover {
  background-color: #f5f5f5;
}
#header {
  background-color: #c2cad183;
  height: auto;
  min-height: 35px;
  font-weight: bold;
  margin: 0;
  padding: 0;
}
.table-list {
  width: 100%;
  margin: auto;
  font-size: 0.9em;
  height: auto;
  max-height: 250px;
  min-height: 140px;
  overflow-y: auto;
  border-radius: 5px;
  padding: 0;
  border: solid #c2cad183 1px;
}
.up-down {
  display: inline-block;
}
.icon:hover {
  cursor: pointer;
  opacity: 0.9;
  color: dimgrey;
}
.icon {
  float: right;
  margin: 0 20% 0 0;
  padding: 0;
  font-size: 150%;
}
.select {
  text-align: center;
}

input[type="checkbox"] {
  transform: scale(1.2);
  cursor: pointer;
}
@media only screen and (max-width: 960px) {
  [class*="full-size"] {
    width: 100%;
  }
  span {
    margin: 0;
  }
}
</style>