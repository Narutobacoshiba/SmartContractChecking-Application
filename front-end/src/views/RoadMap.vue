<template>
  <div class="container">
    
    <h1>Roadmap</h1>
  <div id="main">
    <ul class="progressbar">
      <li v-for="page in pages" :key="page.id" :class="{ active: page.id <= getRoadPageId , chosen: page.id == getCurrentPageId}" >
        <a @click="routing(page)" class="dropbtn">{{ page.name }}</a>
        <div class="description">{{page.description}}</div>
      </li>
    </ul>
  </div></div>
</template>

<script>
export default {
  data() {
    return {
      pages: [
        { id: 1, name: "Start", view: "CheckedSCList", description: "The user clicks on the Check Smart Contract to start a new session."},
        { id: 2, name: "Select Smart Contracts", view: "SmartContractSelection", description:"The user selects Smart Contracts for checking. The user can select one smart contract or several smart contracts."},
        { id: 3, name: "Select Context", view: "ContextSelection", description:"The user selects a context for checking. If the user selects several smart contracts in the previous step, the context contains all their functions."},
        { id: 4, name: "Choose Vulnerabilities", view: "LtlCheckingOptions", description:"he user selects a Contract-Specifc Property or Vulnerability for checking."},
        { id: 5, name: "Generate SC to CPN",view: "GenerateCPNModel", description:"The system generates a list containing two Helena fles. These fles include the model, proposition, and property that need to be checked."},
        { id: 6, name: "Check the SCs",view: "CheckCPNModel", description:"The system calls Helena checker tool to check the property or vulnerability that generated in the previous step"},
        { id: 7, name: "Finish",view: "CheckingResult", description:"The system calls Helena checker tool to check the property or vulnerability that generated in the previous step"},
      ],
      views_to_id:{"CheckedSCList":1,
                  "SmartContractSelection":2,
                   "ContextSelection":3,"UploadContext":3,
                   "LtlCheckingOptions":4,"CSPSettingNonTemp":4,"GeneralVulSetting":4,"InitialMarkingSetting":4,"CSPPropertyTemp":4,
                   "GenerateCPNModel":5,
                   "CheckCPNModel":6,
                   "CheckingResult":7},
    }
  },
  methods: {
    routing(page){
        console.log(page)
      if(page.id <= this.getRoadPageId){
        this.$router.push({ name: page.view})
      }
    }
  },
  computed: {
      getCurrentPageId(){
          return this.$store.getters["data/GetCurrentRoadView"]
      },
      getRoadPageId(){
        return this.$store.getters["data/GetCheckingRoadView"]
      }
  }
};
</script>

<style scoped>
h1{
  text-align: center;
  margin-top: 30px;
}
#main{
  height: 560px;
  width: 50%;
  max-width: 500px;
  margin-left: calc(50% - 380px);
  box-sizing: border-box;
}
.container{
  align-items: center;
}
.progressbar{
  position: relative;
  top: 52%;
  transform: translateY(-50%);
}
.progressbar{
  position: relative;
  counter-reset: step;
}
li{
  list-style: none;
}
.progressbar::after{
  content: '';
  position: absolute;
  width: 1.5px;
  height: calc(100% - 60px);
  right: 90px;
  top: 0;
  background: black;
  z-index: -1;
  margin-top: 5px;
  transform: translateY(5%);
}
.progressbar ul li{
  line-height: 300px;
}
.progressbar li a{
  font-size: 1.2rem;
  line-height: 5rem;
  font-weight: 500;
  
}
.progressbar li a::before {
  content: counter(step);
  counter-increment: step;
  background-color: red;
  position: absolute;
  width: 30px;
  height: 30px;
  line-height: 1.5;
  text-align:  center;
  right: 76px;
  border: 2px solid #929292;
  border-radius: 50%;
  font-size: 1rem;
  transform: translateY(80%);
  background: white;
  color: #bebebe;
  text-align: center;
  font-weight: bold;
}
.progressbar li.active a:before {
  border-color: rgb(91, 206, 91);
  background-color: rgb(91, 206, 91);
  color: white;
}
.progressbar li.choosen a:before {
  border-color: rgb(16, 100, 16);
  background-color: rgb(16, 100, 16);
  color: white;
}
li a{
  text-decoration: none;
  color: black;
}
li.active a{
  color: #0d6efd;
  text-decoration: underline;
}
li.active a:hover{
  cursor: pointer;
}
.dropbtn:hover ~ .description{
  display: block;
}

.description{
    position: absolute;
    height: 60px;
    width: 400px;
    border: 2px solid rgb(49, 49, 49);
    border-radius: 4px;
    padding: 1px 2px 1px 2px;
    margin-left: 440px;
    margin-top: -60px;
    font-size: 13px;
    display: none;
}

@media only screen and (max-width: 960px) {
  #main{
    width: 100%;
    margin: auto;
  }
  .progressbar::after{
    right: 20px;
  }
  .progressbar li a::before{
    right: 6px;
  }
  .progressbar{
    margin: auto;
  }
}
</style>