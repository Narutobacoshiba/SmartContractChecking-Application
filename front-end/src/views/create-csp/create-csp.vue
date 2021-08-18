<template>
  <div class="container" id="main">
    <div id="header">
      <h1>Create a new Contract-Specific Property</h1>
    </div>
      <div class="row">
        <div class="col-2"><h4>Name</h4></div>
        <div class="col-9"><input class="form-control" type="text" value="Dependency" /></div>
      </div>
      <div class="row">
        <div class="label col-2"><h4>Formular</h4></div>
        <div class="col-9">
          <div class="text-edit textarea">
            <editor-sc />
        </div>
        </div>
      </div>
      <div class="row">
        <div class="col-2"><h4>Description</h4></div>
        <div class="col-9">
          <textarea name="" id="" cols="10" rows="10" class="form-control"></textarea>
        </div>
      </div>
        <div id="btn-group">
          <button class="btn btn-primary btn-sm" @click="routing('save')">
            Save
          </button>
          <button class="btn btn-outline-secondary btn-sm" type="button" @click="routing('cancel')">
            Cancel
          </button>
        </div>
  </div>
</template>

<script>
import EditorSc from "../../components/EditorSc.vue"
export default {
    components:{EditorSc},
  data: function () {
    return {
        description: 'LTL property:self Destruction(t fs i ) =¬(testOnBalance(t fs i ) ∧ containsSelf Destruct(t gs j , s i ))∨ (¬self Destruct(t gs j , s i ) ∪ start(t fs i ))'
    };
  },
  methods: {
      routing(param) {
        if(param == "save"){
            this.$router.push(this.$route.params.parent_path);
        } 
        else if(param == "cancel"){
            this.$router.push(this.$route.params.parent_path);
        }
    },
  },
};
</script>

<style scoped>
#main{
  width: 60%;
}
#header{
  margin-top: 40px;
  margin-bottom: 40px;
  text-align: center;
  font-size: 32px;
  font-weight: bold;
}
.row{
  margin-top: 30px;
}
#name-box{
  width: 100%;
}
select{
  width: 50%;
}
textarea{
  width: 100%;
}
#btn-group{
  width: 100%;
  display: flex;
  align-items: center;
}
button{
    margin: auto;
  margin-top: 40px;
}
textarea{
    height: 100px;
}
</style>