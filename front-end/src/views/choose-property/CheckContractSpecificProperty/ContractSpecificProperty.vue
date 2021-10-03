<template>
  <div>
    <div id="pc-body">
      <div id="pcb-header">
        <h1>Contract-Specifc Property Setting - Choose Types</h1>
      </div>
      <div id="pcb-content">
        <p>Please choose your type of Contract-Specifc Property:</p>
        <ul>
          <li>Template: You will design the property by using our template</li>
          <li>Non-template: You will design the property by your own</li>
        </ul>
      </div>
      <div id="pcb-button">
        <a class="link-button" @click="routing('template')">Template</a>
        <a class="link-button" @click="routing('non-template')">Non-template</a>
        <a class="link-button" @click="routing('back')">Back</a>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  methods: {
    routing(param) {
      if (param == "template") {
        this.$router.push({ name: "CSPTemplateSetting" });
      }
      if (param == "non-template") {
        this.$router.push({ name: "CSPNonTemplateSetting" });
      }
      if (param == "back") {
        this.$router.push({ name: "LTLCheckOption" });
      }
    },
  },
};
</script>

<style scoped>
#pc-body {
  width: 600px;
  margin: 0 auto;
  margin-top: 100px;
}
#pcb-header {
  text-align: center;
}
#pcb-header h1 {
  font-size: 40px;
  line-height: 46px;
  margin-bottom: 40px;
}

#pcb-content {
  width: 100%;
  margin-top: 100px;
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
  background: #0090f2;
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
  background: #156fac;
  color: #fff;
}
.choosen_button {
  background-color: #105a8b;
}
.choosen_button:hover {
  background-color: #0b4368;
}
</style>
