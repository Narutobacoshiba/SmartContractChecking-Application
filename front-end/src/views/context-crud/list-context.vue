<template>
  <div id="main">
    <div id="header">Manage Contexts</div>
    <div id="add" class="container">
      <button class="btn btn-outline-primary btn-sm" @click="goAdd">
        Add a Context
      </button>
    </div>
    <div id="table" class="container">
      <div id="tbl-header" class="row">
        <div class="col-2 title">ID</div>
        <div class="col-8 title">Name</div>
        <div class="col-2 title">Action</div>
      </div>
      <div v-for="context in list_context" :key="context.id" class="row list">
        <div class="col-2">{{ context.id }}</div>
        <div class="col-8">{{ context.name }}</div>
        <div class="col-2">
          <i class="material-icons" @click="editContext(context.id)">edit</i>
          <i class="material-icons" @click="deleteContext(context.id,context.name)"
            >delete</i
          >
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { GetContext, DeleteContext } from "../../services/data";
export default {
  data() {
    return {
      list_context: [],
    };
  },
  mounted() {
    this.initData()
  },
  methods: {
    goAdd() {
      this.$router.push({
        name: "AddContext",
        params: { parent_path: "/list-context" },
      });
    },
    editContext(id) {
      this.$router.push({
        name: "EditContext",
        params: { context_id: id, parent_path: "/list-context" },
      });
    },
    async deleteContext(id,ct_name) {
      if(!confirm(`Do you want to delete context ${ct_name}`)){
        return
      }
      console.log(id);
      const response = await DeleteContext(id);
      if (response.status === 200) {
          await this.initData()
      }
    },
    async initData() {
      this.list_context = await GetContext();
    },
  },
  created() {
    
  },
};
</script>

<style scoped>
#main {
  padding-top: 20px;
  background-color: #fafafa;
}
#header {
  margin: auto;
  text-align: center;
  font-size: 35px;
  margin-bottom: 20px;
}
#add {
  width: 70%;
  padding: 0;
  margin-bottom: 10px;
}
#table {
  width: 70%;
  min-width: 600px;
  margin: auto;
  height: 450px;
  border: 1px solid lightblue;
  border-radius: 3px;
}
#tbl-header {
  background-color: #d9edf7;
  height: 40px;
  align-items: center;
  font-weight: bold;
}
#table .list {
  height: 35px;
  border-bottom: 0.5px solid #d8d7d7;
  vertical-align: middle;
  align-items: center;
}
#table .list:hover {
  background-color: #ebebeb;
}
i {
  cursor: pointer;
  margin-right: 10px;
}
</style>