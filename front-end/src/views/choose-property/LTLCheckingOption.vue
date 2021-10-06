<template>
  <div>
    <div id="pc-body">
      <div id="pcb-header">
        <h1>Property Checking Options</h1>
      </div>
      <div id="pcb-content">
        <p>Please choose your way to check the Smart Contracts:</p>
        <ul>
          <li>
            Contract-Specific Property: You will choose the functions and using
            template or non-template to design your LTL formular.
          </li>
          <li>
            General Vulnerability: You will select the common vulnerability from
            the list
          </li>
        </ul>
      </div>
      <div id="pcb-button">
        <a
          class="link-button"
          @click="goCSP"
          :class="{ choosen_button: getCurrentChoose == 'csps-choosetypes' }"
          >Check a Contract-Specifc Property</a
        >
        <a
          class="link-button"
          @click="goGV"
          :class="{ choosen_button: getCurrentChoose == 'check-general-vul' }"
          >Check a General Vulnerability
        </a>
      </div>
      <div id="showConfirmation" v-if="showDialog">
        <div id="components-holder">
          <confirm @cancel="closeDialog" @confirm="cfChange" :dialog="dialog" />
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {};
  },
  methods:{
    goCSP(){
      this.$router.push({name:"CSPSettingType"})
    },
    goGV(){
      this.$router.push({name:"GenaralVulSetting"})
    }
  }
};
</script>

<style scoped>
#pc-body {
  width: 600px;
  margin: 0 auto;
  margin-top: 100px;
  padding: 20px;
}
#pcb-header h1 {
  font-size: 35px;
  margin-bottom: 40px;
  font-weight: bold;
  text-align: center;
}

#pcb-content {
  width: 100%;
  margin-top: 60px;
}
#pcb-content p {
  font-size: 16px;
  font-weight: bold;
  color: rgb(97, 97, 97);
}
#pcb-content li {
  font-size: 14px;
  color: rgb(145, 144, 144);
}
#pcb-button {
  margin-top: 40px;
  width: 100%;
  display: flex;
  justify-content: space-between;
}
.link-button {
  background-color: #0090f2;
  padding: 4px 15px;
  border-radius: 4px;
  color: #fff;
  font-weight: bold;
  font-size: 14px;
  transition: all 0.3s linear;
  cursor: pointer;
  text-decoration: none;
  margin-right: 10px;
}
.link-button:hover {
  background-color: #156fac;
  color: #fff;
}
.choosen_button {
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
.choosen_button:hover {
  background-color: #1079cf;
  color: white;
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
#components-holder {
  width: 50%;
  margin: auto;
  margin-top: 200px;
}
</style>