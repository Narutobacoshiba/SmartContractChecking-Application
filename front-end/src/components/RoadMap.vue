<template>
  <div id="roadmap-body">
    <div id="home-section" @click="goHome">
        <img src="../assets/icon.png" id="home_icon">
    </div>
    <div id="progressbar-section">
      <div id="ps-text">
        <div id="ps-text-step">Step {{getCurrentPageId}} of 7: </div>
        <div id="ps-text-page">{{getCurrentPageName}}</div>
      </div>
      <div id="ps-roadmap">
        <li v-for="page in pages" :key="page.id" :class="{ active: page.id <= getRoadPageId , chosen: page.id == getCurrentPageId}" @click="routing(page)">
          <span class="ttip">
                {{page.name}}
          </span>
        </li>
        
      </div>
    </div>
    <div id="icon-section">
      <div id="list-icon" class="ic-icon" @click="goList">
        <i class="material-icons">view_list</i>
      </div>
      <div id="ic-separator"></div>
      <div id="roadmap-icon" class="ic-icon" @click="goRoadMap">
        <i class="material-icons">map</i>
      </div> 
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      pages: [
        { id: 1, name: "Start", view: "CheckedSCList"},
        { id: 2, name: "Select Smart Contracts", view: "SmartContractSelection"},
        { id: 3, name: "Select Context", view: "ContextSelection"},
        { id: 4, name: "Choose Vulnerabilities", view: "LtlCheckingOptions"},
        { id: 5, name: "Generate SC to CPN",view: "GenerateCPNModel"},
        { id: 6, name: "Check the SCs",view: "CheckCPNModel" },
        { id: 7, name: "Finish",view: "CheckingResult"},
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
    goHome(){
      this.$router.push({ name: "Index" })
    },
    goList(){
      this.$router.push("/list-sc")
    },
    goRoadMap(){
      this.$router.push({ name: "RoadMap" })
    }, 
    routing(page){
      if(page.id <= this.getRoadPageId && page.id != this.getCurrentPageId){
        this.$router.push({ name: page.view})
      }
    }
  },
  mounted(){
    let route_name = this.$route.name
    if(route_name in this.views_to_id){
      let view_id = this.views_to_id[route_name]
      if(view_id > this.$store.getters["data/GetCheckingRoadView"]){
        this.$store.commit("data/SetCheckingRoadView",view_id)
      }
      this.$store.commit("data/SetCurrentRoadView",view_id)
    }
  },
  watch: {
    $route(new_val){
      if(new_val.name in this.views_to_id){
        let view_id = this.views_to_id[new_val.name]
        if(view_id > this.$store.getters["data/GetCheckingRoadView"]){
          this.$store.commit("data/SetCheckingRoadView",view_id)
        }
        this.$store.commit("data/SetCurrentRoadView",view_id)
      }
    }
  },
  computed: {
      getCurrentPageId(){
          return this.$store.getters["data/GetCurrentRoadView"]
        },
      getCurrentPageName(){
        return this.pages[this.getCurrentPageId-1].name
      },
      getRoadPageId(){
        return this.$store.getters["data/GetCheckingRoadView"]
      }
  },
};
</script>

<style scoped>
#roadmap-body{
  position: fixed;
  width: 100%;
  height: 90px;
  min-width: 900px;
  top: 0;
  border-top: 0.5px solid #eaedf0;
  border-bottom: 8px solid #eaedf0;
  display: flex;
  justify-content: space-between;
  background-color: white;
  z-index: 1000;
}

/* ---- section I ---- */
#home-section{
  width: 225px;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
}
#home_icon{
  width: 180px;
  cursor: pointer;
}
/* ---- section II ---- */
#progressbar-section{
  width: calc(100% - 386px);
  height: 100%;

  border-left: 2px solid #eaedf0;
  border-right: 2px solid #eaedf0;
}
#ps-text{
  margin-top: 10px;
  margin-left: 7%;
  height: 20px;
  width: 100%;
  overflow: hidden;
  text-overflow: ellipsis;
  display: flex;
}
#ps-text #ps-text-step{
  color: #969b9e;
  text-transform: uppercase;
  font-size: 12px;
  line-height: 20px;
  font-weight: 500;
  letter-spacing: 1.5px;
}
#ps-text #ps-text-page{
  margin-left: 1%;
  color: rgb(30, 32, 33);
  font-size: 18px;
  line-height: 19px;
  font-weight: 500;
}

#ps-roadmap{
  width: 100%;

  margin-top: 10px;
  display: flex;
  justify-content: center;
  counter-reset: step;
}
#ps-roadmap li {
  float: left;
  width: 17%;
  position: relative;
  text-align: center;
  list-style-type: none;
}

#ps-roadmap li:before {
  content: counter(step);
  counter-increment: step;
  width: 30px;
  height: 30px;
  border: 2px solid #bebebe;
  display: block;
  margin: 0 auto 10px auto;
  border-radius: 4px;
  line-height: 27px;
  background: white;
  color: #bebebe;
  text-align: center;
  font-weight: bold;
  cursor: pointer;
}
#ps-roadmap li:after {
  content: "";
  position: absolute;
  width: 100%;
  height: 2px;
  background: #979797;
  top: 15px;
  left: -50%;
  z-index: -1;
}
#ps-roadmap li.active:before {
  border-color: #5fb8ee;
  background-color: #5fb8ee;
  color: white;
}
#ps-roadmap li.active:after, #ps-roadmap li.chosen:after {
  background-color: #5fb8ee;
}
#ps-roadmap li:first-child:after {
  content: none;
}
#ps-roadmap li .ttip{
  display: none;
}
#ps-roadmap li:hover .ttip{
  display: inline-block;
  background-color: rgb(56, 55, 55);
  opacity: 0.9;
  color: white;
  padding: 5px;
  font-size: 14px;
  border-radius: 3px;
  margin: 0;
}
#ps-roadmap li.chosen:before {
  border-color: #3a7694;
  background-color: #3a7694;
  color: white;
}
/* ---- section III ---- */
#icon-section{
  width: 161px;
  height: 100%;
  display: flex;
}

#ic-separator{
  width: 1px;
  height: 50%;
  margin: auto 0;
  background-color: #eaedf0;
}
.ic-icon{
  width: 80px;
  display: flex;
  justify-content: center;
  align-items: center;
  color: #989c9e;
  cursor: pointer;
}
.ic-icon:hover {
  color: #747779;
}
</style>