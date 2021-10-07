<template>
  <div id="pro-dia">
    <div class="top side">
      <div class="info">
        <h2 class="info-name">{{name}}</h2>
        <p><a href="">View my Profile</a></p>
      </div>
    </div>
    <div class="up-side side">
      <div class="pro-option op">
        <span>Profile</span>
      </div>
      <div class="setting-option op"><span>Setting</span></div>
    </div>
    <div class="down-side side">
      <div class="signout-option op" @click="logout"><span>Logout</span></div>
    </div>
  </div>
</template>

<script>
import { AuthService } from '../services/auth'

export default {
  name: "profiledialog",
  methods: {
    async logout() {
      await AuthService.makeLogout();
    },
    
  },
  computed: {
    name(){
      return this.$store.state.user.currentUser.name
    }
  }
};
</script>

<style scoped>
#pro-dia {
  position: absolute;
  top: 60px;
  width: 160px;
  right: 0px;
  background-color: white;
  padding: 10px;
  border-radius: 1px 0px 1px 10px;
  box-shadow: 0px 0px 4px rgb(48, 47, 47);
}

.op {
  padding-left: 10px;
  width: 100%;
  height: 50px;
  color: white;
  display: flex;
  align-items: center;
  justify-content: flex-start;
  color: #9c98a5;
  position: relative;
}
.side {
  width: 100%;
  background-color: white;
  display: flex;
  align-items: center;
  flex-direction: column;
  border-width: 1px;
  border-bottom-style: solid;
}
.side:last-child {
  border-bottom-style: none;
}
.info-name {
  margin: 0;
  font-size: 20px;
  font-family: sans-serif;
  font-weight: 700;
  color: #a4a4a8;
}
.info p {
  margin-top: -7px;
  margin-bottom: 7px;
}
.info a {
  text-decoration: underline;
  font-family: sans-serif;
  font-size: 15px;
  text-decoration: none;
  margin: 5px;
  font-size: 13px;
  color: rgba(128, 134, 143, 255);
}
.op span {
  position: absolute;
  left: 40px;
  color: #a4a4a8;
  font-weight: 600;
  font-family: sans-serif;
  font-size: 12px;
}
/* font icon */
.icon {
  color: #69788b;
}
.op:hover,
.top:hover {
  cursor: pointer;
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  background-color: #fafcfe9f;
}
</style>