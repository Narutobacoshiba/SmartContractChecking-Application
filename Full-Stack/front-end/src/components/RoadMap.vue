<template>
  <div id="roadmap-body">
    <div id="home-section" @click="goHome">
        <img src="../assets/icon.png" id="home_icon">
    </div>
    <div id="progressbar-section">
      <div id="ps-text">
        <c>Step {{current_page}} of 6: </c><b>{{pages[current_page-1].name}}</b>
      </div>
      <div id="ps-roadmap">
        <li v-for="page in pages" :key="page.id" :class="{ active: page.id <= road_page , chosen: page.id == current_page}" @click="routing(page)">
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
        { id: 1, name: "Select Smart Contracts", view: "sc-selection"},
        { id: 2, name: "Select Context", view: "select-context"},
        { id: 3, name: "Choose Vulnerabilities", view: "choose-vul"},
        { id: 4, name: "Generate SC to CPN",view: "generate-sc2cpn"},
        { id: 5, name: "Check the SCs",view: "check-sc" },
        { id: 6, name: "Finish",view: "finish"},
      ],
      hover: true,
    };
  },
   methods: {
    goHome(){
      this.$router.push("/")
    },
    goList(){
      this.$router.push("/list-sc")
    },
    goRoadMap(){
      this.$router.push("/roadmap")
    }, 
    routing(page){
      if(page.id <= this.road_page){
        this.$store.commit("data/SetProcessView",page.view)
      }
    }
  },
  computed: {
      current_page(){
            var view = this.$store.getters["data/GetProcessView"]
            var id = this.pages.filter(item => {
            return item.view == view;
          })[0].id
          return id
        },
      road_page(){
        return this.$store.getters["data/GetRoadPage"]
      }
  },
};
</script>

<style scoped>
#roadmap-body{
  width: 100%;
  height: 90px;

  border-top: 0.5px solid #eaedf0;
  border-bottom: 8px solid #eaedf0;
  display: flex;
  justify-content: space-between;
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
  height: 17.6px;
  overflow: hidden;
  text-overflow: ellipsis;
}
#ps-text c{
  color: #969b9e;
  text-transform: uppercase;
  font-size: 12px;
  line-height: 20px;
  font-weight: 500;
  letter-spacing: 1.5px;
}
#ps-text d{
  margin-left: 1%;
  color: rgb(30, 32, 33);
  font-size: 20px;
  line-height: 28px;
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
  background-color: black;
  opacity: 0.8;
  color: white;
  padding: 5px;
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