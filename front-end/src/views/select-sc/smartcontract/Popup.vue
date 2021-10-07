<template>
  <div class="wrapper-popup" v-bind:class="{ open: isOpen == true }">
    <div class="rule">
      <p>You have chosen to open:</p>
      <p>etherPropose.sol (200kb)</p>
      <h3>What should Browser do with this file?</h3>
      <div class="form-check ck">
        <input
          class="form-check-input"
          type="radio"
          name="flexRadioDefault"
          id="flexRadioDefault1"
        />
        <label class="form-check-label" for="flexRadioDefault1">
          Open with Brrowser
        </label>
      </div>

      <div class="row ck">
        <div class="col">
          <div class="form-check">
            <input
              class="form-check-input"
              type="radio"
              name="flexRadioDefault"
              id="flexRadioDefault2"
            />
            <label class="form-check-label" for="flexRadioDefault2">
              Open with
            </label>
          </div>
        </div>
        <div class="col">
          <div class="dropdown">
            <button
              class="btn btn-secondary dropdown-toggle"
              type="button"
              id="dropdownMenuButton1"
              data-bs-toggle="dropdown"
              aria-expanded="false"
            >
              Document Viewer(default)
            </button>
            <ul class="dropdown-menu" aria-labelledby="dropdownMenuButton1">
              <li><a class="dropdown-item" href="#">Action</a></li>
              <li><a class="dropdown-item" href="#">Another action</a></li>
              <li><a class="dropdown-item" href="#">Something else here</a></li>
            </ul>
          </div>
        </div>
      </div>

      <div class="form-check ck">
        <input
          class="form-check-input"
          type="radio"
          name="flexRadioDefault"
          id="flexRadioDefault2"
          checked
        />
        <label class="form-check-label" for="flexRadioDefault2">
          Save File
        </label>
      </div>

      <div class="form-check">
        <input
          class="form-check-input"
          type="checkbox"
          value=""
          id="flexCheckDefault"
        />
        <label class="form-check-label" for="flexCheckDefault">
          Do this automaticlly for fles like this from now on
        </label>
      </div>

      <div class="row">
        <div class="col but1">
          <button class="confirm" v-on:click="dahieu">Cancel</button>
        </div>
        <div class="col but2">
          <button class="confirm" @click="routing('uploadfile')">OK</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "popup-rule",
  data() {
    return {};
  },
  props: {
    isOpen: { type: Boolean, default: false },
  },
  computed: {
    getOpen() {
      return {
        open: this.isOpen,
      };
    },
  },
  methods: {
    routing(param) {
      if (param == "uploadfile") {
        this.$router.push({ name: "UpLoadSc" });
      }
    },
    dahieu() {
      this.$emit("clickdahieu");
    },
  },
};
</script>

<style>
.wrapper-popup {
  z-index: 100;
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: rgba(0, 0, 0, 0.4);
  opacity: 0;
  visibility: hidden;
  transition: all 0.3s ease;
}
.wrapper-popup.open {
  opacity: 1;
  visibility: visible;
}
.rule {
  width: 650px;
  padding: 20px;
  font-family: Arial, Helvetica, sans-serif;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%) scale(1.2);
  background-color: #ffffff;
  position: absolute;
  transition: all 0.3s ease;
}
.open .rule {
  transform: translate(-50%, -50%) scale(1);
}
.rule h3 {
  margin-bottom: 10px;
}
.confirm {
  border: 2px solid #333;
  background-color: #ffff;
  padding: 8px 15px;
  margin-top: 20px;
  cursor: pointer;
  transition: all 0.3s ease;
  width: 80px;
}
.confirm:hover {
  background-color: aqua;
  color: red;
}
.row{ 
  padding-bottom: 2%;
  padding-right: 10%;
}
.ck {
  margin-top: 20px;
  margin-bottom: 20px;
}
.but1 {
  text-align: right;
}
.but2 {
  text-align: center;
}
</style>